function setup()

	local x = 100
	local y = 0
	local stepX = 24
	local stepY = 0
	local fillZERO = false
	local fANIM = false
	local texTable = {
		"asset://Score-0.png.imag",
		"asset://Score-1.png.imag",
		"asset://Score-2.png.imag",
		"asset://Score-3.png.imag",
		"asset://Score-4.png.imag",
		"asset://Score-5.png.imag",
		"asset://Score-6.png.imag",
		"asset://Score-7.png.imag",
		"asset://Score-8.png.imag",
		"asset://Score-9.png.imag"
	}
	pSCORE = UI_Score(	nil	,				-- arg[1]	親UIタスクポインタ
						7000,				-- arg[2]	表示プライオリティ
						10,					-- arg[3]	アニメーション時に使用する古い数字の相対プライオリティ
						x, y,				-- arg[4,5]	表示位置
						texTable,			-- arg[6]	数字として使用するテクスチャリストのテーブル
						stepX, stepY,		-- arg[7,8]	各桁数字の表示間隔
						2,					-- arg[9]	表示桁数(最大10桁)
						fillZERO,			-- arg[10]	上の桁を0で埋める場合はtrue, 空白にする場合はfalse
						fANIM				-- arg[11]	値変化時にアニメーションさせる場合true、させなければfalse
						)
	
	-- 表示開始時のアニメーション属性指定
	maskEnter	= bitOR(ANM_X_COORD_0, ANM_SCALE_COORD_2, ANM_A_COLOR_6)	-- フラグ値(※1)
	fEnterParam = {
		-15.0, 0.0,					-- X
		4.0, 1.0, 1.0, 1.0,			-- Scale
		0.3, 1.0					-- Alpha
	}
	sysCommand(pSCORE, UI_SCORE_ENTERANIM,	300, -150, false, 1, maskEnter, fEnterParam)

	prop = TASK_getProperty(pSCORE)
	prop.align = SCORE_ALIGN_CENTER
	TASK_setProperty(pSCORE, prop)

	-- 消去時のアニメーション属性指定
	maskExit	= bitOR(ANM_Y_COORD_1, ANM_A_COLOR_6)
	fExitParam = {
		0.0,	-30.0,
		1.0,	0.0
	}
	sysCommand(pSCORE, UI_SCORE_EXITANIM,	500, 0, false, 1, maskExit , fExitParam )

	sysCommand(pSCORE, UI_SCORE_RESET)
	--[[
		UI_SCORE_RESETは、スコアタスクの値を 0 にリセットします。
	]]

	fCount = 0
	sysCommand(pSCORE, UI_SCORE_SET, 9)
	-- sysCommand(pSCORE, UI_GENERIC_SET_COLOR, 0xff, 0xffffff)
	
	count = 0
end


function execute(deltaT)
	fCount = fCount + deltaT
	if fCount >= 1000 then
		fCount = fCount - 1000

		local score = sysCommand(pSCORE, UI_SCORE_GET)
		--[[
			UI_SCORE_GETは、現在スコアタスクが保持している値を取得します。
			値は必ず整数値となります。
		]]

		score = score + 1

		sysCommand(pSCORE, UI_SCORE_SET, score)
		--[[
			UI_SCORE_SETは、スコアタスクで与える値を指定します。
		]]

	end
	
	count = count + 1
	if count == 20 then
		syslog(string.format("TASK alpha"))
		prop = TASK_getProperty(pSCORE)
		prop.alpha = 128
		TASK_setProperty(pSCORE, prop)	
	end
	if count == 40 then
		syslog(string.format("TASK color"))
		prop = TASK_getProperty(pSCORE)
		prop.color = 0xFF00FF
		TASK_setProperty(pSCORE, prop)	
	end
	if count == 60 then
		syslog(string.format("TASK scalex"))
		prop = TASK_getProperty(pSCORE)
		prop.scaleX = 2.0
		TASK_setProperty(pSCORE, prop)	
	end
	if count == 80 then
		syslog(string.format("TASK scaley"))
		prop = TASK_getProperty(pSCORE)
		prop.scaleY = 2.0
		TASK_setProperty(pSCORE, prop)	
	end
	if count == 100 then
		syslog(string.format("TASK rot"))
		prop = TASK_getProperty(pSCORE)
		prop.rot = 25.0
		TASK_setProperty(pSCORE, prop)	
	end
	if count == 120 then
		syslog(string.format("TASK x"))
		prop = TASK_getProperty(pSCORE)
		prop.x = 200
		TASK_setProperty(pSCORE, prop)	
	end
	if count == 140 then
		syslog(string.format("TASK y"))
		prop = TASK_getProperty(pSCORE)
		prop.y = 200
		TASK_setProperty(pSCORE, prop)	
	end
	if count == 160 then
		syslog(string.format("TASK visible = false"))
		prop = TASK_getProperty(pSCORE)
		prop.visible = false
		TASK_setProperty(pSCORE, prop)	
	end
	if count == 180 then
		syslog(string.format("TASK visible = true"))
		prop = TASK_getProperty(pSCORE)
		prop.visible = true
		TASK_setProperty(pSCORE, prop)	
	end
	
	if count == 200 then
		syslog(string.format("order"))
		prop = TASK_getProperty(pSCORE)
		prop.order = 8000
		TASK_setProperty(pSCORE, prop)
	end
	if count == 300 then
		syslog(string.format("stepX"))
		prop = TASK_getProperty(pSCORE)
		prop.stepX = 100
		TASK_setProperty(pSCORE, prop)
	end
	if count == 400 then
		syslog(string.format("stepY"))
		prop = TASK_getProperty(pSCORE)
		prop.stepY = 20
		TASK_setProperty(pSCORE, prop)
	end
	if count == 450 then
		syslog(string.format("cols"))
		prop = TASK_getProperty(pSCORE)
		prop.cols = 1
		TASK_setProperty(pSCORE, prop)
	end
	if count == 500 then
		syslog(string.format("fillz"))
		prop = TASK_getProperty(pSCORE)
		prop.cols  = 2
		prop.fillz = true
		TASK_setProperty(pSCORE, prop)
	end
	if count == 550 then
		syslog(string.format("value"))
		prop = TASK_getProperty(pSCORE)
		prop.value  = 42
		TASK_setProperty(pSCORE, prop)
	end
	if count == 600 then
		syslog(string.format("align"))
		prop = TASK_getProperty(pSCORE)
		prop.align  = SCORE_ALIGN_LEFT
		TASK_setProperty(pSCORE, prop)
	end
	if count == 650 then
		syslog(string.format("countclip"))
		prop = TASK_getProperty(pSCORE)
		prop.countclip  = true
		TASK_setProperty(pSCORE, prop)
	end
	
	if count == 700 then
		syslog(string.format("CMD UI_SCORE_RESET"))
		sysCommand(pSCORE, UI_SCORE_RESET)
	end
	if count == 800 then
		syslog(string.format("CMD UI_SCORE_SET"))
		sysCommand(pSCORE, UI_SCORE_SET, 100)
	end
	if count == 900 then
		score = sysCommand(pSCORE, UI_SCORE_GET)
		syslog(string.format("CMD UI_SCORE_GET : %i", score))
	end
	if count == 1000 then
		syslog(string.format("CMD UI_SCORE_ALIGN"))
		sysCommand(pSCORE, UI_SCORE_ALIGN, SCORE_ALIGN_RIGHT)
	end
	
end


function leave()
end
