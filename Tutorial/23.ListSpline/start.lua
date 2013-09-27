function setup()
        local x = 0
        local y = 0
        local pForm = UI_Form(nil, 0, x, y, "asset://list.json")
	
	sysCommand(pForm, UI_FORM_ANIM_ENTER)
	
	local pList = sysCommand(pForm, UI_FORM_UPDATE_NODE, "task_list1", FORM_NODE_TASK);
	for i = 1, 50 do
		sysCommand(pList, UI_LIST_ITEM_ADD, "asset://ui_item" .. math.random(1,2) .. ".json")
	end
end

function execute(deltaT)
end

function callback(pList, type, tapX, tapY, moveX, moveY)
	local pos = sysCommand(pList, UI_LIST_GET_POSITION)
	local newPos = sysCommand(pList, UI_LIST_SET_POSITION, pos - moveX)
end
