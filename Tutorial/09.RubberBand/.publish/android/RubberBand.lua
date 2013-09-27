function setup()
	pRB = nil
	UI_TouchPad("callback_TouchPad")

	local list = {
		on = "asset://se_on",
		off = "asset://se_off",
		drag = "asset://se_drag"
	}
	snd = {}
	for key,val in pairs(list) do
		snd[key] = SND_Open(val, false)
	end
end


function execute(deltaT)
end


function leave()
	for key,val in pairs(snd) do
		SND_Close(val)
	end
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
							500,
							nil,
							nil,
							true,
							true,
							true
							)
			SND_Play(snd["on"])
		elseif item.type == PAD_ITEM_DRAG then
			prop = TASK_getProperty(pRB)
			prop.pointX = item.x
			prop.pointY = item.y
			TASK_setProperty(pRB, prop)
		elseif item.type == PAD_ITEM_RELEASE then
			pRB = TASK_kill(pRB)
			SND_Volume(snd["off"], item.x / 960.0)
			SND_Play(snd["off"])
		end
	end
end
