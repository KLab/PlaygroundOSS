function setup()
	pTB = UI_TextInput( nil, false, 	-- <parent pointer>, <password mode>, 
						100, 100,		-- <x>, <y>, 
						300, 40, 		-- <width>, <height>, 
						"default text",	-- "<default text>"
                        "onChangeCb",   -- [ , "<on-change-callback>", 
						0, 				-- <widget-id>, 
						20				-- <max-length>, <enable-chartype> ] )
						)
   
	count = 0
end


function execute(deltaT)
	count = count + 1
	if count == 20 then
		syslog(string.format("TASK alpha"))
		prop = TASK_getProperty(pTB)
		prop.alpha = 128
		TASK_setProperty(pTB, prop)	
	end
	if count == 40 then
		syslog(string.format("TASK color"))
		prop = TASK_getProperty(pTB)
		prop.color = 0xFF00FF
		TASK_setProperty(pTB, prop)	
	end
	if count == 60 then
		syslog(string.format("TASK scalex"))
		prop = TASK_getProperty(pTB)
		prop.scaleX = 2.0
		TASK_setProperty(pTB, prop)	
	end
	if count == 80 then
		syslog(string.format("TASK scaley"))
		prop = TASK_getProperty(pTB)
		prop.scaleY = 2.0
		TASK_setProperty(pTB, prop)	
	end
	if count == 100 then
		syslog(string.format("TASK rot"))
		prop = TASK_getProperty(pTB)
		prop.rot = 25.0
		TASK_setProperty(pTB, prop)	
	end
	if count == 120 then
		syslog(string.format("TASK x"))
		prop = TASK_getProperty(pTB)
		prop.x = 200
		TASK_setProperty(pTB, prop)	
	end
	if count == 140 then
		syslog(string.format("TASK y"))
		prop = TASK_getProperty(pTB)
		prop.y = 200
		TASK_setProperty(pTB, prop)	
	end
	if count == 160 then
		syslog(string.format("TASK visible = false"))
		prop = TASK_getProperty(pTB)
		prop.visible = false
		TASK_setProperty(pTB, prop)	
	end
	if count == 180 then
		syslog(string.format("TASK visible = true"))
		prop = TASK_getProperty(pTB)
		prop.visible = true
		TASK_setProperty(pTB, prop)	
	end
	
	if count == 200 then
		syslog(string.format("CMD UI_TEXTBOX_SETTEXT"))
		sysCommand(pTB, UI_TEXTBOX_SETTEXT, "Hello World!")
	end
	if count == 300 then
		str = sysCommand(pTB, UI_TEXTBOX_GETTEXT)
		syslog(string.format("CMD UI_TEXTBOX_GETTEXT : %s", str))
	end
	if count == 400 then
		syslog(string.format("CMD UI_TEXTBOX_SETPLACEHOLDER"))
		sysCommand(pTB, UI_TEXTBOX_SETPLACEHOLDER, "test")
	end
	if count == 500 then
		syslog(string.format("CMD UI_TEXTBOX_SETCOLOR"))
		sysCommand(pTB, UI_TEXTBOX_SETCOLOR, true, 0xFF0000, 0x0000FF)
	end
	if count == 600 then
		syslog(string.format("CMD UI_TEXTBOX_SETFONT"))
		sysCommand(pTB, UI_TEXTBOX_SETFONT, "Georgia", 32)
	end
	if count == 700 then
		syslog(string.format("CMD UI_TEXTBOX_SETMAXLEN"))
		sysCommand(pTB, UI_TEXTBOX_SETMAXLEN, 5)
	end
	if count == 750 then
		res = sysCommand(pTB, UI_TEXTBOX_GETMAXLEN)
		syslog(string.format("CMD UI_TEXTBOX_GETMAXLEN : %i", res))
	end
	if count == 800 then
		syslog(string.format("CMD UI_TEXTBOX_SETCHARTYPE"))
		sysCommand(pTB, UI_TEXTBOX_SETCHARTYPE, 1)
	end
	if count == 850 then
		res = sysCommand(pTB, UI_TEXTBOX_GETCHARCOUNT)
		syslog(string.format("CMD UI_TEXTBOX_GETCHARCOUNT : %i", res))
	end
end


function leave()
end

function onChangeCb(ptr, newStr, id)
	syslog(string.format("callback - new string = %s", newStr))
end
