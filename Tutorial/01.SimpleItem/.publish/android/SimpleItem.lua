function setup()

	local x = 100
	local y = 100
	pSimpleItem = UI_SimpleItem(	nil,							-- arg[1]:		親となるUIタスクポインタ
									7000,							-- arg[2]:		表示プライオリティ
									x, y,							-- arg[3,4]:	表示位置
									"asset://itemimage.png.imag"	-- arg[5]:		表示assetのパス
								)
	--[[
		UI_SimpleItem は、指定されたassetを単純に指定された位置とプライオリティで表示/再生します。
		主な用途は単純な画像表示です。

		また、SWFなどの再生も可能です。
		複雑な制御を伴わない単純な再生であれば、UI_SWFPlayerよりもUI_SimpleItemのほうが軽量です。

		表示位置やスケーリング、表示RGBA値の設定を標準プロパティで行うことで、
		表示状態の変更が可能です。
	]]
	
	pCtrl = UI_Control(
							"onClick",
							"onDrag"
						)
	
	bFlag = true
	
	count = 0
end


function execute(deltaT)
	count = count + 1
	if count == 20 then
		prop = TASK_getProperty(pSimpleItem)
		prop.alpha = 128
		TASK_setProperty(pSimpleItem, prop)	
	end
	if count == 40 then
		prop = TASK_getProperty(pSimpleItem)
		prop.color = 0xFF00FF
		TASK_setProperty(pSimpleItem, prop)	
	end
	if count == 60 then
		prop = TASK_getProperty(pSimpleItem)
		prop.scaleX = 2.0
		TASK_setProperty(pSimpleItem, prop)	
	end
	if count == 80 then
		prop = TASK_getProperty(pSimpleItem)
		prop.scaleY = 2.0
		TASK_setProperty(pSimpleItem, prop)	
	end
	if count == 100 then
		prop = TASK_getProperty(pSimpleItem)
		prop.rot = 25.0
		TASK_setProperty(pSimpleItem, prop)	
	end
	if count == 120 then
		prop = TASK_getProperty(pSimpleItem)
		prop.x = 200
		TASK_setProperty(pSimpleItem, prop)	
	end
	if count == 140 then
		prop = TASK_getProperty(pSimpleItem)
		prop.y = 200
		TASK_setProperty(pSimpleItem, prop)	
	end
	if count == 160 then
		prop = TASK_getProperty(pSimpleItem)
		prop.visible = false
		TASK_setProperty(pSimpleItem, prop)	
	end
	if count == 180 then
		prop = TASK_getProperty(pSimpleItem)
		prop.visible = true
		prop.order = 8000
		TASK_setProperty(pSimpleItem, prop)	
	end
	if count == 200 then
		prop = TASK_getProperty(pSimpleItem)
		prop.asset = "Never do it"
		TASK_setProperty(pSimpleItem, prop)
	end
	
	
	if count == 400 then 
		syslog(string.format("ON_PINCH"))
		sysCommand(pCtrl, UI_CONTROL_ON_PINCH, "onPinch")
	end
	if count == 600 then 
		syslog(string.format("ON_DBLCLICK"))
		 sysCommand(pCtrl, UI_CONTROL_ON_DBLCLICK, "onDblClick")
	end
	if count == 800 then 
		syslog(string.format("ON_LONGTAP"))
		sysCommand(pCtrl, UI_CONTROL_ON_LONGTAP, "onLongTap")
	end
	if count == 900 then 
		syslog(string.format("SET_GROUP"))
		sysCommand(pCtrl, UI_CONTROL_SET_GROUP, "group-name")
	end
	if count == 1000 then 
		syslog(string.format("SET_MASK"))
		sysCommand(pCtrl, UI_CONTROL_SET_MASK, 0x09)
	end	
		
end


function leave()
end

function onClick(x,y)
	syslog(string.format("Click (%i,%i)",x,y))
end

function onDrag(mode,x,y,mvX,mvY)
	syslog(string.format("Drag - %i - (%i,%i) - mv : (%i,%i)",mode,x,y,mvX,mvY))
end

function onPinch( mode, pinch, rot )
	syslog(string.format("Pinch - pinch : %i - rot : %i",mode,pinch,rot))
end
 
function onDblClick( x, y )
	syslog(string.format("Double Click (%i,%i)",x,y))
end

function onLongTap( t, x, y )
	syslog(string.format("LongTap (%i,%i) - %i",x,y,t))
end