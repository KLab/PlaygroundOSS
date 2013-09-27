function setup()


	--[[------------------------------
		 バーチャルドキュメントタスクの起動
		------------------------------ ]]

	--[[ ここでは、タスクを生成した後の操作を行うため、返されるタスクのポインタを pTask_vdoc 変数に格納しています。
		スコアタスクに限らず、生成後スクリプトから操作する必要のあるタスクは、必ず生成関数が返すポインタを変数として保持する必要があります。 ]]
	
	pTask_vdoc = UI_VirtualDoc(	nil,				-- 親UIタスクのポインタ。親を指定する必要がない場合は nil を指定します。
								70000,				-- 表示プライオリティ値
								100, 400,			-- 表示位置
								200, 1000,			-- ドキュメント面積。この面積のうち、一部だけが切り取られて表示されるイメージです。
								200, 100,			-- 表示面積。実際に画面上で占有される面積です。
								1000,				-- 取り扱う描画コマンド上限値。ここで指定された描画コマンド数を上限として、表示アイテムを登録できます。
								false,				-- 縦スクロールの場合は true を指定します。ここでは横スクロールなので false です。
								"callbackVDOC"		-- ポインティングデバイスコールバックを指定できます。不要な場合は省略可能です。
								)

	--[[ 表示文字のフォントとサイズを指定します。ただし、現時点ではサイズのみが意味を持ち、フォント名はダミーです。]]
	sysCommand(pTask_vdoc, UI_VDOC_FONT, 0, "Georgia", 16)
	
	--[[ ドキュメントを指定のRGBA値でクリアします。]]
	sysCommand(pTask_vdoc, UI_VDOC_CLEAR, 0x00, 0x000000)

	--[[
		描画コマンドをLuaの配列にまとめ、一括して登録します。
		一つの描画コマンドは

		{ <コマンド値>, <パラメータ>[, ... ] }

		の配列形式で記述され、この配列を配列としてまとめたものが、
		「描画コマンド配列」となります。	
		]]
	vDocDraw = {
		{ VD_DRAW_IMAG, 180, 80, "asset://inline.png.imag", 0xff },
		{ VD_DRAW_IMAG, 170, 70, "asset://inline2.png.imag", 0x80 },

		{ VD_DRAW_LINE,   0,  0, 200,  50, 0xff, 0x00ff00 },
		{ VD_DRAW_LINE, 200, 75,   0, 125, 0xff, 0x00ffff },

		{ VD_DRAW_TEXT, 20, 20, "日本語Hello A", 0xff, 0xff0000, 0 },
		{ VD_DRAW_TEXT, 120, 40, "Hello B", 0xff, 0x00ff00, 0 },
		{ VD_DRAW_TEXT, 220, 60, "Hello C", 0xff, 0x0000ff, 0 },
		{ VD_DRAW_TEXT, 320, 80, "Hello D", 0x80, 0xff0000, 0 },
		{ VD_DRAW_TEXT, 420, 100, "Hello E", 0x80, 0x00ff00, 0 },
		{ VD_DRAW_TEXT, 520, 120, "Hello F", 0x80, 0x0000ff, 0 },

		{ VD_FILL_RECT, 625, 25, 50, 50, 0xff, 0xff0000, true },
		{ VD_FILL_RECT, 650, 50, 50, 50, 0x40, 0x00ff00, true },
		{ VD_FILL_RECT, 652, 52, 50, 50, 0x40, 0x00ff00, true },
		{ VD_FILL_RECT, 654, 54, 50, 50, 0x40, 0x00ff00, true },
		{ VD_FILL_RECT, 656, 56, 50, 50, 0x40, 0x00ff00, true },
		{ VD_FILL_RECT, 650, 50, 50, 50, 0x40, 0x00ff00, true },
		{ VD_FILL_RECT, 600,  0,  0, 50, 0x40, 0x00ff00, true },
	}
	
	--[[
		上で作成した描画コマンド配列を、UI_VDOC_DRAW コマンドのパラメータとしてタスクに与えることで、
		描画コマンドがタスクに登録され、以後表示域に表示されるようになります。
		]]
	sysCommand(pTask_vdoc, UI_VDOC_DRAW, vDocDraw)
	
	--[[ VDoc タスクの表示域に表示されるドキュメント中の位置を指定します。初期状態で 0,0の位置を表示域の左上に合わせます。 ]]
	-- sysCommand(pTask_vdoc, UI_VDOC_VIEWPOS, 0, 0)
	
	-- ステージを去るときに破棄できるよう、プログレスバーをステージタスクとして登録しておく。
	TASK_StageOnly(pTask_vdoc)


	-- 表示位置や独立タッチパッド操作ステータスを保持する変数
	vd_pos = { x = 0, y = 0 }
	tp_base = { x = 0, y = 0 }
	tp_mov = { x = 0, y = 0 }
end

--[[
	そのスクリプトが有効な間、システムは毎フレーム1回、必ず　execute(deltaT) を呼び出します。
	引数の deltaT は、直前のフレーム開始から、今回のフレーム開始までに要した時間をミリ秒[ms]で表したものです。
	戻り値は必要ありません。
]]
function execute(deltaT)

	-- このスクリプトでは、スクリプトによる毎フレーム処理を行っていません。

end


--[[
	他のスクリプトをロードし、このスクリプトを去る直前にシステムから呼ばれます。
	ここでは、スクリプト内で生成し、ステージタスクとして登録された全てのタスクを破棄しています。 
	引数、戻り値はいずれもありません。
]]
function leave()
	pTask_cell = TASK_kill(pTask_cell)	-- 明示的な殺し方
	TASK_StageClear()
end


--[[
	setup() の中で、タスク起動時に仕掛けたコールバック関数。
	基本的には、独立してポインティングデバイス入力を取得します。
	全体の操作とは別の関数として、独立させた記述ができます。

	操作対象となるタスクインスタンスが第一引数として与えられ、
	第二引数にはそのフレームで処理できるポインティングデバイス操作キュー配列が与えられます。
	]]
function callbackVDOC(pTask, ttype, x, y, mv_x, mv_y)
	syslog(string.format("%d %d %d %d %d", ttype, x, y, mv_x, mv_y))
	if ttype == 0 then
		tp_base.x = x
		tp_base.y = y
		tp_mov.x = 0
		tp_mov.y = 0
	elseif ttype == 1 then
		tp_mov.x = mv_x
		tp_mov.y = mv_y
		sysCommand(pTask, UI_VDOC_VIEWPOS, -mv_x, -mv_y)
	elseif ttype == 2 then
		tp_mov.x = mv_x
		tp_mov.y = mv_y
		vd_pos.x = x - mv_x
		vd_pos.y = y - mv_y
		sysCommand(pTask, UI_VDOC_VIEWPOS, vd_pos.x, vd_pos.y)
	end
end
