function setup()

	local x = 100
	local y = 100
	pSimpleItem = UI_SimpleItem(	nil,							-- arg[1]:		親となるUIタスクポインタ
									7000,							-- arg[2]:		表示プライオリティ
									x, y,							-- arg[3,4]:	表示位置
									"asset://itemimage.png.imag"	-- arg[5]:		表示assetのパス
								)
	--[[
		時限化するタスクを起動します。
		ここではUI_SimpleItem を用いていますが、他の種類のタスクでも構いません。
	]]

	pLifeCTRL = LIFECtrl(LIFECTRL_TIME, 2000)
	--[[
		LIFECTRL_TIME を第一引数に指定した場合、第二引数はミリ秒単位指定となり、
		実時間経過後に自殺するようになります。

		LIFECTRL_FRAME を指定すると、第二引数がフレーム数の意味となり、
		実時間を問わず指定フレーム数経過後に自殺します。
	]]

	sysCommand(pLifeCTRL, LIFECTRL_ADD_CHILD, pSimpleItem)
	--[[
		LIFECTRL_ADD_CHILD コマンドで、LIFECtrl の子タスクとして
		登録するタスクのポインタを指定します。

		この時点で両者は親子タスクとなるため、親タスクである LIFECtrl の破棄と
		同時に破棄対象となります。
	]]
	
	pLifeCtrl = nil
	pSimpleItem = nil
	--[[
		自動破棄の対象となったタスクのポインタは、
		解放済みアクセスを防ぐためnilを代入しておくことをお勧めします。
	]]
end


function execute(deltaT)
end


function leave()
end
