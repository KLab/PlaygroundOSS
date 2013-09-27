function setup()
	FONT_load("AlexBrush","asset://AlexBrush-Regular-OTF.otf")
	pLabel = UI_Label 	(
							nil, 			-- <parent pointer>, 
							7000, 			-- <order>, 
							100,100,		-- <x>, <y>,
                            0xFF, 0x000000,	-- <alpha>, <rgb>, 
							"AlexBrush",	-- "<font name>", 
							32,				-- <font size>, 
							"Hello World!"	-- "<text string>"
						)

	count = 0
end


function execute(deltaT)
	count = count + 1
	if count == 20 then
		syslog(string.format("TASK alpha"))
		prop = TASK_getProperty(pLabel)
		prop.alpha = 128
		TASK_setProperty(pLabel, prop)	
	end
	if count == 40 then
		syslog(string.format("TASK color"))
		prop = TASK_getProperty(pLabel)
		prop.color = 0xFF00FF
		TASK_setProperty(pLabel, prop)	
	end
	if count == 60 then
		syslog(string.format("TASK scalex"))
		prop = TASK_getProperty(pLabel)
		prop.scaleX = 2.0
		TASK_setProperty(pLabel, prop)	
	end
	if count == 80 then
		syslog(string.format("TASK scaley"))
		prop = TASK_getProperty(pLabel)
		prop.scaleY = 2.0
		TASK_setProperty(pLabel, prop)	
	end
	if count == 100 then
		syslog(string.format("TASK rot"))
		prop = TASK_getProperty(pLabel)
		prop.rot = 25.0
		TASK_setProperty(pLabel, prop)	
	end
	if count == 120 then
		syslog(string.format("TASK x"))
		prop = TASK_getProperty(pLabel)
		prop.x = 200
		TASK_setProperty(pLabel, prop)	
	end
	if count == 140 then
		syslog(string.format("TASK y"))
		prop = TASK_getProperty(pLabel)
		prop.y = 200
		TASK_setProperty(pLabel, prop)	
	end
	if count == 160 then
		syslog(string.format("TASK visible = false"))
		prop = TASK_getProperty(pLabel)
		prop.visible = false
		TASK_setProperty(pLabel, prop)	
	end
	if count == 180 then
		syslog(string.format("TASK visible = true"))
		prop = TASK_getProperty(pLabel)
		prop.visible = true
		prop.order = 8000
		TASK_setProperty(pLabel, prop)	
	end
	if count == 200 then
		syslog(string.format("font"))
		prop = TASK_getProperty(pLabel)
		prop.font = "arial"
		TASK_setProperty(pLabel, prop)
	end
	if count == 220 then
		syslog(string.format("size"))
		prop = TASK_getProperty(pLabel)
		prop.size = prop.size * 2
		TASK_setProperty(pLabel, prop)
	end
	if count == 240 then
		syslog(string.format("txt_alpha"))
		prop = TASK_getProperty(pLabel)
		prop.txt_alpha = 0x80
		TASK_setProperty(pLabel, prop)
	end
	if count == 260 then
		syslog(string.format("txt_color"))
		prop = TASK_getProperty(pLabel)
		prop.txt_color = 0x0000FF
		TASK_setProperty(pLabel, prop)
	end
	if count == 280 then
		syslog(string.format("text"))
		prop = TASK_getProperty(pLabel)
		prop.text = "I swear I've changed!"
		TASK_setProperty(pLabel, prop)
	end
	if count == 300 then
		syslog(string.format("align"))
		prop = TASK_getProperty(pLabel)
		prop.align = 1
		TASK_setProperty(pLabel, prop)
	end
	
	if count == 320 then
		syslog(string.format("CMD UI_LABEL_SET_TEXT"))
		sysCommand(pLabel, UI_LABEL_SET_TEXT, "Once again")
	end
	if count == 340 then
		syslog(string.format("CMD UI_LABEL_SET_COLOR"))
		sysCommand(pLabel, UI_LABEL_SET_COLOR, 0x40, 0xFF0000)
	end
	if count == 360 then
		syslog(string.format("CMD UI_LABEL_SET_FONT"))
		sysCommand(pLabel, UI_LABEL_SET_FONT, "fixed", 12)
	end
	if count == 380 then
		syslog(string.format("CMD UI_LABEL_SET_POSITION"))
		sysCommand(pLabel, UI_LABEL_SET_POSITION, 500, 100)
	end
	if count == 400 then
		syslog(string.format("CMD UI_LABEL_SET_ALIGNMENT"))
		sysCommand(pLabel, UI_LABEL_SET_ALIGNMENT, 5)
	end
end


function leave()

end
