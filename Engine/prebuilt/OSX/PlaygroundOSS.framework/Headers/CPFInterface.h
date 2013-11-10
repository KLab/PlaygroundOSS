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
/*!
  \brief ポーティングレイヤインタフェース CPFInterface と、使用されるインタフェースクラス IClientRequest / iPlatformRequest
  \file  CPFInterface.h

  ゲームの起動から実行、ゲーム側からのプラットフォーム機能利用までを含めた、ポーティングレイヤインタフェース。
  ゲームの実行シーケンスは、

  -# CPFInterface::setPlatformRequest() / IPlatformRequest実装をCPFInterfaceに登録
  -# GameSetup() / ゲーム側スタートアップ関数呼び出し
  -# GameSetup()内: CPFInterface::setClientRequest() / IClientRequest実装をCPFInterfaceに登録
  .
  -# CPFInterface::client().setScreenInfo() / 画面サイズをゲームに通知
  -# CPFInterface::client().setFilePath() / データアクセスパスをゲームに通知
  -# CPFInterface::client().initGame() / ゲーム初期化処理の呼び出し
  .
  となり、プラットフォーム側の実装はこの呼び出し順が保証されなければならない。
  また、ゲーム側もこの順で実行されることを前提として実装される必要がある。

  以上の起動シーケンスが終了した後, CPFInterFace::client().frameFlip() が毎フレームが呼び出される。
  */
#ifndef CPFInterface_h
#define CPFInterface_h

#include "BaseType.h"
#include "FileSystem.h"
#include "OSWidget.h"
#include "ITmpFile.h"


typedef struct {
	float   width;
	float   height;
	float   ascent;
	float   descent;
	float   top;
	float   bottom;
} STextInfo;


//! ゲーム側設定関数
/*
   \return ゲーム側設定の成否

   C++関数。ゲームタイトル側で実装されるべき起動初期化関数。
   ポーティング層は、CPFInterface のメソッドを呼び出すのに先駆け、必ずこの関数を呼ぶこと。

   ゲーム(マルチプラットフォーム側)では、実装したIClientRequest派生クラスをこの関数の中で CPFInterface に登録する。
   */
bool GameSetup(void);

//! ゲーム側インタフェースクラス
/*!
  プラットフォーム側から呼び出される処理をゲーム側で実装するためのインタフェース。
  ゲーム(マルチプラットフォーム側)で内容を実装。
  プラットフォーム側は、

  -# setScreenInfo()
  -# setFilePath()
  -# initGame()

  の順で呼び出してゲームの初期化を行い、毎フレーム frameFlip()を呼び出してゲームの実行を行うように実装される。
  */
class IClientRequest
{
public:
	static const int	ENGINE_USE_DEFAULTDB	= 0x1;
	static const int	ENGINE_USE_DEFAULTFONT	= 0x2;

	enum INPUT_TYPE {
		I_CLICK,    //!< マウスのクリック、タッチパネルのタップ動作
		I_DRAG,     //!< ドラッグ動作
		I_RELEASE,  //!< リリース動作(離す)
		I_CANCEL	//!< Cancel event
	};

	enum EVENT_TYPE {
		E_PAUSE,		// プロセスがポーズ状態になった
		E_RESUME,		// プロセスがレジュームされた
		E_TEXTCHANGE,   // TextBox の文字列が変更された
		E_URLJUMP,      // Webのコマンドリンクが指定された

		E_DIDSTARTLOADWEB,  // Webのロードが開始された
		E_DIDLOADENDWEB,	// Webのロードが終了した
		E_FAILEDLOADWEB,    // Webのロードが失敗した

		E_STORE_BAD_ITEMID,         // アイテムIDが無効
		E_STORE_PURCHASHING,        // 購入処理中
		E_STORE_PURCHASHED,         // 購入処理終了
		E_STORE_FAILED,             // 購入処理失敗

		E_STORE_RESTORE,            // リストア終了
		E_STORE_RESTORE_FAILED,     // リストア失敗
		E_STORE_RESTORE_COMPLETED,  // 全リストア終了

		E_STORE_GET_PRODUCTS, // ProductListの取得.

		// サウンドステータス
		E_SOUND_STATE_PLAY,             // サウンド再生中
		E_SOUND_STATE_STOP,             // サウンド停止中
		E_SOUND_STATE_PAUSE,            // サウンド一時停止中
		E_SOUND_STATE_INVALID_HANDLE,   // サウンドハンドル無効

		// サウンドのミュージックとの並行処理タイプlua定数
		E_SOUND_MULTIPROCESS_MUSIC_CUT,     // ゲームサウンドが再生される際に、iPodミュージックを停止
		E_SOUND_MULTIPROCESS_SOUND_CUT,     // iPodミュージックが再生されている際に、ゲーム中のサウンドを全カット
		E_SOUND_MULTIPROCESS_SOUND_BGM_CUT, // iPodミュージックが再生されている際に、ゲーム中のBGMサウンドを全カット
	};

	static const u32 KEY_BACK = 0x00000001;
	static const u32 KEY_MENU = 0x00000002;

	static const char KEYEVENT_PRESS = 0x01;
	static const char KEYEVENT_RELEASE = 0x02;
	static const char KEYEVENT_CLICK = 0x03;
	IClientRequest();
	virtual ~IClientRequest();

	
	//! ゲーム初期化処理
	/*!
		Send parameters from OS launch application to engine.
		We keep the design generic as option and parameters could vary based
		on version of the engine.
	  */
	virtual void setInitParam(u32 param, void* complexSetup) = 0;

	//! ゲーム初期化処理
	/*!
	  ゲームの初期化処理を記述。
	  描画やスクリプトエンジンのようなシステムタスクの起動や、各種初期値の指定など、ゲームの初期化を行う。
	  */
	virtual bool initGame() = 0;

	//! ゲーム終了処理
	/*!
	  ゲーム起動中に確保されたリソースをすべて破棄する。
	  アプリケーション終了のタイミングでプラットフォーム側から呼び出される。
	  */
	virtual void finishGame() = 0;

	//! 画面情報通知
	/*!
	  \param orientationFlip   横(False)・立て(True)画面
	  \param width             水平方向の解像度
	  \param height            垂直方向の解像度

	  プラットフォーム側から、使用可能な画面解像度についての情報が通知される際に呼び出される。
	  通知された情報はシステム側で保持する必要がある。
	  */
	virtual bool setScreenInfo(bool orientationFlip, int width, int height) = 0;

	//! データアクセスパス
	/*!
	  \param pStr  パス文字列

	  ゲームが利用するデータのアクセスに必要なパス文字列が渡される。
	  プラットフォームによって該当する文字列データが無い場合、動作に影響を与えない文字列が渡される。
	  */
	virtual bool setFilePath(const char * pStr) = 0;

	//! フレーム更新
	/*!
	  \param　dTime  直前のフレームからの経過時間(単位 [ms])

	  毎フレームの更新タイミングで呼び出される。
	  この中でフレーム処理(CKLBTaskMgr.execute()等)を呼び出すことでゲームが動作する。
	  */
	virtual bool frameFlip(u32 dTime) = 0;

	/**
	  ゲームのフレームレートを決まる。
	  一フレーム当たりのミニマムの実行時間を設定する。
	  Defaultは16ms (1000 / 16 = 62fps)
	  */
	virtual s32  getFrameTime() = 0;
	virtual void setFrameTime(s32 time) = 0;

	//! ポインティングデバイス入力
	/*!
	  \param  id     入力されたポイントのID
	  \param  type   入力のタイプ
	  \param  x      入力があった座標
	  \param  y      入力があった座標

	  マウスやタッチパネルなど、ポインティングデバイスによる入力があった際に、プラットフォームレイヤから呼び出される。
	  これらの入力はフレーム駆動と非同期に行われるため、ゲーム側はこれを適切に処理しなければならない。
	  */
	virtual void inputPoint(int id, INPUT_TYPE type, int x, int y) = 0;

	//! input by device buttons
	/*!
	  \param keyId		device key ID
	  \param eventType	input event type
	 */
	virtual void inputDeviceKey(int keyId, char eventType) = 0;

	/*!
	  OSにより生成されたコントロールからのイベント等が通知される。TextBoxの文字列変更や、特殊URLジャンプなど。
	  */
	virtual void controlEvent(EVENT_TYPE type, IWidget * pWidget,
			size_t datasize1, void * pData1, size_t datasize2, void * pData2) = 0;

	typedef enum {
		LEFT_TOP,		// 原点は左上(反時計廻りに0°)
		LEFT_BOTTOM,	// 原点は左下(反時計廻りに90°)
		RIGHT_BOTTOM,	// 原点は右下(反時計廻りに180°)
		RIGHT_TOP		// 原点は右上(反時計廻りに270°)
	} ORIGIN;

	typedef enum {
		PORTRAIT,		// 縦長の画面
		LANDSCAPE		// 横長の画面
	} SCRMODE;

	//! 画面ローテーション通知
	/*!
	  \param origin	新たな原点
	  \param mode		新たな画面の縦横方向

	  \return その画面ローテーションを許可する場合はtrue, 禁止の場合はfalse

	  プラットフォームレイヤから、端末の回転を通知し、回転動作の可否を問い合わせるために呼び出されます。
	  回転動作を許可する際は true を、禁止する場合は false を返します。

	  基本的には新たな画面比率が縦長か横長かだけを通知します。
	  具体的な画面サイズは、許可されて回転動作が完了した後、changeScreenInfo()で通知されます。
	  */
	virtual bool reportScreenRotation(ORIGIN origin, SCRMODE mode) = 0;


	//! 画面比率変更通知
	/*!
	  \param origin	新たな原点の位置
	  \param width	origin が 0 のときの画面幅
	  \param height	origin が 0 のときの画面高
	  回転動作の終了後に確定した、新たな画面の向きと、向きが 0 のときの幅/高さを通知します。

	  もともと回転に対応しており、GL側が回転後の上下を把握して設定を変更する環境の場合は、
	  幅、高さだけが更新されて通知されます。
	  */
	virtual void changeScreenInfo(ORIGIN origin, int width, int height) = 0;

	//! ゲームリブート
	/*!
	  ゲームを最初から実行しなおします。
	  */
	virtual void reboot			() = 0;

	virtual bool executeCommand	(const char* command) = 0;

	virtual void resetViewport	() = 0;

	virtual int  getPhysicalScreenWidth	() = 0;
	virtual int  getPhysicalScreenHeight() = 0;
	virtual void pauseGame		(bool pause) = 0;

	virtual FILE* getShellOutput() = 0;
	virtual void  setShellOutput(FILE* file) = 0;
};

//! プラットフォーム側インタフェースクラス
/*!
  ゲームから呼び出すことで使用されるプラットフォーム側の機能を、
  プラットフォーム側で実装するためのインタフェースクラス。
  */
class IPlatformRequest
{
public:
	IPlatformRequest();
	virtual ~IPlatformRequest();

	virtual bool useEncryption() = 0;

    // ゲーム側からプラットフォーム機能を呼び出す必要があるインタフェースは、
    // こちらにそのインタフェースメソッドを実装する。呼び出しのタイミングは、ゲーム側の実装に依存する。

	//! 各プラットフォーム側デバッグ出力など
	/*!
	  \param  format   printf形式のフォーマット文字列

	  指定された引数を printf 形式として、それぞれのプラットフォーム依存のデバッグ出力として出力する。
	  ゲーム側で実装された klb_assert マクロなどは、最終的にこのメソッドを使って出力される。
	  */
	virtual void detailedLogging(const char * basefile, const char * functionName, int lineNo, const char * format, ...) = 0;
	virtual void logging(const char * format, ...) = 0;
    
    // バンドルバージョン取得
    virtual const char* getBundleVersion() = 0;

	//! ナノ秒時刻取得
	/*!
	  ナノ秒単位の時刻を取得します。
	  取得される時刻の EPOCH は環境によって異なりますが、返される値の差分で経過時間を計測することができます。
	  */
	virtual  s64 nanotime() = 0;

	//! 読み込みストリーム要求
	/*!
	  \param fileName    要求する読み込みストリームの仮想パス
	  \return アクセス対象となるストリームインスタンスのポインタ。ストリームのオープンに失敗した場合は 0

	  ファイルやネットワーク、Webなど、データ読み込み対象となるストリームを開きます。
	  プラットフォーム間の差異を吸収するため、全てのプラットフォームにおいて共通の仮想パス表記が用いられます。

	  <scheme>:<location>

	  <scheme>は、ストリームの種類を表します。

	  - file
	  - ファイルを対象とします。<location>はファイルセグメントと、各セグメント内でのパスとなります。

	  例) file://external/savedata.dat
	  　file://install/MAP_0001.dat
	  　file://asset/assetdata.dat

	  scheme が file:// の場合、一段目はファイルセグメントになります。install は読み出しのみが許可される
	  システムデータ、external は読み書き可能なファイルです。asset が指定された場合、対象のファイルを
	  external から探し、見つからなければ install を探しにいきます。install ファイルに問題が見つかった場合など、
	  修正パッチの配布に利用されることが想定されます。
	  .
	  - sock
	  - ソケットを対象とします。<location>は対象ホストのIPアドレスまたはFQDNとポートになります。
	  例) sock://192.168.0.1:5432
	  　sock://www.apple.com:80
	  .
	  - http/https
	  - HTTPまたはHTTPSによるリソースを対象とします。<location>はURIの scheme を除いたものとなります。
	  つまり、通常のURIを記述すれば、そのまま対象のリソースをアクセスできます。

	  例) http://www.google.co.jp/
	  .
	  */
	virtual IReadStream* openReadStream(const char* fileName, bool decrypt) = 0;


	virtual ITmpFile *	openTmpFile				(const char * filePath) = 0;
	virtual void		removeTmpFile			(const char * filePath) = 0;
	virtual bool		removeFileOrFolder		(const char * filePath) = 0;
    virtual void		excludePathFromBackup	(const char * path)		= 0;
	virtual u32			getFreeSpaceExternalKB	() = 0;
	virtual u32			getPhysicalMemKB		() = 0;

	virtual void*		ifopen	(const char* name, const char* mode) = 0;
	virtual void		ifclose	(void* file) = 0;
	virtual int			ifseek	(void* file, long int offset, int origin) = 0;
	virtual u32			ifread	(void* ptr, u32 size, u32 count, void* file ) = 0;
	virtual u32			ifwrite	(const void * ptr, u32 size, u32 count, void* file) = 0;
	virtual int			ifflush	(void* file) = 0;
	virtual long int	iftell	(void* file) = 0;
	virtual bool		icreateEmptyFile(const char* name) = 0;

    //! オーディオデータのロード
    /*!
     \param url     ロードするオーディオデータの所在(suffix除く)
     \return        アクセス用ハンドル(void 型ポインタ)
     
     指定されたオーディオデータをオープンし再生の準備をした上、アクセス用のポインタをハンドルとして取得します。
     オーディオのファイル形式はプラットフォームに依存するため、urlにはsuffix(もしくは拡張子)無しのパスを指定します。
     また、同じ理由でゲームエンジン側からは直接オーディオデータそのものを参照することはできません

     オーディオデータはプラットフォーム側が管理し、その管理領域にアクセスするためのポインタのみが返されます。
     ポインタの先で示される領域の実装についてはプラットフォーム側に依存し、ゲーム側でその実装に依存するコードを書くことは推奨されません。
     */
    virtual void*   loadAudio(const char* url, bool is_se = false) = 0;
    
    //! オーディオデータのオンメモリ化
    /*!
     \param handle  loadAudio() で取得されたオーディオデータ管理領域
     \return オンメモリ化が正常終了した場合は true, 失敗した場合は false
     
     指定されたオーディオデータをメモリ上に展開し、即時再生できるようにします。
     ゲーム中のSEなどは短い上に頻繁に再生されるデータですが、これらをストレージから読みながら再生すると
     再生開始まで時間がかかることがあります。こうしたSEデータをあらかじめメモリ上に展開し、
     いつでも即時再生できるよう準備するために使用されます。
     */
    virtual bool    preLoad(void* handle) = 0;
    
    
    //! BGMオーディオデータのバッファサイズ指定
    /*!
     \param handle  loadAudio() で取得されたオーディオデータ管理領域
     \param level   バッファサイズ指定。0(小) 〜 2(大) で指定。
     \return オンメモリ化が正常終了した場合は true, 失敗した場合は false
 
     指定されたオーディオデータをBGMとして再生する際の、再生バッファサイズを大中小の3段階で選びます。
     指定されたサイズが具体的にどのように用いられるかはプラットフォームによって異なります。
     これを指定しない場合のデフォルトバッファサイズは 1(中)と同等でなければなりません。
     */
    virtual bool    setBufSize(void * handle, int level) = 0;
    
    //! オーディオデータの再生
    /*!
     \param handle  loadAudio()で取得されたオーディオデータ管理領域

     handleで指定されたオーディオデータの再生を開始します。
     */
    virtual void    playAudio(void* handle, s32 _msec=0, float _tgtVol=1.0f, float _startVol=1.0f) = 0;
    
    //! 再生中オーディオ再生の停止
    /*!
     \param handle  loadAudio()で取得されたオーディオデータ管理領域
     
     handleで指定されたオーディオデータが現在再生中の場合、そのデータの再生を停止します。
     再生中でなければ何もしません。
     */
    virtual void    stopAudio(void* handle, s32 _msec=0, float _tgtVol=0.0f) = 0;

    
    //! オーディオ全体のボリューム設定
    /*!
     \param volume ボリューム値。0.0f〜1.0fの間で指定。
     \param SEmode falseでBGM全体のボリューム設定。trueでSE全体のボリューム設定。
     
     BGMあるいはSE全体のレベルでボリュームを設定する。
     実際の再生ボリュームは、このAPIで設定したボリューム値に、各オーディオデータ個別のボリューム値を掛けた値となる。
     
     SEmode が false の場合はBGMに対するボリューム設定となり、
     個別のオーディオデータのうちpreLoad()でオンメモリ化されていないもののみが影響を受けます。
     
     SEmode が true の場合、SEに対するボリューム設定となり、
     preLoad() でオンメモリ化されたオーディオデータのみが影響を受けます。
     */
    virtual void    setMasterVolume(float volume, bool SEmode) = 0;
    
    
    //! 各オーディオハンドル単位のボリューム設定
    /*!
     */
    virtual void    setAudioVolume(void * handle, float volume) = 0;
    
    //! オーディオのパン設定
    virtual void    setAudioPan(void * handle, float pan) = 0;

    
    //! オーディオデータの解放
    /*!
     \param handle  loadAudio()で取得されたオーディオデータ管理領域
     handleで指定された、現在ロードされているオーディオデータを解放します。
     */
    virtual void    releaseAudio(void* handle) = 0;

    //! オーディオ一時停止
    /*
     \param handle  loadAudio()で取得されたオーディオデータ管理領域
     handleで指定された、現在ロードされているオーディオデータ再生を一時停止します。
     */
    virtual void pauseAudio(void * handle, s32 _msec=0, float _tgtVol=0.0f) = 0;
    
    //! オーディオ再生再開
    /*
     \param handle  loadAudio()で取得されたオーディオデータ管理領域
     handleで指定された、現在ロードされているオーディオデータが一時停止しているときに再生を再開します。
     */
    virtual void resumeAudio(void * handle, s32 _msec=0, float _tgtVol=1.0f) = 0;

    //! オーディオ再生時刻移動
    /*
     \param handle  loadAudio()で取得されたオーディオデータ管理領域
     handleで指定された、現在ロードされているオーディオデータが一時停止しているときに再生を再開します。
     */
    virtual void seekAudio(void * handle, s32 millisec) = 0;

    
    //! オーディオ再生時刻取得
    /*
     \param handle  loadAudio()で取得されたオーディオデータ管理領域
     handleで指定された、現在ロードされているオーディオデータにおける現在の再生位置時刻をミリ秒単位で取得します。
     ただし、環境によって取得できる時刻の分解能は異なり、原則「再生系によって検知された最新の時刻」を返します。
     */
    virtual s32  tellAudio(void * handle) = 0;
    
    
    //! オーディオ合計演奏取得
    /*
     \param handle  loadAudio()で取得されたオーディオデータ管理領域
     handleで指定された、現在ロードされているオーディオデータにおける現在の合計演奏時間をミリ秒単位で取得します。
     */
    virtual s32  totalTimeAudio(void * handle) = 0;
    
    //! オーディオステータス取得
    /*
     \param handle  loadAudio()で取得されたオーディオデータ管理領域
     handleで指定された、現在ロードされているオーディオデータの状態を取得します。
     */
    virtual s32  getState(void * handle) = 0;
    
    //! オーディオにフェードステータスを設定
    /*
     \param _handle     loadAudio()で取得されたオーディオデータ管理領域
     \param _tgtVol     目標のフェード値(0.0f~1.0f)
     \param _msec       フェードにかかる時間(ミリ秒)
     handleで指定された、現在ロードされているオーディオデータにフェード処理を追加
     */
    virtual void setFadeParam(void * _handle, float _tgtVol, u32 _msec) = 0;
    
    //! サウンドとミュージックの並行処理タイプ設定
    virtual void setAudioMultiProcessType( s32 _processType ) = 0;
    
    //! サウンドの割り込み処理をOSに依存するかどうか
    virtual void setPauseOnInterruption(bool _bPauseOnInterruption) = 0;
    
    //! OS起動からの経過時間を取得
    virtual s64 getElapsedTime( void ) = 0;
    
	virtual	bool registerFont(const char* logicalName, const char* physFile, bool default_) = 0;

    //! フォントオブジェクト取得
    virtual void * getFont(int size, const char * fontName = 0, float* pAscent = NULL) = 0;
    
    //! フォントオブジェクト破棄
    virtual void deleteFont(void * pFont) = 0;

	//! フォントオブジェクト取得
    virtual void * getFontSystem(int size, const char * fontName = 0) = 0;
    
    //! フォントオブジェクト破棄
    virtual void deleteFontSystem(void * pFont) = 0;
    
    //! フォントテクスチャ描画
    virtual bool renderText(const char* utf8String, void * pFont, u32 color,    //!< 描画する文字列とフォントの指定
                            u16 width, u16 height, u8 * pBuffer8888,            //!< 描画対象とするテクスチャバッファとそのピクセルサイズ
                            s16 stride, s16 base_x, s16 base_y, bool use4444 = false) = 0;            //!< baseline起点とするテクスチャ内の位置

    virtual bool getTextInfo(const char* utf8String, void * pFont, STextInfo* pReturnInfo) = 0;


	//! 指定アセットパスを各プラットフォーム上のフルパスに変換した文字列を返す。
	// 返された文字列は、別途 delete [] で削除の必要がある。
	virtual const char * getFullPath(const char * assetPath, bool* isReadOnly=NULL) = 0;

	//! 動作環境情報文字列を返す。
	virtual const char * getPlatform() = 0;

	//! eglGetProcAddress() 相当の処理を行う
	virtual void * getGLExtension(const char * ext) = 0;

	//! OS機能によるコントロール配置
	/*!
	  \param type		生成するコントロールのタイプ
	  \param id		コントロールに与えるID
	  \param caption	コントロールに与えるcaption値
	  \param x		コントロールを配置する位置
	  \param y		コントロールを配置する位置
	  \param width	コントロールのサイズ
	  \param height	コントロールのサイズ

	  OS機能を利用してコントロールを生成します。
	  指定された位置やサイズは最大限努力はされますが、
	  指定された位置/サイズと完全に合致しないことがあります。
	  */
	virtual IWidget * createControl(IWidget::CONTROL type, int id,
			const char * caption, int x, int y, int width, int height, ...) = 0;

	//! OS機能によるコントロールの破棄
	/*!
	  \param pControl createControl()の戻り値として返されたcontrolハンドルとなるポインタ

	  createControl()で生成したコントロールを破棄します。
	  */
	virtual void destroyControl(IWidget * pControl) = 0;


	enum APP_TYPE {
		APP_MAIL,
		APP_BROWSER,
		APP_UPDATE,		// アプリケーションのアップデートが可能なアプリ(iOSならAppStore)
	};

	//! OSアプリケーションの起動
	/*!
	  \param type 起動するアプリケーションのタイプ。実際に何が起動されるかはプラットフォーム依存だが、そのタイプを適切にこなせるものである必要がある。

	  createControl()で生成したコントロールを破棄します。
	  */
	virtual bool callApplication(APP_TYPE type, ... ) = 0;


	//! スレッド起動
	/*!

*/
	virtual void *	createThread	(s32 (*thread_func)(void * hThread, void * data), void * data) = 0;
	virtual void	exitThread		(void * hThread, s32 status)   = 0;
	virtual bool	watchThread		(void * hThread, s32 * status) = 0;
	virtual void	deleteThread	(void * hThread) = 0;
	virtual void	breakThread		(void * hThread) = 0;

	virtual int		genUserID		(char * retBuf, int maxlen) = 0;
	virtual int		genUserPW		(const char * salt, char * retBuf, int maxlen) = 0;

	virtual bool	readyDevID		() = 0;
	virtual int		getDevID		(char * retBuf, int maxlen) = 0;
	virtual bool	setSecureDataID	(const char * service_name, const char * user_id)		= 0;
	virtual bool	setSecureDataPW	(const char * service_name, const char * passwd)		= 0;
	virtual int		getSecureDataID	(const char * service_name, char * retBuf, int maxlen)  = 0;
	virtual int		getSecureDataPW	(const char * service_name, char * retBuf, int maxlen)  = 0;
	virtual bool	delSecureDataID	(const char * service_name) = 0;
	virtual bool	delSecureDataPW	(const char * service_name) = 0;

	//! ストア機能
	//! トランザクション監視開始
	virtual void initStoreTransactionObserver() = 0;
	//! トランザクション監視終了
	virtual void releaseStoreTransactionObserver() = 0;
	//! 購入要求: アイテムIDと、その数を渡す
	virtual void buyStoreItems(const char * item_id) = 0;
	//! プロダクトリスト取得要求: アイテムIDの配列とその数、及びcurrency表示にするかの判定とcallbackを渡す.
	virtual void getStoreProducts(const char* json, bool currency_mode) = 0;
	//! サーバー通信後にトランザクションを閉じて購入処理を確定させる。
	virtual void finishStoreTransaction(const char* receipt) = 0;

	virtual void*	allocMutex		() = 0;
	virtual void	freeMutex		(void* mutex) = 0;
	virtual void	mutexLock		(void* mutex) = 0;
	virtual void	mutexUnlock		(void* mutex) = 0;

	virtual void*	allocEventLock	() = 0;
	virtual void	freeEventLock	(void* lock) = 0;
	virtual void	eventSleep		(void* lock) = 0;
	virtual void	eventWakeup		(void* lock) = 0;
	
	virtual void	startAlertDialog( const char* title , const char* message ) = 0;

	virtual void	forbidSleep		(bool is_forbidden) = 0;
};

#ifdef DEBUG
# 
# define DEBUG_PRINT(...) CPFInterface::getInstance().platform().detailedLogging(__FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#else
# define DEBUG_PRINT(...) 
#endif

//!
/*!
  プラットフォーム側とゲーム側のインタフェースとなる Singleton.
  両者のやり取りは必ず CPFInterface インスタンスを介して行われる。

  初期化シーケンス:
  -# CPFInterface::setPlatformRequest() / IPlatformRequest実装をCPFInterfaceに登録
  -# GameSetup() / ゲーム側スタートアップ関数呼び出し
  -# GameSetup()内: CPFInterface::setClientRequest() / IClientRequest実装をCPFInterfaceに登録
  .
  -# CPFInterface::client().setScreenInfo() / 画面サイズをゲームに通知
  -# CPFInterface::client().setFilePath() / データアクセスパスをゲームに通知
  -# CPFInterface::client().initGame() / ゲーム初期化処理の呼び出し
  .
  また、ゲームの実行は毎フレームプラットフォーム側から CPFInterface::client.flipFrame()を呼び出すことで行われる。
  */
class CPFInterface
{
private:
	static CPFInterface * instance;
	IClientRequest * m_pClient;
	IPlatformRequest * m_pPlatform;
private:
	CPFInterface();
	virtual ~CPFInterface();
public:

	//! インスタンス取得
	/*!
	  \return Singletonインスタンスへの参照

	  Singletonインスタンスへの参照を取得する。
	  ゲーム側、プラットフォーム側いずれでも使用される。
	  */
	static CPFInterface& getInstance();

	//! ゲーム側インタフェースの登録
	/*!
	  \param pClient  クライアント側インタフェースのポインタ

	  プラットフォーム側からゲーム側をコールする際に使用されるインタフェースを登録する。
	  IClientRequest(Client側Strategy)を受け取り設定する
	  */
	void setClientRequest(IClientRequest * pClient) {
		m_pClient = pClient;
	}

	//! プラットフォーム側インタフェースの登録
	/*!
	  \param pPlatform  プラットフォーム側インタフェースのポインタ

	  ゲーム側からプラットフォーム側をコールする際に使用されるインタフェースを登録する。
	  IPlatformRequest(Platform側Strategy)を受け取り設定する
	  */
	void setPlatformRequest(IPlatformRequest * pPlatform) {
		m_pPlatform = pPlatform;
	}

	//! ゲーム側インタフェースの参照取得
	/*!
	  \return ゲーム側インタフェースへの参照

	  ゲーム側から指定されたインタフェースへの参照を取得する。
	  */
	inline IClientRequest& client() {
		return *m_pClient;
	}

	//! プラットフォーム側インタフェースの参照取得
	/*!
	  \return プラットフォーム側インタフェースへの参照

	  プラットフォーム側から指定されたインタフェースへの参照を取得する。
	  */
	inline IPlatformRequest& platform() {
		return *m_pPlatform;
	}

	//! エンディアン確認
	/*!
	  \return  ビッグエンディアンのときは true, リトルエンディアンのときは false
	  実行環境のエンディアンを調査する。
	  */
	bool isBigEndian();

	inline bool isClient	() const { return (m_pClient != 0);		}
	inline bool isPlatform	() const { return (m_pPlatform != 0);	}
};

#endif // CPFInterface_h
