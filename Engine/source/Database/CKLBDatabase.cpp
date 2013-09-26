/* 
   Copyright 2013 KLab Inc.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
#include <stdio.h>
#include <stdlib.h>
#include "CKLBDatabase.h"
#include "CPFInterface.h"
#include "encryptFile.h"

// Get a private global symbol owning all the file systems of SQLite.
extern "C" {
	sqlite3_vfs*	gVfsList;
}

// Global Table of IO Methods for encrypted SQLite.
sqlite3_io_methods		gSQLiteEncryptIO;
int						gBaseSizeOsFile;
bool					gInitOnce = true;
int (*gOpenDefaultSQLite)	(sqlite3_vfs*, const char *zName, sqlite3_file*,int flags, int *pOutFlags);

#define	getFileDecrypt(a)			(WrapperFileDecrypt*)(&(((unsigned char*)a)[gBaseSizeOsFile]))

struct WrapperFileDecrypt {
	// Decrypt
	// File ptr
	// + Key, decrypt flag, ...
	CDecryptBaseClass	m_decrypt;
	int					m_size;
	void*				m_file;
	bool				m_no_op;
	int					m_hasHeader;
};

// === SQLite OS Methods ===
int fEncryptOpen					(sqlite3_vfs*, const char *zName, sqlite3_file*, int flags, int *pOutFlags);

// === SQLite IO Methods ===
int fEncryptClose					(sqlite3_file*);
int fEncryptRead					(sqlite3_file*, void*, int iAmt, sqlite3_int64 iOfst);
int fEncryptWrite					(sqlite3_file*, const void*, int iAmt, sqlite3_int64 iOfst);
int fEncryptTruncate				(sqlite3_file*, sqlite3_int64 size);
int fEncryptSync					(sqlite3_file*, int flags);
int fEncryptFileSize				(sqlite3_file*, sqlite3_int64 *pSize);
int fEncryptLock					(sqlite3_file*, int);
int fEncryptUnlock					(sqlite3_file*, int);
int fEncryptCheckReservedLock		(sqlite3_file*, int *pResOut);
int fEncryptFileControl				(sqlite3_file*, int op, void *pArg);
int fEncryptSectorSize				(sqlite3_file*);
int fEncryptDeviceCharacteristics	(sqlite3_file*);
int fEncryptShmMap					(sqlite3_file*, int iPg, int pgsz, int, void volatile**);
int fEncryptShmLock					(sqlite3_file*, int offset, int n, int flags);
void 
	fEncryptShmBarrier				(sqlite3_file*);
int fEncryptShmUnmap				(sqlite3_file*, int deleteFlag);

int fEncryptClose					(sqlite3_file* file)
{
	WrapperFileDecrypt* fileDecrypt = getFileDecrypt(file);
	if (!fileDecrypt->m_no_op) {
		CPFInterface::getInstance().platform().ifclose(fileDecrypt->m_file);
	}

	// SQLITE_IOERR_CLOSE
	return SQLITE_OK;
}

int fEncryptRead					(sqlite3_file* file, void* buff, int iAmt, sqlite3_int64 iOfst)
{
	WrapperFileDecrypt* fileDecrypt = getFileDecrypt(file);

	if (!fileDecrypt->m_no_op) {
		fileDecrypt->m_decrypt.gotoOffset((u32)iOfst);

		IPlatformRequest& pltf = CPFInterface::getInstance().platform();
		pltf.ifseek(fileDecrypt->m_file, (long)(iOfst + (fileDecrypt->m_hasHeader * 4)), SEEK_SET);
		u32 readSize = pltf.ifread(buff, 1, iAmt, fileDecrypt->m_file);

		fileDecrypt->m_decrypt.decryptBlck(buff, readSize);

		if (readSize < iAmt) {
			/* Unread parts of the buffer must be zero-filled */
			memset(&((char*)buff)[readSize], 0, iAmt-readSize);
			return SQLITE_IOERR_SHORT_READ;
		}

		// printf("fEncryptRead Amount[%i] Offset[%i] \n", iAmt, iOfst);
	} else {
		// No op for read.
		return SQLITE_IOERR;
	}

	return SQLITE_OK;
}

int fEncryptWrite					(sqlite3_file* file, const void* data, int iAmt, sqlite3_int64 iOfst)
{
	WrapperFileDecrypt* fileDecrypt = getFileDecrypt(file);

	if (!fileDecrypt->m_no_op) {
		IPlatformRequest& pltf = CPFInterface::getInstance().platform();
		int err = pltf.ifseek(fileDecrypt->m_file, (long)(iOfst + (fileDecrypt->m_hasHeader*4)), SEEK_SET);

		if (!err) {
			if (iAmt != 0) {
				// Recompute key at offset.
				fileDecrypt->m_decrypt.gotoOffset((u32)iOfst);

				// Allocate encrypted buffer
				u8* buff = (u8*)malloc(iAmt);

				if (buff) {
					// Copy original buffer
					memcpy(buff,data,iAmt);
					// Encrypt Buffer. (NOTE : could optimize memcpy by having a SOURCE AND DEST BUFFER)
					fileDecrypt->m_decrypt.decryptBlck(buff, iAmt);
					pltf.ifwrite(buff, 1, iAmt, fileDecrypt->m_file);		
					pltf.ifflush(fileDecrypt->m_file);
					free(buff);
				} else {
					return SQLITE_ERROR;
				}
			}
			return SQLITE_OK;
		}
		return SQLITE_ERROR;
	} else {
		return SQLITE_OK;
	}
}

int fEncryptTruncate				(sqlite3_file* /*file*/, sqlite3_int64 /*size*/)
{
	while (1) {	printf("Unsupported"); }
	return SQLITE_OK;
}

int fEncryptSync					(sqlite3_file* /*file*/, int /*flags*/) 
{
	return SQLITE_OK;
}

int fEncryptFileSize				(sqlite3_file* file, sqlite3_int64 *pSize)
{
	if (pSize) {
		WrapperFileDecrypt* fileDecrypt = getFileDecrypt(file);
		if (!fileDecrypt->m_no_op) {
			IPlatformRequest& pltf = CPFInterface::getInstance().platform();
			int err = pltf.ifseek(fileDecrypt->m_file, 0, SEEK_END);
			if (err == 0) {
				*pSize = pltf.iftell(fileDecrypt->m_file) - (fileDecrypt->m_hasHeader * 4);
			} else {
				return SQLITE_ERROR;
			}
		} else {
			*pSize = 0;
		}
		// printf("fEncryptFileSize %i \n", *pSize);
	}
	return SQLITE_OK;
}

int fEncryptLock					(sqlite3_file* /*file*/, int /*lock*/)
{
	// WrapperFileDecrypt* fileDecrypt = (WrapperFileDecrypt*)file;
	// printf("fEncryptLock %i \n", lock);
	return SQLITE_OK;
}

int fEncryptUnlock					(sqlite3_file* /*file*/, int /*unlock*/)
{
	// WrapperFileDecrypt* fileDecrypt = (WrapperFileDecrypt*)file;
	// printf("fEncryptUnLock %i \n", unlock);
	return SQLITE_OK;
}

int fEncryptCheckReservedLock		(sqlite3_file* /*file*/, int* /*pResOut*/)
{
	// WrapperFileDecrypt* fileDecrypt = (WrapperFileDecrypt*)file;
	return SQLITE_OK;
}

int fEncryptFileControl				(sqlite3_file* /*file*/, int /*op*/, void* /*pArg*/)
{
	return SQLITE_OK;
}

int fEncryptSectorSize				(sqlite3_file* /*file*/)
{
	return 4096; // = SQLITE_DEFAULT_SECTOR_SIZE internal value.
}

int fEncryptDeviceCharacteristics	(sqlite3_file* /*file*/)
{
	// printf("fEncryptDeviceCharacteristics %8X\n", SQLITE_IOCAP_UNDELETABLE_WHEN_OPEN | SQLITE_IOCAP_POWERSAFE_OVERWRITE);
	return SQLITE_IOCAP_UNDELETABLE_WHEN_OPEN | SQLITE_IOCAP_POWERSAFE_OVERWRITE;
}

int fEncryptShmMap					(sqlite3_file*, int /*iPg*/, int /*pgsz*/, int, void volatile**)
{
	while (1) {	printf("Unsupported Memory Mapped Files"); }
	return SQLITE_OK;
}

int fEncryptShmLock					(sqlite3_file*, int /*offset*/, int /*n*/, int /*flags*/)
{
	while (1) {	printf("Unsupported Memory Mapped Files"); }
	return SQLITE_OK;
}

void fEncryptShmBarrier				(sqlite3_file*)
{
	while (1) {	printf("Unsupported Memory Mapped Files"); }
	// Do nothing.
}

int fEncryptShmUnmap				(sqlite3_file*, int /*deleteFlag*/)
{
	while (1) {	printf("Unsupported Memory Mapped Files"); }
	return SQLITE_OK;
}

int fEncryptOpen					(sqlite3_vfs* vfs, const char *zName, sqlite3_file* file, int flags, int *pOutFlags) {
	WrapperFileDecrypt* fileDecrypt = getFileDecrypt(file);

	u32			dwFlagsAndAttributes = 0;
	u32			dwCreationDisposition;
	u32			dwDesiredAccess;
	u32			dwShareMode;
	// void *		zConverted;              /* Filename in OS encoding */
	const char*	zUtf8Name	= zName; /* Filename in UTF-8 encoding */
	int			isExclusive = (flags & SQLITE_OPEN_EXCLUSIVE);
	int			isDelete	= (flags & SQLITE_OPEN_DELETEONCLOSE);
	int			isCreate	= (flags & SQLITE_OPEN_CREATE);
	int			isReadonly	= (flags & SQLITE_OPEN_READONLY);
	int			isReadWrite	= (flags & SQLITE_OPEN_READWRITE);

	int			eType       = flags & 0xFFFFFF00;  /* Type of file to open */

	int			isOpenJournal = (isCreate && (	   eType == SQLITE_OPEN_MASTER_JOURNAL 
												|| eType == SQLITE_OPEN_MAIN_JOURNAL 
												|| eType == SQLITE_OPEN_TEMP_JOURNAL
												|| eType == SQLITE_OPEN_SUBJOURNAL
												|| eType == SQLITE_OPEN_WAL
												));

	if (isOpenJournal) {
		// No-Operation
		fileDecrypt->m_no_op	= true;
		fileDecrypt->m_file		= (void*)0xFFFFFFFF;
		// return SQLITE_OK;
		return SQLITE_ERROR;
	} else {
		fileDecrypt->m_no_op	= false;
	}

	/* Check the following statements are true: 
	**
	**   (a) Exactly one of the READWRITE and READONLY flags must be set, and 
	**   (b) if CREATE is set, then READWRITE must also be set, and
	**   (c) if EXCLUSIVE is set, then CREATE must also be set.
	**   (d) if DELETEONCLOSE is set, then CREATE must also be set.
	*/
	klb_assert((isReadonly == 0 || isReadWrite==0) && (isReadWrite || isReadonly), "SQLite Encrypt Wrapper");
	klb_assert(isCreate == 0    || isReadWrite, "SQLite Encrypt Wrapper");
	klb_assert(isExclusive == 0 || isCreate,    "SQLite Encrypt Wrapper");
	klb_assert(isDelete == 0    || isCreate,    "SQLite Encrypt Wrapper");

	/* The main DB, main journal, WAL file and master journal are never 
	** automatically deleted. Nor are they ever temporary files.  */
	klb_assert( (!isDelete && zName) || eType!=SQLITE_OPEN_MAIN_DB ,        "SQLite Encrypt Wrapper");
	klb_assert( (!isDelete && zName) || eType!=SQLITE_OPEN_MAIN_JOURNAL ,   "SQLite Encrypt Wrapper");
	klb_assert( (!isDelete && zName) || eType!=SQLITE_OPEN_MASTER_JOURNAL , "SQLite Encrypt Wrapper");
	klb_assert( (!isDelete && zName) || eType!=SQLITE_OPEN_WAL ,            "SQLite Encrypt Wrapper");

	/* Assert that the upper layer has set one of the "file-type" flags. */
	klb_assert( eType==SQLITE_OPEN_MAIN_DB  || eType==SQLITE_OPEN_TEMP_DB 
											|| eType==SQLITE_OPEN_MAIN_JOURNAL || eType==SQLITE_OPEN_TEMP_JOURNAL 
											|| eType==SQLITE_OPEN_SUBJOURNAL   || eType==SQLITE_OPEN_MASTER_JOURNAL 
											|| eType==SQLITE_OPEN_TRANSIENT_DB || eType==SQLITE_OPEN_WAL, "SQLite Encrypt Wrapper"
	);

	/* If the second argument to this function is NULL, generate a 
	** temporary file name to use 
	*/
	if( !zUtf8Name ){
		klb_assertAlways("Not supported");
		/*
		rc = getTempname(MAX_PATH+2, zTmpname);
		if( rc!=SQLITE_OK ){
		return rc;
		}
		zUtf8Name = zTmpname;
		*/
	}

	/* Database filenames are double-zero terminated if they are not
	** URIs with parameters.  Hence, they can always be passed into
	** sqlite3_uri_parameter().
	*/
	klb_assert( (eType!=SQLITE_OPEN_MAIN_DB) || (flags & SQLITE_OPEN_URI) ||
				zUtf8Name[strlen(zUtf8Name)+1]==0, "SQLite Encrypt Wrapper" );

	/* Convert the filename to the system encoding. */
	/* Not used
	zConverted = convertUtf8Filename(zUtf8Name);
	if( zConverted==0 ){
	return SQLITE_IOERR_NOMEM;
	} */

#define GENERIC_READ		(0x1)
#define GENERIC_WRITE		(0x2)

#define CREATE_NEW					(0x001)
#define OPEN_ALWAYS					(0x002)
#define OPEN_EXISTING				(0x004)
#define FILE_SHARE_READ				(0x008)
#define FILE_SHARE_WRITE			(0x010)
#define FILE_ATTRIBUTE_TEMPORARY	(0x020)
#define FILE_ATTRIBUTE_NORMAL		(0x040)
#define FILE_ATTRIBUTE_HIDDEN		(0x080)
#define FILE_FLAG_DELETE_ON_CLOSE	(0x100)

	if( isReadWrite ){
		dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
	}else{
		dwDesiredAccess = GENERIC_READ;
	}

	/* SQLITE_OPEN_EXCLUSIVE is used to make sure that a new file is 
	** created. SQLite doesn't use it to indicate "exclusive access" 
	** as it is usually understood.
	*/
	if( isExclusive ){
		/* Creates a new file, only if it does not already exist. */
		/* If the file exists, it fails. */
		dwCreationDisposition = CREATE_NEW;
	}else if( isCreate ){
		/* Open existing file, or create if it doesn't exist */
		dwCreationDisposition = OPEN_ALWAYS;
	}else{
		/* Opens a file, only if it exists. */
		dwCreationDisposition = OPEN_EXISTING;
	}

	dwShareMode = FILE_SHARE_READ | FILE_SHARE_WRITE;

	if( isDelete ) {
	#if SQLITE_OS_WINCE
		dwFlagsAndAttributes = FILE_ATTRIBUTE_HIDDEN;
		isTemp = 1;
	#else
		dwFlagsAndAttributes = FILE_ATTRIBUTE_TEMPORARY
		| FILE_ATTRIBUTE_HIDDEN
		| FILE_FLAG_DELETE_ON_CLOSE;
	#endif
	}else{
		dwFlagsAndAttributes = FILE_ATTRIBUTE_NORMAL;
	}

	/** Setup of wrapper for file system in all cases **/
	// Also call the original open.
	// Decided to DO NOT call the gOpenDefaultSQLite(vfs, zName, file, flags, pOutFlags);
	file->pMethods = &gSQLiteEncryptIO; // Patch here because table is patch in original Open.
	// TODO enable decrypt : 
	const char* openMode;
	if (isReadonly) {
		openMode = "rb";
	} else {
		openMode = "r+b";
	}

	IPlatformRequest& pltf = CPFInterface::getInstance().platform();
	void* f = pltf.ifopen(zName, openMode);	// Read and write possible, but must exist.
	
	if (f) {
		fileDecrypt->m_file	= f;
		u8 header[4];
		header[0] = 0;
		header[1] = 0;
		header[2] = 0;
		header[3] = 0;
		pltf.ifread(header,1,4,f);
		fileDecrypt->m_hasHeader = fileDecrypt->m_decrypt.decryptSetup((const u8*)zName, header);

		pltf.ifseek(f, 0, SEEK_END);
		fileDecrypt->m_size = pltf.iftell(f) - (fileDecrypt->m_hasHeader*4);
		pltf.ifseek(f, (fileDecrypt->m_hasHeader*4), SEEK_SET);

		return SQLITE_OK;
	} else {
		if (isCreate && (!isReadonly)) {
			// Force empty file creation
			if (pltf.icreateEmptyFile(zName)) {
				// Call back itself with a working empty file.
				return fEncryptOpen(vfs, zName, file, flags, pOutFlags);
			}
		}
	}
	return SQLITE_ERROR;
}

static bool initEncryptedVFS() {
	// 1. Need initialize first to init vfsList global variable containing the default fileSystem.
	if ((sqlite3_initialize() == SQLITE_OK) && gInitOnce) {
		gInitOnce = false;
		// 2. Init Struct with all function pointers.
		gSQLiteEncryptIO.iVersion					= 2;
		gSQLiteEncryptIO.xClose						= fEncryptClose;
		gSQLiteEncryptIO.xRead						= fEncryptRead;
		gSQLiteEncryptIO.xWrite						= fEncryptWrite;
		gSQLiteEncryptIO.xTruncate					= fEncryptTruncate;
		gSQLiteEncryptIO.xSync						= fEncryptSync;
		gSQLiteEncryptIO.xFileSize					= fEncryptFileSize;
		gSQLiteEncryptIO.xLock						= fEncryptLock;
		gSQLiteEncryptIO.xUnlock					= fEncryptUnlock;
		gSQLiteEncryptIO.xCheckReservedLock			= fEncryptCheckReservedLock;
		gSQLiteEncryptIO.xFileControl				= fEncryptFileControl;
		gSQLiteEncryptIO.xSectorSize				= fEncryptSectorSize;
		gSQLiteEncryptIO.xDeviceCharacteristics		= fEncryptDeviceCharacteristics;
		gSQLiteEncryptIO.xShmMap					= fEncryptShmMap;
		gSQLiteEncryptIO.xShmLock					= fEncryptShmLock;
		gSQLiteEncryptIO.xShmBarrier				= fEncryptShmBarrier;
		gSQLiteEncryptIO.xShmUnmap					= fEncryptShmUnmap;

		gVfsList = getVFSList();

		// 2.1 Patch the fileSystem xOpen function with custom function that wraps sqlist3_file*
		gOpenDefaultSQLite	= gVfsList->xOpen;
		gVfsList->xOpen		= fEncryptOpen;
		// 2.2 Patch the fileSystem vfs->szOsFile, add our own structure. (need to keep original because we wrap open)
		gBaseSizeOsFile		= (gVfsList->szOsFile + 7) & 0xFFFFFFF8;	// Align 8 byte.
		gVfsList->szOsFile	= ((gBaseSizeOsFile + sizeof(WrapperFileDecrypt)) + 7) & 0xFFFFFFF8;
		return true;
	} else {
		return false;
	}
}

static int callbackFct (void* ctx,int colNum,char** columnText,char** columnName) {
	return ((CKLBDatabase*)ctx)->callBack(colNum,columnText,columnName);
}

bool CKLBDatabase::init(const char* dbFile, int flags) {
	// At least initialize the encryption module for DBs, even without default DB.
	IPlatformRequest& platform = CPFInterface::getInstance().platform();
	if (platform.useEncryption()) {
		initEncryptedVFS();
	}

	if ((dbFile == NULL) || (m_dataBase && m_lastDB && strcmp(m_lastDB,dbFile) == 0)) {
		// Database is already known and was last open.
		return true;
	}

	// Else release old Database and old name
	_release();
	int size = strlen(dbFile);
	m_lastDB = KLBNEWA(char, size+1);

	if (m_lastDB) {
		// New name set
		memcpy(m_lastDB, dbFile, size);
		m_lastDB[size] = 0;

		// Convert Logical path to OS Dependant path
		const char* fullPath = platform.getFullPath(dbFile);

		//int rc = sqlite3_open(fullPath, &m_dataBase);
		int rc = sqlite3_open_v2(fullPath, &m_dataBase, flags, NULL);
		delete[] fullPath;

		if (rc) {
			klb_assertAlways("Can not open db %s", dbFile);
			_release();
			return false;
		}

		char * errMsg;
		m_pragmaJournal = true;
		rc = sqlite3_exec(m_dataBase, "PRAGMA journal_mode = OFF;", callbackFct, this, &errMsg);
		m_pragmaJournal = false;

		if (rc) {
			klb_assertAlways("Impossible to disable journal");
		}

		return true;
	} else {
		return false;
	}
}

void CKLBDatabase::_release() {
	if (m_dataBase) {
		sqlite3_close(m_dataBase);
		m_dataBase = NULL;
	}
	KLBDELETEA(m_lastDB);
	m_lastDB = NULL;
}

int CKLBDatabase::callBack(int /*colNum*/,char** columnText,char** /*columnName*/) {
	if (!m_pragmaJournal) {
		if (columnText[0]) {
			m_result = atoi(columnText[0]);
		} else {
			m_result = 0;
		}
	}
	return 0;
}

s32 CKLBDatabase::lookup(const char* table, const char* resultField, const char* className, const char* filterField, s32 filterValue) {
	char buffer[512];

	m_result = 0xDEADBEEF;

	if (className) {
		if (filterField) {
			sprintf(buffer, "SELECT %s FROM %s WHERE %s=%i AND class='%s';",resultField,table,filterField,filterValue,className);
		} else {
			sprintf(buffer, "SELECT %s FROM %s WHERE class='%s';",resultField,table,className); 
		}
	} else {
		if (filterField) {
			sprintf(buffer, "SELECT %s FROM %s WHERE %s=%i;",resultField,table,filterField,filterValue); 
		} else {
			sprintf(buffer, "SELECT %s FROM %s;",resultField,table /*,className */);
		}
	}

	if (runStatement(buffer)) {
		return m_result;
	} else {
		klb_assertAlways("lookup DB failure");
		return 0;	// 0 on failure.
	}
}

bool CKLBDatabase::runStatement(const char* SQLStatement) {
	char* errMsg;
	if (m_dataBase) {
		int rc = sqlite3_exec(m_dataBase, SQLStatement, callbackFct, this, &errMsg);
		if (rc!=SQLITE_OK) {
			klb_assertAlways("DB Error : %s", errMsg);
			sqlite3_free(errMsg);
			return false;
		}
		return true;
	} else {
		klb_assertAlways("DB Not open");
		return false;
	}
}

CKLBDatabase::CKLBDatabase()
:m_dataBase		(NULL)
,m_lastDB		(NULL)
{
}

CKLBDatabase::~CKLBDatabase() {
	_release();
}
