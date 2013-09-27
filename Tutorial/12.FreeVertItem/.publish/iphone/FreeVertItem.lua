function setup()
	
	verticesArray = {
		100,100,   -- left top
		200,100,   -- right top
		200,200,   -- right bottom
		100,200    -- left bottom
	} 
   
	pFVI = UI_FreeVertItem( nil, 7000, 100, 100, "asset://TileA.png.imag", verticesArray)
	
	
	count = 0
end


function execute(deltaT)
	count = count + 1
	
	if count == 20 then
		syslog(string.format("TASK alpha"))
		prop = TASK_getProperty(pFVI)
		prop.alpha = 128
		TASK_setProperty(pFVI, prop)	
	end
	if count == 40 then
		syslog(string.format("TASK color"))
		prop = TASK_getProperty(pFVI)
		prop.color = 0xFF00FF
		TASK_setProperty(pFVI, prop)	
	end
	if count == 60 then
		syslog(string.format("TASK scalex"))
		prop = TASK_getProperty(pFVI)
		prop.scaleX = 2.0
		TASK_setProperty(pFVI, prop)	
	end
	if count == 80 then
		syslog(string.format("TASK scaley"))
		prop = TASK_getProperty(pFVI)
		prop.scaleY = 2.0
		TASK_setProperty(pFVI, prop)	
	end
	if count == 100 then
		syslog(string.format("TASK rot"))
		prop = TASK_getProperty(pFVI)
		prop.rot = 25.0
		TASK_setProperty(pFVI, prop)	
	end
	if count == 120 then
		syslog(string.format("TASK x"))
		prop = TASK_getProperty(pFVI)
		prop.x = 200
		TASK_setProperty(pFVI, prop)	
	end
	if count == 140 then
		syslog(string.format("TASK y"))
		prop = TASK_getProperty(pFVI)
		prop.y = 200
		TASK_setProperty(pFVI, prop)	
	end
	if count == 160 then
		syslog(string.format("TASK visible = false"))
		prop = TASK_getProperty(pFVI)
		prop.visible = false
		TASK_setProperty(pFVI, prop)	
	end
	if count == 180 then
		syslog(string.format("TASK visible = true"))
		prop = TASK_getProperty(pFVI)
		prop.visible = true
		TASK_setProperty(pFVI, prop)	
	end
	if count == 200 then 
		syslog(string.format("order"))
		prop = TASK_getProperty(pFVI)
		prop.order = 8000
		TASK_setProperty(pFVI, prop)
	end
	if count == 220 then 
		syslog(string.format("asset"))
		prop = TASK_getProperty(pFVI)
		prop.asset = "forbidden"
		TASK_setProperty(pFVI, prop)
	end
	
	if count == 240 then
		coords = { 100, 100, 100, 200, 200, 200, 200, 100 }
		syslog(string.format("CMD UI_FREEVERT_SET_VERTICES"))
		sysCommand(pFVI, UI_FREEVERT_SET_VERTICES, coords)
	end
	if count == 240 then 
		colors = { 0xff000000, 0xffff0000, 0xff00ff00, 0xff0000ff }
		syslog(string.format("CMD UI_FREEVERT_SET_COLORS"))
		sysCommand(pFVI, UI_FREEVERT_SET_COLORS, colors)
	end
	if count == 240 then 
		syslog(string.format("CMD UI_FREEVERT_SET_VERT_COL"))
		sysCommand(pFVI, UI_FREEVERT_SET_VERT_COL, 1, 0xff, 0xffffff)
	end
	if count == 240 then 
		uv = { 0, 0, 0, 1, 1, 1, 1, 0 };
		syslog(string.format("CMD UI_FREEVERT_SET_UV"))
		sysCommand(pFVI, UI_FREEVERT_SET_UV, uv)
	end
end


function leave()
end

