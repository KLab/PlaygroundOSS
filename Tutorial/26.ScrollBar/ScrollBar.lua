function setup()
-- OK test : horiz, vertical.
-- OK test : double graphics.
-- OK test : Enable / Disabled.
-- TODO test : texture 90 rot.
-- TODO call back func support.

	local x = 100
	local y = 100
	pHorizScroll = UI_ScrollBar(	nil,								-- arg[1]:		親となるUIタスクポインタ
											7000,						-- arg[2]:		表示プライオリティ
											x, y,						-- arg[3,4]:	表示位置
											200,						-- Width
											25,							-- Height
											-5,							-- Min Value
											5,							-- Max Value
											0,							-- Current Value
											"asset://Horiz.png.imag",	-- Image
											50,							-- Slider size
											25,							-- Min size

--											17,9,18,					-- Asset Size
--											false,						-- Selected Graphics
											
											false,						-- Vertical is false -> Horizontal
											"callback",
											true,						-- Touch event enabled
											255,						-- Alpha Normal
											128							-- Alpha Selected
								)

	pVertScroll = UI_ScrollBar(	nil,									-- arg[1]:		親となるUIタスクポインタ
											7000,						-- arg[2]:		表示プライオリティ
											400, 400,					-- arg[3,4]:	表示位置
											25,							-- Width
											200,						-- Height
											-5,							-- Min Value
											5,							-- Max Value
											0,							-- Current Value
											"asset://Vert.png.imag",	-- Image
											50,							-- Slider size
											25,							-- Min size

--											17,9,18,					-- Asset Size
--											false,						-- Selected Graphics
											
											true,						-- Vertical is false -> Horizontal
											nil,
											true,						-- Touch event enabled
											255,						-- Alpha Normal
											128							-- Alpha Selected
								)
								
	-- 2 Style bitmap
	pHScroll2 = UI_ScrollBar(	nil,									-- arg[1]:		親となるUIタスクポインタ
											7000,						-- arg[2]:		表示プライオリティ
											0, 400,						-- arg[3,4]:	表示位置
											200,						-- Width
											25,							-- Height
											0,							-- Min Value
											150,						-- Max Value
											0,							-- Current Value
											"asset://Horiz2.png.imag",	-- Image
											50,							-- Slider size
											25,							-- Min size

--											17,9,18,					-- Asset Size
--											true,						-- Selected Graphics
											
											false,						-- Vertical is false -> Horizontal
											nil,
											true,						-- Touch event enabled
											255,						-- Alpha Normal
											128							-- Alpha Selected
								)
								
	-- 2 Style bitmap
	pVertScroll = UI_ScrollBar(	nil,									-- arg[1]:		親となるUIタスクポインタ
											7000,						-- arg[2]:		表示プライオリティ
											400, 0,						-- arg[3,4]:	表示位置
											25,							-- Width
											200,						-- Height
											0,							-- Min Value
											150,						-- Max Value
											0,							-- Current Value
											"asset://Vert2.png.imag",	-- Image
											50,							-- Slider size
											25,							-- Min size

--											17,9,18,					-- Asset Size
--											true,						-- Selected Graphics
											
											true,						-- Vertical
											nil,
											true,						-- Touch event enabled
											255,						-- Alpha Normal
											128							-- Alpha Selected
								)
								
	count = 0
end


function execute(deltaT)

	count = count + 1
	if count == 20 then
		syslog(string.format("TASK alpha"))
		prop = TASK_getProperty(pHorizScroll)
		prop.alpha = 128
		TASK_setProperty(pHorizScroll, prop)	
	end
	if count == 40 then
		syslog(string.format("TASK color"))
		prop = TASK_getProperty(pHorizScroll)
		prop.color = 0xFF00FF
		TASK_setProperty(pHorizScroll, prop)	
	end
	if count == 60 then
		syslog(string.format("TASK scalex"))
		prop = TASK_getProperty(pHorizScroll)
		prop.scaleX = 2.0
		TASK_setProperty(pHorizScroll, prop)	
	end
	if count == 80 then
		syslog(string.format("TASK scaley"))
		prop = TASK_getProperty(pHorizScroll)
		prop.scaleY = 2.0
		TASK_setProperty(pHorizScroll, prop)	
	end
	if count == 100 then
		syslog(string.format("TASK rot"))
		prop = TASK_getProperty(pHorizScroll)
		prop.rot = 25.0
		TASK_setProperty(pHorizScroll, prop)	
	end
	if count == 120 then
		syslog(string.format("TASK x"))
		prop = TASK_getProperty(pHorizScroll)
		prop.x = 200
		TASK_setProperty(pHorizScroll, prop)	
	end
	if count == 140 then
		syslog(string.format("TASK y"))
		prop = TASK_getProperty(pHorizScroll)
		prop.y = 200
		TASK_setProperty(pHorizScroll, prop)	
	end
	if count == 160 then
		syslog(string.format("TASK visible = false"))
		prop = TASK_getProperty(pHorizScroll)
		prop.visible = false
		TASK_setProperty(pHorizScroll, prop)	
	end
	if count == 180 then
		syslog(string.format("TASK visible = true"))
		prop = TASK_getProperty(pHorizScroll)
		prop.visible = true
		TASK_setProperty(pHorizScroll, prop)	
	end
	
	if count == 200 then
		syslog(string.format("order"))
		prop = TASK_getProperty(pHorizScroll)
		prop.order = 8000
		TASK_setProperty(pHorizScroll, prop)	
	end
	if count == 220 then
		syslog(string.format("width"))
		prop = TASK_getProperty(pHorizScroll)
		prop.width = 500
		TASK_setProperty(pHorizScroll, prop)	
	end
	if count == 240 then
		syslog(string.format("height"))
		prop = TASK_getProperty(pHorizScroll)
		prop.height = 100
		TASK_setProperty(pHorizScroll, prop)	
	end
	if count == 260 then
		syslog(string.format("min"))
		prop = TASK_getProperty(pHorizScroll)
		prop.min = -3
		TASK_setProperty(pHorizScroll, prop)	
	end
	if count == 280 then
		syslog(string.format("max"))
		prop = TASK_getProperty(pHorizScroll)
		prop.max = 10
		TASK_setProperty(pHorizScroll, prop)	
	end
	if count == 300 then
		syslog(string.format("pos"))
		prop = TASK_getProperty(pHorizScroll)
		prop.pos = 10
		TASK_setProperty(pHorizScroll, prop)	
	end
	if count == 320 then
		syslog(string.format("img"))
		prop = TASK_getProperty(pHorizScroll)
		prop.img = "forbidden"
		TASK_setProperty(pHorizScroll, prop)	
	end
	if count == 340 then
		syslog(string.format("slider_size"))
		prop = TASK_getProperty(pHorizScroll)
		prop.slider_size = 100
		TASK_setProperty(pHorizScroll, prop)	
	end
	if count == 360 then
		syslog(string.format("slider_minsize"))
		prop = TASK_getProperty(pHorizScroll)
		prop.slider_minsize = 50
		TASK_setProperty(pHorizScroll, prop)	
	end
	if count == 380 then
		syslog(string.format("f_vert"))
		prop = TASK_getProperty(pHorizScroll)
		prop.f_vert = true
		TASK_setProperty(pHorizScroll, prop)	
	end
	if count == 400 then
		syslog(string.format("callback"))
		prop = TASK_getProperty(pHorizScroll)
		prop.f_vert = false
		prop.callback = "forbidden"
		TASK_setProperty(pHorizScroll, prop)	
	end
	if count == 420 then
		syslog(string.format("alpha_normal"))
		prop = TASK_getProperty(pHorizScroll)
		prop.alpha_normal = 0x80
		TASK_setProperty(pHorizScroll, prop)	
	end
	if count == 440 then
		syslog(string.format("alpha_select"))
		prop = TASK_getProperty(pHorizScroll)
		prop.alpha_select = 0xff
		TASK_setProperty(pHorizScroll, prop)	
	end
	if count == 460 then
		syslog(string.format("color_normal"))
		prop = TASK_getProperty(pHorizScroll)
		prop.color_normal = 0xff0000
		TASK_setProperty(pHorizScroll, prop)	
	end
	if count == 480 then
		syslog(string.format("color_select"))
		prop = TASK_getProperty(pHorizScroll)
		prop.color_select = 0x0000ff
		TASK_setProperty(pHorizScroll, prop)	
	end
	if count == 500 then
		syslog(string.format("touch_active = false"))
		prop = TASK_getProperty(pHorizScroll)
		prop.touch_active = false
		TASK_setProperty(pHorizScroll, prop)
	end
	
	if count == 550 then 
		syslog(string.format("CMD UI_SCROLL_SET_MIN"))
		prop = TASK_getProperty(pHorizScroll)
		prop.touch_active = true
		TASK_setProperty(pHorizScroll, prop)	
		sysCommand(pHorizScroll, UI_SCROLL_SET_MIN, 0)
	end
	if count == 560 then 
		ret = sysCommand(pHorizScroll, UI_SCROLL_GET_MIN)
		syslog(string.format("CMD UI_SCROLL_GET_MIN = %i", ret))
	end
	if count == 580 then 
		syslog(string.format("CMD UI_SCROLL_SET_MAX"))
		sysCommand(pHorizScroll, UI_SCROLL_SET_MAX, 2)
	end
	if count == 600 then 
		ret = sysCommand(pHorizScroll, UI_SCROLL_GET_MAX)
		syslog(string.format("CMD UI_SCROLL_GET_MAX = %i", ret))
	end
	if count == 620 then 
		syslog(string.format("CMD UI_SCROLL_SET_POS"))
		sysCommand(pHorizScroll, UI_SCROLL_SET_POS, 1)
	end
	if count == 640 then 
		ret = sysCommand(pHorizScroll, UI_SCROLL_GET_POS)
		syslog(string.format("CMD UI_SCROLL_GET_POS = %i", ret))
	end
	if count == 660 then 
		syslog(string.format("CMD UI_SCROLL_SET_SLIDER_SIZE"))
		sysCommand(pHorizScroll, UI_SCROLL_SET_SLIDER_SIZE, 200)
	end
	if count == 680 then 
		ret = sysCommand(pHorizScroll, UI_SCROLL_GET_SLIDER_SIZE)
		syslog(string.format("CMD UI_SCROLL_GET_SLIDER_SIZE = %i", ret))
	end
	if count == 700 then 
		syslog(string.format("CMD UI_SCROLL_SET_SLIDER_MIN_SIZE"))
		sysCommand(pHorizScroll, UI_SCROLL_SET_SLIDER_MIN_SIZE, 10)
	end
	if count == 720 then 
		ret = sysCommand(pHorizScroll, UI_SCROLL_GET_SLIDER_MIN_SIZE)
		syslog(string.format("CMD UI_SCROLL_GET_SLIDER_MIN_SIZE = %i", ret))
	end
	if count == 740 then 
		syslog(string.format("CMD UI_SCROLL_SET_COLOR_NORMAL"))
		sysCommand(pHorizScroll, UI_SCROLL_SET_COLOR_NORMAL, 0x000000)
	end
	if count == 760 then 
		ret = sysCommand(pHorizScroll, UI_SCROLL_GET_COLOR_NORMAL)
		syslog(string.format("CMD UI_SCROLL_GET_COLOR_NORMAL = %i", ret))
	end
	if count == 780 then 
		syslog(string.format("CMD UI_SCROLL_SET_COLOR_SELECT"))
		sysCommand(pHorizScroll, UI_SCROLL_SET_COLOR_SELECT, 0xffffff)
	end
	if count == 800 then 
		ret = sysCommand(pHorizScroll, UI_SCROLL_GET_COLOR_SELECT)
		syslog(string.format("CMD UI_SCROLL_GET_COLOR_SELECT = %i", ret))
	end
	if count == 820 then 
		syslog(string.format("CMD UI_SCROLL_SET_ALPHA_NORMAL"))
		sysCommand(pHorizScroll, UI_SCROLL_SET_ALPHA_NORMAL, 0xff)
	end
	if count == 840 then 
		ret = sysCommand(pHorizScroll, UI_SCROLL_GET_ALPHA_NORMAL)
		syslog(string.format("CMD UI_SCROLL_GET_ALPHA_NORMAL = %i", ret))
	end
	if count == 860 then 
		syslog(string.format("CMD UI_SCROLL_SET_ALPHA_SELECT"))
		sysCommand(pHorizScroll, UI_SCROLL_SET_ALPHA_SELECT, 0x00)
	end
	if count == 880 then 
		ret = sysCommand(pHorizScroll, UI_SCROLL_GET_ALPHA_SELECT)
		syslog(string.format("CMD UI_SCROLL_GET_ALPHA_SELECT = %i", ret))
	end
	if count == 900 then 
		syslog(string.format("CMD UI_SCROLL_SET_TOUCH_ACTIVE"))
		sysCommand(pHorizScroll, UI_SCROLL_SET_TOUCH_ACTIVE, false)
	end
	if count == 920 then 
		ret = sysCommand(pHorizScroll, UI_SCROLL_GET_TOUCH_ACTIVE)
		syslog(string.format("CMD UI_SCROLL_GET_TOUCH_ACTIVE = %i", ret))
	end
	if count == 940 then 
		syslog(string.format("CMD UI_SCROLL_SELECT_SCRMGR"))
		sysCommand(pHorizScroll, UI_SCROLL_SELECT_SCRMGR, "name")
	end
end


function leave()
end

function callback(task, evnt_type, value)
	syslog(string.format("Value %i",value))
end
