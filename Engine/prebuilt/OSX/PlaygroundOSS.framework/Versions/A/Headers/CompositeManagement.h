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
#ifndef __COMPOSITE_MGT__
#define __COMPOSITE_MGT__

#include "CKLBNode.h"
#include "CKLBAsset.h"
#include "DataSet.h"

class CKLBInnerDef;
class CKLBAnimInfo;

#define	TMP_COMPOSITE_ASSET_STR_BUFFSIZE	(10000)

/*!
* \class CKLBCompositeAsset
* \brief Composite Asset Class
* 
* CKLBCompositeAsset is an asset defining a "Form". 
* A Form is basically a tree of visual tasks and components.
* It allows to create a scene formed with tasks and UI objects without having to 
* heavily rely on scripting. 
* Instead, a loader performs object creation and property setup.
*/
class CKLBCompositeAsset : public CKLBAsset {
	friend class CKLBCompositeAssetPlugin;
	friend class CKLBInnerDef;
	friend class CKLBAnimInfo;
public:
	CKLBCompositeAsset	();
	~CKLBCompositeAsset	();

	void				setGroupID(u16 groupID)	
											{	m_groupID = groupID;	}
	virtual u32			getClassID()		{ return CLS_ASSETCOMPOSITE; }
	virtual CKLBNode*	createSubTree(u32 priorityBase = 0);
	CKLBNode*			createSubTree(CKLBUITask* pParentTask, u32 priorityBase = 0); 
	virtual	ASSET_TYPE	getAssetType()		{ return ASSET_COMPOSITE; }

	void setRecord(IDataSource* source, IDataRecord record);

	void* parserCtx;

	inline s16 get_width() const { return m_width; }
	inline s16 get_height() const { return m_height; }

	enum FIELD_ENUM {
		X_FIELD,
		Y_FIELD,
		SX_FIELD,
		SY_FIELD,
		SW_FIELD,
		SH_FIELD,
		LAYOUT_INFO_FIELD,
		LW_FIELD,
		LH_FIELD,
		CLASS_FIELD,
		ON_CLICK,
		ASSET_FIELD,
		ASSET_DISABLED_FIELD,
		ASSET_FOCUS_FIELD,
		ASSET_PUSH_FIELD,
		ASSET_4,
		ASSET_5,
		ASSET_6,
		ASSET_7,
		ASSET_8,
		ASSET_9,
		SUB_FIELD,
		PRIORITY_FIELD,
		RADIO_FIELD,
		NAME_FIELD,
		TEXT_FIELD,
		ID,
		CLIPX,
		CLIPY,
		CLIPW,
		CLIPH,
		CLIPSTART,
		CLIPEND,
		FONT_SIZE_FIELD,
		FONT_NAME_FIELD,
		COLOR_FIELD,
		WIDTH_FIELD,
		HEIGHT_FIELD,
		ANIM_TYPE,		// Str
		ANIM_EASING,
		ANIM_LENGTH,
		ANIM_SHIFT,
		ANIM_FROMX,
		ANIM_TOX,
		ANIM_FROMY,
		ANIM_TOY,
		ANIM_FROMSCALE,	// Float
		ANIM_TOSCALE,	// Float
		ANIM_FROMALPHA,
		ANIM_TOALPHA,
		ANIM_FROMCOLOR,
		ANIM_TOCOLOR,
		STATES_FIELD,
		XSCALE_FIELD,
		YSCALE_FIELD,
		ROTATION_FIELD,
		ANIM_LOOP,
		ANIM_PINGPONG,
		ANIM_DATA,
		ANIM_FROMSCALE_X,	// Float
		ANIM_TOSCALE_X,		// Float
		ANIM_FROMSCALE_Y,	// Float
		ANIM_TOSCALE_Y,		// Float
		ANIM_FROM_ROTATION,
		ANIM_TO_ROTATION,
		VALUE_FIELD,
		CALLBACK_FIELD,
		ORIENTATION_FIELD,
		ALIGN_FIELD,
		ASSET_0_FIELD,
		ASSET_1_FIELD,
		PRIORITY_OFFSET_FIELD,
		START_PIX_FIELD,
		END_PIX_FIELD,
		ANIM_TIME_FIELD,
		DRAG_ALPHA_FIELD,
		CENTER_X_FIELD,
		CENTER_Y_FIELD,
		FLAG_0_FIELD,
		FLAG_1_FIELD,
		INT_0_FIELD,
		INT_1_FIELD,
		INT_2_FIELD,
		INT_3_FIELD,
		INT_4_FIELD,
		INT_5_FIELD,
		URL_FIELD,
		ALLOW_NAVIGATION_FIELD,
		PRIO_OFFSET_FIELD,
		CENTERX_FIELD,
		CENTERY_FIELD,
		BASEINVISIBLE_FIELD,
		STEPX_FIELD,
		STEPY_FIELD,
		NUMBERCOUNT_FIELD,
		FILLZERO_FIELD,
		ANIMATE_FIELD,
		SOUNDUP_FIELD,
		SOUNDDOWN_FIELD,
		ENABLE_FIELD,
		STARTANGLE_FIELD,
		ENDANGLE_FIELD,
		MINVALUE,
		MAXVALUE,
		MINSLIDERSIZE,
		SLIDERSIZE,
		SELECTCOLOR,
		MAXVERTEX,
		MAXINDEX,
		SPLINE_MASK,
		SPLINE_COUNT,
		SPLINE_ARRAY,
		SPLINE_LENGTH,
		GENERIC_FIELD,
		ISPASSWORD_FIELD,
		VARCLIP_FIELD,
		COUNTCLIP_FIELD,
		PLACEHOLDER_FIELD,
		VISIBLE_FIELD,
		MAXLENGTH,
		CHARTYPE,
		VOL_AUDIO_UP,
		VOL_AUDIO_DOWN,
	};
private:
	bool init();
	bool createSubTreeRecursive(u16 groupID, CKLBUITask* pParentTask, CKLBNode* parent, CKLBInnerDef* parentTemplate, u32 priorityOffset);

	void setupNode(CKLBInnerDef* templateDef, CKLBNode* node);
	void setupTask(CKLBInnerDef* templateDef, CKLBUITask* tsk);

	struct STRINGENTRY {
		STRINGENTRY();
		~STRINGENTRY();

		STRINGENTRY*		next;
		CKLBAsset*			assetCache;
		char*				string;
	};

	STRINGENTRY*	m_allocatedString;

	u16			m_groupID;
	//
	// Parser Stuff.
	//
	u16			m_parserField;
	char*		allocateString(const unsigned char* string, u32 strLen, bool* err);
	
	STRINGENTRY* registerString(const char* string, u32 strLen, bool* err);

private:
	// UI and composite with 32 levels are good enough.
	#define MAX_STACK_DEPTH				(32)
	float*			m_currArraySpline;
	IDataSource*	m_pSource;
	IDataRecord		m_record;
	CKLBInnerDef*	m_pCurrInnerDef;
	CKLBAnimInfo*	m_pCurrAnim;
	CKLBInnerDef*	m_pParent;
	CKLBInnerDef*	m_root;
	CKLBNode*		m_rootParent;
	CKLBInnerDef*	m_parentStack	[MAX_STACK_DEPTH];
	u32				m_basePriority;
	s16				m_width;
	s16				m_height;
	u16				m_parent;
	u8				m_recCount;
	u8				mode;
	bool			m_bTreeMode;
	bool			m_bLowRes;

	//
	// Parser Call back.
	//
	int readStartMap	(unsigned int size);
	int readNull		();
	int readBoolean		(int boolean);
	int readInt			(long long integerVal);
	int readDouble		(double doubleVal);
	int readString		(const unsigned char * stringVal, size_t stringLen, int cte_pool);
	int readMapKey		(const unsigned char * stringVal, size_t stringLen, int cte_pool);
	int readEndMap		();
	int readStartArray	(unsigned int size);
	int readEndArray	();

	static int read_start_map	(void * ctx, unsigned int size);
	static int read_null		(void * ctx);
	static int read_boolean		(void * ctx, int boolean);
	static int read_int			(void * ctx, long long integerVal);
	static int read_double		(void * ctx, double doubleVal);
	static int read_string		(void * ctx, const unsigned char * stringVal, size_t stringLen, int cte_pool);
	static int read_map_key		(void * ctx, const unsigned char * stringVal, size_t stringLen, int cte_pool);
	static int read_end_map		(void * ctx);
	static int read_start_array	(void * ctx, unsigned int size);
	static int read_end_array	(void * ctx);

private:
	//
	// Buffer for asset string name during loading.
	//

	void			resetTmpBuff	();
	const char*		addAssetPrefix	(const char* prefixLessAsset);
	const char*		formatI			(s32 i);
	const char*		formatB			(bool i);
	const char*		formatF			(float f);
	const char*		addString		(const char* source, u32 len);
	const char*		filterDB		(const char* input, bool* filtered = NULL);
	float			filterDBFloat	(CKLBCompositeAsset::STRINGENTRY* input, float original);
	s32				filterDBInt		(CKLBCompositeAsset::STRINGENTRY* input, s32 original);

	static char		tmpBuff[TMP_COMPOSITE_ASSET_STR_BUFFSIZE];
	static char*	ptrBuff;
};

class CKLBCompositeAssetPlugin : public IKLBAssetPlugin {
public:
	CKLBCompositeAssetPlugin();
	~CKLBCompositeAssetPlugin();

	virtual u32					getChunkID()				{ return CHUNK_TAG('C','O','M','P'); }
	virtual	u8					charHeader()				{ return 'P';		}
	virtual const char*			fileExtension()				{ return ".json"; 	}

	virtual CKLBAbstractAsset*	loadAsset(u8* stream, u32 streamSize);
};

//
// Class holding tree definition.
//

#define MAX_HANDLER			(2)
#define MAX_ASSETS			(10)

class CKLBAnimInfo;
class CKLBPropertyBag;

class CKLBInnerDefManager {
public:
	static bool initManager(int size);
	static void releaseManager();
};

class CKLBInnerDef {
public:
	CKLBInnerDef();
	~CKLBInnerDef();
	
	static void* operator new		(size_t size); 
	static void  operator delete	(void *p);

	CKLBAnimInfo*	findAnimation(const char* animName);

	CKLBInnerDef*	next;
	CKLBInnerDef*	sub;
	CKLBAnimInfo*	anim;
	CKLBPropertyBag*	propertyBag;

	float x;
	float y;
	float xscale;
	float yscale;
	float rotation;
	
	u32	layoutInfo;
	u32 priority;
	s32 value;
	s32	radioID;
	
	CKLBCompositeAsset::STRINGENTRY*	fontName;
	u32	color;

	CKLBCompositeAsset::STRINGENTRY*	handler	[MAX_HANDLER];
	CKLBCompositeAsset::STRINGENTRY*	assets	[MAX_ASSETS];

	CKLBCompositeAsset::STRINGENTRY*	name;
	CKLBCompositeAsset::STRINGENTRY*	text;
	CKLBCompositeAsset::STRINGENTRY*	placeholder;
	u32 priorityClipStart;
	u32 priorityClipEnd;
	u32 id;

	float*	spline;
	CKLBCompositeAsset::STRINGENTRY*	dbField[4];
	u32	variable[10];

	s16	lw;
	s16	lh;
	u16	classID;
	s16	sx;
	s16	sy;
	s16	sh;
	s16	sw;
	u16 fontSize;
	s16 clipx;
	s16 clipy;
	s16 clipw;
	s16 cliph;
	s16	width;
	s16 height;
	u16	splineMask;
	u16	splineCount;
	u16	splineLength;
	u8	splineVectorSize;
	u8	volAudioUp;
	u8	volAudioDown;

	u8	flag[4];
	bool	visible;
};

class CKLBAnimInfo {
public:
	CKLBAnimInfo();
	~CKLBAnimInfo();

	CKLBAnimInfo*	m_next;
	s32*	data;

	CKLBCompositeAsset::STRINGENTRY*	mode;

	float	fromScaleX;
	float	toScaleX;
	float	fromScaleY;
	float	toScaleY;
	float	fromRotation;
	float	toRotation;

	u16		dataSize;
	u16		currSize;

	u16		length;
	s16		timeShift;

	s16		fromX;
	s16		toX;

	s16		fromY;
	s16		toY;


	u8		fromAlpha;
	u8		toAlpha;

	u8		fromR;
	u8		toR;

	u8		fromG;
	u8		toG;

	u8		fromB;
	u8		toB;

	u8		spline;
	u8		modeID;

	u8		loop;
	u8		pingpong;
};

#endif
