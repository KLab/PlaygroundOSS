function setup()

	pIT0 = UTIL_IntervalTimer	(
									0, 			--<timerID>
									"callback",--"<callback>" 
									100,		--<interval>
									true		--[ , <repeat> ]
								)
								
	pIT1 = UTIL_IntervalTimer	(
									1, 			--<timerID>
									"callback",--"<callback>" 
									50,			--<interval>
									false		--[ , <repeat> ]
								)

	count = 0
end


function execute(deltaT)
	count = count + 1
	if count == 200 then
		syslog(string.format("timer_id"))
		prop = TASK_getProperty(pIT0)
		prop.timer_id = 2
		TASK_setProperty(pIT0, prop)
	end
	if count == 300 then
		syslog(string.format("interval"))
		prop = TASK_getProperty(pIT0)
		prop.interval = 500
		TASK_setProperty(pIT0, prop)
	end
	if count == 400 then
		syslog(string.format("is_repeating = false"))
		prop = TASK_getProperty(pIT0)
		prop.is_repeating = false
		TASK_setProperty(pIT0, prop)
	end
end


function leave()

end

function callback(timerID)
	syslog(string.format("CALLBACK %i.", timerID))
end
