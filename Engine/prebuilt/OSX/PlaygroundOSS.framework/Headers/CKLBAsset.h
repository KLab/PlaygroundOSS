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
//
// === Asset Management System ===
//
//

#ifndef __CKLB_ASSET__
#define __CKLB_ASSET__

#include "RenderingFramework.h"
#include "CKLBAction.h"
#include "FileSystem.h"

class CKLBAssetManager;

/* Create a 32 bit chunk header with FOUR letters*/
#define	CHUNK_TAG(a,b,c,d)		((a<<24)|(b<<16)|(c<<8)|(d))

#define HAS_CREATENODE			(0x80)
enum ASSET_TYPE {
	ASSET_UIFORM			= 0,
	ASSET_ACTIONHANDLER		= 1,
	ASSET_SWFMOVIE			= 2 | HAS_CREATENODE,
	ASSET_VISUALRULES		= 3,
	ASSET_PROPERTYRULES		= 4,
	ASSET_IMAGE				= 5 | HAS_CREATENODE,
	ASSET_TEXTURE			= 6,
	ASSET_ANIMATIONSPLINE	= 7 | HAS_CREATENODE,
	ASSET_AUDIO				= 8,
	ASSET_MAP				= 9 | HAS_CREATENODE,
	ASSET_CELLANIM			=10 | HAS_CREATENODE,
	ASSET_COMPOSITE			=11 | HAS_CREATENODE,
	ASSET_NODEANIM			=12 | HAS_CREATENODE,
	ASSET_AI				=13
};

struct ASSET_ATTRIB {

	u8	attribID;
	u8	type;

	union u {
		const char*	str;
		s32			value;
		float		fvalue;
	} v;

	// --- Use z as first char for IDE reason ---

	// ====
	static const int	zK0_RECT		= 0;

	static const int	zK1_SC_LEFT		= 1;
	static const int	zK1_SC_MIDDLE	= 2;
	static const int	zK1_SC_RIGHT	= 3;
	static const int	zK1_SC_HASBITMAP= 4;
	static const int	zK1_SC_ISVERTICAL=12;

	static const int	zK2_S9_LEFT		= 5;
	static const int	zK2_S9_MIDDLEX	= 6;
	static const int	zK2_S9_RIGHT	= 7;
	static const int	zK2_S9_TOP		= 8;
	static const int	zK2_S9_MIDDLEY	= 9;
	static const int	zK2_S9_BOTTOM	= 10;

	static const int	z3DMODEL		= 11;
	static const int	zK3_OFFSET		= 13;

	static const int	zK4_STRETCH_OR_SCALE	= 14;
	// last used zK4_STRETCH_OR_SCALE, is Next free is 15. Please update if changes.

	// ====
	static const int	zATTRIB_INT		= 0;
	static const int	zATTRIB_FLOAT	= 1;
	static const int	zATTRIB_STRING	= 2;
};

/*!
* \class CKLBAbstractAsset
* \brief Abstract Asset Class
* 
* Generic basic asset, owns the reference counting mecanism.
* Root class for all asset definition.
*/
class CKLBAbstractAsset : public CKLBObject {
	friend class CKLBAssetManager;
	friend class CKLBDebuggerContext;
public:
	CKLBAbstractAsset();
	~CKLBAbstractAsset();

	virtual	ASSET_TYPE	getAssetType() = 0;

	/* NO DICO
	virtual bool	include	(const char* name);*/
	virtual void unloadRessource() { } /* Do nothing by default */

	virtual void onRegisterSubAsset		()	{ /* Do nothing */ }
	virtual void onUnregisterSubAsset	()	{ /* Do nothing */ }

	void			incrementRefCount		();
	bool			decrementRefCount		();

	inline
	u16				getRefCount				()  { return m_refCount; }

	inline	
	u16				getAssetID				()	{ return m_assetID; }
	
	bool			setNameDirect			(const char* name);

	inline
	const char*		getName					()	{ return m_pName; }
protected:
	const
	char*				m_pName;		/* Used by debugger    */
	const
	char*				m_pNameBuff;
	const
	char*				m_fileSource;
	u16					m_assetID;		/* Runtime decided ID */
	u16					m_refCount;
	bool				m_marked;
protected:
	char*	allocateName		(void* ptr, u32 size);
};

class CKLBNode;

/*!
* \class CKLBAsset
* \brief Asset Class
* 
* A CKLBAsset can create a part of the scene graph when instancing.
*/
class CKLBAsset : public CKLBAbstractAsset {
public:
	virtual CKLBNode*	createSubTree(u32 /*priorityBase*/ = 0)	= 0;
};

/*!
* \class CKLBUIAsset
* \brief UIAsset Class
* 
* Generates an instance of UI Form from asset definition.
*/
class CKLBUIAsset : public CKLBAsset {
public:
	virtual	ASSET_TYPE	getAssetType()		{ return ASSET_UIFORM; }
	virtual CKLBNode*	createSubTree(u32 priorityBase = 0);
};

/*!
* \class CKLBSplineAnimationAsset
* \brief Spline Animation Asset Class
* 
* Generates an instance of a node modified by an animation spline.
*/
class CKLBSplineAnimationAsset : public CKLBAsset {
public:
	virtual	ASSET_TYPE	getAssetType()		{ return ASSET_ANIMATIONSPLINE; }
	virtual u32			getClassID	()		{ return CLS_ASSETANIMSPLINE;   }
	virtual CKLBNode*	createSubTree(u32 /*priorityBase*/ = 0)		{ return NULL; }
};

/*!
* \class CKLBVisualRule
* \brief Visual Rule Class
* 
* Visual Rules are assets part of game units.
* Visual Rule definition loaded by ressource manager.
* Property Change	->		Visual Change
* State Change		->		Visual Change
*/
class CKLBVisualRule : public CKLBAbstractAsset {
public:
	virtual	ASSET_TYPE	getAssetType()		{ return ASSET_VISUALRULES; }
	u16				m_solvedPropertIndex;
	CKLBVisualRule*	m_pNextInTemplate;
};

/*!
* \class CKLBActionRule
* \brief Action Rule Class
* 
* Action Rules are assets part of game units.
*/
class CKLBActionRule : public CKLBAbstractAsset {
public:
	virtual	ASSET_TYPE	getAssetType()		{ return ASSET_PROPERTYRULES; }
	CKLBActionRule*	m_pNextInTemplate;
};

/*!
* \class CKLBActionHandler
* \brief Action Handler Class
* 
* Action Handler are function definition of event handler.
* - Used by game unit.
* - Used by UI components as event handler.
*/
class CKLBActionHandler : public CKLBAbstractAsset {
public:
	virtual	ASSET_TYPE	getAssetType()		{ return ASSET_ACTIONHANDLER; }
	u32					m_actionType;
	CKLBActionHandler*	m_pNextInTemplate;
	virtual		bool	handler(CKLBAction* pAction) = 0;
};

/*!
* \class IKLBAssetPlugin
* \brief Asset Plugin Class
* 
* Base Interface for asset loaders.
* All asset loaders implement this interface to handle new_ asset format.
*/
class IKLBAssetPlugin {
	friend class CKLBAssetManager;
public:
	virtual	u8					charHeader()								= 0;
	virtual u32					getChunkID()								= 0;
	virtual const char*			fileExtension()								= 0;
			void				setReloadingAsset(CKLBAbstractAsset* pAsset) {
				m_pReloadAsset = pAsset;
			}
	virtual void				setCurrentFileName(const char* currentFileName) { } /* Do nothing by default */
	virtual CKLBAbstractAsset*	loadAsset(u8* stream, u32 streamSize)		= 0;
	virtual CKLBAbstractAsset*	loadByFileName(const char* /*fileName*/)	{ /* Do nothing */ return NULL; }
protected:
	IKLBAssetPlugin();
	virtual ~IKLBAssetPlugin();
	CKLBAbstractAsset*	m_pReloadAsset;
private:
	IKLBAssetPlugin*	m_pNext;
};

class Dictionnary;
class CKLBTextureAsset;

/*!
* \class CKLBAssetManager
* \brief Asset Manager Class
* 
* Supports all assets instance life cycle, and asset loader plugin.
*/
class CKLBAssetManager {
public:
	//
	// Async Loading related stuff...
	//
	struct SAsset {
		const char*			name;
		CKLBAbstractAsset*	asset;
		bool				loadingStarted;
		bool				loadingComplete;
		bool				checked;
		bool				added;

		// Information to fill.
		volatile bool		processByMainThread;
		CKLBTextureAsset*	pTexAsset;
		GLenum				pixelFormat;
		CKLBOGLWrapper::TEX_CHANNEL	
							channel;
		u32					opt;
		u32					textureSize;
	};
private:
	volatile	bool	m_ThreadWait;
	volatile	bool	m_AsyncMode;
	SAsset*	m_currAsset;
public:
	bool isAsyncLoading			();
	void setAsyncLoading		(bool mode);
	void setCurrentAsyncAsset	(CKLBAssetManager::SAsset* asset);
	SAsset* getCurrentAsyncAsset();
	void setMainThreadTexture	(CKLBTextureAsset* pTexAsset, GLenum pixelFormat, CKLBOGLWrapper::TEX_CHANNEL channel, u32 opt, u32 textureSize);

	inline
	static CKLBAssetManager& getInstance() {
		static CKLBAssetManager instance;
		return instance;
	}
	static void release() {	getInstance()._release();	}

	void	dump				();

	//
	// Asset definition file.
	//	- Texture
	//	- 
	//
	void		registerAssetPlugIn	(IKLBAssetPlugin* plugin);
	void		registerAsset		(CKLBAbstractAsset* pAsset);

	inline IKLBAssetPlugin* 
				getPlugin			(u8 charCode) { return m_arrayByCharCode[charCode]; }

	void		freeAsset			(u16 assetID);

	inline
	CKLBAbstractAsset*		
				getAsset			(u16 assetID) {
					klb_assert((assetID < m_maxAssetEntry), "invalid asset ID");
					klb_assert(this->m_assetRecord[assetID].m_isFree == false, "already free");
					return this->m_assetRecord[assetID].m_pAsset;
				}

	u16			getAssetIDFromName	(const char* name, char plugin, u32 retryCounter = 0);
	const char*	getAssetNameFromID	(u16 assetID);
	
	// TOO Slow, and not used for now.
	// u16			getAssetCount		();
	// u16			getAssetIDFromIndex	(u16 index);
	//
	// Asset replacement system
	//
	void		assetReplaceMarking			(u16 assetID);
	bool		assetReplaceNameMatch		(CKLBAbstractAsset* oldAsset, CKLBAbstractAsset* newAsset);
	bool		isReplaceMarked				(u16 assetID);
	void		rollBackMarking				(u16 assetID);
	void		assetReplaceFinishDeletion	(u16 assetID);

	// TODO public for the time beeing (See CKLBLuaLibDATA)
	bool		loadAssetStream				(IReadStream* pStream, CKLBAbstractAsset** ppAsset, IKLBAssetPlugin* plugIn = NULL, bool useAsync = false);
private:
	void		checkAsync					(bool asyncMode);
public:
	void		unloadAsset					();
	void		restoreAsset				();

	CKLBAbstractAsset* 
				loadAssetByFileName	(const char* fileName, IKLBAssetPlugin* plugin = NULL, bool noStream = false, bool useAsync = false);
	void		addSearchSubEntry	(CKLBAbstractAsset* pAsset, const char* name);
	void		removeSearchEntry	(const char* name);

	/**
		This function does the real loading AND allocation of memory block in asset manager
		For this reason, it should not be accessible to anybody but only from public "loadAsset" function
		in this class.
	 */
	bool		loadAsset			(u8* stream, u32 streamSize, CKLBAbstractAsset** ppAsset, IKLBAssetPlugin* plugIn = NULL, bool useAsync = false);

	bool		init				(u32 maxAssetEntry, u32 dicoNodeMax);	// 2012.12.11  Reboot時に明示皁E��呼ぶ為に外へ出しました
private:

	// OPTIMIZE RP : can optimize with this union between : pAsset vs prev/next
	struct SAssetEntry {
		CKLBAbstractAsset*	m_pAsset;
		bool				m_isFree;

		u16					m_prev;
		u16					m_next;
	};

	void		addSearchEntry		(CKLBAbstractAsset* pAsset);
	u16			searchEntry			(const char* name);
	
	IKLBAssetPlugin*	m_pAssetDecoders;
	IKLBAssetPlugin*	m_arrayByCharCode[256];
	SAssetEntry*		m_assetRecord;
	u32					m_maxAssetEntry;
	u16					m_freeList;
	bool				m_bIsInit;
	bool				m_unloaded;
	Dictionnary*		m_dictionnary;
	const char*			m_currentLoadingFile;

	CKLBAssetManager		(CKLBAssetManager const&);		// Dont implement.
	void operator=			(CKLBAssetManager const&);		// Dont implement.

	u16		allocateAssetSlot	(CKLBAbstractAsset* pAsset);
	CKLBAbstractAsset* freeAssetSlot		(u16 index);


	CKLBAssetManager();
	~CKLBAssetManager();
	void _release();
};

#endif
