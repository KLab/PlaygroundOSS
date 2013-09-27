function setup()

	local x = 100
	local y = 100
	local tblAREA = {
		x = 16,
		y = 20,
		width = 67,
		height = 60
	}
	pDRAG = UI_DragIcon(	nil,
							7000,
							x, y,
							tblAREA,
							"asset://dragicon.png.imag",
							"asset://dragmark.png.imag",
							10,
							0.5,
							30, 70,
							"dragIcon_dropCallback"
							)
	--[[
		asset://dragicon.png.imag	普段から配置しておくアイコン
		asset://dragmark.png.imag	ドラッグ位置について回る画像
		asset://putimg.png.imag		ドロップ時、その位置に配置される画像
	]]

	--[[ 配置済み画像をクリアできるボタンを配置する ]]
	UI_DbgLabel(nil, 7000, 800, 10, 0xff, 0xff0000, "fixed", 32, "[ Clear ]", 0, "clearPutImage")

	--[[ 配置する画像は、すべて pGRP の子タスクとして生成し、pGRP のkillと同時に死ぬようにする ]]
	pGRP = nil
	clearPutImage(nil, 0)
	
	count = 0
end


function execute(deltaT)
	count = count + 1
	--[[if count == 20 then
		syslog(string.format("TASK alpha"))
		prop = TASK_getProperty(pDRAG)
		prop.alpha = 128
		TASK_setProperty(pDRAG, prop)	
	end
	if count == 40 then
		syslog(string.format("TASK color"))
		prop = TASK_getProperty(pDRAG)
		prop.color = 0xFF00FF
		TASK_setProperty(pDRAG, prop)	
	end
	if count == 60 then
		syslog(string.format("TASK scalex"))
		prop = TASK_getProperty(pDRAG)
		prop.scaleX = 2.0
		TASK_setProperty(pDRAG, prop)	
	end
	if count == 80 then
		syslog(string.format("TASK scaley"))
		prop = TASK_getProperty(pDRAG)
		prop.scaleY = 2.0
		TASK_setProperty(pDRAG, prop)	
	end
	if count == 100 then
		syslog(string.format("TASK rot"))
		prop = TASK_getProperty(pDRAG)
		prop.rot = 25.0
		TASK_setProperty(pDRAG, prop)	
	end
	if count == 120 then
		syslog(string.format("TASK x"))
		prop = TASK_getProperty(pDRAG)
		prop.x = 200
		TASK_setProperty(pDRAG, prop)	
	end
	if count == 140 then
		syslog(string.format("TASK y"))
		prop = TASK_getProperty(pDRAG)
		prop.y = 200
		TASK_setProperty(pDRAG, prop)	
	end
	if count == 160 then
		syslog(string.format("TASK visible = false"))
		prop = TASK_getProperty(pDRAG)
		prop.visible = false
		TASK_setProperty(pDRAG, prop)	
	end
	if count == 180 then
		syslog(string.format("TASK visible = true"))
		prop = TASK_getProperty(pDRAG)
		prop.visible = true
		TASK_setProperty(pDRAG, prop)	
	end
	
	if count == 250 then
		syslog(string.format("order"))
		prop = TASK_getProperty(pDRAG)
		prop.order = 4000
		TASK_setProperty(pDRAG, prop)
	end
	if count == 300 then
		syslog(string.format("asset"))
		prop = TASK_getProperty(pDRAG)
		prop.asset = "asset://putimg.png.imag"
		TASK_setProperty(pDRAG, prop)
	end
	if count == 350 then
		syslog(string.format("drag asset"))
		prop = TASK_getProperty(pDRAG)
		prop.drag = "asset://putimg.png.imag"
		TASK_setProperty(pDRAG, prop)
	end
	if count == 400 then
		syslog(string.format("flags = F_DICON_BASEINVISIBLE"))
		prop = TASK_getProperty(pDRAG)
		prop.flags = F_DICON_BASEINVISIBLE
		TASK_setProperty(pDRAG, prop)
	end
	if count == 550 then
		syslog(string.format("flags = 0"))
		prop = TASK_getProperty(pDRAG)
		prop.flags = 0
		TASK_setProperty(pDRAG, prop)
	end
	if count == 600 then
		syslog(string.format("callback"))
		prop = TASK_getProperty(pDRAG)
		prop.callback = "dragIcon_dropCallback2"
		TASK_setProperty(pDRAG, prop)
	end
	if count == 650 then
		syslog(string.format("drag_scaleX"))
		prop = TASK_getProperty(pDRAG)
		prop.drag_scaleX = 2.0
		TASK_setProperty(pDRAG, prop)
	end
	if count == 750 then
		syslog(string.format("drag_scaleY"))
		prop = TASK_getProperty(pDRAG)
		prop.drag_scaleY = 2.0
		TASK_setProperty(pDRAG, prop)
	end
	
	if count == 750 then
		syslog(string.format("CMD UI_DRAGICON_ENABLE false"))
		sysCommand(pDRAG, UI_DRAGICON_ENABLE, false)
	end
	if count == 850 then
		syslog(string.format("CMD UI_DRAGICON_ENABLE true"))
		sysCommand(pDRAG, UI_DRAGICON_ENABLE, true)
	end
	]]
	if count == 200 then
		syslog(string.format("CMD UI_DRAGICON_DRAGAREA"))
		dropArea = {
			 x = 0,
			 y = 0,
			 width = 400,
			 height = 200
		   }
		sysCommand(pDRAG, UI_DRAGICON_DRAGAREA, dropArea)
	end

end


function leave()
end


function dragIcon_dropCallback(step, x, y)
	if step == DRAGICON_DRAG then
		-- ドラッグ中は、現在の座標をコンソールに出力する
		-- syslog(string.format("drag:( %d, %d )", x, y))
	elseif step == DRAGICON_RELEASE then
		-- ドロップされた位置に、配置画像で UI_SimpleItem を生成する。
		UI_SimpleItem(pGRP, 6000, x, y, "asset://putimg.png.imag")
	end
end

function dragIcon_dropCallback2(step, x, y)
	if step == DRAGICON_DRAG then
		-- ドラッグ中は、現在の座標をコンソールに出力する
		-- syslog(string.format("drag:( %d, %d )", x, y))
	elseif step == DRAGICON_RELEASE then
		-- ドロップされた位置に、配置画像で UI_SimpleItem を生成する。
		UI_SimpleItem(pGRP, 6000, x, y, "asset://dragmark.png.imag")
	end
end

-- 配置済みイメージをクリアするため、親タスクを殺して再生成する。
function clearPutImage(pTask, cmdID)
	pGRP = TASK_kill(pGRP)
	pGRP = UI_Group(nil, 6000, 0, 0)
end
