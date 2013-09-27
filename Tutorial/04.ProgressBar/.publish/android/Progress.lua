function setup()

	pProg = UI_ProgressBar(	nil,			-- 親UIタスクのポインタ。nilの場合は親の無い状態で生成されます。
							200,			-- 表示プライオリティ: 表示システム上のプライオリティ値
							80, 500,		-- 表示座標: 親UIタスクの位置を基準として、相対座標で与えます。
							400, 80,		-- 表示サイズ: 幅と高さ。表示素材のサイズです。0[%] 状態の画像と100[%]状態の画像は同じサイズである必要があります。
							"asset://prog_h_full.png.imag",	 -- 100[%]状態の画像asset名称
							"asset://prog_h_empty.png.imag", -- 0[%]状態の画像asset名称
							16,				-- 始点pixel位置: テクスチャ画像上において、実際に表示が変わるバーの始点となる座標 (※1)
							381,			-- 終点pixel位置: テクスチャ画像上において、実際に表示が変わるバーの終点となる座標 (※1)
							1000,			-- アニメーション時間 (※2)
							false			-- 縦方向フラグ: バーの成長方向が垂直方向であればtrue, 水平方向であれば false (※1)
							--"asset://barfilter.png.imag"
							)
--[[
	prop = TASK_getProperty(pProg)
	prop.filter_visible = true
	TASK_setProperty(pProg, prop)
	
	sysCommand(pProg, UI_PROGRESS_FILTER_ANIM, true, 0xff, 0xffffff, 0x80, 0xffffff, 100)
	]]
end

function execute(deltaT)
	prop = TASK_getProperty(pProg)
	prop.value = 1.0
	TASK_setProperty(pProg, prop)
end


function leave()
	pProg = TASK_kill(pProg)	-- 明示的な殺し方
end
