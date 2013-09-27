function setup()
  sysLoad("asset://VDoc.lua")
  pVDoc =  UI_VirtualDoc( nil, 10000, 
                                   0, 0,     -- x,y
                                   400, 400, -- doc size
                                   400, 400, -- view size
                                   1000, -- command最大数
                                   true  -- vertical
                                   )

  sysCommand(pVDoc, UI_VDOC_ALIGN, VD_ALIGN_CENTER, 200)
  sysCommand(pVDoc, UI_VDOC_FONT,  0, "Courrier New", 16)
  sysCommand(pVDoc, UI_VDOC_CLEAR, 0xff, 0x000000)
 
  vDocDraw = {
    { VD_DRAW_TEXT, 0, 0, "aaaaaaaaaa\nbbbbbbbbbbb\n", 0xff, 0xff0000, 0 },
    { VD_DRAW_TEXT, 0, 100, "cccccccccc\nddddddddddd\n", 0xff, 0xff0000, 0 },
  }
  sysCommand(pVDoc, UI_VDOC_DRAW, vDocDraw)
  sysCommand(pVDoc, UI_VDOC_VIEWPOS, 0, 0)
  
  TASK_StageOnly(pVDoc)
end

function execute(deltaT)
end


function leave()
	TASK_StageClear()
end

