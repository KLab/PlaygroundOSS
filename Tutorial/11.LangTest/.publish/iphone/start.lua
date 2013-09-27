function setup()
	-- Link DB Table with Language dictionnary.
	-- If not linked, work as it was before...
	LANG_useDB("asset://tableScheme.db_","lang_tbl","key","value","group_k")
	-- Preload a group of language info to avoid access.
	LANG_loadGroup("start")
	
	-- Lookup for a loaded key	syslog(LANG_getString("#key1"))
	
	-- Lookup for a unknown key and see if it looks up correctly into DB.
	syslog(LANG_getString("#key4"))
	
	-- Lookup for an unknown key and does not map at all.
	-- syslog(LANG_getString("#keyfail"))
	
end

function execute(deltaT)
end

function leave()

end
