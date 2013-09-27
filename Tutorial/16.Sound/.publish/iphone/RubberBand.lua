function setup()
	pRB = nil
	UI_TouchPad("callback_TouchPad")

	bgm = SND_Open("asset://bgm", true)
	seON = SND_Open("asset://se_on")
	seOFF = SND_Open("asset://se_off")
	seDRAG = SND_Open("asset://se_drag")
	tcount = 0
	SND_Play(bgm)
end


function execute(deltaT)
	tcount = tcount + deltaT
end


function leave()
	seDRAG, seOFF, seON = SND_Close(seDRAG, seOFF, seON)
	bgm = SND_Close(bgm)
end


function callback_TouchPad(arr)

	for idx,item in ipairs(arr) do

		if item.type == PAD_ITEM_TAP then

			local flag = bitOR(RB_ANIM_ENABLE, RB_ANIM_REALTIME)
			pRB = UI_RubberBand(nil,
							7000,
							item.x, item.y,		-- 原点位置
							"asset://origin.png.imag",		-- 原点画像
							"asset://joint.png.imag",		-- 節画像
							"asset://point.png.imag",		-- 先端画像
							10,								-- 分割数
							flag,
							500
							)
			SND_Play(seON)

		elseif item.type == PAD_ITEM_DRAG then
			prop = TASK_getProperty(pRB)
			prop.pointX = item.x
			prop.pointY = item.y
			TASK_setProperty(pRB, prop)
			if tcount > 200 then
				SND_Play(seDRAG)
				tcount = 0
			end
		elseif item.type == PAD_ITEM_RELEASE then
			pRB = TASK_kill(pRB)
			SND_Play(seOFF)
		end

	end
end
