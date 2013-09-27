function setup()
	pItem1 = UI_VariableItem(	nil,							-- arg[1]:		親となるUIタスクポインタ
								7000,							-- arg[2]:		表示プライオリティ
								0, 0,							-- arg[3,4]:	表示位置
								-1,-1,						-- arg[5,6]:	表示サイズ
								"asset://itemimage.png.imag"	-- arg[7]:		表示assetのパス
							)
							
	pItem2 = UI_VariableItem(	nil,							-- arg[1]:		親となるUIタスクポインタ
								7001,							-- arg[2]:		表示プライオリティ
								200,200,						-- arg[3,4]:	表示位置
								200,200,						-- arg[5,6]:	表示サイズ
								"asset://itemimage.png.imag"	-- arg[7]:		表示assetのパス
							)
							
	--[[
		UI_VariableItem just display like UI_SimpleItem.
		Except that it is possible to :
		- Modify the size of the image (perform stretch)
		- Apply a mask by doing texture composition.
		- Change the ressource at runtime.

		Note : size of -1,-1 will result in using original size without knowing the size
	]]
	
	bFlag = true
	
	count = 0
end

function execute(deltaT)
	count = count + 1
	if count == 40 then
		sysCommand(pItem1, UI_VARITEM_CHANGE_ASSET, "asset://itemimage2.png.imag") 
	end
	if count == 80 then
		sysCommand(pItem1, UI_VARITEM_SET_UV, 10,10,500,500) 
	end
	if count == 120 then
		sysCommand(pItem1, UI_VARITEM_RESET_UV) 
	end
	if count == 160 then
		sysCommand(pItem1, UI_VARITEM_SET_MASK, "asset://itemMask.png.imag")
	end
end

function leave()
end
