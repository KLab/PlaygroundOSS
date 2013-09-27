--[[
	TASK_Genericを使用してLuaでタスクを記述する例
]]

tblCHAR2 = {}

function initChar2(key, x, y, asset)
	local tbl = {}

	pGenTask = TASK_Generic("execute_char2", "die_char2", key)

	tbl.x = x
	tbl.y = y
	tbl.asset = asset
	-- CAN PASS pGenTask as parent, but pGenTask has not graphic node : nodes are attached to ROOT.
	tbl.image = UI_SimpleItem(pGenTask, 6000, x, y, asset)

	tblCHAR2[key] = tbl
end

function execute_char2(pTask, deltaT, key)
	prop = TASK_getProperty(tblCHAR2[key].image)
	prop.y = prop.y + 1		-- Char1 と違うのは、y方向動作だということ。
	TASK_setProperty(tblCHAR2[key].image, prop)
	if prop.y > 768 then
		-- Kill generic task in this sample
		TASK_kill(pTask)
		
		-- If we did not pass pGenTask as parent,
		-- we need to kill here, can NOT do it in die_char2.
		-- => Need to kill in execute.
		-- TASK_kill(tblCHAR2[key].image)
	end
end

function die_char2(pTask, key)
	-- NEVER kill in DIE : forbidden by engine, you will get an assert.
	-- TASK_kill(tblCHAR2[key].image)
	tblCHAR2[key] = nil
	syslog(string.format("kill char2[%s]", key))
end
