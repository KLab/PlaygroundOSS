function setup()
	syslog("a")
	tskCanvas = UI_Canvas(
		nil,
		7000,
		20,
		20,
		2000,
		2000,
		"drawfunc"
	)
	syslog("b")
	sysCommand(tskCanvas, UI_CANVAS_ADDRESOURCE, "asset://TileA.png.imag")	-- 0
	sysCommand(tskCanvas, UI_CANVAS_ADDRESOURCE, "asset://TileB.png.imag")	-- 1
	sysCommand(tskCanvas, UI_CANVAS_ADDRESOURCE, "asset://TileC.png.imag")	-- 2
	syslog("c")
	
	
	count = 0
end


function execute(deltaT)
	count = count + 1
	
	if count == 1 then
		drawfunc(tskCanvas)
	end
	if count == 20 then
		syslog(string.format("TASK alpha"))
		prop = TASK_getProperty(tskCanvas)
		prop.alpha = 128
		TASK_setProperty(tskCanvas, prop)	
	end
	if count == 40 then
		syslog(string.format("TASK color"))
		prop = TASK_getProperty(tskCanvas)
		prop.color = 0xFF00FF
		TASK_setProperty(tskCanvas, prop)	
	end
	if count == 60 then
		syslog(string.format("TASK scalex"))
		prop = TASK_getProperty(tskCanvas)
		prop.scaleX = 2.0
		TASK_setProperty(tskCanvas, prop)	
	end
	if count == 80 then
		syslog(string.format("TASK scaley"))
		prop = TASK_getProperty(tskCanvas)
		prop.scaleY = 2.0
		TASK_setProperty(tskCanvas, prop)	
	end
	if count == 100 then
		syslog(string.format("TASK rot"))
		prop = TASK_getProperty(tskCanvas)
		prop.rot = 25.0
		TASK_setProperty(tskCanvas, prop)	
	end
	if count == 120 then
		syslog(string.format("TASK x"))
		prop = TASK_getProperty(tskCanvas)
		prop.x = 200
		TASK_setProperty(tskCanvas, prop)	
	end
	if count == 140 then
		syslog(string.format("TASK y"))
		prop = TASK_getProperty(tskCanvas)
		prop.y = 200
		TASK_setProperty(tskCanvas, prop)	
	end
	if count == 160 then
		syslog(string.format("TASK visible = false"))
		prop = TASK_getProperty(tskCanvas)
		prop.visible = false
		TASK_setProperty(tskCanvas, prop)	
	end
	if count == 180 then
		syslog(string.format("TASK visible = true"))
		prop = TASK_getProperty(tskCanvas)
		prop.visible = true
		TASK_setProperty(tskCanvas, prop)	
	end
	
	if count == 200 then
		syslog(string.format("CMD UI_CANVAS_DRAWIMAGESCALE"))
		drawScaleFunc(tskCanvas)
	end
	if count == 300 then
		syslog(string.format("CMD UI_CANVAS_FILLRECT"))
		sysCommand(tskCanvas, UI_CANVAS_FILLRECT, 300, 0, 100, 100, 0xff, 0xff00ff)
	end
	if count == 380 then
		syslog(string.format("CMD UI_CANVAS_FREEZE"))
		sysCommand(tskCanvas, UI_CANVAS_FREEZE, false)
	end
	if count == 400 then
		syslog(string.format("CMD DYNAMIC"))
		sysCommand(tskCanvas, UI_CANVAS_FREEZE, true)
		sysCommand(tskCanvas, UI_CANVAS_STARTSECTION, 0)
		drawfunc(tskCanvas)
		sysCommand(tskCanvas, UI_CANVAS_ENDSECTION, 0)
		
	end
	if count == 450 then
		syslog(string.format("CMD UI_CANVAS_SECTIONTRANSLATE"))
		sysCommand(tskCanvas, UI_CANVAS_SECTIONTRANSLATE, 0, 100, 100)
	end
	if count == 500 then
		syslog(string.format("CMD UI_CANVAS_SECTIONCOLOR"))
		sysCommand(tskCanvas, UI_CANVAS_SECTIONCOLOR, 0, 0xff, 0xffffff)
	end
end


function leave()
end

function drawfunc(canvas)
	sysCommand(canvas, UI_CANVAS_DRAWIMAGE, 0, 0, 0, 0xFFFFFF, 255)
	sysCommand(canvas, UI_CANVAS_DRAWIMAGE, 20, 0, 1, 0xFFFFFF, 255)
	sysCommand(canvas, UI_CANVAS_DRAWIMAGE, 0, 20, 2, 0xFFFFFF, 255)
	-- sysCommand(canvas, UI_CANVAS_FREEZE, true);
end

function drawScaleFunc(canvas)
	sysCommand(canvas, UI_CANVAS_DRAWIMAGESCALE, 0,  0, 0.2, 0, 0xFFFFFF, 255)
	sysCommand(canvas, UI_CANVAS_DRAWIMAGESCALE, 20, 0, 0.2, 1, 0xFFFFFF, 255)
	sysCommand(canvas, UI_CANVAS_DRAWIMAGESCALE, 0, 20, 0.2, 2, 0xFFFFFF, 255)
	-- sysCommand(canvas, UI_CANVAS_FREEZE, true);
end