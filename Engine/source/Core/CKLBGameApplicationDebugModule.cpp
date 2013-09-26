/* 
   Copyright 2013 KLab Inc.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
#include "CKLBGameApplication.h"

#include "CKLBDrawTask.h"
#include "CKLBTexturePacker.h"
#include "CKLBAsset.h"
#include "CKLBDrawTask.h"
#include "CKLBLuaLibSOUND.h"

static void parseBuffer(char* command, char** args, int* argc) {
	char*	parse		= command;
	bool	emptySpace	= true;
	int		argRes		= 0;

	while (*parse != 0) {
		if (*parse <= 32) {
			// Invisible
			*parse = 0;
			emptySpace = true;
		} else {
			// Char
			if (emptySpace == true) {
				// Transition
				args[argRes++] = parse;
			}
			emptySpace = false;
		}
		parse++;
	}
	*argc = argRes;
}

bool CKLBGameApplication::executeCommand(const char* command) {
	char	commandL[1000];
	char*	commArgs[10];
	int		argCount;

	bool	result = false;
	// Copy string
	int l = strlen(command);
	memcpy(commandL, command, l+1);
	
	// Make sure previous stuff is cleaned.
	printf("\n");

	// Cut Buffer.
	parseBuffer(commandL, commArgs, &argCount);
	
	if (argCount >= 1) {
		if (strcmp("HELP", commArgs[0]) == 0) {
			printf("\n---- Debug Shell Help-----\n");
			printf("DUMP SCENE\n");
			printf("\tDump all the scene graph, including type, name, linked task\n\n");
			printf("DUMP PACKER [DETAIL]\n");
			printf("\tDump texture packer surfaces : position, size, state, buffer type\n\n");
			printf("DUMP ASSET\n");
			printf("\tDump the list of asset registered in the asset dictionnary. Asset created from dynamic Json are not listed (forms)\n\n");
			printf("DUMP RENDER [DETAIL]\n");
			printf("\tDump the list of render command : type, order, vertex/index count\n\n");
			printf("DUMP TASKS\n");
			printf("\tDump the list of tasks instances.\n");
			printf("LOG RENDER\n");
			printf("LOG SYSLOAD\n");
			printf("\tLog execution time of next sysload command\n\n");
			printf("DUMP SYSLOAD\n");
			printf("\tDump the execution time for the sysload command logged.\n\n");
			printf("HELP\n");
			printf("\tThis help.\n\n");

			printf("lt script\n");
			printf("\tToggle display execution time for the script section.(CB included ?)\n\n");

			printf("lt render\n");
			printf("\tToggle display execution time for scene graph update and rendering batch.\n\n");

			printf("lt frame\n");
			printf("\tToggle display execution time for the whole frame.\n\n");

			printf("Note : to disable 'lt' command disable if called again.\n\n");
			result = true;
		} else
		/* if (strcmp("g", commArgs[0]) == 0) {
			if (argCount == 2) {
				int l = strlen(commArgs[1]);
				char* pEnd = &((commArgs[1])[l]);
				long val =  strtol((const char*)commArgs[1],&pEnd,16);
				void* p = (void*)val;
				
				if (CKLBTaskMgr::getInstance().isExistTask((CKLBTask*)p)) {
					
				}
			}

			if (argCount == 3) {
			
			}
		} else */
		if (strcmp("STOP", commArgs[0]) == 0) {
			this->pauseGame(true);
			result = true;
		} else
		if (strcmp("RENDER", commArgs[0]) == 0) {
			if (argCount >= 2) {
				if (strcmp("NORMAL", commArgs[1]) == 0) {
					CKLBRenderingManager::getInstance().renderOverdraw(0);
				} else
				if (strcmp("OVERDRAW", commArgs[1]) == 0) {
					CKLBRenderingManager::getInstance().renderOverdraw(1);
				} else
				if (strcmp("BATCH", commArgs[1]) == 0) {
					CKLBRenderingManager::getInstance().renderOverdraw(2);
				}
				result = true;
			}
		} else
		if (strcmp("UNLOAD", commArgs[0])==0) {
			CKLBAssetManager::getInstance().unloadAsset();
			result = true;
		} else
		if (strcmp("RELOAD", commArgs[0])==0) {
			CKLBAssetManager::getInstance().restoreAsset();
			result = true;
		} else		if (strcmp("PLAY", commArgs[0]) == 0) {
			this->pauseGame(false);
			result = true;
		} else
		if (strcmp("DUMP", commArgs[0]) == 0) {
			if (argCount >= 2) {
				if (strcmp("SCENE", commArgs[1]) == 0) {
					CKLBDrawResource& res = CKLBDrawResource::getInstance();
					res.getRoot()->dump(0, 0xFFFFFFFF);
					result = true;
				} else
				if (strcmp("TASKS", commArgs[1]) == 0) {
					CKLBTaskMgr::getInstance().dump();
					result = true;
				} else
				if (strcmp("PACKER", commArgs[1]) == 0) {
					TexturePacker::getInstance().dump(argCount == 3);
					result = true;
				} else
				if (strcmp("ASSET", commArgs[1]) == 0) {
					CKLBAssetManager::getInstance().dump();
					CKLBLuaLibSOUND::s_dumpObjects();
					result = true;
				} else
				if (strcmp("RENDER", commArgs[1]) == 0) {
					if (argCount == 3) {
						CKLBRenderingManager::getInstance().dump(0xFFFFFFFF);
					}
					CKLBRenderingManager::getInstance().dumpMetrics();
					result = true;
				} else
				if (strcmp("DATASET", commArgs[1]) == 0) {
					CKLBDataHandler::dumpDataSet();
				} else
				if (strcmp("SYSLOAD", commArgs[1]) == 0) {
#ifdef INTERNAL_BENCH
					logTimeDump();
#else
					printf("Please recompile the engine with INTERNAL_BENCH defined. (CKLBLuaTask.h)\n");
#endif
				}
			}
		} else
		if (strcmp("LOG", commArgs[0]) == 0) {
			if (argCount >= 2) {
				if (strcmp("FRAME", commArgs[1]) == 0) {
					CKLBDrawResource& draw = CKLBDrawResource::getInstance();
					draw.setLog(!draw.allowLog());
					result = true;
				} else
				if (strcmp("SYSLOAD", commArgs[1]) == 0) {
#ifdef INTERNAL_BENCH
					logDo();
#else
					printf("Please recompile the engine with INTERNAL_BENCH defined. (CKLBLuaTask.h)\n");
#endif
					result = true;
				}
			}
		} else
		if (strcmp("ENABLE", commArgs[0]) == 0) {
			if (argCount >= 2) {
				if (strcmp("RENDER", commArgs[1]) == 0) {
					if (argCount >= 4) {
						u32 start = atoi(commArgs[2]);
						u32 end   = atoi(commArgs[3]);
						CKLBRenderingManager::getInstance().enableRange(start,end,true);
						result = true;
					}
				}
			}
		} else
		if (strcmp("DISABLE", commArgs[0]) == 0) {
			if (argCount >= 2) {
				if (strcmp("RENDER", commArgs[1]) == 0) {
					if (argCount >= 4) {
						u32 start = atoi(commArgs[2]);
						u32 end   = atoi(commArgs[3]);
						CKLBRenderingManager::getInstance().enableRange(start,end,false);
						result = true;
					}
				}
			}
		}
	}

	if (!result) {
		printf("[Shell] Invalid command : '%s', please try 'help'\n", command); 
	}
	return result;
}
