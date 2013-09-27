function setup()
	local x = 300
	local y = 300
	-- 
	pSWF = UI_SWFPlayer(nil, 7000, x, y, "asset://TestScale.flsh",nil,"flash_callback")
	--[[↑
		arg[6]には、arg[5]で指定された flash asset 内に含まれる movie clip の名称を与えますが、
		flash 全体を再生する場合は nil にします。このため、通常の利用では nil にすることが多くなります。
		
		arg[7]はflashアニメーションが終了した際に呼ばれるコールバック関数の名称です。
		
		UI_SWFPlayerは、起動直後デフォルトで再生状態になっています。
		再生をストップした状態で開始したい場合は、起動直後 UI_SWF_STOP コマンドを使用します。
	]]

	sysCommand(pSWF, UI_SWF_REACHFRAME, "lbl01", "flash_callback")
	sysCommand(pSWF, UI_SWF_REACHFRAME, "lbl02", "flash_callback")
	sysCommand(pSWF, UI_SWF_REACHFRAME, "lbl03", "flash_callback")
	
	--[[
		flashアニメーション中の特定フレームに到達したことを検知するコールバック関数を指定する場合、
		生成した UI_SWFPlayer タスクのポインタに対して UI_SWF_REACHFRAME コマンドを発行します。
		フレームにつけられたラベルと、コールバック関数の名称を引数として与えます。
		
		コールバック関数の引数は、アニメーション終了時のコールバックと同じであるため、
		同じ関数を指定することができます。
	]]

	time_ = 0
end

function execute(deltaT)
end

function leave()
end

--[[ コールバック関数の定義 ]]
function flash_callback(pSWF, label)
	--[[
		pSWFには、この関数を呼び出したタスクのポインタ、
		label には到達したフレームラベルが与えられます。
		アニメーション終了時の呼び出しでは、label の値が ""(空文字列)となります。

		また、呼び出したタスクのポインタが与えられるので、複数の UI_SWFPlayer から
		同じコールバックを呼ぶことが可能です。
	]]

	if label == "" then
		-- アニメーションが終了していたら、"frameLabel" に飛ぶ
		--[[
			flashアニメーションの再生を特定のフレームから行いたい場合、
			UI_SWF_GOTOFRAME コマンドを使用して再生を開始するフレームをラベルで指定します。
		]]
		syslog(string.format("[SWF]reach last frame."))
		sysCommand(pSWF, UI_SWF_GOTOFRAME, "frameLabel")
	else
		-- それ以外へのラベルに到達していたら、到達したラベルを表示する。
		syslog(string.format("[SWF]reach: <%s>", label))
	end
end

--
-- Sampe function, not used.
--
function swfSTOP(pSWF)
	sysCommand(pSWF, UI_SWF_STOP)
	--[[
		UI_SWFPlayerの再生を一時ストップします。本質的にはSTOPというよりPAUSEです。
	]]
end

function swfPLAY(pSWF)
	sysCommand(pSWF, UI_SWF_PLAY)
	--[[
		UI_SWF_STOP でストップ中の再生を再開します。
		再生状態で呼び出した場合は何もしません。
	]]
end
