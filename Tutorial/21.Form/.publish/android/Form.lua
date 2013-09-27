function setup()
	local x = 0
	local y = 0
	local pForm = UI_Form(nil,	-- arg[1]:	親となるUIタスクのポインタ
		7000,		-- arg[2]:	基準表示プライオリティ
		x, y,		-- arg[3,4]:	表示位置
		"asset://form.json",	-- arg[5]:	composit jsonのパス
		false		-- arg[6]:	排他フラグ
	)
	--[[
		arg[6]:排他フラグ は、省略可能です。
		省略した場合は false と同じ挙動になります。
	]]
	
	TASK_StageOnly(pForm)
end

function execute(deltaT)
end

function leave()
	TASK_StageClear()
end


function onBattle()
	syslog('----- Form.onBattle() -----')
	sysLoad("asset://form1.lua")
end

function onClose()
	syslog('----- Form.onClose() -----')
	sysExit()
--	sysLoad("asset://form2.lua")
end

function onContinue()
	syslog('----- Form.onContinue() -----')
end

function chkCard0001_click()
	syslog('----- Form.chkCard0001_click() -----')
end

function chkCard0002_click()
	syslog('----- Form.chkCard0002_click() -----')
end

function chkCard0003_click()
	syslog('----- Form.chkCard0003_click() -----')
end

