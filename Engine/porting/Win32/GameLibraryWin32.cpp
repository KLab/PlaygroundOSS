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
// GameLibraryWin32.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "assert_klb.h"

#include "GameEngine.h"
#include "EngineStdReference.h"

#include <assert.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include "RenderingFramework.h"
#include <Windows.h>
#include <gl/GL.h>
#include "CPFInterface.h"
#include "CWin32Platform.h"
#include "CWin32PathConv.h"
#include "Win32FileLocation.h"

#include "CKLBLuaEnv.h"
#include "CKLBTouchPad.h"

// #pragma comment(lib, "GameLibraryWin32.lib")

//
//-----------------------------------------
//  Global Execution Context
//
#include "CKLBDebugger.h"
#include "CKLBRendering.h"
#include "CKLBAsset.h"

#include <conio.h>

//
//-----------------------------------------
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void EnableOpenGL (HWND hWnd, HDC * hDC, HGLRC * hRC);
void DisableOpenGL(HWND hWnd, HDC hDC, HGLRC hRC);

// Enable OpenGL
void EnableOpenGL(HWND hWnd, HDC * hDC, HGLRC * hRC)
{
	PIXELFORMATDESCRIPTOR pfd;
	int format;
	
	// get the device context (DC)
	*hDC = GetDC( hWnd );
	
	// set the pixel format for the DC
	ZeroMemory( &pfd, sizeof( pfd ) );
	pfd.nSize = sizeof( pfd );
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;
	format = ChoosePixelFormat( *hDC, &pfd );
	SetPixelFormat( *hDC, format, &pfd );
	
	// create and enable the render context (RC)
	*hRC = wglCreateContext( *hDC );
	wglMakeCurrent( *hDC, *hRC );
	
}

// Disable OpenGL
void DisableOpenGL(HWND hWnd, HDC hDC, HGLRC hRC)
{
	wglMakeCurrent( NULL, NULL );
	wglDeleteContext( hRC );
	ReleaseDC( hWnd, hDC );
}


const char* gsrc = NULL;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{                                                                       
	static int  rot         = 0;
	static int  mouse_stat  = 0;
	static int  lastX, lastY;
	static char commandBuff[1000];
	static int  commandLen      = 0;
	static int  g_bRender       = 0;
	static bool g_bRenderChange = true;

	switch (message)
    {
		case WM_CREATE:
			return 0;
		
		case WM_CLOSE:
			PostQuitMessage( 0 );
			return 0;
		
		case WM_COMMAND:
			{
				CWin32Widget::ControlCommand(hWnd, message, wParam, lParam);
			}
			break;
		case WM_DROPFILES:
			// DragQueryFile((HDROP)wParam, 0, &fileNameBuff[0], 512);			
			break;
        case WM_LBUTTONDOWN:
			if(mouse_stat) {	// ボタンを押したまま画面外に出た
				// 最後の座標を使って、無理やり RELEASEを送る
                // If going out of the screen with a pushed button
                // Force sending a RELEASE signal.
				CPFInterface::getInstance().client().inputPoint(0, IClientRequest::I_RELEASE,
						lastX, lastY);
				mouse_stat = 0;
			}
			CPFInterface::getInstance().client().inputPoint(0, IClientRequest::I_CLICK,
					GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			mouse_stat = 1;
			break;
		case WM_MOUSEMOVE:
			if (wParam & MK_LBUTTON) {
				lastX = GET_X_LPARAM(lParam);
				lastY = GET_Y_LPARAM(lParam);
				CPFInterface::getInstance().client().inputPoint(0, IClientRequest::I_DRAG,
						lastX, lastY);
			}
			break;
		case WM_LBUTTONUP:
			CPFInterface::getInstance().client().inputPoint(0, IClientRequest::I_RELEASE,
					GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			mouse_stat = 0;
			break;
		case WM_KEYDOWN:
			switch (wParam) {
			case VK_ESCAPE:
				PostQuitMessage(0);
				return 0;
			case VK_RETURN:
				if (commandLen != 0) {
					CPFInterface::getInstance().client().executeCommand(commandBuff);
					printf("\n");
					commandLen = 0;
					memset(commandBuff, 0, 1000);
				}
				break;
			case VK_LEFT:
				break;
			case VK_RIGHT:
				break;
			case VK_UP:
				break;
			case VK_DOWN:
				break;
			case VK_F1:	// F1
				{
					static const char* eventList = NULL;
					if (!eventList) {
						FILE* f = fopen("EventLog.txt","rb");
						fseek (f, 0, SEEK_END);   // non-portable
						int size=ftell (f);
						u8* buff  = new u8[size+1];
						memset(buff, 0, size+1);
						fseek (f, 0, SEEK_SET);
						fread (buff,1,size,f);
						fclose(f);
						eventList = (const char*)buff;
					}
					gsrc = eventList;
				}

				break;
			case VK_F9:
				if (g_bRenderChange) {
					g_bRender++;
					switch (g_bRender % 3) {
					case 0:			CPFInterface::getInstance().client().executeCommand("RENDER NORMAL"); break;
					case 1:			CPFInterface::getInstance().client().executeCommand("RENDER OVERDRAW"); break;
					case 2:			CPFInterface::getInstance().client().executeCommand("RENDER BATCH"); break;
					}
				}
				break;
			case VK_F2:
				{
					static bool gPlay = true;
					gPlay = !gPlay;
					if (gPlay) {
						CPFInterface::getInstance().client().executeCommand("PLAY");
					} else {
						CPFInterface::getInstance().client().executeCommand("STOP");
					}
				}
				break;
			case VK_F3:
				{
					CPFInterface::getInstance().client().executeCommand("UNLOAD");
				}
				break;
			case VK_F4:
				{
					CPFInterface::getInstance().client().executeCommand("RELOAD");
				}
				break;
			case VK_F8:
				{
					CPFInterface::getInstance().client().inputDeviceKey(IClientRequest::KEY_BACK, IClientRequest::KEYEVENT_CLICK);
					break;
				}
			default:
				if (wParam >=32 && wParam <= 127) {
					commandBuff[commandLen++] = wParam;
					printf("\r%s",commandBuff);
				} else {
					if (wParam == 8) {
						commandBuff[--commandLen] = 0;
						printf("\r%s                                                            ",commandBuff);
					}
				}
			}

			break;
        case WM_DESTROY:
            PostQuitMessage(0);                                             
            break;

        default:                                                            
            return DefWindowProc(hWnd, message, wParam, lParam);            
    }                                                                   
    return 0;                                                           
}    

void sendEvents() {
	if (gsrc) {
		int c = 0;
		bool exit = false;
		const char* src = gsrc;
		while (!exit && (*src != 0)) {
			int items = sscanf(src,"Event%c", &c);
			if (items == 1) {
				src += 6;
				switch (c) {
				case 'S':
					// Start
					exit = true;	// Point to the next frame.
					break;
				case 'E':
					// End
					break;
				case 'F':
					exit = true;
					break;
				case 'P':
					// Process
					break;
				case '0':
					{
						src++;	// skip :
						CKLBTouchPadQueue& queue = CKLBTouchPadQueue::getInstance();
						int id;
						int type;
						int x;
						int y;
						items = sscanf(src,"%i,%i,%i,%i", &id,&type,&x,&y);
						queue.addQueue(id,(IClientRequest::INPUT_TYPE)type,x,y);
					}
					break;
				case '1':
					// Push while processing, should never happen !
					klb_assertAlways("Should never happend");
					break;
				}
			}

			// Reach until EOL
			while ((*src != 0) && (*src != 0xA) && (*src != 0xD)) {
				src++;
			}

			// Skip EOL
			while ((*src == 0xA) || (*src == 0xD)) {
				src++;
			}
		}

		if (*src == 0) {
			gsrc = NULL; 
		} else {
			gsrc = src;
		}
	}
}

char g_basePath[MAX_PATH];
char g_fileName[MAX_PATH];
static char* g_pathExtern;
static char* g_pathInstall;


char* convertPath(const char* input) {
	int len = strlen(input);
	bool addEnd = false;
	if ((input[len-1] != '\\') && (input[len-1] != '/')) {
		addEnd = true;
	}

	char* buffDest = (char*)malloc(len + 1 + (addEnd ? 1 : 0));
	memcpy(buffDest, input, len);
	for (int n=0; n < len; n++) {
		if (buffDest[n] == '\\') {
			buffDest[n] = '/';
		}
	}
	if (addEnd) {
		buffDest[len] = '/';
		len++;
	}
	buffDest[len] = 0;
	return buffDest;
}

#ifdef _WIN32_WCE
int WINAPI WinMain( HINSTANCE,
                    HINSTANCE,
                    LPTSTR,
                    int)
#else
int GameEngineMain(int argc, _TCHAR* argv[])
// int _main (int argc, const char * const* argv)
#endif
{
	bool bStdModuleExist = EngineStdReference();
	klb_assert(bStdModuleExist, "The links of a system are insufficient.");

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("GLEW Test");

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
	  /* Problem: glewInit failed, something is seriously wrong. */
	  fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

#define HEIGHT	(768)
#define WIDTH	(1024)
#define POS_X	(10)
#define POS_Y	(10)
//#define HEIGHT	(800)
//#define WIDTH	(400)
	int scrW	= WIDTH;
	int scrH	= HEIGHT;
	
	int fixedDelta = 0;

	*g_basePath = 0;
	*g_fileName = 0;
	g_pathExtern	= PATH_EXTERN;
	g_pathInstall	= PATH_INSTALL;

	g_fileName[0] = 0;

	bool hasDefaultFont = true;
	bool hasDefaultDB   = false;

	if (argc > 1) {
		int parse	= 1;
		int max		= argc;
		while (parse < max) {
			if(*argv[parse] == '-') {
				if (strcmp("-w",argv[parse]) == 0) {
					sscanf_s(argv[parse+1],"%i",&scrW);
				}

				if (strcmp("-h",argv[parse]) == 0) {
					sscanf_s(argv[parse+1],"%i",&scrH);
				}

				if (strcmp("-i",argv[parse]) == 0) {
					g_pathInstall = convertPath(argv[parse+1]);
				}

				if (strcmp("-e",argv[parse]) == 0) {
					g_pathExtern = convertPath(argv[parse+1]);
				}

				if (strcmp("-t",argv[parse]) == 0) {
					fixedDelta = atoi(argv[parse+1]);
				}

				if (strcmp("-enc", argv[parse]) == 0) {
					bool encrypt = false;
					if (stricmp(argv[parse+1],"true") == 0) {
						encrypt = true;
					}

					if (stricmp(argv[parse+1],"1") == 0) {
						encrypt = true;
					}

					CWin32Platform::setEncrypt(encrypt);
				}

				if (strcmp("-no", argv[parse]) == 0) {
					if (strcmp("defaultfont", argv[parse+1]) == 0) {
						hasDefaultFont = false;
					}
				}

				parse += 2;
			} else {
				// Specify the boot file
				const char* file = argv[parse];
				int lenf = strlen(file);
				
				memcpy(g_fileName, file, lenf);
				g_fileName[lenf] = 0;

				// ファイル名そのものは start.lua に相当する起動ファイルとする。
                // File name of the file used as a start.lua
				parse++;
			}
		}
	}

	CWin32PathConv& pathconv = CWin32PathConv::getInstance();
	pathconv.setPath(g_pathInstall, g_pathExtern);

	WNDCLASS wc;
	HWND hwnd;
	HDC hDC;
	HGLRC hRC;
	HINSTANCE hInstance = GetModuleHandle(NULL);

	// register window class
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon( NULL, IDI_APPLICATION );
	wc.hCursor = LoadCursor( NULL, IDC_ARROW );
	wc.hbrBackground = (HBRUSH)GetStockObject( BLACK_BRUSH );
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "GameEngineGL";
	RegisterClass( &wc );
	
	// create main window
	hwnd = CreateWindow(
		"GameEngineGL", "Playground", 
		WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE,
		0, 0, 256, 256,
		NULL, NULL, hInstance, NULL );

/*		"EngineGL", NULL,
		WS_THICKFRAME|WS_DISABLED,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, 
		hInstance, 
		NULL
	);*/
	
	if (!hwnd)
		return -1;

	// enable OpenGL for the window
	EnableOpenGL( hwnd, &hDC, &hRC );

	// COM Initialization
	CoInitialize(NULL);

	EnableWindow(hwnd, TRUE);

	DragAcceptFiles(hwnd, true);

	RECT area;
	area.left = 0;
	area.top = 0;
#ifdef _WIN32_WCE
	area.right = GetSystemMetrics(SM_CXSCREEN);
	area.bottom = GetSystemMetrics(SM_CYSCREEN);

	SetWindowLong(hwnd, GWL_STYLE, WS_POPUP);

	SetWindowPos(hwnd, HWND_TOPMOST,
					area.left, area.top,
					area.right, area.bottom,
					SWP_FRAMECHANGED);
#else
	// Window border hard coded
	//area.right = scrW + 8;
	//area.bottom = scrH + 27;
	////area.right = GetSystemMetrics(SM_CXSCREEN);
	////area.bottom = GetSystemMetrics(SM_CYSCREEN);
	int addW = GetSystemMetrics(SM_CXSIZEFRAME) * 2;
	int addH = GetSystemMetrics(SM_CYSIZEFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION);
	area.right = scrW + addW;
	area.bottom = scrH + addH;
	

	/*
	AdjustWindowRect(
		&area,
		WS_SYSMENU|WS_THICKFRAME|WS_DISABLED,
		false
	);*/

	SetWindowPos(hwnd, HWND_TOP,
					area.left, area.top,
					area.right, area.bottom,
					SWP_NOMOVE);
#endif

	/* set as foreground window to give this app focus in case it doesn't have it */
	SetForegroundWindow(hwnd);
	ShowWindow(hwnd, SW_SHOWNORMAL);

	glClearColor(1.0f, 0.7f, 0.2039f, 0.0f);
	glDisable( GL_CULL_FACE );

	//

	// testCodeInit();

	CPFInterface& pfif = CPFInterface::getInstance();
	CWin32Platform * pPlatform = new CWin32Platform(hwnd);

	if (!hasDefaultFont) {
		pPlatform->setNoDefaultFont();
	}

	pfif.setPlatformRequest(pPlatform);
	GameSetup();	// client side setup

	// Can only access client AFTER GameSetup.
	pfif.client().setInitParam((hasDefaultDB   ? IClientRequest::ENGINE_USE_DEFAULTDB   : 0)
							|  (hasDefaultFont ? IClientRequest::ENGINE_USE_DEFAULTFONT : 0), NULL); 

	// sound initialize
	SoundSystemInitFor_Win32();
	CWin32AudioMgr::getInstance().init(hwnd);

	// set screen size
	pfif.client().setScreenInfo(false, scrW, scrH);
	// boot path
	if (strlen(g_fileName)) {
		pfif.client().setFilePath(g_fileName);
	} else {
		pfif.client().setFilePath(NULL);
	}
	if (!pfif.client().initGame()) {
		klb_assertAlways("Could not initialize game, most likely memory error");
	} else {
		static DWORD lastTime = GetTickCount();

		// Main message loop:
		bool quit = false;
		s32 frameTime = pfif.client().getFrameTime();
		IClientRequest& pClient = pfif.client();

		while (!quit)
		{
			/* relay message queue messages to windowproc's */
			MSG msg;
			while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);

				if (msg.message == WM_QUIT)
				{
					quit = true;
					break;
				}

				DispatchMessage(&msg);
			}

			if (!quit) {
				// This is not the safest or best way to handle timing, but this code
				// is only added to make the triangle rotate at a basically constant
				// rate, independent of the target (Win32) platform
				DWORD newTime   = GetTickCount();
				DWORD delta     = newTime - lastTime;

				// Handle rollover
				if (newTime < lastTime) {
					delta = 0;
				} else {
					if (delta > (DWORD)frameTime) {
						sendEvents();

						lastTime = newTime;
						//dglClear(GL_COLOR_BUFFER_BIT);
	
						//
						// Rendering complete.
						//		
						//testCodeLoop(delta);
						pClient.frameFlip(fixedDelta ? fixedDelta : delta);

						// pfIF.platform().flipFrame();
						SwapBuffers( hDC );
					}
                    // コントロール(ex. TextBox)が作られている場合、その再描画を行う
					// If a Control (ex TextBox) is done, redraw them.
					CWin32Widget::ReDrawControls();
				}
			}
			Sleep(1);
		}
	}

	pfif.client().finishGame();

	SoundSystemExitFor_Win32();

	delete pPlatform;

	// shutdown OpenGL
	DisableOpenGL( hwnd, hDC, hRC );

	CWin32AudioMgr::getInstance().release();

	// End of COM
	CoUninitialize();

	if(DestroyWindow (hwnd)) {
		printf("DestroyWindow SUCCESS\n");
    }
	return 0;
}
