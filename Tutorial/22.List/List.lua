--
function setup()

	pTask = UI_List(nil, 8000, 8200, 100, 100, 600, 400, 300, false, nil)
	sysCommand(pTask, UI_LIST_USE_SCROLLBAR,
		8200, true, 25, "asset://scrbar.png.imag", 25, nil, 0x80, 0xffffff, 0xff, 0xffffff, true, true)

	sysCommand(pTask, UI_LIST_SET_ITEMMODE, LIST_ITEM_DYNAMIC, "dynamic_callback")

	sysCommand(pTask, UI_LIST_SET_GROUP, "group")
	sysCommand(pTask, UI_LIST_SET_LOOPMODE, true)
	sysCommand(pTask, UI_LIST_SET_MARGIN, 0, 0)
	-- sysCommand(pTask, UI_LIST_SELECT_SCRMGR, "default")
	-- sysCommand(pTask, UI_LIST_SELECT_SCRMGR, "solid")
	sysCommand(pTask, UI_LIST_SELECT_SCRMGR, "page", 300, 10, 0)
--	sysCommand(pTask, UI_LIST_SCRMGR_CALLBACK, "listStop")
--	sysCommand(pTask, UI_LIST_SET_LIMITCLIP, true)
	--sysCommand(pTask, UI_LIST_SET_LIMITAREA, 600)

	prop = TASK_getProperty(pTask)
	prop.visible = true
	prop.default_scroll = true
	TASK_setProperty(pTask, prop)

	local form = CONV_JsonFile2Lua("asset://test_item.json")

		for i=1,40 do
			sysCommand(pTask, UI_LIST_ITEM_ADD, form, 300, i + 10000)
--			sysCommand(pTask, UI_LIST_UPDATE_NODE, i - 1, "label", FORM_LBL_SET_TEXT, string.format("item<%d>", i))
		end

	sysCommand(pTask, UI_LIST_SET_INITIAL, 0)
	-- pText = UI_TextInput(nil, false, 50, 50, 200, 50, "default text", "textCallback", 100)

	--pImage1 = UI_VariableItem(nil, 9000, 0, 0, 100, 100, "asset://test_tex.png.imag")
	--pImage2 = UI_VariableItem(nil, 9000, 100, 0, 100, 100, "asset://test_tex.png.imag")
	--sysCommand(pImage2, UI_VARITEM_SET_UV, 50, 50, 100, 50)
	tblAsset = {
		"asset://test_tex.png.imag",
		"asset://change_tex.png.imag"
	}
	
	count = 0
	preItem = 1
	flag = false
end

function execute(deltaT)

--[[
	count = count + deltaT
	if count >= 1000 then
		count = count - 1000
		preItem = 1 - preItem
		sysCommand(pImage1, UI_VARITEM_CHANGE_ASSET, tblAsset[preItem + 1])

	end
	]]
end

function leave()
	pText = TASK_kill(pText)
	pTask = TASK_kill(pTask)
end


function sub_execute(pGen, deltaT, key)
	count = count + 1
	syslog(string.format("count = %d", count))
	if count == 120 then
		for i=1,30 do
			sysCommand(pTask, UI_LIST_ITEM_ADD, "asset://test_item.json")
		end
		TASK_kill(pGen)
	end
end

function sub_die(pGen, key)
end

function callback_scrollOver(pList, mode, items, length, pos)
	syslog(string.format("mode[%d] items[%d]  length[%d]  pos[%d]", mode, items, length, pos))
end

function textCallback(pTB, str, id)
	syslog(string.format("<%d>[%s]", id, str))
end

function listStop(pList, pos)
	syslog(string.format("List STOP: %d", pos))
end

function movie_callback(pTask)

end

function dragCallback(pList, type, tap_x, tap_y, mv_x, mv_y)

	syslog("call lua callback.")
	if type == PAD_ITEM_TAP then
		
	elseif type == PAD_ITEM_DRAG then
	elseif type == PAD_ITEM_RELEASE then
	end
	
end

function dynamic_callback(pList, index, itemId)
	syslog(string.format("index[%d] itemId[%d]", index, itemId))
	sysCommand(pList, UI_LIST_UPDATE_NODE, index, "label", FORM_LBL_SET_TEXT, string.format("item<%d> id<%d>", index, itemId))

end
