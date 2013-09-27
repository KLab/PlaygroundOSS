function setup()
	pPoly1 = UI_Polyline(nil, 7000, 3)
	pPoly2 = UI_Polyline(nil, 7001, 3)
	
	sysCommand(pPoly1, UI_POLYLINE_SET_POINTCOUNT, 2)
	sysCommand(pPoly1 , UI_POLYLINE_SET_COLOR, 0xff, 0x0000FF)
	sysCommand(pPoly1 , UI_POLYLINE_SET_POINT, 0, 300, 500)
	sysCommand(pPoly1 , UI_POLYLINE_SET_POINT, 1, 500, 200)
	
	sysCommand(pPoly2, UI_POLYLINE_SET_POINTCOUNT, 2)
	sysCommand(pPoly2 , UI_POLYLINE_SET_COLOR, 0xff, 0xFFFFFF)
	sysCommand(pPoly2 , UI_POLYLINE_SET_POINT, 0, 600, 500)
	sysCommand(pPoly2 , UI_POLYLINE_SET_POINT, 1, 400, 200)
	
	count = 0
end


function execute(deltaT)
	count = count + 1
	if count == 20 then
		syslog(string.format("TASK alpha"))
		prop = TASK_getProperty(pPoly1)
		prop.alpha = 0x80
		TASK_setProperty(pPoly1, prop)	
	end
	if count == 40 then
		syslog(string.format("TASK color"))
		prop = TASK_getProperty(pPoly2)
		prop.color = 0xFF0000
		TASK_setProperty(pPoly2, prop)	
	end
	if count == 60 then
		syslog(string.format("TASK scalex"))
		prop = TASK_getProperty(pPoly1)
		prop.scaleX = 0.5
		TASK_setProperty(pPoly1, prop)	
	end
	if count == 80 then
		syslog(string.format("TASK scaley"))
		prop = TASK_getProperty(pPoly1)
		prop.scaleY = 0.5
		TASK_setProperty(pPoly1, prop)	
	end
	if count == 100 then
		syslog(string.format("TASK rot"))
		prop = TASK_getProperty(pPoly1)
		prop.rot = 25.0
		TASK_setProperty(pPoly1, prop)	
	end
	if count == 120 then
		syslog(string.format("TASK x"))
		prop = TASK_getProperty(pPoly1)
		prop.x = 250
		TASK_setProperty(pPoly1, prop)	
	end
	if count == 140 then
		syslog(string.format("TASK y"))
		prop = TASK_getProperty(pPoly1)
		prop.y = 200
		TASK_setProperty(pPoly1, prop)	
	end
	if count == 160 then
		syslog(string.format("TASK visible = false"))
		prop = TASK_getProperty(pPoly1)
		prop.visible = false
		TASK_setProperty(pPoly1, prop)	
	end
	if count == 180 then
		syslog(string.format("TASK visible = true"))
		prop = TASK_getProperty(pPoly1)
		prop.visible = true
		TASK_setProperty(pPoly1, prop)	
	end
	
	if count == 200 then
		syslog(string.format("order"))
		prop = TASK_getProperty(pPoly1)
		prop.order = 7002
		TASK_setProperty(pPoly1, prop)	
	end
	if count == 200 then
		syslog(string.format("maxpointcount"))
		prop = TASK_getProperty(pPoly2)
		prop.maxpointcount = 5
		TASK_setProperty(pPoly2, prop)
		sysCommand(pPoly2 , UI_POLYLINE_SET_POINTCOUNT, 5)
		sysCommand(pPoly2 , UI_POLYLINE_SET_POINT, 0, 100, 100)
		sysCommand(pPoly2 , UI_POLYLINE_SET_POINT, 1, 100, 200)
		sysCommand(pPoly2 , UI_POLYLINE_SET_POINT, 2, 200, 200)
		sysCommand(pPoly2 , UI_POLYLINE_SET_POINT, 3, 200, 100)
		sysCommand(pPoly2 , UI_POLYLINE_SET_POINT, 4, 150, 100)
	end
	
end


function leave()
end
