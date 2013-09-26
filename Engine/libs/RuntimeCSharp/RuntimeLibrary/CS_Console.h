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
#ifndef _CS_Console_
#define _CS_Console_

#include "CS_Object.h"
#include "CS_String.h"

namespace System {

/*static*/ class Console {
public:
/*x*/	//static ConsoleColor BackgroundColor { get; set; }
/*x*/	//static u32 BufferHeight { get; set; }
/*x*/	//static u32 BufferWidth { get; set; }
/*x*/	//static bool CapsLock { get; }
/*x*/	//static u32 CursorLeft { get; set; }
/*x*/	//static u32 CursorSize { get; set; }
/*x*/	//static u32 CursorTop { get; set; }
/*x*/	//static bool CursorVisible { get; set; }
/*x*/	//static TextWriter Error { get; }
/*x*/	//static ConsoleColor ForegroundColor { get; set; }
/*x*/	//static TextReader In { get; }
/*x*/	//static Encoding InputEncoding { get; set; }
/*x*/	//static bool KeyAvailable { get; }
/*x*/	//static u32 LargestWindowHeight { get; }
/*x*/	//static u32 LargestWindowWidth { get; }
/*x*/	//static bool NumberLock { get; }
/*x*/	//static TextWriter Out { get; }
/*x*/	//static Encoding OutputEncoding { get; set; }
/*x*/	//static System::String* Title { get; set; }
/*x*/	//static bool TreatControlCAsInput { get; set; }
/*x*/	//static u32 WindowHeight { get; set; }
/*x*/	//static u32 WindowLeft { get; set; }
/*x*/	//static u32 WindowTop { get; set; }
/*x*/	//static u32 WindowWidth { get; set; }
/*x*/	//static event ConsoleCancelEventHandler CancelKeyPress;

/*x*/	//static void Beep();
/*x*/	//static void Beep(u32 frequency, u32 duration);
/*x*/	//static void Clear();
/*x*/	//static void MoveBufferArea(u32 sourceLeft, u32 sourceTop, u32 sourceWidth, u32 sourceHeight, u32 targetLeft, u32 targetTop);
/*x*/	//static void MoveBufferArea(u32 sourceLeft, u32 sourceTop, u32 sourceWidth, u32 sourceHeight, u32 targetLeft, u32 targetTop, uniChar sourceChar, ConsoleColor sourceForeColor, ConsoleColor sourceBackColor);
/*x*/	//static Stream OpenStandardError();
/*x*/	//static Stream OpenStandardError(u32 bufferSize);
/*x*/	//static Stream OpenStandardInput();
/*x*/	//static Stream OpenStandardInput(u32 bufferSize);
/*x*/	//static Stream OpenStandardOutput();
/*x*/	//static Stream OpenStandardOutput(u32 bufferSize);
/*x*/	//static u32 Read();
/*x*/	//static ConsoleKeyInfo ReadKey();
/*x*/	//static ConsoleKeyInfo ReadKey(bool intercept);
/*x*/	//static System::String* ReadLine();
/*x*/	//static void ResetColor();
/*x*/	//static void SetBufferSize(u32 width, u32 height);
/*x*/	//static void SetCursorPosition(u32 left, u32 top);
/*x*/	//static void SetError(TextWriter newError);
/*x*/	//static void SetIn(TextReader newIn);
/*x*/	//static void SetOut(TextWriter newOut);
/*x*/	//static void SetWindowPosition(u32 left, u32 top);
/*x*/	//static void SetWindowSize(u32 width, u32 height);
/*x*/	static void Write(bool value);
/*x*/	static void Write(uniChar value);
/*x*/	static void Write(System::Array<uniChar>* buffer);
/*x*/	//static void Write(decimal value);
/*x*/	static void Write(double value);
/*x*/	static void Write(float value);
/*x*/	static void Write(s32 value);
/*x*/	static void Write(s64 value);
/*x*/	static void Write(System::Object* value);
/*x*/	static void Write(System::String* value);
/*x*/	static void Write(u32 value);
/*x*/	static void Write(u64 value);
/*x*/	//static void Write(System::String* format, System::Object* arg0);
/*x*/	//static void Write(System::String* format, params object[] arg);
/*x*/	static void Write(System::Array<uniChar>* buffer, u32 index, u32 count);
/*x*/	//static void Write(System::String* format, System::Object* arg0, System::Object* arg1);
/*x*/	//static void Write(System::String* format, System::Object* arg0, System::Object* arg1, System::Object* arg2);
/*x*/	//static void Write(System::String* format, System::Object* arg0, System::Object* arg1, System::Object* arg2, System::Object* arg3);
/*x*/	static void WriteLine()											{ printf("\n");					}
/*x*/	inline static void WriteLine(bool value)						{ Write(value); printf("\n");	}
/*x*/	inline static void WriteLine(uniChar value)						{ Write(value); printf("\n");	}
/*x*/	inline static void WriteLine(System::Array<uniChar>* buffer)	{ Write(buffer); printf("\n");	}
/*x*/	//inline static void WriteLine(decimal value)					{ Write(value); printf("\n");	}
/*x*/	inline static void WriteLine(double value)						{ Write(value); printf("\n");	}
/*x*/	inline static void WriteLine(float value)						{ Write(value); printf("\n");	}
/*x*/	inline static void WriteLine(s32 value)							{ Write(value); printf("\n");	}
/*x*/	inline static void WriteLine(s64 value)							{ Write(value); printf("\n");	}
/*x*/	inline static void WriteLine(System::Object* value)				{ Write(value); printf("\n");	}
/*x*/	inline static void WriteLine(System::String* value)				{ Write(value); printf("\n");	}
/*x*/	inline static void WriteLine(u32 value)							{ Write(value); printf("\n");	}
/*x*/	inline static void WriteLine(u64 value)							{ Write(value); printf("\n");	}
/*x*/	//static void WriteLine(System::String* format, System::Object* arg0)					{ Write(value); printf("\n");	}
/*x*/	//static void WriteLine(System::String* format, params object[] arg)					{ Write(value); printf("\n");	}
/*x*/	inline static void WriteLine(System::Array<uniChar>* buffer, u32 index, u32 count)		{ Write(buffer, index, count); printf("\n");	}
/*x*/	//static void WriteLine(System::String* format, System::Object* arg0, System::Object* arg1);
/*x*/	//static void WriteLine(System::String* format, System::Object* arg0, System::Object* arg1, System::Object* arg2);
/*x*/	//static void WriteLine(System::String* format, System::Object* arg0, System::Object* arg1, System::Object* arg2, System::Object* arg3);

};

}

#endif // _CS_Console_
