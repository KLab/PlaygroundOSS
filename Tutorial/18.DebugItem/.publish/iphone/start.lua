function setup()
	FONT_load("Georgia","asset://AlexBrush-Regular-OTF.otf")
	pDbgLabel = UI_DbgLabel(
							nil,				--<parent pointer>, 
							7000,				--<order>, 
							100,100,			--<x>, <y>,
                            0xFF, 0xFF0000,		--<alpha>, <rgb>, 
							"Georgia", 16,		--"<font name>", <font size>, 
							"Debug Label",		--"<text string>",
							1,					--<cmdID>, 
							"callback"			--"<callback>")
							)
	count = 0
end


function execute(deltaT)
	count = count + 1
	if count == 20 then
		syslog(string.format("TASK alpha"))
		prop = TASK_getProperty(pDbgLabel)
		prop.alpha = 128
		TASK_setProperty(pDbgLabel, prop)	
	end
	if count == 40 then
		syslog(string.format("TASK color"))
		prop = TASK_getProperty(pDbgLabel)
		prop.color = 0xFF00FF
		TASK_setProperty(pDbgLabel, prop)	
	end
	if count == 60 then
		syslog(string.format("TASK scalex"))
		prop = TASK_getProperty(pDbgLabel)
		prop.scaleX = 2.0
		TASK_setProperty(pDbgLabel, prop)	
	end
	if count == 80 then
		syslog(string.format("TASK scaley"))
		prop = TASK_getProperty(pDbgLabel)
		prop.scaleY = 2.0
		TASK_setProperty(pDbgLabel, prop)	
	end
	if count == 100 then
		syslog(string.format("TASK rot"))
		prop = TASK_getProperty(pDbgLabel)
		prop.rot = 25.0
		TASK_setProperty(pDbgLabel, prop)	
	end
	if count == 120 then
		syslog(string.format("TASK x"))
		prop = TASK_getProperty(pDbgLabel)
		prop.x = 200
		TASK_setProperty(pDbgLabel, prop)	
	end
	if count == 140 then
		syslog(string.format("TASK y"))
		prop = TASK_getProperty(pDbgLabel)
		prop.y = 200
		TASK_setProperty(pDbgLabel, prop)	
	end
	if count == 160 then
		syslog(string.format("TASK visible = false"))
		prop = TASK_getProperty(pDbgLabel)
		prop.visible = false
		TASK_setProperty(pDbgLabel, prop)	
	end
	if count == 180 then
		syslog(string.format("TASK visible = true"))
		prop = TASK_getProperty(pDbgLabel)
		prop.visible = true
		prop.order = 8000
		TASK_setProperty(pDbgLabel, prop)	
	end
	
	if count == 200 then
		syslog(string.format("font"))
		prop = TASK_getProperty(pDbgLabel)
		prop.font = "fixed"
		TASK_setProperty(pDbgLabel, prop)
	end
	if count == 220 then
		syslog(string.format("size"))
		prop = TASK_getProperty(pDbgLabel)
		prop.size = 32
		TASK_setProperty(pDbgLabel, prop)
	end
	if count == 240 then
		syslog(string.format("alpha"))
		prop = TASK_getProperty(pDbgLabel)
		prop.alpha = 0x40
		TASK_setProperty(pDbgLabel, prop)
	end
	if count == 280 then
		syslog(string.format("color"))
		prop = TASK_getProperty(pDbgLabel)
		prop.color = 0x0000FF
		TASK_setProperty(pDbgLabel, prop)
	end
	if count == 300 then
		syslog(string.format("text"))
		prop = TASK_getProperty(pDbgLabel)
		prop.text = "I've changed."
		TASK_setProperty(pDbgLabel, prop)
	end
end


function leave()

end

function callback(pTask, cmdID)
	syslog("CALLBACK"..cmdID)
end
