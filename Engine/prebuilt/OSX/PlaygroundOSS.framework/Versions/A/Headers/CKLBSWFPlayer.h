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
// === Flash File support ===
//
//

#ifndef __SWF_PLAYER__
#define __SWF_PLAYER__

#include "CKLBNode.h"
#include "CKLBAsset.h"

// Null index, null offset
#define MAIN_MOVIE_IDX			(0xFFFE)

//
// Movie instruction type
//
#define SHOW_FRAME				(0)
#define PLACE_OBJECT			(1)
#define REMOVE_OBJECT			(2)
#define PLAY_SOUND				(3)
#define PLACE_OBJECT_CLIP		(4)

#define SKIP_SHOW				(4)

//
// Structure index
//
#define SIZE_MOVIE_INFO			(4)

#define CODE_NAMEINDEX			(0)

// Index for normal movies
// & Static Images.

// FrameCount = 0xFFFF : Image asset
// FrameCount = 0x8FFE : Shape
#define CODE_FRAMECOUNT			(1)
#define CODE_STARTINDEX			(2)
#define CODE_OFFSETX			(2)
#define CODE_ENDINDEX			(3)
#define CODE_OFFSETY			(3)

#define CODE_SHAPE_DEF_INDEX	(2)

//
// m_isDisplaying modes
//
#define STOPPED					(0)
#define PLAYING					(1)
#define STOP_TARGET				(2)

//
// Show Frame flow type
//
#define STOP_INSTRUCTION		(0)
#define GOTO_AND_PLAY			(1)
#define GOTO_AND_STOP			(2)
#define SHOW_FRAME_ONLY			(0xFFFF)

typedef unsigned int u32;
typedef unsigned short int u16;
typedef unsigned char u8;
typedef u16* u16p;

// --------------------------------------------------------------------------------
// Player & Related Classes Definition
// --------------------------------------------------------------------------------

class SWFPlayer;
class CKLBSWFMovie;
class CKLBSWFAsset;
class SWFBitmap;

/*!
* \class CKLBSWFMovie
* \brief SWF Movie Specialized Node
* 
* CKLBSWFMovie is a specialized Node for Flash Movies.
* It provides basic control methods for a Flash Movie.
*/
class CKLBSWFMovie : public CKLBNode {
	friend class CKLBSWFAsset;
public:
	CKLBSWFMovie(CKLBSWFAsset* pPlayer, CKLBNode* pParent, u16 layer);
	virtual ~CKLBSWFMovie();

	virtual
	CKLBNode*	clone				(CKLBNode* newItem, CKLBNode* parent, CKLBNode* brother, bool transferSpriteOwnership);

	inline 
	float			getVolumeSE			()	{ return m_volume; }
	void			setVolumeSE			(float volume);

	virtual
	void			setPriority			(u32 order);
	u16				findCodeFrame		(char* label, u16* pFrameNum);
	void			gotoFrame			(u16 frame);
	void			setPlay				(bool play) {
		if (play != m_playMode) {
			m_playMode = play;
			if (play) {
				m_isPlaying			= m_isPlayingBackup;
			} else {
				m_isPlayingBackup	= m_isPlaying;
				m_isPlaying = STOPPED;
			}

			CKLBNode* pNode = this->m_pChild;
			while (pNode) {
				if (pNode->getClassID() == CLS_KLBSWFMOVIE) {
					((CKLBSWFMovie*)pNode)->setPlay(play);
				}
				pNode = ((CKLBSWFMovie*)pNode)->m_pBrother; // Stupid C++ protected spec.
			}
		}
	}
	virtual u32		getClassID			()	{ return CLS_KLBSWFMOVIE; }

	inline
	CKLBSWFAsset*	getPlayer			()	{ return m_player; }

	inline
	void			setListener			(CKLBObject* listener) { MsgRegister(listener); }

	inline
	u16				getFrameRate		()	{ return m_msPerFrame; }
	void			setFrameRate		(u16 milliSecPerFrame) {
		if (milliSecPerFrame) {
			setPlay(true);
			m_msPerFrame = milliSecPerFrame;
		} else {
			setPlay(false);
		}
	}

	s8				replaceAsTemplate	(const char** pArrayString, u32 entryCount);

protected:

	CKLBSWFAsset*	m_player;
	CKLBSWFMovie*	m_flashRoot;

	float			m_volume;
	u32				m_renderOffset;
	u32				m_localTime;
	u32				m_movieStartCode;	// Movie definition index IN MOVIE DATA STREAM ( NOT INDEX OF MOVIE ITSELF IN ARRAY )
	u32				m_movieCode;
	u32				m_movieEndCode;
	u32				m_bitBuf;
	u16				m_bitPos;
	u16				m_uiFrame;
	u16				m_msPerFrame;
	u16				m_updateFrame;
	u8				m_isPlaying;
	u8				m_isPlayingBackup;
	CKLBImageAsset**	m_aBitmapLoaded;
	s32*			m_convTable;
	const char**	m_nameTable;

	bool			m_firstFrame;
	bool			m_rebuildSort;
	bool			m_isFlashRoot;
	bool			m_disableJump;
	bool			m_playMode;
	bool			m_supportCaching;

	virtual
	void			animate				(u32 deltaTimeMilli);
	void			nextFrame			(u16 frame);

	void			InitBits			();
	s32				GetSBits			(s32 n);
	u32				GetBits				(s32 n);

	CKLBImageAsset*	getImage			(u16 movieID);

private:
	void			freeTables			();
	CKLBNode*		addMovie			(u16 movieID, u16 layer);
	void			removeMovie			(CKLBNode* pNode);
	u16				findCodeFrame		(u16 frame);
	void			rebuildSort			();
	void			rebuildRecurse		(CKLBNode* pNode, u32* pIndex, CKLBRenderingManager& pRdr);
	void			setFlashRoot		();
};

struct SShape;
struct SSound;

/*!
* \class CKLBSWFAsset
* \brief Flash Asset Class
* 
* Generates an SWF instance from SWF Movie definition.
* This is an asset that stores exported Flash movies from our converter.
* It contains animation information, link to needed images or sound assets and movie structure.
* Various information about label, movie length is also stored.
*/
class CKLBSWFAsset : public CKLBAsset {
	friend class CKLBNodeSWF;
	friend class CKLBSWFMovie;
public:
	virtual u32		getClassID()		{ return CLS_ASSETFLASH; }

	virtual	ASSET_TYPE	getAssetType()	{ return ASSET_SWFMOVIE; }

	virtual CKLBNode*	createSubTree(u32 priorityBase = 0);
	
	CKLBSWFAsset();
	~CKLBSWFAsset();

	inline
	char*		getConstantString	(u16 stringIndex) {
		klb_assert(stringIndex < m_uiStringCount, "Invalid index");
		klb_assert(m_aConstants, "No constant");
		return m_aConstants[stringIndex];
	}

	inline
	void		setFrameRate		(u16 milliSecPerFrame) {
		m_msPerFrame = milliSecPerFrame;
	}

	bool		LoadData			(u8* pData);
	CKLBSWFAsset* 
				findMovieAsset		(char* name);
	void		setVolumeSE			(float volume);

	CKLBNode*	addMovieA			(char* name, u16 layer, SMatrix2D* m, CKLBNode* root, const char** templateInfo, u32 pairCount);
	CKLBNode*	addMovieB			(u16 movieID, u16 layer, SMatrix2D* m, CKLBNode* root, const char** templateInfo, u32 pairCount);

	u32			getResourceList		(u32 arraySize, const char** arrayOfString);
private:
	void cacheSceneGraph			(CKLBSWFMovie* node, u16 frame);
	bool hasCache					(CKLBSWFMovie* node, u16 frame);
	void restoreSceneGraph			(CKLBSWFMovie* node, u16 frame);

	CKLBNode*	findNode			(char* name);
	u16			findMovie			(char* name);

	CKLBSWFAsset*	m_parentSWF;

	// Animation frame rate : number of millisecond per frame.
	u16		m_msPerFrame;
	
	//-------------------------------------
	// Constant Pool.
	u16			m_uiStringCount;
	u16			m_uiTotalCharsCount;
	char**		m_aConstants;
	char*		m_aChars;

	//-------------------------------------
	// Matrix Information.
	u16			m_uiMatrixCount;

	//-------------------------------------
	// Movie ID when referencing parent.
	u16			m_refMovieID;

	//-------------------------------------
	// Shape Related
	u16			m_uiShapeCount;
	u32			m_uiIndexTotal;
	u16*		m_pIndex;
	SShape*		m_shapes;

	//-------------------------------------
	// Audio Related
	u16			m_uiSoundCount;
	SSound*		m_sounds;

	// Array of object : avoid multiple object --> Faster for scripting.
	// same as : Matrix*	m_aMatrixArray;
	float*		m_aMatrixData;
	u8*			m_aMatrixType;
	u32*		m_aMatrixDataIndex;	// Note : can optimize one indirection with float* computed once.

	//-------------------------------------
	// Stream Information
	u32*		m_aStreamInstruction;
	u32			m_aStreamSize;

	//-------------------------------------
	// Movie Information
	u16						m_uiMovieCount;
	
	struct SCacheEntry {
		SCacheEntry*	m_next;
		CKLBSWFMovie*	m_cacheNode;
		u16				m_cacheFrame;
	};

	SCacheEntry**			m_alistCacheEntries;
	u32*					m_aMovieInfo; // Array of [movie count * 8] entries.
	CKLBSWFAsset*			m_subAssets;
	CKLBImageAsset**		m_aBitmapLoaded;
	bool					m_isMaster;
};

/*!
* \class KLBFlashAssetPlugin
* \brief Flash Asset Plugin Class
* 
* KLBFlashAssetPlugin is in charge of loading Flash Assets.
*/
class KLBFlashAssetPlugin : public IKLBAssetPlugin {
public:
	KLBFlashAssetPlugin();
	~KLBFlashAssetPlugin();

	virtual u32					getChunkID()					{ return CHUNK_TAG('F','L','S','H'); }
	virtual	u8					charHeader()					{ return 'F';			}
	virtual const char*			fileExtension()					{ return ".flsh"; }

	virtual CKLBAbstractAsset*	loadAsset(u8* stream, u32 streamSize);
};


#endif
