function setup()
	pTPad = UI_TouchPad("callback_TP")

	pTask = UI_PieChart(nil, 7000, 480, 320, 200, 200,
						"asset://trash.png.imag", 0, 360, 300)
	sysCommand(pTask, UI_PIE_SET_VALUE, 0.0)
end


function execute(deltaT)
end


function leave()
end

function callback_TP(tbl)
	for idx,item in pairs(tbl) do
		if item.type == PAD_ITEM_TAP then
			if item.y < 200 then
				local start = 360 * item.x / 950
				if start > 360 then
					start = 360
				end
				sysCommand(pTask, UI_PIE_SET_START, start)
			elseif item.y < 400 then
				local v_end = 360 * item.x / 950
				if v_end > 360 then
					v_end = 360
				end
				sysCommand(pTask, UI_PIE_SET_END, v_end)
			else
				local value = item.x / 950
				sysCommand(pTask, UI_PIE_SET_VALUE, value)
				syslog(string.format("value: %f", value))
			end
		end
	end
end
