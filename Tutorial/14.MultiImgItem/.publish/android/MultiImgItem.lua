function setup()
	pAssetList = {
      "asset://TileA.png.imag",
      "asset://TileB.png.imag",
	  "asset://TileC.png.imag"
   }
   pMIT = UI_MultiImgItem( nil, 7000, 100, 100, pAssetList, 2)
   
	count = 0
end


function execute(deltaT)
	count = count + 1
	if count == 20 then
		syslog(string.format("TASK alpha"))
		prop = TASK_getProperty(pMIT)
		prop.alpha = 128
		TASK_setProperty(pMIT, prop)	
	end
	if count == 40 then
		syslog(string.format("TASK color"))
		prop = TASK_getProperty(pMIT)
		prop.color = 0xFF00FF
		TASK_setProperty(pMIT, prop)	
	end
	if count == 60 then
		syslog(string.format("TASK scalex"))
		prop = TASK_getProperty(pMIT)
		prop.scaleX = 2.0
		TASK_setProperty(pMIT, prop)	
	end
	if count == 80 then
		syslog(string.format("TASK scaley"))
		prop = TASK_getProperty(pMIT)
		prop.scaleY = 2.0
		TASK_setProperty(pMIT, prop)	
	end
	if count == 100 then
		syslog(string.format("TASK rot"))
		prop = TASK_getProperty(pMIT)
		prop.rot = 25.0
		TASK_setProperty(pMIT, prop)	
	end
	if count == 120 then
		syslog(string.format("TASK x"))
		prop = TASK_getProperty(pMIT)
		prop.x = 200
		TASK_setProperty(pMIT, prop)	
	end
	if count == 140 then
		syslog(string.format("TASK y"))
		prop = TASK_getProperty(pMIT)
		prop.y = 200
		TASK_setProperty(pMIT, prop)	
	end
	if count == 160 then
		syslog(string.format("TASK visible = false"))
		prop = TASK_getProperty(pMIT)
		prop.visible = false
		TASK_setProperty(pMIT, prop)	
	end
	if count == 180 then
		syslog(string.format("TASK visible = true"))
		prop = TASK_getProperty(pMIT)
		prop.visible = true
		TASK_setProperty(pMIT, prop)	
	end
	
	if count == 200 then
		syslog(string.format("order"))
		prop = TASK_getProperty(pMIT)
		prop.order = 8000
		TASK_setProperty(pMIT, prop)	
	end
	if count == 220 then
		syslog(string.format("index"))
		prop = TASK_getProperty(pMIT)
		prop.index = 0
		TASK_setProperty(pMIT, prop)	
	end
	if count == 240 then
		syslog(string.format("idxmax"))
		prop = TASK_getProperty(pMIT)
		prop.idxmax = 4
		TASK_setProperty(pMIT, prop)	
	end
	
	if count >= 300 and count % 10 == 0 then
		prop = TASK_getProperty(pMIT)
		idx = prop.index
		idx = idx + 1
		if idx % 3 == 0 then 
			idx = 0
		end
		syslog(string.format("CMD UI_MULTIIMG_SET_INDEX = %i", idx))
		sysCommand(pMIT, UI_MULTIIMG_SET_INDEX, idx)
	end
end


function leave()
end
