-- -*- coding: utf-8-unix -*-
---
-- @file Scale9.lua
-- @author Junichi Yamazaki
-- @since 2012-08-31

local pScale9
local count = 0
local asset = "asset://Horiz.png.imag"

function setup()

  count = 0

  pScale9   = UI_Scale9(nil, 7000, 10, 10, 100, 100, asset)
  pScale9_2 = UI_Scale9(nil, 6000, 60, 60, 200, 200, asset)

end


function execute(deltaT)
	count = count + 1
	
	if count == 20 then
		syslog(string.format("TASK alpha"))
		prop = TASK_getProperty(pScale9)
		prop.alpha = 128
		TASK_setProperty(pScale9, prop)	
	end
	if count == 40 then
		syslog(string.format("TASK color"))
		prop = TASK_getProperty(pScale9)
		prop.color = 0xFF00FF
		TASK_setProperty(pScale9, prop)	
	end
	if count == 60 then
		syslog(string.format("TASK scalex"))
		prop = TASK_getProperty(pScale9)
		prop.scaleX = 2.0
		TASK_setProperty(pScale9, prop)	
	end
	if count == 80 then
		syslog(string.format("TASK scaley"))
		prop = TASK_getProperty(pScale9)
		prop.scaleY = 2.0
		TASK_setProperty(pScale9, prop)	
	end
	if count == 100 then
		syslog(string.format("TASK rot"))
		prop = TASK_getProperty(pScale9)
		prop.rot = 25.0
		TASK_setProperty(pScale9, prop)	
	end
	if count == 120 then
		syslog(string.format("TASK x"))
		prop = TASK_getProperty(pScale9)
		prop.x = 200
		TASK_setProperty(pScale9, prop)	
	end
	if count == 140 then
		syslog(string.format("TASK y"))
		prop = TASK_getProperty(pScale9)
		prop.y = 200
		TASK_setProperty(pScale9, prop)	
	end
	if count == 160 then
		syslog(string.format("TASK visible = false"))
		prop = TASK_getProperty(pScale9)
		prop.visible = false
		TASK_setProperty(pScale9, prop)	
	end
	if count == 180 then
		syslog(string.format("TASK visible = true"))
		prop = TASK_getProperty(pScale9)
		prop.visible = true
		TASK_setProperty(pScale9, prop)	
	end
	
	if count == 200 then
		syslog(string.format("order"))
		prop = TASK_getProperty(pScale9)
		prop.order = 5000
		TASK_setProperty(pScale9, prop)	
	end
	if count == 220 then
		syslog(string.format("width"))
		prop = TASK_getProperty(pScale9)
		prop.width = 400
		TASK_setProperty(pScale9, prop)	
	end
	if count == 240 then
		syslog(string.format("height"))
		prop = TASK_getProperty(pScale9)
		prop.height = 50
		TASK_setProperty(pScale9, prop)	
	end
	
	if count == 300 then
		syslog(string.format("CMD UI_SCALE9_SETWIDTH"))
		sysCommand(pScale9, UI_SCALE9_SETWIDTH, 600)
	end
	if count == 400 then
		syslog(string.format("CMD UI_SCALE9_SETHEIGHT"))
		sysCommand(pScale9, UI_SCALE9_SETHEIGHT, 100)
	end

  -- syslog("" .. count)
end


function leave()
end
