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
#ifndef _FRAMEWORK_H
#define _FRAMEWORK_H

#include "RuntimeLibrary/CS_Array.h"
#include "RuntimeLibrary/CS_Console.h"
#include "RuntimeLibrary/CS_Marshal.h"
#include "RuntimeLibrary/CS_Memory.h"
#include "RuntimeLibrary/CS_Object.h"
#include "RuntimeLibrary/CS_String.h"
#include "RuntimeLibrary/CS_System.h"
#include "RuntimeLibrary/Collections/Collections.h"
#include "RuntimeLibrary/Collections/Generic/CS_Dictionary.h"
#include "RuntimeLibrary/Collections/Generic/CS_List.h"
#include "RuntimeLibrary/Collections/Generic/Generic.h"
#include "RuntimeLibrary/InternalUtils.h"
#include "RuntimeLibrary/MarshallingUtils.h"
#include "ExportListC_Likefunction.h"

/* UI_WebView */
static const uniChar _$_cteStr111[] = {85,73,95,87,101,98,86,105,101,119};
static System::String* _$_cteStr111Obj;

/* Please use the draw functions in startDrawList()/endDrawList() blocks */
static const uniChar _$_cteStr110[] = {80,108,101,97,115,101,32,117,115,101,32,116,104,101,32,100,114,97,119,32,102,117,110,99,116,105,111,110,115,32,105,110,32,115,116,97,114,116,68,114,97,119,76,105,115,116,40,41,47,101,110,100,68,114,97,119,76,105,115,116,40,41,32,98,108,111,99,107,115};
static System::String* _$_cteStr110Obj;

/* UI_VirtualDoc */
static const uniChar _$_cteStr109[] = {85,73,95,86,105,114,116,117,97,108,68,111,99};
static System::String* _$_cteStr109Obj;

/* UI_VariableItem */
static const uniChar _$_cteStr108[] = {85,73,95,86,97,114,105,97,98,108,101,73,116,101,109};
static System::String* _$_cteStr108Obj;

/* UI_TouchPad */
static const uniChar _$_cteStr107[] = {85,73,95,84,111,117,99,104,80,97,100};
static System::String* _$_cteStr107Obj;

/* UI_TextInput */
static const uniChar _$_cteStr106[] = {85,73,95,84,101,120,116,73,110,112,117,116};
static System::String* _$_cteStr106Obj;

/* The value of a spline point cannot be greater than 32767 */
static const uniChar _$_cteStr105[] = {84,104,101,32,118,97,108,117,101,32,111,102,32,97,32,115,112,108,105,110,101,32,112,111,105,110,116,32,99,97,110,110,111,116,32,98,101,32,103,114,101,97,116,101,114,32,116,104,97,110,32,51,50,55,54,55};
static System::String* _$_cteStr105Obj;

/* UI_SWFPlayer */
static const uniChar _$_cteStr104[] = {85,73,95,83,87,70,80,108,97,121,101,114};
static System::String* _$_cteStr104Obj;

/* UI_SimpleItem */
static const uniChar _$_cteStr103[] = {85,73,95,83,105,109,112,108,101,73,116,101,109};
static System::String* _$_cteStr103Obj;

/* UI_ScrollBar */
static const uniChar _$_cteStr102[] = {85,73,95,83,99,114,111,108,108,66,97,114};
static System::String* _$_cteStr102Obj;

/* UI_Score */
static const uniChar _$_cteStr101[] = {85,73,95,83,99,111,114,101};
static System::String* _$_cteStr101Obj;

/* UI_Scale9 */
static const uniChar _$_cteStr100[] = {85,73,95,83,99,97,108,101,57};
static System::String* _$_cteStr100Obj;

/* UI_RubberBand */
static const uniChar _$_cteStr99[] = {85,73,95,82,117,98,98,101,114,66,97,110,100};
static System::String* _$_cteStr99Obj;

/* UI_ProgressBar */
static const uniChar _$_cteStr98[] = {85,73,95,80,114,111,103,114,101,115,115,66,97,114};
static System::String* _$_cteStr98Obj;

/* PointCount must be strictly positive */
static const uniChar _$_cteStr97[] = {80,111,105,110,116,67,111,117,110,116,32,109,117,115,116,32,98,101,32,115,116,114,105,99,116,108,121,32,112,111,115,105,116,105,118,101};
static System::String* _$_cteStr97Obj;

/* UI_Polyline */
static const uniChar _$_cteStr96[] = {85,73,95,80,111,108,121,108,105,110,101};
static System::String* _$_cteStr96Obj;

/* UI_PieChart */
static const uniChar _$_cteStr95[] = {85,73,95,80,105,101,67,104,97,114,116};
static System::String* _$_cteStr95Obj;

/* pArrayAsset and pArrayIndexes must have the same length. */
static const uniChar _$_cteStr94[] = {112,65,114,114,97,121,65,115,115,101,116,32,97,110,100,32,112,65,114,114,97,121,73,110,100,101,120,101,115,32,109,117,115,116,32,104,97,118,101,32,116,104,101,32,115,97,109,101,32,108,101,110,103,116,104,46};
static System::String* _$_cteStr94Obj;

/* ArrayAsset and ArrayIndexes must have the same size. */
static const uniChar _$_cteStr93[] = {65,114,114,97,121,65,115,115,101,116,32,97,110,100,32,65,114,114,97,121,73,110,100,101,120,101,115,32,109,117,115,116,32,104,97,118,101,32,116,104,101,32,115,97,109,101,32,115,105,122,101,46};
static System::String* _$_cteStr93Obj;

/* UI_MultiImgItem */
static const uniChar _$_cteStr92[] = {85,73,95,77,117,108,116,105,73,109,103,73,116,101,109};
static System::String* _$_cteStr92Obj;

/* UI_MoviePlayer */
static const uniChar _$_cteStr91[] = {85,73,95,77,111,118,105,101,80,108,97,121,101,114};
static System::String* _$_cteStr91Obj;

/* Not implemented in C++ yet. */
static const uniChar _$_cteStr90[] = {78,111,116,32,105,109,112,108,101,109,101,110,116,101,100,32,105,110,32,67,43,43,32,121,101,116,46};
static System::String* _$_cteStr90Obj;

/* scrollbar */
static const uniChar _$_cteStr89[] = {115,99,114,111,108,108,98,97,114};
static System::String* _$_cteStr89Obj;

/* dynamic */
static const uniChar _$_cteStr88[] = {100,121,110,97,109,105,99};
static System::String* _$_cteStr88Obj;

/* drag */
static const uniChar _$_cteStr87[] = {100,114,97,103};
static System::String* _$_cteStr87Obj;

/* limit */
static const uniChar _$_cteStr86[] = {108,105,109,105,116};
static System::String* _$_cteStr86Obj;

/* UI_List */
static const uniChar _$_cteStr85[] = {85,73,95,76,105,115,116};
static System::String* _$_cteStr85Obj;

/* YOLO */
static const uniChar _$_cteStr84[] = {89,79,76,79};
static System::String* _$_cteStr84Obj;

/* UI_Label */
static const uniChar _$_cteStr83[] = {85,73,95,76,97,98,101,108};
static System::String* _$_cteStr83Obj;

/* UI_Group */
static const uniChar _$_cteStr82[] = {85,73,95,71,114,111,117,112};
static System::String* _$_cteStr82Obj;

/* UV must be a float[8] array. */
static const uniChar _$_cteStr81[] = {85,86,32,109,117,115,116,32,98,101,32,97,32,102,108,111,97,116,91,56,93,32,97,114,114,97,121,46};
static System::String* _$_cteStr81Obj;

/* idx must be between 0 and 7. */
static const uniChar _$_cteStr80[] = {105,100,120,32,109,117,115,116,32,98,101,32,98,101,116,119,101,101,110,32,48,32,97,110,100,32,55,46};
static System::String* _$_cteStr80Obj;

/* Colors must be a uint[4] array. */
static const uniChar _$_cteStr79[] = {67,111,108,111,114,115,32,109,117,115,116,32,98,101,32,97,32,117,105,110,116,91,52,93,32,97,114,114,97,121,46};
static System::String* _$_cteStr79Obj;

/* Vertices must be a float[8] array. */
static const uniChar _$_cteStr78[] = {86,101,114,116,105,99,101,115,32,109,117,115,116,32,98,101,32,97,32,102,108,111,97,116,91,56,93,32,97,114,114,97,121,46};
static System::String* _$_cteStr78Obj;

/* UI_FreeVertItem */
static const uniChar _$_cteStr77[] = {85,73,95,70,114,101,101,86,101,114,116,73,116,101,109};
static System::String* _$_cteStr77Obj;

/* anim */
static const uniChar _$_cteStr76[] = {97,110,105,109};
static System::String* _$_cteStr76Obj;

/* selectable */
static const uniChar _$_cteStr75[] = {115,101,108,101,99,116,97,98,108,101};
static System::String* _$_cteStr75Obj;

/* UI_Form */
static const uniChar _$_cteStr74[] = {85,73,95,70,111,114,109};
static System::String* _$_cteStr74Obj;

/* UI_DragIcon */
static const uniChar _$_cteStr73[] = {85,73,95,68,114,97,103,73,99,111,110};
static System::String* _$_cteStr73Obj;

/* UI_DbgLabel */
static const uniChar _$_cteStr72[] = {85,73,95,68,98,103,76,97,98,101,108};
static System::String* _$_cteStr72Obj;

/* onLongtap */
static const uniChar _$_cteStr71[] = {111,110,76,111,110,103,116,97,112};
static System::String* _$_cteStr71Obj;

/* onDblClick */
static const uniChar _$_cteStr70[] = {111,110,68,98,108,67,108,105,99,107};
static System::String* _$_cteStr70Obj;

/* onClick */
static const uniChar _$_cteStr69[] = {111,110,67,108,105,99,107};
static System::String* _$_cteStr69Obj;

/* onPinch */
static const uniChar _$_cteStr68[] = {111,110,80,105,110,99,104};
static System::String* _$_cteStr68Obj;

/* onDrag */
static const uniChar _$_cteStr67[] = {111,110,68,114,97,103};
static System::String* _$_cteStr67Obj;

/* UI_Control */
static const uniChar _$_cteStr66[] = {85,73,95,67,111,110,116,114,111,108};
static System::String* _$_cteStr66Obj;

/* UI_Clip */
static const uniChar _$_cteStr65[] = {85,73,95,67,108,105,112};
static System::String* _$_cteStr65Obj;

/* UI_Canvas */
static const uniChar _$_cteStr64[] = {85,73,95,67,97,110,118,97,115};
static System::String* _$_cteStr64Obj;

/* STORE_Service */
static const uniChar _$_cteStr63[] = {83,84,79,82,69,95,83,101,114,118,105,99,101};
static System::String* _$_cteStr63Obj;

/* /api */
static const uniChar _$_cteStr62[] = {47,97,112,105};
static System::String* _$_cteStr62Obj;

/* versionUp */
static const uniChar _$_cteStr61[] = {118,101,114,115,105,111,110,85,112};
static System::String* _$_cteStr61Obj;

/* 840 */
static const uniChar _$_cteStr60[] = {56,52,48};
static System::String* _$_cteStr60Obj;

/* HTTP_API */
static const uniChar _$_cteStr59[] = {72,84,84,80,95,65,80,73};
static System::String* _$_cteStr59Obj;

/* UTIL_IntervalTimer */
static const uniChar _$_cteStr58[] = {85,84,73,76,95,73,110,116,101,114,118,97,108,84,105,109,101,114};
static System::String* _$_cteStr58Obj;

/* Unvalid delegate name */
static const uniChar _$_cteStr57[] = {85,110,118,97,108,105,100,32,100,101,108,101,103,97,116,101,32,110,97,109,101};
static System::String* _$_cteStr57Obj;

/* die */
static const uniChar _$_cteStr56[] = {100,105,101};
static System::String* _$_cteStr56Obj;

/* execute */
static const uniChar _$_cteStr55[] = {101,120,101,99,117,116,101};
static System::String* _$_cteStr55Obj;

/* TASK_Generic */
static const uniChar _$_cteStr54[] = {84,65,83,75,95,71,101,110,101,114,105,99};
static System::String* _$_cteStr54Obj;

/* Delegate NULL for this callback : Virtual function in subclass not implemented or delegate is null */
static const uniChar _$_cteStr53[] = {68,101,108,101,103,97,116,101,32,78,85,76,76,32,102,111,114,32,116,104,105,115,32,99,97,108,108,98,97,99,107,32,58,32,86,105,114,116,117,97,108,32,102,117,110,99,116,105,111,110,32,105,110,32,115,117,98,99,108,97,115,115,32,110,111,116,32,105,109,112,108,101,109,101,110,116,101,100,32,111,114,32,100,101,108,101,103,97,116,101,32,105,115,32,110,117,108,108};
static System::String* _$_cteStr53Obj;

/* UTIL_AsyncLoader */
static const uniChar _$_cteStr52[] = {85,84,73,76,95,65,115,121,110,99,76,111,97,100,101,114};
static System::String* _$_cteStr52Obj;

/* LibSound */
static const uniChar _$_cteStr51[] = {76,105,98,83,111,117,110,100};
static System::String* _$_cteStr51Obj;

/* Length must be 16. */
static const uniChar _$_cteStr50[] = {76,101,110,103,116,104,32,109,117,115,116,32,98,101,32,49,54,46};
static System::String* _$_cteStr50Obj;

/* LibFont */
static const uniChar _$_cteStr49[] = {76,105,98,70,111,110,116};
static System::String* _$_cteStr49Obj;

/* There is no Menu building. Please use startMenu before. */
static const uniChar _$_cteStr48[] = {84,104,101,114,101,32,105,115,32,110,111,32,77,101,110,117,32,98,117,105,108,100,105,110,103,46,32,80,108,101,97,115,101,32,117,115,101,32,115,116,97,114,116,77,101,110,117,32,98,101,102,111,114,101,46};
static System::String* _$_cteStr48Obj;

/* A Menu is already being built at the moment. */
static const uniChar _$_cteStr47[] = {65,32,77,101,110,117,32,105,115,32,97,108,114,101,97,100,121,32,98,101,105,110,103,32,98,117,105,108,116,32,97,116,32,116,104,101,32,109,111,109,101,110,116,46};
static System::String* _$_cteStr47Obj;

/* LibDB */
static const uniChar _$_cteStr46[] = {76,105,98,68,66};
static System::String* _$_cteStr46Obj;

/* LibDATA */
static const uniChar _$_cteStr45[] = {76,105,98,68,65,84,65};
static System::String* _$_cteStr45Obj;

/* LibBIN */
static const uniChar _$_cteStr44[] = {76,105,98,66,73,78};
static System::String* _$_cteStr44Obj;

/* ] */
static const uniChar _$_cteStr43[] = {93};
static System::String* _$_cteStr43Obj;

/* [ */
static const uniChar _$_cteStr42[] = {91};
static System::String* _$_cteStr42Obj;

/* ####### Wrapper Reg Display ###### */
static const uniChar _$_cteStr41[] = {35,35,35,35,35,35,35,32,87,114,97,112,112,101,114,32,82,101,103,32,68,105,115,112,108,97,121,32,35,35,35,35,35,35};
static System::String* _$_cteStr41Obj;

/* ################################## */
static const uniChar _$_cteStr40[] = {35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35};
static System::String* _$_cteStr40Obj;

/* This handle is too high. */
static const uniChar _$_cteStr39[] = {84,104,105,115,32,104,97,110,100,108,101,32,105,115,32,116,111,111,32,104,105,103,104,46};
static System::String* _$_cteStr39Obj;

/* [C#] WrapperReg.unregisterGameObject END */
static const uniChar _$_cteStr38[] = {91,67,35,93,32,87,114,97,112,112,101,114,82,101,103,46,117,110,114,101,103,105,115,116,101,114,71,97,109,101,79,98,106,101,99,116,32,69,78,68};
static System::String* _$_cteStr38Obj;

/* Already unregistered. */
static const uniChar _$_cteStr37[] = {65,108,114,101,97,100,121,32,117,110,114,101,103,105,115,116,101,114,101,100,46};
static System::String* _$_cteStr37Obj;

/*  BEGIN */
static const uniChar _$_cteStr36[] = {32,66,69,71,73,78};
static System::String* _$_cteStr36Obj;

/* [C#] WrapperReg.unregisterGameObject  */
static const uniChar _$_cteStr35[] = {91,67,35,93,32,87,114,97,112,112,101,114,82,101,103,46,117,110,114,101,103,105,115,116,101,114,71,97,109,101,79,98,106,101,99,116,32};
static System::String* _$_cteStr35Obj;

/* This object is already registered. */
static const uniChar _$_cteStr34[] = {84,104,105,115,32,111,98,106,101,99,116,32,105,115,32,97,108,114,101,97,100,121,32,114,101,103,105,115,116,101,114,101,100,46};
static System::String* _$_cteStr34Obj;

/* Register GameObject with handle  */
static const uniChar _$_cteStr33[] = {82,101,103,105,115,116,101,114,32,71,97,109,101,79,98,106,101,99,116,32,119,105,116,104,32,104,97,110,100,108,101,32};
static System::String* _$_cteStr33Obj;

/* [C#] WrapperReg - Register GameObject with handle  */
static const uniChar _$_cteStr32[] = {91,67,35,93,32,87,114,97,112,112,101,114,82,101,103,32,45,32,82,101,103,105,115,116,101,114,32,71,97,109,101,79,98,106,101,99,116,32,119,105,116,104,32,104,97,110,100,108,101,32};
static System::String* _$_cteStr32Obj;

/* [C#] WrapperReg - array RESIZE */
static const uniChar _$_cteStr31[] = {91,67,35,93,32,87,114,97,112,112,101,114,82,101,103,32,45,32,97,114,114,97,121,32,82,69,83,73,90,69};
static System::String* _$_cteStr31Obj;

/* [C#] WrapperReg - Handle OK */
static const uniChar _$_cteStr30[] = {91,67,35,93,32,87,114,97,112,112,101,114,82,101,103,32,45,32,72,97,110,100,108,101,32,79,75};
static System::String* _$_cteStr30Obj;

/* [C#] WrapperReg.registerGameObject BEGIN */
static const uniChar _$_cteStr29[] = {91,67,35,93,32,87,114,97,112,112,101,114,82,101,103,46,114,101,103,105,115,116,101,114,71,97,109,101,79,98,106,101,99,116,32,66,69,71,73,78};
static System::String* _$_cteStr29Obj;

/* [C#] WrapperReg cctor END */
static const uniChar _$_cteStr28[] = {91,67,35,93,32,87,114,97,112,112,101,114,82,101,103,32,99,99,116,111,114,32,69,78,68};
static System::String* _$_cteStr28Obj;

/* [C#] WrapperReg cctor BEGIN */
static const uniChar _$_cteStr27[] = {91,67,35,93,32,87,114,97,112,112,101,114,82,101,103,32,99,99,116,111,114,32,66,69,71,73,78};
static System::String* _$_cteStr27Obj;

/* ) =  */
static const uniChar _$_cteStr26[] = {41,32,61,32};
static System::String* _$_cteStr26Obj;

/* [C#] Utils.GetClassIDByName( */
static const uniChar _$_cteStr25[] = {91,67,35,93,32,85,116,105,108,115,46,71,101,116,67,108,97,115,115,73,68,66,121,78,97,109,101,40};
static System::String* _$_cteStr25Obj;

/* There is not any Node compatible with this task. */
static const uniChar _$_cteStr24[] = {84,104,101,114,101,32,105,115,32,110,111,116,32,97,110,121,32,78,111,100,101,32,99,111,109,112,97,116,105,98,108,101,32,119,105,116,104,32,116,104,105,115,32,116,97,115,107,46};
static System::String* _$_cteStr24Obj;

/* Unregister Wrapper */
static const uniChar _$_cteStr23[] = {85,110,114,101,103,105,115,116,101,114,32,87,114,97,112,112,101,114};
static System::String* _$_cteStr23Obj;

/* [C#] NativeManagement.registerWrapper END */
static const uniChar _$_cteStr22[] = {91,67,35,93,32,78,97,116,105,118,101,77,97,110,97,103,101,109,101,110,116,46,114,101,103,105,115,116,101,114,87,114,97,112,112,101,114,32,69,78,68};
static System::String* _$_cteStr22Obj;

/* C# object and C++ object don't have the same typeID, impossible to bind them. */
static const uniChar _$_cteStr21[] = {67,35,32,111,98,106,101,99,116,32,97,110,100,32,67,43,43,32,111,98,106,101,99,116,32,100,111,110,39,116,32,104,97,118,101,32,116,104,101,32,115,97,109,101,32,116,121,112,101,73,68,44,32,105,109,112,111,115,115,105,98,108,101,32,116,111,32,98,105,110,100,32,116,104,101,109,46};
static System::String* _$_cteStr21Obj;

/* [C#] NativeManagement.registerWrapper BEGIN */
static const uniChar _$_cteStr20[] = {91,67,35,93,32,78,97,116,105,118,101,77,97,110,97,103,101,109,101,110,116,46,114,101,103,105,115,116,101,114,87,114,97,112,112,101,114,32,66,69,71,73,78};
static System::String* _$_cteStr20Obj;

/* Error from C++ Engine :  */
static const uniChar _$_cteStr19[] = {69,114,114,111,114,32,102,114,111,109,32,67,43,43,32,69,110,103,105,110,101,32,58,32};
static System::String* _$_cteStr19Obj;

/* . */
static const uniChar _$_cteStr18[] = {46};
static System::String* _$_cteStr18Obj;

/* Invalid index, it must be between 0 and  */
static const uniChar _$_cteStr17[] = {73,110,118,97,108,105,100,32,105,110,100,101,120,44,32,105,116,32,109,117,115,116,32,98,101,32,98,101,116,119,101,101,110,32,48,32,97,110,100,32};
static System::String* _$_cteStr17Obj;

/* NULL function pointer. */
static const uniChar _$_cteStr16[] = {78,85,76,76,32,102,117,110,99,116,105,111,110,32,112,111,105,110,116,101,114,46};
static System::String* _$_cteStr16Obj;

/* This class doesn't have any callback */
static const uniChar _$_cteStr15[] = {84,104,105,115,32,99,108,97,115,115,32,100,111,101,115,110,39,116,32,104,97,118,101,32,97,110,121,32,99,97,108,108,98,97,99,107};
static System::String* _$_cteStr15Obj;

/* [C#] GameObject.Dispose END */
static const uniChar _$_cteStr14[] = {91,67,35,93,32,71,97,109,101,79,98,106,101,99,116,46,68,105,115,112,111,115,101,32,69,78,68};
static System::String* _$_cteStr14Obj;

/* [C#] GameObject.Dispose BEGIN */
static const uniChar _$_cteStr13[] = {91,67,35,93,32,71,97,109,101,79,98,106,101,99,116,46,68,105,115,112,111,115,101,32,66,69,71,73,78};
static System::String* _$_cteStr13Obj;

/* [C#] GameObject.unbind() END */
static const uniChar _$_cteStr12[] = {91,67,35,93,32,71,97,109,101,79,98,106,101,99,116,46,117,110,98,105,110,100,40,41,32,69,78,68};
static System::String* _$_cteStr12Obj;

/* [C#] GameObject.unbind() BEGIN */
static const uniChar _$_cteStr11[] = {91,67,35,93,32,71,97,109,101,79,98,106,101,99,116,46,117,110,98,105,110,100,40,41,32,66,69,71,73,78};
static System::String* _$_cteStr11Obj;

/* There is not any Node with this name. */
static const uniChar _$_cteStr10[] = {84,104,101,114,101,32,105,115,32,110,111,116,32,97,110,121,32,78,111,100,101,32,119,105,116,104,32,116,104,105,115,32,110,97,109,101,46};
static System::String* _$_cteStr10Obj;

/* Impossible to bind with a null name. */
static const uniChar _$_cteStr9[] = {73,109,112,111,115,115,105,98,108,101,32,116,111,32,98,105,110,100,32,119,105,116,104,32,97,32,110,117,108,108,32,110,97,109,101,46};
static System::String* _$_cteStr9Obj;

/* Impossible to bind a null pointer (It can be a failure on Engine side while creating C++ instance). */
static const uniChar _$_cteStr8[] = {73,109,112,111,115,115,105,98,108,101,32,116,111,32,98,105,110,100,32,97,32,110,117,108,108,32,112,111,105,110,116,101,114,32,40,73,116,32,99,97,110,32,98,101,32,97,32,102,97,105,108,117,114,101,32,111,110,32,69,110,103,105,110,101,32,115,105,100,101,32,119,104,105,108,101,32,99,114,101,97,116,105,110,103,32,67,43,43,32,105,110,115,116,97,110,99,101,41,46};
static System::String* _$_cteStr8Obj;

/* This GameObject is already binded. */
static const uniChar _$_cteStr7[] = {84,104,105,115,32,71,97,109,101,79,98,106,101,99,116,32,105,115,32,97,108,114,101,97,100,121,32,98,105,110,100,101,100,46};
static System::String* _$_cteStr7Obj;

/* This C++ object is already wrapped. */
static const uniChar _$_cteStr6[] = {84,104,105,115,32,67,43,43,32,111,98,106,101,99,116,32,105,115,32,97,108,114,101,97,100,121,32,119,114,97,112,112,101,100,46};
static System::String* _$_cteStr6Obj;

/* __Internal */
static const uniChar _$_cteStr5[] = {95,95,73,110,116,101,114,110,97,108};
static System::String* _$_cteStr5Obj;

/* Use iterator or related object created in a different time frame / call back. */
static const uniChar _$_cteStr4[] = {85,115,101,32,105,116,101,114,97,116,111,114,32,111,114,32,114,101,108,97,116,101,100,32,111,98,106,101,99,116,32,99,114,101,97,116,101,100,32,105,110,32,97,32,100,105,102,102,101,114,101,110,116,32,116,105,109,101,32,102,114,97,109,101,32,47,32,99,97,108,108,32,98,97,99,107,46};
static System::String* _$_cteStr4Obj;

/* Null CppObject Pointer. */
static const uniChar _$_cteStr3[] = {78,117,108,108,32,67,112,112,79,98,106,101,99,116,32,80,111,105,110,116,101,114,46};
static System::String* _$_cteStr3Obj;

/* Forbidden Method */
static const uniChar _$_cteStr2[] = {70,111,114,98,105,100,100,101,110,32,77,101,116,104,111,100};
static System::String* _$_cteStr2Obj;

/* Not implemented */
static const uniChar _$_cteStr1[] = {78,111,116,32,105,109,112,108,101,109,101,110,116,101,100};
static System::String* _$_cteStr1Obj;

/*  */
static System::String* _$_cteStr0Obj;

void* _global_array_initializer_6(void* array_);
void* _global_array_initializer_4(void* array_);
void* _global_array_initializer_3(void* array_);
void* _global_array_initializer_2(void* array_);
void* _global_array_initializer_1(void* array_);
void* _global_array_initializer_0(void* array_);


namespace EnginePrototype {
    class _Delegate_Base_FunctionPointerV_inner0;
    template <class TClass> class _DelegateI_FunctionPointerV_inner0;
    class _DelegateS_FunctionPointerV_inner0;
    class _Delegate_Base_FunctionPointerII_inner1;
    template <class TClass> class _DelegateI_FunctionPointerII_inner1;
    class _DelegateS_FunctionPointerII_inner1;
    class _Delegate_Base_FunctionPointerIII_inner2;
    template <class TClass> class _DelegateI_FunctionPointerIII_inner2;
    class _DelegateS_FunctionPointerIII_inner2;
    class _Delegate_Base_FunctionPointerIIII_inner3;
    template <class TClass> class _DelegateI_FunctionPointerIIII_inner3;
    class _DelegateS_FunctionPointerIIII_inner3;
    class _Delegate_Base_FunctionPointerS_inner4;
    template <class TClass> class _DelegateI_FunctionPointerS_inner4;
    class _DelegateS_FunctionPointerS_inner4;
    class _Delegate_Base_FunctionPointerSII_inner5;
    template <class TClass> class _DelegateI_FunctionPointerSII_inner5;
    class _DelegateS_FunctionPointerSII_inner5;
    class _Delegate_Base_FunctionPointerSU_inner6;
    template <class TClass> class _DelegateI_FunctionPointerSU_inner6;
    class _DelegateS_FunctionPointerSU_inner6;
    class _Delegate_Base_FunctionPointerSS_inner7;
    template <class TClass> class _DelegateI_FunctionPointerSS_inner7;
    class _DelegateS_FunctionPointerSS_inner7;
    class _Delegate_Base_FunctionPointerUS_inner8;
    template <class TClass> class _DelegateI_FunctionPointerUS_inner8;
    class _DelegateS_FunctionPointerUS_inner8;
    class _Delegate_Base_FunctionPointerUSS_inner9;
    template <class TClass> class _DelegateI_FunctionPointerUSS_inner9;
    class _DelegateS_FunctionPointerUSS_inner9;
    class _Delegate_Base_FunctionPointerU_inner10;
    template <class TClass> class _DelegateI_FunctionPointerU_inner10;
    class _DelegateS_FunctionPointerU_inner10;
    class _Delegate_Base_FunctionPointerUU_inner11;
    template <class TClass> class _DelegateI_FunctionPointerUU_inner11;
    class _DelegateS_FunctionPointerUU_inner11;
    class _Delegate_Base_FunctionPointerUFF_inner12;
    template <class TClass> class _DelegateI_FunctionPointerUFF_inner12;
    class _DelegateS_FunctionPointerUFF_inner12;
    class _Delegate_Base_FunctionPointerUI_inner13;
    template <class TClass> class _DelegateI_FunctionPointerUI_inner13;
    class _DelegateS_FunctionPointerUI_inner13;
    class _Delegate_Base_FunctionPointerUII_inner14;
    template <class TClass> class _DelegateI_FunctionPointerUII_inner14;
    class _DelegateS_FunctionPointerUII_inner14;
    class _Delegate_Base_FunctionPointerUIIII_inner15;
    template <class TClass> class _DelegateI_FunctionPointerUIIII_inner15;
    class _DelegateS_FunctionPointerUIIII_inner15;
    class _Delegate_Base_FunctionPointerUIIUU_inner16;
    template <class TClass> class _DelegateI_FunctionPointerUIIUU_inner16;
    class _DelegateS_FunctionPointerUIIUU_inner16;
    class _Delegate_Base_FunctionPointerUUII_inner17;
    template <class TClass> class _DelegateI_FunctionPointerUUII_inner17;
    class _DelegateS_FunctionPointerUUII_inner17;
    class _Delegate_Base_FunctionPointerUUUII_inner18;
    template <class TClass> class _DelegateI_FunctionPointerUUUII_inner18;
    class _DelegateS_FunctionPointerUUUII_inner18;
    class _Delegate_Base_FunctionPointerIIIP_retB_inner19;
    template <class TClass> class _DelegateI_FunctionPointerIIIP_retB_inner19;
    class _DelegateS_FunctionPointerIIIP_retB_inner19;
    class _Delegate_Base_FunctionPointerFS_inner20;
    template <class TClass> class _DelegateI_FunctionPointerFS_inner20;
    class _DelegateS_FunctionPointerFS_inner20;
    class _Delegate_Base_CallBack_inner21;
    template <class TClass> class _DelegateI_CallBack_inner21;
    class _DelegateS_CallBack_inner21;
    class _Delegate_Base_ExecuteCallBack_inner22;
    template <class TClass> class _DelegateI_ExecuteCallBack_inner22;
    class _DelegateS_ExecuteCallBack_inner22;
    class _Delegate_Base_DieCallBack_inner23;
    template <class TClass> class _DelegateI_DieCallBack_inner23;
    class _DelegateS_DieCallBack_inner23;
    class _Delegate_Base_CallBack_inner24;
    template <class TClass> class _DelegateI_CallBack_inner24;
    class _DelegateS_CallBack_inner24;
    class _Delegate_Base_CallBack_inner25;
    template <class TClass> class _DelegateI_CallBack_inner25;
    class _DelegateS_CallBack_inner25;
    class _Delegate_Base_CallBackVersionUp_inner26;
    template <class TClass> class _DelegateI_CallBackVersionUp_inner26;
    class _DelegateS_CallBackVersionUp_inner26;
    class _Delegate_Base_CallBack_inner27;
    template <class TClass> class _DelegateI_CallBack_inner27;
    class _DelegateS_CallBack_inner27;
    class _Delegate_Base_onDieCallBack_inner28;
    template <class TClass> class _DelegateI_onDieCallBack_inner28;
    class _DelegateS_onDieCallBack_inner28;
    class _Delegate_Base_CallBack_inner29;
    template <class TClass> class _DelegateI_CallBack_inner29;
    class _DelegateS_CallBack_inner29;
    class _Delegate_Base_OnClickCallBack_inner30;
    template <class TClass> class _DelegateI_OnClickCallBack_inner30;
    class _DelegateS_OnClickCallBack_inner30;
    class _Delegate_Base_OnDblClickCallBack_inner31;
    template <class TClass> class _DelegateI_OnDblClickCallBack_inner31;
    class _DelegateS_OnDblClickCallBack_inner31;
    class _Delegate_Base_OnDragCallBack_inner32;
    template <class TClass> class _DelegateI_OnDragCallBack_inner32;
    class _DelegateS_OnDragCallBack_inner32;
    class _Delegate_Base_OnPinchCallBack_inner33;
    template <class TClass> class _DelegateI_OnPinchCallBack_inner33;
    class _DelegateS_OnPinchCallBack_inner33;
    class _Delegate_Base_OnLongTapCallBack_inner34;
    template <class TClass> class _DelegateI_OnLongTapCallBack_inner34;
    class _DelegateS_OnLongTapCallBack_inner34;
    class _Delegate_Base_CallBack_inner35;
    template <class TClass> class _DelegateI_CallBack_inner35;
    class _DelegateS_CallBack_inner35;
    class _Delegate_Base_CallBack_inner36;
    template <class TClass> class _DelegateI_CallBack_inner36;
    class _DelegateS_CallBack_inner36;
    class _Delegate_Base_SelectableCallBack_inner37;
    template <class TClass> class _DelegateI_SelectableCallBack_inner37;
    class _DelegateS_SelectableCallBack_inner37;
    class _Delegate_Base_AnimCallBack_inner38;
    template <class TClass> class _DelegateI_AnimCallBack_inner38;
    class _DelegateS_AnimCallBack_inner38;
    class _Delegate_Base_AnimCallBack_inner39;
    template <class TClass> class _DelegateI_AnimCallBack_inner39;
    class _DelegateS_AnimCallBack_inner39;
    class _Delegate_Base_LimitCallBack_inner40;
    template <class TClass> class _DelegateI_LimitCallBack_inner40;
    class _DelegateS_LimitCallBack_inner40;
    class _Delegate_Base_DragCallBack_inner41;
    template <class TClass> class _DelegateI_DragCallBack_inner41;
    class _DelegateS_DragCallBack_inner41;
    class _Delegate_Base_DynamicCallBack_inner42;
    template <class TClass> class _DelegateI_DynamicCallBack_inner42;
    class _DelegateS_DynamicCallBack_inner42;
    class _Delegate_Base_ScrollBarCallBack_inner43;
    template <class TClass> class _DelegateI_ScrollBarCallBack_inner43;
    class _DelegateS_ScrollBarCallBack_inner43;
    class _Delegate_Base_AnimCallBack_inner44;
    template <class TClass> class _DelegateI_AnimCallBack_inner44;
    class _DelegateS_AnimCallBack_inner44;
    class _Delegate_Base_CallBack_inner45;
    template <class TClass> class _DelegateI_CallBack_inner45;
    class _DelegateS_CallBack_inner45;
    class _Delegate_Base_ScrollBarCallBack_inner46;
    template <class TClass> class _DelegateI_ScrollBarCallBack_inner46;
    class _DelegateS_ScrollBarCallBack_inner46;
    class _Delegate_Base_CallBack_inner47;
    template <class TClass> class _DelegateI_CallBack_inner47;
    class _DelegateS_CallBack_inner47;
    class _Delegate_Base_CallBack_inner48;
    template <class TClass> class _DelegateI_CallBack_inner48;
    class _DelegateS_CallBack_inner48;
    class _Delegate_Base_CallBack_inner49;
    template <class TClass> class _DelegateI_CallBack_inner49;
    class _DelegateS_CallBack_inner49;
    class _Delegate_Base_CallBack_inner50;
    template <class TClass> class _DelegateI_CallBack_inner50;
    class _DelegateS_CallBack_inner50;
    class _Delegate_Base_CallBack_inner51;
    template <class TClass> class _DelegateI_CallBack_inner51;
    class _DelegateS_CallBack_inner51;
    class CKLBException;
    class CKLBExceptionNotImplemented;
    class CKLBExceptionForbiddenMethod;
    class CKLBExceptionNullCppObject;
    class CKLBExceptionTooOld;
    class GameObject;
    class GameObjectFactory;
    class NativeManagement;
    class NodeIterator;
    class Element;
    class Container;
    class Selectable;
    class AnimationNode;
    struct Size;
    struct USize;
    struct FSize;
    class IClientRequest;
    class __FrameworkUtils;
    class WrapperReg;
    class CSAPP;
    class CSAsset;
    class CSBin;
    class CSData;
    class CSDB;
    class CSDebug;
    class CSEng;
    class CSFont;
    struct STextInfo_inner0;
    class CSGL;
    class CSKey;
    class CSLang;
    class CSMatrix;
    class CSVector_inner1;
    class CSRES;
    class CSSound;
    class CSSystem;
    struct SystemInfo_inner2;
    class CSUI;
    class CKLBAsyncLoader;
    class CKLBGenericTask;
    class CKLBIntervalTimer;
    class CKLBNetAPI;
    class CKLBStoreService;
    class CKLBTask;
    class CKLBUICanvas;
    class CKLBUIClip;
    class CKLBUIControl;
    class CKLBUIDebugItem;
    class CKLBUIDragIcon;
    struct Area_inner3;
    class CKLBUIForm;
    class CKLBUIFreeVertItem;
    class CKLBUIGroup;
    class CKLBUILabel;
    class CKLBUIList;
    class CKLBUIMoviePlayer;
    class CKLBUIMultiImgItem;
    class CKLBUIPieChart;
    class CKLBUIPolyline;
    class CKLBUIProgressBar;
    class CKLBUIRubberBand;
    class CKLBUIScale9;
    class AnimationInfo;
    class CKLBUIScore;
    class CKLBUIScrollBar;
    class CKLBUISimpleItem;
    class CKLBUISWFPlayer;
    class CKLBUITask;
    class Spline_inner4;
    class IntSpline_inner5;
    class IntPoint_inner6;
    class FloatSpline_inner7;
    class FloatPoint_inner8;
    class AnimSpline_inner9;
    class CKLBUITextInput;
    class CKLBUITouchPad;
    class CKLBUIVariableItem;
    class CKLBUIVirtualDoc;
    class CKLBUIWebArea;

}
class EnginePrototype::CKLBException : public System::Exception {

public:
    void _ctor_CKLBException();
    CKLBException(System::String* msg);
    CKLBException();
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 50;
};
class EnginePrototype::CKLBExceptionNotImplemented : public EnginePrototype::CKLBException {

public:
    void _ctor_CKLBExceptionNotImplemented();
    CKLBExceptionNotImplemented(System::String* msg);
    CKLBExceptionNotImplemented();
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 51;
};
class EnginePrototype::CKLBExceptionForbiddenMethod : public EnginePrototype::CKLBException {

public:
    void _ctor_CKLBExceptionForbiddenMethod();
    CKLBExceptionForbiddenMethod(System::String* msg);
    CKLBExceptionForbiddenMethod();
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 52;
};
class EnginePrototype::CKLBExceptionNullCppObject : public EnginePrototype::CKLBException {

public:
    void _ctor_CKLBExceptionNullCppObject();
    CKLBExceptionNullCppObject(System::String* msg);
    CKLBExceptionNullCppObject();
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 53;
};
class EnginePrototype::CKLBExceptionTooOld : public EnginePrototype::CKLBException {

public:
    void _ctor_CKLBExceptionTooOld();
    CKLBExceptionTooOld(System::String* msg);
    CKLBExceptionTooOld();
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 54;
};
class EnginePrototype::GameObject : public System::Object ,public System::IDisposable {

public:
    void _ctor_GameObject();
    static u32 NULLHANDLER;
    inline static u32 _sNULLHANDLERDivEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return NULLHANDLER /= value; }
    inline static u32 _sNULLHANDLERModEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return NULLHANDLER %= value; }

    static u32 NBCALLBACKS;
    inline static u32 _sNBCALLBACKSDivEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return NBCALLBACKS /= value; }
    inline static u32 _sNBCALLBACKSModEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return NBCALLBACKS %= value; }

    System::Object* m_tag;
    inline System::Object*& _gm_tag$() { CHCKTHIS; return m_tag; }
    inline System::Object* _sm_tag(System::Object* _$value);
    inline System::Object* _sm_tag$(System::Object* _$value);

    u32 m_typeID;
    inline u32& _gm_typeID$() { CHCKTHIS; return m_typeID; }
    inline u32 _sm_typeID$(u32 _$value) { CHCKTHIS; return m_typeID = _$value; }
    inline u32 _sm_typeID$postInc()				{ CHCKTHIS; return m_typeID++; }
    inline u32 _sm_typeID$postDec()				{ CHCKTHIS; return m_typeID--; }
    inline u32 _sm_typeID$preInc()				{ CHCKTHIS; return ++m_typeID; }
    inline u32 _sm_typeID$preDec()				{ CHCKTHIS; return --m_typeID; }
    inline u32 _sm_typeID$AddEq(u32 value)		{ CHCKTHIS; return m_typeID += value; }
    inline u32 _sm_typeID$SubEq(u32 value)		{ CHCKTHIS; return m_typeID -= value; }
    inline u32 _sm_typeID$MulEq(u32 value)		{ CHCKTHIS; return m_typeID *= value; }
    inline u32 _sm_typeID$DivEq(u32 value)		{ CHCKTHIS; if (value == 0) { THROWDIVZERO; }; ; return m_typeID /= value; }
    inline u32 _sm_typeID$ModEq(u32 value)		{ CHCKTHIS; if (value == 0) { THROWDIVZERO; }; ; return m_typeID %= value; }
    inline u32 _sm_typeID$XorEq(u32 value)		{ CHCKTHIS; return m_typeID ^= value; }
    inline u32 _sm_typeID$AndEq(u32 value)		{ CHCKTHIS; return m_typeID &= value; }
    inline u32 _sm_typeID$OrEq(u32 value)		{ CHCKTHIS; return m_typeID |= value; }
    inline u32 _sm_typeID$RShiftEq(u32 value)	{ CHCKTHIS; return m_typeID >>= value; }
    inline u32 _sm_typeID$LShiftEq(u32 value)	{ CHCKTHIS; return m_typeID <<= value; }
    inline u32 _sm_typeIDpostInc()				{ return m_typeID++; }
    inline u32 _sm_typeIDpostDec()				{ return m_typeID--; }
    inline u32 _sm_typeIDpreInc()				{ return ++m_typeID; }
    inline u32 _sm_typeIDpreDec()				{ return --m_typeID; }
    inline u32 _sm_typeIDAddEq(u32 value)		{ return m_typeID += value; }
    inline u32 _sm_typeIDSubEq(u32 value)		{ return m_typeID -= value; }
    inline u32 _sm_typeIDMulEq(u32 value)		{ return m_typeID *= value; }
    inline u32 _sm_typeIDDivEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return m_typeID /= value; }
    inline u32 _sm_typeIDModEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return m_typeID %= value; }
    inline u32 _sm_typeIDXorEq(u32 value)		{ return m_typeID ^= value; }
    inline u32 _sm_typeIDAndEq(u32 value)		{ return m_typeID &= value; }
    inline u32 _sm_typeIDOrEq(u32 value)			{ return m_typeID |= value; }
    inline u32 _sm_typeIDRShiftEq(u32 value)		{ return m_typeID >>= value; }
    inline u32 _sm_typeIDLShiftEq(u32 value)		{ return m_typeID <<= value; }

    u32 m_handle;
    inline u32& _gm_handle$() { CHCKTHIS; return m_handle; }
    inline u32 _sm_handle$(u32 _$value) { CHCKTHIS; return m_handle = _$value; }
    inline u32 _sm_handle$postInc()				{ CHCKTHIS; return m_handle++; }
    inline u32 _sm_handle$postDec()				{ CHCKTHIS; return m_handle--; }
    inline u32 _sm_handle$preInc()				{ CHCKTHIS; return ++m_handle; }
    inline u32 _sm_handle$preDec()				{ CHCKTHIS; return --m_handle; }
    inline u32 _sm_handle$AddEq(u32 value)		{ CHCKTHIS; return m_handle += value; }
    inline u32 _sm_handle$SubEq(u32 value)		{ CHCKTHIS; return m_handle -= value; }
    inline u32 _sm_handle$MulEq(u32 value)		{ CHCKTHIS; return m_handle *= value; }
    inline u32 _sm_handle$DivEq(u32 value)		{ CHCKTHIS; if (value == 0) { THROWDIVZERO; }; ; return m_handle /= value; }
    inline u32 _sm_handle$ModEq(u32 value)		{ CHCKTHIS; if (value == 0) { THROWDIVZERO; }; ; return m_handle %= value; }
    inline u32 _sm_handle$XorEq(u32 value)		{ CHCKTHIS; return m_handle ^= value; }
    inline u32 _sm_handle$AndEq(u32 value)		{ CHCKTHIS; return m_handle &= value; }
    inline u32 _sm_handle$OrEq(u32 value)		{ CHCKTHIS; return m_handle |= value; }
    inline u32 _sm_handle$RShiftEq(u32 value)	{ CHCKTHIS; return m_handle >>= value; }
    inline u32 _sm_handle$LShiftEq(u32 value)	{ CHCKTHIS; return m_handle <<= value; }
    inline u32 _sm_handlepostInc()				{ return m_handle++; }
    inline u32 _sm_handlepostDec()				{ return m_handle--; }
    inline u32 _sm_handlepreInc()				{ return ++m_handle; }
    inline u32 _sm_handlepreDec()				{ return --m_handle; }
    inline u32 _sm_handleAddEq(u32 value)		{ return m_handle += value; }
    inline u32 _sm_handleSubEq(u32 value)		{ return m_handle -= value; }
    inline u32 _sm_handleMulEq(u32 value)		{ return m_handle *= value; }
    inline u32 _sm_handleDivEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return m_handle /= value; }
    inline u32 _sm_handleModEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return m_handle %= value; }
    inline u32 _sm_handleXorEq(u32 value)		{ return m_handle ^= value; }
    inline u32 _sm_handleAndEq(u32 value)		{ return m_handle &= value; }
    inline u32 _sm_handleOrEq(u32 value)			{ return m_handle |= value; }
    inline u32 _sm_handleRShiftEq(u32 value)		{ return m_handle >>= value; }
    inline u32 _sm_handleLShiftEq(u32 value)		{ return m_handle <<= value; }

    s32* m_cppObject;
    inline s32*& _gm_cppObject$() { CHCKTHIS; return m_cppObject; }
    inline s32* _sm_cppObject$(s32* _$value) { CHCKTHIS; return m_cppObject = _$value; }
    inline s32* _sm_cppObject$AddEq(s32 value)		{ CHCKTHIS; return m_cppObject += value; }
    inline s32* _sm_cppObject$SubEq(s32 value)		{ CHCKTHIS; return m_cppObject -= value; }
    inline s32* _sm_cppObjectAddEq(s32 value)		{ return m_cppObject += value; }
    inline s32* _sm_cppObjectSubEq(s32 value)		{ return m_cppObject -= value; }

    System::Array<System::Delegate*>* m_callbacksArray;
    inline System::Array<System::Delegate*>*& _gm_callbacksArray$() { CHCKTHIS; return m_callbacksArray; }
    inline System::Array<System::Delegate*>* _sm_callbacksArray(System::Array<System::Delegate*>* _$value);
    inline System::Array<System::Delegate*>* _sm_callbacksArray$(System::Array<System::Delegate*>* _$value);

    inline System::Object* _acc_gTag();
    inline System::Object* _acc_gTag$();

    inline System::Object* _acc_sTag(System::Object* value);
    inline System::Object* _acc_sTag$(System::Object* value);
    inline u32 _acc_gTypeID();
    inline u32 _acc_gTypeID$();

    inline u32 _acc_gHandle();
    inline u32 _acc_gHandle$();

    inline u32 _acc_sHandle(u32 value);
    inline u32 _acc_sHandle$(u32 value);
    inline u32 _acc_sHandlepostInc()			{ u32 tmp; _acc_sHandle((tmp = _acc_gHandle())+1); return tmp; }
    inline u32 _acc_sHandle$postInc()			{ CHCKTHIS; return _acc_sHandlepostInc(); }
    inline u32 _acc_sHandlepostDec()			{ u32 tmp; _acc_sHandle((tmp = _acc_gHandle())-1); return tmp; }
    inline u32 _acc_sHandle$postDec()			{ CHCKTHIS; return _acc_sHandlepostDec(); }
    inline u32 _acc_sHandlepreInc()			{ return _acc_sHandle(_acc_gHandle()+1); }
    inline u32 _acc_sHandle$preInc()			{ CHCKTHIS; return _acc_sHandlepreInc(); }
    inline u32 _acc_sHandlepreDec()			{ return _acc_sHandle(_acc_gHandle()-1); }
    inline u32 _acc_sHandle$preDec()			{ CHCKTHIS; return _acc_sHandlepreDec(); }
    inline u32 _acc_sHandleAddEq(u32 value)	{ return _acc_sHandle(_acc_gHandle() + value); }
    inline u32 _acc_sHandle$AddEq(u32 value)			{ CHCKTHIS; return _acc_sHandleAddEq(value); }
    inline u32 _acc_sHandleSubEq(u32 value)	{ return _acc_sHandle(_acc_gHandle() - value); }
    inline u32 _acc_sHandle$SubEq(u32 value)			{ CHCKTHIS; return _acc_sHandleSubEq(value); }
    inline u32 _acc_sHandleMulEq(u32 value)	{ return _acc_sHandle(_acc_gHandle() * value); }
    inline u32 _acc_sHandle$MulEq(u32 value)			{ CHCKTHIS; return _acc_sHandleMulEq(value); }
    inline u32 _acc_sHandleDivEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sHandle(_acc_gHandle() / value); }
    inline u32 _acc_sHandle$DivEq(u32 value)			{ CHCKTHIS; return _acc_sHandleDivEq(value); }
    inline u32 _acc_sHandleModEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sHandle(_acc_gHandle() % value); }
    inline u32 _acc_sHandle$ModEq(u32 value)			{ CHCKTHIS; return _acc_sHandleModEq(value); }
    inline u32 _acc_sHandleXorEq(u32 value)	{ return _acc_sHandle(_acc_gHandle() ^ value); }
    inline u32 _acc_sHandle$XorEq(u32 value)			{ CHCKTHIS; return _acc_sHandleXorEq(value); }
    inline u32 _acc_sHandleAndEq(u32 value)	{ return _acc_sHandle(_acc_gHandle() & value); }
    inline u32 _acc_sHandle$AndEq(u32 value)			{ CHCKTHIS; return _acc_sHandleAndEq(value); }
    inline u32 _acc_sHandleOrEq(u32 value)		{ return _acc_sHandle(_acc_gHandle() | value); }
    inline u32 _acc_sHandle$OrEq(u32 value)			{ CHCKTHIS; return _acc_sHandleOrEq(value); }
    inline u32 _acc_sHandleRShiftEq(u32 value)	{ return _acc_sHandle(_acc_gHandle() >> value); }
    inline u32 _acc_sHandle$RShiftEq(u32 value)			{ CHCKTHIS; return _acc_sHandleRShiftEq(value); }
    inline u32 _acc_sHandleLShiftEq(u32 value)	{ return _acc_sHandle(_acc_gHandle() << value); }
    inline u32 _acc_sHandle$LShiftEq(u32 value)			{ CHCKTHIS; return _acc_sHandleLShiftEq(value); }
    inline s32* _acc_gCppObject();
    inline s32* _acc_gCppObject$();

    inline s32* _acc_sCppObject(s32* value);
    inline s32* _acc_sCppObject$(s32* value);
    inline s32* _acc_sCppObjectAddEq(s32 value)	{ return _acc_sCppObject(_acc_gCppObject() + value); }
    inline s32* _acc_sCppObject$AddEq(s32 value)			{ CHCKTHIS; return _acc_sCppObjectAddEq(value); }
    inline s32* _acc_sCppObjectSubEq(s32 value)	{ return _acc_sCppObject(_acc_gCppObject() - value); }
    inline s32* _acc_sCppObject$SubEq(s32 value)			{ CHCKTHIS; return _acc_sCppObjectSubEq(value); }
    static u32 _ext_CKLBObjectScriptable_getScriptContext(s32* p);
    static void _ext_CKLBObjectScriptable_setScriptContext(s32* p,u32 handle);
    bool isBoundToCpp();
    inline bool isBoundToCpp$();
    GameObject(u32 typeID);
    void bind(s32* cppObj);
    inline void bind$(s32* cppObj);
    void bind(System::String* nodeName);
    inline void bind$(System::String* nodeName);
    void unbind();
    inline void unbind$();
    virtual void doSetupCallbacks();
    inline void doSetupCallbacks$();
    virtual void clearInternals();
    inline void clearInternals$();
    virtual void Dispose();
    inline void Dispose$();
    virtual void setDelegate(System::Delegate* anyDelegate,System::String* delegateName);
    inline void setDelegate$(System::Delegate* anyDelegate,System::String* delegateName);
    static void staticSetDelegate(u32 handle,System::Delegate* delegatePtr,System::String* delegateName);
    void forceSetupCallBackWithVirtual(System::String* delegateName);
    inline void forceSetupCallBackWithVirtual$(System::String* delegateName);
    void registerCallBack(System::Delegate* callback,u32 index);
    inline void registerCallBack$(System::Delegate* callback,u32 index);
    System::Delegate* getCallBack(u32 index);
    inline System::Delegate* getCallBack$(u32 index);
    GameObject();
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 55;
};
class EnginePrototype::GameObjectFactory : public System::Object {

public:
    void _ctor_GameObjectFactory();
    GameObjectFactory();
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 56;
};
class EnginePrototype::NativeManagement : public System::Object {
friend class FunctionPointerV_inner0;
friend class FunctionPointerII_inner1;
friend class FunctionPointerIII_inner2;
friend class FunctionPointerIIII_inner3;
friend class FunctionPointerS_inner4;
friend class FunctionPointerSII_inner5;
friend class FunctionPointerSU_inner6;
friend class FunctionPointerSS_inner7;
friend class FunctionPointerUS_inner8;
friend class FunctionPointerUSS_inner9;
friend class FunctionPointerU_inner10;
friend class FunctionPointerUU_inner11;
friend class FunctionPointerUFF_inner12;
friend class FunctionPointerUI_inner13;
friend class FunctionPointerUII_inner14;
friend class FunctionPointerUIIII_inner15;
friend class FunctionPointerUIIUU_inner16;
friend class FunctionPointerUUII_inner17;
friend class FunctionPointerUUUII_inner18;
friend class FunctionPointerIIIP_retB_inner19;
friend class FunctionPointerFS_inner20;

public:
    void _ctor_NativeManagement();
    static s32* ms_cppErrorFlag;

    static s32* ms_counter;

    static inline u32 _acc_gCppErrorFlag();
    static inline System::String* _acc_gCppErrorString();
    static u32 _ext_CKLBObject_getTypeID(s32* p);
    static u32 _ext_CKLBObjectScriptable_getScriptContext(s32* p);
    static void _ext_CKLBObjectScriptable_setScriptContext(s32* p,u32 handle);
    static s32* _ext_CKLBScriptEnv_getCallBackCount();
    static s32* _ext_CKLBScriptEnv_getErrorPtr();
    static s32* _ext_CKLBScriptEnv_getErrorString();
    static void _ext_CKLBScriptEnv_resetError();
    static void resetCppError();
    static void intercepCppError();
    static u32 getContextCounter();
    static u32 getTypeID(s32* cppObj);
    static void registerWrapper(s32* cppObj,u32 handle);
    static void unregisterWrapper(s32* cppObj);
    static void destroyFromNative(u32 handle);
    static void doCallBackV(u32 cbInfos);
    static void doCallBackII(u32 cbInfos,s32 int_1,s32 int_2);
    static void doCallBackIII(u32 cbInfos,s32 int_1,s32 int_2,s32 int_3);
    static void doCallBackIIII(u32 cbInfos,s32 int_1,s32 int_2,s32 int_3,s32 int_4);
    static void doCallBackS(u32 cbInfos,s32* intptr_1);
    static void doCallBackSII(u32 cbInfos,s32* intptr_1,s32 int_1,s32 int_2);
    static void doCallBackSU(u32 cbInfos,s32* intptr_1,u32 uint_1);
    static void doCallBackSS(u32 cbInfos,s32* intptr_1,s32* intptr_2);
    static void doCallBackUS(u32 cbInfos,u32 uint_1,s32* intptr_1);
    static void doCallBackUSS(u32 cbInfos,u32 uint_1,s32* intptr_1,s32* intptr_2);
    static void doCallBackU(u32 cbInfos,u32 uint_1);
    static void doCallBackUU(u32 cbInfos,u32 uint_1,u32 uint_2);
    static void doCallBackUFF(u32 cbInfos,u32 uint_1,float float_1,float float_2);
    static void doCallBackUI(u32 cbInfos,u32 uint_1,s32 int_1);
    static void doCallBackUII(u32 cbInfos,u32 uint_1,s32 int_1,s32 int_2);
    static void doCallBackUIIII(u32 cbInfos,u32 uint_1,s32 int_1,s32 int_2,s32 int_3,s32 int_4);
    static void doCallBackUIIUU(u32 cbInfos,u32 uint_1,s32 int_1,s32 int_2,u32 uint_2,u32 uint_3);
    static void doCallBackUUII(u32 cbInfos,u32 uint_1,u32 uint_2,s32 int_1,s32 int_2);
    static void doCallBackUUUII(u32 cbInfos,u32 uint_1,u32 uint_2,u32 uint_3,s32 int_1,s32 int_2);
    static bool doCallBackIIIP_retB(u32 cbInfos,s32 int_1,s32 int_2,s32 int_3,s32* obj_1);
    static void doCallBackFS(u32 cbInfos,float float_1,s32* intptr_1);
    NativeManagement();
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 57;
};
class EnginePrototype::NodeIterator : public System::Object {

public:
    void _ctor_NodeIterator();
    u32 m_counter;
    inline u32& _gm_counter$() { CHCKTHIS; return m_counter; }
    inline u32 _sm_counter$(u32 _$value) { CHCKTHIS; return m_counter = _$value; }
    inline u32 _sm_counter$postInc()				{ CHCKTHIS; return m_counter++; }
    inline u32 _sm_counter$postDec()				{ CHCKTHIS; return m_counter--; }
    inline u32 _sm_counter$preInc()				{ CHCKTHIS; return ++m_counter; }
    inline u32 _sm_counter$preDec()				{ CHCKTHIS; return --m_counter; }
    inline u32 _sm_counter$AddEq(u32 value)		{ CHCKTHIS; return m_counter += value; }
    inline u32 _sm_counter$SubEq(u32 value)		{ CHCKTHIS; return m_counter -= value; }
    inline u32 _sm_counter$MulEq(u32 value)		{ CHCKTHIS; return m_counter *= value; }
    inline u32 _sm_counter$DivEq(u32 value)		{ CHCKTHIS; if (value == 0) { THROWDIVZERO; }; ; return m_counter /= value; }
    inline u32 _sm_counter$ModEq(u32 value)		{ CHCKTHIS; if (value == 0) { THROWDIVZERO; }; ; return m_counter %= value; }
    inline u32 _sm_counter$XorEq(u32 value)		{ CHCKTHIS; return m_counter ^= value; }
    inline u32 _sm_counter$AndEq(u32 value)		{ CHCKTHIS; return m_counter &= value; }
    inline u32 _sm_counter$OrEq(u32 value)		{ CHCKTHIS; return m_counter |= value; }
    inline u32 _sm_counter$RShiftEq(u32 value)	{ CHCKTHIS; return m_counter >>= value; }
    inline u32 _sm_counter$LShiftEq(u32 value)	{ CHCKTHIS; return m_counter <<= value; }
    inline u32 _sm_counterpostInc()				{ return m_counter++; }
    inline u32 _sm_counterpostDec()				{ return m_counter--; }
    inline u32 _sm_counterpreInc()				{ return ++m_counter; }
    inline u32 _sm_counterpreDec()				{ return --m_counter; }
    inline u32 _sm_counterAddEq(u32 value)		{ return m_counter += value; }
    inline u32 _sm_counterSubEq(u32 value)		{ return m_counter -= value; }
    inline u32 _sm_counterMulEq(u32 value)		{ return m_counter *= value; }
    inline u32 _sm_counterDivEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return m_counter /= value; }
    inline u32 _sm_counterModEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return m_counter %= value; }
    inline u32 _sm_counterXorEq(u32 value)		{ return m_counter ^= value; }
    inline u32 _sm_counterAndEq(u32 value)		{ return m_counter &= value; }
    inline u32 _sm_counterOrEq(u32 value)			{ return m_counter |= value; }
    inline u32 _sm_counterRShiftEq(u32 value)		{ return m_counter >>= value; }
    inline u32 _sm_counterLShiftEq(u32 value)		{ return m_counter <<= value; }

    s32* m_nodeCpp;
    inline s32*& _gm_nodeCpp$() { CHCKTHIS; return m_nodeCpp; }
    inline s32* _sm_nodeCpp$(s32* _$value) { CHCKTHIS; return m_nodeCpp = _$value; }
    inline s32* _sm_nodeCpp$AddEq(s32 value)		{ CHCKTHIS; return m_nodeCpp += value; }
    inline s32* _sm_nodeCpp$SubEq(s32 value)		{ CHCKTHIS; return m_nodeCpp -= value; }
    inline s32* _sm_nodeCppAddEq(s32 value)		{ return m_nodeCpp += value; }
    inline s32* _sm_nodeCppSubEq(s32 value)		{ return m_nodeCpp -= value; }

    System::Collections::Generic::List<s32*>* m_navigation;
    inline System::Collections::Generic::List<s32*>*& _gm_navigation$() { CHCKTHIS; return m_navigation; }
    inline System::Collections::Generic::List<s32*>* _sm_navigation(System::Collections::Generic::List<s32*>* _$value);
    inline System::Collections::Generic::List<s32*>* _sm_navigation$(System::Collections::Generic::List<s32*>* _$value);

    inline u32 _acc_gRgba();
    inline u32 _acc_gRgba$();

    inline u32 _acc_sRgba(u32 value);
    inline u32 _acc_sRgba$(u32 value);
    inline u32 _acc_sRgbapostInc()			{ u32 tmp; _acc_sRgba((tmp = _acc_gRgba())+1); return tmp; }
    inline u32 _acc_sRgba$postInc()			{ CHCKTHIS; return _acc_sRgbapostInc(); }
    inline u32 _acc_sRgbapostDec()			{ u32 tmp; _acc_sRgba((tmp = _acc_gRgba())-1); return tmp; }
    inline u32 _acc_sRgba$postDec()			{ CHCKTHIS; return _acc_sRgbapostDec(); }
    inline u32 _acc_sRgbapreInc()			{ return _acc_sRgba(_acc_gRgba()+1); }
    inline u32 _acc_sRgba$preInc()			{ CHCKTHIS; return _acc_sRgbapreInc(); }
    inline u32 _acc_sRgbapreDec()			{ return _acc_sRgba(_acc_gRgba()-1); }
    inline u32 _acc_sRgba$preDec()			{ CHCKTHIS; return _acc_sRgbapreDec(); }
    inline u32 _acc_sRgbaAddEq(u32 value)	{ return _acc_sRgba(_acc_gRgba() + value); }
    inline u32 _acc_sRgba$AddEq(u32 value)			{ CHCKTHIS; return _acc_sRgbaAddEq(value); }
    inline u32 _acc_sRgbaSubEq(u32 value)	{ return _acc_sRgba(_acc_gRgba() - value); }
    inline u32 _acc_sRgba$SubEq(u32 value)			{ CHCKTHIS; return _acc_sRgbaSubEq(value); }
    inline u32 _acc_sRgbaMulEq(u32 value)	{ return _acc_sRgba(_acc_gRgba() * value); }
    inline u32 _acc_sRgba$MulEq(u32 value)			{ CHCKTHIS; return _acc_sRgbaMulEq(value); }
    inline u32 _acc_sRgbaDivEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sRgba(_acc_gRgba() / value); }
    inline u32 _acc_sRgba$DivEq(u32 value)			{ CHCKTHIS; return _acc_sRgbaDivEq(value); }
    inline u32 _acc_sRgbaModEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sRgba(_acc_gRgba() % value); }
    inline u32 _acc_sRgba$ModEq(u32 value)			{ CHCKTHIS; return _acc_sRgbaModEq(value); }
    inline u32 _acc_sRgbaXorEq(u32 value)	{ return _acc_sRgba(_acc_gRgba() ^ value); }
    inline u32 _acc_sRgba$XorEq(u32 value)			{ CHCKTHIS; return _acc_sRgbaXorEq(value); }
    inline u32 _acc_sRgbaAndEq(u32 value)	{ return _acc_sRgba(_acc_gRgba() & value); }
    inline u32 _acc_sRgba$AndEq(u32 value)			{ CHCKTHIS; return _acc_sRgbaAndEq(value); }
    inline u32 _acc_sRgbaOrEq(u32 value)		{ return _acc_sRgba(_acc_gRgba() | value); }
    inline u32 _acc_sRgba$OrEq(u32 value)			{ CHCKTHIS; return _acc_sRgbaOrEq(value); }
    inline u32 _acc_sRgbaRShiftEq(u32 value)	{ return _acc_sRgba(_acc_gRgba() >> value); }
    inline u32 _acc_sRgba$RShiftEq(u32 value)			{ CHCKTHIS; return _acc_sRgbaRShiftEq(value); }
    inline u32 _acc_sRgbaLShiftEq(u32 value)	{ return _acc_sRgba(_acc_gRgba() << value); }
    inline u32 _acc_sRgba$LShiftEq(u32 value)			{ CHCKTHIS; return _acc_sRgbaLShiftEq(value); }
    inline float _acc_gScaleX();
    inline float _acc_gScaleX$();

    inline float _acc_sScaleX(float value);
    inline float _acc_sScaleX$(float value);
    inline float _acc_sScaleXpostInc()			{ float tmp; _acc_sScaleX((tmp = _acc_gScaleX())+1); return tmp; }
    inline float _acc_sScaleX$postInc()			{ CHCKTHIS; return _acc_sScaleXpostInc(); }
    inline float _acc_sScaleXpostDec()			{ float tmp; _acc_sScaleX((tmp = _acc_gScaleX())-1); return tmp; }
    inline float _acc_sScaleX$postDec()			{ CHCKTHIS; return _acc_sScaleXpostDec(); }
    inline float _acc_sScaleXpreInc()			{ return _acc_sScaleX(_acc_gScaleX()+1); }
    inline float _acc_sScaleX$preInc()			{ CHCKTHIS; return _acc_sScaleXpreInc(); }
    inline float _acc_sScaleXpreDec()			{ return _acc_sScaleX(_acc_gScaleX()-1); }
    inline float _acc_sScaleX$preDec()			{ CHCKTHIS; return _acc_sScaleXpreDec(); }
    inline float _acc_sScaleXAddEq(float value)	{ return _acc_sScaleX(_acc_gScaleX() + value); }
    inline float _acc_sScaleX$AddEq(float value)			{ CHCKTHIS; return _acc_sScaleXAddEq(value); }
    inline float _acc_sScaleXSubEq(float value)	{ return _acc_sScaleX(_acc_gScaleX() - value); }
    inline float _acc_sScaleX$SubEq(float value)			{ CHCKTHIS; return _acc_sScaleXSubEq(value); }
    inline float _acc_sScaleXMulEq(float value)	{ return _acc_sScaleX(_acc_gScaleX() * value); }
    inline float _acc_sScaleX$MulEq(float value)			{ CHCKTHIS; return _acc_sScaleXMulEq(value); }
    inline float _acc_sScaleXDivEq(float value)	{ return _acc_sScaleX(_acc_gScaleX() / value); }
    inline float _acc_sScaleX$DivEq(float value)			{ CHCKTHIS; return _acc_sScaleXDivEq(value); }
    inline float _acc_sScaleXModEq(float value)	{  float orig = _acc_gScaleX(); s32 tmp = (s32)(orig / value); return _acc_sScaleX(orig - (tmp * value)); }
    inline float _acc_sScaleX$ModEq(float value)			{ CHCKTHIS; return _acc_sScaleXModEq(value); }
    inline float _acc_gScaleY();
    inline float _acc_gScaleY$();

    inline float _acc_sScaleY(float value);
    inline float _acc_sScaleY$(float value);
    inline float _acc_sScaleYpostInc()			{ float tmp; _acc_sScaleY((tmp = _acc_gScaleY())+1); return tmp; }
    inline float _acc_sScaleY$postInc()			{ CHCKTHIS; return _acc_sScaleYpostInc(); }
    inline float _acc_sScaleYpostDec()			{ float tmp; _acc_sScaleY((tmp = _acc_gScaleY())-1); return tmp; }
    inline float _acc_sScaleY$postDec()			{ CHCKTHIS; return _acc_sScaleYpostDec(); }
    inline float _acc_sScaleYpreInc()			{ return _acc_sScaleY(_acc_gScaleY()+1); }
    inline float _acc_sScaleY$preInc()			{ CHCKTHIS; return _acc_sScaleYpreInc(); }
    inline float _acc_sScaleYpreDec()			{ return _acc_sScaleY(_acc_gScaleY()-1); }
    inline float _acc_sScaleY$preDec()			{ CHCKTHIS; return _acc_sScaleYpreDec(); }
    inline float _acc_sScaleYAddEq(float value)	{ return _acc_sScaleY(_acc_gScaleY() + value); }
    inline float _acc_sScaleY$AddEq(float value)			{ CHCKTHIS; return _acc_sScaleYAddEq(value); }
    inline float _acc_sScaleYSubEq(float value)	{ return _acc_sScaleY(_acc_gScaleY() - value); }
    inline float _acc_sScaleY$SubEq(float value)			{ CHCKTHIS; return _acc_sScaleYSubEq(value); }
    inline float _acc_sScaleYMulEq(float value)	{ return _acc_sScaleY(_acc_gScaleY() * value); }
    inline float _acc_sScaleY$MulEq(float value)			{ CHCKTHIS; return _acc_sScaleYMulEq(value); }
    inline float _acc_sScaleYDivEq(float value)	{ return _acc_sScaleY(_acc_gScaleY() / value); }
    inline float _acc_sScaleY$DivEq(float value)			{ CHCKTHIS; return _acc_sScaleYDivEq(value); }
    inline float _acc_sScaleYModEq(float value)	{  float orig = _acc_gScaleY(); s32 tmp = (s32)(orig / value); return _acc_sScaleY(orig - (tmp * value)); }
    inline float _acc_sScaleY$ModEq(float value)			{ CHCKTHIS; return _acc_sScaleYModEq(value); }
    inline float _acc_sScale(float value);
    inline float _acc_sScale$(float value);
    inline float _acc_gRotation();
    inline float _acc_gRotation$();

    inline float _acc_sRotation(float value);
    inline float _acc_sRotation$(float value);
    inline float _acc_sRotationpostInc()			{ float tmp; _acc_sRotation((tmp = _acc_gRotation())+1); return tmp; }
    inline float _acc_sRotation$postInc()			{ CHCKTHIS; return _acc_sRotationpostInc(); }
    inline float _acc_sRotationpostDec()			{ float tmp; _acc_sRotation((tmp = _acc_gRotation())-1); return tmp; }
    inline float _acc_sRotation$postDec()			{ CHCKTHIS; return _acc_sRotationpostDec(); }
    inline float _acc_sRotationpreInc()			{ return _acc_sRotation(_acc_gRotation()+1); }
    inline float _acc_sRotation$preInc()			{ CHCKTHIS; return _acc_sRotationpreInc(); }
    inline float _acc_sRotationpreDec()			{ return _acc_sRotation(_acc_gRotation()-1); }
    inline float _acc_sRotation$preDec()			{ CHCKTHIS; return _acc_sRotationpreDec(); }
    inline float _acc_sRotationAddEq(float value)	{ return _acc_sRotation(_acc_gRotation() + value); }
    inline float _acc_sRotation$AddEq(float value)			{ CHCKTHIS; return _acc_sRotationAddEq(value); }
    inline float _acc_sRotationSubEq(float value)	{ return _acc_sRotation(_acc_gRotation() - value); }
    inline float _acc_sRotation$SubEq(float value)			{ CHCKTHIS; return _acc_sRotationSubEq(value); }
    inline float _acc_sRotationMulEq(float value)	{ return _acc_sRotation(_acc_gRotation() * value); }
    inline float _acc_sRotation$MulEq(float value)			{ CHCKTHIS; return _acc_sRotationMulEq(value); }
    inline float _acc_sRotationDivEq(float value)	{ return _acc_sRotation(_acc_gRotation() / value); }
    inline float _acc_sRotation$DivEq(float value)			{ CHCKTHIS; return _acc_sRotationDivEq(value); }
    inline float _acc_sRotationModEq(float value)	{  float orig = _acc_gRotation(); s32 tmp = (s32)(orig / value); return _acc_sRotation(orig - (tmp * value)); }
    inline float _acc_sRotation$ModEq(float value)			{ CHCKTHIS; return _acc_sRotationModEq(value); }
    inline float _acc_gX();
    inline float _acc_gX$();

    inline float _acc_sX(float value);
    inline float _acc_sX$(float value);
    inline float _acc_sXpostInc()			{ float tmp; _acc_sX((tmp = _acc_gX())+1); return tmp; }
    inline float _acc_sX$postInc()			{ CHCKTHIS; return _acc_sXpostInc(); }
    inline float _acc_sXpostDec()			{ float tmp; _acc_sX((tmp = _acc_gX())-1); return tmp; }
    inline float _acc_sX$postDec()			{ CHCKTHIS; return _acc_sXpostDec(); }
    inline float _acc_sXpreInc()			{ return _acc_sX(_acc_gX()+1); }
    inline float _acc_sX$preInc()			{ CHCKTHIS; return _acc_sXpreInc(); }
    inline float _acc_sXpreDec()			{ return _acc_sX(_acc_gX()-1); }
    inline float _acc_sX$preDec()			{ CHCKTHIS; return _acc_sXpreDec(); }
    inline float _acc_sXAddEq(float value)	{ return _acc_sX(_acc_gX() + value); }
    inline float _acc_sX$AddEq(float value)			{ CHCKTHIS; return _acc_sXAddEq(value); }
    inline float _acc_sXSubEq(float value)	{ return _acc_sX(_acc_gX() - value); }
    inline float _acc_sX$SubEq(float value)			{ CHCKTHIS; return _acc_sXSubEq(value); }
    inline float _acc_sXMulEq(float value)	{ return _acc_sX(_acc_gX() * value); }
    inline float _acc_sX$MulEq(float value)			{ CHCKTHIS; return _acc_sXMulEq(value); }
    inline float _acc_sXDivEq(float value)	{ return _acc_sX(_acc_gX() / value); }
    inline float _acc_sX$DivEq(float value)			{ CHCKTHIS; return _acc_sXDivEq(value); }
    inline float _acc_sXModEq(float value)	{  float orig = _acc_gX(); s32 tmp = (s32)(orig / value); return _acc_sX(orig - (tmp * value)); }
    inline float _acc_sX$ModEq(float value)			{ CHCKTHIS; return _acc_sXModEq(value); }
    inline float _acc_gY();
    inline float _acc_gY$();

    inline float _acc_sY(float value);
    inline float _acc_sY$(float value);
    inline float _acc_sYpostInc()			{ float tmp; _acc_sY((tmp = _acc_gY())+1); return tmp; }
    inline float _acc_sY$postInc()			{ CHCKTHIS; return _acc_sYpostInc(); }
    inline float _acc_sYpostDec()			{ float tmp; _acc_sY((tmp = _acc_gY())-1); return tmp; }
    inline float _acc_sY$postDec()			{ CHCKTHIS; return _acc_sYpostDec(); }
    inline float _acc_sYpreInc()			{ return _acc_sY(_acc_gY()+1); }
    inline float _acc_sY$preInc()			{ CHCKTHIS; return _acc_sYpreInc(); }
    inline float _acc_sYpreDec()			{ return _acc_sY(_acc_gY()-1); }
    inline float _acc_sY$preDec()			{ CHCKTHIS; return _acc_sYpreDec(); }
    inline float _acc_sYAddEq(float value)	{ return _acc_sY(_acc_gY() + value); }
    inline float _acc_sY$AddEq(float value)			{ CHCKTHIS; return _acc_sYAddEq(value); }
    inline float _acc_sYSubEq(float value)	{ return _acc_sY(_acc_gY() - value); }
    inline float _acc_sY$SubEq(float value)			{ CHCKTHIS; return _acc_sYSubEq(value); }
    inline float _acc_sYMulEq(float value)	{ return _acc_sY(_acc_gY() * value); }
    inline float _acc_sY$MulEq(float value)			{ CHCKTHIS; return _acc_sYMulEq(value); }
    inline float _acc_sYDivEq(float value)	{ return _acc_sY(_acc_gY() / value); }
    inline float _acc_sY$DivEq(float value)			{ CHCKTHIS; return _acc_sYDivEq(value); }
    inline float _acc_sYModEq(float value)	{  float orig = _acc_gY(); s32 tmp = (s32)(orig / value); return _acc_sY(orig - (tmp * value)); }
    inline float _acc_sY$ModEq(float value)			{ CHCKTHIS; return _acc_sYModEq(value); }
    inline bool _acc_gVisible();
    inline bool _acc_gVisible$();

    inline bool _acc_sVisible(bool value);
    inline bool _acc_sVisible$(bool value);
    inline System::String* _acc_gName();
    inline System::String* _acc_gName$();

    inline System::String* _acc_sName(System::String* value);
    inline System::String* _acc_sName$(System::String* value);
    static s32* _ext_node_getRoot();
    static s32* _ext_node_getChild(s32* pNode);
    static s32* _ext_node_getParent(s32* pNode);
    static s32* _ext_node_getBrother(s32* pNode);
    static s32* _ext_node_getNodeFromTask(s32* pTask);
    static float _ext_node_getNodeScaleX(s32* pNode);
    static float _ext_node_getNodeScaleY(s32* pNode);
    static float _ext_node_getRotation(s32* pNode);
    static float _ext_node_getNodeTranslateX(s32* pNode);
    static float _ext_node_getNodeTranslateY(s32* pNode);
    static s32* _ext_node_getName(s32* pNode);
    static void _ext_node_setName(s32* pNode,s32* name);
    static void _ext_node_setTranslate(s32* pNode,float x,float y);
    static void _ext_node_setRotation(s32* pNode,float deg);
    static void _ext_node_setScale(s32* pNode,float scaleX,float scaleY);
    static void _ext_node_getColorMatrixVec(s32* pNode,System::Array<float>* dst);
    static void _ext_node_setColorMatrixVec(s32* pNode,System::Array<float>* src);
    static u32 _ext_node_getColorMatrixUInt(s32* pNode);
    static void _ext_node_setColorMatrixUInt(s32* pNode,u32 val);
    static void _ext_node_setVisible(s32* pNode,bool visible);
    static bool _ext_node_getVisible(s32* pNode);
    static s32* _ext_node_asElement(s32* pNode);
    static s32* _ext_node_asContainer(s32* pNode);
    static s32* _ext_node_asSelectable(s32* pNode);
    static s32* _ext_node_asAnimationNode(s32* pNode);
    static s32* _ext_node_getUITask(s32* pNode);
    static s32* _ext_node_search(s32* pNode,s32* name);
    static s32* _ext_node_searchFirstByTypeID(s32* pNode,u32 typeID);
    NodeIterator();
    NodeIterator(u32 counter,s32* node);
    static s32* getRoot();
    static s32* getNodeFromTask(EnginePrototype::CKLBUITask* task);
    EnginePrototype::Element* getAsElement();
    inline EnginePrototype::Element* getAsElement$();
    EnginePrototype::Container* getAsContainer();
    inline EnginePrototype::Container* getAsContainer$();
    EnginePrototype::Selectable* getAsSelectable();
    inline EnginePrototype::Selectable* getAsSelectable$();
    EnginePrototype::AnimationNode* getAsAnimationNode();
    inline EnginePrototype::AnimationNode* getAsAnimationNode$();
    bool gotoChild(bool registerStack);
    inline bool gotoChild$(bool registerStack);
    bool gotoBrother(bool registerStack);
    inline bool gotoBrother$(bool registerStack);
    bool gotoParent(bool registerStack);
    inline bool gotoParent$(bool registerStack);
    bool rollback();
    inline bool rollback$();
    bool find(System::String* name,bool registerStack);
    inline bool find$(System::String* name,bool registerStack);
    EnginePrototype::CKLBUITask* getAsUITask();
    inline EnginePrototype::CKLBUITask* getAsUITask$();
    EnginePrototype::CKLBUITask* bindTask(EnginePrototype::CKLBUITask* task,System::String* name);
    inline EnginePrototype::CKLBUITask* bindTask$(EnginePrototype::CKLBUITask* task,System::String* name);
    void setXY(float x,float y);
    inline void setXY$(float x,float y);
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 100;
};
class EnginePrototype::Element : public System::Object {

public:
    enum ASSET_TYPE {
        NORMAL_ASSET = 0,
        DISABLED_ASSET = 1,
        FOCUSED_ASSET = 2,
        PUSHED_ASSET = 3,
        _ForceWORD_ASSET_TYPE = 0x7FFFFFFF
    };

    void _ctor_Element();
    s32* m_nodePtr;
    inline s32*& _gm_nodePtr$() { CHCKTHIS; return m_nodePtr; }
    inline s32* _sm_nodePtr$(s32* _$value) { CHCKTHIS; return m_nodePtr = _$value; }
    inline s32* _sm_nodePtr$AddEq(s32 value)		{ CHCKTHIS; return m_nodePtr += value; }
    inline s32* _sm_nodePtr$SubEq(s32 value)		{ CHCKTHIS; return m_nodePtr -= value; }
    inline s32* _sm_nodePtrAddEq(s32 value)		{ return m_nodePtr += value; }
    inline s32* _sm_nodePtrSubEq(s32 value)		{ return m_nodePtr -= value; }

    u32 m_counter;
    inline u32& _gm_counter$() { CHCKTHIS; return m_counter; }
    inline u32 _sm_counter$(u32 _$value) { CHCKTHIS; return m_counter = _$value; }
    inline u32 _sm_counter$postInc()				{ CHCKTHIS; return m_counter++; }
    inline u32 _sm_counter$postDec()				{ CHCKTHIS; return m_counter--; }
    inline u32 _sm_counter$preInc()				{ CHCKTHIS; return ++m_counter; }
    inline u32 _sm_counter$preDec()				{ CHCKTHIS; return --m_counter; }
    inline u32 _sm_counter$AddEq(u32 value)		{ CHCKTHIS; return m_counter += value; }
    inline u32 _sm_counter$SubEq(u32 value)		{ CHCKTHIS; return m_counter -= value; }
    inline u32 _sm_counter$MulEq(u32 value)		{ CHCKTHIS; return m_counter *= value; }
    inline u32 _sm_counter$DivEq(u32 value)		{ CHCKTHIS; if (value == 0) { THROWDIVZERO; }; ; return m_counter /= value; }
    inline u32 _sm_counter$ModEq(u32 value)		{ CHCKTHIS; if (value == 0) { THROWDIVZERO; }; ; return m_counter %= value; }
    inline u32 _sm_counter$XorEq(u32 value)		{ CHCKTHIS; return m_counter ^= value; }
    inline u32 _sm_counter$AndEq(u32 value)		{ CHCKTHIS; return m_counter &= value; }
    inline u32 _sm_counter$OrEq(u32 value)		{ CHCKTHIS; return m_counter |= value; }
    inline u32 _sm_counter$RShiftEq(u32 value)	{ CHCKTHIS; return m_counter >>= value; }
    inline u32 _sm_counter$LShiftEq(u32 value)	{ CHCKTHIS; return m_counter <<= value; }
    inline u32 _sm_counterpostInc()				{ return m_counter++; }
    inline u32 _sm_counterpostDec()				{ return m_counter--; }
    inline u32 _sm_counterpreInc()				{ return ++m_counter; }
    inline u32 _sm_counterpreDec()				{ return --m_counter; }
    inline u32 _sm_counterAddEq(u32 value)		{ return m_counter += value; }
    inline u32 _sm_counterSubEq(u32 value)		{ return m_counter -= value; }
    inline u32 _sm_counterMulEq(u32 value)		{ return m_counter *= value; }
    inline u32 _sm_counterDivEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return m_counter /= value; }
    inline u32 _sm_counterModEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return m_counter %= value; }
    inline u32 _sm_counterXorEq(u32 value)		{ return m_counter ^= value; }
    inline u32 _sm_counterAndEq(u32 value)		{ return m_counter &= value; }
    inline u32 _sm_counterOrEq(u32 value)			{ return m_counter |= value; }
    inline u32 _sm_counterRShiftEq(u32 value)		{ return m_counter >>= value; }
    inline u32 _sm_counterLShiftEq(u32 value)		{ return m_counter <<= value; }

    inline bool _acc_gEnabled();
    inline bool _acc_gEnabled$();

    inline bool _acc_sEnabled(bool value);
    inline bool _acc_sEnabled$(bool value);
    inline System::String* _acc_snormalAsset(System::String* value);
    inline System::String* _acc_snormalAsset$(System::String* value);
    inline System::String* _acc_sdisableAsset(System::String* value);
    inline System::String* _acc_sdisableAsset$(System::String* value);
    static void _ext_element_setEnabled(s32* pElem,bool isEnabled);
    static bool _ext_element_isEnabled(s32* pElem);
    static bool _ext_element_setAsset(s32* pElem,u32 dest,s32* assetName);
    static void _ext_element_setPriority(s32* pElem,u32 renderPriority);
    static u32 _ext_element_getPriority(s32* pElem);
    Element(u32 m_counter,s32* nodePtr);
    Element();
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 101;
};
class EnginePrototype::Container : public EnginePrototype::Element {

public:
    void _ctor_Container();
    inline s32 _acc_gViewOffsetX();
    inline s32 _acc_gViewOffsetX$();

    inline s32 _acc_sViewOffsetX(s32 value);
    inline s32 _acc_sViewOffsetX$(s32 value);
    inline s32 _acc_sViewOffsetXpostInc()			{ s32 tmp; _acc_sViewOffsetX((tmp = _acc_gViewOffsetX())+1); return tmp; }
    inline s32 _acc_sViewOffsetX$postInc()			{ CHCKTHIS; return _acc_sViewOffsetXpostInc(); }
    inline s32 _acc_sViewOffsetXpostDec()			{ s32 tmp; _acc_sViewOffsetX((tmp = _acc_gViewOffsetX())-1); return tmp; }
    inline s32 _acc_sViewOffsetX$postDec()			{ CHCKTHIS; return _acc_sViewOffsetXpostDec(); }
    inline s32 _acc_sViewOffsetXpreInc()			{ return _acc_sViewOffsetX(_acc_gViewOffsetX()+1); }
    inline s32 _acc_sViewOffsetX$preInc()			{ CHCKTHIS; return _acc_sViewOffsetXpreInc(); }
    inline s32 _acc_sViewOffsetXpreDec()			{ return _acc_sViewOffsetX(_acc_gViewOffsetX()-1); }
    inline s32 _acc_sViewOffsetX$preDec()			{ CHCKTHIS; return _acc_sViewOffsetXpreDec(); }
    inline s32 _acc_sViewOffsetXAddEq(s32 value)	{ return _acc_sViewOffsetX(_acc_gViewOffsetX() + value); }
    inline s32 _acc_sViewOffsetX$AddEq(s32 value)			{ CHCKTHIS; return _acc_sViewOffsetXAddEq(value); }
    inline s32 _acc_sViewOffsetXSubEq(s32 value)	{ return _acc_sViewOffsetX(_acc_gViewOffsetX() - value); }
    inline s32 _acc_sViewOffsetX$SubEq(s32 value)			{ CHCKTHIS; return _acc_sViewOffsetXSubEq(value); }
    inline s32 _acc_sViewOffsetXMulEq(s32 value)	{ return _acc_sViewOffsetX(_acc_gViewOffsetX() * value); }
    inline s32 _acc_sViewOffsetX$MulEq(s32 value)			{ CHCKTHIS; return _acc_sViewOffsetXMulEq(value); }
    inline s32 _acc_sViewOffsetXDivEq(s32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sViewOffsetX(_acc_gViewOffsetX() / value); }
    inline s32 _acc_sViewOffsetX$DivEq(s32 value)			{ CHCKTHIS; return _acc_sViewOffsetXDivEq(value); }
    inline s32 _acc_sViewOffsetXModEq(s32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sViewOffsetX(_acc_gViewOffsetX() % value); }
    inline s32 _acc_sViewOffsetX$ModEq(s32 value)			{ CHCKTHIS; return _acc_sViewOffsetXModEq(value); }
    inline s32 _acc_sViewOffsetXXorEq(s32 value)	{ return _acc_sViewOffsetX(_acc_gViewOffsetX() ^ value); }
    inline s32 _acc_sViewOffsetX$XorEq(s32 value)			{ CHCKTHIS; return _acc_sViewOffsetXXorEq(value); }
    inline s32 _acc_sViewOffsetXAndEq(s32 value)	{ return _acc_sViewOffsetX(_acc_gViewOffsetX() & value); }
    inline s32 _acc_sViewOffsetX$AndEq(s32 value)			{ CHCKTHIS; return _acc_sViewOffsetXAndEq(value); }
    inline s32 _acc_sViewOffsetXOrEq(s32 value)		{ return _acc_sViewOffsetX(_acc_gViewOffsetX() | value); }
    inline s32 _acc_sViewOffsetX$OrEq(s32 value)			{ CHCKTHIS; return _acc_sViewOffsetXOrEq(value); }
    inline s32 _acc_sViewOffsetXRShiftEq(s32 value)	{ return _acc_sViewOffsetX(_acc_gViewOffsetX() >> value); }
    inline s32 _acc_sViewOffsetX$RShiftEq(s32 value)			{ CHCKTHIS; return _acc_sViewOffsetXRShiftEq(value); }
    inline s32 _acc_sViewOffsetXLShiftEq(s32 value)	{ return _acc_sViewOffsetX(_acc_gViewOffsetX() << value); }
    inline s32 _acc_sViewOffsetX$LShiftEq(s32 value)			{ CHCKTHIS; return _acc_sViewOffsetXLShiftEq(value); }
    inline s32 _acc_gViewOffsetY();
    inline s32 _acc_gViewOffsetY$();

    inline s32 _acc_sViewOffsetY(s32 value);
    inline s32 _acc_sViewOffsetY$(s32 value);
    inline s32 _acc_sViewOffsetYpostInc()			{ s32 tmp; _acc_sViewOffsetY((tmp = _acc_gViewOffsetY())+1); return tmp; }
    inline s32 _acc_sViewOffsetY$postInc()			{ CHCKTHIS; return _acc_sViewOffsetYpostInc(); }
    inline s32 _acc_sViewOffsetYpostDec()			{ s32 tmp; _acc_sViewOffsetY((tmp = _acc_gViewOffsetY())-1); return tmp; }
    inline s32 _acc_sViewOffsetY$postDec()			{ CHCKTHIS; return _acc_sViewOffsetYpostDec(); }
    inline s32 _acc_sViewOffsetYpreInc()			{ return _acc_sViewOffsetY(_acc_gViewOffsetY()+1); }
    inline s32 _acc_sViewOffsetY$preInc()			{ CHCKTHIS; return _acc_sViewOffsetYpreInc(); }
    inline s32 _acc_sViewOffsetYpreDec()			{ return _acc_sViewOffsetY(_acc_gViewOffsetY()-1); }
    inline s32 _acc_sViewOffsetY$preDec()			{ CHCKTHIS; return _acc_sViewOffsetYpreDec(); }
    inline s32 _acc_sViewOffsetYAddEq(s32 value)	{ return _acc_sViewOffsetY(_acc_gViewOffsetY() + value); }
    inline s32 _acc_sViewOffsetY$AddEq(s32 value)			{ CHCKTHIS; return _acc_sViewOffsetYAddEq(value); }
    inline s32 _acc_sViewOffsetYSubEq(s32 value)	{ return _acc_sViewOffsetY(_acc_gViewOffsetY() - value); }
    inline s32 _acc_sViewOffsetY$SubEq(s32 value)			{ CHCKTHIS; return _acc_sViewOffsetYSubEq(value); }
    inline s32 _acc_sViewOffsetYMulEq(s32 value)	{ return _acc_sViewOffsetY(_acc_gViewOffsetY() * value); }
    inline s32 _acc_sViewOffsetY$MulEq(s32 value)			{ CHCKTHIS; return _acc_sViewOffsetYMulEq(value); }
    inline s32 _acc_sViewOffsetYDivEq(s32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sViewOffsetY(_acc_gViewOffsetY() / value); }
    inline s32 _acc_sViewOffsetY$DivEq(s32 value)			{ CHCKTHIS; return _acc_sViewOffsetYDivEq(value); }
    inline s32 _acc_sViewOffsetYModEq(s32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sViewOffsetY(_acc_gViewOffsetY() % value); }
    inline s32 _acc_sViewOffsetY$ModEq(s32 value)			{ CHCKTHIS; return _acc_sViewOffsetYModEq(value); }
    inline s32 _acc_sViewOffsetYXorEq(s32 value)	{ return _acc_sViewOffsetY(_acc_gViewOffsetY() ^ value); }
    inline s32 _acc_sViewOffsetY$XorEq(s32 value)			{ CHCKTHIS; return _acc_sViewOffsetYXorEq(value); }
    inline s32 _acc_sViewOffsetYAndEq(s32 value)	{ return _acc_sViewOffsetY(_acc_gViewOffsetY() & value); }
    inline s32 _acc_sViewOffsetY$AndEq(s32 value)			{ CHCKTHIS; return _acc_sViewOffsetYAndEq(value); }
    inline s32 _acc_sViewOffsetYOrEq(s32 value)		{ return _acc_sViewOffsetY(_acc_gViewOffsetY() | value); }
    inline s32 _acc_sViewOffsetY$OrEq(s32 value)			{ CHCKTHIS; return _acc_sViewOffsetYOrEq(value); }
    inline s32 _acc_sViewOffsetYRShiftEq(s32 value)	{ return _acc_sViewOffsetY(_acc_gViewOffsetY() >> value); }
    inline s32 _acc_sViewOffsetY$RShiftEq(s32 value)			{ CHCKTHIS; return _acc_sViewOffsetYRShiftEq(value); }
    inline s32 _acc_sViewOffsetYLShiftEq(s32 value)	{ return _acc_sViewOffsetY(_acc_gViewOffsetY() << value); }
    inline s32 _acc_sViewOffsetY$LShiftEq(s32 value)			{ CHCKTHIS; return _acc_sViewOffsetYLShiftEq(value); }
    inline u32 _acc_gRadioValue();
    inline u32 _acc_gRadioValue$();

    static s32 _ext_container_getViewOffsetX(s32* pCont);
    static void _ext_container_setViewOffsetX(s32* pCont,s32 scrollX);
    static s32 _ext_container_getViewOffsetY(s32* pCont);
    static void _ext_container_setViewOffsetY(s32* pCont,s32 scrollY);
    static u32 _ext_container_getRadioValue(s32* pCont);
    Container(u32 m_counter,s32* nodePtr);
    Container();
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 103;
};
class EnginePrototype::Selectable : public EnginePrototype::Element {

public:
    void _ctor_Selectable();
    inline System::String* _acc_spushedAsset(System::String* value);
    inline System::String* _acc_spushedAsset$(System::String* value);
    inline bool _acc_gisDown();
    inline bool _acc_gisDown$();

    inline bool _acc_sisDown(bool value);
    inline bool _acc_sisDown$(bool value);
    inline bool _acc_gcheckBoxMode();
    inline bool _acc_gcheckBoxMode$();

    inline bool _acc_scheckBoxMode(bool value);
    inline bool _acc_scheckBoxMode$(bool value);
    inline u32 _acc_gRadioID();
    inline u32 _acc_gRadioID$();

    inline u32 _acc_sRadioID(u32 value);
    inline u32 _acc_sRadioID$(u32 value);
    inline u32 _acc_sRadioIDpostInc()			{ u32 tmp; _acc_sRadioID((tmp = _acc_gRadioID())+1); return tmp; }
    inline u32 _acc_sRadioID$postInc()			{ CHCKTHIS; return _acc_sRadioIDpostInc(); }
    inline u32 _acc_sRadioIDpostDec()			{ u32 tmp; _acc_sRadioID((tmp = _acc_gRadioID())-1); return tmp; }
    inline u32 _acc_sRadioID$postDec()			{ CHCKTHIS; return _acc_sRadioIDpostDec(); }
    inline u32 _acc_sRadioIDpreInc()			{ return _acc_sRadioID(_acc_gRadioID()+1); }
    inline u32 _acc_sRadioID$preInc()			{ CHCKTHIS; return _acc_sRadioIDpreInc(); }
    inline u32 _acc_sRadioIDpreDec()			{ return _acc_sRadioID(_acc_gRadioID()-1); }
    inline u32 _acc_sRadioID$preDec()			{ CHCKTHIS; return _acc_sRadioIDpreDec(); }
    inline u32 _acc_sRadioIDAddEq(u32 value)	{ return _acc_sRadioID(_acc_gRadioID() + value); }
    inline u32 _acc_sRadioID$AddEq(u32 value)			{ CHCKTHIS; return _acc_sRadioIDAddEq(value); }
    inline u32 _acc_sRadioIDSubEq(u32 value)	{ return _acc_sRadioID(_acc_gRadioID() - value); }
    inline u32 _acc_sRadioID$SubEq(u32 value)			{ CHCKTHIS; return _acc_sRadioIDSubEq(value); }
    inline u32 _acc_sRadioIDMulEq(u32 value)	{ return _acc_sRadioID(_acc_gRadioID() * value); }
    inline u32 _acc_sRadioID$MulEq(u32 value)			{ CHCKTHIS; return _acc_sRadioIDMulEq(value); }
    inline u32 _acc_sRadioIDDivEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sRadioID(_acc_gRadioID() / value); }
    inline u32 _acc_sRadioID$DivEq(u32 value)			{ CHCKTHIS; return _acc_sRadioIDDivEq(value); }
    inline u32 _acc_sRadioIDModEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sRadioID(_acc_gRadioID() % value); }
    inline u32 _acc_sRadioID$ModEq(u32 value)			{ CHCKTHIS; return _acc_sRadioIDModEq(value); }
    inline u32 _acc_sRadioIDXorEq(u32 value)	{ return _acc_sRadioID(_acc_gRadioID() ^ value); }
    inline u32 _acc_sRadioID$XorEq(u32 value)			{ CHCKTHIS; return _acc_sRadioIDXorEq(value); }
    inline u32 _acc_sRadioIDAndEq(u32 value)	{ return _acc_sRadioID(_acc_gRadioID() & value); }
    inline u32 _acc_sRadioID$AndEq(u32 value)			{ CHCKTHIS; return _acc_sRadioIDAndEq(value); }
    inline u32 _acc_sRadioIDOrEq(u32 value)		{ return _acc_sRadioID(_acc_gRadioID() | value); }
    inline u32 _acc_sRadioID$OrEq(u32 value)			{ CHCKTHIS; return _acc_sRadioIDOrEq(value); }
    inline u32 _acc_sRadioIDRShiftEq(u32 value)	{ return _acc_sRadioID(_acc_gRadioID() >> value); }
    inline u32 _acc_sRadioID$RShiftEq(u32 value)			{ CHCKTHIS; return _acc_sRadioIDRShiftEq(value); }
    inline u32 _acc_sRadioIDLShiftEq(u32 value)	{ return _acc_sRadioID(_acc_gRadioID() << value); }
    inline u32 _acc_sRadioID$LShiftEq(u32 value)			{ CHCKTHIS; return _acc_sRadioIDLShiftEq(value); }
    static void _ext_selectable_setClick(s32* pSelect,s32 coordinateX,s32 coordinateY,s32 width,s32 height);
    static bool _ext_selectable_setAudio(s32* pSelect,s32* assetAudio,u32 mode,float volume);
    static void _ext_selectable_setStick(s32* pSelect,bool isStickable);
    static bool _ext_selectable_isStickable(s32* pSelect);
    static void _ext_selectable_setSticked(s32* pSelect,bool isSticked);
    static bool _ext_selectable_isSticked(s32* pSelect);
    static void _ext_selectable_setRadio(s32* pSelect,u32 radioID);
    static u32 _ext_selectable_getRadioID(s32* pSelect);
    Selectable(u32 m_counter,s32* nodePtr);
    bool setAudio(System::String* assetName,u32 mode,float volume);
    inline bool setAudio$(System::String* assetName,u32 mode,float volume);
    void setClickArea(s32 x,s32 y,s32 width,s32 height);
    inline void setClickArea$(s32 x,s32 y,s32 width,s32 height);
    Selectable();
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 104;
};
class EnginePrototype::AnimationNode : public System::Object {

public:
    void _ctor_AnimationNode();
    s32* nodePtr;
    inline s32*& _gnodePtr$() { CHCKTHIS; return nodePtr; }
    inline s32* _snodePtr$(s32* _$value) { CHCKTHIS; return nodePtr = _$value; }
    inline s32* _snodePtr$AddEq(s32 value)		{ CHCKTHIS; return nodePtr += value; }
    inline s32* _snodePtr$SubEq(s32 value)		{ CHCKTHIS; return nodePtr -= value; }
    inline s32* _snodePtrAddEq(s32 value)		{ return nodePtr += value; }
    inline s32* _snodePtrSubEq(s32 value)		{ return nodePtr -= value; }

    u32 m_counter;
    inline u32& _gm_counter$() { CHCKTHIS; return m_counter; }
    inline u32 _sm_counter$(u32 _$value) { CHCKTHIS; return m_counter = _$value; }
    inline u32 _sm_counter$postInc()				{ CHCKTHIS; return m_counter++; }
    inline u32 _sm_counter$postDec()				{ CHCKTHIS; return m_counter--; }
    inline u32 _sm_counter$preInc()				{ CHCKTHIS; return ++m_counter; }
    inline u32 _sm_counter$preDec()				{ CHCKTHIS; return --m_counter; }
    inline u32 _sm_counter$AddEq(u32 value)		{ CHCKTHIS; return m_counter += value; }
    inline u32 _sm_counter$SubEq(u32 value)		{ CHCKTHIS; return m_counter -= value; }
    inline u32 _sm_counter$MulEq(u32 value)		{ CHCKTHIS; return m_counter *= value; }
    inline u32 _sm_counter$DivEq(u32 value)		{ CHCKTHIS; if (value == 0) { THROWDIVZERO; }; ; return m_counter /= value; }
    inline u32 _sm_counter$ModEq(u32 value)		{ CHCKTHIS; if (value == 0) { THROWDIVZERO; }; ; return m_counter %= value; }
    inline u32 _sm_counter$XorEq(u32 value)		{ CHCKTHIS; return m_counter ^= value; }
    inline u32 _sm_counter$AndEq(u32 value)		{ CHCKTHIS; return m_counter &= value; }
    inline u32 _sm_counter$OrEq(u32 value)		{ CHCKTHIS; return m_counter |= value; }
    inline u32 _sm_counter$RShiftEq(u32 value)	{ CHCKTHIS; return m_counter >>= value; }
    inline u32 _sm_counter$LShiftEq(u32 value)	{ CHCKTHIS; return m_counter <<= value; }
    inline u32 _sm_counterpostInc()				{ return m_counter++; }
    inline u32 _sm_counterpostDec()				{ return m_counter--; }
    inline u32 _sm_counterpreInc()				{ return ++m_counter; }
    inline u32 _sm_counterpreDec()				{ return --m_counter; }
    inline u32 _sm_counterAddEq(u32 value)		{ return m_counter += value; }
    inline u32 _sm_counterSubEq(u32 value)		{ return m_counter -= value; }
    inline u32 _sm_counterMulEq(u32 value)		{ return m_counter *= value; }
    inline u32 _sm_counterDivEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return m_counter /= value; }
    inline u32 _sm_counterModEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return m_counter %= value; }
    inline u32 _sm_counterXorEq(u32 value)		{ return m_counter ^= value; }
    inline u32 _sm_counterAndEq(u32 value)		{ return m_counter &= value; }
    inline u32 _sm_counterOrEq(u32 value)			{ return m_counter |= value; }
    inline u32 _sm_counterRShiftEq(u32 value)		{ return m_counter >>= value; }
    inline u32 _sm_counterLShiftEq(u32 value)		{ return m_counter <<= value; }

    AnimationNode(u32 m_counter,s32* nodePtr);
    void setAnimation(EnginePrototype::AnimationInfo* animationInfo);
    inline void setAnimation$(EnginePrototype::AnimationInfo* animationInfo);
    AnimationNode();
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 105;
};
struct EnginePrototype::Size : public System::__GCStruct {

public:
    void _ctor_Size();
    s32 width;
    inline s32& _gwidth$() { CHCKTHIS; return width; }
    inline s32 _swidth$(s32 _$value) { CHCKTHIS; return width = _$value; }
    inline s32 _swidth$postInc()				{ CHCKTHIS; return width++; }
    inline s32 _swidth$postDec()				{ CHCKTHIS; return width--; }
    inline s32 _swidth$preInc()				{ CHCKTHIS; return ++width; }
    inline s32 _swidth$preDec()				{ CHCKTHIS; return --width; }
    inline s32 _swidth$AddEq(s32 value)		{ CHCKTHIS; return width += value; }
    inline s32 _swidth$SubEq(s32 value)		{ CHCKTHIS; return width -= value; }
    inline s32 _swidth$MulEq(s32 value)		{ CHCKTHIS; return width *= value; }
    inline s32 _swidth$DivEq(s32 value)		{ CHCKTHIS; if (value == 0) { THROWDIVZERO; }; ; return width /= value; }
    inline s32 _swidth$ModEq(s32 value)		{ CHCKTHIS; if (value == 0) { THROWDIVZERO; }; ; return width %= value; }
    inline s32 _swidth$XorEq(s32 value)		{ CHCKTHIS; return width ^= value; }
    inline s32 _swidth$AndEq(s32 value)		{ CHCKTHIS; return width &= value; }
    inline s32 _swidth$OrEq(s32 value)		{ CHCKTHIS; return width |= value; }
    inline s32 _swidth$RShiftEq(s32 value)	{ CHCKTHIS; return width >>= value; }
    inline s32 _swidth$LShiftEq(s32 value)	{ CHCKTHIS; return width <<= value; }
    inline s32 _swidthpostInc()				{ return width++; }
    inline s32 _swidthpostDec()				{ return width--; }
    inline s32 _swidthpreInc()				{ return ++width; }
    inline s32 _swidthpreDec()				{ return --width; }
    inline s32 _swidthAddEq(s32 value)		{ return width += value; }
    inline s32 _swidthSubEq(s32 value)		{ return width -= value; }
    inline s32 _swidthMulEq(s32 value)		{ return width *= value; }
    inline s32 _swidthDivEq(s32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return width /= value; }
    inline s32 _swidthModEq(s32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return width %= value; }
    inline s32 _swidthXorEq(s32 value)		{ return width ^= value; }
    inline s32 _swidthAndEq(s32 value)		{ return width &= value; }
    inline s32 _swidthOrEq(s32 value)			{ return width |= value; }
    inline s32 _swidthRShiftEq(s32 value)		{ return width >>= value; }
    inline s32 _swidthLShiftEq(s32 value)		{ return width <<= value; }

    s32 height;
    inline s32& _gheight$() { CHCKTHIS; return height; }
    inline s32 _sheight$(s32 _$value) { CHCKTHIS; return height = _$value; }
    inline s32 _sheight$postInc()				{ CHCKTHIS; return height++; }
    inline s32 _sheight$postDec()				{ CHCKTHIS; return height--; }
    inline s32 _sheight$preInc()				{ CHCKTHIS; return ++height; }
    inline s32 _sheight$preDec()				{ CHCKTHIS; return --height; }
    inline s32 _sheight$AddEq(s32 value)		{ CHCKTHIS; return height += value; }
    inline s32 _sheight$SubEq(s32 value)		{ CHCKTHIS; return height -= value; }
    inline s32 _sheight$MulEq(s32 value)		{ CHCKTHIS; return height *= value; }
    inline s32 _sheight$DivEq(s32 value)		{ CHCKTHIS; if (value == 0) { THROWDIVZERO; }; ; return height /= value; }
    inline s32 _sheight$ModEq(s32 value)		{ CHCKTHIS; if (value == 0) { THROWDIVZERO; }; ; return height %= value; }
    inline s32 _sheight$XorEq(s32 value)		{ CHCKTHIS; return height ^= value; }
    inline s32 _sheight$AndEq(s32 value)		{ CHCKTHIS; return height &= value; }
    inline s32 _sheight$OrEq(s32 value)		{ CHCKTHIS; return height |= value; }
    inline s32 _sheight$RShiftEq(s32 value)	{ CHCKTHIS; return height >>= value; }
    inline s32 _sheight$LShiftEq(s32 value)	{ CHCKTHIS; return height <<= value; }
    inline s32 _sheightpostInc()				{ return height++; }
    inline s32 _sheightpostDec()				{ return height--; }
    inline s32 _sheightpreInc()				{ return ++height; }
    inline s32 _sheightpreDec()				{ return --height; }
    inline s32 _sheightAddEq(s32 value)		{ return height += value; }
    inline s32 _sheightSubEq(s32 value)		{ return height -= value; }
    inline s32 _sheightMulEq(s32 value)		{ return height *= value; }
    inline s32 _sheightDivEq(s32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return height /= value; }
    inline s32 _sheightModEq(s32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return height %= value; }
    inline s32 _sheightXorEq(s32 value)		{ return height ^= value; }
    inline s32 _sheightAndEq(s32 value)		{ return height &= value; }
    inline s32 _sheightOrEq(s32 value)			{ return height |= value; }
    inline s32 _sheightRShiftEq(s32 value)		{ return height >>= value; }
    inline s32 _sheightLShiftEq(s32 value)		{ return height <<= value; }

    Size();
    inline u32 _processGC();
    inline void _releaseGC();
    inline void* _RefSetValue(void* newStruct);
    virtual inline void _moveAlert(u32 offset);
    inline static Size& __registerByRef(Size& m);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_STRUCT | 106;
};
struct EnginePrototype::USize : public System::__GCStruct {

public:
    void _ctor_USize();
    u32 width;
    inline u32& _gwidth$() { CHCKTHIS; return width; }
    inline u32 _swidth$(u32 _$value) { CHCKTHIS; return width = _$value; }
    inline u32 _swidth$postInc()				{ CHCKTHIS; return width++; }
    inline u32 _swidth$postDec()				{ CHCKTHIS; return width--; }
    inline u32 _swidth$preInc()				{ CHCKTHIS; return ++width; }
    inline u32 _swidth$preDec()				{ CHCKTHIS; return --width; }
    inline u32 _swidth$AddEq(u32 value)		{ CHCKTHIS; return width += value; }
    inline u32 _swidth$SubEq(u32 value)		{ CHCKTHIS; return width -= value; }
    inline u32 _swidth$MulEq(u32 value)		{ CHCKTHIS; return width *= value; }
    inline u32 _swidth$DivEq(u32 value)		{ CHCKTHIS; if (value == 0) { THROWDIVZERO; }; ; return width /= value; }
    inline u32 _swidth$ModEq(u32 value)		{ CHCKTHIS; if (value == 0) { THROWDIVZERO; }; ; return width %= value; }
    inline u32 _swidth$XorEq(u32 value)		{ CHCKTHIS; return width ^= value; }
    inline u32 _swidth$AndEq(u32 value)		{ CHCKTHIS; return width &= value; }
    inline u32 _swidth$OrEq(u32 value)		{ CHCKTHIS; return width |= value; }
    inline u32 _swidth$RShiftEq(u32 value)	{ CHCKTHIS; return width >>= value; }
    inline u32 _swidth$LShiftEq(u32 value)	{ CHCKTHIS; return width <<= value; }
    inline u32 _swidthpostInc()				{ return width++; }
    inline u32 _swidthpostDec()				{ return width--; }
    inline u32 _swidthpreInc()				{ return ++width; }
    inline u32 _swidthpreDec()				{ return --width; }
    inline u32 _swidthAddEq(u32 value)		{ return width += value; }
    inline u32 _swidthSubEq(u32 value)		{ return width -= value; }
    inline u32 _swidthMulEq(u32 value)		{ return width *= value; }
    inline u32 _swidthDivEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return width /= value; }
    inline u32 _swidthModEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return width %= value; }
    inline u32 _swidthXorEq(u32 value)		{ return width ^= value; }
    inline u32 _swidthAndEq(u32 value)		{ return width &= value; }
    inline u32 _swidthOrEq(u32 value)			{ return width |= value; }
    inline u32 _swidthRShiftEq(u32 value)		{ return width >>= value; }
    inline u32 _swidthLShiftEq(u32 value)		{ return width <<= value; }

    u32 height;
    inline u32& _gheight$() { CHCKTHIS; return height; }
    inline u32 _sheight$(u32 _$value) { CHCKTHIS; return height = _$value; }
    inline u32 _sheight$postInc()				{ CHCKTHIS; return height++; }
    inline u32 _sheight$postDec()				{ CHCKTHIS; return height--; }
    inline u32 _sheight$preInc()				{ CHCKTHIS; return ++height; }
    inline u32 _sheight$preDec()				{ CHCKTHIS; return --height; }
    inline u32 _sheight$AddEq(u32 value)		{ CHCKTHIS; return height += value; }
    inline u32 _sheight$SubEq(u32 value)		{ CHCKTHIS; return height -= value; }
    inline u32 _sheight$MulEq(u32 value)		{ CHCKTHIS; return height *= value; }
    inline u32 _sheight$DivEq(u32 value)		{ CHCKTHIS; if (value == 0) { THROWDIVZERO; }; ; return height /= value; }
    inline u32 _sheight$ModEq(u32 value)		{ CHCKTHIS; if (value == 0) { THROWDIVZERO; }; ; return height %= value; }
    inline u32 _sheight$XorEq(u32 value)		{ CHCKTHIS; return height ^= value; }
    inline u32 _sheight$AndEq(u32 value)		{ CHCKTHIS; return height &= value; }
    inline u32 _sheight$OrEq(u32 value)		{ CHCKTHIS; return height |= value; }
    inline u32 _sheight$RShiftEq(u32 value)	{ CHCKTHIS; return height >>= value; }
    inline u32 _sheight$LShiftEq(u32 value)	{ CHCKTHIS; return height <<= value; }
    inline u32 _sheightpostInc()				{ return height++; }
    inline u32 _sheightpostDec()				{ return height--; }
    inline u32 _sheightpreInc()				{ return ++height; }
    inline u32 _sheightpreDec()				{ return --height; }
    inline u32 _sheightAddEq(u32 value)		{ return height += value; }
    inline u32 _sheightSubEq(u32 value)		{ return height -= value; }
    inline u32 _sheightMulEq(u32 value)		{ return height *= value; }
    inline u32 _sheightDivEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return height /= value; }
    inline u32 _sheightModEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return height %= value; }
    inline u32 _sheightXorEq(u32 value)		{ return height ^= value; }
    inline u32 _sheightAndEq(u32 value)		{ return height &= value; }
    inline u32 _sheightOrEq(u32 value)			{ return height |= value; }
    inline u32 _sheightRShiftEq(u32 value)		{ return height >>= value; }
    inline u32 _sheightLShiftEq(u32 value)		{ return height <<= value; }

    USize();
    inline u32 _processGC();
    inline void _releaseGC();
    inline void* _RefSetValue(void* newStruct);
    virtual inline void _moveAlert(u32 offset);
    inline static USize& __registerByRef(USize& m);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_STRUCT | 107;
};
struct EnginePrototype::FSize : public System::__GCStruct {

public:
    void _ctor_FSize();
    float width;
    inline float& _gwidth$() { CHCKTHIS; return width; }
    inline float _swidth$(float _$value) { CHCKTHIS; return width = _$value; }
    inline float _swidth$postInc()				{ CHCKTHIS; return width++; }
    inline float _swidth$postDec()				{ CHCKTHIS; return width--; }
    inline float _swidth$preInc()				{ CHCKTHIS; return ++width; }
    inline float _swidth$preDec()				{ CHCKTHIS; return --width; }
    inline float _swidth$AddEq(float value)		{ CHCKTHIS; return width += value; }
    inline float _swidth$SubEq(float value)		{ CHCKTHIS; return width -= value; }
    inline float _swidth$MulEq(float value)		{ CHCKTHIS; return width *= value; }
    inline float _swidth$DivEq(float value)		{ CHCKTHIS; ; return width /= value; }
    inline float _swidth$ModEq(float value)		{ CHCKTHIS; s32 tmp = ((s32)(width / value)); return width = width-(tmp*value); }
    inline float _swidthpostInc()				{ return width++; }
    inline float _swidthpostDec()				{ return width--; }
    inline float _swidthpreInc()				{ return ++width; }
    inline float _swidthpreDec()				{ return --width; }
    inline float _swidthAddEq(float value)		{ return width += value; }
    inline float _swidthSubEq(float value)		{ return width -= value; }
    inline float _swidthMulEq(float value)		{ return width *= value; }
    inline float _swidthDivEq(float value)		{ ; return width /= value; }
    inline float _swidthModEq(float value)		{ s32 tmp = ((s32)(width / value)); return width = width-(tmp*value); }

    float height;
    inline float& _gheight$() { CHCKTHIS; return height; }
    inline float _sheight$(float _$value) { CHCKTHIS; return height = _$value; }
    inline float _sheight$postInc()				{ CHCKTHIS; return height++; }
    inline float _sheight$postDec()				{ CHCKTHIS; return height--; }
    inline float _sheight$preInc()				{ CHCKTHIS; return ++height; }
    inline float _sheight$preDec()				{ CHCKTHIS; return --height; }
    inline float _sheight$AddEq(float value)		{ CHCKTHIS; return height += value; }
    inline float _sheight$SubEq(float value)		{ CHCKTHIS; return height -= value; }
    inline float _sheight$MulEq(float value)		{ CHCKTHIS; return height *= value; }
    inline float _sheight$DivEq(float value)		{ CHCKTHIS; ; return height /= value; }
    inline float _sheight$ModEq(float value)		{ CHCKTHIS; s32 tmp = ((s32)(height / value)); return height = height-(tmp*value); }
    inline float _sheightpostInc()				{ return height++; }
    inline float _sheightpostDec()				{ return height--; }
    inline float _sheightpreInc()				{ return ++height; }
    inline float _sheightpreDec()				{ return --height; }
    inline float _sheightAddEq(float value)		{ return height += value; }
    inline float _sheightSubEq(float value)		{ return height -= value; }
    inline float _sheightMulEq(float value)		{ return height *= value; }
    inline float _sheightDivEq(float value)		{ ; return height /= value; }
    inline float _sheightModEq(float value)		{ s32 tmp = ((s32)(height / value)); return height = height-(tmp*value); }

    FSize();
    inline u32 _processGC();
    inline void _releaseGC();
    inline void* _RefSetValue(void* newStruct);
    virtual inline void _moveAlert(u32 offset);
    inline static FSize& __registerByRef(FSize& m);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_STRUCT | 108;
};
class EnginePrototype::IClientRequest : public System::Object {

public:
    enum EVENT_TYPE {
        E_PAUSE,
        E_RESUME,
        E_TEXTCHANGE,
        E_URLJUMP,
        E_DIDSTARTLOADWEB,
        E_DIDLOADENDWEB,
        E_FAILEDLOADWEB,
        E_STORE_BAD_ITEMID,
        E_STORE_PURCHASHING,
        E_STORE_PURCHASHED,
        E_STORE_FAILED,
        E_STORE_RESTORE,
        E_STORE_RESTORE_FAILED,
        E_STORE_RESTORE_COMPLETED,
        E_STORE_GET_PRODUCTS,
        E_SOUND_STATE_PLAY,
        E_SOUND_STATE_STOP,
        E_SOUND_STATE_PAUSE,
        E_SOUND_STATE_INVALID_HANDLE,
        _ForceWORD_EVENT_TYPE = 0x7FFFFFFF
    };

    void _ctor_IClientRequest();
    IClientRequest();
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 109;
};
class EnginePrototype::__FrameworkUtils : public System::Object {

public:
    void _ctor___FrameworkUtils();
    static u32 _ext_Cpp_getClassIDByName(s32* name);
    static u32 GetClassIDByName(System::String* className);
    static u32 RegisterClass(System::String* className);
    __FrameworkUtils();
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 111;
};
class EnginePrototype::WrapperReg : public System::Object {

public:
    void _ctor_WrapperReg();
    s32 m_listSize;
    inline s32& _gm_listSize$() { CHCKTHIS; return m_listSize; }
    inline s32 _sm_listSize$(s32 _$value) { CHCKTHIS; return m_listSize = _$value; }
    inline s32 _sm_listSize$postInc()				{ CHCKTHIS; return m_listSize++; }
    inline s32 _sm_listSize$postDec()				{ CHCKTHIS; return m_listSize--; }
    inline s32 _sm_listSize$preInc()				{ CHCKTHIS; return ++m_listSize; }
    inline s32 _sm_listSize$preDec()				{ CHCKTHIS; return --m_listSize; }
    inline s32 _sm_listSize$AddEq(s32 value)		{ CHCKTHIS; return m_listSize += value; }
    inline s32 _sm_listSize$SubEq(s32 value)		{ CHCKTHIS; return m_listSize -= value; }
    inline s32 _sm_listSize$MulEq(s32 value)		{ CHCKTHIS; return m_listSize *= value; }
    inline s32 _sm_listSize$DivEq(s32 value)		{ CHCKTHIS; if (value == 0) { THROWDIVZERO; }; ; return m_listSize /= value; }
    inline s32 _sm_listSize$ModEq(s32 value)		{ CHCKTHIS; if (value == 0) { THROWDIVZERO; }; ; return m_listSize %= value; }
    inline s32 _sm_listSize$XorEq(s32 value)		{ CHCKTHIS; return m_listSize ^= value; }
    inline s32 _sm_listSize$AndEq(s32 value)		{ CHCKTHIS; return m_listSize &= value; }
    inline s32 _sm_listSize$OrEq(s32 value)		{ CHCKTHIS; return m_listSize |= value; }
    inline s32 _sm_listSize$RShiftEq(s32 value)	{ CHCKTHIS; return m_listSize >>= value; }
    inline s32 _sm_listSize$LShiftEq(s32 value)	{ CHCKTHIS; return m_listSize <<= value; }
    inline s32 _sm_listSizepostInc()				{ return m_listSize++; }
    inline s32 _sm_listSizepostDec()				{ return m_listSize--; }
    inline s32 _sm_listSizepreInc()				{ return ++m_listSize; }
    inline s32 _sm_listSizepreDec()				{ return --m_listSize; }
    inline s32 _sm_listSizeAddEq(s32 value)		{ return m_listSize += value; }
    inline s32 _sm_listSizeSubEq(s32 value)		{ return m_listSize -= value; }
    inline s32 _sm_listSizeMulEq(s32 value)		{ return m_listSize *= value; }
    inline s32 _sm_listSizeDivEq(s32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return m_listSize /= value; }
    inline s32 _sm_listSizeModEq(s32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return m_listSize %= value; }
    inline s32 _sm_listSizeXorEq(s32 value)		{ return m_listSize ^= value; }
    inline s32 _sm_listSizeAndEq(s32 value)		{ return m_listSize &= value; }
    inline s32 _sm_listSizeOrEq(s32 value)			{ return m_listSize |= value; }
    inline s32 _sm_listSizeRShiftEq(s32 value)		{ return m_listSize >>= value; }
    inline s32 _sm_listSizeLShiftEq(s32 value)		{ return m_listSize <<= value; }

    System::Array<EnginePrototype::GameObject*>* m_list;
    inline System::Array<EnginePrototype::GameObject*>*& _gm_list$() { CHCKTHIS; return m_list; }
    inline System::Array<EnginePrototype::GameObject*>* _sm_list(System::Array<EnginePrototype::GameObject*>* _$value);
    inline System::Array<EnginePrototype::GameObject*>* _sm_list$(System::Array<EnginePrototype::GameObject*>* _$value);

    System::Collections::Generic::List<u32>* m_freeHandlesList;
    inline System::Collections::Generic::List<u32>*& _gm_freeHandlesList$() { CHCKTHIS; return m_freeHandlesList; }
    inline System::Collections::Generic::List<u32>* _sm_freeHandlesList(System::Collections::Generic::List<u32>* _$value);
    inline System::Collections::Generic::List<u32>* _sm_freeHandlesList$(System::Collections::Generic::List<u32>* _$value);

    u32 m_objectCounter;
    inline u32& _gm_objectCounter$() { CHCKTHIS; return m_objectCounter; }
    inline u32 _sm_objectCounter$(u32 _$value) { CHCKTHIS; return m_objectCounter = _$value; }
    inline u32 _sm_objectCounter$postInc()				{ CHCKTHIS; return m_objectCounter++; }
    inline u32 _sm_objectCounter$postDec()				{ CHCKTHIS; return m_objectCounter--; }
    inline u32 _sm_objectCounter$preInc()				{ CHCKTHIS; return ++m_objectCounter; }
    inline u32 _sm_objectCounter$preDec()				{ CHCKTHIS; return --m_objectCounter; }
    inline u32 _sm_objectCounter$AddEq(u32 value)		{ CHCKTHIS; return m_objectCounter += value; }
    inline u32 _sm_objectCounter$SubEq(u32 value)		{ CHCKTHIS; return m_objectCounter -= value; }
    inline u32 _sm_objectCounter$MulEq(u32 value)		{ CHCKTHIS; return m_objectCounter *= value; }
    inline u32 _sm_objectCounter$DivEq(u32 value)		{ CHCKTHIS; if (value == 0) { THROWDIVZERO; }; ; return m_objectCounter /= value; }
    inline u32 _sm_objectCounter$ModEq(u32 value)		{ CHCKTHIS; if (value == 0) { THROWDIVZERO; }; ; return m_objectCounter %= value; }
    inline u32 _sm_objectCounter$XorEq(u32 value)		{ CHCKTHIS; return m_objectCounter ^= value; }
    inline u32 _sm_objectCounter$AndEq(u32 value)		{ CHCKTHIS; return m_objectCounter &= value; }
    inline u32 _sm_objectCounter$OrEq(u32 value)		{ CHCKTHIS; return m_objectCounter |= value; }
    inline u32 _sm_objectCounter$RShiftEq(u32 value)	{ CHCKTHIS; return m_objectCounter >>= value; }
    inline u32 _sm_objectCounter$LShiftEq(u32 value)	{ CHCKTHIS; return m_objectCounter <<= value; }
    inline u32 _sm_objectCounterpostInc()				{ return m_objectCounter++; }
    inline u32 _sm_objectCounterpostDec()				{ return m_objectCounter--; }
    inline u32 _sm_objectCounterpreInc()				{ return ++m_objectCounter; }
    inline u32 _sm_objectCounterpreDec()				{ return --m_objectCounter; }
    inline u32 _sm_objectCounterAddEq(u32 value)		{ return m_objectCounter += value; }
    inline u32 _sm_objectCounterSubEq(u32 value)		{ return m_objectCounter -= value; }
    inline u32 _sm_objectCounterMulEq(u32 value)		{ return m_objectCounter *= value; }
    inline u32 _sm_objectCounterDivEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return m_objectCounter /= value; }
    inline u32 _sm_objectCounterModEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return m_objectCounter %= value; }
    inline u32 _sm_objectCounterXorEq(u32 value)		{ return m_objectCounter ^= value; }
    inline u32 _sm_objectCounterAndEq(u32 value)		{ return m_objectCounter &= value; }
    inline u32 _sm_objectCounterOrEq(u32 value)			{ return m_objectCounter |= value; }
    inline u32 _sm_objectCounterRShiftEq(u32 value)		{ return m_objectCounter >>= value; }
    inline u32 _sm_objectCounterLShiftEq(u32 value)		{ return m_objectCounter <<= value; }

    static EnginePrototype::WrapperReg* reg;
    inline static EnginePrototype::WrapperReg* _sreg(EnginePrototype::WrapperReg* _$value);

    WrapperReg();
    static EnginePrototype::WrapperReg* getInstance();
    u32 registerGameObject(EnginePrototype::GameObject* pObj);
    inline u32 registerGameObject$(EnginePrototype::GameObject* pObj);
    void unregisterGameObject(EnginePrototype::GameObject* pObj);
    inline void unregisterGameObject$(EnginePrototype::GameObject* pObj);
    EnginePrototype::GameObject* getObjectFromHandle(u32 handle);
    inline EnginePrototype::GameObject* getObjectFromHandle$(u32 handle);
    void display();
    inline void display$();
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 113;
};
class EnginePrototype::CSAPP : public System::Object {

public:
    enum APP_TYPE {
        APP_MAIL,
        APP_BROWSER,
        _ForceWORD_APP_TYPE = 0x7FFFFFFF
    };

    void _ctor_CSAPP();
    static bool _ext_CKLBLuaLibAPP_callApplication(s32 type,s32* addr,s32* subject,s32* body);
    static bool callApplication(s32 type,System::String* addr,System::String* subject,System::String* body);
    CSAPP();
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 114;
};
class EnginePrototype::CSAsset : public System::Object {

public:
    void _ctor_CSAsset();
    static void _ext_CKLBLuaLibASSET_getImageSize(s32* assetName,s32& returnWidth,s32& returnHeight);
    static void _ext_CKLBLuaLibASSET_getBoundSize(s32* assetName,float& returnWidth,float& returnHeight);
    static void _ext_CKLBLuaLibASSET_getAssetInfo(s32* assetName,s32& returnImgWidth,s32& returnImgHeight,float& returnBoundWidth,float& returnBoundHeight);
    static void getImageSize(System::String* assetPath,s32& width,s32& height);
    static void getImageSize(System::String* assetPath,EnginePrototype::Size& size);
    static void getBoundSize(System::String* assetPath,float& width,float& height);
    static void getBoundSize(System::String* assetPath,EnginePrototype::FSize& size);
    static void getAssetInfo(System::String* assetPath,s32& imgWidth,s32& imgHeight,float& boundWidth,float& boundHeight);
    static void getAssetInfo(System::String* assetPath,EnginePrototype::Size& imgSize,EnginePrototype::FSize& boundSize);
    CSAsset();
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 116;
};
class EnginePrototype::CSBin : public EnginePrototype::GameObject {

public:
    void _ctor_CSBin();
    static u32 s_classID;
    inline static u32 _ss_classIDDivEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID /= value; }
    inline static u32 _ss_classIDModEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID %= value; }

    static s32* _ext_CKLBLuaLibBIN_open(s32* bin_asset);
    static void _ext_CKLBLuaLibBIN_close(s32* pBIN);
    static bool _ext_CKLBLuaLibBIN_peek(s32* pBIN,s32 offset,s32& value);
    static bool _ext_CKLBLuaLibBIN_peek_u16(s32* pBIN,s32 offset,u32& value,bool f_bigendian);
    static bool _ext_CKLBLuaLibBIN_peek_u32(s32* pBIN,s32 offset,u32& value,bool f_bigendian);
    CSBin(System::String* bin_asset);
    virtual void clearInternals();
    inline void clearInternals$();
    bool peek(s32 offset,s32& value);
    inline bool peek$(s32 offset,s32& value);
    bool peek_u16(s32 offset,u32& value,bool f_bigendian);
    inline bool peek_u16$(s32 offset,u32& value,bool f_bigendian);
    bool peek_u32(s32 offset,u32& value,bool f_bigendian);
    inline bool peek_u32$(s32 offset,u32& value,bool f_bigendian);
    CSBin();
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 117;
};
class EnginePrototype::CSData : public EnginePrototype::GameObject {

public:
    void _ctor_CSData();
    static u32 s_classID;
    inline static u32 _ss_classIDDivEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID /= value; }
    inline static u32 _ss_classIDModEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID %= value; }

    static s32* _ext_CKLBLuaLibDATA_cmdCreateData(u32 dataSetID);
    static bool _ext_CKLBLuaLibDATA_cmdRegistData(s32* pDataSet,s32* nameAsset,u32& pReturnHandle);
    static void _ext_CKLBLuaLibDATA_cmdDelete(s32* pDataSet);
    CSData(u32 ID);
    bool registerData(System::String* nameAsset,u32& pReturnHandle);
    inline bool registerData$(System::String* nameAsset,u32& pReturnHandle);
    virtual void clearInternals();
    inline void clearInternals$();
    CSData();
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 118;
};
class EnginePrototype::CSDB : public EnginePrototype::GameObject {

public:
    void _ctor_CSDB();
    static u32 s_classID;
    inline static u32 _ss_classIDDivEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID /= value; }
    inline static u32 _ss_classIDModEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID %= value; }

    bool m_isWritable;
    inline bool& _gm_isWritable$() { CHCKTHIS; return m_isWritable; }
    inline bool _sm_isWritable$(bool _$value) { CHCKTHIS; return m_isWritable = _$value; }

    bool m_isCreatable;
    inline bool& _gm_isCreatable$() { CHCKTHIS; return m_isCreatable; }
    inline bool _sm_isCreatable$(bool _$value) { CHCKTHIS; return m_isCreatable = _$value; }

    inline bool _acc_gIsWritable();
    inline bool _acc_gIsWritable$();

    inline bool _acc_gIsCreatable();
    inline bool _acc_gIsCreatable$();

    static s32* _ext_CKLBLuaLibDB_dbopen(s32* db_asset,bool b_write,bool b_create);
    static void _ext_CKLBLuaLibDB_dbclose(s32* pDB);
    static void _ext_CKLBLuaLibDB_closeAll();
    static s32* _ext_CKLBLuaLibDB_query(s32* pDB,s32* sqlQuery,s32& nbEntries);
    CSDB(System::String* db_asset,bool b_write,bool b_create);
    virtual void clearInternals();
    inline void clearInternals$();
    static void closeAll();
    void _ref_query(System::String* sqlQuery,System::Array<System::String*>*& results);
    inline void query$(System::String* sqlQuery,System::Array<System::String*>*& results);
    inline void query(System::String* sqlQuery,System::Array<System::String*>*& results);
    CSDB();
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 119;
};
class EnginePrototype::CSDebug : public System::Object {

public:
    enum ESECTION_TYPE {
        M_SWITCH = 0,
        M_NUMBER = 1,
        M_SELECT = 2,
        _ForceWORD_ESECTION_TYPE = 0x7FFFFFFF
    };

    void _ctor_CSDebug();
    static bool s_isBuildingMenu;

    static void _ext_CKLBLuaLibDEBUG_startMenu(u32 maxCount,s32* caption,s32* key);
    static void _ext_CKLBLuaLibDEBUG_addItem(u32 mode,s32* caption,s32* key,s32 min,s32 max,s32 value,System::Array<s32*>* items,u32 itemsCount);
    static void _ext_CKLBLuaLibDEBUG_endMenu();
    static void _ext_CKLBLuaLibDEBUG_removeMenu(s32* key);
    static void setCallback();
    static void startMenu(u32 maxCount,System::String* caption,System::String* key);
    static void addItemSwitch(System::String* itemName,System::String* itemKey,bool defaultValue);
    static void addItemSelect(System::String* itemName,System::String* itemKey,System::String* defaultValue,System::Array<System::String*>* items);
    static void addItemNumber(System::String* itemName,System::String* itemKey,s32 lowerLimit,s32 upperLimit,s32 defaultValue);
    static void endMenu();
    static void removeMenu(System::String* key);
    CSDebug();
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 120;
};
class EnginePrototype::CSEng : public System::Object {

public:
    void _ctor_CSEng();
    static inline bool _acc_gIsRelease();
    static inline System::String* _acc_gPlatform();
    static inline u32 _acc_gFrameId();
    static bool _ext_CKLBLuaLibENG_isRelease();
    static s32* _ext_CKLBLuaLibENG_getPlatform();
    static void _ext_CKLBLuaLibENG_getNanoTime(s32& milli,s32& nano);
    static void _ext_CKLBLuaLibENG_startNanoTime(s32 idx);
    static void _ext_CKLBLuaLibENG_endNanoTime(s32 idx,s32& milli,s32& nano);
    static u32 _ext_CKLBLuaLibENG_getFrameID();
    static void getNanoTime(s32& milli,s32& nano);
    static void startNanoTime(s32 idx);
    static void endNanoTime(s32 idx,s32& milli,s32& nano);
    CSEng();
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 122;
};
class EnginePrototype::CSFont : public EnginePrototype::GameObject {
friend struct STextInfo_inner0;

public:
    void _ctor_CSFont();
    static u32 s_classID;
    inline static u32 _ss_classIDDivEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID /= value; }
    inline static u32 _ss_classIDModEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID %= value; }

    u32 m_size;
    inline u32& _gm_size$() { CHCKTHIS; return m_size; }
    inline u32 _sm_size$(u32 _$value) { CHCKTHIS; return m_size = _$value; }
    inline u32 _sm_size$postInc()				{ CHCKTHIS; return m_size++; }
    inline u32 _sm_size$postDec()				{ CHCKTHIS; return m_size--; }
    inline u32 _sm_size$preInc()				{ CHCKTHIS; return ++m_size; }
    inline u32 _sm_size$preDec()				{ CHCKTHIS; return --m_size; }
    inline u32 _sm_size$AddEq(u32 value)		{ CHCKTHIS; return m_size += value; }
    inline u32 _sm_size$SubEq(u32 value)		{ CHCKTHIS; return m_size -= value; }
    inline u32 _sm_size$MulEq(u32 value)		{ CHCKTHIS; return m_size *= value; }
    inline u32 _sm_size$DivEq(u32 value)		{ CHCKTHIS; if (value == 0) { THROWDIVZERO; }; ; return m_size /= value; }
    inline u32 _sm_size$ModEq(u32 value)		{ CHCKTHIS; if (value == 0) { THROWDIVZERO; }; ; return m_size %= value; }
    inline u32 _sm_size$XorEq(u32 value)		{ CHCKTHIS; return m_size ^= value; }
    inline u32 _sm_size$AndEq(u32 value)		{ CHCKTHIS; return m_size &= value; }
    inline u32 _sm_size$OrEq(u32 value)		{ CHCKTHIS; return m_size |= value; }
    inline u32 _sm_size$RShiftEq(u32 value)	{ CHCKTHIS; return m_size >>= value; }
    inline u32 _sm_size$LShiftEq(u32 value)	{ CHCKTHIS; return m_size <<= value; }
    inline u32 _sm_sizepostInc()				{ return m_size++; }
    inline u32 _sm_sizepostDec()				{ return m_size--; }
    inline u32 _sm_sizepreInc()				{ return ++m_size; }
    inline u32 _sm_sizepreDec()				{ return --m_size; }
    inline u32 _sm_sizeAddEq(u32 value)		{ return m_size += value; }
    inline u32 _sm_sizeSubEq(u32 value)		{ return m_size -= value; }
    inline u32 _sm_sizeMulEq(u32 value)		{ return m_size *= value; }
    inline u32 _sm_sizeDivEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return m_size /= value; }
    inline u32 _sm_sizeModEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return m_size %= value; }
    inline u32 _sm_sizeXorEq(u32 value)		{ return m_size ^= value; }
    inline u32 _sm_sizeAndEq(u32 value)		{ return m_size &= value; }
    inline u32 _sm_sizeOrEq(u32 value)			{ return m_size |= value; }
    inline u32 _sm_sizeRShiftEq(u32 value)		{ return m_size >>= value; }
    inline u32 _sm_sizeLShiftEq(u32 value)		{ return m_size <<= value; }

    System::String* m_name;
    inline System::String*& _gm_name$() { CHCKTHIS; return m_name; }
    inline System::String* _sm_name(System::String* _$value);
    inline System::String* _sm_name$(System::String* _$value);

    inline u32 _acc_gSize();
    inline u32 _acc_gSize$();

    inline u32 _acc_sSize(u32 value);
    inline u32 _acc_sSize$(u32 value);
    inline u32 _acc_sSizepostInc()			{ u32 tmp; _acc_sSize((tmp = _acc_gSize())+1); return tmp; }
    inline u32 _acc_sSize$postInc()			{ CHCKTHIS; return _acc_sSizepostInc(); }
    inline u32 _acc_sSizepostDec()			{ u32 tmp; _acc_sSize((tmp = _acc_gSize())-1); return tmp; }
    inline u32 _acc_sSize$postDec()			{ CHCKTHIS; return _acc_sSizepostDec(); }
    inline u32 _acc_sSizepreInc()			{ return _acc_sSize(_acc_gSize()+1); }
    inline u32 _acc_sSize$preInc()			{ CHCKTHIS; return _acc_sSizepreInc(); }
    inline u32 _acc_sSizepreDec()			{ return _acc_sSize(_acc_gSize()-1); }
    inline u32 _acc_sSize$preDec()			{ CHCKTHIS; return _acc_sSizepreDec(); }
    inline u32 _acc_sSizeAddEq(u32 value)	{ return _acc_sSize(_acc_gSize() + value); }
    inline u32 _acc_sSize$AddEq(u32 value)			{ CHCKTHIS; return _acc_sSizeAddEq(value); }
    inline u32 _acc_sSizeSubEq(u32 value)	{ return _acc_sSize(_acc_gSize() - value); }
    inline u32 _acc_sSize$SubEq(u32 value)			{ CHCKTHIS; return _acc_sSizeSubEq(value); }
    inline u32 _acc_sSizeMulEq(u32 value)	{ return _acc_sSize(_acc_gSize() * value); }
    inline u32 _acc_sSize$MulEq(u32 value)			{ CHCKTHIS; return _acc_sSizeMulEq(value); }
    inline u32 _acc_sSizeDivEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sSize(_acc_gSize() / value); }
    inline u32 _acc_sSize$DivEq(u32 value)			{ CHCKTHIS; return _acc_sSizeDivEq(value); }
    inline u32 _acc_sSizeModEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sSize(_acc_gSize() % value); }
    inline u32 _acc_sSize$ModEq(u32 value)			{ CHCKTHIS; return _acc_sSizeModEq(value); }
    inline u32 _acc_sSizeXorEq(u32 value)	{ return _acc_sSize(_acc_gSize() ^ value); }
    inline u32 _acc_sSize$XorEq(u32 value)			{ CHCKTHIS; return _acc_sSizeXorEq(value); }
    inline u32 _acc_sSizeAndEq(u32 value)	{ return _acc_sSize(_acc_gSize() & value); }
    inline u32 _acc_sSize$AndEq(u32 value)			{ CHCKTHIS; return _acc_sSizeAndEq(value); }
    inline u32 _acc_sSizeOrEq(u32 value)		{ return _acc_sSize(_acc_gSize() | value); }
    inline u32 _acc_sSize$OrEq(u32 value)			{ CHCKTHIS; return _acc_sSizeOrEq(value); }
    inline u32 _acc_sSizeRShiftEq(u32 value)	{ return _acc_sSize(_acc_gSize() >> value); }
    inline u32 _acc_sSize$RShiftEq(u32 value)			{ CHCKTHIS; return _acc_sSizeRShiftEq(value); }
    inline u32 _acc_sSizeLShiftEq(u32 value)	{ return _acc_sSize(_acc_gSize() << value); }
    inline u32 _acc_sSize$LShiftEq(u32 value)			{ CHCKTHIS; return _acc_sSizeLShiftEq(value); }
    inline System::String* _acc_gName();
    inline System::String* _acc_gName$();

    inline System::String* _acc_sName(System::String* value);
    inline System::String* _acc_sName$(System::String* value);
    static s32* _ext_CKLBLuaLibFONT_createFont(s32 size,s32* fontName);
    static void _ext_CKLBLuaLibFONT_removeFont(s32* font);
    static void _ext_CKLBLuaLibFONT_cmdGetTextInfo(s32* str,s32* font,EnginePrototype::STextInfo_inner0& outInfo);
    CSFont(u32 size,System::String* name);
    virtual void clearInternals();
    inline void clearInternals$();
    void getTextInfo(System::String* text,EnginePrototype::STextInfo_inner0& info);
    inline void getTextInfo$(System::String* text,EnginePrototype::STextInfo_inner0& info);
    CSFont();
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 123;
};
struct EnginePrototype::STextInfo_inner0 : public System::__GCStruct {

public:
    void _ctor_STextInfo_inner0();
    float width;
    inline float& _gwidth$() { CHCKTHIS; return width; }
    inline float _swidth$(float _$value) { CHCKTHIS; return width = _$value; }
    inline float _swidth$postInc()				{ CHCKTHIS; return width++; }
    inline float _swidth$postDec()				{ CHCKTHIS; return width--; }
    inline float _swidth$preInc()				{ CHCKTHIS; return ++width; }
    inline float _swidth$preDec()				{ CHCKTHIS; return --width; }
    inline float _swidth$AddEq(float value)		{ CHCKTHIS; return width += value; }
    inline float _swidth$SubEq(float value)		{ CHCKTHIS; return width -= value; }
    inline float _swidth$MulEq(float value)		{ CHCKTHIS; return width *= value; }
    inline float _swidth$DivEq(float value)		{ CHCKTHIS; ; return width /= value; }
    inline float _swidth$ModEq(float value)		{ CHCKTHIS; s32 tmp = ((s32)(width / value)); return width = width-(tmp*value); }
    inline float _swidthpostInc()				{ return width++; }
    inline float _swidthpostDec()				{ return width--; }
    inline float _swidthpreInc()				{ return ++width; }
    inline float _swidthpreDec()				{ return --width; }
    inline float _swidthAddEq(float value)		{ return width += value; }
    inline float _swidthSubEq(float value)		{ return width -= value; }
    inline float _swidthMulEq(float value)		{ return width *= value; }
    inline float _swidthDivEq(float value)		{ ; return width /= value; }
    inline float _swidthModEq(float value)		{ s32 tmp = ((s32)(width / value)); return width = width-(tmp*value); }

    float height;
    inline float& _gheight$() { CHCKTHIS; return height; }
    inline float _sheight$(float _$value) { CHCKTHIS; return height = _$value; }
    inline float _sheight$postInc()				{ CHCKTHIS; return height++; }
    inline float _sheight$postDec()				{ CHCKTHIS; return height--; }
    inline float _sheight$preInc()				{ CHCKTHIS; return ++height; }
    inline float _sheight$preDec()				{ CHCKTHIS; return --height; }
    inline float _sheight$AddEq(float value)		{ CHCKTHIS; return height += value; }
    inline float _sheight$SubEq(float value)		{ CHCKTHIS; return height -= value; }
    inline float _sheight$MulEq(float value)		{ CHCKTHIS; return height *= value; }
    inline float _sheight$DivEq(float value)		{ CHCKTHIS; ; return height /= value; }
    inline float _sheight$ModEq(float value)		{ CHCKTHIS; s32 tmp = ((s32)(height / value)); return height = height-(tmp*value); }
    inline float _sheightpostInc()				{ return height++; }
    inline float _sheightpostDec()				{ return height--; }
    inline float _sheightpreInc()				{ return ++height; }
    inline float _sheightpreDec()				{ return --height; }
    inline float _sheightAddEq(float value)		{ return height += value; }
    inline float _sheightSubEq(float value)		{ return height -= value; }
    inline float _sheightMulEq(float value)		{ return height *= value; }
    inline float _sheightDivEq(float value)		{ ; return height /= value; }
    inline float _sheightModEq(float value)		{ s32 tmp = ((s32)(height / value)); return height = height-(tmp*value); }

    float ascent;
    inline float& _gascent$() { CHCKTHIS; return ascent; }
    inline float _sascent$(float _$value) { CHCKTHIS; return ascent = _$value; }
    inline float _sascent$postInc()				{ CHCKTHIS; return ascent++; }
    inline float _sascent$postDec()				{ CHCKTHIS; return ascent--; }
    inline float _sascent$preInc()				{ CHCKTHIS; return ++ascent; }
    inline float _sascent$preDec()				{ CHCKTHIS; return --ascent; }
    inline float _sascent$AddEq(float value)		{ CHCKTHIS; return ascent += value; }
    inline float _sascent$SubEq(float value)		{ CHCKTHIS; return ascent -= value; }
    inline float _sascent$MulEq(float value)		{ CHCKTHIS; return ascent *= value; }
    inline float _sascent$DivEq(float value)		{ CHCKTHIS; ; return ascent /= value; }
    inline float _sascent$ModEq(float value)		{ CHCKTHIS; s32 tmp = ((s32)(ascent / value)); return ascent = ascent-(tmp*value); }
    inline float _sascentpostInc()				{ return ascent++; }
    inline float _sascentpostDec()				{ return ascent--; }
    inline float _sascentpreInc()				{ return ++ascent; }
    inline float _sascentpreDec()				{ return --ascent; }
    inline float _sascentAddEq(float value)		{ return ascent += value; }
    inline float _sascentSubEq(float value)		{ return ascent -= value; }
    inline float _sascentMulEq(float value)		{ return ascent *= value; }
    inline float _sascentDivEq(float value)		{ ; return ascent /= value; }
    inline float _sascentModEq(float value)		{ s32 tmp = ((s32)(ascent / value)); return ascent = ascent-(tmp*value); }

    float descent;
    inline float& _gdescent$() { CHCKTHIS; return descent; }
    inline float _sdescent$(float _$value) { CHCKTHIS; return descent = _$value; }
    inline float _sdescent$postInc()				{ CHCKTHIS; return descent++; }
    inline float _sdescent$postDec()				{ CHCKTHIS; return descent--; }
    inline float _sdescent$preInc()				{ CHCKTHIS; return ++descent; }
    inline float _sdescent$preDec()				{ CHCKTHIS; return --descent; }
    inline float _sdescent$AddEq(float value)		{ CHCKTHIS; return descent += value; }
    inline float _sdescent$SubEq(float value)		{ CHCKTHIS; return descent -= value; }
    inline float _sdescent$MulEq(float value)		{ CHCKTHIS; return descent *= value; }
    inline float _sdescent$DivEq(float value)		{ CHCKTHIS; ; return descent /= value; }
    inline float _sdescent$ModEq(float value)		{ CHCKTHIS; s32 tmp = ((s32)(descent / value)); return descent = descent-(tmp*value); }
    inline float _sdescentpostInc()				{ return descent++; }
    inline float _sdescentpostDec()				{ return descent--; }
    inline float _sdescentpreInc()				{ return ++descent; }
    inline float _sdescentpreDec()				{ return --descent; }
    inline float _sdescentAddEq(float value)		{ return descent += value; }
    inline float _sdescentSubEq(float value)		{ return descent -= value; }
    inline float _sdescentMulEq(float value)		{ return descent *= value; }
    inline float _sdescentDivEq(float value)		{ ; return descent /= value; }
    inline float _sdescentModEq(float value)		{ s32 tmp = ((s32)(descent / value)); return descent = descent-(tmp*value); }

    float top;
    inline float& _gtop$() { CHCKTHIS; return top; }
    inline float _stop$(float _$value) { CHCKTHIS; return top = _$value; }
    inline float _stop$postInc()				{ CHCKTHIS; return top++; }
    inline float _stop$postDec()				{ CHCKTHIS; return top--; }
    inline float _stop$preInc()				{ CHCKTHIS; return ++top; }
    inline float _stop$preDec()				{ CHCKTHIS; return --top; }
    inline float _stop$AddEq(float value)		{ CHCKTHIS; return top += value; }
    inline float _stop$SubEq(float value)		{ CHCKTHIS; return top -= value; }
    inline float _stop$MulEq(float value)		{ CHCKTHIS; return top *= value; }
    inline float _stop$DivEq(float value)		{ CHCKTHIS; ; return top /= value; }
    inline float _stop$ModEq(float value)		{ CHCKTHIS; s32 tmp = ((s32)(top / value)); return top = top-(tmp*value); }
    inline float _stoppostInc()				{ return top++; }
    inline float _stoppostDec()				{ return top--; }
    inline float _stoppreInc()				{ return ++top; }
    inline float _stoppreDec()				{ return --top; }
    inline float _stopAddEq(float value)		{ return top += value; }
    inline float _stopSubEq(float value)		{ return top -= value; }
    inline float _stopMulEq(float value)		{ return top *= value; }
    inline float _stopDivEq(float value)		{ ; return top /= value; }
    inline float _stopModEq(float value)		{ s32 tmp = ((s32)(top / value)); return top = top-(tmp*value); }

    float bottom;
    inline float& _gbottom$() { CHCKTHIS; return bottom; }
    inline float _sbottom$(float _$value) { CHCKTHIS; return bottom = _$value; }
    inline float _sbottom$postInc()				{ CHCKTHIS; return bottom++; }
    inline float _sbottom$postDec()				{ CHCKTHIS; return bottom--; }
    inline float _sbottom$preInc()				{ CHCKTHIS; return ++bottom; }
    inline float _sbottom$preDec()				{ CHCKTHIS; return --bottom; }
    inline float _sbottom$AddEq(float value)		{ CHCKTHIS; return bottom += value; }
    inline float _sbottom$SubEq(float value)		{ CHCKTHIS; return bottom -= value; }
    inline float _sbottom$MulEq(float value)		{ CHCKTHIS; return bottom *= value; }
    inline float _sbottom$DivEq(float value)		{ CHCKTHIS; ; return bottom /= value; }
    inline float _sbottom$ModEq(float value)		{ CHCKTHIS; s32 tmp = ((s32)(bottom / value)); return bottom = bottom-(tmp*value); }
    inline float _sbottompostInc()				{ return bottom++; }
    inline float _sbottompostDec()				{ return bottom--; }
    inline float _sbottompreInc()				{ return ++bottom; }
    inline float _sbottompreDec()				{ return --bottom; }
    inline float _sbottomAddEq(float value)		{ return bottom += value; }
    inline float _sbottomSubEq(float value)		{ return bottom -= value; }
    inline float _sbottomMulEq(float value)		{ return bottom *= value; }
    inline float _sbottomDivEq(float value)		{ ; return bottom /= value; }
    inline float _sbottomModEq(float value)		{ s32 tmp = ((s32)(bottom / value)); return bottom = bottom-(tmp*value); }

    STextInfo_inner0();
    inline u32 _processGC();
    inline void _releaseGC();
    inline void* _RefSetValue(void* newStruct);
    virtual inline void _moveAlert(u32 offset);
    inline static STextInfo_inner0& __registerByRef(STextInfo_inner0& m);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_STRUCT | 124;
};
class EnginePrototype::CSGL : public System::Object {

public:
    void _ctor_CSGL();
    static void _ext_CKLBLuaLibGL_GLClearColor(float r,float g,float b,float a);
    static void _ext_CKLBLuaLibGL_GLSetResolution(s32 width,s32 height);
    static bool _ext_CKLBLuaLibGL_GLCreateScreenAsset(s32* name);
    static bool _ext_CKLBLuaLibGL_GLDoScreenShot(s32* name);
    static void _ext_CKLBLuaLibGL_GLFreeScreenAsset(s32* name);
    static void _ext_CKLBLuaLibGL_SGGetGuardBand(float& leftBorder,float& rightBorder,float& topBorder,float& bottomBorder);
    static void _ext_CKLBLuaLibGL_SGSetGuardBand(float leftBorder,float rightBorder,float topBorder,float bottomBorder);
    static void clearColor(float r,float g,float b,float a);
    static void setResolution(s32 width,s32 height);
    static bool createScreenAsset(System::String* name);
    static bool doScreenShot(System::String* name);
    static void freeScreenAsset(System::String* name);
    static void getGuardBand(float& leftBorder,float& rightBorder,float& topBorder,float& bottomBorder);
    static void setGuardBand(float leftBorder,float rightBorder,float topBorder,float bottomBorder);
    CSGL();
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 126;
};
class EnginePrototype::CSKey : public System::Object {

public:
    void _ctor_CSKey();
    static s32 _ext_CKLBLuaLibKEY_genUserID(s32* userId,u32 bufSize);
    static s32 _ext_CKLBLuaLibKEY_genUserPW(s32* userId,s32* buf,u32 bufSize);
    static bool _ext_CKLBLuaLibKEY_setSecureID(s32* serviceName,s32* userId);
    static bool _ext_CKLBLuaLibKEY_setSecurePW(s32* serviceName,s32* passwd);
    static s32 _ext_CKLBLuaLibKEY_getSecureID(s32* serviceName,s32* buf,u32 bufSize);
    static s32 _ext_CKLBLuaLibKEY_getSecurePW(s32* serviceName,s32* buf,u32 bufSize);
    static bool _ext_CKLBLuaLibKEY_delSecureID(s32* serviceName);
    static bool _ext_CKLBLuaLibKEY_delSecurePW(s32* serviceName);
    static s32 _ref_genUserID(System::String*& userId,u32 bufSize);
    inline static s32 genUserID(System::String*& userId,u32 bufSize);
    static s32 _ref_genUserPW(System::String* userId,System::String*& passwd,u32 bufSize);
    inline static s32 genUserPW(System::String* userId,System::String*& passwd,u32 bufSize);
    static bool setSecureID(System::String* serviceName,System::String* userId);
    static bool setSecurePW(System::String* serviceName,System::String* passwd);
    static s32 _ref_getSecureID(System::String* serviceName,System::String*& secureID,u32 bufSize);
    inline static s32 getSecureID(System::String* serviceName,System::String*& secureID,u32 bufSize);
    static s32 _ref_getSecurePW(System::String* serviceName,System::String*& securePW,u32 bufSize);
    inline static s32 getSecurePW(System::String* serviceName,System::String*& securePW,u32 bufSize);
    static bool delSecureID(System::String* serviceName);
    static bool delSecurePW(System::String* serviceName);
    CSKey();
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 127;
};
class EnginePrototype::CSLang : public System::Object {

public:
    void _ctor_CSLang();
    static bool _ext_CKLBLuaLibLANG_addString(s32* id,s32* str);
    static s32* _ext_CKLBLuaLibLANG_getString(s32* id);
    static void _ext_CKLBLuaLibLANG_removeString(s32* id);
    static bool _ext_CKLBLuaLibLANG_useDB(s32* dbFile,s32* table,s32* keyF,s32* valueF,s32* groupF);
    static bool _ext_CKLBLuaLibLANG_loadGroup(s32* groupId);
    static bool addString(System::String* id,System::String* str);
    static System::String* getString(System::String* id);
    static void removeString(System::String* id);
    static bool useDB(System::String* dbFile,System::String* table,System::String* keyF,System::String* valueF,System::String* groupF);
    static bool loadGroup(System::String* groupId);
    CSLang();
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 128;
};
class EnginePrototype::CSMatrix : public System::Object ,public System::ICloneable {
friend class CSVector_inner1;

public:
    void _ctor_CSMatrix();
    static float EPSILON;
    inline static float _sEPSILONModEq(float value)		{ s32 tmp = ((s32)(EPSILON / value)); return EPSILON = EPSILON-(tmp*value); }

    System::Array<float>* m_matrix;
    inline System::Array<float>*& _gm_matrix$() { CHCKTHIS; return m_matrix; }
    inline System::Array<float>* _sm_matrix(System::Array<float>* _$value);
    inline System::Array<float>* _sm_matrix$(System::Array<float>* _$value);

    inline float _idx_g(s32 i, s32 j);
    inline float _idx_g$(s32 i, s32 j);

    CSMatrix(System::Array<float>* matrix);
    System::Object* Clone();
    inline System::Object* Clone$();
    EnginePrototype::CSMatrix* Copy();
    inline EnginePrototype::CSMatrix* Copy$();
    EnginePrototype::CSMatrix* Transposed();
    inline EnginePrototype::CSMatrix* Transposed$();
    EnginePrototype::CSMatrix* Mul(EnginePrototype::CSMatrix* mat);
    inline EnginePrototype::CSMatrix* Mul$(EnginePrototype::CSMatrix* mat);
    EnginePrototype::CSVector_inner1* Mul(EnginePrototype::CSVector_inner1* vect);
    inline EnginePrototype::CSVector_inner1* Mul$(EnginePrototype::CSVector_inner1* vect);
    static float fabs(float f);
    EnginePrototype::CSMatrix* Inverse();
    inline EnginePrototype::CSMatrix* Inverse$();
    CSMatrix();
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 129;
};
class EnginePrototype::CSVector_inner1 : public System::Object ,public System::ICloneable {

public:
    void _ctor_CSVector_inner1();
    System::Array<float>* m_vector;
    inline System::Array<float>*& _gm_vector$() { CHCKTHIS; return m_vector; }
    inline System::Array<float>* _sm_vector(System::Array<float>* _$value);
    inline System::Array<float>* _sm_vector$(System::Array<float>* _$value);

    inline float _idx_g(s32 i);
    inline float _idx_g$(s32 i);

    CSVector_inner1(System::Array<float>* vector);
    System::Object* Clone();
    inline System::Object* Clone$();
    CSVector_inner1();
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 130;
};
class EnginePrototype::CSRES : public System::Object {

public:
    void _ctor_CSRES();
    static void _ext_CKLBLuaLibRES_dumpSceneGraph(s32* task);
    static void _ext_CKLBLuaLibRES_dumpRendering(bool detailed);
    static void _ext_CKLBLuaLibRES_dumpAssets();
    static void _ext_CKLBLuaLibRES_dumpDataSet();
    static void _ext_CKLBLuaLibRES_dumpTexturePacker(bool detailed);
    static void _ext_CKLBLuaLibRES_dumpGeometryCost(bool detailed);
    static void dumpSceneGraph(EnginePrototype::CKLBUITask* task);
    static void dumpRendering(bool detailed);
    static void dumpAssets();
    static void dumpDataSet();
    static void dumpTexturePacker(bool detailed);
    static void dumpGeometryCost(bool detailed);
    CSRES();
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 132;
};
class EnginePrototype::CSSound : public EnginePrototype::GameObject {

public:
    enum EBUF_SIZE {
        SND_BUF_SMALL = 0,
        SND_BUF_MEDIUM = 1,
        SND_BUF_LARGE = 2,
        _ForceWORD_EBUF_SIZE = 0x7FFFFFFF
    };

    void _ctor_CSSound();
    static u32 s_classID;
    inline static u32 _ss_classIDDivEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID /= value; }
    inline static u32 _ss_classIDModEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID %= value; }

    s32 m_bufSize;
    inline s32& _gm_bufSize$() { CHCKTHIS; return m_bufSize; }
    inline s32 _sm_bufSize$(s32 _$value) { CHCKTHIS; return m_bufSize = _$value; }
    inline s32 _sm_bufSize$postInc()				{ CHCKTHIS; return (s32)(((s32&)m_bufSize)++); }
    inline s32 _sm_bufSize$postDec()				{ CHCKTHIS; return (s32)(((s32&)m_bufSize)--); }
    inline s32 _sm_bufSize$preInc()				{ CHCKTHIS; return (s32)(++(s32&)m_bufSize); }
    inline s32 _sm_bufSize$preDec()				{ CHCKTHIS; return (s32)(--(s32&)m_bufSize); }
    inline s32 _sm_bufSize$AddEq(s32 value)		{ CHCKTHIS; return (s32)((s32&)m_bufSize += value); }
    inline s32 _sm_bufSize$SubEq(s32 value)		{ CHCKTHIS; return (s32)((s32&)m_bufSize -= value); }
    inline s32 _sm_bufSizepostInc()				{ return (s32)(((s32&)m_bufSize)++); }
    inline s32 _sm_bufSizepostDec()				{ return (s32)(((s32&)m_bufSize)--); }
    inline s32 _sm_bufSizepreInc()				{ return (s32)(++(s32&)m_bufSize); }
    inline s32 _sm_bufSizepreDec()				{ return (s32)(--(s32&)m_bufSize); }
    inline s32 _sm_bufSizeAddEq(s32 value)		{ return (s32)((s32&)m_bufSize += value); }
    inline s32 _sm_bufSizeSubEq(s32 value)		{ return (s32)((s32&)m_bufSize -= value); }

    float m_volume;
    inline float& _gm_volume$() { CHCKTHIS; return m_volume; }
    inline float _sm_volume$(float _$value) { CHCKTHIS; return m_volume = _$value; }
    inline float _sm_volume$postInc()				{ CHCKTHIS; return m_volume++; }
    inline float _sm_volume$postDec()				{ CHCKTHIS; return m_volume--; }
    inline float _sm_volume$preInc()				{ CHCKTHIS; return ++m_volume; }
    inline float _sm_volume$preDec()				{ CHCKTHIS; return --m_volume; }
    inline float _sm_volume$AddEq(float value)		{ CHCKTHIS; return m_volume += value; }
    inline float _sm_volume$SubEq(float value)		{ CHCKTHIS; return m_volume -= value; }
    inline float _sm_volume$MulEq(float value)		{ CHCKTHIS; return m_volume *= value; }
    inline float _sm_volume$DivEq(float value)		{ CHCKTHIS; ; return m_volume /= value; }
    inline float _sm_volume$ModEq(float value)		{ CHCKTHIS; s32 tmp = ((s32)(m_volume / value)); return m_volume = m_volume-(tmp*value); }
    inline float _sm_volumepostInc()				{ return m_volume++; }
    inline float _sm_volumepostDec()				{ return m_volume--; }
    inline float _sm_volumepreInc()				{ return ++m_volume; }
    inline float _sm_volumepreDec()				{ return --m_volume; }
    inline float _sm_volumeAddEq(float value)		{ return m_volume += value; }
    inline float _sm_volumeSubEq(float value)		{ return m_volume -= value; }
    inline float _sm_volumeMulEq(float value)		{ return m_volume *= value; }
    inline float _sm_volumeDivEq(float value)		{ ; return m_volume /= value; }
    inline float _sm_volumeModEq(float value)		{ s32 tmp = ((s32)(m_volume / value)); return m_volume = m_volume-(tmp*value); }

    float m_pan;
    inline float& _gm_pan$() { CHCKTHIS; return m_pan; }
    inline float _sm_pan$(float _$value) { CHCKTHIS; return m_pan = _$value; }
    inline float _sm_pan$postInc()				{ CHCKTHIS; return m_pan++; }
    inline float _sm_pan$postDec()				{ CHCKTHIS; return m_pan--; }
    inline float _sm_pan$preInc()				{ CHCKTHIS; return ++m_pan; }
    inline float _sm_pan$preDec()				{ CHCKTHIS; return --m_pan; }
    inline float _sm_pan$AddEq(float value)		{ CHCKTHIS; return m_pan += value; }
    inline float _sm_pan$SubEq(float value)		{ CHCKTHIS; return m_pan -= value; }
    inline float _sm_pan$MulEq(float value)		{ CHCKTHIS; return m_pan *= value; }
    inline float _sm_pan$DivEq(float value)		{ CHCKTHIS; ; return m_pan /= value; }
    inline float _sm_pan$ModEq(float value)		{ CHCKTHIS; s32 tmp = ((s32)(m_pan / value)); return m_pan = m_pan-(tmp*value); }
    inline float _sm_panpostInc()				{ return m_pan++; }
    inline float _sm_panpostDec()				{ return m_pan--; }
    inline float _sm_panpreInc()				{ return ++m_pan; }
    inline float _sm_panpreDec()				{ return --m_pan; }
    inline float _sm_panAddEq(float value)		{ return m_pan += value; }
    inline float _sm_panSubEq(float value)		{ return m_pan -= value; }
    inline float _sm_panMulEq(float value)		{ return m_pan *= value; }
    inline float _sm_panDivEq(float value)		{ ; return m_pan /= value; }
    inline float _sm_panModEq(float value)		{ s32 tmp = ((s32)(m_pan / value)); return m_pan = m_pan-(tmp*value); }

    inline s32 _acc_gBufSize();
    inline s32 _acc_gBufSize$();

    inline float _acc_gVolume();
    inline float _acc_gVolume$();

    inline float _acc_sVolume(float value);
    inline float _acc_sVolume$(float value);
    inline float _acc_sVolumepostInc()			{ float tmp; _acc_sVolume((tmp = _acc_gVolume())+1); return tmp; }
    inline float _acc_sVolume$postInc()			{ CHCKTHIS; return _acc_sVolumepostInc(); }
    inline float _acc_sVolumepostDec()			{ float tmp; _acc_sVolume((tmp = _acc_gVolume())-1); return tmp; }
    inline float _acc_sVolume$postDec()			{ CHCKTHIS; return _acc_sVolumepostDec(); }
    inline float _acc_sVolumepreInc()			{ return _acc_sVolume(_acc_gVolume()+1); }
    inline float _acc_sVolume$preInc()			{ CHCKTHIS; return _acc_sVolumepreInc(); }
    inline float _acc_sVolumepreDec()			{ return _acc_sVolume(_acc_gVolume()-1); }
    inline float _acc_sVolume$preDec()			{ CHCKTHIS; return _acc_sVolumepreDec(); }
    inline float _acc_sVolumeAddEq(float value)	{ return _acc_sVolume(_acc_gVolume() + value); }
    inline float _acc_sVolume$AddEq(float value)			{ CHCKTHIS; return _acc_sVolumeAddEq(value); }
    inline float _acc_sVolumeSubEq(float value)	{ return _acc_sVolume(_acc_gVolume() - value); }
    inline float _acc_sVolume$SubEq(float value)			{ CHCKTHIS; return _acc_sVolumeSubEq(value); }
    inline float _acc_sVolumeMulEq(float value)	{ return _acc_sVolume(_acc_gVolume() * value); }
    inline float _acc_sVolume$MulEq(float value)			{ CHCKTHIS; return _acc_sVolumeMulEq(value); }
    inline float _acc_sVolumeDivEq(float value)	{ return _acc_sVolume(_acc_gVolume() / value); }
    inline float _acc_sVolume$DivEq(float value)			{ CHCKTHIS; return _acc_sVolumeDivEq(value); }
    inline float _acc_sVolumeModEq(float value)	{  float orig = _acc_gVolume(); s32 tmp = (s32)(orig / value); return _acc_sVolume(orig - (tmp * value)); }
    inline float _acc_sVolume$ModEq(float value)			{ CHCKTHIS; return _acc_sVolumeModEq(value); }
    inline float _acc_gPan();
    inline float _acc_gPan$();

    inline float _acc_sPan(float value);
    inline float _acc_sPan$(float value);
    inline float _acc_sPanpostInc()			{ float tmp; _acc_sPan((tmp = _acc_gPan())+1); return tmp; }
    inline float _acc_sPan$postInc()			{ CHCKTHIS; return _acc_sPanpostInc(); }
    inline float _acc_sPanpostDec()			{ float tmp; _acc_sPan((tmp = _acc_gPan())-1); return tmp; }
    inline float _acc_sPan$postDec()			{ CHCKTHIS; return _acc_sPanpostDec(); }
    inline float _acc_sPanpreInc()			{ return _acc_sPan(_acc_gPan()+1); }
    inline float _acc_sPan$preInc()			{ CHCKTHIS; return _acc_sPanpreInc(); }
    inline float _acc_sPanpreDec()			{ return _acc_sPan(_acc_gPan()-1); }
    inline float _acc_sPan$preDec()			{ CHCKTHIS; return _acc_sPanpreDec(); }
    inline float _acc_sPanAddEq(float value)	{ return _acc_sPan(_acc_gPan() + value); }
    inline float _acc_sPan$AddEq(float value)			{ CHCKTHIS; return _acc_sPanAddEq(value); }
    inline float _acc_sPanSubEq(float value)	{ return _acc_sPan(_acc_gPan() - value); }
    inline float _acc_sPan$SubEq(float value)			{ CHCKTHIS; return _acc_sPanSubEq(value); }
    inline float _acc_sPanMulEq(float value)	{ return _acc_sPan(_acc_gPan() * value); }
    inline float _acc_sPan$MulEq(float value)			{ CHCKTHIS; return _acc_sPanMulEq(value); }
    inline float _acc_sPanDivEq(float value)	{ return _acc_sPan(_acc_gPan() / value); }
    inline float _acc_sPan$DivEq(float value)			{ CHCKTHIS; return _acc_sPanDivEq(value); }
    inline float _acc_sPanModEq(float value)	{  float orig = _acc_gPan(); s32 tmp = (s32)(orig / value); return _acc_sPan(orig - (tmp * value)); }
    inline float _acc_sPan$ModEq(float value)			{ CHCKTHIS; return _acc_sPanModEq(value); }
    inline s32 _acc_gLength();
    inline s32 _acc_gLength$();

    static s32* _ext_CKLBLuaLibSOUND_cmdSoundOpen(s32* sndAsset,bool fBgm);
    static bool _ext_CKLBLuaLibSOUND_cmdSoundSetBufSize(s32* pSnd,s32 level);
    static void _ext_CKLBLuaLibSOUND_cmdSoundClose(s32* pSnd);
    static s32 _ext_CKLBLuaLibSOUND_removeSoundAll();
    static void _ext_CKLBLuaLibSOUND_cmdSoundPlay(s32* pSnd,u32 fade_msec,float tgtVol,float globalVol);
    static void _ext_CKLBLuaLibSOUND_cmdSoundStop(s32* pSnd,u32 fade_msec,float tgtVol);
    static void _ext_CKLBLuaLibSOUND_cmdSoundVolume(s32* pSnd,float volume);
    static void _ext_CKLBLuaLibSOUND_cmdSoundPan(s32* pSnd,float pan);
    static void _ext_CKLBLuaLibSOUND_cmdSoundPause(s32* pSnd);
    static void _ext_CKLBLuaLibSOUND_cmdSoundResume(s32* pSnd);
    static void _ext_CKLBLuaLibSOUND_cmdSoundSeek(s32* pSnd,s32 millisec);
    static s32 _ext_CKLBLuaLibSOUND_cmdSoundTell(s32* pSnd);
    static s32 _ext_CKLBLuaLibSOUND_cmdSoundState(s32* pSnd);
    static void _ext_CKLBLuaLibSOUND_cmdVolumeBGM(float volume);
    static void _ext_CKLBLuaLibSOUND_cmdVolumeSE(float volume);
    static s32 _ext_CKLBLuaLibSOUND_cmdGetLength(s32* pSnd);
    static void _ext_CKLBLuaLibSOUND_cmdSetFade(s32* pSnd,s32 millisec,float tgtVol);
    CSSound(System::String* sound_asset,bool bgmMode);
    bool setBufSize(s32 size);
    inline bool setBufSize$(s32 size);
    virtual void clearInternals();
    inline void clearInternals$();
    static void closeAll();
    void play(u32 fade_msec,float tgtVol,float globalVol);
    inline void play$(u32 fade_msec,float tgtVol,float globalVol);
    void stop(u32 fade_msec,float tgtVol);
    inline void stop$(u32 fade_msec,float tgtVol);
    void pause();
    inline void pause$();
    void resume();
    inline void resume$();
    void seek(s32 milliseconds);
    inline void seek$(s32 milliseconds);
    s32 tell();
    inline s32 tell$();
    s32 state();
    inline s32 state$();
    void setFade(s32 millisec,float tgtVol);
    inline void setFade$(s32 millisec,float tgtVol);
    static void volumeBGM(float volume);
    static void volumeSE(float volume);
    CSSound();
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 133;
};
class EnginePrototype::CSSystem : public System::Object {
friend struct SystemInfo_inner2;

public:
    void _ctor_CSSystem();
    static void _ext_CKLBLuaEnv_cmdLogging(s32* msg);
    static void _ext_CKLBLuaEnv_cmdExit();
    static void _ext_CKLBLuaEnv_cmdSystemInfo(s32& width,s32& height);
    static void _ext_CKLBLuaEnv_cmdSystemReboot();
    static void logging(System::String* msg);
    static void exitGame();
    static void getInfo(EnginePrototype::SystemInfo_inner2& sysInfos);
    static void reboot();
    CSSystem();
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 135;
};
struct EnginePrototype::SystemInfo_inner2 : public System::__GCStruct {

public:
    void _ctor_SystemInfo_inner2();
    s32 width;
    inline s32& _gwidth$() { CHCKTHIS; return width; }
    inline s32 _swidth$(s32 _$value) { CHCKTHIS; return width = _$value; }
    inline s32 _swidth$postInc()				{ CHCKTHIS; return width++; }
    inline s32 _swidth$postDec()				{ CHCKTHIS; return width--; }
    inline s32 _swidth$preInc()				{ CHCKTHIS; return ++width; }
    inline s32 _swidth$preDec()				{ CHCKTHIS; return --width; }
    inline s32 _swidth$AddEq(s32 value)		{ CHCKTHIS; return width += value; }
    inline s32 _swidth$SubEq(s32 value)		{ CHCKTHIS; return width -= value; }
    inline s32 _swidth$MulEq(s32 value)		{ CHCKTHIS; return width *= value; }
    inline s32 _swidth$DivEq(s32 value)		{ CHCKTHIS; if (value == 0) { THROWDIVZERO; }; ; return width /= value; }
    inline s32 _swidth$ModEq(s32 value)		{ CHCKTHIS; if (value == 0) { THROWDIVZERO; }; ; return width %= value; }
    inline s32 _swidth$XorEq(s32 value)		{ CHCKTHIS; return width ^= value; }
    inline s32 _swidth$AndEq(s32 value)		{ CHCKTHIS; return width &= value; }
    inline s32 _swidth$OrEq(s32 value)		{ CHCKTHIS; return width |= value; }
    inline s32 _swidth$RShiftEq(s32 value)	{ CHCKTHIS; return width >>= value; }
    inline s32 _swidth$LShiftEq(s32 value)	{ CHCKTHIS; return width <<= value; }
    inline s32 _swidthpostInc()				{ return width++; }
    inline s32 _swidthpostDec()				{ return width--; }
    inline s32 _swidthpreInc()				{ return ++width; }
    inline s32 _swidthpreDec()				{ return --width; }
    inline s32 _swidthAddEq(s32 value)		{ return width += value; }
    inline s32 _swidthSubEq(s32 value)		{ return width -= value; }
    inline s32 _swidthMulEq(s32 value)		{ return width *= value; }
    inline s32 _swidthDivEq(s32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return width /= value; }
    inline s32 _swidthModEq(s32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return width %= value; }
    inline s32 _swidthXorEq(s32 value)		{ return width ^= value; }
    inline s32 _swidthAndEq(s32 value)		{ return width &= value; }
    inline s32 _swidthOrEq(s32 value)			{ return width |= value; }
    inline s32 _swidthRShiftEq(s32 value)		{ return width >>= value; }
    inline s32 _swidthLShiftEq(s32 value)		{ return width <<= value; }

    s32 height;
    inline s32& _gheight$() { CHCKTHIS; return height; }
    inline s32 _sheight$(s32 _$value) { CHCKTHIS; return height = _$value; }
    inline s32 _sheight$postInc()				{ CHCKTHIS; return height++; }
    inline s32 _sheight$postDec()				{ CHCKTHIS; return height--; }
    inline s32 _sheight$preInc()				{ CHCKTHIS; return ++height; }
    inline s32 _sheight$preDec()				{ CHCKTHIS; return --height; }
    inline s32 _sheight$AddEq(s32 value)		{ CHCKTHIS; return height += value; }
    inline s32 _sheight$SubEq(s32 value)		{ CHCKTHIS; return height -= value; }
    inline s32 _sheight$MulEq(s32 value)		{ CHCKTHIS; return height *= value; }
    inline s32 _sheight$DivEq(s32 value)		{ CHCKTHIS; if (value == 0) { THROWDIVZERO; }; ; return height /= value; }
    inline s32 _sheight$ModEq(s32 value)		{ CHCKTHIS; if (value == 0) { THROWDIVZERO; }; ; return height %= value; }
    inline s32 _sheight$XorEq(s32 value)		{ CHCKTHIS; return height ^= value; }
    inline s32 _sheight$AndEq(s32 value)		{ CHCKTHIS; return height &= value; }
    inline s32 _sheight$OrEq(s32 value)		{ CHCKTHIS; return height |= value; }
    inline s32 _sheight$RShiftEq(s32 value)	{ CHCKTHIS; return height >>= value; }
    inline s32 _sheight$LShiftEq(s32 value)	{ CHCKTHIS; return height <<= value; }
    inline s32 _sheightpostInc()				{ return height++; }
    inline s32 _sheightpostDec()				{ return height--; }
    inline s32 _sheightpreInc()				{ return ++height; }
    inline s32 _sheightpreDec()				{ return --height; }
    inline s32 _sheightAddEq(s32 value)		{ return height += value; }
    inline s32 _sheightSubEq(s32 value)		{ return height -= value; }
    inline s32 _sheightMulEq(s32 value)		{ return height *= value; }
    inline s32 _sheightDivEq(s32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return height /= value; }
    inline s32 _sheightModEq(s32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return height %= value; }
    inline s32 _sheightXorEq(s32 value)		{ return height ^= value; }
    inline s32 _sheightAndEq(s32 value)		{ return height &= value; }
    inline s32 _sheightOrEq(s32 value)			{ return height |= value; }
    inline s32 _sheightRShiftEq(s32 value)		{ return height >>= value; }
    inline s32 _sheightLShiftEq(s32 value)		{ return height <<= value; }

    SystemInfo_inner2();
    inline u32 _processGC();
    inline void _releaseGC();
    inline void* _RefSetValue(void* newStruct);
    virtual inline void _moveAlert(u32 offset);
    inline static SystemInfo_inner2& __registerByRef(SystemInfo_inner2& m);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_STRUCT | 136;
};
class EnginePrototype::CSUI : public System::Object {

public:
    enum E_POSITION {
        LEFT = 1,
        RIGHT = 2,
        H_CENTER = 3,
        TOP = 4,
        BOTTOM = 8,
        V_CENTER = 12,
        _ForceWORD_E_POSITION = 0x7FFFFFFF
    };

    void _ctor_CSUI();
    static void _ext_CKLBLuaLibUI_calcPosition(float x,float y,float w,float h,u32 mask,float& out_rx,float& out_ry);
    static void calcPosition(float x,float y,float w,float h,s32 mask,float& out_rx,float& out_ry);
    CSUI();
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 138;
};
class EnginePrototype::CKLBTask : public EnginePrototype::GameObject {
friend class onDieCallBack_inner28;

public:
class _anon_0;
    enum ETASK_PHASE {
        P_BEGIN = 0,
        P_INPUT = 1,
        P_DBGSIGN = 2,
        P_DBGMENU = 3,
        P_UIPREV = 4,
        P_SCRIPT = 5,
        P_UIPROC = 6,
        P_UIAFTER = 7,
        P_MENU = 8,
        P_PREV = 9,
        P_NORMAL = 10,
        P_AFTER = 11,
        P_JUDGE = 12,
        P_DRAW = 13,
        P_GC = 14,
        P_END = 15,
        P_MAX = 16,
        _ForceWORD_ETASK_PHASE = 0x7FFFFFFF
    };

    void _ctor_CKLBTask();
    EnginePrototype::_Delegate_Base_onDieCallBack_inner28* m_callback;
    inline EnginePrototype::_Delegate_Base_onDieCallBack_inner28*& _gm_callback$() { CHCKTHIS; return m_callback; }
    inline EnginePrototype::_Delegate_Base_onDieCallBack_inner28* _sm_callback(EnginePrototype::_Delegate_Base_onDieCallBack_inner28* _$value);
    inline EnginePrototype::_Delegate_Base_onDieCallBack_inner28* _sm_callback$(EnginePrototype::_Delegate_Base_onDieCallBack_inner28* _$value);

    EnginePrototype::CKLBIntervalTimer* m_timer;
    inline EnginePrototype::CKLBIntervalTimer*& _gm_timer$() { CHCKTHIS; return m_timer; }
    inline EnginePrototype::CKLBIntervalTimer* _sm_timer(EnginePrototype::CKLBIntervalTimer* _$value);
    inline EnginePrototype::CKLBIntervalTimer* _sm_timer$(EnginePrototype::CKLBIntervalTimer* _$value);

    static void _ext_Task_kill(s32* task);
    static void _ext_Task_setStageTask(s32* task);
    static void _ext_Task_clearStageTask();
    static void _ext_Task_setPause(s32* task,bool bPause,bool bRecursive);
    static void _ext_Task_setManagerPause(bool bPause);
    static void _ext_Task_interposeTimer(s32* pTask,s32* pTimer);
    static bool _ext_Task_isKill(s32* task);
    CKLBTask(u32 classID);
    virtual void doSetupCallbacks();
    inline void doSetupCallbacks$();
    void setOnDieCallBack(EnginePrototype::_Delegate_Base_onDieCallBack_inner28* anyDelegate);
    inline void setOnDieCallBack$(EnginePrototype::_Delegate_Base_onDieCallBack_inner28* anyDelegate);
    virtual void onDieCallBackFunction();
    inline void onDieCallBackFunction$();
    void kill();
    inline void kill$();
    bool isKill();
    inline bool isKill$();
    virtual void Dispose();
    inline void Dispose$();
    void setPause(bool bPause,bool bRecursive);
    inline void setPause$(bool bPause,bool bRecursive);
    void setLifeTime(s32 mode,u32 time);
    inline void setLifeTime$(s32 mode,u32 time);
    void stageOnly();
    inline void stageOnly$();
    static void clearStage();
    static void setManagerPause(bool bPause);
    CKLBTask();
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 161;
};
class EnginePrototype::CKLBAsyncLoader : public EnginePrototype::CKLBTask {
friend class CallBack_inner21;

public:
    void _ctor_CKLBAsyncLoader();
    static u32 s_classID;
    inline static u32 _ss_classIDDivEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID /= value; }
    inline static u32 _ss_classIDModEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID %= value; }

    EnginePrototype::_Delegate_Base_CallBack_inner21* m_callback;
    inline EnginePrototype::_Delegate_Base_CallBack_inner21*& _gm_callback$() { CHCKTHIS; return m_callback; }
    inline EnginePrototype::_Delegate_Base_CallBack_inner21* _sm_callback(EnginePrototype::_Delegate_Base_CallBack_inner21* _$value);
    inline EnginePrototype::_Delegate_Base_CallBack_inner21* _sm_callback$(EnginePrototype::_Delegate_Base_CallBack_inner21* _$value);

    inline u32 _acc_gProcessCount();
    inline u32 _acc_gProcessCount$();

    inline u32 _acc_gTotalCount();
    inline u32 _acc_gTotalCount$();

    static s32* _ext_CKLBAsyncLoader_create(s32* pParentTask,System::Array<s32*>* assets,u32 count,u32 datasetID);
    static u32 _ext_CKLBAsyncLoader_getProcessCount(s32* p);
    static u32 _ext_CKLBAsyncLoader_getTotalCount(s32* p);
    CKLBAsyncLoader(EnginePrototype::CKLBTask* pParent,System::Array<System::String*>* assets,u32 datasetID,EnginePrototype::_Delegate_Base_CallBack_inner21* callback);
    CKLBAsyncLoader();
    virtual void doSetupCallbacks();
    inline void doSetupCallbacks$();
    virtual void setDelegate(System::Delegate* anyDelegate,System::String* delegateName);
    inline void setDelegate$(System::Delegate* anyDelegate,System::String* delegateName);
    virtual void callBackFunction(u32 loaded,u32 total);
    inline void callBackFunction$(u32 loaded,u32 total);
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 140;
};
class EnginePrototype::CKLBGenericTask : public EnginePrototype::CKLBTask {
friend class ExecuteCallBack_inner22;
friend class DieCallBack_inner23;

public:
    void _ctor_CKLBGenericTask();
    static u32 s_classID;
    inline static u32 _ss_classIDDivEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID /= value; }
    inline static u32 _ss_classIDModEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID %= value; }

    EnginePrototype::_Delegate_Base_ExecuteCallBack_inner22* m_executeCallBack;
    inline EnginePrototype::_Delegate_Base_ExecuteCallBack_inner22*& _gm_executeCallBack$() { CHCKTHIS; return m_executeCallBack; }
    inline EnginePrototype::_Delegate_Base_ExecuteCallBack_inner22* _sm_executeCallBack(EnginePrototype::_Delegate_Base_ExecuteCallBack_inner22* _$value);
    inline EnginePrototype::_Delegate_Base_ExecuteCallBack_inner22* _sm_executeCallBack$(EnginePrototype::_Delegate_Base_ExecuteCallBack_inner22* _$value);

    EnginePrototype::_Delegate_Base_DieCallBack_inner23* m_dieCallBack;
    inline EnginePrototype::_Delegate_Base_DieCallBack_inner23*& _gm_dieCallBack$() { CHCKTHIS; return m_dieCallBack; }
    inline EnginePrototype::_Delegate_Base_DieCallBack_inner23* _sm_dieCallBack(EnginePrototype::_Delegate_Base_DieCallBack_inner23* _$value);
    inline EnginePrototype::_Delegate_Base_DieCallBack_inner23* _sm_dieCallBack$(EnginePrototype::_Delegate_Base_DieCallBack_inner23* _$value);

    static s32* _ext_CKLBGenericTask_create(s32* pParent,u32 phase);
    CKLBGenericTask(EnginePrototype::CKLBTask* parent,s32 phase,EnginePrototype::_Delegate_Base_ExecuteCallBack_inner22* executeCallBack,EnginePrototype::_Delegate_Base_DieCallBack_inner23* dieCallBack);
    CKLBGenericTask();
    virtual void doSetupCallbacks();
    inline void doSetupCallbacks$();
    virtual void setDelegate(System::Delegate* anyDelegate,System::String* delegateName);
    inline void setDelegate$(System::Delegate* anyDelegate,System::String* delegateName);
    virtual void executeCallBackFunction(u32 deltaTime);
    inline void executeCallBackFunction$(u32 deltaTime);
    virtual void dieCallBackFunction();
    inline void dieCallBackFunction$();
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 143;
};
class EnginePrototype::CKLBNetAPI : public EnginePrototype::CKLBTask {
friend class CallBack_inner25;
friend class CallBackVersionUp_inner26;

public:
    enum ESTATUS {
        NETAPIMSG_SESSION_CANCELED = -999,
        NETAPIMSG_CONNECTION_FAILED = -500,
        NETAPIMSG_INVITE_FAILED = -200,
        NETAPIMSG_STARTUP_FAILED = -100,
        NETAPIMSG_SERVER_TIMEOUT = -4,
        NETAPIMSG_REQUEST_FAILED = -3,
        NETAPIMSG_LOGIN_FAILED = -2,
        NETAPIMSG_SERVER_ERROR = -1,
        NETAPIMSG_UNKNOWN = 0,
        NETAPIMSG_LOGIN_SUCCESS = 2,
        NETAPIMSG_REQUEST_SUCCESS = 3,
        NETAPIMSG_STARTUP_SUCCESS = 100,
        NETAPIMSG_INVITE_SUCCESS = 200,
        _ForceWORD_ESTATUS = 0x7FFFFFFF
    };

    void _ctor_CKLBNetAPI();
    static u32 s_classID;
    inline static u32 _ss_classIDDivEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID /= value; }
    inline static u32 _ss_classIDModEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID %= value; }

    EnginePrototype::_Delegate_Base_CallBack_inner25* m_callback;
    inline EnginePrototype::_Delegate_Base_CallBack_inner25*& _gm_callback$() { CHCKTHIS; return m_callback; }
    inline EnginePrototype::_Delegate_Base_CallBack_inner25* _sm_callback(EnginePrototype::_Delegate_Base_CallBack_inner25* _$value);
    inline EnginePrototype::_Delegate_Base_CallBack_inner25* _sm_callback$(EnginePrototype::_Delegate_Base_CallBack_inner25* _$value);

    EnginePrototype::_Delegate_Base_CallBackVersionUp_inner26* m_callbackVersionUp;
    inline EnginePrototype::_Delegate_Base_CallBackVersionUp_inner26*& _gm_callbackVersionUp$() { CHCKTHIS; return m_callbackVersionUp; }
    inline EnginePrototype::_Delegate_Base_CallBackVersionUp_inner26* _sm_callbackVersionUp(EnginePrototype::_Delegate_Base_CallBackVersionUp_inner26* _$value);
    inline EnginePrototype::_Delegate_Base_CallBackVersionUp_inner26* _sm_callbackVersionUp$(EnginePrototype::_Delegate_Base_CallBackVersionUp_inner26* _$value);

    static s32* _ext_CKLBNetAPI_create(s32* pParent,s32* apiurl,s32* client_version,s32* consumerKey,s32* applicationId,u32 sessionMax,s32* region);
    static bool _ext_CKLBNetAPI_startUp(s32* p,s32* loginID,s32* password,s32* invite,u32 timeout,u32& session);
    static bool _ext_CKLBNetAPI_login(s32* p,s32* loginID,s32* password,u32 timeout,u32& session);
    static bool _ext_CKLBNetAPI_cancel(s32* p,u32 uniq);
    static void _ext_CKLBNetAPI_cancelAll(s32* p);
    static bool _ext_CKLBNetAPI_watchMaintenance(s32* p,u32 timeout,u32& session);
    static void _ext_CKLBNetAPI_debugHdr(s32* p,bool debugflag);
    static void _ext_CKLBNetAPI_genCmdNumID(s32* p,s32* body,s32 serial,s32* buf);
    static bool _ext_CKLBNetAPI_sendHTTP(s32* p,s32* apiURL,s32* json,u32 timeout,bool passVersionCheck,u32& session);
    CKLBNetAPI(EnginePrototype::CKLBTask* parent,System::String* apiUrl,System::String* clientVersion,System::String* consumerKey,System::String* applicationID,u32 sessionMax,System::String* region,EnginePrototype::_Delegate_Base_CallBack_inner25* callback,EnginePrototype::_Delegate_Base_CallBackVersionUp_inner26* versionUpCallback);
    CKLBNetAPI();
    virtual void doSetupCallbacks();
    inline void doSetupCallbacks$();
    virtual void setDelegate(System::Delegate* anyDelegate,System::String* delegateName);
    inline void setDelegate$(System::Delegate* anyDelegate,System::String* delegateName);
    virtual bool callBackFunction(s32 uniq,s32 msg,s32 status,s32* pRoot);
    inline bool callBackFunction$(s32 uniq,s32 msg,s32 status,s32* pRoot);
    virtual void callBackVersionUpFunction(s32* clientVer,s32* serverVer);
    inline void callBackVersionUpFunction$(s32* clientVer,s32* serverVer);
    bool startUp(u32& session,System::String* loginID,System::String* password,System::String* invite,u32 timeout);
    inline bool startUp$(u32& session,System::String* loginID,System::String* password,System::String* invite,u32 timeout);
    bool login(u32& session,System::String* loginID,System::String* password,u32 timeout);
    inline bool login$(u32& session,System::String* loginID,System::String* password,u32 timeout);
    bool cancel(u32 session);
    inline bool cancel$(u32 session);
    bool send(u32& session,System::String* json,System::String* apiURL,u32 timeout,bool pass_version_check);
    inline bool send$(u32& session,System::String* json,System::String* apiURL,u32 timeout,bool pass_version_check);
    void cancelAll();
    inline void cancelAll$();
    bool watchMaintenance(u32& session,u32 timeout);
    inline bool watchMaintenance$(u32& session,u32 timeout);
    void debugHdr(bool debugflag);
    inline void debugHdr$(bool debugflag);
    void _ref_genCmdNumID(System::String*& numID,System::String* body,s32 serial);
    inline void genCmdNumID$(System::String*& numID,System::String* body,s32 serial);
    inline void genCmdNumID(System::String*& numID,System::String* body,s32 serial);
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 152;
};
class EnginePrototype::CKLBStoreService : public EnginePrototype::CKLBTask {
friend class CallBack_inner27;

public:
    void _ctor_CKLBStoreService();
    static u32 s_classID;
    inline static u32 _ss_classIDDivEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID /= value; }
    inline static u32 _ss_classIDModEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID %= value; }

    EnginePrototype::_Delegate_Base_CallBack_inner27* m_callback;
    inline EnginePrototype::_Delegate_Base_CallBack_inner27*& _gm_callback$() { CHCKTHIS; return m_callback; }
    inline EnginePrototype::_Delegate_Base_CallBack_inner27* _sm_callback(EnginePrototype::_Delegate_Base_CallBack_inner27* _$value);
    inline EnginePrototype::_Delegate_Base_CallBack_inner27* _sm_callback$(EnginePrototype::_Delegate_Base_CallBack_inner27* _$value);

    static s32* _ext_CKLBStoreService_create();
    static void _ext_CKLBStoreService_buyItems(s32* p,s32* item);
    static void _ext_CKLBStoreService_getProducts(s32* p,s32* json,bool currency);
    CKLBStoreService(EnginePrototype::_Delegate_Base_CallBack_inner27* callback);
    CKLBStoreService();
    virtual void doSetupCallbacks();
    inline void doSetupCallbacks$();
    virtual void setDelegate(System::Delegate* anyDelegate,System::String* delegateName);
    inline void setDelegate$(System::Delegate* anyDelegate,System::String* delegateName);
    virtual void callBackFunction(u32 type,s32* itemID,s32* param);
    inline void callBackFunction$(u32 type,s32* itemID,s32* param);
    void buyItems(System::String* item);
    inline void buyItems$(System::String* item);
    void getProducts(System::String* json,bool currency);
    inline void getProducts$(System::String* json,bool currency);
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 158;
};
class EnginePrototype::CKLBTask::_anon_0 : public System::Object {

public:
    void _ctor__anon_0();
    EnginePrototype::CKLBTask* _this__;
    inline EnginePrototype::CKLBTask*& _g_this__$() { CHCKTHIS; return _this__; }
    inline EnginePrototype::CKLBTask* _s_this__(EnginePrototype::CKLBTask* _$value);
    inline EnginePrototype::CKLBTask* _s_this__$(EnginePrototype::CKLBTask* _$value);

    s32 mode;
    inline s32& _gmode$() { CHCKTHIS; return mode; }
    inline s32 _smode$(s32 _$value) { CHCKTHIS; return mode = _$value; }
    inline s32 _smode$postInc()				{ CHCKTHIS; return (s32)(((s32&)mode)++); }
    inline s32 _smode$postDec()				{ CHCKTHIS; return (s32)(((s32&)mode)--); }
    inline s32 _smode$preInc()				{ CHCKTHIS; return (s32)(++(s32&)mode); }
    inline s32 _smode$preDec()				{ CHCKTHIS; return (s32)(--(s32&)mode); }
    inline s32 _smode$AddEq(s32 value)		{ CHCKTHIS; return (s32)((s32&)mode += value); }
    inline s32 _smode$SubEq(s32 value)		{ CHCKTHIS; return (s32)((s32&)mode -= value); }
    inline s32 _smodepostInc()				{ return (s32)(((s32&)mode)++); }
    inline s32 _smodepostDec()				{ return (s32)(((s32&)mode)--); }
    inline s32 _smodepreInc()				{ return (s32)(++(s32&)mode); }
    inline s32 _smodepreDec()				{ return (s32)(--(s32&)mode); }
    inline s32 _smodeAddEq(s32 value)		{ return (s32)((s32&)mode += value); }
    inline s32 _smodeSubEq(s32 value)		{ return (s32)((s32&)mode -= value); }

    u32 time;
    inline u32& _gtime$() { CHCKTHIS; return time; }
    inline u32 _stime$(u32 _$value) { CHCKTHIS; return time = _$value; }
    inline u32 _stime$postInc()				{ CHCKTHIS; return time++; }
    inline u32 _stime$postDec()				{ CHCKTHIS; return time--; }
    inline u32 _stime$preInc()				{ CHCKTHIS; return ++time; }
    inline u32 _stime$preDec()				{ CHCKTHIS; return --time; }
    inline u32 _stime$AddEq(u32 value)		{ CHCKTHIS; return time += value; }
    inline u32 _stime$SubEq(u32 value)		{ CHCKTHIS; return time -= value; }
    inline u32 _stime$MulEq(u32 value)		{ CHCKTHIS; return time *= value; }
    inline u32 _stime$DivEq(u32 value)		{ CHCKTHIS; if (value == 0) { THROWDIVZERO; }; ; return time /= value; }
    inline u32 _stime$ModEq(u32 value)		{ CHCKTHIS; if (value == 0) { THROWDIVZERO; }; ; return time %= value; }
    inline u32 _stime$XorEq(u32 value)		{ CHCKTHIS; return time ^= value; }
    inline u32 _stime$AndEq(u32 value)		{ CHCKTHIS; return time &= value; }
    inline u32 _stime$OrEq(u32 value)		{ CHCKTHIS; return time |= value; }
    inline u32 _stime$RShiftEq(u32 value)	{ CHCKTHIS; return time >>= value; }
    inline u32 _stime$LShiftEq(u32 value)	{ CHCKTHIS; return time <<= value; }
    inline u32 _stimepostInc()				{ return time++; }
    inline u32 _stimepostDec()				{ return time--; }
    inline u32 _stimepreInc()				{ return ++time; }
    inline u32 _stimepreDec()				{ return --time; }
    inline u32 _stimeAddEq(u32 value)		{ return time += value; }
    inline u32 _stimeSubEq(u32 value)		{ return time -= value; }
    inline u32 _stimeMulEq(u32 value)		{ return time *= value; }
    inline u32 _stimeDivEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return time /= value; }
    inline u32 _stimeModEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return time %= value; }
    inline u32 _stimeXorEq(u32 value)		{ return time ^= value; }
    inline u32 _stimeAndEq(u32 value)		{ return time &= value; }
    inline u32 _stimeOrEq(u32 value)			{ return time |= value; }
    inline u32 _stimeRShiftEq(u32 value)		{ return time >>= value; }
    inline u32 _stimeLShiftEq(u32 value)		{ return time <<= value; }

    _anon_0(EnginePrototype::CKLBTask* _this__,s32 mode,u32 time);
    void _delegate(EnginePrototype::CKLBIntervalTimer* caller);
    inline void _delegate$(EnginePrototype::CKLBIntervalTimer* caller);
    _anon_0();
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 165;
};
struct EnginePrototype::Area_inner3 : public System::__GCStruct {

public:
    void _ctor_Area_inner3();
    s32 x;
    inline s32& _gx$() { CHCKTHIS; return x; }
    inline s32 _sx$(s32 _$value) { CHCKTHIS; return x = _$value; }
    inline s32 _sx$postInc()				{ CHCKTHIS; return x++; }
    inline s32 _sx$postDec()				{ CHCKTHIS; return x--; }
    inline s32 _sx$preInc()				{ CHCKTHIS; return ++x; }
    inline s32 _sx$preDec()				{ CHCKTHIS; return --x; }
    inline s32 _sx$AddEq(s32 value)		{ CHCKTHIS; return x += value; }
    inline s32 _sx$SubEq(s32 value)		{ CHCKTHIS; return x -= value; }
    inline s32 _sx$MulEq(s32 value)		{ CHCKTHIS; return x *= value; }
    inline s32 _sx$DivEq(s32 value)		{ CHCKTHIS; if (value == 0) { THROWDIVZERO; }; ; return x /= value; }
    inline s32 _sx$ModEq(s32 value)		{ CHCKTHIS; if (value == 0) { THROWDIVZERO; }; ; return x %= value; }
    inline s32 _sx$XorEq(s32 value)		{ CHCKTHIS; return x ^= value; }
    inline s32 _sx$AndEq(s32 value)		{ CHCKTHIS; return x &= value; }
    inline s32 _sx$OrEq(s32 value)		{ CHCKTHIS; return x |= value; }
    inline s32 _sx$RShiftEq(s32 value)	{ CHCKTHIS; return x >>= value; }
    inline s32 _sx$LShiftEq(s32 value)	{ CHCKTHIS; return x <<= value; }
    inline s32 _sxpostInc()				{ return x++; }
    inline s32 _sxpostDec()				{ return x--; }
    inline s32 _sxpreInc()				{ return ++x; }
    inline s32 _sxpreDec()				{ return --x; }
    inline s32 _sxAddEq(s32 value)		{ return x += value; }
    inline s32 _sxSubEq(s32 value)		{ return x -= value; }
    inline s32 _sxMulEq(s32 value)		{ return x *= value; }
    inline s32 _sxDivEq(s32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return x /= value; }
    inline s32 _sxModEq(s32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return x %= value; }
    inline s32 _sxXorEq(s32 value)		{ return x ^= value; }
    inline s32 _sxAndEq(s32 value)		{ return x &= value; }
    inline s32 _sxOrEq(s32 value)			{ return x |= value; }
    inline s32 _sxRShiftEq(s32 value)		{ return x >>= value; }
    inline s32 _sxLShiftEq(s32 value)		{ return x <<= value; }

    s32 y;
    inline s32& _gy$() { CHCKTHIS; return y; }
    inline s32 _sy$(s32 _$value) { CHCKTHIS; return y = _$value; }
    inline s32 _sy$postInc()				{ CHCKTHIS; return y++; }
    inline s32 _sy$postDec()				{ CHCKTHIS; return y--; }
    inline s32 _sy$preInc()				{ CHCKTHIS; return ++y; }
    inline s32 _sy$preDec()				{ CHCKTHIS; return --y; }
    inline s32 _sy$AddEq(s32 value)		{ CHCKTHIS; return y += value; }
    inline s32 _sy$SubEq(s32 value)		{ CHCKTHIS; return y -= value; }
    inline s32 _sy$MulEq(s32 value)		{ CHCKTHIS; return y *= value; }
    inline s32 _sy$DivEq(s32 value)		{ CHCKTHIS; if (value == 0) { THROWDIVZERO; }; ; return y /= value; }
    inline s32 _sy$ModEq(s32 value)		{ CHCKTHIS; if (value == 0) { THROWDIVZERO; }; ; return y %= value; }
    inline s32 _sy$XorEq(s32 value)		{ CHCKTHIS; return y ^= value; }
    inline s32 _sy$AndEq(s32 value)		{ CHCKTHIS; return y &= value; }
    inline s32 _sy$OrEq(s32 value)		{ CHCKTHIS; return y |= value; }
    inline s32 _sy$RShiftEq(s32 value)	{ CHCKTHIS; return y >>= value; }
    inline s32 _sy$LShiftEq(s32 value)	{ CHCKTHIS; return y <<= value; }
    inline s32 _sypostInc()				{ return y++; }
    inline s32 _sypostDec()				{ return y--; }
    inline s32 _sypreInc()				{ return ++y; }
    inline s32 _sypreDec()				{ return --y; }
    inline s32 _syAddEq(s32 value)		{ return y += value; }
    inline s32 _sySubEq(s32 value)		{ return y -= value; }
    inline s32 _syMulEq(s32 value)		{ return y *= value; }
    inline s32 _syDivEq(s32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return y /= value; }
    inline s32 _syModEq(s32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return y %= value; }
    inline s32 _syXorEq(s32 value)		{ return y ^= value; }
    inline s32 _syAndEq(s32 value)		{ return y &= value; }
    inline s32 _syOrEq(s32 value)			{ return y |= value; }
    inline s32 _syRShiftEq(s32 value)		{ return y >>= value; }
    inline s32 _syLShiftEq(s32 value)		{ return y <<= value; }

    s32 width;
    inline s32& _gwidth$() { CHCKTHIS; return width; }
    inline s32 _swidth$(s32 _$value) { CHCKTHIS; return width = _$value; }
    inline s32 _swidth$postInc()				{ CHCKTHIS; return width++; }
    inline s32 _swidth$postDec()				{ CHCKTHIS; return width--; }
    inline s32 _swidth$preInc()				{ CHCKTHIS; return ++width; }
    inline s32 _swidth$preDec()				{ CHCKTHIS; return --width; }
    inline s32 _swidth$AddEq(s32 value)		{ CHCKTHIS; return width += value; }
    inline s32 _swidth$SubEq(s32 value)		{ CHCKTHIS; return width -= value; }
    inline s32 _swidth$MulEq(s32 value)		{ CHCKTHIS; return width *= value; }
    inline s32 _swidth$DivEq(s32 value)		{ CHCKTHIS; if (value == 0) { THROWDIVZERO; }; ; return width /= value; }
    inline s32 _swidth$ModEq(s32 value)		{ CHCKTHIS; if (value == 0) { THROWDIVZERO; }; ; return width %= value; }
    inline s32 _swidth$XorEq(s32 value)		{ CHCKTHIS; return width ^= value; }
    inline s32 _swidth$AndEq(s32 value)		{ CHCKTHIS; return width &= value; }
    inline s32 _swidth$OrEq(s32 value)		{ CHCKTHIS; return width |= value; }
    inline s32 _swidth$RShiftEq(s32 value)	{ CHCKTHIS; return width >>= value; }
    inline s32 _swidth$LShiftEq(s32 value)	{ CHCKTHIS; return width <<= value; }
    inline s32 _swidthpostInc()				{ return width++; }
    inline s32 _swidthpostDec()				{ return width--; }
    inline s32 _swidthpreInc()				{ return ++width; }
    inline s32 _swidthpreDec()				{ return --width; }
    inline s32 _swidthAddEq(s32 value)		{ return width += value; }
    inline s32 _swidthSubEq(s32 value)		{ return width -= value; }
    inline s32 _swidthMulEq(s32 value)		{ return width *= value; }
    inline s32 _swidthDivEq(s32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return width /= value; }
    inline s32 _swidthModEq(s32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return width %= value; }
    inline s32 _swidthXorEq(s32 value)		{ return width ^= value; }
    inline s32 _swidthAndEq(s32 value)		{ return width &= value; }
    inline s32 _swidthOrEq(s32 value)			{ return width |= value; }
    inline s32 _swidthRShiftEq(s32 value)		{ return width >>= value; }
    inline s32 _swidthLShiftEq(s32 value)		{ return width <<= value; }

    s32 height;
    inline s32& _gheight$() { CHCKTHIS; return height; }
    inline s32 _sheight$(s32 _$value) { CHCKTHIS; return height = _$value; }
    inline s32 _sheight$postInc()				{ CHCKTHIS; return height++; }
    inline s32 _sheight$postDec()				{ CHCKTHIS; return height--; }
    inline s32 _sheight$preInc()				{ CHCKTHIS; return ++height; }
    inline s32 _sheight$preDec()				{ CHCKTHIS; return --height; }
    inline s32 _sheight$AddEq(s32 value)		{ CHCKTHIS; return height += value; }
    inline s32 _sheight$SubEq(s32 value)		{ CHCKTHIS; return height -= value; }
    inline s32 _sheight$MulEq(s32 value)		{ CHCKTHIS; return height *= value; }
    inline s32 _sheight$DivEq(s32 value)		{ CHCKTHIS; if (value == 0) { THROWDIVZERO; }; ; return height /= value; }
    inline s32 _sheight$ModEq(s32 value)		{ CHCKTHIS; if (value == 0) { THROWDIVZERO; }; ; return height %= value; }
    inline s32 _sheight$XorEq(s32 value)		{ CHCKTHIS; return height ^= value; }
    inline s32 _sheight$AndEq(s32 value)		{ CHCKTHIS; return height &= value; }
    inline s32 _sheight$OrEq(s32 value)		{ CHCKTHIS; return height |= value; }
    inline s32 _sheight$RShiftEq(s32 value)	{ CHCKTHIS; return height >>= value; }
    inline s32 _sheight$LShiftEq(s32 value)	{ CHCKTHIS; return height <<= value; }
    inline s32 _sheightpostInc()				{ return height++; }
    inline s32 _sheightpostDec()				{ return height--; }
    inline s32 _sheightpreInc()				{ return ++height; }
    inline s32 _sheightpreDec()				{ return --height; }
    inline s32 _sheightAddEq(s32 value)		{ return height += value; }
    inline s32 _sheightSubEq(s32 value)		{ return height -= value; }
    inline s32 _sheightMulEq(s32 value)		{ return height *= value; }
    inline s32 _sheightDivEq(s32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return height /= value; }
    inline s32 _sheightModEq(s32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return height %= value; }
    inline s32 _sheightXorEq(s32 value)		{ return height ^= value; }
    inline s32 _sheightAndEq(s32 value)		{ return height &= value; }
    inline s32 _sheightOrEq(s32 value)			{ return height |= value; }
    inline s32 _sheightRShiftEq(s32 value)		{ return height >>= value; }
    inline s32 _sheightLShiftEq(s32 value)		{ return height <<= value; }

    Area_inner3(s32 _x,s32 _y,s32 _width,s32 _height);
    void setValues(s32 _x,s32 _y,s32 _width,s32 _height);
    inline void setValues$(s32 _x,s32 _y,s32 _width,s32 _height);
    Area_inner3();
    inline u32 _processGC();
    inline void _releaseGC();
    inline void* _RefSetValue(void* newStruct);
    virtual inline void _moveAlert(u32 offset);
    inline static Area_inner3& __registerByRef(Area_inner3& m);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_STRUCT | 189;
};
class EnginePrototype::AnimationInfo : public System::Object {

public:
    enum EIDX {
        X_COORD = 0,
        Y_COORD = 1,
        SCALE_COORD = 2,
        R_COLOR = 3,
        G_COLOR = 4,
        B_COLOR = 5,
        A_COLOR = 6,
        SCALEX_COORD = 7,
        SCALEY_COORD = 8,
        ROTATION_COORD = 9,
        COUNT = 9,
        _ForceWORD_EIDX = 0x7FFFFFFF
    };

    void _ctor_AnimationInfo();
    u32 m_mask;
    inline u32& _gm_mask$() { CHCKTHIS; return m_mask; }
    inline u32 _sm_mask$(u32 _$value) { CHCKTHIS; return m_mask = _$value; }
    inline u32 _sm_mask$postInc()				{ CHCKTHIS; return m_mask++; }
    inline u32 _sm_mask$postDec()				{ CHCKTHIS; return m_mask--; }
    inline u32 _sm_mask$preInc()				{ CHCKTHIS; return ++m_mask; }
    inline u32 _sm_mask$preDec()				{ CHCKTHIS; return --m_mask; }
    inline u32 _sm_mask$AddEq(u32 value)		{ CHCKTHIS; return m_mask += value; }
    inline u32 _sm_mask$SubEq(u32 value)		{ CHCKTHIS; return m_mask -= value; }
    inline u32 _sm_mask$MulEq(u32 value)		{ CHCKTHIS; return m_mask *= value; }
    inline u32 _sm_mask$DivEq(u32 value)		{ CHCKTHIS; if (value == 0) { THROWDIVZERO; }; ; return m_mask /= value; }
    inline u32 _sm_mask$ModEq(u32 value)		{ CHCKTHIS; if (value == 0) { THROWDIVZERO; }; ; return m_mask %= value; }
    inline u32 _sm_mask$XorEq(u32 value)		{ CHCKTHIS; return m_mask ^= value; }
    inline u32 _sm_mask$AndEq(u32 value)		{ CHCKTHIS; return m_mask &= value; }
    inline u32 _sm_mask$OrEq(u32 value)		{ CHCKTHIS; return m_mask |= value; }
    inline u32 _sm_mask$RShiftEq(u32 value)	{ CHCKTHIS; return m_mask >>= value; }
    inline u32 _sm_mask$LShiftEq(u32 value)	{ CHCKTHIS; return m_mask <<= value; }
    inline u32 _sm_maskpostInc()				{ return m_mask++; }
    inline u32 _sm_maskpostDec()				{ return m_mask--; }
    inline u32 _sm_maskpreInc()				{ return ++m_mask; }
    inline u32 _sm_maskpreDec()				{ return --m_mask; }
    inline u32 _sm_maskAddEq(u32 value)		{ return m_mask += value; }
    inline u32 _sm_maskSubEq(u32 value)		{ return m_mask -= value; }
    inline u32 _sm_maskMulEq(u32 value)		{ return m_mask *= value; }
    inline u32 _sm_maskDivEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return m_mask /= value; }
    inline u32 _sm_maskModEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return m_mask %= value; }
    inline u32 _sm_maskXorEq(u32 value)		{ return m_mask ^= value; }
    inline u32 _sm_maskAndEq(u32 value)		{ return m_mask &= value; }
    inline u32 _sm_maskOrEq(u32 value)			{ return m_mask |= value; }
    inline u32 _sm_maskRShiftEq(u32 value)		{ return m_mask >>= value; }
    inline u32 _sm_maskLShiftEq(u32 value)		{ return m_mask <<= value; }

    static System::Array<u32>* ms_maskArr;
    inline static System::Array<u32>* _sms_maskArr(System::Array<u32>* _$value);

    static System::Array<s32>* ms_indexes;
    inline static System::Array<s32>* _sms_indexes(System::Array<s32>* _$value);

    System::Array<float>* m_internalArray;
    inline System::Array<float>*& _gm_internalArray$() { CHCKTHIS; return m_internalArray; }
    inline System::Array<float>* _sm_internalArray(System::Array<float>* _$value);
    inline System::Array<float>* _sm_internalArray$(System::Array<float>* _$value);

    void createAlphaAnimation(float start,float end);
    inline void createAlphaAnimation$(float start,float end);
    void createRGBAnimation(float RStart,float REnd,float GStart,float GEnd,float BStart,float BEnd);
    inline void createRGBAnimation$(float RStart,float REnd,float GStart,float GEnd,float BStart,float BEnd);
    void createScaleAnimation(float start,float end);
    inline void createScaleAnimation$(float start,float end);
    void createXOffsetAnimation(float start,float end);
    inline void createXOffsetAnimation$(float start,float end);
    void createYOffsetAnimation(float start,float end);
    inline void createYOffsetAnimation$(float start,float end);
    void _ref_getAnimInfo(u32& type,u32& affected,System::Array<float>*& arrayParam);
    inline void getAnimInfo$(u32& type,u32& affected,System::Array<float>*& arrayParam);
    inline void getAnimInfo(u32& type,u32& affected,System::Array<float>*& arrayParam);
    AnimationInfo();
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 227;
};
class EnginePrototype::CKLBUITask : public EnginePrototype::CKLBTask {
friend class Spline_inner4;
friend class IntSpline_inner5;
friend class IntPoint_inner6;
friend class FloatSpline_inner7;
friend class FloatPoint_inner8;
friend class AnimSpline_inner9;

public:
    enum ETARGET_TYPE {
        MODIFY_X = 1,
        MODIFY_Y = 2,
        MODIFY_SCALE = 3,
        MODIFY_R = 4,
        MODIFY_G = 5,
        MODIFY_B = 6,
        MODIFY_A = 7,
        MODIFY_ROT = 8,
        _ForceWORD_ETARGET_TYPE = 0x7FFFFFFF
    };

    enum ESPLINE_TYPE {
        INT_SPLINE,
        FLOAT_SPLINE,
        _ForceWORD_ESPLINE_TYPE = 0x7FFFFFFF
    };

    void _ctor_CKLBUITask();
    inline float _acc_gScaleX();
    inline float _acc_gScaleX$();

    inline float _acc_sScaleX(float value);
    inline float _acc_sScaleX$(float value);
    inline float _acc_sScaleXpostInc()			{ float tmp; _acc_sScaleX((tmp = _acc_gScaleX())+1); return tmp; }
    inline float _acc_sScaleX$postInc()			{ CHCKTHIS; return _acc_sScaleXpostInc(); }
    inline float _acc_sScaleXpostDec()			{ float tmp; _acc_sScaleX((tmp = _acc_gScaleX())-1); return tmp; }
    inline float _acc_sScaleX$postDec()			{ CHCKTHIS; return _acc_sScaleXpostDec(); }
    inline float _acc_sScaleXpreInc()			{ return _acc_sScaleX(_acc_gScaleX()+1); }
    inline float _acc_sScaleX$preInc()			{ CHCKTHIS; return _acc_sScaleXpreInc(); }
    inline float _acc_sScaleXpreDec()			{ return _acc_sScaleX(_acc_gScaleX()-1); }
    inline float _acc_sScaleX$preDec()			{ CHCKTHIS; return _acc_sScaleXpreDec(); }
    inline float _acc_sScaleXAddEq(float value)	{ return _acc_sScaleX(_acc_gScaleX() + value); }
    inline float _acc_sScaleX$AddEq(float value)			{ CHCKTHIS; return _acc_sScaleXAddEq(value); }
    inline float _acc_sScaleXSubEq(float value)	{ return _acc_sScaleX(_acc_gScaleX() - value); }
    inline float _acc_sScaleX$SubEq(float value)			{ CHCKTHIS; return _acc_sScaleXSubEq(value); }
    inline float _acc_sScaleXMulEq(float value)	{ return _acc_sScaleX(_acc_gScaleX() * value); }
    inline float _acc_sScaleX$MulEq(float value)			{ CHCKTHIS; return _acc_sScaleXMulEq(value); }
    inline float _acc_sScaleXDivEq(float value)	{ return _acc_sScaleX(_acc_gScaleX() / value); }
    inline float _acc_sScaleX$DivEq(float value)			{ CHCKTHIS; return _acc_sScaleXDivEq(value); }
    inline float _acc_sScaleXModEq(float value)	{  float orig = _acc_gScaleX(); s32 tmp = (s32)(orig / value); return _acc_sScaleX(orig - (tmp * value)); }
    inline float _acc_sScaleX$ModEq(float value)			{ CHCKTHIS; return _acc_sScaleXModEq(value); }
    inline float _acc_gScaleY();
    inline float _acc_gScaleY$();

    inline float _acc_sScaleY(float value);
    inline float _acc_sScaleY$(float value);
    inline float _acc_sScaleYpostInc()			{ float tmp; _acc_sScaleY((tmp = _acc_gScaleY())+1); return tmp; }
    inline float _acc_sScaleY$postInc()			{ CHCKTHIS; return _acc_sScaleYpostInc(); }
    inline float _acc_sScaleYpostDec()			{ float tmp; _acc_sScaleY((tmp = _acc_gScaleY())-1); return tmp; }
    inline float _acc_sScaleY$postDec()			{ CHCKTHIS; return _acc_sScaleYpostDec(); }
    inline float _acc_sScaleYpreInc()			{ return _acc_sScaleY(_acc_gScaleY()+1); }
    inline float _acc_sScaleY$preInc()			{ CHCKTHIS; return _acc_sScaleYpreInc(); }
    inline float _acc_sScaleYpreDec()			{ return _acc_sScaleY(_acc_gScaleY()-1); }
    inline float _acc_sScaleY$preDec()			{ CHCKTHIS; return _acc_sScaleYpreDec(); }
    inline float _acc_sScaleYAddEq(float value)	{ return _acc_sScaleY(_acc_gScaleY() + value); }
    inline float _acc_sScaleY$AddEq(float value)			{ CHCKTHIS; return _acc_sScaleYAddEq(value); }
    inline float _acc_sScaleYSubEq(float value)	{ return _acc_sScaleY(_acc_gScaleY() - value); }
    inline float _acc_sScaleY$SubEq(float value)			{ CHCKTHIS; return _acc_sScaleYSubEq(value); }
    inline float _acc_sScaleYMulEq(float value)	{ return _acc_sScaleY(_acc_gScaleY() * value); }
    inline float _acc_sScaleY$MulEq(float value)			{ CHCKTHIS; return _acc_sScaleYMulEq(value); }
    inline float _acc_sScaleYDivEq(float value)	{ return _acc_sScaleY(_acc_gScaleY() / value); }
    inline float _acc_sScaleY$DivEq(float value)			{ CHCKTHIS; return _acc_sScaleYDivEq(value); }
    inline float _acc_sScaleYModEq(float value)	{  float orig = _acc_gScaleY(); s32 tmp = (s32)(orig / value); return _acc_sScaleY(orig - (tmp * value)); }
    inline float _acc_sScaleY$ModEq(float value)			{ CHCKTHIS; return _acc_sScaleYModEq(value); }
    inline float _acc_gRotation();
    inline float _acc_gRotation$();

    inline float _acc_sRotation(float value);
    inline float _acc_sRotation$(float value);
    inline float _acc_sRotationpostInc()			{ float tmp; _acc_sRotation((tmp = _acc_gRotation())+1); return tmp; }
    inline float _acc_sRotation$postInc()			{ CHCKTHIS; return _acc_sRotationpostInc(); }
    inline float _acc_sRotationpostDec()			{ float tmp; _acc_sRotation((tmp = _acc_gRotation())-1); return tmp; }
    inline float _acc_sRotation$postDec()			{ CHCKTHIS; return _acc_sRotationpostDec(); }
    inline float _acc_sRotationpreInc()			{ return _acc_sRotation(_acc_gRotation()+1); }
    inline float _acc_sRotation$preInc()			{ CHCKTHIS; return _acc_sRotationpreInc(); }
    inline float _acc_sRotationpreDec()			{ return _acc_sRotation(_acc_gRotation()-1); }
    inline float _acc_sRotation$preDec()			{ CHCKTHIS; return _acc_sRotationpreDec(); }
    inline float _acc_sRotationAddEq(float value)	{ return _acc_sRotation(_acc_gRotation() + value); }
    inline float _acc_sRotation$AddEq(float value)			{ CHCKTHIS; return _acc_sRotationAddEq(value); }
    inline float _acc_sRotationSubEq(float value)	{ return _acc_sRotation(_acc_gRotation() - value); }
    inline float _acc_sRotation$SubEq(float value)			{ CHCKTHIS; return _acc_sRotationSubEq(value); }
    inline float _acc_sRotationMulEq(float value)	{ return _acc_sRotation(_acc_gRotation() * value); }
    inline float _acc_sRotation$MulEq(float value)			{ CHCKTHIS; return _acc_sRotationMulEq(value); }
    inline float _acc_sRotationDivEq(float value)	{ return _acc_sRotation(_acc_gRotation() / value); }
    inline float _acc_sRotation$DivEq(float value)			{ CHCKTHIS; return _acc_sRotationDivEq(value); }
    inline float _acc_sRotationModEq(float value)	{  float orig = _acc_gRotation(); s32 tmp = (s32)(orig / value); return _acc_sRotation(orig - (tmp * value)); }
    inline float _acc_sRotation$ModEq(float value)			{ CHCKTHIS; return _acc_sRotationModEq(value); }
    inline float _acc_gX();
    inline float _acc_gX$();

    inline float _acc_sX(float value);
    inline float _acc_sX$(float value);
    inline float _acc_sXpostInc()			{ float tmp; _acc_sX((tmp = _acc_gX())+1); return tmp; }
    inline float _acc_sX$postInc()			{ CHCKTHIS; return _acc_sXpostInc(); }
    inline float _acc_sXpostDec()			{ float tmp; _acc_sX((tmp = _acc_gX())-1); return tmp; }
    inline float _acc_sX$postDec()			{ CHCKTHIS; return _acc_sXpostDec(); }
    inline float _acc_sXpreInc()			{ return _acc_sX(_acc_gX()+1); }
    inline float _acc_sX$preInc()			{ CHCKTHIS; return _acc_sXpreInc(); }
    inline float _acc_sXpreDec()			{ return _acc_sX(_acc_gX()-1); }
    inline float _acc_sX$preDec()			{ CHCKTHIS; return _acc_sXpreDec(); }
    inline float _acc_sXAddEq(float value)	{ return _acc_sX(_acc_gX() + value); }
    inline float _acc_sX$AddEq(float value)			{ CHCKTHIS; return _acc_sXAddEq(value); }
    inline float _acc_sXSubEq(float value)	{ return _acc_sX(_acc_gX() - value); }
    inline float _acc_sX$SubEq(float value)			{ CHCKTHIS; return _acc_sXSubEq(value); }
    inline float _acc_sXMulEq(float value)	{ return _acc_sX(_acc_gX() * value); }
    inline float _acc_sX$MulEq(float value)			{ CHCKTHIS; return _acc_sXMulEq(value); }
    inline float _acc_sXDivEq(float value)	{ return _acc_sX(_acc_gX() / value); }
    inline float _acc_sX$DivEq(float value)			{ CHCKTHIS; return _acc_sXDivEq(value); }
    inline float _acc_sXModEq(float value)	{  float orig = _acc_gX(); s32 tmp = (s32)(orig / value); return _acc_sX(orig - (tmp * value)); }
    inline float _acc_sX$ModEq(float value)			{ CHCKTHIS; return _acc_sXModEq(value); }
    inline float _acc_gY();
    inline float _acc_gY$();

    inline float _acc_sY(float value);
    inline float _acc_sY$(float value);
    inline float _acc_sYpostInc()			{ float tmp; _acc_sY((tmp = _acc_gY())+1); return tmp; }
    inline float _acc_sY$postInc()			{ CHCKTHIS; return _acc_sYpostInc(); }
    inline float _acc_sYpostDec()			{ float tmp; _acc_sY((tmp = _acc_gY())-1); return tmp; }
    inline float _acc_sY$postDec()			{ CHCKTHIS; return _acc_sYpostDec(); }
    inline float _acc_sYpreInc()			{ return _acc_sY(_acc_gY()+1); }
    inline float _acc_sY$preInc()			{ CHCKTHIS; return _acc_sYpreInc(); }
    inline float _acc_sYpreDec()			{ return _acc_sY(_acc_gY()-1); }
    inline float _acc_sY$preDec()			{ CHCKTHIS; return _acc_sYpreDec(); }
    inline float _acc_sYAddEq(float value)	{ return _acc_sY(_acc_gY() + value); }
    inline float _acc_sY$AddEq(float value)			{ CHCKTHIS; return _acc_sYAddEq(value); }
    inline float _acc_sYSubEq(float value)	{ return _acc_sY(_acc_gY() - value); }
    inline float _acc_sY$SubEq(float value)			{ CHCKTHIS; return _acc_sYSubEq(value); }
    inline float _acc_sYMulEq(float value)	{ return _acc_sY(_acc_gY() * value); }
    inline float _acc_sY$MulEq(float value)			{ CHCKTHIS; return _acc_sYMulEq(value); }
    inline float _acc_sYDivEq(float value)	{ return _acc_sY(_acc_gY() / value); }
    inline float _acc_sY$DivEq(float value)			{ CHCKTHIS; return _acc_sYDivEq(value); }
    inline float _acc_sYModEq(float value)	{  float orig = _acc_gY(); s32 tmp = (s32)(orig / value); return _acc_sY(orig - (tmp * value)); }
    inline float _acc_sY$ModEq(float value)			{ CHCKTHIS; return _acc_sYModEq(value); }
    inline bool _acc_gIsVisible();
    inline bool _acc_gIsVisible$();

    inline bool _acc_sIsVisible(bool value);
    inline bool _acc_sIsVisible$(bool value);
    inline u32 _acc_gArgb();
    inline u32 _acc_gArgb$();

    inline u32 _acc_sArgb(u32 value);
    inline u32 _acc_sArgb$(u32 value);
    inline u32 _acc_sArgbpostInc()			{ u32 tmp; _acc_sArgb((tmp = _acc_gArgb())+1); return tmp; }
    inline u32 _acc_sArgb$postInc()			{ CHCKTHIS; return _acc_sArgbpostInc(); }
    inline u32 _acc_sArgbpostDec()			{ u32 tmp; _acc_sArgb((tmp = _acc_gArgb())-1); return tmp; }
    inline u32 _acc_sArgb$postDec()			{ CHCKTHIS; return _acc_sArgbpostDec(); }
    inline u32 _acc_sArgbpreInc()			{ return _acc_sArgb(_acc_gArgb()+1); }
    inline u32 _acc_sArgb$preInc()			{ CHCKTHIS; return _acc_sArgbpreInc(); }
    inline u32 _acc_sArgbpreDec()			{ return _acc_sArgb(_acc_gArgb()-1); }
    inline u32 _acc_sArgb$preDec()			{ CHCKTHIS; return _acc_sArgbpreDec(); }
    inline u32 _acc_sArgbAddEq(u32 value)	{ return _acc_sArgb(_acc_gArgb() + value); }
    inline u32 _acc_sArgb$AddEq(u32 value)			{ CHCKTHIS; return _acc_sArgbAddEq(value); }
    inline u32 _acc_sArgbSubEq(u32 value)	{ return _acc_sArgb(_acc_gArgb() - value); }
    inline u32 _acc_sArgb$SubEq(u32 value)			{ CHCKTHIS; return _acc_sArgbSubEq(value); }
    inline u32 _acc_sArgbMulEq(u32 value)	{ return _acc_sArgb(_acc_gArgb() * value); }
    inline u32 _acc_sArgb$MulEq(u32 value)			{ CHCKTHIS; return _acc_sArgbMulEq(value); }
    inline u32 _acc_sArgbDivEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sArgb(_acc_gArgb() / value); }
    inline u32 _acc_sArgb$DivEq(u32 value)			{ CHCKTHIS; return _acc_sArgbDivEq(value); }
    inline u32 _acc_sArgbModEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sArgb(_acc_gArgb() % value); }
    inline u32 _acc_sArgb$ModEq(u32 value)			{ CHCKTHIS; return _acc_sArgbModEq(value); }
    inline u32 _acc_sArgbXorEq(u32 value)	{ return _acc_sArgb(_acc_gArgb() ^ value); }
    inline u32 _acc_sArgb$XorEq(u32 value)			{ CHCKTHIS; return _acc_sArgbXorEq(value); }
    inline u32 _acc_sArgbAndEq(u32 value)	{ return _acc_sArgb(_acc_gArgb() & value); }
    inline u32 _acc_sArgb$AndEq(u32 value)			{ CHCKTHIS; return _acc_sArgbAndEq(value); }
    inline u32 _acc_sArgbOrEq(u32 value)		{ return _acc_sArgb(_acc_gArgb() | value); }
    inline u32 _acc_sArgb$OrEq(u32 value)			{ CHCKTHIS; return _acc_sArgbOrEq(value); }
    inline u32 _acc_sArgbRShiftEq(u32 value)	{ return _acc_sArgb(_acc_gArgb() >> value); }
    inline u32 _acc_sArgb$RShiftEq(u32 value)			{ CHCKTHIS; return _acc_sArgbRShiftEq(value); }
    inline u32 _acc_sArgbLShiftEq(u32 value)	{ return _acc_sArgb(_acc_gArgb() << value); }
    inline u32 _acc_sArgb$LShiftEq(u32 value)			{ CHCKTHIS; return _acc_sArgbLShiftEq(value); }
    inline bool _acc_gIsNodeAnim();
    inline bool _acc_gIsNodeAnim$();

    static bool _ext_CKLBUITask_getVisible(s32* p);
    static void _ext_CKLBUITask_setVisible(s32* p,bool isVisible);
    static float _ext_CKLBUITask_getScaleX(s32* p);
    static void _ext_CKLBUITask_setScaleX(s32* p,float scaleX);
    static float _ext_CKLBUITask_getScaleY(s32* p);
    static void _ext_CKLBUITask_setScaleY(s32* p,float scaleY);
    static float _ext_CKLBUITask_getX(s32* p);
    static void _ext_CKLBUITask_setX(s32* p,float x);
    static float _ext_CKLBUITask_getY(s32* p);
    static void _ext_CKLBUITask_setY(s32* p,float y);
    static float _ext_CKLBUITask_getRotation(s32* p);
    static void _ext_CKLBUITask_setRotation(s32* p,float rotation);
    static u32 _ext_CKLBUITask_getArgb(s32* p);
    static void _ext_CKLBUITask_setArgb(s32* p,u32 argb);
    static bool _ext_CKLBUITask_isAnim(s32* p);
    static void _ext_CKLBUITask_play(s32* p);
    static void _ext_CKLBUITask_stop(s32* p);
    static bool _ext_CKLBUITask_setParamCount(s32* p,u32 splineCount,u32 maxKeyCount);
    static void _ext_CKLBUITask_setTarget(s32* p,u32 splineIndex,s32 targetParameter);
    static void _ext_CKLBUITask_addKeys(s32* p,u32 splineIndex,u32 time,s32 value);
    static void _ext_CKLBUITask_addKeysFixed(s32* p,u32 splineIndex,u32 time,s32 fixed16Value);
    static void _ext_CKLBUITask_generateAnimation(s32* p);
    static bool _ext_CKLBUITask_reconnect(s32* p,s32* nodeName);
    CKLBUITask(u32 classID);
    EnginePrototype::NodeIterator* _ref_getIterator(EnginePrototype::NodeIterator*& nodeIterator);
    inline EnginePrototype::NodeIterator* getIterator$(EnginePrototype::NodeIterator*& nodeIterator);
    inline EnginePrototype::NodeIterator* getIterator(EnginePrototype::NodeIterator*& nodeIterator);
    EnginePrototype::NodeIterator* _ref_getIteratorFromName(System::String* name,EnginePrototype::NodeIterator*& nodeIterator);
    inline EnginePrototype::NodeIterator* getIteratorFromName$(System::String* name,EnginePrototype::NodeIterator*& nodeIterator);
    inline EnginePrototype::NodeIterator* getIteratorFromName(System::String* name,EnginePrototype::NodeIterator*& nodeIterator);
    void nodeReconnect(System::String* nodeName);
    inline void nodeReconnect$(System::String* nodeName);
    void animationPlay();
    inline void animationPlay$();
    void animationStop();
    inline void animationStop$();
    void setScale(float scaleX,float scaleY);
    inline void setScale$(float scaleX,float scaleY);
    void setAnimSpline(EnginePrototype::AnimSpline_inner9* splineArray);
    inline void setAnimSpline$(EnginePrototype::AnimSpline_inner9* splineArray);
    CKLBUITask();
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 239;
};
class EnginePrototype::CKLBIntervalTimer : public EnginePrototype::CKLBUITask {
friend class CallBack_inner24;

public:
    enum ETIMERMODE {
        INTERVALTIMER_TIME = 0,
        INTERVALTIMER_FRAME,
        _ForceWORD_ETIMERMODE = 0x7FFFFFFF
    };

    void _ctor_CKLBIntervalTimer();
    static u32 s_classID;
    inline static u32 _ss_classIDDivEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID /= value; }
    inline static u32 _ss_classIDModEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID %= value; }

    EnginePrototype::_Delegate_Base_CallBack_inner24* m_callback;
    inline EnginePrototype::_Delegate_Base_CallBack_inner24*& _gm_callback$() { CHCKTHIS; return m_callback; }
    inline EnginePrototype::_Delegate_Base_CallBack_inner24* _sm_callback(EnginePrototype::_Delegate_Base_CallBack_inner24* _$value);
    inline EnginePrototype::_Delegate_Base_CallBack_inner24* _sm_callback$(EnginePrototype::_Delegate_Base_CallBack_inner24* _$value);

    inline s32 _acc_gMode();
    inline s32 _acc_gMode$();

    inline u32 _acc_gInterval();
    inline u32 _acc_gInterval$();

    inline u32 _acc_sInterval(u32 value);
    inline u32 _acc_sInterval$(u32 value);
    inline u32 _acc_sIntervalpostInc()			{ u32 tmp; _acc_sInterval((tmp = _acc_gInterval())+1); return tmp; }
    inline u32 _acc_sInterval$postInc()			{ CHCKTHIS; return _acc_sIntervalpostInc(); }
    inline u32 _acc_sIntervalpostDec()			{ u32 tmp; _acc_sInterval((tmp = _acc_gInterval())-1); return tmp; }
    inline u32 _acc_sInterval$postDec()			{ CHCKTHIS; return _acc_sIntervalpostDec(); }
    inline u32 _acc_sIntervalpreInc()			{ return _acc_sInterval(_acc_gInterval()+1); }
    inline u32 _acc_sInterval$preInc()			{ CHCKTHIS; return _acc_sIntervalpreInc(); }
    inline u32 _acc_sIntervalpreDec()			{ return _acc_sInterval(_acc_gInterval()-1); }
    inline u32 _acc_sInterval$preDec()			{ CHCKTHIS; return _acc_sIntervalpreDec(); }
    inline u32 _acc_sIntervalAddEq(u32 value)	{ return _acc_sInterval(_acc_gInterval() + value); }
    inline u32 _acc_sInterval$AddEq(u32 value)			{ CHCKTHIS; return _acc_sIntervalAddEq(value); }
    inline u32 _acc_sIntervalSubEq(u32 value)	{ return _acc_sInterval(_acc_gInterval() - value); }
    inline u32 _acc_sInterval$SubEq(u32 value)			{ CHCKTHIS; return _acc_sIntervalSubEq(value); }
    inline u32 _acc_sIntervalMulEq(u32 value)	{ return _acc_sInterval(_acc_gInterval() * value); }
    inline u32 _acc_sInterval$MulEq(u32 value)			{ CHCKTHIS; return _acc_sIntervalMulEq(value); }
    inline u32 _acc_sIntervalDivEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sInterval(_acc_gInterval() / value); }
    inline u32 _acc_sInterval$DivEq(u32 value)			{ CHCKTHIS; return _acc_sIntervalDivEq(value); }
    inline u32 _acc_sIntervalModEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sInterval(_acc_gInterval() % value); }
    inline u32 _acc_sInterval$ModEq(u32 value)			{ CHCKTHIS; return _acc_sIntervalModEq(value); }
    inline u32 _acc_sIntervalXorEq(u32 value)	{ return _acc_sInterval(_acc_gInterval() ^ value); }
    inline u32 _acc_sInterval$XorEq(u32 value)			{ CHCKTHIS; return _acc_sIntervalXorEq(value); }
    inline u32 _acc_sIntervalAndEq(u32 value)	{ return _acc_sInterval(_acc_gInterval() & value); }
    inline u32 _acc_sInterval$AndEq(u32 value)			{ CHCKTHIS; return _acc_sIntervalAndEq(value); }
    inline u32 _acc_sIntervalOrEq(u32 value)		{ return _acc_sInterval(_acc_gInterval() | value); }
    inline u32 _acc_sInterval$OrEq(u32 value)			{ CHCKTHIS; return _acc_sIntervalOrEq(value); }
    inline u32 _acc_sIntervalRShiftEq(u32 value)	{ return _acc_sInterval(_acc_gInterval() >> value); }
    inline u32 _acc_sInterval$RShiftEq(u32 value)			{ CHCKTHIS; return _acc_sIntervalRShiftEq(value); }
    inline u32 _acc_sIntervalLShiftEq(u32 value)	{ return _acc_sInterval(_acc_gInterval() << value); }
    inline u32 _acc_sInterval$LShiftEq(u32 value)			{ CHCKTHIS; return _acc_sIntervalLShiftEq(value); }
    inline bool _acc_gRepeat();
    inline bool _acc_gRepeat$();

    inline bool _acc_sRepeat(bool value);
    inline bool _acc_sRepeat$(bool value);
    static s32* _ext_CKLBIntervalTimer_create(s32* pParent,u32 interval,bool repeat,u8 mode);
    static u32 _ext_CKLBIntervalTimer_getTimerID(s32* p);
    static void _ext_CKLBIntervalTimer_setTimerID(s32* p,u32 ID);
    static bool _ext_CKLBIntervalTimer_getRepeat(s32* p);
    static void _ext_CKLBIntervalTimer_setRepeat(s32* p,bool boolean);
    static u32 _ext_CKLBIntervalTimer_getInterval(s32* p);
    static void _ext_CKLBIntervalTimer_setInterval(s32* p,u32 interval);
    static u8 _ext_CKLBIntervalTimer_getMode(s32* p);
    CKLBIntervalTimer(EnginePrototype::CKLBTask* parent,u32 interval,EnginePrototype::_Delegate_Base_CallBack_inner24* callback,bool repeat,s32 mode);
    CKLBIntervalTimer();
    virtual void doSetupCallbacks();
    inline void doSetupCallbacks$();
    virtual void setDelegate(System::Delegate* anyDelegate,System::String* delegateName);
    inline void setDelegate$(System::Delegate* anyDelegate,System::String* delegateName);
    virtual void callBackFunction();
    inline void callBackFunction$();
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 148;
};
class EnginePrototype::CKLBUICanvas : public EnginePrototype::CKLBUITask {
friend class CallBack_inner29;

public:
    void _ctor_CKLBUICanvas();
    static u32 s_classID;
    inline static u32 _ss_classIDDivEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID /= value; }
    inline static u32 _ss_classIDModEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID %= value; }

    EnginePrototype::_Delegate_Base_CallBack_inner29* m_callback;
    inline EnginePrototype::_Delegate_Base_CallBack_inner29*& _gm_callback$() { CHCKTHIS; return m_callback; }
    inline EnginePrototype::_Delegate_Base_CallBack_inner29* _sm_callback(EnginePrototype::_Delegate_Base_CallBack_inner29* _$value);
    inline EnginePrototype::_Delegate_Base_CallBack_inner29* _sm_callback$(EnginePrototype::_Delegate_Base_CallBack_inner29* _$value);

    inline u32 _acc_gOrder();
    inline u32 _acc_gOrder$();

    inline u32 _acc_sOrder(u32 value);
    inline u32 _acc_sOrder$(u32 value);
    inline u32 _acc_sOrderpostInc()			{ u32 tmp; _acc_sOrder((tmp = _acc_gOrder())+1); return tmp; }
    inline u32 _acc_sOrder$postInc()			{ CHCKTHIS; return _acc_sOrderpostInc(); }
    inline u32 _acc_sOrderpostDec()			{ u32 tmp; _acc_sOrder((tmp = _acc_gOrder())-1); return tmp; }
    inline u32 _acc_sOrder$postDec()			{ CHCKTHIS; return _acc_sOrderpostDec(); }
    inline u32 _acc_sOrderpreInc()			{ return _acc_sOrder(_acc_gOrder()+1); }
    inline u32 _acc_sOrder$preInc()			{ CHCKTHIS; return _acc_sOrderpreInc(); }
    inline u32 _acc_sOrderpreDec()			{ return _acc_sOrder(_acc_gOrder()-1); }
    inline u32 _acc_sOrder$preDec()			{ CHCKTHIS; return _acc_sOrderpreDec(); }
    inline u32 _acc_sOrderAddEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() + value); }
    inline u32 _acc_sOrder$AddEq(u32 value)			{ CHCKTHIS; return _acc_sOrderAddEq(value); }
    inline u32 _acc_sOrderSubEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() - value); }
    inline u32 _acc_sOrder$SubEq(u32 value)			{ CHCKTHIS; return _acc_sOrderSubEq(value); }
    inline u32 _acc_sOrderMulEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() * value); }
    inline u32 _acc_sOrder$MulEq(u32 value)			{ CHCKTHIS; return _acc_sOrderMulEq(value); }
    inline u32 _acc_sOrderDivEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sOrder(_acc_gOrder() / value); }
    inline u32 _acc_sOrder$DivEq(u32 value)			{ CHCKTHIS; return _acc_sOrderDivEq(value); }
    inline u32 _acc_sOrderModEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sOrder(_acc_gOrder() % value); }
    inline u32 _acc_sOrder$ModEq(u32 value)			{ CHCKTHIS; return _acc_sOrderModEq(value); }
    inline u32 _acc_sOrderXorEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() ^ value); }
    inline u32 _acc_sOrder$XorEq(u32 value)			{ CHCKTHIS; return _acc_sOrderXorEq(value); }
    inline u32 _acc_sOrderAndEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() & value); }
    inline u32 _acc_sOrder$AndEq(u32 value)			{ CHCKTHIS; return _acc_sOrderAndEq(value); }
    inline u32 _acc_sOrderOrEq(u32 value)		{ return _acc_sOrder(_acc_gOrder() | value); }
    inline u32 _acc_sOrder$OrEq(u32 value)			{ CHCKTHIS; return _acc_sOrderOrEq(value); }
    inline u32 _acc_sOrderRShiftEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() >> value); }
    inline u32 _acc_sOrder$RShiftEq(u32 value)			{ CHCKTHIS; return _acc_sOrderRShiftEq(value); }
    inline u32 _acc_sOrderLShiftEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() << value); }
    inline u32 _acc_sOrder$LShiftEq(u32 value)			{ CHCKTHIS; return _acc_sOrderLShiftEq(value); }
    inline u32 _acc_gIdxMax();
    inline u32 _acc_gIdxMax$();

    inline bool _acc_sFreeze(bool value);
    inline bool _acc_sFreeze$(bool value);
    static s32* _ext_CKLBUICanvas_create(s32* pParent,u32 order,float x,float y,u32 vertexMax,u32 indexMax);
    static u32 _ext_CKLBUICanvas_getOrder(s32* p);
    static void _ext_CKLBUICanvas_setOrder(s32* p,u32 order);
    static u32 _ext_CKLBUICanvas_getIdxMax(s32* p);
    static bool _ext_CKLBUICanvas_addResource(s32* p,s32* asset);
    static void _ext_CKLBUICanvas_setFreeze(s32* p,bool freeze);
    static void _ext_CKLBUICanvas_drawImage(s32* p,float x,float y,u32 idx,u32 color);
    static void _ext_CKLBUICanvas_drawImageScale(s32* p,float x,float y,float scale,u32 idx,u32 color);
    static void _ext_CKLBUICanvas_fillRect(s32* p,float x,float y,float w,float h,u32 color);
    static void _ext_CKLBUICanvas_startDynamicSection(s32* p,u32 idx);
    static void _ext_CKLBUICanvas_endDynamicSection(s32* p,u32 idx);
    static void _ext_CKLBUICanvas_dynamicSectionTranslate(s32* p,u32 idx,float deltaX,float deltaY);
    static void _ext_CKLBUICanvas_dynamicSectionColor(s32* p,u32 idx,u32 color);
    CKLBUICanvas(EnginePrototype::CKLBUITask* parent,u32 order,float x,float y,u32 vertexMax,u32 indexMax,EnginePrototype::_Delegate_Base_CallBack_inner29* onDrawCallBack);
    CKLBUICanvas();
    virtual void doSetupCallbacks();
    inline void doSetupCallbacks$();
    virtual void setDelegate(System::Delegate* anyDelegate,System::String* delegateName);
    inline void setDelegate$(System::Delegate* anyDelegate,System::String* delegateName);
    virtual void callBackFunction();
    inline void callBackFunction$();
    bool addResource(System::String* asset);
    inline bool addResource$(System::String* asset);
    void drawImage(float x,float y,u32 idx,u32 color);
    inline void drawImage$(float x,float y,u32 idx,u32 color);
    void drawImageScale(float x,float y,float scale,u32 idx,u32 color);
    inline void drawImageScale$(float x,float y,float scale,u32 idx,u32 color);
    void fillRect(float x,float y,float w,float h,u32 color);
    inline void fillRect$(float x,float y,float w,float h,u32 color);
    void startDynamicSection(u32 idx);
    inline void startDynamicSection$(u32 idx);
    void endDynamicSection(u32 idx);
    inline void endDynamicSection$(u32 idx);
    void dynamicSectionTranslate(u32 idx,float deltaX,float deltaY);
    inline void dynamicSectionTranslate$(u32 idx,float deltaX,float deltaY);
    void dynamicSectionColor(u32 idx,u32 color);
    inline void dynamicSectionColor$(u32 idx,u32 color);
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 166;
};
class EnginePrototype::CKLBUIClip : public EnginePrototype::CKLBUITask {

public:
    void _ctor_CKLBUIClip();
    static u32 s_classID;
    inline static u32 _ss_classIDDivEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID /= value; }
    inline static u32 _ss_classIDModEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID %= value; }

    inline u32 _acc_gOrder();
    inline u32 _acc_gOrder$();

    inline u32 _acc_sOrder(u32 value);
    inline u32 _acc_sOrder$(u32 value);
    inline u32 _acc_sOrderpostInc()			{ u32 tmp; _acc_sOrder((tmp = _acc_gOrder())+1); return tmp; }
    inline u32 _acc_sOrder$postInc()			{ CHCKTHIS; return _acc_sOrderpostInc(); }
    inline u32 _acc_sOrderpostDec()			{ u32 tmp; _acc_sOrder((tmp = _acc_gOrder())-1); return tmp; }
    inline u32 _acc_sOrder$postDec()			{ CHCKTHIS; return _acc_sOrderpostDec(); }
    inline u32 _acc_sOrderpreInc()			{ return _acc_sOrder(_acc_gOrder()+1); }
    inline u32 _acc_sOrder$preInc()			{ CHCKTHIS; return _acc_sOrderpreInc(); }
    inline u32 _acc_sOrderpreDec()			{ return _acc_sOrder(_acc_gOrder()-1); }
    inline u32 _acc_sOrder$preDec()			{ CHCKTHIS; return _acc_sOrderpreDec(); }
    inline u32 _acc_sOrderAddEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() + value); }
    inline u32 _acc_sOrder$AddEq(u32 value)			{ CHCKTHIS; return _acc_sOrderAddEq(value); }
    inline u32 _acc_sOrderSubEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() - value); }
    inline u32 _acc_sOrder$SubEq(u32 value)			{ CHCKTHIS; return _acc_sOrderSubEq(value); }
    inline u32 _acc_sOrderMulEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() * value); }
    inline u32 _acc_sOrder$MulEq(u32 value)			{ CHCKTHIS; return _acc_sOrderMulEq(value); }
    inline u32 _acc_sOrderDivEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sOrder(_acc_gOrder() / value); }
    inline u32 _acc_sOrder$DivEq(u32 value)			{ CHCKTHIS; return _acc_sOrderDivEq(value); }
    inline u32 _acc_sOrderModEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sOrder(_acc_gOrder() % value); }
    inline u32 _acc_sOrder$ModEq(u32 value)			{ CHCKTHIS; return _acc_sOrderModEq(value); }
    inline u32 _acc_sOrderXorEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() ^ value); }
    inline u32 _acc_sOrder$XorEq(u32 value)			{ CHCKTHIS; return _acc_sOrderXorEq(value); }
    inline u32 _acc_sOrderAndEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() & value); }
    inline u32 _acc_sOrder$AndEq(u32 value)			{ CHCKTHIS; return _acc_sOrderAndEq(value); }
    inline u32 _acc_sOrderOrEq(u32 value)		{ return _acc_sOrder(_acc_gOrder() | value); }
    inline u32 _acc_sOrder$OrEq(u32 value)			{ CHCKTHIS; return _acc_sOrderOrEq(value); }
    inline u32 _acc_sOrderRShiftEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() >> value); }
    inline u32 _acc_sOrder$RShiftEq(u32 value)			{ CHCKTHIS; return _acc_sOrderRShiftEq(value); }
    inline u32 _acc_sOrderLShiftEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() << value); }
    inline u32 _acc_sOrder$LShiftEq(u32 value)			{ CHCKTHIS; return _acc_sOrderLShiftEq(value); }
    inline u32 _acc_gMaxOrder();
    inline u32 _acc_gMaxOrder$();

    inline u32 _acc_sMaxOrder(u32 value);
    inline u32 _acc_sMaxOrder$(u32 value);
    inline u32 _acc_sMaxOrderpostInc()			{ u32 tmp; _acc_sMaxOrder((tmp = _acc_gMaxOrder())+1); return tmp; }
    inline u32 _acc_sMaxOrder$postInc()			{ CHCKTHIS; return _acc_sMaxOrderpostInc(); }
    inline u32 _acc_sMaxOrderpostDec()			{ u32 tmp; _acc_sMaxOrder((tmp = _acc_gMaxOrder())-1); return tmp; }
    inline u32 _acc_sMaxOrder$postDec()			{ CHCKTHIS; return _acc_sMaxOrderpostDec(); }
    inline u32 _acc_sMaxOrderpreInc()			{ return _acc_sMaxOrder(_acc_gMaxOrder()+1); }
    inline u32 _acc_sMaxOrder$preInc()			{ CHCKTHIS; return _acc_sMaxOrderpreInc(); }
    inline u32 _acc_sMaxOrderpreDec()			{ return _acc_sMaxOrder(_acc_gMaxOrder()-1); }
    inline u32 _acc_sMaxOrder$preDec()			{ CHCKTHIS; return _acc_sMaxOrderpreDec(); }
    inline u32 _acc_sMaxOrderAddEq(u32 value)	{ return _acc_sMaxOrder(_acc_gMaxOrder() + value); }
    inline u32 _acc_sMaxOrder$AddEq(u32 value)			{ CHCKTHIS; return _acc_sMaxOrderAddEq(value); }
    inline u32 _acc_sMaxOrderSubEq(u32 value)	{ return _acc_sMaxOrder(_acc_gMaxOrder() - value); }
    inline u32 _acc_sMaxOrder$SubEq(u32 value)			{ CHCKTHIS; return _acc_sMaxOrderSubEq(value); }
    inline u32 _acc_sMaxOrderMulEq(u32 value)	{ return _acc_sMaxOrder(_acc_gMaxOrder() * value); }
    inline u32 _acc_sMaxOrder$MulEq(u32 value)			{ CHCKTHIS; return _acc_sMaxOrderMulEq(value); }
    inline u32 _acc_sMaxOrderDivEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sMaxOrder(_acc_gMaxOrder() / value); }
    inline u32 _acc_sMaxOrder$DivEq(u32 value)			{ CHCKTHIS; return _acc_sMaxOrderDivEq(value); }
    inline u32 _acc_sMaxOrderModEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sMaxOrder(_acc_gMaxOrder() % value); }
    inline u32 _acc_sMaxOrder$ModEq(u32 value)			{ CHCKTHIS; return _acc_sMaxOrderModEq(value); }
    inline u32 _acc_sMaxOrderXorEq(u32 value)	{ return _acc_sMaxOrder(_acc_gMaxOrder() ^ value); }
    inline u32 _acc_sMaxOrder$XorEq(u32 value)			{ CHCKTHIS; return _acc_sMaxOrderXorEq(value); }
    inline u32 _acc_sMaxOrderAndEq(u32 value)	{ return _acc_sMaxOrder(_acc_gMaxOrder() & value); }
    inline u32 _acc_sMaxOrder$AndEq(u32 value)			{ CHCKTHIS; return _acc_sMaxOrderAndEq(value); }
    inline u32 _acc_sMaxOrderOrEq(u32 value)		{ return _acc_sMaxOrder(_acc_gMaxOrder() | value); }
    inline u32 _acc_sMaxOrder$OrEq(u32 value)			{ CHCKTHIS; return _acc_sMaxOrderOrEq(value); }
    inline u32 _acc_sMaxOrderRShiftEq(u32 value)	{ return _acc_sMaxOrder(_acc_gMaxOrder() >> value); }
    inline u32 _acc_sMaxOrder$RShiftEq(u32 value)			{ CHCKTHIS; return _acc_sMaxOrderRShiftEq(value); }
    inline u32 _acc_sMaxOrderLShiftEq(u32 value)	{ return _acc_sMaxOrder(_acc_gMaxOrder() << value); }
    inline u32 _acc_sMaxOrder$LShiftEq(u32 value)			{ CHCKTHIS; return _acc_sMaxOrderLShiftEq(value); }
    inline float _acc_gWidth();
    inline float _acc_gWidth$();

    inline float _acc_sWidth(float value);
    inline float _acc_sWidth$(float value);
    inline float _acc_sWidthpostInc()			{ float tmp; _acc_sWidth((tmp = _acc_gWidth())+1); return tmp; }
    inline float _acc_sWidth$postInc()			{ CHCKTHIS; return _acc_sWidthpostInc(); }
    inline float _acc_sWidthpostDec()			{ float tmp; _acc_sWidth((tmp = _acc_gWidth())-1); return tmp; }
    inline float _acc_sWidth$postDec()			{ CHCKTHIS; return _acc_sWidthpostDec(); }
    inline float _acc_sWidthpreInc()			{ return _acc_sWidth(_acc_gWidth()+1); }
    inline float _acc_sWidth$preInc()			{ CHCKTHIS; return _acc_sWidthpreInc(); }
    inline float _acc_sWidthpreDec()			{ return _acc_sWidth(_acc_gWidth()-1); }
    inline float _acc_sWidth$preDec()			{ CHCKTHIS; return _acc_sWidthpreDec(); }
    inline float _acc_sWidthAddEq(float value)	{ return _acc_sWidth(_acc_gWidth() + value); }
    inline float _acc_sWidth$AddEq(float value)			{ CHCKTHIS; return _acc_sWidthAddEq(value); }
    inline float _acc_sWidthSubEq(float value)	{ return _acc_sWidth(_acc_gWidth() - value); }
    inline float _acc_sWidth$SubEq(float value)			{ CHCKTHIS; return _acc_sWidthSubEq(value); }
    inline float _acc_sWidthMulEq(float value)	{ return _acc_sWidth(_acc_gWidth() * value); }
    inline float _acc_sWidth$MulEq(float value)			{ CHCKTHIS; return _acc_sWidthMulEq(value); }
    inline float _acc_sWidthDivEq(float value)	{ return _acc_sWidth(_acc_gWidth() / value); }
    inline float _acc_sWidth$DivEq(float value)			{ CHCKTHIS; return _acc_sWidthDivEq(value); }
    inline float _acc_sWidthModEq(float value)	{  float orig = _acc_gWidth(); s32 tmp = (s32)(orig / value); return _acc_sWidth(orig - (tmp * value)); }
    inline float _acc_sWidth$ModEq(float value)			{ CHCKTHIS; return _acc_sWidthModEq(value); }
    inline float _acc_gHeight();
    inline float _acc_gHeight$();

    inline float _acc_sHeight(float value);
    inline float _acc_sHeight$(float value);
    inline float _acc_sHeightpostInc()			{ float tmp; _acc_sHeight((tmp = _acc_gHeight())+1); return tmp; }
    inline float _acc_sHeight$postInc()			{ CHCKTHIS; return _acc_sHeightpostInc(); }
    inline float _acc_sHeightpostDec()			{ float tmp; _acc_sHeight((tmp = _acc_gHeight())-1); return tmp; }
    inline float _acc_sHeight$postDec()			{ CHCKTHIS; return _acc_sHeightpostDec(); }
    inline float _acc_sHeightpreInc()			{ return _acc_sHeight(_acc_gHeight()+1); }
    inline float _acc_sHeight$preInc()			{ CHCKTHIS; return _acc_sHeightpreInc(); }
    inline float _acc_sHeightpreDec()			{ return _acc_sHeight(_acc_gHeight()-1); }
    inline float _acc_sHeight$preDec()			{ CHCKTHIS; return _acc_sHeightpreDec(); }
    inline float _acc_sHeightAddEq(float value)	{ return _acc_sHeight(_acc_gHeight() + value); }
    inline float _acc_sHeight$AddEq(float value)			{ CHCKTHIS; return _acc_sHeightAddEq(value); }
    inline float _acc_sHeightSubEq(float value)	{ return _acc_sHeight(_acc_gHeight() - value); }
    inline float _acc_sHeight$SubEq(float value)			{ CHCKTHIS; return _acc_sHeightSubEq(value); }
    inline float _acc_sHeightMulEq(float value)	{ return _acc_sHeight(_acc_gHeight() * value); }
    inline float _acc_sHeight$MulEq(float value)			{ CHCKTHIS; return _acc_sHeightMulEq(value); }
    inline float _acc_sHeightDivEq(float value)	{ return _acc_sHeight(_acc_gHeight() / value); }
    inline float _acc_sHeight$DivEq(float value)			{ CHCKTHIS; return _acc_sHeightDivEq(value); }
    inline float _acc_sHeightModEq(float value)	{  float orig = _acc_gHeight(); s32 tmp = (s32)(orig / value); return _acc_sHeight(orig - (tmp * value)); }
    inline float _acc_sHeight$ModEq(float value)			{ CHCKTHIS; return _acc_sHeightModEq(value); }
    static s32* _ext_CKLBUIClip_create(s32* pParent,u32 baseOrder,u32 maxOrder,float x,float y,float clipWidth,float clipHeight);
    static u32 _ext_CKLBUIClip_getOrder(s32* p);
    static void _ext_CKLBUIClip_setOrder(s32* p,u32 order);
    static u32 _ext_CKLBUIClip_getMaxOdr(s32* p);
    static void _ext_CKLBUIClip_setMaxOdr(s32* p,u32 maxodr);
    static float _ext_CKLBUIClip_getWidth(s32* p);
    static void _ext_CKLBUIClip_setWidth(s32* p,float width);
    static float _ext_CKLBUIClip_getHeight(s32* p);
    static void _ext_CKLBUIClip_setHeight(s32* p,float height);
    static void _ext_CKLBUIClip_setPosition(s32* p,float x,float y);
    static void _ext_CKLBUIClip_setSize(s32* p,float width,float height);
    CKLBUIClip(EnginePrototype::CKLBUITask* parent,u32 baseOrder,u32 maxOrder,float x,float y,float clipWidth,float clipHeight);
    CKLBUIClip();
    void getSize(EnginePrototype::FSize& size);
    inline void getSize$(EnginePrototype::FSize& size);
    void setSize(EnginePrototype::FSize size);
    inline void setSize$(EnginePrototype::FSize size);
    void setSize(float width,float height);
    inline void setSize$(float width,float height);
    void setPosition(float x,float y);
    inline void setPosition$(float x,float y);
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 169;
};
class EnginePrototype::CKLBUIControl : public EnginePrototype::CKLBUITask {
friend class OnClickCallBack_inner30;
friend class OnDblClickCallBack_inner31;
friend class OnDragCallBack_inner32;
friend class OnPinchCallBack_inner33;
friend class OnLongTapCallBack_inner34;

public:
    enum EMODE {
        TAP,
        DRAG,
        RELEASE,
        _ForceWORD_EMODE = 0x7FFFFFFF
    };

    enum EMASK {
        MASK_CLICK = 1,
        MASK_DRAG = 2,
        MASK_PINCH = 4,
        MASK_DBLCLICK = 8,
        MASK_LONGTAP = 16,
        _ForceWORD_EMASK = 0x7FFFFFFF
    };

    void _ctor_CKLBUIControl();
    static u32 s_classID;
    inline static u32 _ss_classIDDivEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID /= value; }
    inline static u32 _ss_classIDModEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID %= value; }

    EnginePrototype::_Delegate_Base_OnDragCallBack_inner32* m_onDragCallBack;
    inline EnginePrototype::_Delegate_Base_OnDragCallBack_inner32*& _gm_onDragCallBack$() { CHCKTHIS; return m_onDragCallBack; }
    inline EnginePrototype::_Delegate_Base_OnDragCallBack_inner32* _sm_onDragCallBack(EnginePrototype::_Delegate_Base_OnDragCallBack_inner32* _$value);
    inline EnginePrototype::_Delegate_Base_OnDragCallBack_inner32* _sm_onDragCallBack$(EnginePrototype::_Delegate_Base_OnDragCallBack_inner32* _$value);

    EnginePrototype::_Delegate_Base_OnPinchCallBack_inner33* m_onPinchCallBack;
    inline EnginePrototype::_Delegate_Base_OnPinchCallBack_inner33*& _gm_onPinchCallBack$() { CHCKTHIS; return m_onPinchCallBack; }
    inline EnginePrototype::_Delegate_Base_OnPinchCallBack_inner33* _sm_onPinchCallBack(EnginePrototype::_Delegate_Base_OnPinchCallBack_inner33* _$value);
    inline EnginePrototype::_Delegate_Base_OnPinchCallBack_inner33* _sm_onPinchCallBack$(EnginePrototype::_Delegate_Base_OnPinchCallBack_inner33* _$value);

    EnginePrototype::_Delegate_Base_OnClickCallBack_inner30* m_onClickCallBack;
    inline EnginePrototype::_Delegate_Base_OnClickCallBack_inner30*& _gm_onClickCallBack$() { CHCKTHIS; return m_onClickCallBack; }
    inline EnginePrototype::_Delegate_Base_OnClickCallBack_inner30* _sm_onClickCallBack(EnginePrototype::_Delegate_Base_OnClickCallBack_inner30* _$value);
    inline EnginePrototype::_Delegate_Base_OnClickCallBack_inner30* _sm_onClickCallBack$(EnginePrototype::_Delegate_Base_OnClickCallBack_inner30* _$value);

    EnginePrototype::_Delegate_Base_OnDblClickCallBack_inner31* m_onDblClickCallBack;
    inline EnginePrototype::_Delegate_Base_OnDblClickCallBack_inner31*& _gm_onDblClickCallBack$() { CHCKTHIS; return m_onDblClickCallBack; }
    inline EnginePrototype::_Delegate_Base_OnDblClickCallBack_inner31* _sm_onDblClickCallBack(EnginePrototype::_Delegate_Base_OnDblClickCallBack_inner31* _$value);
    inline EnginePrototype::_Delegate_Base_OnDblClickCallBack_inner31* _sm_onDblClickCallBack$(EnginePrototype::_Delegate_Base_OnDblClickCallBack_inner31* _$value);

    EnginePrototype::_Delegate_Base_OnLongTapCallBack_inner34* m_onLongTapCallBack;
    inline EnginePrototype::_Delegate_Base_OnLongTapCallBack_inner34*& _gm_onLongTapCallBack$() { CHCKTHIS; return m_onLongTapCallBack; }
    inline EnginePrototype::_Delegate_Base_OnLongTapCallBack_inner34* _sm_onLongTapCallBack(EnginePrototype::_Delegate_Base_OnLongTapCallBack_inner34* _$value);
    inline EnginePrototype::_Delegate_Base_OnLongTapCallBack_inner34* _sm_onLongTapCallBack$(EnginePrototype::_Delegate_Base_OnLongTapCallBack_inner34* _$value);

    static s32* _ext_CKLBUIControl_create(s32* pParent);
    static bool _ext_CKLBUIControl_setGroup(s32* p,s32* groupName);
    static void _ext_CKLBUIControl_setMask(s32* p,u16 mask);
    static void _ext_CKLBUIControl_lock(s32* p,bool lockMode);
    CKLBUIControl(EnginePrototype::CKLBTask* parent,EnginePrototype::_Delegate_Base_OnClickCallBack_inner30* onClickCallBack,EnginePrototype::_Delegate_Base_OnDragCallBack_inner32* onDragCallBack);
    CKLBUIControl();
    virtual void doSetupCallbacks();
    inline void doSetupCallbacks$();
    virtual void setDelegate(System::Delegate* anyDelegate,System::String* delegateName);
    inline void setDelegate$(System::Delegate* anyDelegate,System::String* delegateName);
    virtual void onClickCallBackFunction(s32 x,s32 y);
    inline void onClickCallBackFunction$(s32 x,s32 y);
    virtual void onDragCallBackFunction(u32 mode,s32 x,s32 y,s32 mvX,s32 mvY);
    inline void onDragCallBackFunction$(u32 mode,s32 x,s32 y,s32 mvX,s32 mvY);
    virtual void onPinchCallBackFunction(u32 mode,float pinch,float rotation);
    inline void onPinchCallBackFunction$(u32 mode,float pinch,float rotation);
    virtual void onDblClickCallBackFunction(s32 x,s32 y);
    inline void onDblClickCallBackFunction$(s32 x,s32 y);
    virtual void onLongTapCallBackFunction(u32 elapsedTime,s32 x,s32 y);
    inline void onLongTapCallBackFunction$(u32 elapsedTime,s32 x,s32 y);
    bool setGroup(System::String* groupName);
    inline bool setGroup$(System::String* groupName);
    void setMask(s32 mask);
    inline void setMask$(s32 mask);
    void setLock(bool lockBool);
    inline void setLock$(bool lockBool);
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 170;
};
class EnginePrototype::CKLBUIDebugItem : public EnginePrototype::CKLBUITask {
friend class CallBack_inner35;

public:
    void _ctor_CKLBUIDebugItem();
    static u32 s_classID;
    inline static u32 _ss_classIDDivEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID /= value; }
    inline static u32 _ss_classIDModEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID %= value; }

    EnginePrototype::_Delegate_Base_CallBack_inner35* m_callback;
    inline EnginePrototype::_Delegate_Base_CallBack_inner35*& _gm_callback$() { CHCKTHIS; return m_callback; }
    inline EnginePrototype::_Delegate_Base_CallBack_inner35* _sm_callback(EnginePrototype::_Delegate_Base_CallBack_inner35* _$value);
    inline EnginePrototype::_Delegate_Base_CallBack_inner35* _sm_callback$(EnginePrototype::_Delegate_Base_CallBack_inner35* _$value);

    inline u32 _acc_gOrder();
    inline u32 _acc_gOrder$();

    inline u32 _acc_sOrder(u32 value);
    inline u32 _acc_sOrder$(u32 value);
    inline u32 _acc_sOrderpostInc()			{ u32 tmp; _acc_sOrder((tmp = _acc_gOrder())+1); return tmp; }
    inline u32 _acc_sOrder$postInc()			{ CHCKTHIS; return _acc_sOrderpostInc(); }
    inline u32 _acc_sOrderpostDec()			{ u32 tmp; _acc_sOrder((tmp = _acc_gOrder())-1); return tmp; }
    inline u32 _acc_sOrder$postDec()			{ CHCKTHIS; return _acc_sOrderpostDec(); }
    inline u32 _acc_sOrderpreInc()			{ return _acc_sOrder(_acc_gOrder()+1); }
    inline u32 _acc_sOrder$preInc()			{ CHCKTHIS; return _acc_sOrderpreInc(); }
    inline u32 _acc_sOrderpreDec()			{ return _acc_sOrder(_acc_gOrder()-1); }
    inline u32 _acc_sOrder$preDec()			{ CHCKTHIS; return _acc_sOrderpreDec(); }
    inline u32 _acc_sOrderAddEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() + value); }
    inline u32 _acc_sOrder$AddEq(u32 value)			{ CHCKTHIS; return _acc_sOrderAddEq(value); }
    inline u32 _acc_sOrderSubEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() - value); }
    inline u32 _acc_sOrder$SubEq(u32 value)			{ CHCKTHIS; return _acc_sOrderSubEq(value); }
    inline u32 _acc_sOrderMulEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() * value); }
    inline u32 _acc_sOrder$MulEq(u32 value)			{ CHCKTHIS; return _acc_sOrderMulEq(value); }
    inline u32 _acc_sOrderDivEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sOrder(_acc_gOrder() / value); }
    inline u32 _acc_sOrder$DivEq(u32 value)			{ CHCKTHIS; return _acc_sOrderDivEq(value); }
    inline u32 _acc_sOrderModEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sOrder(_acc_gOrder() % value); }
    inline u32 _acc_sOrder$ModEq(u32 value)			{ CHCKTHIS; return _acc_sOrderModEq(value); }
    inline u32 _acc_sOrderXorEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() ^ value); }
    inline u32 _acc_sOrder$XorEq(u32 value)			{ CHCKTHIS; return _acc_sOrderXorEq(value); }
    inline u32 _acc_sOrderAndEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() & value); }
    inline u32 _acc_sOrder$AndEq(u32 value)			{ CHCKTHIS; return _acc_sOrderAndEq(value); }
    inline u32 _acc_sOrderOrEq(u32 value)		{ return _acc_sOrder(_acc_gOrder() | value); }
    inline u32 _acc_sOrder$OrEq(u32 value)			{ CHCKTHIS; return _acc_sOrderOrEq(value); }
    inline u32 _acc_sOrderRShiftEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() >> value); }
    inline u32 _acc_sOrder$RShiftEq(u32 value)			{ CHCKTHIS; return _acc_sOrderRShiftEq(value); }
    inline u32 _acc_sOrderLShiftEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() << value); }
    inline u32 _acc_sOrder$LShiftEq(u32 value)			{ CHCKTHIS; return _acc_sOrderLShiftEq(value); }
    inline System::String* _acc_gFont();
    inline System::String* _acc_gFont$();

    inline System::String* _acc_sFont(System::String* value);
    inline System::String* _acc_sFont$(System::String* value);
    inline u32 _acc_gSize();
    inline u32 _acc_gSize$();

    inline u32 _acc_sSize(u32 value);
    inline u32 _acc_sSize$(u32 value);
    inline u32 _acc_sSizepostInc()			{ u32 tmp; _acc_sSize((tmp = _acc_gSize())+1); return tmp; }
    inline u32 _acc_sSize$postInc()			{ CHCKTHIS; return _acc_sSizepostInc(); }
    inline u32 _acc_sSizepostDec()			{ u32 tmp; _acc_sSize((tmp = _acc_gSize())-1); return tmp; }
    inline u32 _acc_sSize$postDec()			{ CHCKTHIS; return _acc_sSizepostDec(); }
    inline u32 _acc_sSizepreInc()			{ return _acc_sSize(_acc_gSize()+1); }
    inline u32 _acc_sSize$preInc()			{ CHCKTHIS; return _acc_sSizepreInc(); }
    inline u32 _acc_sSizepreDec()			{ return _acc_sSize(_acc_gSize()-1); }
    inline u32 _acc_sSize$preDec()			{ CHCKTHIS; return _acc_sSizepreDec(); }
    inline u32 _acc_sSizeAddEq(u32 value)	{ return _acc_sSize(_acc_gSize() + value); }
    inline u32 _acc_sSize$AddEq(u32 value)			{ CHCKTHIS; return _acc_sSizeAddEq(value); }
    inline u32 _acc_sSizeSubEq(u32 value)	{ return _acc_sSize(_acc_gSize() - value); }
    inline u32 _acc_sSize$SubEq(u32 value)			{ CHCKTHIS; return _acc_sSizeSubEq(value); }
    inline u32 _acc_sSizeMulEq(u32 value)	{ return _acc_sSize(_acc_gSize() * value); }
    inline u32 _acc_sSize$MulEq(u32 value)			{ CHCKTHIS; return _acc_sSizeMulEq(value); }
    inline u32 _acc_sSizeDivEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sSize(_acc_gSize() / value); }
    inline u32 _acc_sSize$DivEq(u32 value)			{ CHCKTHIS; return _acc_sSizeDivEq(value); }
    inline u32 _acc_sSizeModEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sSize(_acc_gSize() % value); }
    inline u32 _acc_sSize$ModEq(u32 value)			{ CHCKTHIS; return _acc_sSizeModEq(value); }
    inline u32 _acc_sSizeXorEq(u32 value)	{ return _acc_sSize(_acc_gSize() ^ value); }
    inline u32 _acc_sSize$XorEq(u32 value)			{ CHCKTHIS; return _acc_sSizeXorEq(value); }
    inline u32 _acc_sSizeAndEq(u32 value)	{ return _acc_sSize(_acc_gSize() & value); }
    inline u32 _acc_sSize$AndEq(u32 value)			{ CHCKTHIS; return _acc_sSizeAndEq(value); }
    inline u32 _acc_sSizeOrEq(u32 value)		{ return _acc_sSize(_acc_gSize() | value); }
    inline u32 _acc_sSize$OrEq(u32 value)			{ CHCKTHIS; return _acc_sSizeOrEq(value); }
    inline u32 _acc_sSizeRShiftEq(u32 value)	{ return _acc_sSize(_acc_gSize() >> value); }
    inline u32 _acc_sSize$RShiftEq(u32 value)			{ CHCKTHIS; return _acc_sSizeRShiftEq(value); }
    inline u32 _acc_sSizeLShiftEq(u32 value)	{ return _acc_sSize(_acc_gSize() << value); }
    inline u32 _acc_sSize$LShiftEq(u32 value)			{ CHCKTHIS; return _acc_sSizeLShiftEq(value); }
    inline u32 _acc_gTextArgb();
    inline u32 _acc_gTextArgb$();

    inline u32 _acc_sTextArgb(u32 value);
    inline u32 _acc_sTextArgb$(u32 value);
    inline u32 _acc_sTextArgbpostInc()			{ u32 tmp; _acc_sTextArgb((tmp = _acc_gTextArgb())+1); return tmp; }
    inline u32 _acc_sTextArgb$postInc()			{ CHCKTHIS; return _acc_sTextArgbpostInc(); }
    inline u32 _acc_sTextArgbpostDec()			{ u32 tmp; _acc_sTextArgb((tmp = _acc_gTextArgb())-1); return tmp; }
    inline u32 _acc_sTextArgb$postDec()			{ CHCKTHIS; return _acc_sTextArgbpostDec(); }
    inline u32 _acc_sTextArgbpreInc()			{ return _acc_sTextArgb(_acc_gTextArgb()+1); }
    inline u32 _acc_sTextArgb$preInc()			{ CHCKTHIS; return _acc_sTextArgbpreInc(); }
    inline u32 _acc_sTextArgbpreDec()			{ return _acc_sTextArgb(_acc_gTextArgb()-1); }
    inline u32 _acc_sTextArgb$preDec()			{ CHCKTHIS; return _acc_sTextArgbpreDec(); }
    inline u32 _acc_sTextArgbAddEq(u32 value)	{ return _acc_sTextArgb(_acc_gTextArgb() + value); }
    inline u32 _acc_sTextArgb$AddEq(u32 value)			{ CHCKTHIS; return _acc_sTextArgbAddEq(value); }
    inline u32 _acc_sTextArgbSubEq(u32 value)	{ return _acc_sTextArgb(_acc_gTextArgb() - value); }
    inline u32 _acc_sTextArgb$SubEq(u32 value)			{ CHCKTHIS; return _acc_sTextArgbSubEq(value); }
    inline u32 _acc_sTextArgbMulEq(u32 value)	{ return _acc_sTextArgb(_acc_gTextArgb() * value); }
    inline u32 _acc_sTextArgb$MulEq(u32 value)			{ CHCKTHIS; return _acc_sTextArgbMulEq(value); }
    inline u32 _acc_sTextArgbDivEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sTextArgb(_acc_gTextArgb() / value); }
    inline u32 _acc_sTextArgb$DivEq(u32 value)			{ CHCKTHIS; return _acc_sTextArgbDivEq(value); }
    inline u32 _acc_sTextArgbModEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sTextArgb(_acc_gTextArgb() % value); }
    inline u32 _acc_sTextArgb$ModEq(u32 value)			{ CHCKTHIS; return _acc_sTextArgbModEq(value); }
    inline u32 _acc_sTextArgbXorEq(u32 value)	{ return _acc_sTextArgb(_acc_gTextArgb() ^ value); }
    inline u32 _acc_sTextArgb$XorEq(u32 value)			{ CHCKTHIS; return _acc_sTextArgbXorEq(value); }
    inline u32 _acc_sTextArgbAndEq(u32 value)	{ return _acc_sTextArgb(_acc_gTextArgb() & value); }
    inline u32 _acc_sTextArgb$AndEq(u32 value)			{ CHCKTHIS; return _acc_sTextArgbAndEq(value); }
    inline u32 _acc_sTextArgbOrEq(u32 value)		{ return _acc_sTextArgb(_acc_gTextArgb() | value); }
    inline u32 _acc_sTextArgb$OrEq(u32 value)			{ CHCKTHIS; return _acc_sTextArgbOrEq(value); }
    inline u32 _acc_sTextArgbRShiftEq(u32 value)	{ return _acc_sTextArgb(_acc_gTextArgb() >> value); }
    inline u32 _acc_sTextArgb$RShiftEq(u32 value)			{ CHCKTHIS; return _acc_sTextArgbRShiftEq(value); }
    inline u32 _acc_sTextArgbLShiftEq(u32 value)	{ return _acc_sTextArgb(_acc_gTextArgb() << value); }
    inline u32 _acc_sTextArgb$LShiftEq(u32 value)			{ CHCKTHIS; return _acc_sTextArgbLShiftEq(value); }
    inline System::String* _acc_gText();
    inline System::String* _acc_gText$();

    inline System::String* _acc_sText(System::String* value);
    inline System::String* _acc_sText$(System::String* value);
    static s32* _ext_CKLBUIDebugItem_create(s32* pParent,u32 order,float x,float y,u32 argb,s32* font,u32 size,s32* text,u32 id);
    static u32 _ext_CKLBUIDebugItem_getOrder(s32* p);
    static void _ext_CKLBUIDebugItem_setOrder(s32* p,u32 order);
    static u32 _ext_CKLBUIDebugItem_getColor(s32* p);
    static void _ext_CKLBUIDebugItem_setColor(s32* p,u32 order);
    static s32* _ext_CKLBUIDebugItem_getFont(s32* p);
    static void _ext_CKLBUIDebugItem_setFont(s32* p,s32* font);
    static u32 _ext_CKLBUIDebugItem_getSize(s32* p);
    static void _ext_CKLBUIDebugItem_setSize(s32* p,u32 order);
    static s32* _ext_CKLBUIDebugItem_getText(s32* p);
    static void _ext_CKLBUIDebugItem_setText(s32* p,s32* text);
    CKLBUIDebugItem(EnginePrototype::CKLBUITask* parent,u32 order,float x,float y,u32 argb,System::String* font_name,u32 font_size,System::String* text,u32 cmdID,EnginePrototype::_Delegate_Base_CallBack_inner35* callback);
    CKLBUIDebugItem();
    virtual void doSetupCallbacks();
    inline void doSetupCallbacks$();
    virtual void setDelegate(System::Delegate* anyDelegate,System::String* delegateName);
    inline void setDelegate$(System::Delegate* anyDelegate,System::String* delegateName);
    virtual void callBackFunction(u32 cmdID);
    inline void callBackFunction$(u32 cmdID);
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 183;
};
class EnginePrototype::CKLBUIDragIcon : public EnginePrototype::CKLBUITask {
friend struct Area_inner3;
friend class CallBack_inner36;

public:
    enum ESTEP {
        DRAG,
        RELEASE,
        _ForceWORD_ESTEP = 0x7FFFFFFF
    };

    enum EFLAGS {
        F_DICON_BASEINVISIBLE = 4,
        _ForceWORD_EFLAGS = 0x7FFFFFFF
    };

    void _ctor_CKLBUIDragIcon();
    static u32 s_classID;
    inline static u32 _ss_classIDDivEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID /= value; }
    inline static u32 _ss_classIDModEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID %= value; }

    EnginePrototype::_Delegate_Base_CallBack_inner36* m_callback;
    inline EnginePrototype::_Delegate_Base_CallBack_inner36*& _gm_callback$() { CHCKTHIS; return m_callback; }
    inline EnginePrototype::_Delegate_Base_CallBack_inner36* _sm_callback(EnginePrototype::_Delegate_Base_CallBack_inner36* _$value);
    inline EnginePrototype::_Delegate_Base_CallBack_inner36* _sm_callback$(EnginePrototype::_Delegate_Base_CallBack_inner36* _$value);

    inline u32 _acc_gOrder();
    inline u32 _acc_gOrder$();

    inline System::String* _acc_gAsset();
    inline System::String* _acc_gAsset$();

    inline System::String* _acc_gDragAsset();
    inline System::String* _acc_gDragAsset$();

    inline s32 _acc_gFlags();
    inline s32 _acc_gFlags$();

    inline s32 _acc_sFlags(s32 value);
    inline s32 _acc_sFlags$(s32 value);
    inline s32 _acc_sFlagspostInc()			{ s32 tmp = _acc_gFlags(); _acc_sFlags((s32)((s32)tmp + 1)); return tmp; }
    inline s32 _acc_sFlags$postInc()			{ CHCKTHIS; return _acc_sFlagspostInc(); }
    inline s32 _acc_sFlagspostDec()			{ s32 tmp = _acc_gFlags(); _acc_sFlags((s32)((s32)tmp - 1)); return tmp; }
    inline s32 _acc_sFlags$postDec()			{ CHCKTHIS; return _acc_sFlagspostDec(); }
    inline s32 _acc_sFlagspreInc()			{ return _acc_sFlags((s32)((s32)_acc_gFlags()+1)); }
    inline s32 _acc_sFlags$preInc()			{ CHCKTHIS; return _acc_sFlagspreInc(); }
    inline s32 _acc_sFlagspreDec()			{ return _acc_sFlags((s32)((s32)_acc_gFlags()-1)); }
    inline s32 _acc_sFlags$preDec()			{ CHCKTHIS; return _acc_sFlagspreDec(); }
    inline s32 _acc_sFlagsAddEq(s32 value)	{ return _acc_sFlags((s32)((s32)_acc_gFlags() + value)); }
    inline s32 _acc_sFlags$AddEq(s32 value)			{ CHCKTHIS; return _acc_sFlagsAddEq(value); }
    inline s32 _acc_sFlagsSubEq(s32 value)	{ return _acc_sFlags((s32)((s32)_acc_gFlags() - value)); }
    inline s32 _acc_sFlags$SubEq(s32 value)			{ CHCKTHIS; return _acc_sFlagsSubEq(value); }
    inline float _acc_gDragScaleX();
    inline float _acc_gDragScaleX$();

    inline float _acc_sDragScaleX(float value);
    inline float _acc_sDragScaleX$(float value);
    inline float _acc_sDragScaleXpostInc()			{ float tmp; _acc_sDragScaleX((tmp = _acc_gDragScaleX())+1); return tmp; }
    inline float _acc_sDragScaleX$postInc()			{ CHCKTHIS; return _acc_sDragScaleXpostInc(); }
    inline float _acc_sDragScaleXpostDec()			{ float tmp; _acc_sDragScaleX((tmp = _acc_gDragScaleX())-1); return tmp; }
    inline float _acc_sDragScaleX$postDec()			{ CHCKTHIS; return _acc_sDragScaleXpostDec(); }
    inline float _acc_sDragScaleXpreInc()			{ return _acc_sDragScaleX(_acc_gDragScaleX()+1); }
    inline float _acc_sDragScaleX$preInc()			{ CHCKTHIS; return _acc_sDragScaleXpreInc(); }
    inline float _acc_sDragScaleXpreDec()			{ return _acc_sDragScaleX(_acc_gDragScaleX()-1); }
    inline float _acc_sDragScaleX$preDec()			{ CHCKTHIS; return _acc_sDragScaleXpreDec(); }
    inline float _acc_sDragScaleXAddEq(float value)	{ return _acc_sDragScaleX(_acc_gDragScaleX() + value); }
    inline float _acc_sDragScaleX$AddEq(float value)			{ CHCKTHIS; return _acc_sDragScaleXAddEq(value); }
    inline float _acc_sDragScaleXSubEq(float value)	{ return _acc_sDragScaleX(_acc_gDragScaleX() - value); }
    inline float _acc_sDragScaleX$SubEq(float value)			{ CHCKTHIS; return _acc_sDragScaleXSubEq(value); }
    inline float _acc_sDragScaleXMulEq(float value)	{ return _acc_sDragScaleX(_acc_gDragScaleX() * value); }
    inline float _acc_sDragScaleX$MulEq(float value)			{ CHCKTHIS; return _acc_sDragScaleXMulEq(value); }
    inline float _acc_sDragScaleXDivEq(float value)	{ return _acc_sDragScaleX(_acc_gDragScaleX() / value); }
    inline float _acc_sDragScaleX$DivEq(float value)			{ CHCKTHIS; return _acc_sDragScaleXDivEq(value); }
    inline float _acc_sDragScaleXModEq(float value)	{  float orig = _acc_gDragScaleX(); s32 tmp = (s32)(orig / value); return _acc_sDragScaleX(orig - (tmp * value)); }
    inline float _acc_sDragScaleX$ModEq(float value)			{ CHCKTHIS; return _acc_sDragScaleXModEq(value); }
    inline float _acc_gDragScaleY();
    inline float _acc_gDragScaleY$();

    inline float _acc_sDragScaleY(float value);
    inline float _acc_sDragScaleY$(float value);
    inline float _acc_sDragScaleYpostInc()			{ float tmp; _acc_sDragScaleY((tmp = _acc_gDragScaleY())+1); return tmp; }
    inline float _acc_sDragScaleY$postInc()			{ CHCKTHIS; return _acc_sDragScaleYpostInc(); }
    inline float _acc_sDragScaleYpostDec()			{ float tmp; _acc_sDragScaleY((tmp = _acc_gDragScaleY())-1); return tmp; }
    inline float _acc_sDragScaleY$postDec()			{ CHCKTHIS; return _acc_sDragScaleYpostDec(); }
    inline float _acc_sDragScaleYpreInc()			{ return _acc_sDragScaleY(_acc_gDragScaleY()+1); }
    inline float _acc_sDragScaleY$preInc()			{ CHCKTHIS; return _acc_sDragScaleYpreInc(); }
    inline float _acc_sDragScaleYpreDec()			{ return _acc_sDragScaleY(_acc_gDragScaleY()-1); }
    inline float _acc_sDragScaleY$preDec()			{ CHCKTHIS; return _acc_sDragScaleYpreDec(); }
    inline float _acc_sDragScaleYAddEq(float value)	{ return _acc_sDragScaleY(_acc_gDragScaleY() + value); }
    inline float _acc_sDragScaleY$AddEq(float value)			{ CHCKTHIS; return _acc_sDragScaleYAddEq(value); }
    inline float _acc_sDragScaleYSubEq(float value)	{ return _acc_sDragScaleY(_acc_gDragScaleY() - value); }
    inline float _acc_sDragScaleY$SubEq(float value)			{ CHCKTHIS; return _acc_sDragScaleYSubEq(value); }
    inline float _acc_sDragScaleYMulEq(float value)	{ return _acc_sDragScaleY(_acc_gDragScaleY() * value); }
    inline float _acc_sDragScaleY$MulEq(float value)			{ CHCKTHIS; return _acc_sDragScaleYMulEq(value); }
    inline float _acc_sDragScaleYDivEq(float value)	{ return _acc_sDragScaleY(_acc_gDragScaleY() / value); }
    inline float _acc_sDragScaleY$DivEq(float value)			{ CHCKTHIS; return _acc_sDragScaleYDivEq(value); }
    inline float _acc_sDragScaleYModEq(float value)	{  float orig = _acc_gDragScaleY(); s32 tmp = (s32)(orig / value); return _acc_sDragScaleY(orig - (tmp * value)); }
    inline float _acc_sDragScaleY$ModEq(float value)			{ CHCKTHIS; return _acc_sDragScaleYModEq(value); }
    inline bool _acc_gEnable();
    inline bool _acc_gEnable$();

    inline bool _acc_sEnable(bool value);
    inline bool _acc_sEnable$(bool value);
    static s32* _ext_CKLBUIDragIcon_create(s32* pParent,u32 order,float x,float y,EnginePrototype::Area_inner3& tap_area,s32* asset,s32* drag_asset,s32 drag_order_offset,float drag_alpha,float center_x,float center_y,u32 flags);
    static u32 _ext_CKLBUIDragIcon_getOrder(s32* p);
    static s32* _ext_CKLBUIDragIcon_getAsset(s32* p);
    static s32* _ext_CKLBUIDragIcon_getDrag(s32* p);
    static u32 _ext_CKLBUIDragIcon_getFlags(s32* p);
    static void _ext_CKLBUIDragIcon_setFlags(s32* p,u32 flag);
    static bool _ext_CKLBUIDragIcon_getEnable(s32* p);
    static void _ext_CKLBUIDragIcon_setEnable(s32* p,bool enable);
    static float _ext_CKLBUIDragIcon_getDragScaleX(s32* p);
    static void _ext_CKLBUIDragIcon_setDragScaleX(s32* p,float x);
    static float _ext_CKLBUIDragIcon_getDragScaleY(s32* p);
    static void _ext_CKLBUIDragIcon_setDragScaleY(s32* p,float y);
    static void _ext_CKLBUIDragIcon_dragArea(s32* p,EnginePrototype::Area_inner3& area);
    CKLBUIDragIcon(EnginePrototype::CKLBUITask* parent,u32 order,float x,float y,EnginePrototype::Area_inner3& tap_area,System::String* asset,System::String* drag_asset,s32 drag_order_offset,float drag_alpha,float center_x,float center_y,EnginePrototype::_Delegate_Base_CallBack_inner36* callback,u32 flags);
    CKLBUIDragIcon();
    virtual void doSetupCallbacks();
    inline void doSetupCallbacks$();
    virtual void setDelegate(System::Delegate* anyDelegate,System::String* delegateName);
    inline void setDelegate$(System::Delegate* anyDelegate,System::String* delegateName);
    virtual void callBackFunction(u32 type,s32 x,s32 y);
    inline void callBackFunction$(u32 type,s32 x,s32 y);
    void dragArea(EnginePrototype::Area_inner3 area);
    inline void dragArea$(EnginePrototype::Area_inner3 area);
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 186;
};
class EnginePrototype::CKLBUIForm : public EnginePrototype::CKLBUITask {
friend class SelectableCallBack_inner37;
friend class AnimCallBack_inner38;

public:
    void _ctor_CKLBUIForm();
    static u32 s_classID;
    inline static u32 _ss_classIDDivEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID /= value; }
    inline static u32 _ss_classIDModEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID %= value; }

    EnginePrototype::_Delegate_Base_SelectableCallBack_inner37* m_selectableCallback;
    inline EnginePrototype::_Delegate_Base_SelectableCallBack_inner37*& _gm_selectableCallback$() { CHCKTHIS; return m_selectableCallback; }
    inline EnginePrototype::_Delegate_Base_SelectableCallBack_inner37* _sm_selectableCallback(EnginePrototype::_Delegate_Base_SelectableCallBack_inner37* _$value);
    inline EnginePrototype::_Delegate_Base_SelectableCallBack_inner37* _sm_selectableCallback$(EnginePrototype::_Delegate_Base_SelectableCallBack_inner37* _$value);

    EnginePrototype::_Delegate_Base_AnimCallBack_inner38* m_animCallback;
    inline EnginePrototype::_Delegate_Base_AnimCallBack_inner38*& _gm_animCallback$() { CHCKTHIS; return m_animCallback; }
    inline EnginePrototype::_Delegate_Base_AnimCallBack_inner38* _sm_animCallback(EnginePrototype::_Delegate_Base_AnimCallBack_inner38* _$value);
    inline EnginePrototype::_Delegate_Base_AnimCallBack_inner38* _sm_animCallback$(EnginePrototype::_Delegate_Base_AnimCallBack_inner38* _$value);

    inline u32 _acc_gOrder();
    inline u32 _acc_gOrder$();

    inline System::String* _acc_gAsset();
    inline System::String* _acc_gAsset$();

    inline bool _acc_gIsFile();
    inline bool _acc_gIsFile$();

    inline bool _acc_gExclusive();
    inline bool _acc_gExclusive$();

    inline bool _acc_sExclusive(bool value);
    inline bool _acc_sExclusive$(bool value);
    static s32* _ext_CKLBUIForm_create(s32* pParent,u32 order,float x,float y,bool bAssetFile,s32* asset,bool bExclusive,bool modal,bool urgent);
    static s32* _ext_CKLBUIForm_getAsset(s32* p);
    static u32 _ext_CKLBUIForm_getOrder(s32* p);
    static bool _ext_CKLBUIForm_getExclusive(s32* p);
    static void _ext_CKLBUIForm_setExclusive(s32* p,bool exclusive);
    static bool _ext_CKLBUIForm_getIsFile(s32* p);
    static void _ext_CKLBUIForm_setEnable(s32* p,bool isEnabled);
    static bool _ext_CKLBUIForm_existNode(s32* p,s32* name);
    static void _ext_CKLBUIForm_inputEnable(s32* p,bool bEnable);
    static bool _ext_CKLBUIForm_animation(s32* p,s32* animname,bool blend);
    static bool _ext_CKLBUIForm_animEnter(s32* p);
    static bool _ext_CKLBUIForm_animLeave(s32* p);
    static bool _ext_CKLBUIForm_isAnim(s32* p,s32* name);
    static bool _ext_CKLBUIForm_skipAnim(s32* p,s32* name);
    static bool _ext_CKLBUIForm_setGroup(s32* p,s32* groupName);
    static void _ext_CKLBUIForm_setGlobalVolume(s32* p,float volume);
    CKLBUIForm(EnginePrototype::CKLBUITask* parent,u32 order,s32 x,s32 y,bool assetFile,System::String* asset_name,bool bExclusive,bool modal,bool urgent);
    CKLBUIForm();
    virtual void doSetupCallbacks();
    inline void doSetupCallbacks$();
    virtual void setDelegate(System::Delegate* anyDelegate,System::String* delegateName);
    inline void setDelegate$(System::Delegate* anyDelegate,System::String* delegateName);
    virtual void animCallBackFunction(s32* name,u32 id);
    inline void animCallBackFunction$(s32* name,u32 id);
    virtual void selectableCallbackFunction(s32* name,s32 type,s32 param);
    inline void selectableCallbackFunction$(s32* name,s32 type,s32 param);
    void setEnabled(bool isEnabled);
    inline void setEnabled$(bool isEnabled);
    bool existNode(System::String* name);
    inline bool existNode$(System::String* name);
    void inputEnable(bool bEnable);
    inline void inputEnable$(bool bEnable);
    bool animation(System::String* animationName,bool blend);
    inline bool animation$(System::String* animationName,bool blend);
    bool isRunningAnimation(System::String* animationName);
    inline bool isRunningAnimation$(System::String* animationName);
    bool skipAnim(System::String* animationName);
    inline bool skipAnim$(System::String* animationName);
    bool animEnter();
    inline bool animEnter$();
    bool animLeave();
    inline bool animLeave$();
    bool setGroup(System::String* groupName);
    inline bool setGroup$(System::String* groupName);
    void setGlobalVolume(float volume);
    inline void setGlobalVolume$(float volume);
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 193;
};
class EnginePrototype::CKLBUIFreeVertItem : public EnginePrototype::CKLBUITask {

public:
    void _ctor_CKLBUIFreeVertItem();
    static u32 s_classID;
    inline static u32 _ss_classIDDivEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID /= value; }
    inline static u32 _ss_classIDModEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID %= value; }

    inline u32 _acc_gOrder();
    inline u32 _acc_gOrder$();

    inline u32 _acc_sOrder(u32 value);
    inline u32 _acc_sOrder$(u32 value);
    inline u32 _acc_sOrderpostInc()			{ u32 tmp; _acc_sOrder((tmp = _acc_gOrder())+1); return tmp; }
    inline u32 _acc_sOrder$postInc()			{ CHCKTHIS; return _acc_sOrderpostInc(); }
    inline u32 _acc_sOrderpostDec()			{ u32 tmp; _acc_sOrder((tmp = _acc_gOrder())-1); return tmp; }
    inline u32 _acc_sOrder$postDec()			{ CHCKTHIS; return _acc_sOrderpostDec(); }
    inline u32 _acc_sOrderpreInc()			{ return _acc_sOrder(_acc_gOrder()+1); }
    inline u32 _acc_sOrder$preInc()			{ CHCKTHIS; return _acc_sOrderpreInc(); }
    inline u32 _acc_sOrderpreDec()			{ return _acc_sOrder(_acc_gOrder()-1); }
    inline u32 _acc_sOrder$preDec()			{ CHCKTHIS; return _acc_sOrderpreDec(); }
    inline u32 _acc_sOrderAddEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() + value); }
    inline u32 _acc_sOrder$AddEq(u32 value)			{ CHCKTHIS; return _acc_sOrderAddEq(value); }
    inline u32 _acc_sOrderSubEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() - value); }
    inline u32 _acc_sOrder$SubEq(u32 value)			{ CHCKTHIS; return _acc_sOrderSubEq(value); }
    inline u32 _acc_sOrderMulEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() * value); }
    inline u32 _acc_sOrder$MulEq(u32 value)			{ CHCKTHIS; return _acc_sOrderMulEq(value); }
    inline u32 _acc_sOrderDivEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sOrder(_acc_gOrder() / value); }
    inline u32 _acc_sOrder$DivEq(u32 value)			{ CHCKTHIS; return _acc_sOrderDivEq(value); }
    inline u32 _acc_sOrderModEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sOrder(_acc_gOrder() % value); }
    inline u32 _acc_sOrder$ModEq(u32 value)			{ CHCKTHIS; return _acc_sOrderModEq(value); }
    inline u32 _acc_sOrderXorEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() ^ value); }
    inline u32 _acc_sOrder$XorEq(u32 value)			{ CHCKTHIS; return _acc_sOrderXorEq(value); }
    inline u32 _acc_sOrderAndEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() & value); }
    inline u32 _acc_sOrder$AndEq(u32 value)			{ CHCKTHIS; return _acc_sOrderAndEq(value); }
    inline u32 _acc_sOrderOrEq(u32 value)		{ return _acc_sOrder(_acc_gOrder() | value); }
    inline u32 _acc_sOrder$OrEq(u32 value)			{ CHCKTHIS; return _acc_sOrderOrEq(value); }
    inline u32 _acc_sOrderRShiftEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() >> value); }
    inline u32 _acc_sOrder$RShiftEq(u32 value)			{ CHCKTHIS; return _acc_sOrderRShiftEq(value); }
    inline u32 _acc_sOrderLShiftEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() << value); }
    inline u32 _acc_sOrder$LShiftEq(u32 value)			{ CHCKTHIS; return _acc_sOrderLShiftEq(value); }
    inline System::String* _acc_gAsset();
    inline System::String* _acc_gAsset$();

    static s32* _ext_CKLBUIFreeVertItem_create(s32* parent,u32 order,float x,float y,s32* asset,System::Array<float>* verticesArray);
    static u32 _ext_CKLBUIFreeVertItem_getOrder(s32* p);
    static void _ext_CKLBUIFreeVertItem_setOrder(s32* p,u32 order);
    static s32* _ext_CKLBUIFreeVertItem_getAsset(s32* p);
    static void _ext_CKLBUIFreeVertItem_setVertices(s32* p,System::Array<float>* coord);
    static void _ext_CKLBUIFreeVertItem_setColors(s32* p,System::Array<u32>* colors);
    static void _ext_CKLBUIFreeVertItem_setVertCol(s32* p,s32 idx,u32 argb);
    static void _ext_CKLBUIFreeVertItem_setUV(s32* p,System::Array<float>* uv);
    CKLBUIFreeVertItem(EnginePrototype::CKLBUITask* parent,u32 order,float x,float y,System::String* asset,System::Array<float>* verticesArray);
    CKLBUIFreeVertItem();
    void setVertices(System::Array<float>* coords);
    inline void setVertices$(System::Array<float>* coords);
    void setColors(System::Array<u32>* colors);
    inline void setColors$(System::Array<u32>* colors);
    void setVertCol(s32 idx,u32 argb);
    inline void setVertCol$(s32 idx,u32 argb);
    void setUv(System::Array<float>* uv);
    inline void setUv$(System::Array<float>* uv);
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 198;
};
class EnginePrototype::CKLBUIGroup : public EnginePrototype::CKLBUITask {
friend class AnimCallBack_inner39;

public:
    void _ctor_CKLBUIGroup();
    static u32 s_classID;
    inline static u32 _ss_classIDDivEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID /= value; }
    inline static u32 _ss_classIDModEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID %= value; }

    EnginePrototype::_Delegate_Base_AnimCallBack_inner39* m_animCallback;
    inline EnginePrototype::_Delegate_Base_AnimCallBack_inner39*& _gm_animCallback$() { CHCKTHIS; return m_animCallback; }
    inline EnginePrototype::_Delegate_Base_AnimCallBack_inner39* _sm_animCallback(EnginePrototype::_Delegate_Base_AnimCallBack_inner39* _$value);
    inline EnginePrototype::_Delegate_Base_AnimCallBack_inner39* _sm_animCallback$(EnginePrototype::_Delegate_Base_AnimCallBack_inner39* _$value);

    static s32* _ext_CKLBUIGroup_create(s32* parent,float x,float y);
    static bool _ext_CKLBUIGroup_setAnimCallback(s32* p,s32* callback);
    static bool _ext_CKLBUIGroup_setAnimation(s32* p,s32* anim_name,bool blend);
    static bool _ext_CKLBUIGroup_isAnim(s32* p,s32* anim_name);
    static bool _ext_CKLBUIGroup_skipAnim(s32* p,s32* anim_name);
    CKLBUIGroup(EnginePrototype::CKLBUITask* parent,float x,float y);
    CKLBUIGroup();
    virtual void doSetupCallbacks();
    inline void doSetupCallbacks$();
    virtual void setDelegate(System::Delegate* anyDelegate,System::String* delegateName);
    inline void setDelegate$(System::Delegate* anyDelegate,System::String* delegateName);
    virtual void animCallBackFunction(s32* name,u32 id);
    inline void animCallBackFunction$(s32* name,u32 id);
    bool setAnimation(System::String* animationName,bool blendFlag);
    inline bool setAnimation$(System::String* animationName,bool blendFlag);
    bool isRunningAnimation(System::String* animationName);
    inline bool isRunningAnimation$(System::String* animationName);
    bool skipAnim(System::String* animationName);
    inline bool skipAnim$(System::String* animationName);
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 199;
};
class EnginePrototype::CKLBUILabel : public EnginePrototype::CKLBUITask {

public:
    enum EALIGN {
        MID = 5,
        TOP_LEFT = 10,
        TOP = 9,
        TOP_RIGHT = 8,
        LEFT = 6,
        RIGHT = 4,
        BOTTOM_LEFT = 2,
        BOTTOM = 1,
        BOTTOM_RIGHT = 0,
        _ForceWORD_EALIGN = 0x7FFFFFFF
    };

    void _ctor_CKLBUILabel();
    static u32 s_classID;
    inline static u32 _ss_classIDDivEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID /= value; }
    inline static u32 _ss_classIDModEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID %= value; }

    inline u32 _acc_gOrder();
    inline u32 _acc_gOrder$();

    inline u32 _acc_sOrder(u32 value);
    inline u32 _acc_sOrder$(u32 value);
    inline u32 _acc_sOrderpostInc()			{ u32 tmp; _acc_sOrder((tmp = _acc_gOrder())+1); return tmp; }
    inline u32 _acc_sOrder$postInc()			{ CHCKTHIS; return _acc_sOrderpostInc(); }
    inline u32 _acc_sOrderpostDec()			{ u32 tmp; _acc_sOrder((tmp = _acc_gOrder())-1); return tmp; }
    inline u32 _acc_sOrder$postDec()			{ CHCKTHIS; return _acc_sOrderpostDec(); }
    inline u32 _acc_sOrderpreInc()			{ return _acc_sOrder(_acc_gOrder()+1); }
    inline u32 _acc_sOrder$preInc()			{ CHCKTHIS; return _acc_sOrderpreInc(); }
    inline u32 _acc_sOrderpreDec()			{ return _acc_sOrder(_acc_gOrder()-1); }
    inline u32 _acc_sOrder$preDec()			{ CHCKTHIS; return _acc_sOrderpreDec(); }
    inline u32 _acc_sOrderAddEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() + value); }
    inline u32 _acc_sOrder$AddEq(u32 value)			{ CHCKTHIS; return _acc_sOrderAddEq(value); }
    inline u32 _acc_sOrderSubEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() - value); }
    inline u32 _acc_sOrder$SubEq(u32 value)			{ CHCKTHIS; return _acc_sOrderSubEq(value); }
    inline u32 _acc_sOrderMulEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() * value); }
    inline u32 _acc_sOrder$MulEq(u32 value)			{ CHCKTHIS; return _acc_sOrderMulEq(value); }
    inline u32 _acc_sOrderDivEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sOrder(_acc_gOrder() / value); }
    inline u32 _acc_sOrder$DivEq(u32 value)			{ CHCKTHIS; return _acc_sOrderDivEq(value); }
    inline u32 _acc_sOrderModEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sOrder(_acc_gOrder() % value); }
    inline u32 _acc_sOrder$ModEq(u32 value)			{ CHCKTHIS; return _acc_sOrderModEq(value); }
    inline u32 _acc_sOrderXorEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() ^ value); }
    inline u32 _acc_sOrder$XorEq(u32 value)			{ CHCKTHIS; return _acc_sOrderXorEq(value); }
    inline u32 _acc_sOrderAndEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() & value); }
    inline u32 _acc_sOrder$AndEq(u32 value)			{ CHCKTHIS; return _acc_sOrderAndEq(value); }
    inline u32 _acc_sOrderOrEq(u32 value)		{ return _acc_sOrder(_acc_gOrder() | value); }
    inline u32 _acc_sOrder$OrEq(u32 value)			{ CHCKTHIS; return _acc_sOrderOrEq(value); }
    inline u32 _acc_sOrderRShiftEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() >> value); }
    inline u32 _acc_sOrder$RShiftEq(u32 value)			{ CHCKTHIS; return _acc_sOrderRShiftEq(value); }
    inline u32 _acc_sOrderLShiftEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() << value); }
    inline u32 _acc_sOrder$LShiftEq(u32 value)			{ CHCKTHIS; return _acc_sOrderLShiftEq(value); }
    inline System::String* _acc_gFontName();
    inline System::String* _acc_gFontName$();

    inline System::String* _acc_sFontName(System::String* value);
    inline System::String* _acc_sFontName$(System::String* value);
    inline u32 _acc_gFontSize();
    inline u32 _acc_gFontSize$();

    inline u32 _acc_sFontSize(u32 value);
    inline u32 _acc_sFontSize$(u32 value);
    inline u32 _acc_sFontSizepostInc()			{ u32 tmp; _acc_sFontSize((tmp = _acc_gFontSize())+1); return tmp; }
    inline u32 _acc_sFontSize$postInc()			{ CHCKTHIS; return _acc_sFontSizepostInc(); }
    inline u32 _acc_sFontSizepostDec()			{ u32 tmp; _acc_sFontSize((tmp = _acc_gFontSize())-1); return tmp; }
    inline u32 _acc_sFontSize$postDec()			{ CHCKTHIS; return _acc_sFontSizepostDec(); }
    inline u32 _acc_sFontSizepreInc()			{ return _acc_sFontSize(_acc_gFontSize()+1); }
    inline u32 _acc_sFontSize$preInc()			{ CHCKTHIS; return _acc_sFontSizepreInc(); }
    inline u32 _acc_sFontSizepreDec()			{ return _acc_sFontSize(_acc_gFontSize()-1); }
    inline u32 _acc_sFontSize$preDec()			{ CHCKTHIS; return _acc_sFontSizepreDec(); }
    inline u32 _acc_sFontSizeAddEq(u32 value)	{ return _acc_sFontSize(_acc_gFontSize() + value); }
    inline u32 _acc_sFontSize$AddEq(u32 value)			{ CHCKTHIS; return _acc_sFontSizeAddEq(value); }
    inline u32 _acc_sFontSizeSubEq(u32 value)	{ return _acc_sFontSize(_acc_gFontSize() - value); }
    inline u32 _acc_sFontSize$SubEq(u32 value)			{ CHCKTHIS; return _acc_sFontSizeSubEq(value); }
    inline u32 _acc_sFontSizeMulEq(u32 value)	{ return _acc_sFontSize(_acc_gFontSize() * value); }
    inline u32 _acc_sFontSize$MulEq(u32 value)			{ CHCKTHIS; return _acc_sFontSizeMulEq(value); }
    inline u32 _acc_sFontSizeDivEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sFontSize(_acc_gFontSize() / value); }
    inline u32 _acc_sFontSize$DivEq(u32 value)			{ CHCKTHIS; return _acc_sFontSizeDivEq(value); }
    inline u32 _acc_sFontSizeModEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sFontSize(_acc_gFontSize() % value); }
    inline u32 _acc_sFontSize$ModEq(u32 value)			{ CHCKTHIS; return _acc_sFontSizeModEq(value); }
    inline u32 _acc_sFontSizeXorEq(u32 value)	{ return _acc_sFontSize(_acc_gFontSize() ^ value); }
    inline u32 _acc_sFontSize$XorEq(u32 value)			{ CHCKTHIS; return _acc_sFontSizeXorEq(value); }
    inline u32 _acc_sFontSizeAndEq(u32 value)	{ return _acc_sFontSize(_acc_gFontSize() & value); }
    inline u32 _acc_sFontSize$AndEq(u32 value)			{ CHCKTHIS; return _acc_sFontSizeAndEq(value); }
    inline u32 _acc_sFontSizeOrEq(u32 value)		{ return _acc_sFontSize(_acc_gFontSize() | value); }
    inline u32 _acc_sFontSize$OrEq(u32 value)			{ CHCKTHIS; return _acc_sFontSizeOrEq(value); }
    inline u32 _acc_sFontSizeRShiftEq(u32 value)	{ return _acc_sFontSize(_acc_gFontSize() >> value); }
    inline u32 _acc_sFontSize$RShiftEq(u32 value)			{ CHCKTHIS; return _acc_sFontSizeRShiftEq(value); }
    inline u32 _acc_sFontSizeLShiftEq(u32 value)	{ return _acc_sFontSize(_acc_gFontSize() << value); }
    inline u32 _acc_sFontSize$LShiftEq(u32 value)			{ CHCKTHIS; return _acc_sFontSizeLShiftEq(value); }
    inline u32 _acc_gTxtArgb();
    inline u32 _acc_gTxtArgb$();

    inline u32 _acc_sTxtArgb(u32 value);
    inline u32 _acc_sTxtArgb$(u32 value);
    inline u32 _acc_sTxtArgbpostInc()			{ u32 tmp; _acc_sTxtArgb((tmp = _acc_gTxtArgb())+1); return tmp; }
    inline u32 _acc_sTxtArgb$postInc()			{ CHCKTHIS; return _acc_sTxtArgbpostInc(); }
    inline u32 _acc_sTxtArgbpostDec()			{ u32 tmp; _acc_sTxtArgb((tmp = _acc_gTxtArgb())-1); return tmp; }
    inline u32 _acc_sTxtArgb$postDec()			{ CHCKTHIS; return _acc_sTxtArgbpostDec(); }
    inline u32 _acc_sTxtArgbpreInc()			{ return _acc_sTxtArgb(_acc_gTxtArgb()+1); }
    inline u32 _acc_sTxtArgb$preInc()			{ CHCKTHIS; return _acc_sTxtArgbpreInc(); }
    inline u32 _acc_sTxtArgbpreDec()			{ return _acc_sTxtArgb(_acc_gTxtArgb()-1); }
    inline u32 _acc_sTxtArgb$preDec()			{ CHCKTHIS; return _acc_sTxtArgbpreDec(); }
    inline u32 _acc_sTxtArgbAddEq(u32 value)	{ return _acc_sTxtArgb(_acc_gTxtArgb() + value); }
    inline u32 _acc_sTxtArgb$AddEq(u32 value)			{ CHCKTHIS; return _acc_sTxtArgbAddEq(value); }
    inline u32 _acc_sTxtArgbSubEq(u32 value)	{ return _acc_sTxtArgb(_acc_gTxtArgb() - value); }
    inline u32 _acc_sTxtArgb$SubEq(u32 value)			{ CHCKTHIS; return _acc_sTxtArgbSubEq(value); }
    inline u32 _acc_sTxtArgbMulEq(u32 value)	{ return _acc_sTxtArgb(_acc_gTxtArgb() * value); }
    inline u32 _acc_sTxtArgb$MulEq(u32 value)			{ CHCKTHIS; return _acc_sTxtArgbMulEq(value); }
    inline u32 _acc_sTxtArgbDivEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sTxtArgb(_acc_gTxtArgb() / value); }
    inline u32 _acc_sTxtArgb$DivEq(u32 value)			{ CHCKTHIS; return _acc_sTxtArgbDivEq(value); }
    inline u32 _acc_sTxtArgbModEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sTxtArgb(_acc_gTxtArgb() % value); }
    inline u32 _acc_sTxtArgb$ModEq(u32 value)			{ CHCKTHIS; return _acc_sTxtArgbModEq(value); }
    inline u32 _acc_sTxtArgbXorEq(u32 value)	{ return _acc_sTxtArgb(_acc_gTxtArgb() ^ value); }
    inline u32 _acc_sTxtArgb$XorEq(u32 value)			{ CHCKTHIS; return _acc_sTxtArgbXorEq(value); }
    inline u32 _acc_sTxtArgbAndEq(u32 value)	{ return _acc_sTxtArgb(_acc_gTxtArgb() & value); }
    inline u32 _acc_sTxtArgb$AndEq(u32 value)			{ CHCKTHIS; return _acc_sTxtArgbAndEq(value); }
    inline u32 _acc_sTxtArgbOrEq(u32 value)		{ return _acc_sTxtArgb(_acc_gTxtArgb() | value); }
    inline u32 _acc_sTxtArgb$OrEq(u32 value)			{ CHCKTHIS; return _acc_sTxtArgbOrEq(value); }
    inline u32 _acc_sTxtArgbRShiftEq(u32 value)	{ return _acc_sTxtArgb(_acc_gTxtArgb() >> value); }
    inline u32 _acc_sTxtArgb$RShiftEq(u32 value)			{ CHCKTHIS; return _acc_sTxtArgbRShiftEq(value); }
    inline u32 _acc_sTxtArgbLShiftEq(u32 value)	{ return _acc_sTxtArgb(_acc_gTxtArgb() << value); }
    inline u32 _acc_sTxtArgb$LShiftEq(u32 value)			{ CHCKTHIS; return _acc_sTxtArgbLShiftEq(value); }
    inline System::String* _acc_gText();
    inline System::String* _acc_gText$();

    inline System::String* _acc_sText(System::String* value);
    inline System::String* _acc_sText$(System::String* value);
    inline s32 _acc_gAlign();
    inline s32 _acc_gAlign$();

    inline s32 _acc_sAlign(s32 value);
    inline s32 _acc_sAlign$(s32 value);
    inline s32 _acc_sAlignpostInc()			{ s32 tmp = _acc_gAlign(); _acc_sAlign((s32)((s32)tmp + 1)); return tmp; }
    inline s32 _acc_sAlign$postInc()			{ CHCKTHIS; return _acc_sAlignpostInc(); }
    inline s32 _acc_sAlignpostDec()			{ s32 tmp = _acc_gAlign(); _acc_sAlign((s32)((s32)tmp - 1)); return tmp; }
    inline s32 _acc_sAlign$postDec()			{ CHCKTHIS; return _acc_sAlignpostDec(); }
    inline s32 _acc_sAlignpreInc()			{ return _acc_sAlign((s32)((s32)_acc_gAlign()+1)); }
    inline s32 _acc_sAlign$preInc()			{ CHCKTHIS; return _acc_sAlignpreInc(); }
    inline s32 _acc_sAlignpreDec()			{ return _acc_sAlign((s32)((s32)_acc_gAlign()-1)); }
    inline s32 _acc_sAlign$preDec()			{ CHCKTHIS; return _acc_sAlignpreDec(); }
    inline s32 _acc_sAlignAddEq(s32 value)	{ return _acc_sAlign((s32)((s32)_acc_gAlign() + value)); }
    inline s32 _acc_sAlign$AddEq(s32 value)			{ CHCKTHIS; return _acc_sAlignAddEq(value); }
    inline s32 _acc_sAlignSubEq(s32 value)	{ return _acc_sAlign((s32)((s32)_acc_gAlign() - value)); }
    inline s32 _acc_sAlign$SubEq(s32 value)			{ CHCKTHIS; return _acc_sAlignSubEq(value); }
    static s32* _ext_CKLBUILabel_create(s32* pParent,u32 order,float x,float y,u32 argb,s32* font,u32 size,s32* text,u32 align);
    static u32 _ext_CKLBUILabel_getOrder(s32* p);
    static void _ext_CKLBUILabel_setOrder(s32* p,u32 order);
    static u32 _ext_CKLBUILabel_getAlign(s32* p);
    static void _ext_CKLBUILabel_setAlign(s32* p,u32 align);
    static s32* _ext_CKLBUILabel_getText(s32* p);
    static void _ext_CKLBUILabel_setText(s32* p,s32* text);
    static u32 _ext_CKLBUILabel_getColor(s32* p);
    static void _ext_CKLBUILabel_setColor(s32* p,u32 color);
    static s32* _ext_CKLBUILabel_getFont(s32* p);
    static void _ext_CKLBUILabel_setFont(s32* p,s32* font);
    static u32 _ext_CKLBUILabel_getFontSize(s32* p);
    static void _ext_CKLBUILabel_setFontSize(s32* p,u32 size);
    static void _ext_CKLBUILabel_setPosition(s32* p,float x,float y);
    CKLBUILabel(EnginePrototype::CKLBUITask* parent,u32 order,float x,float y,u32 argb,System::String* font_name,u32 font_size,System::String* text,s32 align);
    CKLBUILabel();
    void setFont(System::String* name,u32 size);
    inline void setFont$(System::String* name,u32 size);
    void setPosition(float x,float y);
    inline void setPosition$(float x,float y);
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 202;
};
class EnginePrototype::CKLBUIList : public EnginePrototype::CKLBUITask {
friend class LimitCallBack_inner40;
friend class DragCallBack_inner41;
friend class DynamicCallBack_inner42;
friend class ScrollBarCallBack_inner43;
friend class AnimCallBack_inner44;

public:
    enum EPOSITION_MODE {
        LIST_VIEW_TOP,
        LIST_VIEW_CENTER,
        LIST_VIEW_END,
        LIST_VIEW_OFFSET,
        _ForceWORD_EPOSITION_MODE = 0x7FFFFFFF
    };

    enum ESCROLLBAR_VALUE {
        LIST_SCROVER_TOP,
        LIST_SCROVER_BOTTTOM,
        LIST_SCROVER_TAKEOFF,
        _ForceWORD_ESCROLLBAR_VALUE = 0x7FFFFFFF
    };

    enum EITEM_MODE {
        LIST_ITEM_NORMAL,
        LIST_ITEM_DYNAMIC,
        LIST_ITEM_FLYWEIGHT,
        _ForceWORD_EITEM_MODE = 0x7FFFFFFF
    };

    void _ctor_CKLBUIList();
    static u32 s_classID;
    inline static u32 _ss_classIDDivEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID /= value; }
    inline static u32 _ss_classIDModEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID %= value; }

    EnginePrototype::_Delegate_Base_LimitCallBack_inner40* m_limitCallback;
    inline EnginePrototype::_Delegate_Base_LimitCallBack_inner40*& _gm_limitCallback$() { CHCKTHIS; return m_limitCallback; }
    inline EnginePrototype::_Delegate_Base_LimitCallBack_inner40* _sm_limitCallback(EnginePrototype::_Delegate_Base_LimitCallBack_inner40* _$value);
    inline EnginePrototype::_Delegate_Base_LimitCallBack_inner40* _sm_limitCallback$(EnginePrototype::_Delegate_Base_LimitCallBack_inner40* _$value);

    EnginePrototype::_Delegate_Base_DragCallBack_inner41* m_dragCallback;
    inline EnginePrototype::_Delegate_Base_DragCallBack_inner41*& _gm_dragCallback$() { CHCKTHIS; return m_dragCallback; }
    inline EnginePrototype::_Delegate_Base_DragCallBack_inner41* _sm_dragCallback(EnginePrototype::_Delegate_Base_DragCallBack_inner41* _$value);
    inline EnginePrototype::_Delegate_Base_DragCallBack_inner41* _sm_dragCallback$(EnginePrototype::_Delegate_Base_DragCallBack_inner41* _$value);

    EnginePrototype::_Delegate_Base_DynamicCallBack_inner42* m_dynamicCallback;
    inline EnginePrototype::_Delegate_Base_DynamicCallBack_inner42*& _gm_dynamicCallback$() { CHCKTHIS; return m_dynamicCallback; }
    inline EnginePrototype::_Delegate_Base_DynamicCallBack_inner42* _sm_dynamicCallback(EnginePrototype::_Delegate_Base_DynamicCallBack_inner42* _$value);
    inline EnginePrototype::_Delegate_Base_DynamicCallBack_inner42* _sm_dynamicCallback$(EnginePrototype::_Delegate_Base_DynamicCallBack_inner42* _$value);

    EnginePrototype::_Delegate_Base_ScrollBarCallBack_inner43* m_scrollbarCallback;
    inline EnginePrototype::_Delegate_Base_ScrollBarCallBack_inner43*& _gm_scrollbarCallback$() { CHCKTHIS; return m_scrollbarCallback; }
    inline EnginePrototype::_Delegate_Base_ScrollBarCallBack_inner43* _sm_scrollbarCallback(EnginePrototype::_Delegate_Base_ScrollBarCallBack_inner43* _$value);
    inline EnginePrototype::_Delegate_Base_ScrollBarCallBack_inner43* _sm_scrollbarCallback$(EnginePrototype::_Delegate_Base_ScrollBarCallBack_inner43* _$value);

    EnginePrototype::_Delegate_Base_AnimCallBack_inner44* m_animCallback;
    inline EnginePrototype::_Delegate_Base_AnimCallBack_inner44*& _gm_animCallback$() { CHCKTHIS; return m_animCallback; }
    inline EnginePrototype::_Delegate_Base_AnimCallBack_inner44* _sm_animCallback(EnginePrototype::_Delegate_Base_AnimCallBack_inner44* _$value);
    inline EnginePrototype::_Delegate_Base_AnimCallBack_inner44* _sm_animCallback$(EnginePrototype::_Delegate_Base_AnimCallBack_inner44* _$value);

    inline u32 _acc_gWidth();
    inline u32 _acc_gWidth$();

    inline u32 _acc_sWidth(u32 value);
    inline u32 _acc_sWidth$(u32 value);
    inline u32 _acc_sWidthpostInc()			{ u32 tmp; _acc_sWidth((tmp = _acc_gWidth())+1); return tmp; }
    inline u32 _acc_sWidth$postInc()			{ CHCKTHIS; return _acc_sWidthpostInc(); }
    inline u32 _acc_sWidthpostDec()			{ u32 tmp; _acc_sWidth((tmp = _acc_gWidth())-1); return tmp; }
    inline u32 _acc_sWidth$postDec()			{ CHCKTHIS; return _acc_sWidthpostDec(); }
    inline u32 _acc_sWidthpreInc()			{ return _acc_sWidth(_acc_gWidth()+1); }
    inline u32 _acc_sWidth$preInc()			{ CHCKTHIS; return _acc_sWidthpreInc(); }
    inline u32 _acc_sWidthpreDec()			{ return _acc_sWidth(_acc_gWidth()-1); }
    inline u32 _acc_sWidth$preDec()			{ CHCKTHIS; return _acc_sWidthpreDec(); }
    inline u32 _acc_sWidthAddEq(u32 value)	{ return _acc_sWidth(_acc_gWidth() + value); }
    inline u32 _acc_sWidth$AddEq(u32 value)			{ CHCKTHIS; return _acc_sWidthAddEq(value); }
    inline u32 _acc_sWidthSubEq(u32 value)	{ return _acc_sWidth(_acc_gWidth() - value); }
    inline u32 _acc_sWidth$SubEq(u32 value)			{ CHCKTHIS; return _acc_sWidthSubEq(value); }
    inline u32 _acc_sWidthMulEq(u32 value)	{ return _acc_sWidth(_acc_gWidth() * value); }
    inline u32 _acc_sWidth$MulEq(u32 value)			{ CHCKTHIS; return _acc_sWidthMulEq(value); }
    inline u32 _acc_sWidthDivEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sWidth(_acc_gWidth() / value); }
    inline u32 _acc_sWidth$DivEq(u32 value)			{ CHCKTHIS; return _acc_sWidthDivEq(value); }
    inline u32 _acc_sWidthModEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sWidth(_acc_gWidth() % value); }
    inline u32 _acc_sWidth$ModEq(u32 value)			{ CHCKTHIS; return _acc_sWidthModEq(value); }
    inline u32 _acc_sWidthXorEq(u32 value)	{ return _acc_sWidth(_acc_gWidth() ^ value); }
    inline u32 _acc_sWidth$XorEq(u32 value)			{ CHCKTHIS; return _acc_sWidthXorEq(value); }
    inline u32 _acc_sWidthAndEq(u32 value)	{ return _acc_sWidth(_acc_gWidth() & value); }
    inline u32 _acc_sWidth$AndEq(u32 value)			{ CHCKTHIS; return _acc_sWidthAndEq(value); }
    inline u32 _acc_sWidthOrEq(u32 value)		{ return _acc_sWidth(_acc_gWidth() | value); }
    inline u32 _acc_sWidth$OrEq(u32 value)			{ CHCKTHIS; return _acc_sWidthOrEq(value); }
    inline u32 _acc_sWidthRShiftEq(u32 value)	{ return _acc_sWidth(_acc_gWidth() >> value); }
    inline u32 _acc_sWidth$RShiftEq(u32 value)			{ CHCKTHIS; return _acc_sWidthRShiftEq(value); }
    inline u32 _acc_sWidthLShiftEq(u32 value)	{ return _acc_sWidth(_acc_gWidth() << value); }
    inline u32 _acc_sWidth$LShiftEq(u32 value)			{ CHCKTHIS; return _acc_sWidthLShiftEq(value); }
    inline u32 _acc_gHeight();
    inline u32 _acc_gHeight$();

    inline u32 _acc_sHeight(u32 value);
    inline u32 _acc_sHeight$(u32 value);
    inline u32 _acc_sHeightpostInc()			{ u32 tmp; _acc_sHeight((tmp = _acc_gHeight())+1); return tmp; }
    inline u32 _acc_sHeight$postInc()			{ CHCKTHIS; return _acc_sHeightpostInc(); }
    inline u32 _acc_sHeightpostDec()			{ u32 tmp; _acc_sHeight((tmp = _acc_gHeight())-1); return tmp; }
    inline u32 _acc_sHeight$postDec()			{ CHCKTHIS; return _acc_sHeightpostDec(); }
    inline u32 _acc_sHeightpreInc()			{ return _acc_sHeight(_acc_gHeight()+1); }
    inline u32 _acc_sHeight$preInc()			{ CHCKTHIS; return _acc_sHeightpreInc(); }
    inline u32 _acc_sHeightpreDec()			{ return _acc_sHeight(_acc_gHeight()-1); }
    inline u32 _acc_sHeight$preDec()			{ CHCKTHIS; return _acc_sHeightpreDec(); }
    inline u32 _acc_sHeightAddEq(u32 value)	{ return _acc_sHeight(_acc_gHeight() + value); }
    inline u32 _acc_sHeight$AddEq(u32 value)			{ CHCKTHIS; return _acc_sHeightAddEq(value); }
    inline u32 _acc_sHeightSubEq(u32 value)	{ return _acc_sHeight(_acc_gHeight() - value); }
    inline u32 _acc_sHeight$SubEq(u32 value)			{ CHCKTHIS; return _acc_sHeightSubEq(value); }
    inline u32 _acc_sHeightMulEq(u32 value)	{ return _acc_sHeight(_acc_gHeight() * value); }
    inline u32 _acc_sHeight$MulEq(u32 value)			{ CHCKTHIS; return _acc_sHeightMulEq(value); }
    inline u32 _acc_sHeightDivEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sHeight(_acc_gHeight() / value); }
    inline u32 _acc_sHeight$DivEq(u32 value)			{ CHCKTHIS; return _acc_sHeightDivEq(value); }
    inline u32 _acc_sHeightModEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sHeight(_acc_gHeight() % value); }
    inline u32 _acc_sHeight$ModEq(u32 value)			{ CHCKTHIS; return _acc_sHeightModEq(value); }
    inline u32 _acc_sHeightXorEq(u32 value)	{ return _acc_sHeight(_acc_gHeight() ^ value); }
    inline u32 _acc_sHeight$XorEq(u32 value)			{ CHCKTHIS; return _acc_sHeightXorEq(value); }
    inline u32 _acc_sHeightAndEq(u32 value)	{ return _acc_sHeight(_acc_gHeight() & value); }
    inline u32 _acc_sHeight$AndEq(u32 value)			{ CHCKTHIS; return _acc_sHeightAndEq(value); }
    inline u32 _acc_sHeightOrEq(u32 value)		{ return _acc_sHeight(_acc_gHeight() | value); }
    inline u32 _acc_sHeight$OrEq(u32 value)			{ CHCKTHIS; return _acc_sHeightOrEq(value); }
    inline u32 _acc_sHeightRShiftEq(u32 value)	{ return _acc_sHeight(_acc_gHeight() >> value); }
    inline u32 _acc_sHeight$RShiftEq(u32 value)			{ CHCKTHIS; return _acc_sHeightRShiftEq(value); }
    inline u32 _acc_sHeightLShiftEq(u32 value)	{ return _acc_sHeight(_acc_gHeight() << value); }
    inline u32 _acc_sHeight$LShiftEq(u32 value)			{ CHCKTHIS; return _acc_sHeightLShiftEq(value); }
    inline s32 _acc_gStepX();
    inline s32 _acc_gStepX$();

    inline s32 _acc_sStepX(s32 value);
    inline s32 _acc_sStepX$(s32 value);
    inline s32 _acc_sStepXpostInc()			{ s32 tmp; _acc_sStepX((tmp = _acc_gStepX())+1); return tmp; }
    inline s32 _acc_sStepX$postInc()			{ CHCKTHIS; return _acc_sStepXpostInc(); }
    inline s32 _acc_sStepXpostDec()			{ s32 tmp; _acc_sStepX((tmp = _acc_gStepX())-1); return tmp; }
    inline s32 _acc_sStepX$postDec()			{ CHCKTHIS; return _acc_sStepXpostDec(); }
    inline s32 _acc_sStepXpreInc()			{ return _acc_sStepX(_acc_gStepX()+1); }
    inline s32 _acc_sStepX$preInc()			{ CHCKTHIS; return _acc_sStepXpreInc(); }
    inline s32 _acc_sStepXpreDec()			{ return _acc_sStepX(_acc_gStepX()-1); }
    inline s32 _acc_sStepX$preDec()			{ CHCKTHIS; return _acc_sStepXpreDec(); }
    inline s32 _acc_sStepXAddEq(s32 value)	{ return _acc_sStepX(_acc_gStepX() + value); }
    inline s32 _acc_sStepX$AddEq(s32 value)			{ CHCKTHIS; return _acc_sStepXAddEq(value); }
    inline s32 _acc_sStepXSubEq(s32 value)	{ return _acc_sStepX(_acc_gStepX() - value); }
    inline s32 _acc_sStepX$SubEq(s32 value)			{ CHCKTHIS; return _acc_sStepXSubEq(value); }
    inline s32 _acc_sStepXMulEq(s32 value)	{ return _acc_sStepX(_acc_gStepX() * value); }
    inline s32 _acc_sStepX$MulEq(s32 value)			{ CHCKTHIS; return _acc_sStepXMulEq(value); }
    inline s32 _acc_sStepXDivEq(s32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sStepX(_acc_gStepX() / value); }
    inline s32 _acc_sStepX$DivEq(s32 value)			{ CHCKTHIS; return _acc_sStepXDivEq(value); }
    inline s32 _acc_sStepXModEq(s32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sStepX(_acc_gStepX() % value); }
    inline s32 _acc_sStepX$ModEq(s32 value)			{ CHCKTHIS; return _acc_sStepXModEq(value); }
    inline s32 _acc_sStepXXorEq(s32 value)	{ return _acc_sStepX(_acc_gStepX() ^ value); }
    inline s32 _acc_sStepX$XorEq(s32 value)			{ CHCKTHIS; return _acc_sStepXXorEq(value); }
    inline s32 _acc_sStepXAndEq(s32 value)	{ return _acc_sStepX(_acc_gStepX() & value); }
    inline s32 _acc_sStepX$AndEq(s32 value)			{ CHCKTHIS; return _acc_sStepXAndEq(value); }
    inline s32 _acc_sStepXOrEq(s32 value)		{ return _acc_sStepX(_acc_gStepX() | value); }
    inline s32 _acc_sStepX$OrEq(s32 value)			{ CHCKTHIS; return _acc_sStepXOrEq(value); }
    inline s32 _acc_sStepXRShiftEq(s32 value)	{ return _acc_sStepX(_acc_gStepX() >> value); }
    inline s32 _acc_sStepX$RShiftEq(s32 value)			{ CHCKTHIS; return _acc_sStepXRShiftEq(value); }
    inline s32 _acc_sStepXLShiftEq(s32 value)	{ return _acc_sStepX(_acc_gStepX() << value); }
    inline s32 _acc_sStepX$LShiftEq(s32 value)			{ CHCKTHIS; return _acc_sStepXLShiftEq(value); }
    inline s32 _acc_gStepY();
    inline s32 _acc_gStepY$();

    inline s32 _acc_sStepY(s32 value);
    inline s32 _acc_sStepY$(s32 value);
    inline s32 _acc_sStepYpostInc()			{ s32 tmp; _acc_sStepY((tmp = _acc_gStepY())+1); return tmp; }
    inline s32 _acc_sStepY$postInc()			{ CHCKTHIS; return _acc_sStepYpostInc(); }
    inline s32 _acc_sStepYpostDec()			{ s32 tmp; _acc_sStepY((tmp = _acc_gStepY())-1); return tmp; }
    inline s32 _acc_sStepY$postDec()			{ CHCKTHIS; return _acc_sStepYpostDec(); }
    inline s32 _acc_sStepYpreInc()			{ return _acc_sStepY(_acc_gStepY()+1); }
    inline s32 _acc_sStepY$preInc()			{ CHCKTHIS; return _acc_sStepYpreInc(); }
    inline s32 _acc_sStepYpreDec()			{ return _acc_sStepY(_acc_gStepY()-1); }
    inline s32 _acc_sStepY$preDec()			{ CHCKTHIS; return _acc_sStepYpreDec(); }
    inline s32 _acc_sStepYAddEq(s32 value)	{ return _acc_sStepY(_acc_gStepY() + value); }
    inline s32 _acc_sStepY$AddEq(s32 value)			{ CHCKTHIS; return _acc_sStepYAddEq(value); }
    inline s32 _acc_sStepYSubEq(s32 value)	{ return _acc_sStepY(_acc_gStepY() - value); }
    inline s32 _acc_sStepY$SubEq(s32 value)			{ CHCKTHIS; return _acc_sStepYSubEq(value); }
    inline s32 _acc_sStepYMulEq(s32 value)	{ return _acc_sStepY(_acc_gStepY() * value); }
    inline s32 _acc_sStepY$MulEq(s32 value)			{ CHCKTHIS; return _acc_sStepYMulEq(value); }
    inline s32 _acc_sStepYDivEq(s32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sStepY(_acc_gStepY() / value); }
    inline s32 _acc_sStepY$DivEq(s32 value)			{ CHCKTHIS; return _acc_sStepYDivEq(value); }
    inline s32 _acc_sStepYModEq(s32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sStepY(_acc_gStepY() % value); }
    inline s32 _acc_sStepY$ModEq(s32 value)			{ CHCKTHIS; return _acc_sStepYModEq(value); }
    inline s32 _acc_sStepYXorEq(s32 value)	{ return _acc_sStepY(_acc_gStepY() ^ value); }
    inline s32 _acc_sStepY$XorEq(s32 value)			{ CHCKTHIS; return _acc_sStepYXorEq(value); }
    inline s32 _acc_sStepYAndEq(s32 value)	{ return _acc_sStepY(_acc_gStepY() & value); }
    inline s32 _acc_sStepY$AndEq(s32 value)			{ CHCKTHIS; return _acc_sStepYAndEq(value); }
    inline s32 _acc_sStepYOrEq(s32 value)		{ return _acc_sStepY(_acc_gStepY() | value); }
    inline s32 _acc_sStepY$OrEq(s32 value)			{ CHCKTHIS; return _acc_sStepYOrEq(value); }
    inline s32 _acc_sStepYRShiftEq(s32 value)	{ return _acc_sStepY(_acc_gStepY() >> value); }
    inline s32 _acc_sStepY$RShiftEq(s32 value)			{ CHCKTHIS; return _acc_sStepYRShiftEq(value); }
    inline s32 _acc_sStepYLShiftEq(s32 value)	{ return _acc_sStepY(_acc_gStepY() << value); }
    inline s32 _acc_sStepY$LShiftEq(s32 value)			{ CHCKTHIS; return _acc_sStepYLShiftEq(value); }
    inline u32 _acc_gOrder();
    inline u32 _acc_gOrder$();

    inline u32 _acc_sOrder(u32 value);
    inline u32 _acc_sOrder$(u32 value);
    inline u32 _acc_sOrderpostInc()			{ u32 tmp; _acc_sOrder((tmp = _acc_gOrder())+1); return tmp; }
    inline u32 _acc_sOrder$postInc()			{ CHCKTHIS; return _acc_sOrderpostInc(); }
    inline u32 _acc_sOrderpostDec()			{ u32 tmp; _acc_sOrder((tmp = _acc_gOrder())-1); return tmp; }
    inline u32 _acc_sOrder$postDec()			{ CHCKTHIS; return _acc_sOrderpostDec(); }
    inline u32 _acc_sOrderpreInc()			{ return _acc_sOrder(_acc_gOrder()+1); }
    inline u32 _acc_sOrder$preInc()			{ CHCKTHIS; return _acc_sOrderpreInc(); }
    inline u32 _acc_sOrderpreDec()			{ return _acc_sOrder(_acc_gOrder()-1); }
    inline u32 _acc_sOrder$preDec()			{ CHCKTHIS; return _acc_sOrderpreDec(); }
    inline u32 _acc_sOrderAddEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() + value); }
    inline u32 _acc_sOrder$AddEq(u32 value)			{ CHCKTHIS; return _acc_sOrderAddEq(value); }
    inline u32 _acc_sOrderSubEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() - value); }
    inline u32 _acc_sOrder$SubEq(u32 value)			{ CHCKTHIS; return _acc_sOrderSubEq(value); }
    inline u32 _acc_sOrderMulEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() * value); }
    inline u32 _acc_sOrder$MulEq(u32 value)			{ CHCKTHIS; return _acc_sOrderMulEq(value); }
    inline u32 _acc_sOrderDivEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sOrder(_acc_gOrder() / value); }
    inline u32 _acc_sOrder$DivEq(u32 value)			{ CHCKTHIS; return _acc_sOrderDivEq(value); }
    inline u32 _acc_sOrderModEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sOrder(_acc_gOrder() % value); }
    inline u32 _acc_sOrder$ModEq(u32 value)			{ CHCKTHIS; return _acc_sOrderModEq(value); }
    inline u32 _acc_sOrderXorEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() ^ value); }
    inline u32 _acc_sOrder$XorEq(u32 value)			{ CHCKTHIS; return _acc_sOrderXorEq(value); }
    inline u32 _acc_sOrderAndEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() & value); }
    inline u32 _acc_sOrder$AndEq(u32 value)			{ CHCKTHIS; return _acc_sOrderAndEq(value); }
    inline u32 _acc_sOrderOrEq(u32 value)		{ return _acc_sOrder(_acc_gOrder() | value); }
    inline u32 _acc_sOrder$OrEq(u32 value)			{ CHCKTHIS; return _acc_sOrderOrEq(value); }
    inline u32 _acc_sOrderRShiftEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() >> value); }
    inline u32 _acc_sOrder$RShiftEq(u32 value)			{ CHCKTHIS; return _acc_sOrderRShiftEq(value); }
    inline u32 _acc_sOrderLShiftEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() << value); }
    inline u32 _acc_sOrder$LShiftEq(u32 value)			{ CHCKTHIS; return _acc_sOrderLShiftEq(value); }
    inline u32 _acc_gMaxodr();
    inline u32 _acc_gMaxodr$();

    inline u32 _acc_sMaxodr(u32 value);
    inline u32 _acc_sMaxodr$(u32 value);
    inline u32 _acc_sMaxodrpostInc()			{ u32 tmp; _acc_sMaxodr((tmp = _acc_gMaxodr())+1); return tmp; }
    inline u32 _acc_sMaxodr$postInc()			{ CHCKTHIS; return _acc_sMaxodrpostInc(); }
    inline u32 _acc_sMaxodrpostDec()			{ u32 tmp; _acc_sMaxodr((tmp = _acc_gMaxodr())-1); return tmp; }
    inline u32 _acc_sMaxodr$postDec()			{ CHCKTHIS; return _acc_sMaxodrpostDec(); }
    inline u32 _acc_sMaxodrpreInc()			{ return _acc_sMaxodr(_acc_gMaxodr()+1); }
    inline u32 _acc_sMaxodr$preInc()			{ CHCKTHIS; return _acc_sMaxodrpreInc(); }
    inline u32 _acc_sMaxodrpreDec()			{ return _acc_sMaxodr(_acc_gMaxodr()-1); }
    inline u32 _acc_sMaxodr$preDec()			{ CHCKTHIS; return _acc_sMaxodrpreDec(); }
    inline u32 _acc_sMaxodrAddEq(u32 value)	{ return _acc_sMaxodr(_acc_gMaxodr() + value); }
    inline u32 _acc_sMaxodr$AddEq(u32 value)			{ CHCKTHIS; return _acc_sMaxodrAddEq(value); }
    inline u32 _acc_sMaxodrSubEq(u32 value)	{ return _acc_sMaxodr(_acc_gMaxodr() - value); }
    inline u32 _acc_sMaxodr$SubEq(u32 value)			{ CHCKTHIS; return _acc_sMaxodrSubEq(value); }
    inline u32 _acc_sMaxodrMulEq(u32 value)	{ return _acc_sMaxodr(_acc_gMaxodr() * value); }
    inline u32 _acc_sMaxodr$MulEq(u32 value)			{ CHCKTHIS; return _acc_sMaxodrMulEq(value); }
    inline u32 _acc_sMaxodrDivEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sMaxodr(_acc_gMaxodr() / value); }
    inline u32 _acc_sMaxodr$DivEq(u32 value)			{ CHCKTHIS; return _acc_sMaxodrDivEq(value); }
    inline u32 _acc_sMaxodrModEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sMaxodr(_acc_gMaxodr() % value); }
    inline u32 _acc_sMaxodr$ModEq(u32 value)			{ CHCKTHIS; return _acc_sMaxodrModEq(value); }
    inline u32 _acc_sMaxodrXorEq(u32 value)	{ return _acc_sMaxodr(_acc_gMaxodr() ^ value); }
    inline u32 _acc_sMaxodr$XorEq(u32 value)			{ CHCKTHIS; return _acc_sMaxodrXorEq(value); }
    inline u32 _acc_sMaxodrAndEq(u32 value)	{ return _acc_sMaxodr(_acc_gMaxodr() & value); }
    inline u32 _acc_sMaxodr$AndEq(u32 value)			{ CHCKTHIS; return _acc_sMaxodrAndEq(value); }
    inline u32 _acc_sMaxodrOrEq(u32 value)		{ return _acc_sMaxodr(_acc_gMaxodr() | value); }
    inline u32 _acc_sMaxodr$OrEq(u32 value)			{ CHCKTHIS; return _acc_sMaxodrOrEq(value); }
    inline u32 _acc_sMaxodrRShiftEq(u32 value)	{ return _acc_sMaxodr(_acc_gMaxodr() >> value); }
    inline u32 _acc_sMaxodr$RShiftEq(u32 value)			{ CHCKTHIS; return _acc_sMaxodrRShiftEq(value); }
    inline u32 _acc_sMaxodrLShiftEq(u32 value)	{ return _acc_sMaxodr(_acc_gMaxodr() << value); }
    inline u32 _acc_sMaxodr$LShiftEq(u32 value)			{ CHCKTHIS; return _acc_sMaxodrLShiftEq(value); }
    inline bool _acc_gIsVertical();
    inline bool _acc_gIsVertical$();

    inline bool _acc_sIsVertical(bool value);
    inline bool _acc_sIsVertical$(bool value);
    inline u32 _acc_gItems();
    inline u32 _acc_gItems$();

    inline s32 _acc_gMarginTop();
    inline s32 _acc_gMarginTop$();

    inline s32 _acc_sMarginTop(s32 value);
    inline s32 _acc_sMarginTop$(s32 value);
    inline s32 _acc_sMarginToppostInc()			{ s32 tmp; _acc_sMarginTop((tmp = _acc_gMarginTop())+1); return tmp; }
    inline s32 _acc_sMarginTop$postInc()			{ CHCKTHIS; return _acc_sMarginToppostInc(); }
    inline s32 _acc_sMarginToppostDec()			{ s32 tmp; _acc_sMarginTop((tmp = _acc_gMarginTop())-1); return tmp; }
    inline s32 _acc_sMarginTop$postDec()			{ CHCKTHIS; return _acc_sMarginToppostDec(); }
    inline s32 _acc_sMarginToppreInc()			{ return _acc_sMarginTop(_acc_gMarginTop()+1); }
    inline s32 _acc_sMarginTop$preInc()			{ CHCKTHIS; return _acc_sMarginToppreInc(); }
    inline s32 _acc_sMarginToppreDec()			{ return _acc_sMarginTop(_acc_gMarginTop()-1); }
    inline s32 _acc_sMarginTop$preDec()			{ CHCKTHIS; return _acc_sMarginToppreDec(); }
    inline s32 _acc_sMarginTopAddEq(s32 value)	{ return _acc_sMarginTop(_acc_gMarginTop() + value); }
    inline s32 _acc_sMarginTop$AddEq(s32 value)			{ CHCKTHIS; return _acc_sMarginTopAddEq(value); }
    inline s32 _acc_sMarginTopSubEq(s32 value)	{ return _acc_sMarginTop(_acc_gMarginTop() - value); }
    inline s32 _acc_sMarginTop$SubEq(s32 value)			{ CHCKTHIS; return _acc_sMarginTopSubEq(value); }
    inline s32 _acc_sMarginTopMulEq(s32 value)	{ return _acc_sMarginTop(_acc_gMarginTop() * value); }
    inline s32 _acc_sMarginTop$MulEq(s32 value)			{ CHCKTHIS; return _acc_sMarginTopMulEq(value); }
    inline s32 _acc_sMarginTopDivEq(s32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sMarginTop(_acc_gMarginTop() / value); }
    inline s32 _acc_sMarginTop$DivEq(s32 value)			{ CHCKTHIS; return _acc_sMarginTopDivEq(value); }
    inline s32 _acc_sMarginTopModEq(s32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sMarginTop(_acc_gMarginTop() % value); }
    inline s32 _acc_sMarginTop$ModEq(s32 value)			{ CHCKTHIS; return _acc_sMarginTopModEq(value); }
    inline s32 _acc_sMarginTopXorEq(s32 value)	{ return _acc_sMarginTop(_acc_gMarginTop() ^ value); }
    inline s32 _acc_sMarginTop$XorEq(s32 value)			{ CHCKTHIS; return _acc_sMarginTopXorEq(value); }
    inline s32 _acc_sMarginTopAndEq(s32 value)	{ return _acc_sMarginTop(_acc_gMarginTop() & value); }
    inline s32 _acc_sMarginTop$AndEq(s32 value)			{ CHCKTHIS; return _acc_sMarginTopAndEq(value); }
    inline s32 _acc_sMarginTopOrEq(s32 value)		{ return _acc_sMarginTop(_acc_gMarginTop() | value); }
    inline s32 _acc_sMarginTop$OrEq(s32 value)			{ CHCKTHIS; return _acc_sMarginTopOrEq(value); }
    inline s32 _acc_sMarginTopRShiftEq(s32 value)	{ return _acc_sMarginTop(_acc_gMarginTop() >> value); }
    inline s32 _acc_sMarginTop$RShiftEq(s32 value)			{ CHCKTHIS; return _acc_sMarginTopRShiftEq(value); }
    inline s32 _acc_sMarginTopLShiftEq(s32 value)	{ return _acc_sMarginTop(_acc_gMarginTop() << value); }
    inline s32 _acc_sMarginTop$LShiftEq(s32 value)			{ CHCKTHIS; return _acc_sMarginTopLShiftEq(value); }
    inline s32 _acc_gMarginBottom();
    inline s32 _acc_gMarginBottom$();

    inline s32 _acc_sMarginBottom(s32 value);
    inline s32 _acc_sMarginBottom$(s32 value);
    inline s32 _acc_sMarginBottompostInc()			{ s32 tmp; _acc_sMarginBottom((tmp = _acc_gMarginBottom())+1); return tmp; }
    inline s32 _acc_sMarginBottom$postInc()			{ CHCKTHIS; return _acc_sMarginBottompostInc(); }
    inline s32 _acc_sMarginBottompostDec()			{ s32 tmp; _acc_sMarginBottom((tmp = _acc_gMarginBottom())-1); return tmp; }
    inline s32 _acc_sMarginBottom$postDec()			{ CHCKTHIS; return _acc_sMarginBottompostDec(); }
    inline s32 _acc_sMarginBottompreInc()			{ return _acc_sMarginBottom(_acc_gMarginBottom()+1); }
    inline s32 _acc_sMarginBottom$preInc()			{ CHCKTHIS; return _acc_sMarginBottompreInc(); }
    inline s32 _acc_sMarginBottompreDec()			{ return _acc_sMarginBottom(_acc_gMarginBottom()-1); }
    inline s32 _acc_sMarginBottom$preDec()			{ CHCKTHIS; return _acc_sMarginBottompreDec(); }
    inline s32 _acc_sMarginBottomAddEq(s32 value)	{ return _acc_sMarginBottom(_acc_gMarginBottom() + value); }
    inline s32 _acc_sMarginBottom$AddEq(s32 value)			{ CHCKTHIS; return _acc_sMarginBottomAddEq(value); }
    inline s32 _acc_sMarginBottomSubEq(s32 value)	{ return _acc_sMarginBottom(_acc_gMarginBottom() - value); }
    inline s32 _acc_sMarginBottom$SubEq(s32 value)			{ CHCKTHIS; return _acc_sMarginBottomSubEq(value); }
    inline s32 _acc_sMarginBottomMulEq(s32 value)	{ return _acc_sMarginBottom(_acc_gMarginBottom() * value); }
    inline s32 _acc_sMarginBottom$MulEq(s32 value)			{ CHCKTHIS; return _acc_sMarginBottomMulEq(value); }
    inline s32 _acc_sMarginBottomDivEq(s32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sMarginBottom(_acc_gMarginBottom() / value); }
    inline s32 _acc_sMarginBottom$DivEq(s32 value)			{ CHCKTHIS; return _acc_sMarginBottomDivEq(value); }
    inline s32 _acc_sMarginBottomModEq(s32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sMarginBottom(_acc_gMarginBottom() % value); }
    inline s32 _acc_sMarginBottom$ModEq(s32 value)			{ CHCKTHIS; return _acc_sMarginBottomModEq(value); }
    inline s32 _acc_sMarginBottomXorEq(s32 value)	{ return _acc_sMarginBottom(_acc_gMarginBottom() ^ value); }
    inline s32 _acc_sMarginBottom$XorEq(s32 value)			{ CHCKTHIS; return _acc_sMarginBottomXorEq(value); }
    inline s32 _acc_sMarginBottomAndEq(s32 value)	{ return _acc_sMarginBottom(_acc_gMarginBottom() & value); }
    inline s32 _acc_sMarginBottom$AndEq(s32 value)			{ CHCKTHIS; return _acc_sMarginBottomAndEq(value); }
    inline s32 _acc_sMarginBottomOrEq(s32 value)		{ return _acc_sMarginBottom(_acc_gMarginBottom() | value); }
    inline s32 _acc_sMarginBottom$OrEq(s32 value)			{ CHCKTHIS; return _acc_sMarginBottomOrEq(value); }
    inline s32 _acc_sMarginBottomRShiftEq(s32 value)	{ return _acc_sMarginBottom(_acc_gMarginBottom() >> value); }
    inline s32 _acc_sMarginBottom$RShiftEq(s32 value)			{ CHCKTHIS; return _acc_sMarginBottomRShiftEq(value); }
    inline s32 _acc_sMarginBottomLShiftEq(s32 value)	{ return _acc_sMarginBottom(_acc_gMarginBottom() << value); }
    inline s32 _acc_sMarginBottom$LShiftEq(s32 value)			{ CHCKTHIS; return _acc_sMarginBottomLShiftEq(value); }
    inline bool _acc_gDefaultScroll();
    inline bool _acc_gDefaultScroll$();

    inline bool _acc_sDefaultScroll(bool value);
    inline bool _acc_sDefaultScroll$(bool value);
    inline s32 _acc_gPosition();
    inline s32 _acc_gPosition$();

    inline s32 _acc_gLimit();
    inline s32 _acc_gLimit$();

    inline bool _acc_gLoopMode();
    inline bool _acc_gLoopMode$();

    inline bool _acc_sLoopMode(bool value);
    inline bool _acc_sLoopMode$(bool value);
    static s32* _ext_CKLBUIList_create(s32* pParent,u32 baseOrder,u32 maxOrder,float x,float y,float clipWidth,float clipHeight,s32 defaultLineStep,bool vertical,u32 optionalFlags);
    static u32 _ext_CKLBUIList_getWidth(s32* p);
    static void _ext_CKLBUIList_setWidth(s32* p,u32 width);
    static u32 _ext_CKLBUIList_getHeight(s32* p);
    static void _ext_CKLBUIList_setHeight(s32* p,u32 height);
    static s32 _ext_CKLBUIList_getStepX(s32* p);
    static void _ext_CKLBUIList_setStepX(s32* p,s32 x);
    static s32 _ext_CKLBUIList_getStepY(s32* p);
    static void _ext_CKLBUIList_setStepY(s32* p,s32 y);
    static u32 _ext_CKLBUIList_getOrder(s32* p);
    static void _ext_CKLBUIList_setOrder(s32* p,u32 order);
    static u32 _ext_CKLBUIList_getMaxOrder(s32* p);
    static void _ext_CKLBUIList_setMaxOrder(s32* p,u32 order);
    static bool _ext_CKLBUIList_getVertical(s32* p);
    static void _ext_CKLBUIList_setVertical(s32* p,bool vertical);
    static u32 _ext_CKLBUIList_getItems(s32* p);
    static s32 _ext_CKLBUIList_getMarginTop(s32* p);
    static void _ext_CKLBUIList_setMarginTop(s32* p,s32 top);
    static s32 _ext_CKLBUIList_getMarginBottom(s32* p);
    static void _ext_CKLBUIList_setMarginBottom(s32* p,s32 bottom);
    static bool _ext_CKLBUIList_getDefaultScroll(s32* p);
    static void _ext_CKLBUIList_setDefaultScroll(s32* p,bool scroll);
    static bool _ext_CKLBUIList_cmdItemRemove(s32* p,s32 idx);
    static void _ext_CKLBUIList_cmdItemMove(s32* p,s32 src,s32 dst);
    static void _ext_CKLBUIList_cmdSetMargin(s32* p,s32 top,s32 bottom);
    static s32 _ext_CKLBUIList_cmdGetPosition(s32* p);
    static s32 _ext_CKLBUIList_cmdSetPosition(s32* p,s32 pos,s32 dir);
    static void _ext_CKLBUIList_cmdSetItemID(s32* p,s32 index,s32 id);
    static s32 _ext_CKLBUIList_cmdSearchID(s32* p,s32 id);
    static void _ext_CKLBUIList_cmdSetItemPos(s32* p,s32 mode,s32 idx,s32 offset);
    static void _ext_CKLBUIList_cmdSetLimitClip(s32* p,bool chklimit);
    static s32 _ext_CKLBUIList_cmdGetLimit(s32* p);
    static bool _ext_CKLBUIList_cmdSetLimitArea(s32* p,s32 limitArea);
    static void _ext_CKLBUIList_cmdChangeStep(s32* p,s32 index,s32 step);
    static void _ext_CKLBUIList_cmdInputEnable(s32* p,bool enable);
    static bool _ext_CKLBUIList_cmdExistNode(s32* p,s32 index,s32* name);
    static bool _ext_CKLBUIList_cmdAnimationItem(s32* p,s32 index,s32* name,bool blend);
    static bool _ext_CKLBUIList_cmdAnimationAll(s32* p,s32* name,bool blend);
    static bool _ext_CKLBUIList_cmdItemAnimSkip(s32* p,s32 idx,s32* name);
    static bool _ext_CKLBUIList_cmdAllAnimSkip(s32* p,s32* name);
    static void _ext_CKLBUIList_cmdSetGroup(s32* p,s32* group_name);
    static void _ext_CKLBUIList_setLoop(s32* p,bool mode);
    static s32 _ext_CKLBUIList_cmdSetInitial(s32* p,s32 pos);
    static bool _ext_CKLBUIList_useScrollBar(s32* p,u32 order,bool side,s32 lineWeight,s32* image,s32 minSlenderSize,u32 colorNormal,u32 colorSelect,bool active,bool hideMode,bool shortHide);
    static void _ext_CKLBUIList_cmdFWModeConfig(s32* p,s32 itemStep,s32 maxItems);
    static bool _ext_CKLBUIList_cmdSetItemMode(s32* p,s32 itemMode);
    static bool _ext_CKLBUIList_cmdAddRecords(s32* p,s32 insIdx,s32* tpForm,s32* dbRecords,s32 step);
    static bool _ext_CKLBUIList_cmdSelectScrMgr(s32* p,s32* name,System::Array<s32>* optParams,u32 nb);
    static void _ext_CKLBUIList_cmdSetClip(s32* p,u32 orderBegin,u32 orderEnd,s16 clipX,s16 clipY,s16 clipWidth,s16 clipHeight);
    static bool _ext_CKLBUIList_cmdItemAdd(s32* p,s32* name);
    static bool _ext_CKLBUIList_cmdItemAdd2(s32* p,s32* name,s32 step,s32 id);
    static bool _ext_CKLBUIList_cmdInsertItem(s32* p,s32* name,s32 idx);
    static bool _ext_CKLBUIList_cmdInsertItem2(s32* p,s32* name,s32 idx,s32 step,s32 id);
    static bool _ext_CKLBUIList_cmdRemoveSelection(s32* p,System::Array<s32>* indexes,u32 nb);
    static void _ext_CKLBUIList_setDragRect(s32* p,s32 left,s32 top,s32 right,s32 bottom);
    CKLBUIList(EnginePrototype::CKLBUITask* parent,u32 base_priority,u32 max_order,float x,float y,float clip_width,float clip_height,s32 default_line_step,EnginePrototype::_Delegate_Base_DragCallBack_inner41* callback,bool vertical,u32 option_flags);
    CKLBUIList();
    virtual void doSetupCallbacks();
    inline void doSetupCallbacks$();
    virtual void setDelegate(System::Delegate* anyDelegate,System::String* delegateName);
    inline void setDelegate$(System::Delegate* anyDelegate,System::String* delegateName);
    virtual void dragCallBackFunction(u32 type,s32 x,s32 y,s32 param1,s32 param2);
    inline void dragCallBackFunction$(u32 type,s32 x,s32 y,s32 param1,s32 param2);
    virtual void limitCallBackFunction(u32 type,u32 itemCount,s32 listLength,s32 pos);
    inline void limitCallBackFunction$(u32 type,u32 itemCount,s32 listLength,s32 pos);
    virtual void dynamicCallBackFunction(s32 index,s32 id);
    inline void dynamicCallBackFunction$(s32 index,s32 id);
    virtual void scrollbarCallBackFunction(u32 type,s32 pos);
    inline void scrollbarCallBackFunction$(u32 type,s32 pos);
    virtual void animCallBackFunction(s32* name,u32 id);
    inline void animCallBackFunction$(s32* name,u32 id);
    void getSize(EnginePrototype::USize& size);
    inline void getSize$(EnginePrototype::USize& size);
    void setSize(EnginePrototype::USize size);
    inline void setSize$(EnginePrototype::USize size);
    void setSize(u32 width,u32 height);
    inline void setSize$(u32 width,u32 height);
    void itemAdd(System::String* asset);
    inline void itemAdd$(System::String* asset);
    void itemAdd(System::String* asset,s32 step,s32 id);
    inline void itemAdd$(System::String* asset,s32 step,s32 id);
    void itemInsert(System::String* asset,s32 index);
    inline void itemInsert$(System::String* asset,s32 index);
    void itemInsert(System::String* asset,s32 index,s32 step,s32 id);
    inline void itemInsert$(System::String* asset,s32 index,s32 step,s32 id);
    bool itemRemove(s32 index);
    inline bool itemRemove$(s32 index);
    void itemMove(s32 src,s32 dst);
    inline void itemMove$(s32 src,s32 dst);
    void itemRemoveSelection(System::Array<s32>* indexes);
    inline void itemRemoveSelection$(System::Array<s32>* indexes);
    void setMargin(s32 margin_top,s32 margin_bottom);
    inline void setMargin$(s32 margin_top,s32 margin_bottom);
    void setItemPosition(s32 positionMode,s32 index,s32 offset);
    inline void setItemPosition$(s32 positionMode,s32 index,s32 offset);
    void changeStep(s32 index,s32 newStep);
    inline void changeStep$(s32 index,s32 newStep);
    void setLimitClip(bool limitClipEnable);
    inline void setLimitClip$(bool limitClipEnable);
    void setLimitClip(bool limitClipEnable,EnginePrototype::_Delegate_Base_LimitCallBack_inner40* limitCallback);
    inline void setLimitClip$(bool limitClipEnable,EnginePrototype::_Delegate_Base_LimitCallBack_inner40* limitCallback);
    bool setLimitArea(s32 size);
    inline bool setLimitArea$(s32 size);
    void setInputEnable(bool enableFlag);
    inline void setInputEnable$(bool enableFlag);
    bool existNode(s32 index,System::String* name);
    inline bool existNode$(s32 index,System::String* name);
    bool animationItem(s32 index,System::String* animationName,bool blendFlag);
    inline bool animationItem$(s32 index,System::String* animationName,bool blendFlag);
    bool animationAll(System::String* animationName,bool blendFlag);
    inline bool animationAll$(System::String* animationName,bool blendFlag);
    bool useScrollbar(u32 order,bool side,s32 lineWeight,System::String* image,s32 minSliderSize,u32 colorNormal,u32 colorSelect,bool active,bool hideMode,bool shortHide);
    inline bool useScrollbar$(u32 order,bool side,s32 lineWeight,System::String* image,s32 minSliderSize,u32 colorNormal,u32 colorSelect,bool active,bool hideMode,bool shortHide);
    bool useScrollbar(u32 order,bool side,s32 lineWeight,System::String* image,s32 minSliderSize,u32 colorNormal,u32 colorSelect,bool active,EnginePrototype::_Delegate_Base_ScrollBarCallBack_inner43* callback,bool hideMode,bool shortHide);
    inline bool useScrollbar$(u32 order,bool side,s32 lineWeight,System::String* image,s32 minSliderSize,u32 colorNormal,u32 colorSelect,bool active,EnginePrototype::_Delegate_Base_ScrollBarCallBack_inner43* callback,bool hideMode,bool shortHide);
    void setItemID(s32 index,s32 id);
    inline void setItemID$(s32 index,s32 id);
    s32 searchID(s32 index);
    inline s32 searchID$(s32 index);
    bool selectScrMgr(System::String* managerName,System::Array<s32>* optParams);
    inline bool selectScrMgr$(System::String* managerName,System::Array<s32>* optParams);
    bool itemAnimSkip(s32 idx,System::String* name);
    inline bool itemAnimSkip$(s32 idx,System::String* name);
    bool allAnimSkip(System::String* groupName);
    inline bool allAnimSkip$(System::String* groupName);
    bool addRecords(s32 insIdx,System::String* tpForm,System::String* dbRecords,s32 step);
    inline bool addRecords$(s32 insIdx,System::String* tpForm,System::String* dbRecords,s32 step);
    s32 setInitial(s32 pos);
    inline s32 setInitial$(s32 pos);
    void fwModeConfig(s32 itemStep,s32 maxItems);
    inline void fwModeConfig$(s32 itemStep,s32 maxItems);
    void fwItemAdd();
    inline void fwItemAdd$();
    void fwItemInsertTop();
    inline void fwItemInsertTop$();
    bool setItemMode(s32 mode);
    inline bool setItemMode$(s32 mode);
    bool setItemMode(s32 mode,EnginePrototype::_Delegate_Base_DynamicCallBack_inner42* dynamicCallback);
    inline bool setItemMode$(s32 mode,EnginePrototype::_Delegate_Base_DynamicCallBack_inner42* dynamicCallback);
    s32 setPosition(s32 pos,s32 dir);
    inline s32 setPosition$(s32 pos,s32 dir);
    void setGroup(System::String* groupName);
    inline void setGroup$(System::String* groupName);
    void setClip(u32 orderBegin,u32 orderEnd,s16 clipX,s16 clipY,s16 clipWidth,s16 clipHeight);
    inline void setClip$(u32 orderBegin,u32 orderEnd,s16 clipX,s16 clipY,s16 clipWidth,s16 clipHeight);
    void setDragRect(s32 left,s32 top,s32 right,s32 bottom);
    inline void setDragRect$(s32 left,s32 top,s32 right,s32 bottom);
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 204;
};
class EnginePrototype::CKLBUIMoviePlayer : public EnginePrototype::CKLBUITask {
friend class CallBack_inner45;

public:
    void _ctor_CKLBUIMoviePlayer();
    static u32 s_classID;
    inline static u32 _ss_classIDDivEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID /= value; }
    inline static u32 _ss_classIDModEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID %= value; }

    EnginePrototype::_Delegate_Base_CallBack_inner45* m_callback;
    inline EnginePrototype::_Delegate_Base_CallBack_inner45*& _gm_callback$() { CHCKTHIS; return m_callback; }
    inline EnginePrototype::_Delegate_Base_CallBack_inner45* _sm_callback(EnginePrototype::_Delegate_Base_CallBack_inner45* _$value);
    inline EnginePrototype::_Delegate_Base_CallBack_inner45* _sm_callback$(EnginePrototype::_Delegate_Base_CallBack_inner45* _$value);

    inline u32 _acc_gWidth();
    inline u32 _acc_gWidth$();

    inline u32 _acc_sWidth(u32 value);
    inline u32 _acc_sWidth$(u32 value);
    inline u32 _acc_sWidthpostInc()			{ u32 tmp; _acc_sWidth((tmp = _acc_gWidth())+1); return tmp; }
    inline u32 _acc_sWidth$postInc()			{ CHCKTHIS; return _acc_sWidthpostInc(); }
    inline u32 _acc_sWidthpostDec()			{ u32 tmp; _acc_sWidth((tmp = _acc_gWidth())-1); return tmp; }
    inline u32 _acc_sWidth$postDec()			{ CHCKTHIS; return _acc_sWidthpostDec(); }
    inline u32 _acc_sWidthpreInc()			{ return _acc_sWidth(_acc_gWidth()+1); }
    inline u32 _acc_sWidth$preInc()			{ CHCKTHIS; return _acc_sWidthpreInc(); }
    inline u32 _acc_sWidthpreDec()			{ return _acc_sWidth(_acc_gWidth()-1); }
    inline u32 _acc_sWidth$preDec()			{ CHCKTHIS; return _acc_sWidthpreDec(); }
    inline u32 _acc_sWidthAddEq(u32 value)	{ return _acc_sWidth(_acc_gWidth() + value); }
    inline u32 _acc_sWidth$AddEq(u32 value)			{ CHCKTHIS; return _acc_sWidthAddEq(value); }
    inline u32 _acc_sWidthSubEq(u32 value)	{ return _acc_sWidth(_acc_gWidth() - value); }
    inline u32 _acc_sWidth$SubEq(u32 value)			{ CHCKTHIS; return _acc_sWidthSubEq(value); }
    inline u32 _acc_sWidthMulEq(u32 value)	{ return _acc_sWidth(_acc_gWidth() * value); }
    inline u32 _acc_sWidth$MulEq(u32 value)			{ CHCKTHIS; return _acc_sWidthMulEq(value); }
    inline u32 _acc_sWidthDivEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sWidth(_acc_gWidth() / value); }
    inline u32 _acc_sWidth$DivEq(u32 value)			{ CHCKTHIS; return _acc_sWidthDivEq(value); }
    inline u32 _acc_sWidthModEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sWidth(_acc_gWidth() % value); }
    inline u32 _acc_sWidth$ModEq(u32 value)			{ CHCKTHIS; return _acc_sWidthModEq(value); }
    inline u32 _acc_sWidthXorEq(u32 value)	{ return _acc_sWidth(_acc_gWidth() ^ value); }
    inline u32 _acc_sWidth$XorEq(u32 value)			{ CHCKTHIS; return _acc_sWidthXorEq(value); }
    inline u32 _acc_sWidthAndEq(u32 value)	{ return _acc_sWidth(_acc_gWidth() & value); }
    inline u32 _acc_sWidth$AndEq(u32 value)			{ CHCKTHIS; return _acc_sWidthAndEq(value); }
    inline u32 _acc_sWidthOrEq(u32 value)		{ return _acc_sWidth(_acc_gWidth() | value); }
    inline u32 _acc_sWidth$OrEq(u32 value)			{ CHCKTHIS; return _acc_sWidthOrEq(value); }
    inline u32 _acc_sWidthRShiftEq(u32 value)	{ return _acc_sWidth(_acc_gWidth() >> value); }
    inline u32 _acc_sWidth$RShiftEq(u32 value)			{ CHCKTHIS; return _acc_sWidthRShiftEq(value); }
    inline u32 _acc_sWidthLShiftEq(u32 value)	{ return _acc_sWidth(_acc_gWidth() << value); }
    inline u32 _acc_sWidth$LShiftEq(u32 value)			{ CHCKTHIS; return _acc_sWidthLShiftEq(value); }
    inline u32 _acc_gHeight();
    inline u32 _acc_gHeight$();

    inline u32 _acc_sHeight(u32 value);
    inline u32 _acc_sHeight$(u32 value);
    inline u32 _acc_sHeightpostInc()			{ u32 tmp; _acc_sHeight((tmp = _acc_gHeight())+1); return tmp; }
    inline u32 _acc_sHeight$postInc()			{ CHCKTHIS; return _acc_sHeightpostInc(); }
    inline u32 _acc_sHeightpostDec()			{ u32 tmp; _acc_sHeight((tmp = _acc_gHeight())-1); return tmp; }
    inline u32 _acc_sHeight$postDec()			{ CHCKTHIS; return _acc_sHeightpostDec(); }
    inline u32 _acc_sHeightpreInc()			{ return _acc_sHeight(_acc_gHeight()+1); }
    inline u32 _acc_sHeight$preInc()			{ CHCKTHIS; return _acc_sHeightpreInc(); }
    inline u32 _acc_sHeightpreDec()			{ return _acc_sHeight(_acc_gHeight()-1); }
    inline u32 _acc_sHeight$preDec()			{ CHCKTHIS; return _acc_sHeightpreDec(); }
    inline u32 _acc_sHeightAddEq(u32 value)	{ return _acc_sHeight(_acc_gHeight() + value); }
    inline u32 _acc_sHeight$AddEq(u32 value)			{ CHCKTHIS; return _acc_sHeightAddEq(value); }
    inline u32 _acc_sHeightSubEq(u32 value)	{ return _acc_sHeight(_acc_gHeight() - value); }
    inline u32 _acc_sHeight$SubEq(u32 value)			{ CHCKTHIS; return _acc_sHeightSubEq(value); }
    inline u32 _acc_sHeightMulEq(u32 value)	{ return _acc_sHeight(_acc_gHeight() * value); }
    inline u32 _acc_sHeight$MulEq(u32 value)			{ CHCKTHIS; return _acc_sHeightMulEq(value); }
    inline u32 _acc_sHeightDivEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sHeight(_acc_gHeight() / value); }
    inline u32 _acc_sHeight$DivEq(u32 value)			{ CHCKTHIS; return _acc_sHeightDivEq(value); }
    inline u32 _acc_sHeightModEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sHeight(_acc_gHeight() % value); }
    inline u32 _acc_sHeight$ModEq(u32 value)			{ CHCKTHIS; return _acc_sHeightModEq(value); }
    inline u32 _acc_sHeightXorEq(u32 value)	{ return _acc_sHeight(_acc_gHeight() ^ value); }
    inline u32 _acc_sHeight$XorEq(u32 value)			{ CHCKTHIS; return _acc_sHeightXorEq(value); }
    inline u32 _acc_sHeightAndEq(u32 value)	{ return _acc_sHeight(_acc_gHeight() & value); }
    inline u32 _acc_sHeight$AndEq(u32 value)			{ CHCKTHIS; return _acc_sHeightAndEq(value); }
    inline u32 _acc_sHeightOrEq(u32 value)		{ return _acc_sHeight(_acc_gHeight() | value); }
    inline u32 _acc_sHeight$OrEq(u32 value)			{ CHCKTHIS; return _acc_sHeightOrEq(value); }
    inline u32 _acc_sHeightRShiftEq(u32 value)	{ return _acc_sHeight(_acc_gHeight() >> value); }
    inline u32 _acc_sHeight$RShiftEq(u32 value)			{ CHCKTHIS; return _acc_sHeightRShiftEq(value); }
    inline u32 _acc_sHeightLShiftEq(u32 value)	{ return _acc_sHeight(_acc_gHeight() << value); }
    inline u32 _acc_sHeight$LShiftEq(u32 value)			{ CHCKTHIS; return _acc_sHeightLShiftEq(value); }
    inline System::String* _acc_gPath();
    inline System::String* _acc_gPath$();

    inline System::String* _acc_sPath(System::String* value);
    inline System::String* _acc_sPath$(System::String* value);
    static s32* _ext_CKLBUIMoviePlayer_create(s32* pParent,bool mode,float x,float y,float width,float height,s32* url);
    static u32 _ext_CKLBUIMoviePlayer_getWidth(s32* p);
    static void _ext_CKLBUIMoviePlayer_setWidth(s32* p,u32 width);
    static u32 _ext_CKLBUIMoviePlayer_getHeight(s32* p);
    static void _ext_CKLBUIMoviePlayer_setHeight(s32* p,u32 height);
    static s32* _ext_CKLBUIMoviePlayer_getText(s32* p);
    static void _ext_CKLBUIMoviePlayer_setText(s32* p,s32* text);
    static void _ext_CKLBUIMoviePlayer_moviePlay(s32* p);
    static void _ext_CKLBUIMoviePlayer_movieStop(s32* p);
    static void _ext_CKLBUIMoviePlayer_moviePause(s32* p);
    static void _ext_CKLBUIMoviePlayer_movieResume(s32* p);
    CKLBUIMoviePlayer(EnginePrototype::CKLBUITask* parent,bool background_mode,float x,float y,float width,float height,EnginePrototype::_Delegate_Base_CallBack_inner45* callback,System::String* url);
    CKLBUIMoviePlayer();
    virtual void doSetupCallbacks();
    inline void doSetupCallbacks$();
    virtual void setDelegate(System::Delegate* anyDelegate,System::String* delegateName);
    inline void setDelegate$(System::Delegate* anyDelegate,System::String* delegateName);
    virtual void callBackFunction();
    inline void callBackFunction$();
    void getSize(EnginePrototype::USize& size);
    inline void getSize$(EnginePrototype::USize& size);
    void setSize(EnginePrototype::USize size);
    inline void setSize$(EnginePrototype::USize size);
    void setSize(u32 width,u32 height);
    inline void setSize$(u32 width,u32 height);
    void play();
    inline void play$();
    void pause();
    inline void pause$();
    void stop();
    inline void stop$();
    void resume();
    inline void resume$();
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 218;
};
class EnginePrototype::CKLBUIMultiImgItem : public EnginePrototype::CKLBUITask {

public:
    void _ctor_CKLBUIMultiImgItem();
    static u32 s_classID;
    inline static u32 _ss_classIDDivEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID /= value; }
    inline static u32 _ss_classIDModEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID %= value; }

    inline u32 _acc_gOrder();
    inline u32 _acc_gOrder$();

    inline u32 _acc_sOrder(u32 value);
    inline u32 _acc_sOrder$(u32 value);
    inline u32 _acc_sOrderpostInc()			{ u32 tmp; _acc_sOrder((tmp = _acc_gOrder())+1); return tmp; }
    inline u32 _acc_sOrder$postInc()			{ CHCKTHIS; return _acc_sOrderpostInc(); }
    inline u32 _acc_sOrderpostDec()			{ u32 tmp; _acc_sOrder((tmp = _acc_gOrder())-1); return tmp; }
    inline u32 _acc_sOrder$postDec()			{ CHCKTHIS; return _acc_sOrderpostDec(); }
    inline u32 _acc_sOrderpreInc()			{ return _acc_sOrder(_acc_gOrder()+1); }
    inline u32 _acc_sOrder$preInc()			{ CHCKTHIS; return _acc_sOrderpreInc(); }
    inline u32 _acc_sOrderpreDec()			{ return _acc_sOrder(_acc_gOrder()-1); }
    inline u32 _acc_sOrder$preDec()			{ CHCKTHIS; return _acc_sOrderpreDec(); }
    inline u32 _acc_sOrderAddEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() + value); }
    inline u32 _acc_sOrder$AddEq(u32 value)			{ CHCKTHIS; return _acc_sOrderAddEq(value); }
    inline u32 _acc_sOrderSubEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() - value); }
    inline u32 _acc_sOrder$SubEq(u32 value)			{ CHCKTHIS; return _acc_sOrderSubEq(value); }
    inline u32 _acc_sOrderMulEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() * value); }
    inline u32 _acc_sOrder$MulEq(u32 value)			{ CHCKTHIS; return _acc_sOrderMulEq(value); }
    inline u32 _acc_sOrderDivEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sOrder(_acc_gOrder() / value); }
    inline u32 _acc_sOrder$DivEq(u32 value)			{ CHCKTHIS; return _acc_sOrderDivEq(value); }
    inline u32 _acc_sOrderModEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sOrder(_acc_gOrder() % value); }
    inline u32 _acc_sOrder$ModEq(u32 value)			{ CHCKTHIS; return _acc_sOrderModEq(value); }
    inline u32 _acc_sOrderXorEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() ^ value); }
    inline u32 _acc_sOrder$XorEq(u32 value)			{ CHCKTHIS; return _acc_sOrderXorEq(value); }
    inline u32 _acc_sOrderAndEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() & value); }
    inline u32 _acc_sOrder$AndEq(u32 value)			{ CHCKTHIS; return _acc_sOrderAndEq(value); }
    inline u32 _acc_sOrderOrEq(u32 value)		{ return _acc_sOrder(_acc_gOrder() | value); }
    inline u32 _acc_sOrder$OrEq(u32 value)			{ CHCKTHIS; return _acc_sOrderOrEq(value); }
    inline u32 _acc_sOrderRShiftEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() >> value); }
    inline u32 _acc_sOrder$RShiftEq(u32 value)			{ CHCKTHIS; return _acc_sOrderRShiftEq(value); }
    inline u32 _acc_sOrderLShiftEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() << value); }
    inline u32 _acc_sOrder$LShiftEq(u32 value)			{ CHCKTHIS; return _acc_sOrderLShiftEq(value); }
    inline u32 _acc_gIndex();
    inline u32 _acc_gIndex$();

    inline u32 _acc_sIndex(u32 value);
    inline u32 _acc_sIndex$(u32 value);
    inline u32 _acc_sIndexpostInc()			{ u32 tmp; _acc_sIndex((tmp = _acc_gIndex())+1); return tmp; }
    inline u32 _acc_sIndex$postInc()			{ CHCKTHIS; return _acc_sIndexpostInc(); }
    inline u32 _acc_sIndexpostDec()			{ u32 tmp; _acc_sIndex((tmp = _acc_gIndex())-1); return tmp; }
    inline u32 _acc_sIndex$postDec()			{ CHCKTHIS; return _acc_sIndexpostDec(); }
    inline u32 _acc_sIndexpreInc()			{ return _acc_sIndex(_acc_gIndex()+1); }
    inline u32 _acc_sIndex$preInc()			{ CHCKTHIS; return _acc_sIndexpreInc(); }
    inline u32 _acc_sIndexpreDec()			{ return _acc_sIndex(_acc_gIndex()-1); }
    inline u32 _acc_sIndex$preDec()			{ CHCKTHIS; return _acc_sIndexpreDec(); }
    inline u32 _acc_sIndexAddEq(u32 value)	{ return _acc_sIndex(_acc_gIndex() + value); }
    inline u32 _acc_sIndex$AddEq(u32 value)			{ CHCKTHIS; return _acc_sIndexAddEq(value); }
    inline u32 _acc_sIndexSubEq(u32 value)	{ return _acc_sIndex(_acc_gIndex() - value); }
    inline u32 _acc_sIndex$SubEq(u32 value)			{ CHCKTHIS; return _acc_sIndexSubEq(value); }
    inline u32 _acc_sIndexMulEq(u32 value)	{ return _acc_sIndex(_acc_gIndex() * value); }
    inline u32 _acc_sIndex$MulEq(u32 value)			{ CHCKTHIS; return _acc_sIndexMulEq(value); }
    inline u32 _acc_sIndexDivEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sIndex(_acc_gIndex() / value); }
    inline u32 _acc_sIndex$DivEq(u32 value)			{ CHCKTHIS; return _acc_sIndexDivEq(value); }
    inline u32 _acc_sIndexModEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sIndex(_acc_gIndex() % value); }
    inline u32 _acc_sIndex$ModEq(u32 value)			{ CHCKTHIS; return _acc_sIndexModEq(value); }
    inline u32 _acc_sIndexXorEq(u32 value)	{ return _acc_sIndex(_acc_gIndex() ^ value); }
    inline u32 _acc_sIndex$XorEq(u32 value)			{ CHCKTHIS; return _acc_sIndexXorEq(value); }
    inline u32 _acc_sIndexAndEq(u32 value)	{ return _acc_sIndex(_acc_gIndex() & value); }
    inline u32 _acc_sIndex$AndEq(u32 value)			{ CHCKTHIS; return _acc_sIndexAndEq(value); }
    inline u32 _acc_sIndexOrEq(u32 value)		{ return _acc_sIndex(_acc_gIndex() | value); }
    inline u32 _acc_sIndex$OrEq(u32 value)			{ CHCKTHIS; return _acc_sIndexOrEq(value); }
    inline u32 _acc_sIndexRShiftEq(u32 value)	{ return _acc_sIndex(_acc_gIndex() >> value); }
    inline u32 _acc_sIndex$RShiftEq(u32 value)			{ CHCKTHIS; return _acc_sIndexRShiftEq(value); }
    inline u32 _acc_sIndexLShiftEq(u32 value)	{ return _acc_sIndex(_acc_gIndex() << value); }
    inline u32 _acc_sIndex$LShiftEq(u32 value)			{ CHCKTHIS; return _acc_sIndexLShiftEq(value); }
    inline u32 _acc_gIdMax();
    inline u32 _acc_gIdMax$();

    inline u32 _acc_sIdMax(u32 value);
    inline u32 _acc_sIdMax$(u32 value);
    inline u32 _acc_sIdMaxpostInc()			{ u32 tmp; _acc_sIdMax((tmp = _acc_gIdMax())+1); return tmp; }
    inline u32 _acc_sIdMax$postInc()			{ CHCKTHIS; return _acc_sIdMaxpostInc(); }
    inline u32 _acc_sIdMaxpostDec()			{ u32 tmp; _acc_sIdMax((tmp = _acc_gIdMax())-1); return tmp; }
    inline u32 _acc_sIdMax$postDec()			{ CHCKTHIS; return _acc_sIdMaxpostDec(); }
    inline u32 _acc_sIdMaxpreInc()			{ return _acc_sIdMax(_acc_gIdMax()+1); }
    inline u32 _acc_sIdMax$preInc()			{ CHCKTHIS; return _acc_sIdMaxpreInc(); }
    inline u32 _acc_sIdMaxpreDec()			{ return _acc_sIdMax(_acc_gIdMax()-1); }
    inline u32 _acc_sIdMax$preDec()			{ CHCKTHIS; return _acc_sIdMaxpreDec(); }
    inline u32 _acc_sIdMaxAddEq(u32 value)	{ return _acc_sIdMax(_acc_gIdMax() + value); }
    inline u32 _acc_sIdMax$AddEq(u32 value)			{ CHCKTHIS; return _acc_sIdMaxAddEq(value); }
    inline u32 _acc_sIdMaxSubEq(u32 value)	{ return _acc_sIdMax(_acc_gIdMax() - value); }
    inline u32 _acc_sIdMax$SubEq(u32 value)			{ CHCKTHIS; return _acc_sIdMaxSubEq(value); }
    inline u32 _acc_sIdMaxMulEq(u32 value)	{ return _acc_sIdMax(_acc_gIdMax() * value); }
    inline u32 _acc_sIdMax$MulEq(u32 value)			{ CHCKTHIS; return _acc_sIdMaxMulEq(value); }
    inline u32 _acc_sIdMaxDivEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sIdMax(_acc_gIdMax() / value); }
    inline u32 _acc_sIdMax$DivEq(u32 value)			{ CHCKTHIS; return _acc_sIdMaxDivEq(value); }
    inline u32 _acc_sIdMaxModEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sIdMax(_acc_gIdMax() % value); }
    inline u32 _acc_sIdMax$ModEq(u32 value)			{ CHCKTHIS; return _acc_sIdMaxModEq(value); }
    inline u32 _acc_sIdMaxXorEq(u32 value)	{ return _acc_sIdMax(_acc_gIdMax() ^ value); }
    inline u32 _acc_sIdMax$XorEq(u32 value)			{ CHCKTHIS; return _acc_sIdMaxXorEq(value); }
    inline u32 _acc_sIdMaxAndEq(u32 value)	{ return _acc_sIdMax(_acc_gIdMax() & value); }
    inline u32 _acc_sIdMax$AndEq(u32 value)			{ CHCKTHIS; return _acc_sIdMaxAndEq(value); }
    inline u32 _acc_sIdMaxOrEq(u32 value)		{ return _acc_sIdMax(_acc_gIdMax() | value); }
    inline u32 _acc_sIdMax$OrEq(u32 value)			{ CHCKTHIS; return _acc_sIdMaxOrEq(value); }
    inline u32 _acc_sIdMaxRShiftEq(u32 value)	{ return _acc_sIdMax(_acc_gIdMax() >> value); }
    inline u32 _acc_sIdMax$RShiftEq(u32 value)			{ CHCKTHIS; return _acc_sIdMaxRShiftEq(value); }
    inline u32 _acc_sIdMaxLShiftEq(u32 value)	{ return _acc_sIdMax(_acc_gIdMax() << value); }
    inline u32 _acc_sIdMax$LShiftEq(u32 value)			{ CHCKTHIS; return _acc_sIdMaxLShiftEq(value); }
    static s32* _ext_CKLBUIMultiImgItem_create(s32* pParent,u32 order,float x,float y,u32 idx,System::Array<s32*>* pArrayAsset,System::Array<u32>* pArrayIndexes,u32 assetCount);
    static u32 _ext_CKLBUIMultiImgItem_getIndexMax(s32* p);
    static void _ext_CKLBUIMultiImgItem_setIndexMax(s32* p,u32 index);
    static u32 _ext_CKLBUIMultiImgItem_getOrder(s32* p);
    static void _ext_CKLBUIMultiImgItem_setOrder(s32* p,u32 order);
    static u32 _ext_CKLBUIMultiImgItem_getIndex(s32* p);
    static void _ext_CKLBUIMultiImgItem_setIndex(s32* p,u32 index);
    static bool _ext_CKLBUIMultiImgItem_changeAssets(s32* p,System::Array<s32*>* pArrayAsset,System::Array<u32>* pArrayIndexes,u32 assetCount);
    CKLBUIMultiImgItem(EnginePrototype::CKLBUITask* parent,u32 order,float x,float y,System::Array<System::String*>* pArrayAsset,System::Array<u32>* pArrayIndexes,u32 index);
    CKLBUIMultiImgItem();
    bool changeAssets(System::Array<System::String*>* pArrayAsset,System::Array<u32>* pArrayIndexes);
    inline bool changeAssets$(System::Array<System::String*>* pArrayAsset,System::Array<u32>* pArrayIndexes);
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 221;
};
class EnginePrototype::CKLBUIPieChart : public EnginePrototype::CKLBUITask {

public:
    void _ctor_CKLBUIPieChart();
    static u32 s_classID;
    inline static u32 _ss_classIDDivEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID /= value; }
    inline static u32 _ss_classIDModEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID %= value; }

    inline u32 _acc_gOrder();
    inline u32 _acc_gOrder$();

    inline float _acc_gStart();
    inline float _acc_gStart$();

    inline float _acc_sStart(float value);
    inline float _acc_sStart$(float value);
    inline float _acc_sStartpostInc()			{ float tmp; _acc_sStart((tmp = _acc_gStart())+1); return tmp; }
    inline float _acc_sStart$postInc()			{ CHCKTHIS; return _acc_sStartpostInc(); }
    inline float _acc_sStartpostDec()			{ float tmp; _acc_sStart((tmp = _acc_gStart())-1); return tmp; }
    inline float _acc_sStart$postDec()			{ CHCKTHIS; return _acc_sStartpostDec(); }
    inline float _acc_sStartpreInc()			{ return _acc_sStart(_acc_gStart()+1); }
    inline float _acc_sStart$preInc()			{ CHCKTHIS; return _acc_sStartpreInc(); }
    inline float _acc_sStartpreDec()			{ return _acc_sStart(_acc_gStart()-1); }
    inline float _acc_sStart$preDec()			{ CHCKTHIS; return _acc_sStartpreDec(); }
    inline float _acc_sStartAddEq(float value)	{ return _acc_sStart(_acc_gStart() + value); }
    inline float _acc_sStart$AddEq(float value)			{ CHCKTHIS; return _acc_sStartAddEq(value); }
    inline float _acc_sStartSubEq(float value)	{ return _acc_sStart(_acc_gStart() - value); }
    inline float _acc_sStart$SubEq(float value)			{ CHCKTHIS; return _acc_sStartSubEq(value); }
    inline float _acc_sStartMulEq(float value)	{ return _acc_sStart(_acc_gStart() * value); }
    inline float _acc_sStart$MulEq(float value)			{ CHCKTHIS; return _acc_sStartMulEq(value); }
    inline float _acc_sStartDivEq(float value)	{ return _acc_sStart(_acc_gStart() / value); }
    inline float _acc_sStart$DivEq(float value)			{ CHCKTHIS; return _acc_sStartDivEq(value); }
    inline float _acc_sStartModEq(float value)	{  float orig = _acc_gStart(); s32 tmp = (s32)(orig / value); return _acc_sStart(orig - (tmp * value)); }
    inline float _acc_sStart$ModEq(float value)			{ CHCKTHIS; return _acc_sStartModEq(value); }
    inline float _acc_gEnd();
    inline float _acc_gEnd$();

    inline float _acc_sEnd(float value);
    inline float _acc_sEnd$(float value);
    inline float _acc_sEndpostInc()			{ float tmp; _acc_sEnd((tmp = _acc_gEnd())+1); return tmp; }
    inline float _acc_sEnd$postInc()			{ CHCKTHIS; return _acc_sEndpostInc(); }
    inline float _acc_sEndpostDec()			{ float tmp; _acc_sEnd((tmp = _acc_gEnd())-1); return tmp; }
    inline float _acc_sEnd$postDec()			{ CHCKTHIS; return _acc_sEndpostDec(); }
    inline float _acc_sEndpreInc()			{ return _acc_sEnd(_acc_gEnd()+1); }
    inline float _acc_sEnd$preInc()			{ CHCKTHIS; return _acc_sEndpreInc(); }
    inline float _acc_sEndpreDec()			{ return _acc_sEnd(_acc_gEnd()-1); }
    inline float _acc_sEnd$preDec()			{ CHCKTHIS; return _acc_sEndpreDec(); }
    inline float _acc_sEndAddEq(float value)	{ return _acc_sEnd(_acc_gEnd() + value); }
    inline float _acc_sEnd$AddEq(float value)			{ CHCKTHIS; return _acc_sEndAddEq(value); }
    inline float _acc_sEndSubEq(float value)	{ return _acc_sEnd(_acc_gEnd() - value); }
    inline float _acc_sEnd$SubEq(float value)			{ CHCKTHIS; return _acc_sEndSubEq(value); }
    inline float _acc_sEndMulEq(float value)	{ return _acc_sEnd(_acc_gEnd() * value); }
    inline float _acc_sEnd$MulEq(float value)			{ CHCKTHIS; return _acc_sEndMulEq(value); }
    inline float _acc_sEndDivEq(float value)	{ return _acc_sEnd(_acc_gEnd() / value); }
    inline float _acc_sEnd$DivEq(float value)			{ CHCKTHIS; return _acc_sEndDivEq(value); }
    inline float _acc_sEndModEq(float value)	{  float orig = _acc_gEnd(); s32 tmp = (s32)(orig / value); return _acc_sEnd(orig - (tmp * value)); }
    inline float _acc_sEnd$ModEq(float value)			{ CHCKTHIS; return _acc_sEndModEq(value); }
    inline float _acc_gValue();
    inline float _acc_gValue$();

    inline float _acc_sValue(float value);
    inline float _acc_sValue$(float value);
    inline float _acc_sValuepostInc()			{ float tmp; _acc_sValue((tmp = _acc_gValue())+1); return tmp; }
    inline float _acc_sValue$postInc()			{ CHCKTHIS; return _acc_sValuepostInc(); }
    inline float _acc_sValuepostDec()			{ float tmp; _acc_sValue((tmp = _acc_gValue())-1); return tmp; }
    inline float _acc_sValue$postDec()			{ CHCKTHIS; return _acc_sValuepostDec(); }
    inline float _acc_sValuepreInc()			{ return _acc_sValue(_acc_gValue()+1); }
    inline float _acc_sValue$preInc()			{ CHCKTHIS; return _acc_sValuepreInc(); }
    inline float _acc_sValuepreDec()			{ return _acc_sValue(_acc_gValue()-1); }
    inline float _acc_sValue$preDec()			{ CHCKTHIS; return _acc_sValuepreDec(); }
    inline float _acc_sValueAddEq(float value)	{ return _acc_sValue(_acc_gValue() + value); }
    inline float _acc_sValue$AddEq(float value)			{ CHCKTHIS; return _acc_sValueAddEq(value); }
    inline float _acc_sValueSubEq(float value)	{ return _acc_sValue(_acc_gValue() - value); }
    inline float _acc_sValue$SubEq(float value)			{ CHCKTHIS; return _acc_sValueSubEq(value); }
    inline float _acc_sValueMulEq(float value)	{ return _acc_sValue(_acc_gValue() * value); }
    inline float _acc_sValue$MulEq(float value)			{ CHCKTHIS; return _acc_sValueMulEq(value); }
    inline float _acc_sValueDivEq(float value)	{ return _acc_sValue(_acc_gValue() / value); }
    inline float _acc_sValue$DivEq(float value)			{ CHCKTHIS; return _acc_sValueDivEq(value); }
    inline float _acc_sValueModEq(float value)	{  float orig = _acc_gValue(); s32 tmp = (s32)(orig / value); return _acc_sValue(orig - (tmp * value)); }
    inline float _acc_sValue$ModEq(float value)			{ CHCKTHIS; return _acc_sValueModEq(value); }
    inline s32 _acc_gAnim();
    inline s32 _acc_gAnim$();

    static s32* _ext_CKLBUIPieChart_create(s32* pParent,u32 order,float x,float y,float width,float height,s32* asset,float start,float end,s32 anim,float initial);
    static float _ext_CKLBUIPieChart_getStart(s32* p);
    static void _ext_CKLBUIPieChart_setStart(s32* p,float start);
    static float _ext_CKLBUIPieChart_getEnd(s32* p);
    static void _ext_CKLBUIPieChart_setEnd(s32* p,float end);
    static float _ext_CKLBUIPieChart_getValue(s32* p);
    static void _ext_CKLBUIPieChart_setValue(s32* p,float value);
    static s32 _ext_CKLBUIPieChart_getAnim(s32* p);
    static u32 _ext_CKLBUIPieChart_getOrder(s32* p);
    static bool _ext_CKLBUIPieChart_changeAsset(s32* p,s32* assetName);
    CKLBUIPieChart(EnginePrototype::CKLBUITask* parent,u32 order,float x,float y,float width,float height,System::String* image_asset,float start_angle,float end_angle,s32 anim_time,float initial_value);
    CKLBUIPieChart();
    bool changeAsset(System::String* assetName);
    inline bool changeAsset$(System::String* assetName);
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 222;
};
class EnginePrototype::CKLBUIPolyline : public EnginePrototype::CKLBUITask {

public:
    void _ctor_CKLBUIPolyline();
    static u32 s_classID;
    inline static u32 _ss_classIDDivEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID /= value; }
    inline static u32 _ss_classIDModEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID %= value; }

    inline u32 _acc_gOrder();
    inline u32 _acc_gOrder$();

    inline u32 _acc_gMaxPointCount();
    inline u32 _acc_gMaxPointCount$();

    inline u32 _acc_sMaxPointCount(u32 value);
    inline u32 _acc_sMaxPointCount$(u32 value);
    inline u32 _acc_sMaxPointCountpostInc()			{ u32 tmp; _acc_sMaxPointCount((tmp = _acc_gMaxPointCount())+1); return tmp; }
    inline u32 _acc_sMaxPointCount$postInc()			{ CHCKTHIS; return _acc_sMaxPointCountpostInc(); }
    inline u32 _acc_sMaxPointCountpostDec()			{ u32 tmp; _acc_sMaxPointCount((tmp = _acc_gMaxPointCount())-1); return tmp; }
    inline u32 _acc_sMaxPointCount$postDec()			{ CHCKTHIS; return _acc_sMaxPointCountpostDec(); }
    inline u32 _acc_sMaxPointCountpreInc()			{ return _acc_sMaxPointCount(_acc_gMaxPointCount()+1); }
    inline u32 _acc_sMaxPointCount$preInc()			{ CHCKTHIS; return _acc_sMaxPointCountpreInc(); }
    inline u32 _acc_sMaxPointCountpreDec()			{ return _acc_sMaxPointCount(_acc_gMaxPointCount()-1); }
    inline u32 _acc_sMaxPointCount$preDec()			{ CHCKTHIS; return _acc_sMaxPointCountpreDec(); }
    inline u32 _acc_sMaxPointCountAddEq(u32 value)	{ return _acc_sMaxPointCount(_acc_gMaxPointCount() + value); }
    inline u32 _acc_sMaxPointCount$AddEq(u32 value)			{ CHCKTHIS; return _acc_sMaxPointCountAddEq(value); }
    inline u32 _acc_sMaxPointCountSubEq(u32 value)	{ return _acc_sMaxPointCount(_acc_gMaxPointCount() - value); }
    inline u32 _acc_sMaxPointCount$SubEq(u32 value)			{ CHCKTHIS; return _acc_sMaxPointCountSubEq(value); }
    inline u32 _acc_sMaxPointCountMulEq(u32 value)	{ return _acc_sMaxPointCount(_acc_gMaxPointCount() * value); }
    inline u32 _acc_sMaxPointCount$MulEq(u32 value)			{ CHCKTHIS; return _acc_sMaxPointCountMulEq(value); }
    inline u32 _acc_sMaxPointCountDivEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sMaxPointCount(_acc_gMaxPointCount() / value); }
    inline u32 _acc_sMaxPointCount$DivEq(u32 value)			{ CHCKTHIS; return _acc_sMaxPointCountDivEq(value); }
    inline u32 _acc_sMaxPointCountModEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sMaxPointCount(_acc_gMaxPointCount() % value); }
    inline u32 _acc_sMaxPointCount$ModEq(u32 value)			{ CHCKTHIS; return _acc_sMaxPointCountModEq(value); }
    inline u32 _acc_sMaxPointCountXorEq(u32 value)	{ return _acc_sMaxPointCount(_acc_gMaxPointCount() ^ value); }
    inline u32 _acc_sMaxPointCount$XorEq(u32 value)			{ CHCKTHIS; return _acc_sMaxPointCountXorEq(value); }
    inline u32 _acc_sMaxPointCountAndEq(u32 value)	{ return _acc_sMaxPointCount(_acc_gMaxPointCount() & value); }
    inline u32 _acc_sMaxPointCount$AndEq(u32 value)			{ CHCKTHIS; return _acc_sMaxPointCountAndEq(value); }
    inline u32 _acc_sMaxPointCountOrEq(u32 value)		{ return _acc_sMaxPointCount(_acc_gMaxPointCount() | value); }
    inline u32 _acc_sMaxPointCount$OrEq(u32 value)			{ CHCKTHIS; return _acc_sMaxPointCountOrEq(value); }
    inline u32 _acc_sMaxPointCountRShiftEq(u32 value)	{ return _acc_sMaxPointCount(_acc_gMaxPointCount() >> value); }
    inline u32 _acc_sMaxPointCount$RShiftEq(u32 value)			{ CHCKTHIS; return _acc_sMaxPointCountRShiftEq(value); }
    inline u32 _acc_sMaxPointCountLShiftEq(u32 value)	{ return _acc_sMaxPointCount(_acc_gMaxPointCount() << value); }
    inline u32 _acc_sMaxPointCount$LShiftEq(u32 value)			{ CHCKTHIS; return _acc_sMaxPointCountLShiftEq(value); }
    inline u32 _acc_gPointCount();
    inline u32 _acc_gPointCount$();

    inline u32 _acc_sPointCount(u32 value);
    inline u32 _acc_sPointCount$(u32 value);
    inline u32 _acc_sPointCountpostInc()			{ u32 tmp; _acc_sPointCount((tmp = _acc_gPointCount())+1); return tmp; }
    inline u32 _acc_sPointCount$postInc()			{ CHCKTHIS; return _acc_sPointCountpostInc(); }
    inline u32 _acc_sPointCountpostDec()			{ u32 tmp; _acc_sPointCount((tmp = _acc_gPointCount())-1); return tmp; }
    inline u32 _acc_sPointCount$postDec()			{ CHCKTHIS; return _acc_sPointCountpostDec(); }
    inline u32 _acc_sPointCountpreInc()			{ return _acc_sPointCount(_acc_gPointCount()+1); }
    inline u32 _acc_sPointCount$preInc()			{ CHCKTHIS; return _acc_sPointCountpreInc(); }
    inline u32 _acc_sPointCountpreDec()			{ return _acc_sPointCount(_acc_gPointCount()-1); }
    inline u32 _acc_sPointCount$preDec()			{ CHCKTHIS; return _acc_sPointCountpreDec(); }
    inline u32 _acc_sPointCountAddEq(u32 value)	{ return _acc_sPointCount(_acc_gPointCount() + value); }
    inline u32 _acc_sPointCount$AddEq(u32 value)			{ CHCKTHIS; return _acc_sPointCountAddEq(value); }
    inline u32 _acc_sPointCountSubEq(u32 value)	{ return _acc_sPointCount(_acc_gPointCount() - value); }
    inline u32 _acc_sPointCount$SubEq(u32 value)			{ CHCKTHIS; return _acc_sPointCountSubEq(value); }
    inline u32 _acc_sPointCountMulEq(u32 value)	{ return _acc_sPointCount(_acc_gPointCount() * value); }
    inline u32 _acc_sPointCount$MulEq(u32 value)			{ CHCKTHIS; return _acc_sPointCountMulEq(value); }
    inline u32 _acc_sPointCountDivEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sPointCount(_acc_gPointCount() / value); }
    inline u32 _acc_sPointCount$DivEq(u32 value)			{ CHCKTHIS; return _acc_sPointCountDivEq(value); }
    inline u32 _acc_sPointCountModEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sPointCount(_acc_gPointCount() % value); }
    inline u32 _acc_sPointCount$ModEq(u32 value)			{ CHCKTHIS; return _acc_sPointCountModEq(value); }
    inline u32 _acc_sPointCountXorEq(u32 value)	{ return _acc_sPointCount(_acc_gPointCount() ^ value); }
    inline u32 _acc_sPointCount$XorEq(u32 value)			{ CHCKTHIS; return _acc_sPointCountXorEq(value); }
    inline u32 _acc_sPointCountAndEq(u32 value)	{ return _acc_sPointCount(_acc_gPointCount() & value); }
    inline u32 _acc_sPointCount$AndEq(u32 value)			{ CHCKTHIS; return _acc_sPointCountAndEq(value); }
    inline u32 _acc_sPointCountOrEq(u32 value)		{ return _acc_sPointCount(_acc_gPointCount() | value); }
    inline u32 _acc_sPointCount$OrEq(u32 value)			{ CHCKTHIS; return _acc_sPointCountOrEq(value); }
    inline u32 _acc_sPointCountRShiftEq(u32 value)	{ return _acc_sPointCount(_acc_gPointCount() >> value); }
    inline u32 _acc_sPointCount$RShiftEq(u32 value)			{ CHCKTHIS; return _acc_sPointCountRShiftEq(value); }
    inline u32 _acc_sPointCountLShiftEq(u32 value)	{ return _acc_sPointCount(_acc_gPointCount() << value); }
    inline u32 _acc_sPointCount$LShiftEq(u32 value)			{ CHCKTHIS; return _acc_sPointCountLShiftEq(value); }
    inline u32 _acc_gColor();
    inline u32 _acc_gColor$();

    inline u32 _acc_sColor(u32 value);
    inline u32 _acc_sColor$(u32 value);
    inline u32 _acc_sColorpostInc()			{ u32 tmp; _acc_sColor((tmp = _acc_gColor())+1); return tmp; }
    inline u32 _acc_sColor$postInc()			{ CHCKTHIS; return _acc_sColorpostInc(); }
    inline u32 _acc_sColorpostDec()			{ u32 tmp; _acc_sColor((tmp = _acc_gColor())-1); return tmp; }
    inline u32 _acc_sColor$postDec()			{ CHCKTHIS; return _acc_sColorpostDec(); }
    inline u32 _acc_sColorpreInc()			{ return _acc_sColor(_acc_gColor()+1); }
    inline u32 _acc_sColor$preInc()			{ CHCKTHIS; return _acc_sColorpreInc(); }
    inline u32 _acc_sColorpreDec()			{ return _acc_sColor(_acc_gColor()-1); }
    inline u32 _acc_sColor$preDec()			{ CHCKTHIS; return _acc_sColorpreDec(); }
    inline u32 _acc_sColorAddEq(u32 value)	{ return _acc_sColor(_acc_gColor() + value); }
    inline u32 _acc_sColor$AddEq(u32 value)			{ CHCKTHIS; return _acc_sColorAddEq(value); }
    inline u32 _acc_sColorSubEq(u32 value)	{ return _acc_sColor(_acc_gColor() - value); }
    inline u32 _acc_sColor$SubEq(u32 value)			{ CHCKTHIS; return _acc_sColorSubEq(value); }
    inline u32 _acc_sColorMulEq(u32 value)	{ return _acc_sColor(_acc_gColor() * value); }
    inline u32 _acc_sColor$MulEq(u32 value)			{ CHCKTHIS; return _acc_sColorMulEq(value); }
    inline u32 _acc_sColorDivEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sColor(_acc_gColor() / value); }
    inline u32 _acc_sColor$DivEq(u32 value)			{ CHCKTHIS; return _acc_sColorDivEq(value); }
    inline u32 _acc_sColorModEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sColor(_acc_gColor() % value); }
    inline u32 _acc_sColor$ModEq(u32 value)			{ CHCKTHIS; return _acc_sColorModEq(value); }
    inline u32 _acc_sColorXorEq(u32 value)	{ return _acc_sColor(_acc_gColor() ^ value); }
    inline u32 _acc_sColor$XorEq(u32 value)			{ CHCKTHIS; return _acc_sColorXorEq(value); }
    inline u32 _acc_sColorAndEq(u32 value)	{ return _acc_sColor(_acc_gColor() & value); }
    inline u32 _acc_sColor$AndEq(u32 value)			{ CHCKTHIS; return _acc_sColorAndEq(value); }
    inline u32 _acc_sColorOrEq(u32 value)		{ return _acc_sColor(_acc_gColor() | value); }
    inline u32 _acc_sColor$OrEq(u32 value)			{ CHCKTHIS; return _acc_sColorOrEq(value); }
    inline u32 _acc_sColorRShiftEq(u32 value)	{ return _acc_sColor(_acc_gColor() >> value); }
    inline u32 _acc_sColor$RShiftEq(u32 value)			{ CHCKTHIS; return _acc_sColorRShiftEq(value); }
    inline u32 _acc_sColorLShiftEq(u32 value)	{ return _acc_sColor(_acc_gColor() << value); }
    inline u32 _acc_sColor$LShiftEq(u32 value)			{ CHCKTHIS; return _acc_sColorLShiftEq(value); }
    static s32* _ext_CKLBUIPolyline_create(s32* parent,u32 order,u32 maxPoint);
    static u32 _ext_CKLBUIPolyline_getMaxPoint(s32* p);
    static void _ext_CKLBUIPolyline_setMaxPoint(s32* p,u32 maxpointcount);
    static u32 _ext_CKLBUIPolyline_getOrder(s32* p);
    static u32 _ext_CKLBUIPolyline_getPointCount(s32* p);
    static void _ext_CKLBUIPolyline_setPointCount(s32* p,u32 pointcount);
    static void _ext_CKLBUIPolyline_setPoint(s32* p,u32 idx,float x,float y);
    static u32 _ext_CKLBUIPolyline_getColor(s32* p);
    static void _ext_CKLBUIPolyline_setColor(s32* p,u32 color);
    CKLBUIPolyline(EnginePrototype::CKLBUITask* parent,u32 order,u32 maxPoint);
    CKLBUIPolyline();
    void setPoint(u32 point_index,float x,float y);
    inline void setPoint$(u32 point_index,float x,float y);
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 223;
};
class EnginePrototype::CKLBUIProgressBar : public EnginePrototype::CKLBUITask {

public:
    void _ctor_CKLBUIProgressBar();
    static u32 s_classID;
    inline static u32 _ss_classIDDivEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID /= value; }
    inline static u32 _ss_classIDModEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID %= value; }

    inline u32 _acc_gOrder();
    inline u32 _acc_gOrder$();

    inline u32 _acc_sOrder(u32 value);
    inline u32 _acc_sOrder$(u32 value);
    inline u32 _acc_sOrderpostInc()			{ u32 tmp; _acc_sOrder((tmp = _acc_gOrder())+1); return tmp; }
    inline u32 _acc_sOrder$postInc()			{ CHCKTHIS; return _acc_sOrderpostInc(); }
    inline u32 _acc_sOrderpostDec()			{ u32 tmp; _acc_sOrder((tmp = _acc_gOrder())-1); return tmp; }
    inline u32 _acc_sOrder$postDec()			{ CHCKTHIS; return _acc_sOrderpostDec(); }
    inline u32 _acc_sOrderpreInc()			{ return _acc_sOrder(_acc_gOrder()+1); }
    inline u32 _acc_sOrder$preInc()			{ CHCKTHIS; return _acc_sOrderpreInc(); }
    inline u32 _acc_sOrderpreDec()			{ return _acc_sOrder(_acc_gOrder()-1); }
    inline u32 _acc_sOrder$preDec()			{ CHCKTHIS; return _acc_sOrderpreDec(); }
    inline u32 _acc_sOrderAddEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() + value); }
    inline u32 _acc_sOrder$AddEq(u32 value)			{ CHCKTHIS; return _acc_sOrderAddEq(value); }
    inline u32 _acc_sOrderSubEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() - value); }
    inline u32 _acc_sOrder$SubEq(u32 value)			{ CHCKTHIS; return _acc_sOrderSubEq(value); }
    inline u32 _acc_sOrderMulEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() * value); }
    inline u32 _acc_sOrder$MulEq(u32 value)			{ CHCKTHIS; return _acc_sOrderMulEq(value); }
    inline u32 _acc_sOrderDivEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sOrder(_acc_gOrder() / value); }
    inline u32 _acc_sOrder$DivEq(u32 value)			{ CHCKTHIS; return _acc_sOrderDivEq(value); }
    inline u32 _acc_sOrderModEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sOrder(_acc_gOrder() % value); }
    inline u32 _acc_sOrder$ModEq(u32 value)			{ CHCKTHIS; return _acc_sOrderModEq(value); }
    inline u32 _acc_sOrderXorEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() ^ value); }
    inline u32 _acc_sOrder$XorEq(u32 value)			{ CHCKTHIS; return _acc_sOrderXorEq(value); }
    inline u32 _acc_sOrderAndEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() & value); }
    inline u32 _acc_sOrder$AndEq(u32 value)			{ CHCKTHIS; return _acc_sOrderAndEq(value); }
    inline u32 _acc_sOrderOrEq(u32 value)		{ return _acc_sOrder(_acc_gOrder() | value); }
    inline u32 _acc_sOrder$OrEq(u32 value)			{ CHCKTHIS; return _acc_sOrderOrEq(value); }
    inline u32 _acc_sOrderRShiftEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() >> value); }
    inline u32 _acc_sOrder$RShiftEq(u32 value)			{ CHCKTHIS; return _acc_sOrderRShiftEq(value); }
    inline u32 _acc_sOrderLShiftEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() << value); }
    inline u32 _acc_sOrder$LShiftEq(u32 value)			{ CHCKTHIS; return _acc_sOrderLShiftEq(value); }
    inline float _acc_gWidth();
    inline float _acc_gWidth$();

    inline float _acc_sWidth(float value);
    inline float _acc_sWidth$(float value);
    inline float _acc_sWidthpostInc()			{ float tmp; _acc_sWidth((tmp = _acc_gWidth())+1); return tmp; }
    inline float _acc_sWidth$postInc()			{ CHCKTHIS; return _acc_sWidthpostInc(); }
    inline float _acc_sWidthpostDec()			{ float tmp; _acc_sWidth((tmp = _acc_gWidth())-1); return tmp; }
    inline float _acc_sWidth$postDec()			{ CHCKTHIS; return _acc_sWidthpostDec(); }
    inline float _acc_sWidthpreInc()			{ return _acc_sWidth(_acc_gWidth()+1); }
    inline float _acc_sWidth$preInc()			{ CHCKTHIS; return _acc_sWidthpreInc(); }
    inline float _acc_sWidthpreDec()			{ return _acc_sWidth(_acc_gWidth()-1); }
    inline float _acc_sWidth$preDec()			{ CHCKTHIS; return _acc_sWidthpreDec(); }
    inline float _acc_sWidthAddEq(float value)	{ return _acc_sWidth(_acc_gWidth() + value); }
    inline float _acc_sWidth$AddEq(float value)			{ CHCKTHIS; return _acc_sWidthAddEq(value); }
    inline float _acc_sWidthSubEq(float value)	{ return _acc_sWidth(_acc_gWidth() - value); }
    inline float _acc_sWidth$SubEq(float value)			{ CHCKTHIS; return _acc_sWidthSubEq(value); }
    inline float _acc_sWidthMulEq(float value)	{ return _acc_sWidth(_acc_gWidth() * value); }
    inline float _acc_sWidth$MulEq(float value)			{ CHCKTHIS; return _acc_sWidthMulEq(value); }
    inline float _acc_sWidthDivEq(float value)	{ return _acc_sWidth(_acc_gWidth() / value); }
    inline float _acc_sWidth$DivEq(float value)			{ CHCKTHIS; return _acc_sWidthDivEq(value); }
    inline float _acc_sWidthModEq(float value)	{  float orig = _acc_gWidth(); s32 tmp = (s32)(orig / value); return _acc_sWidth(orig - (tmp * value)); }
    inline float _acc_sWidth$ModEq(float value)			{ CHCKTHIS; return _acc_sWidthModEq(value); }
    inline float _acc_gHeight();
    inline float _acc_gHeight$();

    inline float _acc_sHeight(float value);
    inline float _acc_sHeight$(float value);
    inline float _acc_sHeightpostInc()			{ float tmp; _acc_sHeight((tmp = _acc_gHeight())+1); return tmp; }
    inline float _acc_sHeight$postInc()			{ CHCKTHIS; return _acc_sHeightpostInc(); }
    inline float _acc_sHeightpostDec()			{ float tmp; _acc_sHeight((tmp = _acc_gHeight())-1); return tmp; }
    inline float _acc_sHeight$postDec()			{ CHCKTHIS; return _acc_sHeightpostDec(); }
    inline float _acc_sHeightpreInc()			{ return _acc_sHeight(_acc_gHeight()+1); }
    inline float _acc_sHeight$preInc()			{ CHCKTHIS; return _acc_sHeightpreInc(); }
    inline float _acc_sHeightpreDec()			{ return _acc_sHeight(_acc_gHeight()-1); }
    inline float _acc_sHeight$preDec()			{ CHCKTHIS; return _acc_sHeightpreDec(); }
    inline float _acc_sHeightAddEq(float value)	{ return _acc_sHeight(_acc_gHeight() + value); }
    inline float _acc_sHeight$AddEq(float value)			{ CHCKTHIS; return _acc_sHeightAddEq(value); }
    inline float _acc_sHeightSubEq(float value)	{ return _acc_sHeight(_acc_gHeight() - value); }
    inline float _acc_sHeight$SubEq(float value)			{ CHCKTHIS; return _acc_sHeightSubEq(value); }
    inline float _acc_sHeightMulEq(float value)	{ return _acc_sHeight(_acc_gHeight() * value); }
    inline float _acc_sHeight$MulEq(float value)			{ CHCKTHIS; return _acc_sHeightMulEq(value); }
    inline float _acc_sHeightDivEq(float value)	{ return _acc_sHeight(_acc_gHeight() / value); }
    inline float _acc_sHeight$DivEq(float value)			{ CHCKTHIS; return _acc_sHeightDivEq(value); }
    inline float _acc_sHeightModEq(float value)	{  float orig = _acc_gHeight(); s32 tmp = (s32)(orig / value); return _acc_sHeight(orig - (tmp * value)); }
    inline float _acc_sHeight$ModEq(float value)			{ CHCKTHIS; return _acc_sHeightModEq(value); }
    inline bool _acc_gIsVertical();
    inline bool _acc_gIsVertical$();

    inline bool _acc_sIsVertical(bool value);
    inline bool _acc_sIsVertical$(bool value);
    inline u32 _acc_gAnimTime();
    inline u32 _acc_gAnimTime$();

    inline u32 _acc_sAnimTime(u32 value);
    inline u32 _acc_sAnimTime$(u32 value);
    inline u32 _acc_sAnimTimepostInc()			{ u32 tmp; _acc_sAnimTime((tmp = _acc_gAnimTime())+1); return tmp; }
    inline u32 _acc_sAnimTime$postInc()			{ CHCKTHIS; return _acc_sAnimTimepostInc(); }
    inline u32 _acc_sAnimTimepostDec()			{ u32 tmp; _acc_sAnimTime((tmp = _acc_gAnimTime())-1); return tmp; }
    inline u32 _acc_sAnimTime$postDec()			{ CHCKTHIS; return _acc_sAnimTimepostDec(); }
    inline u32 _acc_sAnimTimepreInc()			{ return _acc_sAnimTime(_acc_gAnimTime()+1); }
    inline u32 _acc_sAnimTime$preInc()			{ CHCKTHIS; return _acc_sAnimTimepreInc(); }
    inline u32 _acc_sAnimTimepreDec()			{ return _acc_sAnimTime(_acc_gAnimTime()-1); }
    inline u32 _acc_sAnimTime$preDec()			{ CHCKTHIS; return _acc_sAnimTimepreDec(); }
    inline u32 _acc_sAnimTimeAddEq(u32 value)	{ return _acc_sAnimTime(_acc_gAnimTime() + value); }
    inline u32 _acc_sAnimTime$AddEq(u32 value)			{ CHCKTHIS; return _acc_sAnimTimeAddEq(value); }
    inline u32 _acc_sAnimTimeSubEq(u32 value)	{ return _acc_sAnimTime(_acc_gAnimTime() - value); }
    inline u32 _acc_sAnimTime$SubEq(u32 value)			{ CHCKTHIS; return _acc_sAnimTimeSubEq(value); }
    inline u32 _acc_sAnimTimeMulEq(u32 value)	{ return _acc_sAnimTime(_acc_gAnimTime() * value); }
    inline u32 _acc_sAnimTime$MulEq(u32 value)			{ CHCKTHIS; return _acc_sAnimTimeMulEq(value); }
    inline u32 _acc_sAnimTimeDivEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sAnimTime(_acc_gAnimTime() / value); }
    inline u32 _acc_sAnimTime$DivEq(u32 value)			{ CHCKTHIS; return _acc_sAnimTimeDivEq(value); }
    inline u32 _acc_sAnimTimeModEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sAnimTime(_acc_gAnimTime() % value); }
    inline u32 _acc_sAnimTime$ModEq(u32 value)			{ CHCKTHIS; return _acc_sAnimTimeModEq(value); }
    inline u32 _acc_sAnimTimeXorEq(u32 value)	{ return _acc_sAnimTime(_acc_gAnimTime() ^ value); }
    inline u32 _acc_sAnimTime$XorEq(u32 value)			{ CHCKTHIS; return _acc_sAnimTimeXorEq(value); }
    inline u32 _acc_sAnimTimeAndEq(u32 value)	{ return _acc_sAnimTime(_acc_gAnimTime() & value); }
    inline u32 _acc_sAnimTime$AndEq(u32 value)			{ CHCKTHIS; return _acc_sAnimTimeAndEq(value); }
    inline u32 _acc_sAnimTimeOrEq(u32 value)		{ return _acc_sAnimTime(_acc_gAnimTime() | value); }
    inline u32 _acc_sAnimTime$OrEq(u32 value)			{ CHCKTHIS; return _acc_sAnimTimeOrEq(value); }
    inline u32 _acc_sAnimTimeRShiftEq(u32 value)	{ return _acc_sAnimTime(_acc_gAnimTime() >> value); }
    inline u32 _acc_sAnimTime$RShiftEq(u32 value)			{ CHCKTHIS; return _acc_sAnimTimeRShiftEq(value); }
    inline u32 _acc_sAnimTimeLShiftEq(u32 value)	{ return _acc_sAnimTime(_acc_gAnimTime() << value); }
    inline u32 _acc_sAnimTime$LShiftEq(u32 value)			{ CHCKTHIS; return _acc_sAnimTimeLShiftEq(value); }
    inline float _acc_gStart();
    inline float _acc_gStart$();

    inline float _acc_sStart(float value);
    inline float _acc_sStart$(float value);
    inline float _acc_sStartpostInc()			{ float tmp; _acc_sStart((tmp = _acc_gStart())+1); return tmp; }
    inline float _acc_sStart$postInc()			{ CHCKTHIS; return _acc_sStartpostInc(); }
    inline float _acc_sStartpostDec()			{ float tmp; _acc_sStart((tmp = _acc_gStart())-1); return tmp; }
    inline float _acc_sStart$postDec()			{ CHCKTHIS; return _acc_sStartpostDec(); }
    inline float _acc_sStartpreInc()			{ return _acc_sStart(_acc_gStart()+1); }
    inline float _acc_sStart$preInc()			{ CHCKTHIS; return _acc_sStartpreInc(); }
    inline float _acc_sStartpreDec()			{ return _acc_sStart(_acc_gStart()-1); }
    inline float _acc_sStart$preDec()			{ CHCKTHIS; return _acc_sStartpreDec(); }
    inline float _acc_sStartAddEq(float value)	{ return _acc_sStart(_acc_gStart() + value); }
    inline float _acc_sStart$AddEq(float value)			{ CHCKTHIS; return _acc_sStartAddEq(value); }
    inline float _acc_sStartSubEq(float value)	{ return _acc_sStart(_acc_gStart() - value); }
    inline float _acc_sStart$SubEq(float value)			{ CHCKTHIS; return _acc_sStartSubEq(value); }
    inline float _acc_sStartMulEq(float value)	{ return _acc_sStart(_acc_gStart() * value); }
    inline float _acc_sStart$MulEq(float value)			{ CHCKTHIS; return _acc_sStartMulEq(value); }
    inline float _acc_sStartDivEq(float value)	{ return _acc_sStart(_acc_gStart() / value); }
    inline float _acc_sStart$DivEq(float value)			{ CHCKTHIS; return _acc_sStartDivEq(value); }
    inline float _acc_sStartModEq(float value)	{  float orig = _acc_gStart(); s32 tmp = (s32)(orig / value); return _acc_sStart(orig - (tmp * value)); }
    inline float _acc_sStart$ModEq(float value)			{ CHCKTHIS; return _acc_sStartModEq(value); }
    inline float _acc_gEnd();
    inline float _acc_gEnd$();

    inline float _acc_sEnd(float value);
    inline float _acc_sEnd$(float value);
    inline float _acc_sEndpostInc()			{ float tmp; _acc_sEnd((tmp = _acc_gEnd())+1); return tmp; }
    inline float _acc_sEnd$postInc()			{ CHCKTHIS; return _acc_sEndpostInc(); }
    inline float _acc_sEndpostDec()			{ float tmp; _acc_sEnd((tmp = _acc_gEnd())-1); return tmp; }
    inline float _acc_sEnd$postDec()			{ CHCKTHIS; return _acc_sEndpostDec(); }
    inline float _acc_sEndpreInc()			{ return _acc_sEnd(_acc_gEnd()+1); }
    inline float _acc_sEnd$preInc()			{ CHCKTHIS; return _acc_sEndpreInc(); }
    inline float _acc_sEndpreDec()			{ return _acc_sEnd(_acc_gEnd()-1); }
    inline float _acc_sEnd$preDec()			{ CHCKTHIS; return _acc_sEndpreDec(); }
    inline float _acc_sEndAddEq(float value)	{ return _acc_sEnd(_acc_gEnd() + value); }
    inline float _acc_sEnd$AddEq(float value)			{ CHCKTHIS; return _acc_sEndAddEq(value); }
    inline float _acc_sEndSubEq(float value)	{ return _acc_sEnd(_acc_gEnd() - value); }
    inline float _acc_sEnd$SubEq(float value)			{ CHCKTHIS; return _acc_sEndSubEq(value); }
    inline float _acc_sEndMulEq(float value)	{ return _acc_sEnd(_acc_gEnd() * value); }
    inline float _acc_sEnd$MulEq(float value)			{ CHCKTHIS; return _acc_sEndMulEq(value); }
    inline float _acc_sEndDivEq(float value)	{ return _acc_sEnd(_acc_gEnd() / value); }
    inline float _acc_sEnd$DivEq(float value)			{ CHCKTHIS; return _acc_sEndDivEq(value); }
    inline float _acc_sEndModEq(float value)	{  float orig = _acc_gEnd(); s32 tmp = (s32)(orig / value); return _acc_sEnd(orig - (tmp * value)); }
    inline float _acc_sEnd$ModEq(float value)			{ CHCKTHIS; return _acc_sEndModEq(value); }
    inline System::String* _acc_gImageEmpty();
    inline System::String* _acc_gImageEmpty$();

    inline System::String* _acc_sImageEmpty(System::String* value);
    inline System::String* _acc_sImageEmpty$(System::String* value);
    inline System::String* _acc_gImageFull();
    inline System::String* _acc_gImageFull$();

    inline System::String* _acc_sImageFull(System::String* value);
    inline System::String* _acc_sImageFull$(System::String* value);
    inline System::String* _acc_gImageFilter();
    inline System::String* _acc_gImageFilter$();

    inline System::String* _acc_sImageFilter(System::String* value);
    inline System::String* _acc_sImageFilter$(System::String* value);
    inline float _acc_gValue();
    inline float _acc_gValue$();

    inline float _acc_sValue(float value);
    inline float _acc_sValue$(float value);
    inline float _acc_sValuepostInc()			{ float tmp; _acc_sValue((tmp = _acc_gValue())+1); return tmp; }
    inline float _acc_sValue$postInc()			{ CHCKTHIS; return _acc_sValuepostInc(); }
    inline float _acc_sValuepostDec()			{ float tmp; _acc_sValue((tmp = _acc_gValue())-1); return tmp; }
    inline float _acc_sValue$postDec()			{ CHCKTHIS; return _acc_sValuepostDec(); }
    inline float _acc_sValuepreInc()			{ return _acc_sValue(_acc_gValue()+1); }
    inline float _acc_sValue$preInc()			{ CHCKTHIS; return _acc_sValuepreInc(); }
    inline float _acc_sValuepreDec()			{ return _acc_sValue(_acc_gValue()-1); }
    inline float _acc_sValue$preDec()			{ CHCKTHIS; return _acc_sValuepreDec(); }
    inline float _acc_sValueAddEq(float value)	{ return _acc_sValue(_acc_gValue() + value); }
    inline float _acc_sValue$AddEq(float value)			{ CHCKTHIS; return _acc_sValueAddEq(value); }
    inline float _acc_sValueSubEq(float value)	{ return _acc_sValue(_acc_gValue() - value); }
    inline float _acc_sValue$SubEq(float value)			{ CHCKTHIS; return _acc_sValueSubEq(value); }
    inline float _acc_sValueMulEq(float value)	{ return _acc_sValue(_acc_gValue() * value); }
    inline float _acc_sValue$MulEq(float value)			{ CHCKTHIS; return _acc_sValueMulEq(value); }
    inline float _acc_sValueDivEq(float value)	{ return _acc_sValue(_acc_gValue() / value); }
    inline float _acc_sValue$DivEq(float value)			{ CHCKTHIS; return _acc_sValueDivEq(value); }
    inline float _acc_sValueModEq(float value)	{  float orig = _acc_gValue(); s32 tmp = (s32)(orig / value); return _acc_sValue(orig - (tmp * value)); }
    inline float _acc_sValue$ModEq(float value)			{ CHCKTHIS; return _acc_sValueModEq(value); }
    inline bool _acc_gFilterVisible();
    inline bool _acc_gFilterVisible$();

    inline bool _acc_sFilterVisible(bool value);
    inline bool _acc_sFilterVisible$(bool value);
    inline u32 _acc_gFilterColor();
    inline u32 _acc_gFilterColor$();

    inline u32 _acc_sFilterColor(u32 value);
    inline u32 _acc_sFilterColor$(u32 value);
    inline u32 _acc_sFilterColorpostInc()			{ u32 tmp; _acc_sFilterColor((tmp = _acc_gFilterColor())+1); return tmp; }
    inline u32 _acc_sFilterColor$postInc()			{ CHCKTHIS; return _acc_sFilterColorpostInc(); }
    inline u32 _acc_sFilterColorpostDec()			{ u32 tmp; _acc_sFilterColor((tmp = _acc_gFilterColor())-1); return tmp; }
    inline u32 _acc_sFilterColor$postDec()			{ CHCKTHIS; return _acc_sFilterColorpostDec(); }
    inline u32 _acc_sFilterColorpreInc()			{ return _acc_sFilterColor(_acc_gFilterColor()+1); }
    inline u32 _acc_sFilterColor$preInc()			{ CHCKTHIS; return _acc_sFilterColorpreInc(); }
    inline u32 _acc_sFilterColorpreDec()			{ return _acc_sFilterColor(_acc_gFilterColor()-1); }
    inline u32 _acc_sFilterColor$preDec()			{ CHCKTHIS; return _acc_sFilterColorpreDec(); }
    inline u32 _acc_sFilterColorAddEq(u32 value)	{ return _acc_sFilterColor(_acc_gFilterColor() + value); }
    inline u32 _acc_sFilterColor$AddEq(u32 value)			{ CHCKTHIS; return _acc_sFilterColorAddEq(value); }
    inline u32 _acc_sFilterColorSubEq(u32 value)	{ return _acc_sFilterColor(_acc_gFilterColor() - value); }
    inline u32 _acc_sFilterColor$SubEq(u32 value)			{ CHCKTHIS; return _acc_sFilterColorSubEq(value); }
    inline u32 _acc_sFilterColorMulEq(u32 value)	{ return _acc_sFilterColor(_acc_gFilterColor() * value); }
    inline u32 _acc_sFilterColor$MulEq(u32 value)			{ CHCKTHIS; return _acc_sFilterColorMulEq(value); }
    inline u32 _acc_sFilterColorDivEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sFilterColor(_acc_gFilterColor() / value); }
    inline u32 _acc_sFilterColor$DivEq(u32 value)			{ CHCKTHIS; return _acc_sFilterColorDivEq(value); }
    inline u32 _acc_sFilterColorModEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sFilterColor(_acc_gFilterColor() % value); }
    inline u32 _acc_sFilterColor$ModEq(u32 value)			{ CHCKTHIS; return _acc_sFilterColorModEq(value); }
    inline u32 _acc_sFilterColorXorEq(u32 value)	{ return _acc_sFilterColor(_acc_gFilterColor() ^ value); }
    inline u32 _acc_sFilterColor$XorEq(u32 value)			{ CHCKTHIS; return _acc_sFilterColorXorEq(value); }
    inline u32 _acc_sFilterColorAndEq(u32 value)	{ return _acc_sFilterColor(_acc_gFilterColor() & value); }
    inline u32 _acc_sFilterColor$AndEq(u32 value)			{ CHCKTHIS; return _acc_sFilterColorAndEq(value); }
    inline u32 _acc_sFilterColorOrEq(u32 value)		{ return _acc_sFilterColor(_acc_gFilterColor() | value); }
    inline u32 _acc_sFilterColor$OrEq(u32 value)			{ CHCKTHIS; return _acc_sFilterColorOrEq(value); }
    inline u32 _acc_sFilterColorRShiftEq(u32 value)	{ return _acc_sFilterColor(_acc_gFilterColor() >> value); }
    inline u32 _acc_sFilterColor$RShiftEq(u32 value)			{ CHCKTHIS; return _acc_sFilterColorRShiftEq(value); }
    inline u32 _acc_sFilterColorLShiftEq(u32 value)	{ return _acc_sFilterColor(_acc_gFilterColor() << value); }
    inline u32 _acc_sFilterColor$LShiftEq(u32 value)			{ CHCKTHIS; return _acc_sFilterColorLShiftEq(value); }
    static s32* _ext_CKLBUIProgressBar_create(s32* pParent,u32 order,float x,float y,float width,float height,s32* fullImage,s32* emptyImage,s32 startPix,s32 endPix,s32 anim,bool vert,s32* barfilterImage);
    static u32 _ext_CKLBUIProgressBar_getOrder(s32* p);
    static void _ext_CKLBUIProgressBar_setOrder(s32* p,u32 order);
    static float _ext_CKLBUIProgressBar_getWidth(s32* p);
    static void _ext_CKLBUIProgressBar_setWidth(s32* p,float width);
    static float _ext_CKLBUIProgressBar_getHeight(s32* p);
    static void _ext_CKLBUIProgressBar_setHeight(s32* p,float height);
    static bool _ext_CKLBUIProgressBar_getVertical(s32* p);
    static void _ext_CKLBUIProgressBar_setVertical(s32* p,bool vertical);
    static u32 _ext_CKLBUIProgressBar_getAnimTime(s32* p);
    static void _ext_CKLBUIProgressBar_setAnimTime(s32* p,u32 time);
    static float _ext_CKLBUIProgressBar_getStart(s32* p);
    static void _ext_CKLBUIProgressBar_setStart(s32* p,float start);
    static float _ext_CKLBUIProgressBar_getEnd(s32* p);
    static void _ext_CKLBUIProgressBar_setEnd(s32* p,float end);
    static float _ext_CKLBUIProgressBar_getValue(s32* p);
    static void _ext_CKLBUIProgressBar_setValue(s32* p,float value);
    static s32* _ext_CKLBUIProgressBar_getImgEmpty(s32* p);
    static void _ext_CKLBUIProgressBar_setImgEmpty(s32* p,s32* imageEmpty);
    static s32* _ext_CKLBUIProgressBar_getImgFull(s32* p);
    static void _ext_CKLBUIProgressBar_setImgFull(s32* p,s32* imageFull);
    static s32* _ext_CKLBUIProgressBar_getImgFilter(s32* p);
    static void _ext_CKLBUIProgressBar_setImgFilter(s32* p,s32* imageFilter);
    static void _ext_CKLBUIProgressBar_reset(s32* p);
    static bool _ext_CKLBUIProgressBar_getFilterVisible(s32* p);
    static void _ext_CKLBUIProgressBar_setFilterVisible(s32* p,bool value);
    static u32 _ext_CKLBUIProgressBar_getFilterColor(s32* p);
    static void _ext_CKLBUIProgressBar_setFilterColor(s32* p,u32 value);
    static bool _ext_CKLBUIProgressBar_setFilterAnim(s32* p,bool bColAnim,u32 argb1,u32 argb2,u32 freq);
    CKLBUIProgressBar(EnginePrototype::CKLBUITask* parent,u32 order,float x,float y,float width,float height,System::String* imageFull,System::String* imageEmpty,s32 startPix,s32 endPix,s32 animTime,bool verticalFlag,System::String* barfilterImage);
    CKLBUIProgressBar();
    void getSize(EnginePrototype::FSize& size);
    inline void getSize$(EnginePrototype::FSize& size);
    void setSize(EnginePrototype::FSize size);
    inline void setSize$(EnginePrototype::FSize size);
    void setSize(float width,float height);
    inline void setSize$(float width,float height);
    void reset();
    inline void reset$();
    void complete();
    inline void complete$();
    bool setFilterAnim(bool bColAnim,u32 argb1,u32 argb2,u32 freq);
    inline bool setFilterAnim$(bool bColAnim,u32 argb1,u32 argb2,u32 freq);
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 224;
};
class EnginePrototype::CKLBUIRubberBand : public EnginePrototype::CKLBUITask {

public:
    void _ctor_CKLBUIRubberBand();
    static u32 s_classID;
    inline static u32 _ss_classIDDivEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID /= value; }
    inline static u32 _ss_classIDModEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID %= value; }

    inline u32 _acc_gOrder();
    inline u32 _acc_gOrder$();

    inline System::String* _acc_gAssetOrigin();
    inline System::String* _acc_gAssetOrigin$();

    inline System::String* _acc_gAssetJoint();
    inline System::String* _acc_gAssetJoint$();

    inline System::String* _acc_gAssetPoint();
    inline System::String* _acc_gAssetPoint$();

    inline float _acc_gOriginX();
    inline float _acc_gOriginX$();

    inline float _acc_sOriginX(float value);
    inline float _acc_sOriginX$(float value);
    inline float _acc_sOriginXpostInc()			{ float tmp; _acc_sOriginX((tmp = _acc_gOriginX())+1); return tmp; }
    inline float _acc_sOriginX$postInc()			{ CHCKTHIS; return _acc_sOriginXpostInc(); }
    inline float _acc_sOriginXpostDec()			{ float tmp; _acc_sOriginX((tmp = _acc_gOriginX())-1); return tmp; }
    inline float _acc_sOriginX$postDec()			{ CHCKTHIS; return _acc_sOriginXpostDec(); }
    inline float _acc_sOriginXpreInc()			{ return _acc_sOriginX(_acc_gOriginX()+1); }
    inline float _acc_sOriginX$preInc()			{ CHCKTHIS; return _acc_sOriginXpreInc(); }
    inline float _acc_sOriginXpreDec()			{ return _acc_sOriginX(_acc_gOriginX()-1); }
    inline float _acc_sOriginX$preDec()			{ CHCKTHIS; return _acc_sOriginXpreDec(); }
    inline float _acc_sOriginXAddEq(float value)	{ return _acc_sOriginX(_acc_gOriginX() + value); }
    inline float _acc_sOriginX$AddEq(float value)			{ CHCKTHIS; return _acc_sOriginXAddEq(value); }
    inline float _acc_sOriginXSubEq(float value)	{ return _acc_sOriginX(_acc_gOriginX() - value); }
    inline float _acc_sOriginX$SubEq(float value)			{ CHCKTHIS; return _acc_sOriginXSubEq(value); }
    inline float _acc_sOriginXMulEq(float value)	{ return _acc_sOriginX(_acc_gOriginX() * value); }
    inline float _acc_sOriginX$MulEq(float value)			{ CHCKTHIS; return _acc_sOriginXMulEq(value); }
    inline float _acc_sOriginXDivEq(float value)	{ return _acc_sOriginX(_acc_gOriginX() / value); }
    inline float _acc_sOriginX$DivEq(float value)			{ CHCKTHIS; return _acc_sOriginXDivEq(value); }
    inline float _acc_sOriginXModEq(float value)	{  float orig = _acc_gOriginX(); s32 tmp = (s32)(orig / value); return _acc_sOriginX(orig - (tmp * value)); }
    inline float _acc_sOriginX$ModEq(float value)			{ CHCKTHIS; return _acc_sOriginXModEq(value); }
    inline float _acc_gOriginY();
    inline float _acc_gOriginY$();

    inline float _acc_sOriginY(float value);
    inline float _acc_sOriginY$(float value);
    inline float _acc_sOriginYpostInc()			{ float tmp; _acc_sOriginY((tmp = _acc_gOriginY())+1); return tmp; }
    inline float _acc_sOriginY$postInc()			{ CHCKTHIS; return _acc_sOriginYpostInc(); }
    inline float _acc_sOriginYpostDec()			{ float tmp; _acc_sOriginY((tmp = _acc_gOriginY())-1); return tmp; }
    inline float _acc_sOriginY$postDec()			{ CHCKTHIS; return _acc_sOriginYpostDec(); }
    inline float _acc_sOriginYpreInc()			{ return _acc_sOriginY(_acc_gOriginY()+1); }
    inline float _acc_sOriginY$preInc()			{ CHCKTHIS; return _acc_sOriginYpreInc(); }
    inline float _acc_sOriginYpreDec()			{ return _acc_sOriginY(_acc_gOriginY()-1); }
    inline float _acc_sOriginY$preDec()			{ CHCKTHIS; return _acc_sOriginYpreDec(); }
    inline float _acc_sOriginYAddEq(float value)	{ return _acc_sOriginY(_acc_gOriginY() + value); }
    inline float _acc_sOriginY$AddEq(float value)			{ CHCKTHIS; return _acc_sOriginYAddEq(value); }
    inline float _acc_sOriginYSubEq(float value)	{ return _acc_sOriginY(_acc_gOriginY() - value); }
    inline float _acc_sOriginY$SubEq(float value)			{ CHCKTHIS; return _acc_sOriginYSubEq(value); }
    inline float _acc_sOriginYMulEq(float value)	{ return _acc_sOriginY(_acc_gOriginY() * value); }
    inline float _acc_sOriginY$MulEq(float value)			{ CHCKTHIS; return _acc_sOriginYMulEq(value); }
    inline float _acc_sOriginYDivEq(float value)	{ return _acc_sOriginY(_acc_gOriginY() / value); }
    inline float _acc_sOriginY$DivEq(float value)			{ CHCKTHIS; return _acc_sOriginYDivEq(value); }
    inline float _acc_sOriginYModEq(float value)	{  float orig = _acc_gOriginY(); s32 tmp = (s32)(orig / value); return _acc_sOriginY(orig - (tmp * value)); }
    inline float _acc_sOriginY$ModEq(float value)			{ CHCKTHIS; return _acc_sOriginYModEq(value); }
    inline float _acc_gPointX();
    inline float _acc_gPointX$();

    inline float _acc_sPointX(float value);
    inline float _acc_sPointX$(float value);
    inline float _acc_sPointXpostInc()			{ float tmp; _acc_sPointX((tmp = _acc_gPointX())+1); return tmp; }
    inline float _acc_sPointX$postInc()			{ CHCKTHIS; return _acc_sPointXpostInc(); }
    inline float _acc_sPointXpostDec()			{ float tmp; _acc_sPointX((tmp = _acc_gPointX())-1); return tmp; }
    inline float _acc_sPointX$postDec()			{ CHCKTHIS; return _acc_sPointXpostDec(); }
    inline float _acc_sPointXpreInc()			{ return _acc_sPointX(_acc_gPointX()+1); }
    inline float _acc_sPointX$preInc()			{ CHCKTHIS; return _acc_sPointXpreInc(); }
    inline float _acc_sPointXpreDec()			{ return _acc_sPointX(_acc_gPointX()-1); }
    inline float _acc_sPointX$preDec()			{ CHCKTHIS; return _acc_sPointXpreDec(); }
    inline float _acc_sPointXAddEq(float value)	{ return _acc_sPointX(_acc_gPointX() + value); }
    inline float _acc_sPointX$AddEq(float value)			{ CHCKTHIS; return _acc_sPointXAddEq(value); }
    inline float _acc_sPointXSubEq(float value)	{ return _acc_sPointX(_acc_gPointX() - value); }
    inline float _acc_sPointX$SubEq(float value)			{ CHCKTHIS; return _acc_sPointXSubEq(value); }
    inline float _acc_sPointXMulEq(float value)	{ return _acc_sPointX(_acc_gPointX() * value); }
    inline float _acc_sPointX$MulEq(float value)			{ CHCKTHIS; return _acc_sPointXMulEq(value); }
    inline float _acc_sPointXDivEq(float value)	{ return _acc_sPointX(_acc_gPointX() / value); }
    inline float _acc_sPointX$DivEq(float value)			{ CHCKTHIS; return _acc_sPointXDivEq(value); }
    inline float _acc_sPointXModEq(float value)	{  float orig = _acc_gPointX(); s32 tmp = (s32)(orig / value); return _acc_sPointX(orig - (tmp * value)); }
    inline float _acc_sPointX$ModEq(float value)			{ CHCKTHIS; return _acc_sPointXModEq(value); }
    inline float _acc_gPointY();
    inline float _acc_gPointY$();

    inline float _acc_sPointY(float value);
    inline float _acc_sPointY$(float value);
    inline float _acc_sPointYpostInc()			{ float tmp; _acc_sPointY((tmp = _acc_gPointY())+1); return tmp; }
    inline float _acc_sPointY$postInc()			{ CHCKTHIS; return _acc_sPointYpostInc(); }
    inline float _acc_sPointYpostDec()			{ float tmp; _acc_sPointY((tmp = _acc_gPointY())-1); return tmp; }
    inline float _acc_sPointY$postDec()			{ CHCKTHIS; return _acc_sPointYpostDec(); }
    inline float _acc_sPointYpreInc()			{ return _acc_sPointY(_acc_gPointY()+1); }
    inline float _acc_sPointY$preInc()			{ CHCKTHIS; return _acc_sPointYpreInc(); }
    inline float _acc_sPointYpreDec()			{ return _acc_sPointY(_acc_gPointY()-1); }
    inline float _acc_sPointY$preDec()			{ CHCKTHIS; return _acc_sPointYpreDec(); }
    inline float _acc_sPointYAddEq(float value)	{ return _acc_sPointY(_acc_gPointY() + value); }
    inline float _acc_sPointY$AddEq(float value)			{ CHCKTHIS; return _acc_sPointYAddEq(value); }
    inline float _acc_sPointYSubEq(float value)	{ return _acc_sPointY(_acc_gPointY() - value); }
    inline float _acc_sPointY$SubEq(float value)			{ CHCKTHIS; return _acc_sPointYSubEq(value); }
    inline float _acc_sPointYMulEq(float value)	{ return _acc_sPointY(_acc_gPointY() * value); }
    inline float _acc_sPointY$MulEq(float value)			{ CHCKTHIS; return _acc_sPointYMulEq(value); }
    inline float _acc_sPointYDivEq(float value)	{ return _acc_sPointY(_acc_gPointY() / value); }
    inline float _acc_sPointY$DivEq(float value)			{ CHCKTHIS; return _acc_sPointYDivEq(value); }
    inline float _acc_sPointYModEq(float value)	{  float orig = _acc_gPointY(); s32 tmp = (s32)(orig / value); return _acc_sPointY(orig - (tmp * value)); }
    inline float _acc_sPointY$ModEq(float value)			{ CHCKTHIS; return _acc_sPointYModEq(value); }
    inline bool _acc_gAnimFlag();
    inline bool _acc_gAnimFlag$();

    inline bool _acc_sAnimFlag(bool value);
    inline bool _acc_sAnimFlag$(bool value);
    inline bool _acc_gRealTimeFlag();
    inline bool _acc_gRealTimeFlag$();

    inline bool _acc_sRealTimeFlag(bool value);
    inline bool _acc_sRealTimeFlag$(bool value);
    inline u32 _acc_gAnimTime();
    inline u32 _acc_gAnimTime$();

    inline u32 _acc_sAnimTime(u32 value);
    inline u32 _acc_sAnimTime$(u32 value);
    inline u32 _acc_sAnimTimepostInc()			{ u32 tmp; _acc_sAnimTime((tmp = _acc_gAnimTime())+1); return tmp; }
    inline u32 _acc_sAnimTime$postInc()			{ CHCKTHIS; return _acc_sAnimTimepostInc(); }
    inline u32 _acc_sAnimTimepostDec()			{ u32 tmp; _acc_sAnimTime((tmp = _acc_gAnimTime())-1); return tmp; }
    inline u32 _acc_sAnimTime$postDec()			{ CHCKTHIS; return _acc_sAnimTimepostDec(); }
    inline u32 _acc_sAnimTimepreInc()			{ return _acc_sAnimTime(_acc_gAnimTime()+1); }
    inline u32 _acc_sAnimTime$preInc()			{ CHCKTHIS; return _acc_sAnimTimepreInc(); }
    inline u32 _acc_sAnimTimepreDec()			{ return _acc_sAnimTime(_acc_gAnimTime()-1); }
    inline u32 _acc_sAnimTime$preDec()			{ CHCKTHIS; return _acc_sAnimTimepreDec(); }
    inline u32 _acc_sAnimTimeAddEq(u32 value)	{ return _acc_sAnimTime(_acc_gAnimTime() + value); }
    inline u32 _acc_sAnimTime$AddEq(u32 value)			{ CHCKTHIS; return _acc_sAnimTimeAddEq(value); }
    inline u32 _acc_sAnimTimeSubEq(u32 value)	{ return _acc_sAnimTime(_acc_gAnimTime() - value); }
    inline u32 _acc_sAnimTime$SubEq(u32 value)			{ CHCKTHIS; return _acc_sAnimTimeSubEq(value); }
    inline u32 _acc_sAnimTimeMulEq(u32 value)	{ return _acc_sAnimTime(_acc_gAnimTime() * value); }
    inline u32 _acc_sAnimTime$MulEq(u32 value)			{ CHCKTHIS; return _acc_sAnimTimeMulEq(value); }
    inline u32 _acc_sAnimTimeDivEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sAnimTime(_acc_gAnimTime() / value); }
    inline u32 _acc_sAnimTime$DivEq(u32 value)			{ CHCKTHIS; return _acc_sAnimTimeDivEq(value); }
    inline u32 _acc_sAnimTimeModEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sAnimTime(_acc_gAnimTime() % value); }
    inline u32 _acc_sAnimTime$ModEq(u32 value)			{ CHCKTHIS; return _acc_sAnimTimeModEq(value); }
    inline u32 _acc_sAnimTimeXorEq(u32 value)	{ return _acc_sAnimTime(_acc_gAnimTime() ^ value); }
    inline u32 _acc_sAnimTime$XorEq(u32 value)			{ CHCKTHIS; return _acc_sAnimTimeXorEq(value); }
    inline u32 _acc_sAnimTimeAndEq(u32 value)	{ return _acc_sAnimTime(_acc_gAnimTime() & value); }
    inline u32 _acc_sAnimTime$AndEq(u32 value)			{ CHCKTHIS; return _acc_sAnimTimeAndEq(value); }
    inline u32 _acc_sAnimTimeOrEq(u32 value)		{ return _acc_sAnimTime(_acc_gAnimTime() | value); }
    inline u32 _acc_sAnimTime$OrEq(u32 value)			{ CHCKTHIS; return _acc_sAnimTimeOrEq(value); }
    inline u32 _acc_sAnimTimeRShiftEq(u32 value)	{ return _acc_sAnimTime(_acc_gAnimTime() >> value); }
    inline u32 _acc_sAnimTime$RShiftEq(u32 value)			{ CHCKTHIS; return _acc_sAnimTimeRShiftEq(value); }
    inline u32 _acc_sAnimTimeLShiftEq(u32 value)	{ return _acc_sAnimTime(_acc_gAnimTime() << value); }
    inline u32 _acc_sAnimTime$LShiftEq(u32 value)			{ CHCKTHIS; return _acc_sAnimTimeLShiftEq(value); }
    static s32* _ext_CKLBUIRubberBand_create(s32* pParent,u32 order,float x,float y,u32 resolution,s32* origin,s32* joint,s32* point,u32 flags,u32 animTime,s32 joint_order_off,s32 point_order_off,bool rot_origin,bool rot_joint,bool rot_point);
    static float _ext_CKLBUIRubberBand_getOriginX(s32* p);
    static void _ext_CKLBUIRubberBand_setOriginX(s32* p,float x);
    static float _ext_CKLBUIRubberBand_getOriginY(s32* p);
    static void _ext_CKLBUIRubberBand_setOriginY(s32* p,float y);
    static float _ext_CKLBUIRubberBand_getPointX(s32* p);
    static void _ext_CKLBUIRubberBand_setPointX(s32* p,float x);
    static float _ext_CKLBUIRubberBand_getPointY(s32* p);
    static void _ext_CKLBUIRubberBand_setPointY(s32* p,float y);
    static bool _ext_CKLBUIRubberBand_getFAnim(s32* p);
    static void _ext_CKLBUIRubberBand_setFAnim(s32* p,bool fAnim);
    static bool _ext_CKLBUIRubberBand_getFAnimRT(s32* p);
    static void _ext_CKLBUIRubberBand_setFAnimRT(s32* p,bool fAnimRT);
    static u32 _ext_CKLBUIRubberBand_getAnimTime(s32* p);
    static void _ext_CKLBUIRubberBand_setAnimTime(s32* p,u32 animTime);
    static u32 _ext_CKLBUIRubberBand_getOrder(s32* p);
    static s32* _ext_CKLBUIRubberBand_getAssetOrigin(s32* p);
    static s32* _ext_CKLBUIRubberBand_getAssetJoint(s32* p);
    static s32* _ext_CKLBUIRubberBand_getAssetPoint(s32* p);
    static bool _ext_CKLBUIRubberBand_setOrder(s32* p,u32 orderOrigin,u32 orderJoint,u32 orderPoint);
    CKLBUIRubberBand(EnginePrototype::CKLBUITask* parent,u32 order,float origin_x,float origin_y,System::String* origin_asset,System::String* joint_asset,System::String* point_asset,u32 resolution,u32 option_flags,u32 animation_time,s32 joint_priority_offset,s32 point_priority_offset,bool rot_origin,bool rot_joint,bool rot_point);
    CKLBUIRubberBand();
    void setOrder(u32 orderOrigin,u32 orderJoint,u32 orderPoint);
    inline void setOrder$(u32 orderOrigin,u32 orderJoint,u32 orderPoint);
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 225;
};
class EnginePrototype::CKLBUIScale9 : public EnginePrototype::CKLBUITask {

public:
    void _ctor_CKLBUIScale9();
    static u32 s_classID;
    inline static u32 _ss_classIDDivEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID /= value; }
    inline static u32 _ss_classIDModEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID %= value; }

    inline u32 _acc_gOrder();
    inline u32 _acc_gOrder$();

    inline u32 _acc_sOrder(u32 value);
    inline u32 _acc_sOrder$(u32 value);
    inline u32 _acc_sOrderpostInc()			{ u32 tmp; _acc_sOrder((tmp = _acc_gOrder())+1); return tmp; }
    inline u32 _acc_sOrder$postInc()			{ CHCKTHIS; return _acc_sOrderpostInc(); }
    inline u32 _acc_sOrderpostDec()			{ u32 tmp; _acc_sOrder((tmp = _acc_gOrder())-1); return tmp; }
    inline u32 _acc_sOrder$postDec()			{ CHCKTHIS; return _acc_sOrderpostDec(); }
    inline u32 _acc_sOrderpreInc()			{ return _acc_sOrder(_acc_gOrder()+1); }
    inline u32 _acc_sOrder$preInc()			{ CHCKTHIS; return _acc_sOrderpreInc(); }
    inline u32 _acc_sOrderpreDec()			{ return _acc_sOrder(_acc_gOrder()-1); }
    inline u32 _acc_sOrder$preDec()			{ CHCKTHIS; return _acc_sOrderpreDec(); }
    inline u32 _acc_sOrderAddEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() + value); }
    inline u32 _acc_sOrder$AddEq(u32 value)			{ CHCKTHIS; return _acc_sOrderAddEq(value); }
    inline u32 _acc_sOrderSubEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() - value); }
    inline u32 _acc_sOrder$SubEq(u32 value)			{ CHCKTHIS; return _acc_sOrderSubEq(value); }
    inline u32 _acc_sOrderMulEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() * value); }
    inline u32 _acc_sOrder$MulEq(u32 value)			{ CHCKTHIS; return _acc_sOrderMulEq(value); }
    inline u32 _acc_sOrderDivEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sOrder(_acc_gOrder() / value); }
    inline u32 _acc_sOrder$DivEq(u32 value)			{ CHCKTHIS; return _acc_sOrderDivEq(value); }
    inline u32 _acc_sOrderModEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sOrder(_acc_gOrder() % value); }
    inline u32 _acc_sOrder$ModEq(u32 value)			{ CHCKTHIS; return _acc_sOrderModEq(value); }
    inline u32 _acc_sOrderXorEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() ^ value); }
    inline u32 _acc_sOrder$XorEq(u32 value)			{ CHCKTHIS; return _acc_sOrderXorEq(value); }
    inline u32 _acc_sOrderAndEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() & value); }
    inline u32 _acc_sOrder$AndEq(u32 value)			{ CHCKTHIS; return _acc_sOrderAndEq(value); }
    inline u32 _acc_sOrderOrEq(u32 value)		{ return _acc_sOrder(_acc_gOrder() | value); }
    inline u32 _acc_sOrder$OrEq(u32 value)			{ CHCKTHIS; return _acc_sOrderOrEq(value); }
    inline u32 _acc_sOrderRShiftEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() >> value); }
    inline u32 _acc_sOrder$RShiftEq(u32 value)			{ CHCKTHIS; return _acc_sOrderRShiftEq(value); }
    inline u32 _acc_sOrderLShiftEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() << value); }
    inline u32 _acc_sOrder$LShiftEq(u32 value)			{ CHCKTHIS; return _acc_sOrderLShiftEq(value); }
    inline s32 _acc_gWidth();
    inline s32 _acc_gWidth$();

    inline s32 _acc_sWidth(s32 value);
    inline s32 _acc_sWidth$(s32 value);
    inline s32 _acc_sWidthpostInc()			{ s32 tmp; _acc_sWidth((tmp = _acc_gWidth())+1); return tmp; }
    inline s32 _acc_sWidth$postInc()			{ CHCKTHIS; return _acc_sWidthpostInc(); }
    inline s32 _acc_sWidthpostDec()			{ s32 tmp; _acc_sWidth((tmp = _acc_gWidth())-1); return tmp; }
    inline s32 _acc_sWidth$postDec()			{ CHCKTHIS; return _acc_sWidthpostDec(); }
    inline s32 _acc_sWidthpreInc()			{ return _acc_sWidth(_acc_gWidth()+1); }
    inline s32 _acc_sWidth$preInc()			{ CHCKTHIS; return _acc_sWidthpreInc(); }
    inline s32 _acc_sWidthpreDec()			{ return _acc_sWidth(_acc_gWidth()-1); }
    inline s32 _acc_sWidth$preDec()			{ CHCKTHIS; return _acc_sWidthpreDec(); }
    inline s32 _acc_sWidthAddEq(s32 value)	{ return _acc_sWidth(_acc_gWidth() + value); }
    inline s32 _acc_sWidth$AddEq(s32 value)			{ CHCKTHIS; return _acc_sWidthAddEq(value); }
    inline s32 _acc_sWidthSubEq(s32 value)	{ return _acc_sWidth(_acc_gWidth() - value); }
    inline s32 _acc_sWidth$SubEq(s32 value)			{ CHCKTHIS; return _acc_sWidthSubEq(value); }
    inline s32 _acc_sWidthMulEq(s32 value)	{ return _acc_sWidth(_acc_gWidth() * value); }
    inline s32 _acc_sWidth$MulEq(s32 value)			{ CHCKTHIS; return _acc_sWidthMulEq(value); }
    inline s32 _acc_sWidthDivEq(s32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sWidth(_acc_gWidth() / value); }
    inline s32 _acc_sWidth$DivEq(s32 value)			{ CHCKTHIS; return _acc_sWidthDivEq(value); }
    inline s32 _acc_sWidthModEq(s32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sWidth(_acc_gWidth() % value); }
    inline s32 _acc_sWidth$ModEq(s32 value)			{ CHCKTHIS; return _acc_sWidthModEq(value); }
    inline s32 _acc_sWidthXorEq(s32 value)	{ return _acc_sWidth(_acc_gWidth() ^ value); }
    inline s32 _acc_sWidth$XorEq(s32 value)			{ CHCKTHIS; return _acc_sWidthXorEq(value); }
    inline s32 _acc_sWidthAndEq(s32 value)	{ return _acc_sWidth(_acc_gWidth() & value); }
    inline s32 _acc_sWidth$AndEq(s32 value)			{ CHCKTHIS; return _acc_sWidthAndEq(value); }
    inline s32 _acc_sWidthOrEq(s32 value)		{ return _acc_sWidth(_acc_gWidth() | value); }
    inline s32 _acc_sWidth$OrEq(s32 value)			{ CHCKTHIS; return _acc_sWidthOrEq(value); }
    inline s32 _acc_sWidthRShiftEq(s32 value)	{ return _acc_sWidth(_acc_gWidth() >> value); }
    inline s32 _acc_sWidth$RShiftEq(s32 value)			{ CHCKTHIS; return _acc_sWidthRShiftEq(value); }
    inline s32 _acc_sWidthLShiftEq(s32 value)	{ return _acc_sWidth(_acc_gWidth() << value); }
    inline s32 _acc_sWidth$LShiftEq(s32 value)			{ CHCKTHIS; return _acc_sWidthLShiftEq(value); }
    inline s32 _acc_gHeight();
    inline s32 _acc_gHeight$();

    inline s32 _acc_sHeight(s32 value);
    inline s32 _acc_sHeight$(s32 value);
    inline s32 _acc_sHeightpostInc()			{ s32 tmp; _acc_sHeight((tmp = _acc_gHeight())+1); return tmp; }
    inline s32 _acc_sHeight$postInc()			{ CHCKTHIS; return _acc_sHeightpostInc(); }
    inline s32 _acc_sHeightpostDec()			{ s32 tmp; _acc_sHeight((tmp = _acc_gHeight())-1); return tmp; }
    inline s32 _acc_sHeight$postDec()			{ CHCKTHIS; return _acc_sHeightpostDec(); }
    inline s32 _acc_sHeightpreInc()			{ return _acc_sHeight(_acc_gHeight()+1); }
    inline s32 _acc_sHeight$preInc()			{ CHCKTHIS; return _acc_sHeightpreInc(); }
    inline s32 _acc_sHeightpreDec()			{ return _acc_sHeight(_acc_gHeight()-1); }
    inline s32 _acc_sHeight$preDec()			{ CHCKTHIS; return _acc_sHeightpreDec(); }
    inline s32 _acc_sHeightAddEq(s32 value)	{ return _acc_sHeight(_acc_gHeight() + value); }
    inline s32 _acc_sHeight$AddEq(s32 value)			{ CHCKTHIS; return _acc_sHeightAddEq(value); }
    inline s32 _acc_sHeightSubEq(s32 value)	{ return _acc_sHeight(_acc_gHeight() - value); }
    inline s32 _acc_sHeight$SubEq(s32 value)			{ CHCKTHIS; return _acc_sHeightSubEq(value); }
    inline s32 _acc_sHeightMulEq(s32 value)	{ return _acc_sHeight(_acc_gHeight() * value); }
    inline s32 _acc_sHeight$MulEq(s32 value)			{ CHCKTHIS; return _acc_sHeightMulEq(value); }
    inline s32 _acc_sHeightDivEq(s32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sHeight(_acc_gHeight() / value); }
    inline s32 _acc_sHeight$DivEq(s32 value)			{ CHCKTHIS; return _acc_sHeightDivEq(value); }
    inline s32 _acc_sHeightModEq(s32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sHeight(_acc_gHeight() % value); }
    inline s32 _acc_sHeight$ModEq(s32 value)			{ CHCKTHIS; return _acc_sHeightModEq(value); }
    inline s32 _acc_sHeightXorEq(s32 value)	{ return _acc_sHeight(_acc_gHeight() ^ value); }
    inline s32 _acc_sHeight$XorEq(s32 value)			{ CHCKTHIS; return _acc_sHeightXorEq(value); }
    inline s32 _acc_sHeightAndEq(s32 value)	{ return _acc_sHeight(_acc_gHeight() & value); }
    inline s32 _acc_sHeight$AndEq(s32 value)			{ CHCKTHIS; return _acc_sHeightAndEq(value); }
    inline s32 _acc_sHeightOrEq(s32 value)		{ return _acc_sHeight(_acc_gHeight() | value); }
    inline s32 _acc_sHeight$OrEq(s32 value)			{ CHCKTHIS; return _acc_sHeightOrEq(value); }
    inline s32 _acc_sHeightRShiftEq(s32 value)	{ return _acc_sHeight(_acc_gHeight() >> value); }
    inline s32 _acc_sHeight$RShiftEq(s32 value)			{ CHCKTHIS; return _acc_sHeightRShiftEq(value); }
    inline s32 _acc_sHeightLShiftEq(s32 value)	{ return _acc_sHeight(_acc_gHeight() << value); }
    inline s32 _acc_sHeight$LShiftEq(s32 value)			{ CHCKTHIS; return _acc_sHeightLShiftEq(value); }
    inline System::String* _acc_gAsset();
    inline System::String* _acc_gAsset$();

    inline System::String* _acc_sAsset(System::String* value);
    inline System::String* _acc_sAsset$(System::String* value);
    static s32* _ext_CKLBUIScale9_create(s32* pParent,u32 order,float x,float y,s32 width,s32 height,s32* asset);
    static s32 _ext_CKLBUIScale9_getWidth(s32* p);
    static void _ext_CKLBUIScale9_setWidth(s32* p,s32 width);
    static s32 _ext_CKLBUIScale9_getHeight(s32* p);
    static void _ext_CKLBUIScale9_setHeight(s32* p,s32 height);
    static u32 _ext_CKLBUIScale9_getOrder(s32* p);
    static void _ext_CKLBUIScale9_setOrder(s32* p,u32 order);
    static s32* _ext_CKLBUIScale9_getAsset(s32* p);
    static bool _ext_CKLBUIScale9_setAsset(s32* p,s32* asset);
    CKLBUIScale9(EnginePrototype::CKLBUITask* parent,u32 order,float x,float y,s32 width,s32 height,System::String* asset);
    CKLBUIScale9();
    void getSize(EnginePrototype::Size& size);
    inline void getSize$(EnginePrototype::Size& size);
    void setSize(EnginePrototype::Size size);
    inline void setSize$(EnginePrototype::Size size);
    void setSize(s32 width,s32 height);
    inline void setSize$(s32 width,s32 height);
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 226;
};
class EnginePrototype::CKLBUIScore : public EnginePrototype::CKLBUITask {

public:
    enum EALIGN {
        ALIGN_RIGHT = 0,
        ALIGN_CENTER = 1,
        ALIGN_LEFT = 2,
        _ForceWORD_EALIGN = 0x7FFFFFFF
    };

    void _ctor_CKLBUIScore();
    static u32 s_classID;
    inline static u32 _ss_classIDDivEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID /= value; }
    inline static u32 _ss_classIDModEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID %= value; }

    inline u32 _acc_gOrder();
    inline u32 _acc_gOrder$();

    inline u32 _acc_sOrder(u32 value);
    inline u32 _acc_sOrder$(u32 value);
    inline u32 _acc_sOrderpostInc()			{ u32 tmp; _acc_sOrder((tmp = _acc_gOrder())+1); return tmp; }
    inline u32 _acc_sOrder$postInc()			{ CHCKTHIS; return _acc_sOrderpostInc(); }
    inline u32 _acc_sOrderpostDec()			{ u32 tmp; _acc_sOrder((tmp = _acc_gOrder())-1); return tmp; }
    inline u32 _acc_sOrder$postDec()			{ CHCKTHIS; return _acc_sOrderpostDec(); }
    inline u32 _acc_sOrderpreInc()			{ return _acc_sOrder(_acc_gOrder()+1); }
    inline u32 _acc_sOrder$preInc()			{ CHCKTHIS; return _acc_sOrderpreInc(); }
    inline u32 _acc_sOrderpreDec()			{ return _acc_sOrder(_acc_gOrder()-1); }
    inline u32 _acc_sOrder$preDec()			{ CHCKTHIS; return _acc_sOrderpreDec(); }
    inline u32 _acc_sOrderAddEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() + value); }
    inline u32 _acc_sOrder$AddEq(u32 value)			{ CHCKTHIS; return _acc_sOrderAddEq(value); }
    inline u32 _acc_sOrderSubEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() - value); }
    inline u32 _acc_sOrder$SubEq(u32 value)			{ CHCKTHIS; return _acc_sOrderSubEq(value); }
    inline u32 _acc_sOrderMulEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() * value); }
    inline u32 _acc_sOrder$MulEq(u32 value)			{ CHCKTHIS; return _acc_sOrderMulEq(value); }
    inline u32 _acc_sOrderDivEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sOrder(_acc_gOrder() / value); }
    inline u32 _acc_sOrder$DivEq(u32 value)			{ CHCKTHIS; return _acc_sOrderDivEq(value); }
    inline u32 _acc_sOrderModEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sOrder(_acc_gOrder() % value); }
    inline u32 _acc_sOrder$ModEq(u32 value)			{ CHCKTHIS; return _acc_sOrderModEq(value); }
    inline u32 _acc_sOrderXorEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() ^ value); }
    inline u32 _acc_sOrder$XorEq(u32 value)			{ CHCKTHIS; return _acc_sOrderXorEq(value); }
    inline u32 _acc_sOrderAndEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() & value); }
    inline u32 _acc_sOrder$AndEq(u32 value)			{ CHCKTHIS; return _acc_sOrderAndEq(value); }
    inline u32 _acc_sOrderOrEq(u32 value)		{ return _acc_sOrder(_acc_gOrder() | value); }
    inline u32 _acc_sOrder$OrEq(u32 value)			{ CHCKTHIS; return _acc_sOrderOrEq(value); }
    inline u32 _acc_sOrderRShiftEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() >> value); }
    inline u32 _acc_sOrder$RShiftEq(u32 value)			{ CHCKTHIS; return _acc_sOrderRShiftEq(value); }
    inline u32 _acc_sOrderLShiftEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() << value); }
    inline u32 _acc_sOrder$LShiftEq(u32 value)			{ CHCKTHIS; return _acc_sOrderLShiftEq(value); }
    inline u32 _acc_gOdoff();
    inline u32 _acc_gOdoff$();

    inline s32 _acc_gStepX();
    inline s32 _acc_gStepX$();

    inline s32 _acc_sStepX(s32 value);
    inline s32 _acc_sStepX$(s32 value);
    inline s32 _acc_sStepXpostInc()			{ s32 tmp; _acc_sStepX((tmp = _acc_gStepX())+1); return tmp; }
    inline s32 _acc_sStepX$postInc()			{ CHCKTHIS; return _acc_sStepXpostInc(); }
    inline s32 _acc_sStepXpostDec()			{ s32 tmp; _acc_sStepX((tmp = _acc_gStepX())-1); return tmp; }
    inline s32 _acc_sStepX$postDec()			{ CHCKTHIS; return _acc_sStepXpostDec(); }
    inline s32 _acc_sStepXpreInc()			{ return _acc_sStepX(_acc_gStepX()+1); }
    inline s32 _acc_sStepX$preInc()			{ CHCKTHIS; return _acc_sStepXpreInc(); }
    inline s32 _acc_sStepXpreDec()			{ return _acc_sStepX(_acc_gStepX()-1); }
    inline s32 _acc_sStepX$preDec()			{ CHCKTHIS; return _acc_sStepXpreDec(); }
    inline s32 _acc_sStepXAddEq(s32 value)	{ return _acc_sStepX(_acc_gStepX() + value); }
    inline s32 _acc_sStepX$AddEq(s32 value)			{ CHCKTHIS; return _acc_sStepXAddEq(value); }
    inline s32 _acc_sStepXSubEq(s32 value)	{ return _acc_sStepX(_acc_gStepX() - value); }
    inline s32 _acc_sStepX$SubEq(s32 value)			{ CHCKTHIS; return _acc_sStepXSubEq(value); }
    inline s32 _acc_sStepXMulEq(s32 value)	{ return _acc_sStepX(_acc_gStepX() * value); }
    inline s32 _acc_sStepX$MulEq(s32 value)			{ CHCKTHIS; return _acc_sStepXMulEq(value); }
    inline s32 _acc_sStepXDivEq(s32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sStepX(_acc_gStepX() / value); }
    inline s32 _acc_sStepX$DivEq(s32 value)			{ CHCKTHIS; return _acc_sStepXDivEq(value); }
    inline s32 _acc_sStepXModEq(s32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sStepX(_acc_gStepX() % value); }
    inline s32 _acc_sStepX$ModEq(s32 value)			{ CHCKTHIS; return _acc_sStepXModEq(value); }
    inline s32 _acc_sStepXXorEq(s32 value)	{ return _acc_sStepX(_acc_gStepX() ^ value); }
    inline s32 _acc_sStepX$XorEq(s32 value)			{ CHCKTHIS; return _acc_sStepXXorEq(value); }
    inline s32 _acc_sStepXAndEq(s32 value)	{ return _acc_sStepX(_acc_gStepX() & value); }
    inline s32 _acc_sStepX$AndEq(s32 value)			{ CHCKTHIS; return _acc_sStepXAndEq(value); }
    inline s32 _acc_sStepXOrEq(s32 value)		{ return _acc_sStepX(_acc_gStepX() | value); }
    inline s32 _acc_sStepX$OrEq(s32 value)			{ CHCKTHIS; return _acc_sStepXOrEq(value); }
    inline s32 _acc_sStepXRShiftEq(s32 value)	{ return _acc_sStepX(_acc_gStepX() >> value); }
    inline s32 _acc_sStepX$RShiftEq(s32 value)			{ CHCKTHIS; return _acc_sStepXRShiftEq(value); }
    inline s32 _acc_sStepXLShiftEq(s32 value)	{ return _acc_sStepX(_acc_gStepX() << value); }
    inline s32 _acc_sStepX$LShiftEq(s32 value)			{ CHCKTHIS; return _acc_sStepXLShiftEq(value); }
    inline s32 _acc_gStepY();
    inline s32 _acc_gStepY$();

    inline s32 _acc_sStepY(s32 value);
    inline s32 _acc_sStepY$(s32 value);
    inline s32 _acc_sStepYpostInc()			{ s32 tmp; _acc_sStepY((tmp = _acc_gStepY())+1); return tmp; }
    inline s32 _acc_sStepY$postInc()			{ CHCKTHIS; return _acc_sStepYpostInc(); }
    inline s32 _acc_sStepYpostDec()			{ s32 tmp; _acc_sStepY((tmp = _acc_gStepY())-1); return tmp; }
    inline s32 _acc_sStepY$postDec()			{ CHCKTHIS; return _acc_sStepYpostDec(); }
    inline s32 _acc_sStepYpreInc()			{ return _acc_sStepY(_acc_gStepY()+1); }
    inline s32 _acc_sStepY$preInc()			{ CHCKTHIS; return _acc_sStepYpreInc(); }
    inline s32 _acc_sStepYpreDec()			{ return _acc_sStepY(_acc_gStepY()-1); }
    inline s32 _acc_sStepY$preDec()			{ CHCKTHIS; return _acc_sStepYpreDec(); }
    inline s32 _acc_sStepYAddEq(s32 value)	{ return _acc_sStepY(_acc_gStepY() + value); }
    inline s32 _acc_sStepY$AddEq(s32 value)			{ CHCKTHIS; return _acc_sStepYAddEq(value); }
    inline s32 _acc_sStepYSubEq(s32 value)	{ return _acc_sStepY(_acc_gStepY() - value); }
    inline s32 _acc_sStepY$SubEq(s32 value)			{ CHCKTHIS; return _acc_sStepYSubEq(value); }
    inline s32 _acc_sStepYMulEq(s32 value)	{ return _acc_sStepY(_acc_gStepY() * value); }
    inline s32 _acc_sStepY$MulEq(s32 value)			{ CHCKTHIS; return _acc_sStepYMulEq(value); }
    inline s32 _acc_sStepYDivEq(s32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sStepY(_acc_gStepY() / value); }
    inline s32 _acc_sStepY$DivEq(s32 value)			{ CHCKTHIS; return _acc_sStepYDivEq(value); }
    inline s32 _acc_sStepYModEq(s32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sStepY(_acc_gStepY() % value); }
    inline s32 _acc_sStepY$ModEq(s32 value)			{ CHCKTHIS; return _acc_sStepYModEq(value); }
    inline s32 _acc_sStepYXorEq(s32 value)	{ return _acc_sStepY(_acc_gStepY() ^ value); }
    inline s32 _acc_sStepY$XorEq(s32 value)			{ CHCKTHIS; return _acc_sStepYXorEq(value); }
    inline s32 _acc_sStepYAndEq(s32 value)	{ return _acc_sStepY(_acc_gStepY() & value); }
    inline s32 _acc_sStepY$AndEq(s32 value)			{ CHCKTHIS; return _acc_sStepYAndEq(value); }
    inline s32 _acc_sStepYOrEq(s32 value)		{ return _acc_sStepY(_acc_gStepY() | value); }
    inline s32 _acc_sStepY$OrEq(s32 value)			{ CHCKTHIS; return _acc_sStepYOrEq(value); }
    inline s32 _acc_sStepYRShiftEq(s32 value)	{ return _acc_sStepY(_acc_gStepY() >> value); }
    inline s32 _acc_sStepY$RShiftEq(s32 value)			{ CHCKTHIS; return _acc_sStepYRShiftEq(value); }
    inline s32 _acc_sStepYLShiftEq(s32 value)	{ return _acc_sStepY(_acc_gStepY() << value); }
    inline s32 _acc_sStepY$LShiftEq(s32 value)			{ CHCKTHIS; return _acc_sStepYLShiftEq(value); }
    inline u32 _acc_gCols();
    inline u32 _acc_gCols$();

    inline u32 _acc_sCols(u32 value);
    inline u32 _acc_sCols$(u32 value);
    inline u32 _acc_sColspostInc()			{ u32 tmp; _acc_sCols((tmp = _acc_gCols())+1); return tmp; }
    inline u32 _acc_sCols$postInc()			{ CHCKTHIS; return _acc_sColspostInc(); }
    inline u32 _acc_sColspostDec()			{ u32 tmp; _acc_sCols((tmp = _acc_gCols())-1); return tmp; }
    inline u32 _acc_sCols$postDec()			{ CHCKTHIS; return _acc_sColspostDec(); }
    inline u32 _acc_sColspreInc()			{ return _acc_sCols(_acc_gCols()+1); }
    inline u32 _acc_sCols$preInc()			{ CHCKTHIS; return _acc_sColspreInc(); }
    inline u32 _acc_sColspreDec()			{ return _acc_sCols(_acc_gCols()-1); }
    inline u32 _acc_sCols$preDec()			{ CHCKTHIS; return _acc_sColspreDec(); }
    inline u32 _acc_sColsAddEq(u32 value)	{ return _acc_sCols(_acc_gCols() + value); }
    inline u32 _acc_sCols$AddEq(u32 value)			{ CHCKTHIS; return _acc_sColsAddEq(value); }
    inline u32 _acc_sColsSubEq(u32 value)	{ return _acc_sCols(_acc_gCols() - value); }
    inline u32 _acc_sCols$SubEq(u32 value)			{ CHCKTHIS; return _acc_sColsSubEq(value); }
    inline u32 _acc_sColsMulEq(u32 value)	{ return _acc_sCols(_acc_gCols() * value); }
    inline u32 _acc_sCols$MulEq(u32 value)			{ CHCKTHIS; return _acc_sColsMulEq(value); }
    inline u32 _acc_sColsDivEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sCols(_acc_gCols() / value); }
    inline u32 _acc_sCols$DivEq(u32 value)			{ CHCKTHIS; return _acc_sColsDivEq(value); }
    inline u32 _acc_sColsModEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sCols(_acc_gCols() % value); }
    inline u32 _acc_sCols$ModEq(u32 value)			{ CHCKTHIS; return _acc_sColsModEq(value); }
    inline u32 _acc_sColsXorEq(u32 value)	{ return _acc_sCols(_acc_gCols() ^ value); }
    inline u32 _acc_sCols$XorEq(u32 value)			{ CHCKTHIS; return _acc_sColsXorEq(value); }
    inline u32 _acc_sColsAndEq(u32 value)	{ return _acc_sCols(_acc_gCols() & value); }
    inline u32 _acc_sCols$AndEq(u32 value)			{ CHCKTHIS; return _acc_sColsAndEq(value); }
    inline u32 _acc_sColsOrEq(u32 value)		{ return _acc_sCols(_acc_gCols() | value); }
    inline u32 _acc_sCols$OrEq(u32 value)			{ CHCKTHIS; return _acc_sColsOrEq(value); }
    inline u32 _acc_sColsRShiftEq(u32 value)	{ return _acc_sCols(_acc_gCols() >> value); }
    inline u32 _acc_sCols$RShiftEq(u32 value)			{ CHCKTHIS; return _acc_sColsRShiftEq(value); }
    inline u32 _acc_sColsLShiftEq(u32 value)	{ return _acc_sCols(_acc_gCols() << value); }
    inline u32 _acc_sCols$LShiftEq(u32 value)			{ CHCKTHIS; return _acc_sColsLShiftEq(value); }
    inline bool _acc_gFillZero();
    inline bool _acc_gFillZero$();

    inline bool _acc_sFillZero(bool value);
    inline bool _acc_sFillZero$(bool value);
    inline bool _acc_gIsAnim();
    inline bool _acc_gIsAnim$();

    inline u32 _acc_gValue();
    inline u32 _acc_gValue$();

    inline u32 _acc_sValue(u32 value);
    inline u32 _acc_sValue$(u32 value);
    inline u32 _acc_sValuepostInc()			{ u32 tmp; _acc_sValue((tmp = _acc_gValue())+1); return tmp; }
    inline u32 _acc_sValue$postInc()			{ CHCKTHIS; return _acc_sValuepostInc(); }
    inline u32 _acc_sValuepostDec()			{ u32 tmp; _acc_sValue((tmp = _acc_gValue())-1); return tmp; }
    inline u32 _acc_sValue$postDec()			{ CHCKTHIS; return _acc_sValuepostDec(); }
    inline u32 _acc_sValuepreInc()			{ return _acc_sValue(_acc_gValue()+1); }
    inline u32 _acc_sValue$preInc()			{ CHCKTHIS; return _acc_sValuepreInc(); }
    inline u32 _acc_sValuepreDec()			{ return _acc_sValue(_acc_gValue()-1); }
    inline u32 _acc_sValue$preDec()			{ CHCKTHIS; return _acc_sValuepreDec(); }
    inline u32 _acc_sValueAddEq(u32 value)	{ return _acc_sValue(_acc_gValue() + value); }
    inline u32 _acc_sValue$AddEq(u32 value)			{ CHCKTHIS; return _acc_sValueAddEq(value); }
    inline u32 _acc_sValueSubEq(u32 value)	{ return _acc_sValue(_acc_gValue() - value); }
    inline u32 _acc_sValue$SubEq(u32 value)			{ CHCKTHIS; return _acc_sValueSubEq(value); }
    inline u32 _acc_sValueMulEq(u32 value)	{ return _acc_sValue(_acc_gValue() * value); }
    inline u32 _acc_sValue$MulEq(u32 value)			{ CHCKTHIS; return _acc_sValueMulEq(value); }
    inline u32 _acc_sValueDivEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sValue(_acc_gValue() / value); }
    inline u32 _acc_sValue$DivEq(u32 value)			{ CHCKTHIS; return _acc_sValueDivEq(value); }
    inline u32 _acc_sValueModEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sValue(_acc_gValue() % value); }
    inline u32 _acc_sValue$ModEq(u32 value)			{ CHCKTHIS; return _acc_sValueModEq(value); }
    inline u32 _acc_sValueXorEq(u32 value)	{ return _acc_sValue(_acc_gValue() ^ value); }
    inline u32 _acc_sValue$XorEq(u32 value)			{ CHCKTHIS; return _acc_sValueXorEq(value); }
    inline u32 _acc_sValueAndEq(u32 value)	{ return _acc_sValue(_acc_gValue() & value); }
    inline u32 _acc_sValue$AndEq(u32 value)			{ CHCKTHIS; return _acc_sValueAndEq(value); }
    inline u32 _acc_sValueOrEq(u32 value)		{ return _acc_sValue(_acc_gValue() | value); }
    inline u32 _acc_sValue$OrEq(u32 value)			{ CHCKTHIS; return _acc_sValueOrEq(value); }
    inline u32 _acc_sValueRShiftEq(u32 value)	{ return _acc_sValue(_acc_gValue() >> value); }
    inline u32 _acc_sValue$RShiftEq(u32 value)			{ CHCKTHIS; return _acc_sValueRShiftEq(value); }
    inline u32 _acc_sValueLShiftEq(u32 value)	{ return _acc_sValue(_acc_gValue() << value); }
    inline u32 _acc_sValue$LShiftEq(u32 value)			{ CHCKTHIS; return _acc_sValueLShiftEq(value); }
    inline s32 _acc_gAlign();
    inline s32 _acc_gAlign$();

    inline s32 _acc_sAlign(s32 value);
    inline s32 _acc_sAlign$(s32 value);
    inline s32 _acc_sAlignpostInc()			{ s32 tmp = _acc_gAlign(); _acc_sAlign((s32)((s32)tmp + 1)); return tmp; }
    inline s32 _acc_sAlign$postInc()			{ CHCKTHIS; return _acc_sAlignpostInc(); }
    inline s32 _acc_sAlignpostDec()			{ s32 tmp = _acc_gAlign(); _acc_sAlign((s32)((s32)tmp - 1)); return tmp; }
    inline s32 _acc_sAlign$postDec()			{ CHCKTHIS; return _acc_sAlignpostDec(); }
    inline s32 _acc_sAlignpreInc()			{ return _acc_sAlign((s32)((s32)_acc_gAlign()+1)); }
    inline s32 _acc_sAlign$preInc()			{ CHCKTHIS; return _acc_sAlignpreInc(); }
    inline s32 _acc_sAlignpreDec()			{ return _acc_sAlign((s32)((s32)_acc_gAlign()-1)); }
    inline s32 _acc_sAlign$preDec()			{ CHCKTHIS; return _acc_sAlignpreDec(); }
    inline s32 _acc_sAlignAddEq(s32 value)	{ return _acc_sAlign((s32)((s32)_acc_gAlign() + value)); }
    inline s32 _acc_sAlign$AddEq(s32 value)			{ CHCKTHIS; return _acc_sAlignAddEq(value); }
    inline s32 _acc_sAlignSubEq(s32 value)	{ return _acc_sAlign((s32)((s32)_acc_gAlign() - value)); }
    inline s32 _acc_sAlign$SubEq(s32 value)			{ CHCKTHIS; return _acc_sAlignSubEq(value); }
    inline bool _acc_gCountClip();
    inline bool _acc_gCountClip$();

    inline bool _acc_sCountClip(bool value);
    inline bool _acc_sCountClip$(bool value);
    inline System::Array<System::String*>* _acc_gTextures();
    inline System::Array<System::String*>* _acc_gTextures$();

    static s32* _ext_CKLBUIScore_create(s32* pParent,u32 order,s32 orderOffset,float x,float y,System::Array<s32*>* texTable,float stepX,float stepY,s32 column,bool fillZero,bool animFlags,u32 align,bool countClip);
    static u32 _ext_CKLBUIScore_getValue(s32* p);
    static void _ext_CKLBUIScore_setValue(s32* p,u32 value);
    static u32 _ext_CKLBUIScore_getOrder(s32* p);
    static void _ext_CKLBUIScore_setOrder(s32* p,u32 value);
    static u32 _ext_CKLBUIScore_getOrderOffset(s32* p);
    static s32 _ext_CKLBUIScore_getStepX(s32* p);
    static void _ext_CKLBUIScore_setStepX(s32* p,s32 value);
    static s32 _ext_CKLBUIScore_getStepY(s32* p);
    static void _ext_CKLBUIScore_setStepY(s32* p,s32 value);
    static u32 _ext_CKLBUIScore_getColumn(s32* p);
    static void _ext_CKLBUIScore_setColumn(s32* p,u32 value);
    static bool _ext_CKLBUIScore_getFillZero(s32* p);
    static void _ext_CKLBUIScore_setFillZero(s32* p,bool value);
    static bool _ext_CKLBUIScore_getAnim(s32* p);
    static s32 _ext_CKLBUIScore_getAlign(s32* p);
    static void _ext_CKLBUIScore_setAlign(s32* p,s32 align);
    static s32* _ext_CKLBUIScore_getTextures(s32* p);
    static bool _ext_CKLBUIScore_getCountClip(s32* p);
    static void _ext_CKLBUIScore_setCountClip(s32* p,bool value);
    static void _ext_CKLBUIScore_setEnterAnimation(s32* p,u32 milliSecondsPlayTime,s32 timeShift,u32 type,u32 affected,System::Array<float>* arrayParam);
    static void _ext_CKLBUIScore_setExitAnimation(s32* p,u32 milliSecondsPlayTime,s32 timeShift,u32 type,u32 affected,System::Array<float>* arrayParam);
    CKLBUIScore(EnginePrototype::CKLBUITask* parent,u32 order,s32 orderOffset,float x,float y,System::Array<System::String*>* textureTable,float stepX,float stepY,s32 column,bool fillZeroFlag,bool animationFlag,s32 align,bool countClip);
    CKLBUIScore();
    void reset();
    inline void reset$();
    void enterAnim(EnginePrototype::AnimationInfo* animation,u32 msPlayTime,s32 timeShift);
    inline void enterAnim$(EnginePrototype::AnimationInfo* animation,u32 msPlayTime,s32 timeShift);
    void exitAnim(EnginePrototype::AnimationInfo* animation,u32 msPlayTime,s32 timeShift);
    inline void exitAnim$(EnginePrototype::AnimationInfo* animation,u32 msPlayTime,s32 timeShift);
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 229;
};
class EnginePrototype::CKLBUIScrollBar : public EnginePrototype::CKLBUITask {
friend class ScrollBarCallBack_inner46;

public:
    enum ETYPE {
        SCROLLBAR_DRAG = 0,
        SCROLLBAR_RELEASE = 1,
        _ForceWORD_ETYPE = 0x7FFFFFFF
    };

    void _ctor_CKLBUIScrollBar();
    static u32 s_classID;
    inline static u32 _ss_classIDDivEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID /= value; }
    inline static u32 _ss_classIDModEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID %= value; }

    EnginePrototype::_Delegate_Base_ScrollBarCallBack_inner46* m_callback;
    inline EnginePrototype::_Delegate_Base_ScrollBarCallBack_inner46*& _gm_callback$() { CHCKTHIS; return m_callback; }
    inline EnginePrototype::_Delegate_Base_ScrollBarCallBack_inner46* _sm_callback(EnginePrototype::_Delegate_Base_ScrollBarCallBack_inner46* _$value);
    inline EnginePrototype::_Delegate_Base_ScrollBarCallBack_inner46* _sm_callback$(EnginePrototype::_Delegate_Base_ScrollBarCallBack_inner46* _$value);

    inline u32 _acc_gOrder();
    inline u32 _acc_gOrder$();

    inline u32 _acc_sOrder(u32 value);
    inline u32 _acc_sOrder$(u32 value);
    inline u32 _acc_sOrderpostInc()			{ u32 tmp; _acc_sOrder((tmp = _acc_gOrder())+1); return tmp; }
    inline u32 _acc_sOrder$postInc()			{ CHCKTHIS; return _acc_sOrderpostInc(); }
    inline u32 _acc_sOrderpostDec()			{ u32 tmp; _acc_sOrder((tmp = _acc_gOrder())-1); return tmp; }
    inline u32 _acc_sOrder$postDec()			{ CHCKTHIS; return _acc_sOrderpostDec(); }
    inline u32 _acc_sOrderpreInc()			{ return _acc_sOrder(_acc_gOrder()+1); }
    inline u32 _acc_sOrder$preInc()			{ CHCKTHIS; return _acc_sOrderpreInc(); }
    inline u32 _acc_sOrderpreDec()			{ return _acc_sOrder(_acc_gOrder()-1); }
    inline u32 _acc_sOrder$preDec()			{ CHCKTHIS; return _acc_sOrderpreDec(); }
    inline u32 _acc_sOrderAddEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() + value); }
    inline u32 _acc_sOrder$AddEq(u32 value)			{ CHCKTHIS; return _acc_sOrderAddEq(value); }
    inline u32 _acc_sOrderSubEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() - value); }
    inline u32 _acc_sOrder$SubEq(u32 value)			{ CHCKTHIS; return _acc_sOrderSubEq(value); }
    inline u32 _acc_sOrderMulEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() * value); }
    inline u32 _acc_sOrder$MulEq(u32 value)			{ CHCKTHIS; return _acc_sOrderMulEq(value); }
    inline u32 _acc_sOrderDivEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sOrder(_acc_gOrder() / value); }
    inline u32 _acc_sOrder$DivEq(u32 value)			{ CHCKTHIS; return _acc_sOrderDivEq(value); }
    inline u32 _acc_sOrderModEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sOrder(_acc_gOrder() % value); }
    inline u32 _acc_sOrder$ModEq(u32 value)			{ CHCKTHIS; return _acc_sOrderModEq(value); }
    inline u32 _acc_sOrderXorEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() ^ value); }
    inline u32 _acc_sOrder$XorEq(u32 value)			{ CHCKTHIS; return _acc_sOrderXorEq(value); }
    inline u32 _acc_sOrderAndEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() & value); }
    inline u32 _acc_sOrder$AndEq(u32 value)			{ CHCKTHIS; return _acc_sOrderAndEq(value); }
    inline u32 _acc_sOrderOrEq(u32 value)		{ return _acc_sOrder(_acc_gOrder() | value); }
    inline u32 _acc_sOrder$OrEq(u32 value)			{ CHCKTHIS; return _acc_sOrderOrEq(value); }
    inline u32 _acc_sOrderRShiftEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() >> value); }
    inline u32 _acc_sOrder$RShiftEq(u32 value)			{ CHCKTHIS; return _acc_sOrderRShiftEq(value); }
    inline u32 _acc_sOrderLShiftEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() << value); }
    inline u32 _acc_sOrder$LShiftEq(u32 value)			{ CHCKTHIS; return _acc_sOrderLShiftEq(value); }
    inline s32 _acc_gWidth();
    inline s32 _acc_gWidth$();

    inline s32 _acc_sWidth(s32 value);
    inline s32 _acc_sWidth$(s32 value);
    inline s32 _acc_sWidthpostInc()			{ s32 tmp; _acc_sWidth((tmp = _acc_gWidth())+1); return tmp; }
    inline s32 _acc_sWidth$postInc()			{ CHCKTHIS; return _acc_sWidthpostInc(); }
    inline s32 _acc_sWidthpostDec()			{ s32 tmp; _acc_sWidth((tmp = _acc_gWidth())-1); return tmp; }
    inline s32 _acc_sWidth$postDec()			{ CHCKTHIS; return _acc_sWidthpostDec(); }
    inline s32 _acc_sWidthpreInc()			{ return _acc_sWidth(_acc_gWidth()+1); }
    inline s32 _acc_sWidth$preInc()			{ CHCKTHIS; return _acc_sWidthpreInc(); }
    inline s32 _acc_sWidthpreDec()			{ return _acc_sWidth(_acc_gWidth()-1); }
    inline s32 _acc_sWidth$preDec()			{ CHCKTHIS; return _acc_sWidthpreDec(); }
    inline s32 _acc_sWidthAddEq(s32 value)	{ return _acc_sWidth(_acc_gWidth() + value); }
    inline s32 _acc_sWidth$AddEq(s32 value)			{ CHCKTHIS; return _acc_sWidthAddEq(value); }
    inline s32 _acc_sWidthSubEq(s32 value)	{ return _acc_sWidth(_acc_gWidth() - value); }
    inline s32 _acc_sWidth$SubEq(s32 value)			{ CHCKTHIS; return _acc_sWidthSubEq(value); }
    inline s32 _acc_sWidthMulEq(s32 value)	{ return _acc_sWidth(_acc_gWidth() * value); }
    inline s32 _acc_sWidth$MulEq(s32 value)			{ CHCKTHIS; return _acc_sWidthMulEq(value); }
    inline s32 _acc_sWidthDivEq(s32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sWidth(_acc_gWidth() / value); }
    inline s32 _acc_sWidth$DivEq(s32 value)			{ CHCKTHIS; return _acc_sWidthDivEq(value); }
    inline s32 _acc_sWidthModEq(s32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sWidth(_acc_gWidth() % value); }
    inline s32 _acc_sWidth$ModEq(s32 value)			{ CHCKTHIS; return _acc_sWidthModEq(value); }
    inline s32 _acc_sWidthXorEq(s32 value)	{ return _acc_sWidth(_acc_gWidth() ^ value); }
    inline s32 _acc_sWidth$XorEq(s32 value)			{ CHCKTHIS; return _acc_sWidthXorEq(value); }
    inline s32 _acc_sWidthAndEq(s32 value)	{ return _acc_sWidth(_acc_gWidth() & value); }
    inline s32 _acc_sWidth$AndEq(s32 value)			{ CHCKTHIS; return _acc_sWidthAndEq(value); }
    inline s32 _acc_sWidthOrEq(s32 value)		{ return _acc_sWidth(_acc_gWidth() | value); }
    inline s32 _acc_sWidth$OrEq(s32 value)			{ CHCKTHIS; return _acc_sWidthOrEq(value); }
    inline s32 _acc_sWidthRShiftEq(s32 value)	{ return _acc_sWidth(_acc_gWidth() >> value); }
    inline s32 _acc_sWidth$RShiftEq(s32 value)			{ CHCKTHIS; return _acc_sWidthRShiftEq(value); }
    inline s32 _acc_sWidthLShiftEq(s32 value)	{ return _acc_sWidth(_acc_gWidth() << value); }
    inline s32 _acc_sWidth$LShiftEq(s32 value)			{ CHCKTHIS; return _acc_sWidthLShiftEq(value); }
    inline s32 _acc_gHeight();
    inline s32 _acc_gHeight$();

    inline s32 _acc_sHeight(s32 value);
    inline s32 _acc_sHeight$(s32 value);
    inline s32 _acc_sHeightpostInc()			{ s32 tmp; _acc_sHeight((tmp = _acc_gHeight())+1); return tmp; }
    inline s32 _acc_sHeight$postInc()			{ CHCKTHIS; return _acc_sHeightpostInc(); }
    inline s32 _acc_sHeightpostDec()			{ s32 tmp; _acc_sHeight((tmp = _acc_gHeight())-1); return tmp; }
    inline s32 _acc_sHeight$postDec()			{ CHCKTHIS; return _acc_sHeightpostDec(); }
    inline s32 _acc_sHeightpreInc()			{ return _acc_sHeight(_acc_gHeight()+1); }
    inline s32 _acc_sHeight$preInc()			{ CHCKTHIS; return _acc_sHeightpreInc(); }
    inline s32 _acc_sHeightpreDec()			{ return _acc_sHeight(_acc_gHeight()-1); }
    inline s32 _acc_sHeight$preDec()			{ CHCKTHIS; return _acc_sHeightpreDec(); }
    inline s32 _acc_sHeightAddEq(s32 value)	{ return _acc_sHeight(_acc_gHeight() + value); }
    inline s32 _acc_sHeight$AddEq(s32 value)			{ CHCKTHIS; return _acc_sHeightAddEq(value); }
    inline s32 _acc_sHeightSubEq(s32 value)	{ return _acc_sHeight(_acc_gHeight() - value); }
    inline s32 _acc_sHeight$SubEq(s32 value)			{ CHCKTHIS; return _acc_sHeightSubEq(value); }
    inline s32 _acc_sHeightMulEq(s32 value)	{ return _acc_sHeight(_acc_gHeight() * value); }
    inline s32 _acc_sHeight$MulEq(s32 value)			{ CHCKTHIS; return _acc_sHeightMulEq(value); }
    inline s32 _acc_sHeightDivEq(s32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sHeight(_acc_gHeight() / value); }
    inline s32 _acc_sHeight$DivEq(s32 value)			{ CHCKTHIS; return _acc_sHeightDivEq(value); }
    inline s32 _acc_sHeightModEq(s32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sHeight(_acc_gHeight() % value); }
    inline s32 _acc_sHeight$ModEq(s32 value)			{ CHCKTHIS; return _acc_sHeightModEq(value); }
    inline s32 _acc_sHeightXorEq(s32 value)	{ return _acc_sHeight(_acc_gHeight() ^ value); }
    inline s32 _acc_sHeight$XorEq(s32 value)			{ CHCKTHIS; return _acc_sHeightXorEq(value); }
    inline s32 _acc_sHeightAndEq(s32 value)	{ return _acc_sHeight(_acc_gHeight() & value); }
    inline s32 _acc_sHeight$AndEq(s32 value)			{ CHCKTHIS; return _acc_sHeightAndEq(value); }
    inline s32 _acc_sHeightOrEq(s32 value)		{ return _acc_sHeight(_acc_gHeight() | value); }
    inline s32 _acc_sHeight$OrEq(s32 value)			{ CHCKTHIS; return _acc_sHeightOrEq(value); }
    inline s32 _acc_sHeightRShiftEq(s32 value)	{ return _acc_sHeight(_acc_gHeight() >> value); }
    inline s32 _acc_sHeight$RShiftEq(s32 value)			{ CHCKTHIS; return _acc_sHeightRShiftEq(value); }
    inline s32 _acc_sHeightLShiftEq(s32 value)	{ return _acc_sHeight(_acc_gHeight() << value); }
    inline s32 _acc_sHeight$LShiftEq(s32 value)			{ CHCKTHIS; return _acc_sHeightLShiftEq(value); }
    inline s32 _acc_gStart();
    inline s32 _acc_gStart$();

    inline s32 _acc_sStart(s32 value);
    inline s32 _acc_sStart$(s32 value);
    inline s32 _acc_sStartpostInc()			{ s32 tmp; _acc_sStart((tmp = _acc_gStart())+1); return tmp; }
    inline s32 _acc_sStart$postInc()			{ CHCKTHIS; return _acc_sStartpostInc(); }
    inline s32 _acc_sStartpostDec()			{ s32 tmp; _acc_sStart((tmp = _acc_gStart())-1); return tmp; }
    inline s32 _acc_sStart$postDec()			{ CHCKTHIS; return _acc_sStartpostDec(); }
    inline s32 _acc_sStartpreInc()			{ return _acc_sStart(_acc_gStart()+1); }
    inline s32 _acc_sStart$preInc()			{ CHCKTHIS; return _acc_sStartpreInc(); }
    inline s32 _acc_sStartpreDec()			{ return _acc_sStart(_acc_gStart()-1); }
    inline s32 _acc_sStart$preDec()			{ CHCKTHIS; return _acc_sStartpreDec(); }
    inline s32 _acc_sStartAddEq(s32 value)	{ return _acc_sStart(_acc_gStart() + value); }
    inline s32 _acc_sStart$AddEq(s32 value)			{ CHCKTHIS; return _acc_sStartAddEq(value); }
    inline s32 _acc_sStartSubEq(s32 value)	{ return _acc_sStart(_acc_gStart() - value); }
    inline s32 _acc_sStart$SubEq(s32 value)			{ CHCKTHIS; return _acc_sStartSubEq(value); }
    inline s32 _acc_sStartMulEq(s32 value)	{ return _acc_sStart(_acc_gStart() * value); }
    inline s32 _acc_sStart$MulEq(s32 value)			{ CHCKTHIS; return _acc_sStartMulEq(value); }
    inline s32 _acc_sStartDivEq(s32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sStart(_acc_gStart() / value); }
    inline s32 _acc_sStart$DivEq(s32 value)			{ CHCKTHIS; return _acc_sStartDivEq(value); }
    inline s32 _acc_sStartModEq(s32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sStart(_acc_gStart() % value); }
    inline s32 _acc_sStart$ModEq(s32 value)			{ CHCKTHIS; return _acc_sStartModEq(value); }
    inline s32 _acc_sStartXorEq(s32 value)	{ return _acc_sStart(_acc_gStart() ^ value); }
    inline s32 _acc_sStart$XorEq(s32 value)			{ CHCKTHIS; return _acc_sStartXorEq(value); }
    inline s32 _acc_sStartAndEq(s32 value)	{ return _acc_sStart(_acc_gStart() & value); }
    inline s32 _acc_sStart$AndEq(s32 value)			{ CHCKTHIS; return _acc_sStartAndEq(value); }
    inline s32 _acc_sStartOrEq(s32 value)		{ return _acc_sStart(_acc_gStart() | value); }
    inline s32 _acc_sStart$OrEq(s32 value)			{ CHCKTHIS; return _acc_sStartOrEq(value); }
    inline s32 _acc_sStartRShiftEq(s32 value)	{ return _acc_sStart(_acc_gStart() >> value); }
    inline s32 _acc_sStart$RShiftEq(s32 value)			{ CHCKTHIS; return _acc_sStartRShiftEq(value); }
    inline s32 _acc_sStartLShiftEq(s32 value)	{ return _acc_sStart(_acc_gStart() << value); }
    inline s32 _acc_sStart$LShiftEq(s32 value)			{ CHCKTHIS; return _acc_sStartLShiftEq(value); }
    inline s32 _acc_gEnd();
    inline s32 _acc_gEnd$();

    inline s32 _acc_sEnd(s32 value);
    inline s32 _acc_sEnd$(s32 value);
    inline s32 _acc_sEndpostInc()			{ s32 tmp; _acc_sEnd((tmp = _acc_gEnd())+1); return tmp; }
    inline s32 _acc_sEnd$postInc()			{ CHCKTHIS; return _acc_sEndpostInc(); }
    inline s32 _acc_sEndpostDec()			{ s32 tmp; _acc_sEnd((tmp = _acc_gEnd())-1); return tmp; }
    inline s32 _acc_sEnd$postDec()			{ CHCKTHIS; return _acc_sEndpostDec(); }
    inline s32 _acc_sEndpreInc()			{ return _acc_sEnd(_acc_gEnd()+1); }
    inline s32 _acc_sEnd$preInc()			{ CHCKTHIS; return _acc_sEndpreInc(); }
    inline s32 _acc_sEndpreDec()			{ return _acc_sEnd(_acc_gEnd()-1); }
    inline s32 _acc_sEnd$preDec()			{ CHCKTHIS; return _acc_sEndpreDec(); }
    inline s32 _acc_sEndAddEq(s32 value)	{ return _acc_sEnd(_acc_gEnd() + value); }
    inline s32 _acc_sEnd$AddEq(s32 value)			{ CHCKTHIS; return _acc_sEndAddEq(value); }
    inline s32 _acc_sEndSubEq(s32 value)	{ return _acc_sEnd(_acc_gEnd() - value); }
    inline s32 _acc_sEnd$SubEq(s32 value)			{ CHCKTHIS; return _acc_sEndSubEq(value); }
    inline s32 _acc_sEndMulEq(s32 value)	{ return _acc_sEnd(_acc_gEnd() * value); }
    inline s32 _acc_sEnd$MulEq(s32 value)			{ CHCKTHIS; return _acc_sEndMulEq(value); }
    inline s32 _acc_sEndDivEq(s32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sEnd(_acc_gEnd() / value); }
    inline s32 _acc_sEnd$DivEq(s32 value)			{ CHCKTHIS; return _acc_sEndDivEq(value); }
    inline s32 _acc_sEndModEq(s32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sEnd(_acc_gEnd() % value); }
    inline s32 _acc_sEnd$ModEq(s32 value)			{ CHCKTHIS; return _acc_sEndModEq(value); }
    inline s32 _acc_sEndXorEq(s32 value)	{ return _acc_sEnd(_acc_gEnd() ^ value); }
    inline s32 _acc_sEnd$XorEq(s32 value)			{ CHCKTHIS; return _acc_sEndXorEq(value); }
    inline s32 _acc_sEndAndEq(s32 value)	{ return _acc_sEnd(_acc_gEnd() & value); }
    inline s32 _acc_sEnd$AndEq(s32 value)			{ CHCKTHIS; return _acc_sEndAndEq(value); }
    inline s32 _acc_sEndOrEq(s32 value)		{ return _acc_sEnd(_acc_gEnd() | value); }
    inline s32 _acc_sEnd$OrEq(s32 value)			{ CHCKTHIS; return _acc_sEndOrEq(value); }
    inline s32 _acc_sEndRShiftEq(s32 value)	{ return _acc_sEnd(_acc_gEnd() >> value); }
    inline s32 _acc_sEnd$RShiftEq(s32 value)			{ CHCKTHIS; return _acc_sEndRShiftEq(value); }
    inline s32 _acc_sEndLShiftEq(s32 value)	{ return _acc_sEnd(_acc_gEnd() << value); }
    inline s32 _acc_sEnd$LShiftEq(s32 value)			{ CHCKTHIS; return _acc_sEndLShiftEq(value); }
    inline s32 _acc_gPos();
    inline s32 _acc_gPos$();

    inline s32 _acc_sPos(s32 value);
    inline s32 _acc_sPos$(s32 value);
    inline s32 _acc_sPospostInc()			{ s32 tmp; _acc_sPos((tmp = _acc_gPos())+1); return tmp; }
    inline s32 _acc_sPos$postInc()			{ CHCKTHIS; return _acc_sPospostInc(); }
    inline s32 _acc_sPospostDec()			{ s32 tmp; _acc_sPos((tmp = _acc_gPos())-1); return tmp; }
    inline s32 _acc_sPos$postDec()			{ CHCKTHIS; return _acc_sPospostDec(); }
    inline s32 _acc_sPospreInc()			{ return _acc_sPos(_acc_gPos()+1); }
    inline s32 _acc_sPos$preInc()			{ CHCKTHIS; return _acc_sPospreInc(); }
    inline s32 _acc_sPospreDec()			{ return _acc_sPos(_acc_gPos()-1); }
    inline s32 _acc_sPos$preDec()			{ CHCKTHIS; return _acc_sPospreDec(); }
    inline s32 _acc_sPosAddEq(s32 value)	{ return _acc_sPos(_acc_gPos() + value); }
    inline s32 _acc_sPos$AddEq(s32 value)			{ CHCKTHIS; return _acc_sPosAddEq(value); }
    inline s32 _acc_sPosSubEq(s32 value)	{ return _acc_sPos(_acc_gPos() - value); }
    inline s32 _acc_sPos$SubEq(s32 value)			{ CHCKTHIS; return _acc_sPosSubEq(value); }
    inline s32 _acc_sPosMulEq(s32 value)	{ return _acc_sPos(_acc_gPos() * value); }
    inline s32 _acc_sPos$MulEq(s32 value)			{ CHCKTHIS; return _acc_sPosMulEq(value); }
    inline s32 _acc_sPosDivEq(s32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sPos(_acc_gPos() / value); }
    inline s32 _acc_sPos$DivEq(s32 value)			{ CHCKTHIS; return _acc_sPosDivEq(value); }
    inline s32 _acc_sPosModEq(s32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sPos(_acc_gPos() % value); }
    inline s32 _acc_sPos$ModEq(s32 value)			{ CHCKTHIS; return _acc_sPosModEq(value); }
    inline s32 _acc_sPosXorEq(s32 value)	{ return _acc_sPos(_acc_gPos() ^ value); }
    inline s32 _acc_sPos$XorEq(s32 value)			{ CHCKTHIS; return _acc_sPosXorEq(value); }
    inline s32 _acc_sPosAndEq(s32 value)	{ return _acc_sPos(_acc_gPos() & value); }
    inline s32 _acc_sPos$AndEq(s32 value)			{ CHCKTHIS; return _acc_sPosAndEq(value); }
    inline s32 _acc_sPosOrEq(s32 value)		{ return _acc_sPos(_acc_gPos() | value); }
    inline s32 _acc_sPos$OrEq(s32 value)			{ CHCKTHIS; return _acc_sPosOrEq(value); }
    inline s32 _acc_sPosRShiftEq(s32 value)	{ return _acc_sPos(_acc_gPos() >> value); }
    inline s32 _acc_sPos$RShiftEq(s32 value)			{ CHCKTHIS; return _acc_sPosRShiftEq(value); }
    inline s32 _acc_sPosLShiftEq(s32 value)	{ return _acc_sPos(_acc_gPos() << value); }
    inline s32 _acc_sPos$LShiftEq(s32 value)			{ CHCKTHIS; return _acc_sPosLShiftEq(value); }
    inline System::String* _acc_gImg();
    inline System::String* _acc_gImg$();

    inline s32 _acc_gSliderSize();
    inline s32 _acc_gSliderSize$();

    inline s32 _acc_sSliderSize(s32 value);
    inline s32 _acc_sSliderSize$(s32 value);
    inline s32 _acc_sSliderSizepostInc()			{ s32 tmp; _acc_sSliderSize((tmp = _acc_gSliderSize())+1); return tmp; }
    inline s32 _acc_sSliderSize$postInc()			{ CHCKTHIS; return _acc_sSliderSizepostInc(); }
    inline s32 _acc_sSliderSizepostDec()			{ s32 tmp; _acc_sSliderSize((tmp = _acc_gSliderSize())-1); return tmp; }
    inline s32 _acc_sSliderSize$postDec()			{ CHCKTHIS; return _acc_sSliderSizepostDec(); }
    inline s32 _acc_sSliderSizepreInc()			{ return _acc_sSliderSize(_acc_gSliderSize()+1); }
    inline s32 _acc_sSliderSize$preInc()			{ CHCKTHIS; return _acc_sSliderSizepreInc(); }
    inline s32 _acc_sSliderSizepreDec()			{ return _acc_sSliderSize(_acc_gSliderSize()-1); }
    inline s32 _acc_sSliderSize$preDec()			{ CHCKTHIS; return _acc_sSliderSizepreDec(); }
    inline s32 _acc_sSliderSizeAddEq(s32 value)	{ return _acc_sSliderSize(_acc_gSliderSize() + value); }
    inline s32 _acc_sSliderSize$AddEq(s32 value)			{ CHCKTHIS; return _acc_sSliderSizeAddEq(value); }
    inline s32 _acc_sSliderSizeSubEq(s32 value)	{ return _acc_sSliderSize(_acc_gSliderSize() - value); }
    inline s32 _acc_sSliderSize$SubEq(s32 value)			{ CHCKTHIS; return _acc_sSliderSizeSubEq(value); }
    inline s32 _acc_sSliderSizeMulEq(s32 value)	{ return _acc_sSliderSize(_acc_gSliderSize() * value); }
    inline s32 _acc_sSliderSize$MulEq(s32 value)			{ CHCKTHIS; return _acc_sSliderSizeMulEq(value); }
    inline s32 _acc_sSliderSizeDivEq(s32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sSliderSize(_acc_gSliderSize() / value); }
    inline s32 _acc_sSliderSize$DivEq(s32 value)			{ CHCKTHIS; return _acc_sSliderSizeDivEq(value); }
    inline s32 _acc_sSliderSizeModEq(s32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sSliderSize(_acc_gSliderSize() % value); }
    inline s32 _acc_sSliderSize$ModEq(s32 value)			{ CHCKTHIS; return _acc_sSliderSizeModEq(value); }
    inline s32 _acc_sSliderSizeXorEq(s32 value)	{ return _acc_sSliderSize(_acc_gSliderSize() ^ value); }
    inline s32 _acc_sSliderSize$XorEq(s32 value)			{ CHCKTHIS; return _acc_sSliderSizeXorEq(value); }
    inline s32 _acc_sSliderSizeAndEq(s32 value)	{ return _acc_sSliderSize(_acc_gSliderSize() & value); }
    inline s32 _acc_sSliderSize$AndEq(s32 value)			{ CHCKTHIS; return _acc_sSliderSizeAndEq(value); }
    inline s32 _acc_sSliderSizeOrEq(s32 value)		{ return _acc_sSliderSize(_acc_gSliderSize() | value); }
    inline s32 _acc_sSliderSize$OrEq(s32 value)			{ CHCKTHIS; return _acc_sSliderSizeOrEq(value); }
    inline s32 _acc_sSliderSizeRShiftEq(s32 value)	{ return _acc_sSliderSize(_acc_gSliderSize() >> value); }
    inline s32 _acc_sSliderSize$RShiftEq(s32 value)			{ CHCKTHIS; return _acc_sSliderSizeRShiftEq(value); }
    inline s32 _acc_sSliderSizeLShiftEq(s32 value)	{ return _acc_sSliderSize(_acc_gSliderSize() << value); }
    inline s32 _acc_sSliderSize$LShiftEq(s32 value)			{ CHCKTHIS; return _acc_sSliderSizeLShiftEq(value); }
    inline s32 _acc_gSliderSizeMin();
    inline s32 _acc_gSliderSizeMin$();

    inline s32 _acc_sSliderSizeMin(s32 value);
    inline s32 _acc_sSliderSizeMin$(s32 value);
    inline s32 _acc_sSliderSizeMinpostInc()			{ s32 tmp; _acc_sSliderSizeMin((tmp = _acc_gSliderSizeMin())+1); return tmp; }
    inline s32 _acc_sSliderSizeMin$postInc()			{ CHCKTHIS; return _acc_sSliderSizeMinpostInc(); }
    inline s32 _acc_sSliderSizeMinpostDec()			{ s32 tmp; _acc_sSliderSizeMin((tmp = _acc_gSliderSizeMin())-1); return tmp; }
    inline s32 _acc_sSliderSizeMin$postDec()			{ CHCKTHIS; return _acc_sSliderSizeMinpostDec(); }
    inline s32 _acc_sSliderSizeMinpreInc()			{ return _acc_sSliderSizeMin(_acc_gSliderSizeMin()+1); }
    inline s32 _acc_sSliderSizeMin$preInc()			{ CHCKTHIS; return _acc_sSliderSizeMinpreInc(); }
    inline s32 _acc_sSliderSizeMinpreDec()			{ return _acc_sSliderSizeMin(_acc_gSliderSizeMin()-1); }
    inline s32 _acc_sSliderSizeMin$preDec()			{ CHCKTHIS; return _acc_sSliderSizeMinpreDec(); }
    inline s32 _acc_sSliderSizeMinAddEq(s32 value)	{ return _acc_sSliderSizeMin(_acc_gSliderSizeMin() + value); }
    inline s32 _acc_sSliderSizeMin$AddEq(s32 value)			{ CHCKTHIS; return _acc_sSliderSizeMinAddEq(value); }
    inline s32 _acc_sSliderSizeMinSubEq(s32 value)	{ return _acc_sSliderSizeMin(_acc_gSliderSizeMin() - value); }
    inline s32 _acc_sSliderSizeMin$SubEq(s32 value)			{ CHCKTHIS; return _acc_sSliderSizeMinSubEq(value); }
    inline s32 _acc_sSliderSizeMinMulEq(s32 value)	{ return _acc_sSliderSizeMin(_acc_gSliderSizeMin() * value); }
    inline s32 _acc_sSliderSizeMin$MulEq(s32 value)			{ CHCKTHIS; return _acc_sSliderSizeMinMulEq(value); }
    inline s32 _acc_sSliderSizeMinDivEq(s32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sSliderSizeMin(_acc_gSliderSizeMin() / value); }
    inline s32 _acc_sSliderSizeMin$DivEq(s32 value)			{ CHCKTHIS; return _acc_sSliderSizeMinDivEq(value); }
    inline s32 _acc_sSliderSizeMinModEq(s32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sSliderSizeMin(_acc_gSliderSizeMin() % value); }
    inline s32 _acc_sSliderSizeMin$ModEq(s32 value)			{ CHCKTHIS; return _acc_sSliderSizeMinModEq(value); }
    inline s32 _acc_sSliderSizeMinXorEq(s32 value)	{ return _acc_sSliderSizeMin(_acc_gSliderSizeMin() ^ value); }
    inline s32 _acc_sSliderSizeMin$XorEq(s32 value)			{ CHCKTHIS; return _acc_sSliderSizeMinXorEq(value); }
    inline s32 _acc_sSliderSizeMinAndEq(s32 value)	{ return _acc_sSliderSizeMin(_acc_gSliderSizeMin() & value); }
    inline s32 _acc_sSliderSizeMin$AndEq(s32 value)			{ CHCKTHIS; return _acc_sSliderSizeMinAndEq(value); }
    inline s32 _acc_sSliderSizeMinOrEq(s32 value)		{ return _acc_sSliderSizeMin(_acc_gSliderSizeMin() | value); }
    inline s32 _acc_sSliderSizeMin$OrEq(s32 value)			{ CHCKTHIS; return _acc_sSliderSizeMinOrEq(value); }
    inline s32 _acc_sSliderSizeMinRShiftEq(s32 value)	{ return _acc_sSliderSizeMin(_acc_gSliderSizeMin() >> value); }
    inline s32 _acc_sSliderSizeMin$RShiftEq(s32 value)			{ CHCKTHIS; return _acc_sSliderSizeMinRShiftEq(value); }
    inline s32 _acc_sSliderSizeMinLShiftEq(s32 value)	{ return _acc_sSliderSizeMin(_acc_gSliderSizeMin() << value); }
    inline s32 _acc_sSliderSizeMin$LShiftEq(s32 value)			{ CHCKTHIS; return _acc_sSliderSizeMinLShiftEq(value); }
    inline bool _acc_gIsVertical();
    inline bool _acc_gIsVertical$();

    inline bool _acc_sIsVertical(bool value);
    inline bool _acc_sIsVertical$(bool value);
    inline u32 _acc_gArgbNormal();
    inline u32 _acc_gArgbNormal$();

    inline u32 _acc_sArgbNormal(u32 value);
    inline u32 _acc_sArgbNormal$(u32 value);
    inline u32 _acc_sArgbNormalpostInc()			{ u32 tmp; _acc_sArgbNormal((tmp = _acc_gArgbNormal())+1); return tmp; }
    inline u32 _acc_sArgbNormal$postInc()			{ CHCKTHIS; return _acc_sArgbNormalpostInc(); }
    inline u32 _acc_sArgbNormalpostDec()			{ u32 tmp; _acc_sArgbNormal((tmp = _acc_gArgbNormal())-1); return tmp; }
    inline u32 _acc_sArgbNormal$postDec()			{ CHCKTHIS; return _acc_sArgbNormalpostDec(); }
    inline u32 _acc_sArgbNormalpreInc()			{ return _acc_sArgbNormal(_acc_gArgbNormal()+1); }
    inline u32 _acc_sArgbNormal$preInc()			{ CHCKTHIS; return _acc_sArgbNormalpreInc(); }
    inline u32 _acc_sArgbNormalpreDec()			{ return _acc_sArgbNormal(_acc_gArgbNormal()-1); }
    inline u32 _acc_sArgbNormal$preDec()			{ CHCKTHIS; return _acc_sArgbNormalpreDec(); }
    inline u32 _acc_sArgbNormalAddEq(u32 value)	{ return _acc_sArgbNormal(_acc_gArgbNormal() + value); }
    inline u32 _acc_sArgbNormal$AddEq(u32 value)			{ CHCKTHIS; return _acc_sArgbNormalAddEq(value); }
    inline u32 _acc_sArgbNormalSubEq(u32 value)	{ return _acc_sArgbNormal(_acc_gArgbNormal() - value); }
    inline u32 _acc_sArgbNormal$SubEq(u32 value)			{ CHCKTHIS; return _acc_sArgbNormalSubEq(value); }
    inline u32 _acc_sArgbNormalMulEq(u32 value)	{ return _acc_sArgbNormal(_acc_gArgbNormal() * value); }
    inline u32 _acc_sArgbNormal$MulEq(u32 value)			{ CHCKTHIS; return _acc_sArgbNormalMulEq(value); }
    inline u32 _acc_sArgbNormalDivEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sArgbNormal(_acc_gArgbNormal() / value); }
    inline u32 _acc_sArgbNormal$DivEq(u32 value)			{ CHCKTHIS; return _acc_sArgbNormalDivEq(value); }
    inline u32 _acc_sArgbNormalModEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sArgbNormal(_acc_gArgbNormal() % value); }
    inline u32 _acc_sArgbNormal$ModEq(u32 value)			{ CHCKTHIS; return _acc_sArgbNormalModEq(value); }
    inline u32 _acc_sArgbNormalXorEq(u32 value)	{ return _acc_sArgbNormal(_acc_gArgbNormal() ^ value); }
    inline u32 _acc_sArgbNormal$XorEq(u32 value)			{ CHCKTHIS; return _acc_sArgbNormalXorEq(value); }
    inline u32 _acc_sArgbNormalAndEq(u32 value)	{ return _acc_sArgbNormal(_acc_gArgbNormal() & value); }
    inline u32 _acc_sArgbNormal$AndEq(u32 value)			{ CHCKTHIS; return _acc_sArgbNormalAndEq(value); }
    inline u32 _acc_sArgbNormalOrEq(u32 value)		{ return _acc_sArgbNormal(_acc_gArgbNormal() | value); }
    inline u32 _acc_sArgbNormal$OrEq(u32 value)			{ CHCKTHIS; return _acc_sArgbNormalOrEq(value); }
    inline u32 _acc_sArgbNormalRShiftEq(u32 value)	{ return _acc_sArgbNormal(_acc_gArgbNormal() >> value); }
    inline u32 _acc_sArgbNormal$RShiftEq(u32 value)			{ CHCKTHIS; return _acc_sArgbNormalRShiftEq(value); }
    inline u32 _acc_sArgbNormalLShiftEq(u32 value)	{ return _acc_sArgbNormal(_acc_gArgbNormal() << value); }
    inline u32 _acc_sArgbNormal$LShiftEq(u32 value)			{ CHCKTHIS; return _acc_sArgbNormalLShiftEq(value); }
    inline u32 _acc_gArgbActive();
    inline u32 _acc_gArgbActive$();

    inline u32 _acc_sArgbActive(u32 value);
    inline u32 _acc_sArgbActive$(u32 value);
    inline u32 _acc_sArgbActivepostInc()			{ u32 tmp; _acc_sArgbActive((tmp = _acc_gArgbActive())+1); return tmp; }
    inline u32 _acc_sArgbActive$postInc()			{ CHCKTHIS; return _acc_sArgbActivepostInc(); }
    inline u32 _acc_sArgbActivepostDec()			{ u32 tmp; _acc_sArgbActive((tmp = _acc_gArgbActive())-1); return tmp; }
    inline u32 _acc_sArgbActive$postDec()			{ CHCKTHIS; return _acc_sArgbActivepostDec(); }
    inline u32 _acc_sArgbActivepreInc()			{ return _acc_sArgbActive(_acc_gArgbActive()+1); }
    inline u32 _acc_sArgbActive$preInc()			{ CHCKTHIS; return _acc_sArgbActivepreInc(); }
    inline u32 _acc_sArgbActivepreDec()			{ return _acc_sArgbActive(_acc_gArgbActive()-1); }
    inline u32 _acc_sArgbActive$preDec()			{ CHCKTHIS; return _acc_sArgbActivepreDec(); }
    inline u32 _acc_sArgbActiveAddEq(u32 value)	{ return _acc_sArgbActive(_acc_gArgbActive() + value); }
    inline u32 _acc_sArgbActive$AddEq(u32 value)			{ CHCKTHIS; return _acc_sArgbActiveAddEq(value); }
    inline u32 _acc_sArgbActiveSubEq(u32 value)	{ return _acc_sArgbActive(_acc_gArgbActive() - value); }
    inline u32 _acc_sArgbActive$SubEq(u32 value)			{ CHCKTHIS; return _acc_sArgbActiveSubEq(value); }
    inline u32 _acc_sArgbActiveMulEq(u32 value)	{ return _acc_sArgbActive(_acc_gArgbActive() * value); }
    inline u32 _acc_sArgbActive$MulEq(u32 value)			{ CHCKTHIS; return _acc_sArgbActiveMulEq(value); }
    inline u32 _acc_sArgbActiveDivEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sArgbActive(_acc_gArgbActive() / value); }
    inline u32 _acc_sArgbActive$DivEq(u32 value)			{ CHCKTHIS; return _acc_sArgbActiveDivEq(value); }
    inline u32 _acc_sArgbActiveModEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sArgbActive(_acc_gArgbActive() % value); }
    inline u32 _acc_sArgbActive$ModEq(u32 value)			{ CHCKTHIS; return _acc_sArgbActiveModEq(value); }
    inline u32 _acc_sArgbActiveXorEq(u32 value)	{ return _acc_sArgbActive(_acc_gArgbActive() ^ value); }
    inline u32 _acc_sArgbActive$XorEq(u32 value)			{ CHCKTHIS; return _acc_sArgbActiveXorEq(value); }
    inline u32 _acc_sArgbActiveAndEq(u32 value)	{ return _acc_sArgbActive(_acc_gArgbActive() & value); }
    inline u32 _acc_sArgbActive$AndEq(u32 value)			{ CHCKTHIS; return _acc_sArgbActiveAndEq(value); }
    inline u32 _acc_sArgbActiveOrEq(u32 value)		{ return _acc_sArgbActive(_acc_gArgbActive() | value); }
    inline u32 _acc_sArgbActive$OrEq(u32 value)			{ CHCKTHIS; return _acc_sArgbActiveOrEq(value); }
    inline u32 _acc_sArgbActiveRShiftEq(u32 value)	{ return _acc_sArgbActive(_acc_gArgbActive() >> value); }
    inline u32 _acc_sArgbActive$RShiftEq(u32 value)			{ CHCKTHIS; return _acc_sArgbActiveRShiftEq(value); }
    inline u32 _acc_sArgbActiveLShiftEq(u32 value)	{ return _acc_sArgbActive(_acc_gArgbActive() << value); }
    inline u32 _acc_sArgbActive$LShiftEq(u32 value)			{ CHCKTHIS; return _acc_sArgbActiveLShiftEq(value); }
    inline bool _acc_gIsTouchActive();
    inline bool _acc_gIsTouchActive$();

    inline bool _acc_sIsTouchActive(bool value);
    inline bool _acc_sIsTouchActive$(bool value);
    inline u32 _acc_gMode();
    inline u32 _acc_gMode$();

    inline u32 _acc_sMode(u32 value);
    inline u32 _acc_sMode$(u32 value);
    inline u32 _acc_sModepostInc()			{ u32 tmp; _acc_sMode((tmp = _acc_gMode())+1); return tmp; }
    inline u32 _acc_sMode$postInc()			{ CHCKTHIS; return _acc_sModepostInc(); }
    inline u32 _acc_sModepostDec()			{ u32 tmp; _acc_sMode((tmp = _acc_gMode())-1); return tmp; }
    inline u32 _acc_sMode$postDec()			{ CHCKTHIS; return _acc_sModepostDec(); }
    inline u32 _acc_sModepreInc()			{ return _acc_sMode(_acc_gMode()+1); }
    inline u32 _acc_sMode$preInc()			{ CHCKTHIS; return _acc_sModepreInc(); }
    inline u32 _acc_sModepreDec()			{ return _acc_sMode(_acc_gMode()-1); }
    inline u32 _acc_sMode$preDec()			{ CHCKTHIS; return _acc_sModepreDec(); }
    inline u32 _acc_sModeAddEq(u32 value)	{ return _acc_sMode(_acc_gMode() + value); }
    inline u32 _acc_sMode$AddEq(u32 value)			{ CHCKTHIS; return _acc_sModeAddEq(value); }
    inline u32 _acc_sModeSubEq(u32 value)	{ return _acc_sMode(_acc_gMode() - value); }
    inline u32 _acc_sMode$SubEq(u32 value)			{ CHCKTHIS; return _acc_sModeSubEq(value); }
    inline u32 _acc_sModeMulEq(u32 value)	{ return _acc_sMode(_acc_gMode() * value); }
    inline u32 _acc_sMode$MulEq(u32 value)			{ CHCKTHIS; return _acc_sModeMulEq(value); }
    inline u32 _acc_sModeDivEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sMode(_acc_gMode() / value); }
    inline u32 _acc_sMode$DivEq(u32 value)			{ CHCKTHIS; return _acc_sModeDivEq(value); }
    inline u32 _acc_sModeModEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sMode(_acc_gMode() % value); }
    inline u32 _acc_sMode$ModEq(u32 value)			{ CHCKTHIS; return _acc_sModeModEq(value); }
    inline u32 _acc_sModeXorEq(u32 value)	{ return _acc_sMode(_acc_gMode() ^ value); }
    inline u32 _acc_sMode$XorEq(u32 value)			{ CHCKTHIS; return _acc_sModeXorEq(value); }
    inline u32 _acc_sModeAndEq(u32 value)	{ return _acc_sMode(_acc_gMode() & value); }
    inline u32 _acc_sMode$AndEq(u32 value)			{ CHCKTHIS; return _acc_sModeAndEq(value); }
    inline u32 _acc_sModeOrEq(u32 value)		{ return _acc_sMode(_acc_gMode() | value); }
    inline u32 _acc_sMode$OrEq(u32 value)			{ CHCKTHIS; return _acc_sModeOrEq(value); }
    inline u32 _acc_sModeRShiftEq(u32 value)	{ return _acc_sMode(_acc_gMode() >> value); }
    inline u32 _acc_sMode$RShiftEq(u32 value)			{ CHCKTHIS; return _acc_sModeRShiftEq(value); }
    inline u32 _acc_sModeLShiftEq(u32 value)	{ return _acc_sMode(_acc_gMode() << value); }
    inline u32 _acc_sMode$LShiftEq(u32 value)			{ CHCKTHIS; return _acc_sModeLShiftEq(value); }
    static s32* _ext_CKLBUIScrollBar_create(s32* pParent,u32 order,float x,float y,float width,float height,s32 minValue,s32 maxValue,s32 pos,s32* image,s32 slider_size,s32 min_slider_size,u32 colorNormal,u32 colorSelect,bool vert,bool active,bool hideMode);
    static s32 _ext_CKLBUIScrollBar_getMin(s32* p);
    static void _ext_CKLBUIScrollBar_setMin(s32* p,s32 value);
    static s32 _ext_CKLBUIScrollBar_getMax(s32* p);
    static void _ext_CKLBUIScrollBar_setMax(s32* p,s32 value);
    static s32 _ext_CKLBUIScrollBar_getPos(s32* p);
    static void _ext_CKLBUIScrollBar_setPos(s32* p,s32 value);
    static s32 _ext_CKLBUIScrollBar_getSliderSize(s32* p);
    static void _ext_CKLBUIScrollBar_setSliderSize(s32* p,s32 value);
    static s32 _ext_CKLBUIScrollBar_getSliderSizeMin(s32* p);
    static void _ext_CKLBUIScrollBar_setSliderSizeMin(s32* p,s32 value);
    static bool _ext_CKLBUIScrollBar_getTouchActive(s32* p);
    static void _ext_CKLBUIScrollBar_setTouchActive(s32* p,bool active);
    static u32 _ext_CKLBUIScrollBar_getNormalColor(s32* p);
    static void _ext_CKLBUIScrollBar_setNormalColor(s32* p,u32 color);
    static u32 _ext_CKLBUIScrollBar_getActiveColor(s32* p);
    static void _ext_CKLBUIScrollBar_setActiveColor(s32* p,u32 color);
    static void _ext_CKLBUIScrollBar_setMode(s32* p,u32 mode);
    static bool _ext_CKLBUIScrollBar_getVertical(s32* p);
    static void _ext_CKLBUIScrollBar_setVertical(s32* p,bool vertical);
    static s32 _ext_CKLBUIScrollBar_getWidth(s32* p);
    static void _ext_CKLBUIScrollBar_setWidth(s32* p,s32 width);
    static s32 _ext_CKLBUIScrollBar_getHeight(s32* p);
    static void _ext_CKLBUIScrollBar_setHeight(s32* p,s32 height);
    static u32 _ext_CKLBUIScrollBar_getOrder(s32* p);
    static void _ext_CKLBUIScrollBar_setOrder(s32* p,u32 order);
    static s32* _ext_CKLBUIScrollBar_getImage(s32* p);
    static u32 _ext_CKLBUIScrollBar_getMode(s32* p);
    static bool _ext_CKLBUIScrollBar_selectScrMgr(s32* p,s32* name,s32 len,System::Array<s32>* args);
    CKLBUIScrollBar(EnginePrototype::CKLBUITask* parent,u32 order,float x,float y,float width,float height,s32 minValue,s32 maxValue,s32 pos,System::String* image,s32 sliderSize,s32 minSliderSize,u32 argbNormal,u32 argbSelect,bool vert,bool active,bool hideMode,EnginePrototype::_Delegate_Base_ScrollBarCallBack_inner46* callback);
    CKLBUIScrollBar();
    virtual void doSetupCallbacks();
    inline void doSetupCallbacks$();
    virtual void setDelegate(System::Delegate* anyDelegate,System::String* delegateName);
    inline void setDelegate$(System::Delegate* anyDelegate,System::String* delegateName);
    virtual void callBackFunction(u32 type,s32 pos);
    inline void callBackFunction$(u32 type,s32 pos);
    void getSize(EnginePrototype::Size& size);
    inline void getSize$(EnginePrototype::Size& size);
    void setSize(EnginePrototype::Size size);
    inline void setSize$(EnginePrototype::Size size);
    void setSize(s32 width,s32 height);
    inline void setSize$(s32 width,s32 height);
    void selectScrollManager(System::String* name,System::Array<s32>* args);
    inline void selectScrollManager$(System::String* name,System::Array<s32>* args);
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 231;
};
class EnginePrototype::CKLBUISimpleItem : public EnginePrototype::CKLBUITask {

public:
    void _ctor_CKLBUISimpleItem();
    static u32 s_classID;
    inline static u32 _ss_classIDDivEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID /= value; }
    inline static u32 _ss_classIDModEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID %= value; }

    inline u32 _acc_gOrder();
    inline u32 _acc_gOrder$();

    inline u32 _acc_sOrder(u32 value);
    inline u32 _acc_sOrder$(u32 value);
    inline u32 _acc_sOrderpostInc()			{ u32 tmp; _acc_sOrder((tmp = _acc_gOrder())+1); return tmp; }
    inline u32 _acc_sOrder$postInc()			{ CHCKTHIS; return _acc_sOrderpostInc(); }
    inline u32 _acc_sOrderpostDec()			{ u32 tmp; _acc_sOrder((tmp = _acc_gOrder())-1); return tmp; }
    inline u32 _acc_sOrder$postDec()			{ CHCKTHIS; return _acc_sOrderpostDec(); }
    inline u32 _acc_sOrderpreInc()			{ return _acc_sOrder(_acc_gOrder()+1); }
    inline u32 _acc_sOrder$preInc()			{ CHCKTHIS; return _acc_sOrderpreInc(); }
    inline u32 _acc_sOrderpreDec()			{ return _acc_sOrder(_acc_gOrder()-1); }
    inline u32 _acc_sOrder$preDec()			{ CHCKTHIS; return _acc_sOrderpreDec(); }
    inline u32 _acc_sOrderAddEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() + value); }
    inline u32 _acc_sOrder$AddEq(u32 value)			{ CHCKTHIS; return _acc_sOrderAddEq(value); }
    inline u32 _acc_sOrderSubEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() - value); }
    inline u32 _acc_sOrder$SubEq(u32 value)			{ CHCKTHIS; return _acc_sOrderSubEq(value); }
    inline u32 _acc_sOrderMulEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() * value); }
    inline u32 _acc_sOrder$MulEq(u32 value)			{ CHCKTHIS; return _acc_sOrderMulEq(value); }
    inline u32 _acc_sOrderDivEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sOrder(_acc_gOrder() / value); }
    inline u32 _acc_sOrder$DivEq(u32 value)			{ CHCKTHIS; return _acc_sOrderDivEq(value); }
    inline u32 _acc_sOrderModEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sOrder(_acc_gOrder() % value); }
    inline u32 _acc_sOrder$ModEq(u32 value)			{ CHCKTHIS; return _acc_sOrderModEq(value); }
    inline u32 _acc_sOrderXorEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() ^ value); }
    inline u32 _acc_sOrder$XorEq(u32 value)			{ CHCKTHIS; return _acc_sOrderXorEq(value); }
    inline u32 _acc_sOrderAndEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() & value); }
    inline u32 _acc_sOrder$AndEq(u32 value)			{ CHCKTHIS; return _acc_sOrderAndEq(value); }
    inline u32 _acc_sOrderOrEq(u32 value)		{ return _acc_sOrder(_acc_gOrder() | value); }
    inline u32 _acc_sOrder$OrEq(u32 value)			{ CHCKTHIS; return _acc_sOrderOrEq(value); }
    inline u32 _acc_sOrderRShiftEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() >> value); }
    inline u32 _acc_sOrder$RShiftEq(u32 value)			{ CHCKTHIS; return _acc_sOrderRShiftEq(value); }
    inline u32 _acc_sOrderLShiftEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() << value); }
    inline u32 _acc_sOrder$LShiftEq(u32 value)			{ CHCKTHIS; return _acc_sOrderLShiftEq(value); }
    inline System::String* _acc_gAsset();
    inline System::String* _acc_gAsset$();

    static s32* _ext_CKLBUISimpleItem_create(s32* pParent,u32 order,float x,float y,s32* asset);
    static u32 _ext_CKLBUISimpleItem_getOrder(s32* p);
    static void _ext_CKLBUISimpleItem_setOrder(s32* p,u32 order);
    static s32* _ext_CKLBUISimpleItem_getAsset(s32* p);
    CKLBUISimpleItem(EnginePrototype::CKLBUITask* parent,u32 order,float x,float y,System::String* asset);
    CKLBUISimpleItem();
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 235;
};
class EnginePrototype::CKLBUISWFPlayer : public EnginePrototype::CKLBUITask {
friend class CallBack_inner47;

public:
    void _ctor_CKLBUISWFPlayer();
    static u32 s_classID;
    inline static u32 _ss_classIDDivEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID /= value; }
    inline static u32 _ss_classIDModEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID %= value; }

    EnginePrototype::_Delegate_Base_CallBack_inner47* m_callback;
    inline EnginePrototype::_Delegate_Base_CallBack_inner47*& _gm_callback$() { CHCKTHIS; return m_callback; }
    inline EnginePrototype::_Delegate_Base_CallBack_inner47* _sm_callback(EnginePrototype::_Delegate_Base_CallBack_inner47* _$value);
    inline EnginePrototype::_Delegate_Base_CallBack_inner47* _sm_callback$(EnginePrototype::_Delegate_Base_CallBack_inner47* _$value);

    inline u32 _acc_gOrder();
    inline u32 _acc_gOrder$();

    inline u32 _acc_sOrder(u32 value);
    inline u32 _acc_sOrder$(u32 value);
    inline u32 _acc_sOrderpostInc()			{ u32 tmp; _acc_sOrder((tmp = _acc_gOrder())+1); return tmp; }
    inline u32 _acc_sOrder$postInc()			{ CHCKTHIS; return _acc_sOrderpostInc(); }
    inline u32 _acc_sOrderpostDec()			{ u32 tmp; _acc_sOrder((tmp = _acc_gOrder())-1); return tmp; }
    inline u32 _acc_sOrder$postDec()			{ CHCKTHIS; return _acc_sOrderpostDec(); }
    inline u32 _acc_sOrderpreInc()			{ return _acc_sOrder(_acc_gOrder()+1); }
    inline u32 _acc_sOrder$preInc()			{ CHCKTHIS; return _acc_sOrderpreInc(); }
    inline u32 _acc_sOrderpreDec()			{ return _acc_sOrder(_acc_gOrder()-1); }
    inline u32 _acc_sOrder$preDec()			{ CHCKTHIS; return _acc_sOrderpreDec(); }
    inline u32 _acc_sOrderAddEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() + value); }
    inline u32 _acc_sOrder$AddEq(u32 value)			{ CHCKTHIS; return _acc_sOrderAddEq(value); }
    inline u32 _acc_sOrderSubEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() - value); }
    inline u32 _acc_sOrder$SubEq(u32 value)			{ CHCKTHIS; return _acc_sOrderSubEq(value); }
    inline u32 _acc_sOrderMulEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() * value); }
    inline u32 _acc_sOrder$MulEq(u32 value)			{ CHCKTHIS; return _acc_sOrderMulEq(value); }
    inline u32 _acc_sOrderDivEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sOrder(_acc_gOrder() / value); }
    inline u32 _acc_sOrder$DivEq(u32 value)			{ CHCKTHIS; return _acc_sOrderDivEq(value); }
    inline u32 _acc_sOrderModEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sOrder(_acc_gOrder() % value); }
    inline u32 _acc_sOrder$ModEq(u32 value)			{ CHCKTHIS; return _acc_sOrderModEq(value); }
    inline u32 _acc_sOrderXorEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() ^ value); }
    inline u32 _acc_sOrder$XorEq(u32 value)			{ CHCKTHIS; return _acc_sOrderXorEq(value); }
    inline u32 _acc_sOrderAndEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() & value); }
    inline u32 _acc_sOrder$AndEq(u32 value)			{ CHCKTHIS; return _acc_sOrderAndEq(value); }
    inline u32 _acc_sOrderOrEq(u32 value)		{ return _acc_sOrder(_acc_gOrder() | value); }
    inline u32 _acc_sOrder$OrEq(u32 value)			{ CHCKTHIS; return _acc_sOrderOrEq(value); }
    inline u32 _acc_sOrderRShiftEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() >> value); }
    inline u32 _acc_sOrder$RShiftEq(u32 value)			{ CHCKTHIS; return _acc_sOrderRShiftEq(value); }
    inline u32 _acc_sOrderLShiftEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() << value); }
    inline u32 _acc_sOrder$LShiftEq(u32 value)			{ CHCKTHIS; return _acc_sOrderLShiftEq(value); }
    inline System::String* _acc_gAsset();
    inline System::String* _acc_gAsset$();

    inline System::String* _acc_gMovieName();
    inline System::String* _acc_gMovieName$();

    inline bool _acc_gIsPlaying();
    inline bool _acc_gIsPlaying$();

    inline bool _acc_sIsPlaying(bool value);
    inline bool _acc_sIsPlaying$(bool value);
    inline u32 _acc_gFramerate();
    inline u32 _acc_gFramerate$();

    inline u32 _acc_sFramerate(u32 value);
    inline u32 _acc_sFramerate$(u32 value);
    inline u32 _acc_sFrameratepostInc()			{ u32 tmp; _acc_sFramerate((tmp = _acc_gFramerate())+1); return tmp; }
    inline u32 _acc_sFramerate$postInc()			{ CHCKTHIS; return _acc_sFrameratepostInc(); }
    inline u32 _acc_sFrameratepostDec()			{ u32 tmp; _acc_sFramerate((tmp = _acc_gFramerate())-1); return tmp; }
    inline u32 _acc_sFramerate$postDec()			{ CHCKTHIS; return _acc_sFrameratepostDec(); }
    inline u32 _acc_sFrameratepreInc()			{ return _acc_sFramerate(_acc_gFramerate()+1); }
    inline u32 _acc_sFramerate$preInc()			{ CHCKTHIS; return _acc_sFrameratepreInc(); }
    inline u32 _acc_sFrameratepreDec()			{ return _acc_sFramerate(_acc_gFramerate()-1); }
    inline u32 _acc_sFramerate$preDec()			{ CHCKTHIS; return _acc_sFrameratepreDec(); }
    inline u32 _acc_sFramerateAddEq(u32 value)	{ return _acc_sFramerate(_acc_gFramerate() + value); }
    inline u32 _acc_sFramerate$AddEq(u32 value)			{ CHCKTHIS; return _acc_sFramerateAddEq(value); }
    inline u32 _acc_sFramerateSubEq(u32 value)	{ return _acc_sFramerate(_acc_gFramerate() - value); }
    inline u32 _acc_sFramerate$SubEq(u32 value)			{ CHCKTHIS; return _acc_sFramerateSubEq(value); }
    inline u32 _acc_sFramerateMulEq(u32 value)	{ return _acc_sFramerate(_acc_gFramerate() * value); }
    inline u32 _acc_sFramerate$MulEq(u32 value)			{ CHCKTHIS; return _acc_sFramerateMulEq(value); }
    inline u32 _acc_sFramerateDivEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sFramerate(_acc_gFramerate() / value); }
    inline u32 _acc_sFramerate$DivEq(u32 value)			{ CHCKTHIS; return _acc_sFramerateDivEq(value); }
    inline u32 _acc_sFramerateModEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sFramerate(_acc_gFramerate() % value); }
    inline u32 _acc_sFramerate$ModEq(u32 value)			{ CHCKTHIS; return _acc_sFramerateModEq(value); }
    inline u32 _acc_sFramerateXorEq(u32 value)	{ return _acc_sFramerate(_acc_gFramerate() ^ value); }
    inline u32 _acc_sFramerate$XorEq(u32 value)			{ CHCKTHIS; return _acc_sFramerateXorEq(value); }
    inline u32 _acc_sFramerateAndEq(u32 value)	{ return _acc_sFramerate(_acc_gFramerate() & value); }
    inline u32 _acc_sFramerate$AndEq(u32 value)			{ CHCKTHIS; return _acc_sFramerateAndEq(value); }
    inline u32 _acc_sFramerateOrEq(u32 value)		{ return _acc_sFramerate(_acc_gFramerate() | value); }
    inline u32 _acc_sFramerate$OrEq(u32 value)			{ CHCKTHIS; return _acc_sFramerateOrEq(value); }
    inline u32 _acc_sFramerateRShiftEq(u32 value)	{ return _acc_sFramerate(_acc_gFramerate() >> value); }
    inline u32 _acc_sFramerate$RShiftEq(u32 value)			{ CHCKTHIS; return _acc_sFramerateRShiftEq(value); }
    inline u32 _acc_sFramerateLShiftEq(u32 value)	{ return _acc_sFramerate(_acc_gFramerate() << value); }
    inline u32 _acc_sFramerate$LShiftEq(u32 value)			{ CHCKTHIS; return _acc_sFramerateLShiftEq(value); }
    inline bool _acc_gIsAnim();
    inline bool _acc_gIsAnim$();

    inline float _acc_gVolume();
    inline float _acc_gVolume$();

    inline float _acc_sVolume(float value);
    inline float _acc_sVolume$(float value);
    inline float _acc_sVolumepostInc()			{ float tmp; _acc_sVolume((tmp = _acc_gVolume())+1); return tmp; }
    inline float _acc_sVolume$postInc()			{ CHCKTHIS; return _acc_sVolumepostInc(); }
    inline float _acc_sVolumepostDec()			{ float tmp; _acc_sVolume((tmp = _acc_gVolume())-1); return tmp; }
    inline float _acc_sVolume$postDec()			{ CHCKTHIS; return _acc_sVolumepostDec(); }
    inline float _acc_sVolumepreInc()			{ return _acc_sVolume(_acc_gVolume()+1); }
    inline float _acc_sVolume$preInc()			{ CHCKTHIS; return _acc_sVolumepreInc(); }
    inline float _acc_sVolumepreDec()			{ return _acc_sVolume(_acc_gVolume()-1); }
    inline float _acc_sVolume$preDec()			{ CHCKTHIS; return _acc_sVolumepreDec(); }
    inline float _acc_sVolumeAddEq(float value)	{ return _acc_sVolume(_acc_gVolume() + value); }
    inline float _acc_sVolume$AddEq(float value)			{ CHCKTHIS; return _acc_sVolumeAddEq(value); }
    inline float _acc_sVolumeSubEq(float value)	{ return _acc_sVolume(_acc_gVolume() - value); }
    inline float _acc_sVolume$SubEq(float value)			{ CHCKTHIS; return _acc_sVolumeSubEq(value); }
    inline float _acc_sVolumeMulEq(float value)	{ return _acc_sVolume(_acc_gVolume() * value); }
    inline float _acc_sVolume$MulEq(float value)			{ CHCKTHIS; return _acc_sVolumeMulEq(value); }
    inline float _acc_sVolumeDivEq(float value)	{ return _acc_sVolume(_acc_gVolume() / value); }
    inline float _acc_sVolume$DivEq(float value)			{ CHCKTHIS; return _acc_sVolumeDivEq(value); }
    inline float _acc_sVolumeModEq(float value)	{  float orig = _acc_gVolume(); s32 tmp = (s32)(orig / value); return _acc_sVolume(orig - (tmp * value)); }
    inline float _acc_sVolume$ModEq(float value)			{ CHCKTHIS; return _acc_sVolumeModEq(value); }
    static s32* _ext_CKLBUISWFPlayer_create(s32* parent,u32 order,float x,float y,s32* asset,s32* movieNameconst,System::Array<s32*>* replaceList,s32 assetCnt);
    static bool _ext_CKLBUISWFPlayer_getPlay(s32* p);
    static void _ext_CKLBUISWFPlayer_setPlay(s32* p,bool play);
    static u32 _ext_CKLBUISWFPlayer_getOrder(s32* p);
    static void _ext_CKLBUISWFPlayer_setOrder(s32* p,u32 order);
    static void _ext_CKLBUISWFPlayer_gotoFrame(s32* p,s32* label);
    static u32 _ext_CKLBUISWFPlayer_getFrameRate(s32* p);
    static void _ext_CKLBUISWFPlayer_setFrameRate(s32* p,u32 fps);
    static bool _ext_CKLBUISWFPlayer_isAnimating(s32* p);
    static void _ext_CKLBUISWFPlayer_setFrameRateScale(s32* p,float scale);
    static s32* _ext_CKLBUISWFPlayer_getAsset(s32* p);
    static s32* _ext_CKLBUISWFPlayer_getMovieName(s32* p);
    static float _ext_CKLBUISWFPlayer_getVolume(s32* p);
    static void _ext_CKLBUISWFPlayer_setVolume(s32* p,float volume);
    CKLBUISWFPlayer(EnginePrototype::CKLBUITask* parent,u32 order,float x,float y,System::String* asset,System::String* movieName,EnginePrototype::_Delegate_Base_CallBack_inner47* callback,System::Array<System::String*>* replaceList,s32 assetCnt);
    CKLBUISWFPlayer();
    virtual void doSetupCallbacks();
    inline void doSetupCallbacks$();
    virtual void setDelegate(System::Delegate* anyDelegate,System::String* delegateName);
    inline void setDelegate$(System::Delegate* anyDelegate,System::String* delegateName);
    virtual void callBackFunction(s32* label);
    inline void callBackFunction$(s32* label);
    void play();
    inline void play$();
    void stop();
    inline void stop$();
    void goToFrame(System::String* label);
    inline void goToFrame$(System::String* label);
    void setFramerateScale(float scale);
    inline void setFramerateScale$(float scale);
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 236;
};
class EnginePrototype::Spline_inner4 : public System::Object {

public:
    void _ctor_Spline_inner4();
    s32 m_targetType;
    inline s32& _gm_targetType$() { CHCKTHIS; return m_targetType; }
    inline s32 _sm_targetType$(s32 _$value) { CHCKTHIS; return m_targetType = _$value; }
    inline s32 _sm_targetType$postInc()				{ CHCKTHIS; return (s32)(((s32&)m_targetType)++); }
    inline s32 _sm_targetType$postDec()				{ CHCKTHIS; return (s32)(((s32&)m_targetType)--); }
    inline s32 _sm_targetType$preInc()				{ CHCKTHIS; return (s32)(++(s32&)m_targetType); }
    inline s32 _sm_targetType$preDec()				{ CHCKTHIS; return (s32)(--(s32&)m_targetType); }
    inline s32 _sm_targetType$AddEq(s32 value)		{ CHCKTHIS; return (s32)((s32&)m_targetType += value); }
    inline s32 _sm_targetType$SubEq(s32 value)		{ CHCKTHIS; return (s32)((s32&)m_targetType -= value); }
    inline s32 _sm_targetTypepostInc()				{ return (s32)(((s32&)m_targetType)++); }
    inline s32 _sm_targetTypepostDec()				{ return (s32)(((s32&)m_targetType)--); }
    inline s32 _sm_targetTypepreInc()				{ return (s32)(++(s32&)m_targetType); }
    inline s32 _sm_targetTypepreDec()				{ return (s32)(--(s32&)m_targetType); }
    inline s32 _sm_targetTypeAddEq(s32 value)		{ return (s32)((s32&)m_targetType += value); }
    inline s32 _sm_targetTypeSubEq(s32 value)		{ return (s32)((s32&)m_targetType -= value); }

    inline s32 _acc_gTargetType();
    inline s32 _acc_gTargetType$();

    virtual u32 _acc_gKeyCount() = 0;
    virtual u32 _acc_gKeyCount$() = 0;
    Spline_inner4(s32 targetType);
    virtual void addKeyInt(u32 time,s32 value) = 0;
    inline void addKeyInt$(u32 time,s32 value);
    virtual void addKeyFloat(u32 time,float value) = 0;
    inline void addKeyFloat$(u32 time,float value);
    virtual void addKeys(s32* p,u32 splineIndex) = 0;
    inline void addKeys$(s32* p,u32 splineIndex);
    Spline_inner4();
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 242;
};
class EnginePrototype::IntSpline_inner5 : public EnginePrototype::Spline_inner4 {
friend class IntPoint_inner6;

public:
    void _ctor_IntSpline_inner5();
    System::Collections::Generic::List<EnginePrototype::IntPoint_inner6*>* m_points;
    inline System::Collections::Generic::List<EnginePrototype::IntPoint_inner6*>*& _gm_points$() { CHCKTHIS; return m_points; }
    inline System::Collections::Generic::List<EnginePrototype::IntPoint_inner6*>* _sm_points(System::Collections::Generic::List<EnginePrototype::IntPoint_inner6*>* _$value);
    inline System::Collections::Generic::List<EnginePrototype::IntPoint_inner6*>* _sm_points$(System::Collections::Generic::List<EnginePrototype::IntPoint_inner6*>* _$value);

    virtual u32 _acc_gKeyCount();
    inline u32 _acc_gKeyCount$();

    IntSpline_inner5(s32 targetType);
    virtual void addKeyInt(u32 time,s32 value);
    inline void addKeyInt$(u32 time,s32 value);
    virtual void addKeyFloat(u32 time,float value);
    inline void addKeyFloat$(u32 time,float value);
    virtual void addKeys(s32* p,u32 splineIndex);
    inline void addKeys$(s32* p,u32 splineIndex);
    IntSpline_inner5();
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 244;
};
class EnginePrototype::IntPoint_inner6 : public System::Object {

public:
    void _ctor_IntPoint_inner6();
    u32 m_time;
    inline u32& _gm_time$() { CHCKTHIS; return m_time; }
    inline u32 _sm_time$(u32 _$value) { CHCKTHIS; return m_time = _$value; }
    inline u32 _sm_time$postInc()				{ CHCKTHIS; return m_time++; }
    inline u32 _sm_time$postDec()				{ CHCKTHIS; return m_time--; }
    inline u32 _sm_time$preInc()				{ CHCKTHIS; return ++m_time; }
    inline u32 _sm_time$preDec()				{ CHCKTHIS; return --m_time; }
    inline u32 _sm_time$AddEq(u32 value)		{ CHCKTHIS; return m_time += value; }
    inline u32 _sm_time$SubEq(u32 value)		{ CHCKTHIS; return m_time -= value; }
    inline u32 _sm_time$MulEq(u32 value)		{ CHCKTHIS; return m_time *= value; }
    inline u32 _sm_time$DivEq(u32 value)		{ CHCKTHIS; if (value == 0) { THROWDIVZERO; }; ; return m_time /= value; }
    inline u32 _sm_time$ModEq(u32 value)		{ CHCKTHIS; if (value == 0) { THROWDIVZERO; }; ; return m_time %= value; }
    inline u32 _sm_time$XorEq(u32 value)		{ CHCKTHIS; return m_time ^= value; }
    inline u32 _sm_time$AndEq(u32 value)		{ CHCKTHIS; return m_time &= value; }
    inline u32 _sm_time$OrEq(u32 value)		{ CHCKTHIS; return m_time |= value; }
    inline u32 _sm_time$RShiftEq(u32 value)	{ CHCKTHIS; return m_time >>= value; }
    inline u32 _sm_time$LShiftEq(u32 value)	{ CHCKTHIS; return m_time <<= value; }
    inline u32 _sm_timepostInc()				{ return m_time++; }
    inline u32 _sm_timepostDec()				{ return m_time--; }
    inline u32 _sm_timepreInc()				{ return ++m_time; }
    inline u32 _sm_timepreDec()				{ return --m_time; }
    inline u32 _sm_timeAddEq(u32 value)		{ return m_time += value; }
    inline u32 _sm_timeSubEq(u32 value)		{ return m_time -= value; }
    inline u32 _sm_timeMulEq(u32 value)		{ return m_time *= value; }
    inline u32 _sm_timeDivEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return m_time /= value; }
    inline u32 _sm_timeModEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return m_time %= value; }
    inline u32 _sm_timeXorEq(u32 value)		{ return m_time ^= value; }
    inline u32 _sm_timeAndEq(u32 value)		{ return m_time &= value; }
    inline u32 _sm_timeOrEq(u32 value)			{ return m_time |= value; }
    inline u32 _sm_timeRShiftEq(u32 value)		{ return m_time >>= value; }
    inline u32 _sm_timeLShiftEq(u32 value)		{ return m_time <<= value; }

    s16 m_value;
    inline s16& _gm_value$() { CHCKTHIS; return m_value; }
    inline s16 _sm_value$(s16 _$value) { CHCKTHIS; return m_value = _$value; }
    inline s16 _sm_value$postInc()				{ CHCKTHIS; return m_value++; }
    inline s16 _sm_value$postDec()				{ CHCKTHIS; return m_value--; }
    inline s16 _sm_value$preInc()				{ CHCKTHIS; return ++m_value; }
    inline s16 _sm_value$preDec()				{ CHCKTHIS; return --m_value; }
    inline s16 _sm_value$AddEq(s16 value)		{ CHCKTHIS; return m_value += value; }
    inline s16 _sm_value$SubEq(s16 value)		{ CHCKTHIS; return m_value -= value; }
    inline s16 _sm_value$MulEq(s16 value)		{ CHCKTHIS; return m_value *= value; }
    inline s16 _sm_value$DivEq(s16 value)		{ CHCKTHIS; if (value == 0) { THROWDIVZERO; }; ; return m_value /= value; }
    inline s16 _sm_value$ModEq(s16 value)		{ CHCKTHIS; if (value == 0) { THROWDIVZERO; }; ; return m_value %= value; }
    inline s16 _sm_value$XorEq(s16 value)		{ CHCKTHIS; return m_value ^= value; }
    inline s16 _sm_value$AndEq(s16 value)		{ CHCKTHIS; return m_value &= value; }
    inline s16 _sm_value$OrEq(s16 value)		{ CHCKTHIS; return m_value |= value; }
    inline s16 _sm_value$RShiftEq(s16 value)	{ CHCKTHIS; return m_value >>= value; }
    inline s16 _sm_value$LShiftEq(s16 value)	{ CHCKTHIS; return m_value <<= value; }
    inline s16 _sm_valuepostInc()				{ return m_value++; }
    inline s16 _sm_valuepostDec()				{ return m_value--; }
    inline s16 _sm_valuepreInc()				{ return ++m_value; }
    inline s16 _sm_valuepreDec()				{ return --m_value; }
    inline s16 _sm_valueAddEq(s16 value)		{ return m_value += value; }
    inline s16 _sm_valueSubEq(s16 value)		{ return m_value -= value; }
    inline s16 _sm_valueMulEq(s16 value)		{ return m_value *= value; }
    inline s16 _sm_valueDivEq(s16 value)		{ if (value == 0) { THROWDIVZERO; }; ; return m_value /= value; }
    inline s16 _sm_valueModEq(s16 value)		{ if (value == 0) { THROWDIVZERO; }; ; return m_value %= value; }
    inline s16 _sm_valueXorEq(s16 value)		{ return m_value ^= value; }
    inline s16 _sm_valueAndEq(s16 value)		{ return m_value &= value; }
    inline s16 _sm_valueOrEq(s16 value)			{ return m_value |= value; }
    inline s16 _sm_valueRShiftEq(s16 value)		{ return m_value >>= value; }
    inline s16 _sm_valueLShiftEq(s16 value)		{ return m_value <<= value; }

    inline u32 _acc_gTime();
    inline u32 _acc_gTime$();

    inline s16 _acc_gValue();
    inline s16 _acc_gValue$();

    IntPoint_inner6(u32 time,s16 value);
    IntPoint_inner6();
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 246;
};
class EnginePrototype::FloatSpline_inner7 : public EnginePrototype::Spline_inner4 {
friend class FloatPoint_inner8;

public:
    void _ctor_FloatSpline_inner7();
    System::Collections::Generic::List<EnginePrototype::FloatPoint_inner8*>* m_points;
    inline System::Collections::Generic::List<EnginePrototype::FloatPoint_inner8*>*& _gm_points$() { CHCKTHIS; return m_points; }
    inline System::Collections::Generic::List<EnginePrototype::FloatPoint_inner8*>* _sm_points(System::Collections::Generic::List<EnginePrototype::FloatPoint_inner8*>* _$value);
    inline System::Collections::Generic::List<EnginePrototype::FloatPoint_inner8*>* _sm_points$(System::Collections::Generic::List<EnginePrototype::FloatPoint_inner8*>* _$value);

    virtual u32 _acc_gKeyCount();
    inline u32 _acc_gKeyCount$();

    FloatSpline_inner7(s32 targetType);
    virtual void addKeyFloat(u32 time,float value);
    inline void addKeyFloat$(u32 time,float value);
    virtual void addKeyInt(u32 time,s32 value);
    inline void addKeyInt$(u32 time,s32 value);
    virtual void addKeys(s32* p,u32 splineIndex);
    inline void addKeys$(s32* p,u32 splineIndex);
    FloatSpline_inner7();
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 248;
};
class EnginePrototype::FloatPoint_inner8 : public System::Object {

public:
    void _ctor_FloatPoint_inner8();
    u32 m_time;
    inline u32& _gm_time$() { CHCKTHIS; return m_time; }
    inline u32 _sm_time$(u32 _$value) { CHCKTHIS; return m_time = _$value; }
    inline u32 _sm_time$postInc()				{ CHCKTHIS; return m_time++; }
    inline u32 _sm_time$postDec()				{ CHCKTHIS; return m_time--; }
    inline u32 _sm_time$preInc()				{ CHCKTHIS; return ++m_time; }
    inline u32 _sm_time$preDec()				{ CHCKTHIS; return --m_time; }
    inline u32 _sm_time$AddEq(u32 value)		{ CHCKTHIS; return m_time += value; }
    inline u32 _sm_time$SubEq(u32 value)		{ CHCKTHIS; return m_time -= value; }
    inline u32 _sm_time$MulEq(u32 value)		{ CHCKTHIS; return m_time *= value; }
    inline u32 _sm_time$DivEq(u32 value)		{ CHCKTHIS; if (value == 0) { THROWDIVZERO; }; ; return m_time /= value; }
    inline u32 _sm_time$ModEq(u32 value)		{ CHCKTHIS; if (value == 0) { THROWDIVZERO; }; ; return m_time %= value; }
    inline u32 _sm_time$XorEq(u32 value)		{ CHCKTHIS; return m_time ^= value; }
    inline u32 _sm_time$AndEq(u32 value)		{ CHCKTHIS; return m_time &= value; }
    inline u32 _sm_time$OrEq(u32 value)		{ CHCKTHIS; return m_time |= value; }
    inline u32 _sm_time$RShiftEq(u32 value)	{ CHCKTHIS; return m_time >>= value; }
    inline u32 _sm_time$LShiftEq(u32 value)	{ CHCKTHIS; return m_time <<= value; }
    inline u32 _sm_timepostInc()				{ return m_time++; }
    inline u32 _sm_timepostDec()				{ return m_time--; }
    inline u32 _sm_timepreInc()				{ return ++m_time; }
    inline u32 _sm_timepreDec()				{ return --m_time; }
    inline u32 _sm_timeAddEq(u32 value)		{ return m_time += value; }
    inline u32 _sm_timeSubEq(u32 value)		{ return m_time -= value; }
    inline u32 _sm_timeMulEq(u32 value)		{ return m_time *= value; }
    inline u32 _sm_timeDivEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return m_time /= value; }
    inline u32 _sm_timeModEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return m_time %= value; }
    inline u32 _sm_timeXorEq(u32 value)		{ return m_time ^= value; }
    inline u32 _sm_timeAndEq(u32 value)		{ return m_time &= value; }
    inline u32 _sm_timeOrEq(u32 value)			{ return m_time |= value; }
    inline u32 _sm_timeRShiftEq(u32 value)		{ return m_time >>= value; }
    inline u32 _sm_timeLShiftEq(u32 value)		{ return m_time <<= value; }

    float m_value;
    inline float& _gm_value$() { CHCKTHIS; return m_value; }
    inline float _sm_value$(float _$value) { CHCKTHIS; return m_value = _$value; }
    inline float _sm_value$postInc()				{ CHCKTHIS; return m_value++; }
    inline float _sm_value$postDec()				{ CHCKTHIS; return m_value--; }
    inline float _sm_value$preInc()				{ CHCKTHIS; return ++m_value; }
    inline float _sm_value$preDec()				{ CHCKTHIS; return --m_value; }
    inline float _sm_value$AddEq(float value)		{ CHCKTHIS; return m_value += value; }
    inline float _sm_value$SubEq(float value)		{ CHCKTHIS; return m_value -= value; }
    inline float _sm_value$MulEq(float value)		{ CHCKTHIS; return m_value *= value; }
    inline float _sm_value$DivEq(float value)		{ CHCKTHIS; ; return m_value /= value; }
    inline float _sm_value$ModEq(float value)		{ CHCKTHIS; s32 tmp = ((s32)(m_value / value)); return m_value = m_value-(tmp*value); }
    inline float _sm_valuepostInc()				{ return m_value++; }
    inline float _sm_valuepostDec()				{ return m_value--; }
    inline float _sm_valuepreInc()				{ return ++m_value; }
    inline float _sm_valuepreDec()				{ return --m_value; }
    inline float _sm_valueAddEq(float value)		{ return m_value += value; }
    inline float _sm_valueSubEq(float value)		{ return m_value -= value; }
    inline float _sm_valueMulEq(float value)		{ return m_value *= value; }
    inline float _sm_valueDivEq(float value)		{ ; return m_value /= value; }
    inline float _sm_valueModEq(float value)		{ s32 tmp = ((s32)(m_value / value)); return m_value = m_value-(tmp*value); }

    inline u32 _acc_gTime();
    inline u32 _acc_gTime$();

    inline float _acc_gValue();
    inline float _acc_gValue$();

    FloatPoint_inner8(u32 time,float value);
    FloatPoint_inner8();
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 250;
};
class EnginePrototype::AnimSpline_inner9 : public System::Object {

public:
    void _ctor_AnimSpline_inner9();
    System::Collections::Generic::List<EnginePrototype::Spline_inner4*>* m_splines;
    inline System::Collections::Generic::List<EnginePrototype::Spline_inner4*>*& _gm_splines$() { CHCKTHIS; return m_splines; }
    inline System::Collections::Generic::List<EnginePrototype::Spline_inner4*>* _sm_splines(System::Collections::Generic::List<EnginePrototype::Spline_inner4*>* _$value);
    inline System::Collections::Generic::List<EnginePrototype::Spline_inner4*>* _sm_splines$(System::Collections::Generic::List<EnginePrototype::Spline_inner4*>* _$value);

    inline System::Collections::Generic::List<EnginePrototype::Spline_inner4*>* _acc_gSplines();
    inline System::Collections::Generic::List<EnginePrototype::Spline_inner4*>* _acc_gSplines$();

    AnimSpline_inner9();
    EnginePrototype::Spline_inner4* addNewSpline(s32 targetType,s32 splineType);
    inline EnginePrototype::Spline_inner4* addNewSpline$(s32 targetType,s32 splineType);
    void reset();
    inline void reset$();
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 252;
};
class EnginePrototype::CKLBUITextInput : public EnginePrototype::CKLBUITask {
friend class CallBack_inner48;

public:
    enum ECHAR_TYPE {
        TXCH_7BIT_ASCII = 1,
        TXCH_UTF8 = 2,
        _ForceWORD_ECHAR_TYPE = 0x7FFFFFFF
    };

    void _ctor_CKLBUITextInput();
    static u32 s_classID;
    inline static u32 _ss_classIDDivEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID /= value; }
    inline static u32 _ss_classIDModEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID %= value; }

    EnginePrototype::_Delegate_Base_CallBack_inner48* m_callback;
    inline EnginePrototype::_Delegate_Base_CallBack_inner48*& _gm_callback$() { CHCKTHIS; return m_callback; }
    inline EnginePrototype::_Delegate_Base_CallBack_inner48* _sm_callback(EnginePrototype::_Delegate_Base_CallBack_inner48* _$value);
    inline EnginePrototype::_Delegate_Base_CallBack_inner48* _sm_callback$(EnginePrototype::_Delegate_Base_CallBack_inner48* _$value);

    inline u32 _acc_gWidth();
    inline u32 _acc_gWidth$();

    inline u32 _acc_sWidth(u32 value);
    inline u32 _acc_sWidth$(u32 value);
    inline u32 _acc_sWidthpostInc()			{ u32 tmp; _acc_sWidth((tmp = _acc_gWidth())+1); return tmp; }
    inline u32 _acc_sWidth$postInc()			{ CHCKTHIS; return _acc_sWidthpostInc(); }
    inline u32 _acc_sWidthpostDec()			{ u32 tmp; _acc_sWidth((tmp = _acc_gWidth())-1); return tmp; }
    inline u32 _acc_sWidth$postDec()			{ CHCKTHIS; return _acc_sWidthpostDec(); }
    inline u32 _acc_sWidthpreInc()			{ return _acc_sWidth(_acc_gWidth()+1); }
    inline u32 _acc_sWidth$preInc()			{ CHCKTHIS; return _acc_sWidthpreInc(); }
    inline u32 _acc_sWidthpreDec()			{ return _acc_sWidth(_acc_gWidth()-1); }
    inline u32 _acc_sWidth$preDec()			{ CHCKTHIS; return _acc_sWidthpreDec(); }
    inline u32 _acc_sWidthAddEq(u32 value)	{ return _acc_sWidth(_acc_gWidth() + value); }
    inline u32 _acc_sWidth$AddEq(u32 value)			{ CHCKTHIS; return _acc_sWidthAddEq(value); }
    inline u32 _acc_sWidthSubEq(u32 value)	{ return _acc_sWidth(_acc_gWidth() - value); }
    inline u32 _acc_sWidth$SubEq(u32 value)			{ CHCKTHIS; return _acc_sWidthSubEq(value); }
    inline u32 _acc_sWidthMulEq(u32 value)	{ return _acc_sWidth(_acc_gWidth() * value); }
    inline u32 _acc_sWidth$MulEq(u32 value)			{ CHCKTHIS; return _acc_sWidthMulEq(value); }
    inline u32 _acc_sWidthDivEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sWidth(_acc_gWidth() / value); }
    inline u32 _acc_sWidth$DivEq(u32 value)			{ CHCKTHIS; return _acc_sWidthDivEq(value); }
    inline u32 _acc_sWidthModEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sWidth(_acc_gWidth() % value); }
    inline u32 _acc_sWidth$ModEq(u32 value)			{ CHCKTHIS; return _acc_sWidthModEq(value); }
    inline u32 _acc_sWidthXorEq(u32 value)	{ return _acc_sWidth(_acc_gWidth() ^ value); }
    inline u32 _acc_sWidth$XorEq(u32 value)			{ CHCKTHIS; return _acc_sWidthXorEq(value); }
    inline u32 _acc_sWidthAndEq(u32 value)	{ return _acc_sWidth(_acc_gWidth() & value); }
    inline u32 _acc_sWidth$AndEq(u32 value)			{ CHCKTHIS; return _acc_sWidthAndEq(value); }
    inline u32 _acc_sWidthOrEq(u32 value)		{ return _acc_sWidth(_acc_gWidth() | value); }
    inline u32 _acc_sWidth$OrEq(u32 value)			{ CHCKTHIS; return _acc_sWidthOrEq(value); }
    inline u32 _acc_sWidthRShiftEq(u32 value)	{ return _acc_sWidth(_acc_gWidth() >> value); }
    inline u32 _acc_sWidth$RShiftEq(u32 value)			{ CHCKTHIS; return _acc_sWidthRShiftEq(value); }
    inline u32 _acc_sWidthLShiftEq(u32 value)	{ return _acc_sWidth(_acc_gWidth() << value); }
    inline u32 _acc_sWidth$LShiftEq(u32 value)			{ CHCKTHIS; return _acc_sWidthLShiftEq(value); }
    inline u32 _acc_gHeight();
    inline u32 _acc_gHeight$();

    inline u32 _acc_sHeight(u32 value);
    inline u32 _acc_sHeight$(u32 value);
    inline u32 _acc_sHeightpostInc()			{ u32 tmp; _acc_sHeight((tmp = _acc_gHeight())+1); return tmp; }
    inline u32 _acc_sHeight$postInc()			{ CHCKTHIS; return _acc_sHeightpostInc(); }
    inline u32 _acc_sHeightpostDec()			{ u32 tmp; _acc_sHeight((tmp = _acc_gHeight())-1); return tmp; }
    inline u32 _acc_sHeight$postDec()			{ CHCKTHIS; return _acc_sHeightpostDec(); }
    inline u32 _acc_sHeightpreInc()			{ return _acc_sHeight(_acc_gHeight()+1); }
    inline u32 _acc_sHeight$preInc()			{ CHCKTHIS; return _acc_sHeightpreInc(); }
    inline u32 _acc_sHeightpreDec()			{ return _acc_sHeight(_acc_gHeight()-1); }
    inline u32 _acc_sHeight$preDec()			{ CHCKTHIS; return _acc_sHeightpreDec(); }
    inline u32 _acc_sHeightAddEq(u32 value)	{ return _acc_sHeight(_acc_gHeight() + value); }
    inline u32 _acc_sHeight$AddEq(u32 value)			{ CHCKTHIS; return _acc_sHeightAddEq(value); }
    inline u32 _acc_sHeightSubEq(u32 value)	{ return _acc_sHeight(_acc_gHeight() - value); }
    inline u32 _acc_sHeight$SubEq(u32 value)			{ CHCKTHIS; return _acc_sHeightSubEq(value); }
    inline u32 _acc_sHeightMulEq(u32 value)	{ return _acc_sHeight(_acc_gHeight() * value); }
    inline u32 _acc_sHeight$MulEq(u32 value)			{ CHCKTHIS; return _acc_sHeightMulEq(value); }
    inline u32 _acc_sHeightDivEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sHeight(_acc_gHeight() / value); }
    inline u32 _acc_sHeight$DivEq(u32 value)			{ CHCKTHIS; return _acc_sHeightDivEq(value); }
    inline u32 _acc_sHeightModEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sHeight(_acc_gHeight() % value); }
    inline u32 _acc_sHeight$ModEq(u32 value)			{ CHCKTHIS; return _acc_sHeightModEq(value); }
    inline u32 _acc_sHeightXorEq(u32 value)	{ return _acc_sHeight(_acc_gHeight() ^ value); }
    inline u32 _acc_sHeight$XorEq(u32 value)			{ CHCKTHIS; return _acc_sHeightXorEq(value); }
    inline u32 _acc_sHeightAndEq(u32 value)	{ return _acc_sHeight(_acc_gHeight() & value); }
    inline u32 _acc_sHeight$AndEq(u32 value)			{ CHCKTHIS; return _acc_sHeightAndEq(value); }
    inline u32 _acc_sHeightOrEq(u32 value)		{ return _acc_sHeight(_acc_gHeight() | value); }
    inline u32 _acc_sHeight$OrEq(u32 value)			{ CHCKTHIS; return _acc_sHeightOrEq(value); }
    inline u32 _acc_sHeightRShiftEq(u32 value)	{ return _acc_sHeight(_acc_gHeight() >> value); }
    inline u32 _acc_sHeight$RShiftEq(u32 value)			{ CHCKTHIS; return _acc_sHeightRShiftEq(value); }
    inline u32 _acc_sHeightLShiftEq(u32 value)	{ return _acc_sHeight(_acc_gHeight() << value); }
    inline u32 _acc_sHeight$LShiftEq(u32 value)			{ CHCKTHIS; return _acc_sHeightLShiftEq(value); }
    inline System::String* _acc_gText();
    inline System::String* _acc_gText$();

    inline System::String* _acc_sText(System::String* value);
    inline System::String* _acc_sText$(System::String* value);
    inline s32 _acc_gMaxLen();
    inline s32 _acc_gMaxLen$();

    inline s32 _acc_sMaxLen(s32 value);
    inline s32 _acc_sMaxLen$(s32 value);
    inline s32 _acc_sMaxLenpostInc()			{ s32 tmp; _acc_sMaxLen((tmp = _acc_gMaxLen())+1); return tmp; }
    inline s32 _acc_sMaxLen$postInc()			{ CHCKTHIS; return _acc_sMaxLenpostInc(); }
    inline s32 _acc_sMaxLenpostDec()			{ s32 tmp; _acc_sMaxLen((tmp = _acc_gMaxLen())-1); return tmp; }
    inline s32 _acc_sMaxLen$postDec()			{ CHCKTHIS; return _acc_sMaxLenpostDec(); }
    inline s32 _acc_sMaxLenpreInc()			{ return _acc_sMaxLen(_acc_gMaxLen()+1); }
    inline s32 _acc_sMaxLen$preInc()			{ CHCKTHIS; return _acc_sMaxLenpreInc(); }
    inline s32 _acc_sMaxLenpreDec()			{ return _acc_sMaxLen(_acc_gMaxLen()-1); }
    inline s32 _acc_sMaxLen$preDec()			{ CHCKTHIS; return _acc_sMaxLenpreDec(); }
    inline s32 _acc_sMaxLenAddEq(s32 value)	{ return _acc_sMaxLen(_acc_gMaxLen() + value); }
    inline s32 _acc_sMaxLen$AddEq(s32 value)			{ CHCKTHIS; return _acc_sMaxLenAddEq(value); }
    inline s32 _acc_sMaxLenSubEq(s32 value)	{ return _acc_sMaxLen(_acc_gMaxLen() - value); }
    inline s32 _acc_sMaxLen$SubEq(s32 value)			{ CHCKTHIS; return _acc_sMaxLenSubEq(value); }
    inline s32 _acc_sMaxLenMulEq(s32 value)	{ return _acc_sMaxLen(_acc_gMaxLen() * value); }
    inline s32 _acc_sMaxLen$MulEq(s32 value)			{ CHCKTHIS; return _acc_sMaxLenMulEq(value); }
    inline s32 _acc_sMaxLenDivEq(s32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sMaxLen(_acc_gMaxLen() / value); }
    inline s32 _acc_sMaxLen$DivEq(s32 value)			{ CHCKTHIS; return _acc_sMaxLenDivEq(value); }
    inline s32 _acc_sMaxLenModEq(s32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sMaxLen(_acc_gMaxLen() % value); }
    inline s32 _acc_sMaxLen$ModEq(s32 value)			{ CHCKTHIS; return _acc_sMaxLenModEq(value); }
    inline s32 _acc_sMaxLenXorEq(s32 value)	{ return _acc_sMaxLen(_acc_gMaxLen() ^ value); }
    inline s32 _acc_sMaxLen$XorEq(s32 value)			{ CHCKTHIS; return _acc_sMaxLenXorEq(value); }
    inline s32 _acc_sMaxLenAndEq(s32 value)	{ return _acc_sMaxLen(_acc_gMaxLen() & value); }
    inline s32 _acc_sMaxLen$AndEq(s32 value)			{ CHCKTHIS; return _acc_sMaxLenAndEq(value); }
    inline s32 _acc_sMaxLenOrEq(s32 value)		{ return _acc_sMaxLen(_acc_gMaxLen() | value); }
    inline s32 _acc_sMaxLen$OrEq(s32 value)			{ CHCKTHIS; return _acc_sMaxLenOrEq(value); }
    inline s32 _acc_sMaxLenRShiftEq(s32 value)	{ return _acc_sMaxLen(_acc_gMaxLen() >> value); }
    inline s32 _acc_sMaxLen$RShiftEq(s32 value)			{ CHCKTHIS; return _acc_sMaxLenRShiftEq(value); }
    inline s32 _acc_sMaxLenLShiftEq(s32 value)	{ return _acc_sMaxLen(_acc_gMaxLen() << value); }
    inline s32 _acc_sMaxLen$LShiftEq(s32 value)			{ CHCKTHIS; return _acc_sMaxLenLShiftEq(value); }
    inline s32 _acc_gCharCount();
    inline s32 _acc_gCharCount$();

    static s32* _ext_CKLBUITextInput_create(s32* parent,bool passwordMode,float x,float y,float width,float height,s32* defaultText,s32 widgetId,s32 maxLen,u32 charType);
    static u32 _ext_CKLBUITextInput_getWidth(s32* p);
    static void _ext_CKLBUITextInput_setWidth(s32* p,u32 width);
    static u32 _ext_CKLBUITextInput_getHeight(s32* p);
    static void _ext_CKLBUITextInput_setHeight(s32* p,u32 height);
    static s32* _ext_CKLBUITextInput_getText(s32* p);
    static void _ext_CKLBUITextInput_setText(s32* p,s32* text);
    static void _ext_CKLBUITextInput_setPlaceHolder(s32* p,s32* placeholder);
    static void _ext_CKLBUITextInput_setColor(s32* p,bool bTouch,u32 foregroundRgb,u32 backgroundRgb);
    static s32 _ext_CKLBUITextInput_getMaxLen(s32* p);
    static void _ext_CKLBUITextInput_setMaxLen(s32* p,s32 maxlen);
    static void _ext_CKLBUITextInput_setCharType(s32* p,u32 chartype);
    static s32 _ext_CKLBUITextInput_getCharCount(s32* p);
    static void _ext_CKLBUITextInput_setFont(s32* p,s32* fontName,float fontSize);
    CKLBUITextInput(EnginePrototype::CKLBUITask* parent,bool passwordMode,s32 x,s32 y,u32 width,u32 height,System::String* defaultText,EnginePrototype::_Delegate_Base_CallBack_inner48* callback,s32 widgetId,s32 maxLen,u32 charType);
    CKLBUITextInput();
    virtual void doSetupCallbacks();
    inline void doSetupCallbacks$();
    virtual void setDelegate(System::Delegate* anyDelegate,System::String* delegateName);
    inline void setDelegate$(System::Delegate* anyDelegate,System::String* delegateName);
    virtual void callBackFunction(s32* txt,u32 id);
    inline void callBackFunction$(s32* txt,u32 id);
    void getSize(EnginePrototype::USize& size);
    inline void getSize$(EnginePrototype::USize& size);
    void setSize(EnginePrototype::USize size);
    inline void setSize$(EnginePrototype::USize size);
    void setSize(u32 width,u32 height);
    inline void setSize$(u32 width,u32 height);
    void setColor(bool bTouch,u32 foregroundRgb,u32 backgroundRgb);
    inline void setColor$(bool bTouch,u32 foregroundRgb,u32 backgroundRgb);
    void setFont(System::String* fontName,float fontSize);
    inline void setFont$(System::String* fontName,float fontSize);
    void setCharType(s32 chartype);
    inline void setCharType$(s32 chartype);
    void setPlaceHolder(System::String* placeHolder);
    inline void setPlaceHolder$(System::String* placeHolder);
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 254;
};
class EnginePrototype::CKLBUITouchPad : public EnginePrototype::CKLBTask {
friend class CallBack_inner49;

public:
    enum ETYPE {
        TAP,
        DRAG,
        RELEASE,
        _ForceWORD_ETYPE = 0x7FFFFFFF
    };

    void _ctor_CKLBUITouchPad();
    static u32 s_classID;
    inline static u32 _ss_classIDDivEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID /= value; }
    inline static u32 _ss_classIDModEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID %= value; }

    EnginePrototype::_Delegate_Base_CallBack_inner49* m_callback;
    inline EnginePrototype::_Delegate_Base_CallBack_inner49*& _gm_callback$() { CHCKTHIS; return m_callback; }
    inline EnginePrototype::_Delegate_Base_CallBack_inner49* _sm_callback(EnginePrototype::_Delegate_Base_CallBack_inner49* _$value);
    inline EnginePrototype::_Delegate_Base_CallBack_inner49* _sm_callback$(EnginePrototype::_Delegate_Base_CallBack_inner49* _$value);

    static s32* _ext_CKLBUITouchPad_create(s32* pParent,bool modal);
    static bool _ext_CKLBUITouchPad_setGroup(s32* p,s32* group_name);
    static void _ext_CKLBUITouchPad_setLock(s32* p,bool lock_mode);
    static void _ext_CKLBUITouchPad_setGetAll(s32* p,bool bAll);
    CKLBUITouchPad(EnginePrototype::CKLBTask* parent,EnginePrototype::_Delegate_Base_CallBack_inner49* callback,bool modal);
    CKLBUITouchPad();
    virtual void doSetupCallbacks();
    inline void doSetupCallbacks$();
    virtual void setDelegate(System::Delegate* anyDelegate,System::String* delegateName);
    inline void setDelegate$(System::Delegate* anyDelegate,System::String* delegateName);
    virtual void callBackFunction(u32 execount,u32 type,u32 id,s32 x,s32 y);
    inline void callBackFunction$(u32 execount,u32 type,u32 id,s32 x,s32 y);
    void setGetAll(bool bGetAll);
    inline void setGetAll$(bool bGetAll);
    void setLock(bool bLock);
    inline void setLock$(bool bLock);
    bool setGroup(System::String* group_name);
    inline bool setGroup$(System::String* group_name);
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 258;
};
class EnginePrototype::CKLBUIVariableItem : public EnginePrototype::CKLBUITask {

public:
    void _ctor_CKLBUIVariableItem();
    static u32 s_classID;
    inline static u32 _ss_classIDDivEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID /= value; }
    inline static u32 _ss_classIDModEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID %= value; }

    inline u32 _acc_gOrder();
    inline u32 _acc_gOrder$();

    inline u32 _acc_sOrder(u32 value);
    inline u32 _acc_sOrder$(u32 value);
    inline u32 _acc_sOrderpostInc()			{ u32 tmp; _acc_sOrder((tmp = _acc_gOrder())+1); return tmp; }
    inline u32 _acc_sOrder$postInc()			{ CHCKTHIS; return _acc_sOrderpostInc(); }
    inline u32 _acc_sOrderpostDec()			{ u32 tmp; _acc_sOrder((tmp = _acc_gOrder())-1); return tmp; }
    inline u32 _acc_sOrder$postDec()			{ CHCKTHIS; return _acc_sOrderpostDec(); }
    inline u32 _acc_sOrderpreInc()			{ return _acc_sOrder(_acc_gOrder()+1); }
    inline u32 _acc_sOrder$preInc()			{ CHCKTHIS; return _acc_sOrderpreInc(); }
    inline u32 _acc_sOrderpreDec()			{ return _acc_sOrder(_acc_gOrder()-1); }
    inline u32 _acc_sOrder$preDec()			{ CHCKTHIS; return _acc_sOrderpreDec(); }
    inline u32 _acc_sOrderAddEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() + value); }
    inline u32 _acc_sOrder$AddEq(u32 value)			{ CHCKTHIS; return _acc_sOrderAddEq(value); }
    inline u32 _acc_sOrderSubEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() - value); }
    inline u32 _acc_sOrder$SubEq(u32 value)			{ CHCKTHIS; return _acc_sOrderSubEq(value); }
    inline u32 _acc_sOrderMulEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() * value); }
    inline u32 _acc_sOrder$MulEq(u32 value)			{ CHCKTHIS; return _acc_sOrderMulEq(value); }
    inline u32 _acc_sOrderDivEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sOrder(_acc_gOrder() / value); }
    inline u32 _acc_sOrder$DivEq(u32 value)			{ CHCKTHIS; return _acc_sOrderDivEq(value); }
    inline u32 _acc_sOrderModEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sOrder(_acc_gOrder() % value); }
    inline u32 _acc_sOrder$ModEq(u32 value)			{ CHCKTHIS; return _acc_sOrderModEq(value); }
    inline u32 _acc_sOrderXorEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() ^ value); }
    inline u32 _acc_sOrder$XorEq(u32 value)			{ CHCKTHIS; return _acc_sOrderXorEq(value); }
    inline u32 _acc_sOrderAndEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() & value); }
    inline u32 _acc_sOrder$AndEq(u32 value)			{ CHCKTHIS; return _acc_sOrderAndEq(value); }
    inline u32 _acc_sOrderOrEq(u32 value)		{ return _acc_sOrder(_acc_gOrder() | value); }
    inline u32 _acc_sOrder$OrEq(u32 value)			{ CHCKTHIS; return _acc_sOrderOrEq(value); }
    inline u32 _acc_sOrderRShiftEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() >> value); }
    inline u32 _acc_sOrder$RShiftEq(u32 value)			{ CHCKTHIS; return _acc_sOrderRShiftEq(value); }
    inline u32 _acc_sOrderLShiftEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() << value); }
    inline u32 _acc_sOrder$LShiftEq(u32 value)			{ CHCKTHIS; return _acc_sOrderLShiftEq(value); }
    inline System::String* _acc_gAsset();
    inline System::String* _acc_gAsset$();

    inline System::String* _acc_sAsset(System::String* value);
    inline System::String* _acc_sAsset$(System::String* value);
    inline float _acc_gWidth();
    inline float _acc_gWidth$();

    inline float _acc_sWidth(float value);
    inline float _acc_sWidth$(float value);
    inline float _acc_sWidthpostInc()			{ float tmp; _acc_sWidth((tmp = _acc_gWidth())+1); return tmp; }
    inline float _acc_sWidth$postInc()			{ CHCKTHIS; return _acc_sWidthpostInc(); }
    inline float _acc_sWidthpostDec()			{ float tmp; _acc_sWidth((tmp = _acc_gWidth())-1); return tmp; }
    inline float _acc_sWidth$postDec()			{ CHCKTHIS; return _acc_sWidthpostDec(); }
    inline float _acc_sWidthpreInc()			{ return _acc_sWidth(_acc_gWidth()+1); }
    inline float _acc_sWidth$preInc()			{ CHCKTHIS; return _acc_sWidthpreInc(); }
    inline float _acc_sWidthpreDec()			{ return _acc_sWidth(_acc_gWidth()-1); }
    inline float _acc_sWidth$preDec()			{ CHCKTHIS; return _acc_sWidthpreDec(); }
    inline float _acc_sWidthAddEq(float value)	{ return _acc_sWidth(_acc_gWidth() + value); }
    inline float _acc_sWidth$AddEq(float value)			{ CHCKTHIS; return _acc_sWidthAddEq(value); }
    inline float _acc_sWidthSubEq(float value)	{ return _acc_sWidth(_acc_gWidth() - value); }
    inline float _acc_sWidth$SubEq(float value)			{ CHCKTHIS; return _acc_sWidthSubEq(value); }
    inline float _acc_sWidthMulEq(float value)	{ return _acc_sWidth(_acc_gWidth() * value); }
    inline float _acc_sWidth$MulEq(float value)			{ CHCKTHIS; return _acc_sWidthMulEq(value); }
    inline float _acc_sWidthDivEq(float value)	{ return _acc_sWidth(_acc_gWidth() / value); }
    inline float _acc_sWidth$DivEq(float value)			{ CHCKTHIS; return _acc_sWidthDivEq(value); }
    inline float _acc_sWidthModEq(float value)	{  float orig = _acc_gWidth(); s32 tmp = (s32)(orig / value); return _acc_sWidth(orig - (tmp * value)); }
    inline float _acc_sWidth$ModEq(float value)			{ CHCKTHIS; return _acc_sWidthModEq(value); }
    inline float _acc_gHeight();
    inline float _acc_gHeight$();

    inline float _acc_sHeight(float value);
    inline float _acc_sHeight$(float value);
    inline float _acc_sHeightpostInc()			{ float tmp; _acc_sHeight((tmp = _acc_gHeight())+1); return tmp; }
    inline float _acc_sHeight$postInc()			{ CHCKTHIS; return _acc_sHeightpostInc(); }
    inline float _acc_sHeightpostDec()			{ float tmp; _acc_sHeight((tmp = _acc_gHeight())-1); return tmp; }
    inline float _acc_sHeight$postDec()			{ CHCKTHIS; return _acc_sHeightpostDec(); }
    inline float _acc_sHeightpreInc()			{ return _acc_sHeight(_acc_gHeight()+1); }
    inline float _acc_sHeight$preInc()			{ CHCKTHIS; return _acc_sHeightpreInc(); }
    inline float _acc_sHeightpreDec()			{ return _acc_sHeight(_acc_gHeight()-1); }
    inline float _acc_sHeight$preDec()			{ CHCKTHIS; return _acc_sHeightpreDec(); }
    inline float _acc_sHeightAddEq(float value)	{ return _acc_sHeight(_acc_gHeight() + value); }
    inline float _acc_sHeight$AddEq(float value)			{ CHCKTHIS; return _acc_sHeightAddEq(value); }
    inline float _acc_sHeightSubEq(float value)	{ return _acc_sHeight(_acc_gHeight() - value); }
    inline float _acc_sHeight$SubEq(float value)			{ CHCKTHIS; return _acc_sHeightSubEq(value); }
    inline float _acc_sHeightMulEq(float value)	{ return _acc_sHeight(_acc_gHeight() * value); }
    inline float _acc_sHeight$MulEq(float value)			{ CHCKTHIS; return _acc_sHeightMulEq(value); }
    inline float _acc_sHeightDivEq(float value)	{ return _acc_sHeight(_acc_gHeight() / value); }
    inline float _acc_sHeight$DivEq(float value)			{ CHCKTHIS; return _acc_sHeightDivEq(value); }
    inline float _acc_sHeightModEq(float value)	{  float orig = _acc_gHeight(); s32 tmp = (s32)(orig / value); return _acc_sHeight(orig - (tmp * value)); }
    inline float _acc_sHeight$ModEq(float value)			{ CHCKTHIS; return _acc_sHeightModEq(value); }
    static s32* _ext_CKLBUIVariableItem_create(s32* pParent,u32 order,float x,float y,float width,float height,s32* asset);
    static u32 _ext_CKLBUIVariableItem_getOrder(s32* p);
    static void _ext_CKLBUIVariableItem_setOrder(s32* p,u32 order);
    static s32* _ext_CKLBUIVariableItem_getAsset(s32* p);
    static float _ext_CKLBUIVariableItem_getWidth(s32* p);
    static void _ext_CKLBUIVariableItem_setWidth(s32* p,float width);
    static float _ext_CKLBUIVariableItem_getHeight(s32* p);
    static void _ext_CKLBUIVariableItem_setHeight(s32* p,float height);
    static bool _ext_CKLBUIVariableItem_changeAsset(s32* p,s32* assetName);
    static void _ext_CKLBUIVariableItem_changeUV(s32* p,float x,float y,float width,float height);
    static bool _ext_CKLBUIVariableItem_setMaskAsset(s32* p,s32* assetName);
    CKLBUIVariableItem(EnginePrototype::CKLBUITask* parent,u32 order,float x,float y,float width,float height,System::String* asset);
    CKLBUIVariableItem();
    void getSize(EnginePrototype::FSize& size);
    inline void getSize$(EnginePrototype::FSize& size);
    void setUV(float x,float y,float width,float height);
    inline void setUV$(float x,float y,float width,float height);
    bool setMaskAsset(System::String* assetName);
    inline bool setMaskAsset$(System::String* assetName);
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 262;
};
class EnginePrototype::CKLBUIVirtualDoc : public EnginePrototype::CKLBUITask {
friend class CallBack_inner50;

public:
    enum ETYPE {
        TAP,
        DRAG,
        RELEASE,
        _ForceWORD_ETYPE = 0x7FFFFFFF
    };

    enum EALIGN {
        VD_ALIGN_LEFT = 0,
        VD_ALIGN_CENTER,
        VD_ALIGN_RIGHT,
        _ForceWORD_EALIGN = 0x7FFFFFFF
    };

    void _ctor_CKLBUIVirtualDoc();
    static u32 s_classID;
    inline static u32 _ss_classIDDivEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID /= value; }
    inline static u32 _ss_classIDModEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID %= value; }

    EnginePrototype::_Delegate_Base_CallBack_inner50* m_callback;
    inline EnginePrototype::_Delegate_Base_CallBack_inner50*& _gm_callback$() { CHCKTHIS; return m_callback; }
    inline EnginePrototype::_Delegate_Base_CallBack_inner50* _sm_callback(EnginePrototype::_Delegate_Base_CallBack_inner50* _$value);
    inline EnginePrototype::_Delegate_Base_CallBack_inner50* _sm_callback$(EnginePrototype::_Delegate_Base_CallBack_inner50* _$value);

    bool m_isLocked;
    inline bool& _gm_isLocked$() { CHCKTHIS; return m_isLocked; }
    inline bool _sm_isLocked$(bool _$value) { CHCKTHIS; return m_isLocked = _$value; }

    inline u32 _acc_gOrder();
    inline u32 _acc_gOrder$();

    inline u32 _acc_sOrder(u32 value);
    inline u32 _acc_sOrder$(u32 value);
    inline u32 _acc_sOrderpostInc()			{ u32 tmp; _acc_sOrder((tmp = _acc_gOrder())+1); return tmp; }
    inline u32 _acc_sOrder$postInc()			{ CHCKTHIS; return _acc_sOrderpostInc(); }
    inline u32 _acc_sOrderpostDec()			{ u32 tmp; _acc_sOrder((tmp = _acc_gOrder())-1); return tmp; }
    inline u32 _acc_sOrder$postDec()			{ CHCKTHIS; return _acc_sOrderpostDec(); }
    inline u32 _acc_sOrderpreInc()			{ return _acc_sOrder(_acc_gOrder()+1); }
    inline u32 _acc_sOrder$preInc()			{ CHCKTHIS; return _acc_sOrderpreInc(); }
    inline u32 _acc_sOrderpreDec()			{ return _acc_sOrder(_acc_gOrder()-1); }
    inline u32 _acc_sOrder$preDec()			{ CHCKTHIS; return _acc_sOrderpreDec(); }
    inline u32 _acc_sOrderAddEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() + value); }
    inline u32 _acc_sOrder$AddEq(u32 value)			{ CHCKTHIS; return _acc_sOrderAddEq(value); }
    inline u32 _acc_sOrderSubEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() - value); }
    inline u32 _acc_sOrder$SubEq(u32 value)			{ CHCKTHIS; return _acc_sOrderSubEq(value); }
    inline u32 _acc_sOrderMulEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() * value); }
    inline u32 _acc_sOrder$MulEq(u32 value)			{ CHCKTHIS; return _acc_sOrderMulEq(value); }
    inline u32 _acc_sOrderDivEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sOrder(_acc_gOrder() / value); }
    inline u32 _acc_sOrder$DivEq(u32 value)			{ CHCKTHIS; return _acc_sOrderDivEq(value); }
    inline u32 _acc_sOrderModEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sOrder(_acc_gOrder() % value); }
    inline u32 _acc_sOrder$ModEq(u32 value)			{ CHCKTHIS; return _acc_sOrderModEq(value); }
    inline u32 _acc_sOrderXorEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() ^ value); }
    inline u32 _acc_sOrder$XorEq(u32 value)			{ CHCKTHIS; return _acc_sOrderXorEq(value); }
    inline u32 _acc_sOrderAndEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() & value); }
    inline u32 _acc_sOrder$AndEq(u32 value)			{ CHCKTHIS; return _acc_sOrderAndEq(value); }
    inline u32 _acc_sOrderOrEq(u32 value)		{ return _acc_sOrder(_acc_gOrder() | value); }
    inline u32 _acc_sOrder$OrEq(u32 value)			{ CHCKTHIS; return _acc_sOrderOrEq(value); }
    inline u32 _acc_sOrderRShiftEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() >> value); }
    inline u32 _acc_sOrder$RShiftEq(u32 value)			{ CHCKTHIS; return _acc_sOrderRShiftEq(value); }
    inline u32 _acc_sOrderLShiftEq(u32 value)	{ return _acc_sOrder(_acc_gOrder() << value); }
    inline u32 _acc_sOrder$LShiftEq(u32 value)			{ CHCKTHIS; return _acc_sOrderLShiftEq(value); }
    inline u32 _acc_gCmdMax();
    inline u32 _acc_gCmdMax$();

    inline u32 _acc_sCmdMax(u32 value);
    inline u32 _acc_sCmdMax$(u32 value);
    inline u32 _acc_sCmdMaxpostInc()			{ u32 tmp; _acc_sCmdMax((tmp = _acc_gCmdMax())+1); return tmp; }
    inline u32 _acc_sCmdMax$postInc()			{ CHCKTHIS; return _acc_sCmdMaxpostInc(); }
    inline u32 _acc_sCmdMaxpostDec()			{ u32 tmp; _acc_sCmdMax((tmp = _acc_gCmdMax())-1); return tmp; }
    inline u32 _acc_sCmdMax$postDec()			{ CHCKTHIS; return _acc_sCmdMaxpostDec(); }
    inline u32 _acc_sCmdMaxpreInc()			{ return _acc_sCmdMax(_acc_gCmdMax()+1); }
    inline u32 _acc_sCmdMax$preInc()			{ CHCKTHIS; return _acc_sCmdMaxpreInc(); }
    inline u32 _acc_sCmdMaxpreDec()			{ return _acc_sCmdMax(_acc_gCmdMax()-1); }
    inline u32 _acc_sCmdMax$preDec()			{ CHCKTHIS; return _acc_sCmdMaxpreDec(); }
    inline u32 _acc_sCmdMaxAddEq(u32 value)	{ return _acc_sCmdMax(_acc_gCmdMax() + value); }
    inline u32 _acc_sCmdMax$AddEq(u32 value)			{ CHCKTHIS; return _acc_sCmdMaxAddEq(value); }
    inline u32 _acc_sCmdMaxSubEq(u32 value)	{ return _acc_sCmdMax(_acc_gCmdMax() - value); }
    inline u32 _acc_sCmdMax$SubEq(u32 value)			{ CHCKTHIS; return _acc_sCmdMaxSubEq(value); }
    inline u32 _acc_sCmdMaxMulEq(u32 value)	{ return _acc_sCmdMax(_acc_gCmdMax() * value); }
    inline u32 _acc_sCmdMax$MulEq(u32 value)			{ CHCKTHIS; return _acc_sCmdMaxMulEq(value); }
    inline u32 _acc_sCmdMaxDivEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sCmdMax(_acc_gCmdMax() / value); }
    inline u32 _acc_sCmdMax$DivEq(u32 value)			{ CHCKTHIS; return _acc_sCmdMaxDivEq(value); }
    inline u32 _acc_sCmdMaxModEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sCmdMax(_acc_gCmdMax() % value); }
    inline u32 _acc_sCmdMax$ModEq(u32 value)			{ CHCKTHIS; return _acc_sCmdMaxModEq(value); }
    inline u32 _acc_sCmdMaxXorEq(u32 value)	{ return _acc_sCmdMax(_acc_gCmdMax() ^ value); }
    inline u32 _acc_sCmdMax$XorEq(u32 value)			{ CHCKTHIS; return _acc_sCmdMaxXorEq(value); }
    inline u32 _acc_sCmdMaxAndEq(u32 value)	{ return _acc_sCmdMax(_acc_gCmdMax() & value); }
    inline u32 _acc_sCmdMax$AndEq(u32 value)			{ CHCKTHIS; return _acc_sCmdMaxAndEq(value); }
    inline u32 _acc_sCmdMaxOrEq(u32 value)		{ return _acc_sCmdMax(_acc_gCmdMax() | value); }
    inline u32 _acc_sCmdMax$OrEq(u32 value)			{ CHCKTHIS; return _acc_sCmdMaxOrEq(value); }
    inline u32 _acc_sCmdMaxRShiftEq(u32 value)	{ return _acc_sCmdMax(_acc_gCmdMax() >> value); }
    inline u32 _acc_sCmdMax$RShiftEq(u32 value)			{ CHCKTHIS; return _acc_sCmdMaxRShiftEq(value); }
    inline u32 _acc_sCmdMaxLShiftEq(u32 value)	{ return _acc_sCmdMax(_acc_gCmdMax() << value); }
    inline u32 _acc_sCmdMax$LShiftEq(u32 value)			{ CHCKTHIS; return _acc_sCmdMaxLShiftEq(value); }
    inline bool _acc_gVertical();
    inline bool _acc_gVertical$();

    inline bool _acc_sVertical(bool value);
    inline bool _acc_sVertical$(bool value);
    inline u32 _acc_gDocWidth();
    inline u32 _acc_gDocWidth$();

    inline u32 _acc_sDocWidth(u32 value);
    inline u32 _acc_sDocWidth$(u32 value);
    inline u32 _acc_sDocWidthpostInc()			{ u32 tmp; _acc_sDocWidth((tmp = _acc_gDocWidth())+1); return tmp; }
    inline u32 _acc_sDocWidth$postInc()			{ CHCKTHIS; return _acc_sDocWidthpostInc(); }
    inline u32 _acc_sDocWidthpostDec()			{ u32 tmp; _acc_sDocWidth((tmp = _acc_gDocWidth())-1); return tmp; }
    inline u32 _acc_sDocWidth$postDec()			{ CHCKTHIS; return _acc_sDocWidthpostDec(); }
    inline u32 _acc_sDocWidthpreInc()			{ return _acc_sDocWidth(_acc_gDocWidth()+1); }
    inline u32 _acc_sDocWidth$preInc()			{ CHCKTHIS; return _acc_sDocWidthpreInc(); }
    inline u32 _acc_sDocWidthpreDec()			{ return _acc_sDocWidth(_acc_gDocWidth()-1); }
    inline u32 _acc_sDocWidth$preDec()			{ CHCKTHIS; return _acc_sDocWidthpreDec(); }
    inline u32 _acc_sDocWidthAddEq(u32 value)	{ return _acc_sDocWidth(_acc_gDocWidth() + value); }
    inline u32 _acc_sDocWidth$AddEq(u32 value)			{ CHCKTHIS; return _acc_sDocWidthAddEq(value); }
    inline u32 _acc_sDocWidthSubEq(u32 value)	{ return _acc_sDocWidth(_acc_gDocWidth() - value); }
    inline u32 _acc_sDocWidth$SubEq(u32 value)			{ CHCKTHIS; return _acc_sDocWidthSubEq(value); }
    inline u32 _acc_sDocWidthMulEq(u32 value)	{ return _acc_sDocWidth(_acc_gDocWidth() * value); }
    inline u32 _acc_sDocWidth$MulEq(u32 value)			{ CHCKTHIS; return _acc_sDocWidthMulEq(value); }
    inline u32 _acc_sDocWidthDivEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sDocWidth(_acc_gDocWidth() / value); }
    inline u32 _acc_sDocWidth$DivEq(u32 value)			{ CHCKTHIS; return _acc_sDocWidthDivEq(value); }
    inline u32 _acc_sDocWidthModEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sDocWidth(_acc_gDocWidth() % value); }
    inline u32 _acc_sDocWidth$ModEq(u32 value)			{ CHCKTHIS; return _acc_sDocWidthModEq(value); }
    inline u32 _acc_sDocWidthXorEq(u32 value)	{ return _acc_sDocWidth(_acc_gDocWidth() ^ value); }
    inline u32 _acc_sDocWidth$XorEq(u32 value)			{ CHCKTHIS; return _acc_sDocWidthXorEq(value); }
    inline u32 _acc_sDocWidthAndEq(u32 value)	{ return _acc_sDocWidth(_acc_gDocWidth() & value); }
    inline u32 _acc_sDocWidth$AndEq(u32 value)			{ CHCKTHIS; return _acc_sDocWidthAndEq(value); }
    inline u32 _acc_sDocWidthOrEq(u32 value)		{ return _acc_sDocWidth(_acc_gDocWidth() | value); }
    inline u32 _acc_sDocWidth$OrEq(u32 value)			{ CHCKTHIS; return _acc_sDocWidthOrEq(value); }
    inline u32 _acc_sDocWidthRShiftEq(u32 value)	{ return _acc_sDocWidth(_acc_gDocWidth() >> value); }
    inline u32 _acc_sDocWidth$RShiftEq(u32 value)			{ CHCKTHIS; return _acc_sDocWidthRShiftEq(value); }
    inline u32 _acc_sDocWidthLShiftEq(u32 value)	{ return _acc_sDocWidth(_acc_gDocWidth() << value); }
    inline u32 _acc_sDocWidth$LShiftEq(u32 value)			{ CHCKTHIS; return _acc_sDocWidthLShiftEq(value); }
    inline u32 _acc_gDocHeight();
    inline u32 _acc_gDocHeight$();

    inline u32 _acc_sDocHeight(u32 value);
    inline u32 _acc_sDocHeight$(u32 value);
    inline u32 _acc_sDocHeightpostInc()			{ u32 tmp; _acc_sDocHeight((tmp = _acc_gDocHeight())+1); return tmp; }
    inline u32 _acc_sDocHeight$postInc()			{ CHCKTHIS; return _acc_sDocHeightpostInc(); }
    inline u32 _acc_sDocHeightpostDec()			{ u32 tmp; _acc_sDocHeight((tmp = _acc_gDocHeight())-1); return tmp; }
    inline u32 _acc_sDocHeight$postDec()			{ CHCKTHIS; return _acc_sDocHeightpostDec(); }
    inline u32 _acc_sDocHeightpreInc()			{ return _acc_sDocHeight(_acc_gDocHeight()+1); }
    inline u32 _acc_sDocHeight$preInc()			{ CHCKTHIS; return _acc_sDocHeightpreInc(); }
    inline u32 _acc_sDocHeightpreDec()			{ return _acc_sDocHeight(_acc_gDocHeight()-1); }
    inline u32 _acc_sDocHeight$preDec()			{ CHCKTHIS; return _acc_sDocHeightpreDec(); }
    inline u32 _acc_sDocHeightAddEq(u32 value)	{ return _acc_sDocHeight(_acc_gDocHeight() + value); }
    inline u32 _acc_sDocHeight$AddEq(u32 value)			{ CHCKTHIS; return _acc_sDocHeightAddEq(value); }
    inline u32 _acc_sDocHeightSubEq(u32 value)	{ return _acc_sDocHeight(_acc_gDocHeight() - value); }
    inline u32 _acc_sDocHeight$SubEq(u32 value)			{ CHCKTHIS; return _acc_sDocHeightSubEq(value); }
    inline u32 _acc_sDocHeightMulEq(u32 value)	{ return _acc_sDocHeight(_acc_gDocHeight() * value); }
    inline u32 _acc_sDocHeight$MulEq(u32 value)			{ CHCKTHIS; return _acc_sDocHeightMulEq(value); }
    inline u32 _acc_sDocHeightDivEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sDocHeight(_acc_gDocHeight() / value); }
    inline u32 _acc_sDocHeight$DivEq(u32 value)			{ CHCKTHIS; return _acc_sDocHeightDivEq(value); }
    inline u32 _acc_sDocHeightModEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sDocHeight(_acc_gDocHeight() % value); }
    inline u32 _acc_sDocHeight$ModEq(u32 value)			{ CHCKTHIS; return _acc_sDocHeightModEq(value); }
    inline u32 _acc_sDocHeightXorEq(u32 value)	{ return _acc_sDocHeight(_acc_gDocHeight() ^ value); }
    inline u32 _acc_sDocHeight$XorEq(u32 value)			{ CHCKTHIS; return _acc_sDocHeightXorEq(value); }
    inline u32 _acc_sDocHeightAndEq(u32 value)	{ return _acc_sDocHeight(_acc_gDocHeight() & value); }
    inline u32 _acc_sDocHeight$AndEq(u32 value)			{ CHCKTHIS; return _acc_sDocHeightAndEq(value); }
    inline u32 _acc_sDocHeightOrEq(u32 value)		{ return _acc_sDocHeight(_acc_gDocHeight() | value); }
    inline u32 _acc_sDocHeight$OrEq(u32 value)			{ CHCKTHIS; return _acc_sDocHeightOrEq(value); }
    inline u32 _acc_sDocHeightRShiftEq(u32 value)	{ return _acc_sDocHeight(_acc_gDocHeight() >> value); }
    inline u32 _acc_sDocHeight$RShiftEq(u32 value)			{ CHCKTHIS; return _acc_sDocHeightRShiftEq(value); }
    inline u32 _acc_sDocHeightLShiftEq(u32 value)	{ return _acc_sDocHeight(_acc_gDocHeight() << value); }
    inline u32 _acc_sDocHeight$LShiftEq(u32 value)			{ CHCKTHIS; return _acc_sDocHeightLShiftEq(value); }
    inline u32 _acc_gViewWidth();
    inline u32 _acc_gViewWidth$();

    inline u32 _acc_sViewWidth(u32 value);
    inline u32 _acc_sViewWidth$(u32 value);
    inline u32 _acc_sViewWidthpostInc()			{ u32 tmp; _acc_sViewWidth((tmp = _acc_gViewWidth())+1); return tmp; }
    inline u32 _acc_sViewWidth$postInc()			{ CHCKTHIS; return _acc_sViewWidthpostInc(); }
    inline u32 _acc_sViewWidthpostDec()			{ u32 tmp; _acc_sViewWidth((tmp = _acc_gViewWidth())-1); return tmp; }
    inline u32 _acc_sViewWidth$postDec()			{ CHCKTHIS; return _acc_sViewWidthpostDec(); }
    inline u32 _acc_sViewWidthpreInc()			{ return _acc_sViewWidth(_acc_gViewWidth()+1); }
    inline u32 _acc_sViewWidth$preInc()			{ CHCKTHIS; return _acc_sViewWidthpreInc(); }
    inline u32 _acc_sViewWidthpreDec()			{ return _acc_sViewWidth(_acc_gViewWidth()-1); }
    inline u32 _acc_sViewWidth$preDec()			{ CHCKTHIS; return _acc_sViewWidthpreDec(); }
    inline u32 _acc_sViewWidthAddEq(u32 value)	{ return _acc_sViewWidth(_acc_gViewWidth() + value); }
    inline u32 _acc_sViewWidth$AddEq(u32 value)			{ CHCKTHIS; return _acc_sViewWidthAddEq(value); }
    inline u32 _acc_sViewWidthSubEq(u32 value)	{ return _acc_sViewWidth(_acc_gViewWidth() - value); }
    inline u32 _acc_sViewWidth$SubEq(u32 value)			{ CHCKTHIS; return _acc_sViewWidthSubEq(value); }
    inline u32 _acc_sViewWidthMulEq(u32 value)	{ return _acc_sViewWidth(_acc_gViewWidth() * value); }
    inline u32 _acc_sViewWidth$MulEq(u32 value)			{ CHCKTHIS; return _acc_sViewWidthMulEq(value); }
    inline u32 _acc_sViewWidthDivEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sViewWidth(_acc_gViewWidth() / value); }
    inline u32 _acc_sViewWidth$DivEq(u32 value)			{ CHCKTHIS; return _acc_sViewWidthDivEq(value); }
    inline u32 _acc_sViewWidthModEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sViewWidth(_acc_gViewWidth() % value); }
    inline u32 _acc_sViewWidth$ModEq(u32 value)			{ CHCKTHIS; return _acc_sViewWidthModEq(value); }
    inline u32 _acc_sViewWidthXorEq(u32 value)	{ return _acc_sViewWidth(_acc_gViewWidth() ^ value); }
    inline u32 _acc_sViewWidth$XorEq(u32 value)			{ CHCKTHIS; return _acc_sViewWidthXorEq(value); }
    inline u32 _acc_sViewWidthAndEq(u32 value)	{ return _acc_sViewWidth(_acc_gViewWidth() & value); }
    inline u32 _acc_sViewWidth$AndEq(u32 value)			{ CHCKTHIS; return _acc_sViewWidthAndEq(value); }
    inline u32 _acc_sViewWidthOrEq(u32 value)		{ return _acc_sViewWidth(_acc_gViewWidth() | value); }
    inline u32 _acc_sViewWidth$OrEq(u32 value)			{ CHCKTHIS; return _acc_sViewWidthOrEq(value); }
    inline u32 _acc_sViewWidthRShiftEq(u32 value)	{ return _acc_sViewWidth(_acc_gViewWidth() >> value); }
    inline u32 _acc_sViewWidth$RShiftEq(u32 value)			{ CHCKTHIS; return _acc_sViewWidthRShiftEq(value); }
    inline u32 _acc_sViewWidthLShiftEq(u32 value)	{ return _acc_sViewWidth(_acc_gViewWidth() << value); }
    inline u32 _acc_sViewWidth$LShiftEq(u32 value)			{ CHCKTHIS; return _acc_sViewWidthLShiftEq(value); }
    inline u32 _acc_gViewHeight();
    inline u32 _acc_gViewHeight$();

    inline u32 _acc_sViewHeight(u32 value);
    inline u32 _acc_sViewHeight$(u32 value);
    inline u32 _acc_sViewHeightpostInc()			{ u32 tmp; _acc_sViewHeight((tmp = _acc_gViewHeight())+1); return tmp; }
    inline u32 _acc_sViewHeight$postInc()			{ CHCKTHIS; return _acc_sViewHeightpostInc(); }
    inline u32 _acc_sViewHeightpostDec()			{ u32 tmp; _acc_sViewHeight((tmp = _acc_gViewHeight())-1); return tmp; }
    inline u32 _acc_sViewHeight$postDec()			{ CHCKTHIS; return _acc_sViewHeightpostDec(); }
    inline u32 _acc_sViewHeightpreInc()			{ return _acc_sViewHeight(_acc_gViewHeight()+1); }
    inline u32 _acc_sViewHeight$preInc()			{ CHCKTHIS; return _acc_sViewHeightpreInc(); }
    inline u32 _acc_sViewHeightpreDec()			{ return _acc_sViewHeight(_acc_gViewHeight()-1); }
    inline u32 _acc_sViewHeight$preDec()			{ CHCKTHIS; return _acc_sViewHeightpreDec(); }
    inline u32 _acc_sViewHeightAddEq(u32 value)	{ return _acc_sViewHeight(_acc_gViewHeight() + value); }
    inline u32 _acc_sViewHeight$AddEq(u32 value)			{ CHCKTHIS; return _acc_sViewHeightAddEq(value); }
    inline u32 _acc_sViewHeightSubEq(u32 value)	{ return _acc_sViewHeight(_acc_gViewHeight() - value); }
    inline u32 _acc_sViewHeight$SubEq(u32 value)			{ CHCKTHIS; return _acc_sViewHeightSubEq(value); }
    inline u32 _acc_sViewHeightMulEq(u32 value)	{ return _acc_sViewHeight(_acc_gViewHeight() * value); }
    inline u32 _acc_sViewHeight$MulEq(u32 value)			{ CHCKTHIS; return _acc_sViewHeightMulEq(value); }
    inline u32 _acc_sViewHeightDivEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sViewHeight(_acc_gViewHeight() / value); }
    inline u32 _acc_sViewHeight$DivEq(u32 value)			{ CHCKTHIS; return _acc_sViewHeightDivEq(value); }
    inline u32 _acc_sViewHeightModEq(u32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sViewHeight(_acc_gViewHeight() % value); }
    inline u32 _acc_sViewHeight$ModEq(u32 value)			{ CHCKTHIS; return _acc_sViewHeightModEq(value); }
    inline u32 _acc_sViewHeightXorEq(u32 value)	{ return _acc_sViewHeight(_acc_gViewHeight() ^ value); }
    inline u32 _acc_sViewHeight$XorEq(u32 value)			{ CHCKTHIS; return _acc_sViewHeightXorEq(value); }
    inline u32 _acc_sViewHeightAndEq(u32 value)	{ return _acc_sViewHeight(_acc_gViewHeight() & value); }
    inline u32 _acc_sViewHeight$AndEq(u32 value)			{ CHCKTHIS; return _acc_sViewHeightAndEq(value); }
    inline u32 _acc_sViewHeightOrEq(u32 value)		{ return _acc_sViewHeight(_acc_gViewHeight() | value); }
    inline u32 _acc_sViewHeight$OrEq(u32 value)			{ CHCKTHIS; return _acc_sViewHeightOrEq(value); }
    inline u32 _acc_sViewHeightRShiftEq(u32 value)	{ return _acc_sViewHeight(_acc_gViewHeight() >> value); }
    inline u32 _acc_sViewHeight$RShiftEq(u32 value)			{ CHCKTHIS; return _acc_sViewHeightRShiftEq(value); }
    inline u32 _acc_sViewHeightLShiftEq(u32 value)	{ return _acc_sViewHeight(_acc_gViewHeight() << value); }
    inline u32 _acc_sViewHeight$LShiftEq(u32 value)			{ CHCKTHIS; return _acc_sViewHeightLShiftEq(value); }
    static s32* _ext_CKLBUIVirtualDoc_create(s32* pParent,u32 order,float x,float y,u32 docWidth,u32 docHeight,u32 viewWidth,u32 viewHeight,u32 maxCommandNums,bool verticalFlag);
    static void _ext_CKLBUIVirtualDoc_clear(s32* p,u32 color);
    static void _ext_CKLBUIVirtualDoc_setFont(s32* p,u32 idx,s32* fontName,u32 fontSize);
    static void _ext_CKLBUIVirtualDoc_setViewPortPos(s32* p,s32 x,s32 y);
    static void _ext_CKLBUIVirtualDoc_drawLine(s32* p,s32 x0,s32 y0,s32 x1,s32 y1,u32 color);
    static void _ext_CKLBUIVirtualDoc_drawImage(s32* p,s32 x0,s32 y0,s32* image,u32 alpha);
    static void _ext_CKLBUIVirtualDoc_fillRect(s32* p,s32 x0,s32 y0,u32 width,u32 height,u32 color,bool fill);
    static void _ext_CKLBUIVirtualDoc_drawText(s32* p,s32 x0,s32 y0,s32* str,u32 color,u32 fontidx);
    static void _ext_CKLBUIVirtualDoc_startDocument(s32* p);
    static void _ext_CKLBUIVirtualDoc_checkDocumentSize(s32* p);
    static void _ext_CKLBUIVirtualDoc_endDocument(s32* p);
    static u32 _ext_CKLBUIVirtualDoc_getCommandMax(s32* p);
    static void _ext_CKLBUIVirtualDoc_setCommandMax(s32* p,u32 command);
    static u32 _ext_CKLBUIVirtualDoc_getDocHeight(s32* p);
    static void _ext_CKLBUIVirtualDoc_setDocHeight(s32* p,u32 command);
    static u32 _ext_CKLBUIVirtualDoc_getDocWidth(s32* p);
    static void _ext_CKLBUIVirtualDoc_setDocWidth(s32* p,u32 command);
    static bool _ext_CKLBUIVirtualDoc_getVertical(s32* p);
    static void _ext_CKLBUIVirtualDoc_setVertical(s32* p,bool vertical);
    static u32 _ext_CKLBUIVirtualDoc_getViewHeight(s32* p);
    static void _ext_CKLBUIVirtualDoc_setViewHeight(s32* p,u32 height);
    static u32 _ext_CKLBUIVirtualDoc_getViewWidth(s32* p);
    static void _ext_CKLBUIVirtualDoc_setViewWidth(s32* p,u32 width);
    static u32 _ext_CKLBUIVirtualDoc_getOrder(s32* p);
    static void _ext_CKLBUIVirtualDoc_setOrder(s32* p,u32 order);
    static void _ext_CKLBUIVirtualDoc_setAlign(s32* p,u32 align,s32 alignWidth);
    CKLBUIVirtualDoc(EnginePrototype::CKLBUITask* parent,u32 order,float x,float y,u32 docWidth,u32 docHeight,u32 viewWidth,u32 viewHeight,u32 maxCommandNums,bool verticalFlag,EnginePrototype::_Delegate_Base_CallBack_inner50* callback);
    CKLBUIVirtualDoc();
    virtual void doSetupCallbacks();
    inline void doSetupCallbacks$();
    virtual void setDelegate(System::Delegate* anyDelegate,System::String* delegateName);
    inline void setDelegate$(System::Delegate* anyDelegate,System::String* delegateName);
    virtual void callBackFunction(u32 type,s32 x,s32 y,u32 moveX,u32 moveY);
    inline void callBackFunction$(u32 type,s32 x,s32 y,u32 moveX,u32 moveY);
    void getDocSize(EnginePrototype::USize& size);
    inline void getDocSize$(EnginePrototype::USize& size);
    void setDocSize(EnginePrototype::USize size);
    inline void setDocSize$(EnginePrototype::USize size);
    void setDocSize(u32 width,u32 height);
    inline void setDocSize$(u32 width,u32 height);
    void getViewSize(EnginePrototype::USize& size);
    inline void getViewSize$(EnginePrototype::USize& size);
    void setViewSize(EnginePrototype::USize size);
    inline void setViewSize$(EnginePrototype::USize size);
    void setViewSize(u32 width,u32 height);
    inline void setViewSize$(u32 width,u32 height);
    void setFont(u32 index,System::String* name,u32 size);
    inline void setFont$(u32 index,System::String* name,u32 size);
    void clear(u32 argb);
    inline void clear$(u32 argb);
    void setViewPortPos(s32 x,s32 y);
    inline void setViewPortPos$(s32 x,s32 y);
    void setAlign(s32 align,s32 alignWidth);
    inline void setAlign$(s32 align,s32 alignWidth);
    void startDrawList(u32 commandCount);
    inline void startDrawList$(u32 commandCount);
    void endDrawList();
    inline void endDrawList$();
    void drawLine(s32 x0,s32 y0,s32 x1,s32 y1,u32 argb);
    inline void drawLine$(s32 x0,s32 y0,s32 x1,s32 y1,u32 argb);
    void drawText(s32 x0,s32 y0,System::String* str,u32 argb,u32 font_index);
    inline void drawText$(s32 x0,s32 y0,System::String* str,u32 argb,u32 font_index);
    void drawFillRect(s32 x0,s32 y0,u32 width,u32 height,u32 argb,bool fill);
    inline void drawFillRect$(s32 x0,s32 y0,u32 width,u32 height,u32 argb,bool fill);
    void drawImage(s32 x,s32 y,System::String* image,u32 alpha);
    inline void drawImage$(s32 x,s32 y,System::String* image,u32 alpha);
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 263;
};
class EnginePrototype::CKLBUIWebArea : public EnginePrototype::CKLBUITask {
friend class CallBack_inner51;

public:
    void _ctor_CKLBUIWebArea();
    static u32 s_classID;
    inline static u32 _ss_classIDDivEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID /= value; }
    inline static u32 _ss_classIDModEq(u32 value)		{ if (value == 0) { THROWDIVZERO; }; ; return s_classID %= value; }

    EnginePrototype::_Delegate_Base_CallBack_inner51* m_callback;
    inline EnginePrototype::_Delegate_Base_CallBack_inner51*& _gm_callback$() { CHCKTHIS; return m_callback; }
    inline EnginePrototype::_Delegate_Base_CallBack_inner51* _sm_callback(EnginePrototype::_Delegate_Base_CallBack_inner51* _$value);
    inline EnginePrototype::_Delegate_Base_CallBack_inner51* _sm_callback$(EnginePrototype::_Delegate_Base_CallBack_inner51* _$value);

    inline s32 _acc_gWidth();
    inline s32 _acc_gWidth$();

    inline s32 _acc_sWidth(s32 value);
    inline s32 _acc_sWidth$(s32 value);
    inline s32 _acc_sWidthpostInc()			{ s32 tmp; _acc_sWidth((tmp = _acc_gWidth())+1); return tmp; }
    inline s32 _acc_sWidth$postInc()			{ CHCKTHIS; return _acc_sWidthpostInc(); }
    inline s32 _acc_sWidthpostDec()			{ s32 tmp; _acc_sWidth((tmp = _acc_gWidth())-1); return tmp; }
    inline s32 _acc_sWidth$postDec()			{ CHCKTHIS; return _acc_sWidthpostDec(); }
    inline s32 _acc_sWidthpreInc()			{ return _acc_sWidth(_acc_gWidth()+1); }
    inline s32 _acc_sWidth$preInc()			{ CHCKTHIS; return _acc_sWidthpreInc(); }
    inline s32 _acc_sWidthpreDec()			{ return _acc_sWidth(_acc_gWidth()-1); }
    inline s32 _acc_sWidth$preDec()			{ CHCKTHIS; return _acc_sWidthpreDec(); }
    inline s32 _acc_sWidthAddEq(s32 value)	{ return _acc_sWidth(_acc_gWidth() + value); }
    inline s32 _acc_sWidth$AddEq(s32 value)			{ CHCKTHIS; return _acc_sWidthAddEq(value); }
    inline s32 _acc_sWidthSubEq(s32 value)	{ return _acc_sWidth(_acc_gWidth() - value); }
    inline s32 _acc_sWidth$SubEq(s32 value)			{ CHCKTHIS; return _acc_sWidthSubEq(value); }
    inline s32 _acc_sWidthMulEq(s32 value)	{ return _acc_sWidth(_acc_gWidth() * value); }
    inline s32 _acc_sWidth$MulEq(s32 value)			{ CHCKTHIS; return _acc_sWidthMulEq(value); }
    inline s32 _acc_sWidthDivEq(s32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sWidth(_acc_gWidth() / value); }
    inline s32 _acc_sWidth$DivEq(s32 value)			{ CHCKTHIS; return _acc_sWidthDivEq(value); }
    inline s32 _acc_sWidthModEq(s32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sWidth(_acc_gWidth() % value); }
    inline s32 _acc_sWidth$ModEq(s32 value)			{ CHCKTHIS; return _acc_sWidthModEq(value); }
    inline s32 _acc_sWidthXorEq(s32 value)	{ return _acc_sWidth(_acc_gWidth() ^ value); }
    inline s32 _acc_sWidth$XorEq(s32 value)			{ CHCKTHIS; return _acc_sWidthXorEq(value); }
    inline s32 _acc_sWidthAndEq(s32 value)	{ return _acc_sWidth(_acc_gWidth() & value); }
    inline s32 _acc_sWidth$AndEq(s32 value)			{ CHCKTHIS; return _acc_sWidthAndEq(value); }
    inline s32 _acc_sWidthOrEq(s32 value)		{ return _acc_sWidth(_acc_gWidth() | value); }
    inline s32 _acc_sWidth$OrEq(s32 value)			{ CHCKTHIS; return _acc_sWidthOrEq(value); }
    inline s32 _acc_sWidthRShiftEq(s32 value)	{ return _acc_sWidth(_acc_gWidth() >> value); }
    inline s32 _acc_sWidth$RShiftEq(s32 value)			{ CHCKTHIS; return _acc_sWidthRShiftEq(value); }
    inline s32 _acc_sWidthLShiftEq(s32 value)	{ return _acc_sWidth(_acc_gWidth() << value); }
    inline s32 _acc_sWidth$LShiftEq(s32 value)			{ CHCKTHIS; return _acc_sWidthLShiftEq(value); }
    inline s32 _acc_gHeight();
    inline s32 _acc_gHeight$();

    inline s32 _acc_sHeight(s32 value);
    inline s32 _acc_sHeight$(s32 value);
    inline s32 _acc_sHeightpostInc()			{ s32 tmp; _acc_sHeight((tmp = _acc_gHeight())+1); return tmp; }
    inline s32 _acc_sHeight$postInc()			{ CHCKTHIS; return _acc_sHeightpostInc(); }
    inline s32 _acc_sHeightpostDec()			{ s32 tmp; _acc_sHeight((tmp = _acc_gHeight())-1); return tmp; }
    inline s32 _acc_sHeight$postDec()			{ CHCKTHIS; return _acc_sHeightpostDec(); }
    inline s32 _acc_sHeightpreInc()			{ return _acc_sHeight(_acc_gHeight()+1); }
    inline s32 _acc_sHeight$preInc()			{ CHCKTHIS; return _acc_sHeightpreInc(); }
    inline s32 _acc_sHeightpreDec()			{ return _acc_sHeight(_acc_gHeight()-1); }
    inline s32 _acc_sHeight$preDec()			{ CHCKTHIS; return _acc_sHeightpreDec(); }
    inline s32 _acc_sHeightAddEq(s32 value)	{ return _acc_sHeight(_acc_gHeight() + value); }
    inline s32 _acc_sHeight$AddEq(s32 value)			{ CHCKTHIS; return _acc_sHeightAddEq(value); }
    inline s32 _acc_sHeightSubEq(s32 value)	{ return _acc_sHeight(_acc_gHeight() - value); }
    inline s32 _acc_sHeight$SubEq(s32 value)			{ CHCKTHIS; return _acc_sHeightSubEq(value); }
    inline s32 _acc_sHeightMulEq(s32 value)	{ return _acc_sHeight(_acc_gHeight() * value); }
    inline s32 _acc_sHeight$MulEq(s32 value)			{ CHCKTHIS; return _acc_sHeightMulEq(value); }
    inline s32 _acc_sHeightDivEq(s32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sHeight(_acc_gHeight() / value); }
    inline s32 _acc_sHeight$DivEq(s32 value)			{ CHCKTHIS; return _acc_sHeightDivEq(value); }
    inline s32 _acc_sHeightModEq(s32 value)	{ if (value == 0) { THROWDIVZERO; }; return _acc_sHeight(_acc_gHeight() % value); }
    inline s32 _acc_sHeight$ModEq(s32 value)			{ CHCKTHIS; return _acc_sHeightModEq(value); }
    inline s32 _acc_sHeightXorEq(s32 value)	{ return _acc_sHeight(_acc_gHeight() ^ value); }
    inline s32 _acc_sHeight$XorEq(s32 value)			{ CHCKTHIS; return _acc_sHeightXorEq(value); }
    inline s32 _acc_sHeightAndEq(s32 value)	{ return _acc_sHeight(_acc_gHeight() & value); }
    inline s32 _acc_sHeight$AndEq(s32 value)			{ CHCKTHIS; return _acc_sHeightAndEq(value); }
    inline s32 _acc_sHeightOrEq(s32 value)		{ return _acc_sHeight(_acc_gHeight() | value); }
    inline s32 _acc_sHeight$OrEq(s32 value)			{ CHCKTHIS; return _acc_sHeightOrEq(value); }
    inline s32 _acc_sHeightRShiftEq(s32 value)	{ return _acc_sHeight(_acc_gHeight() >> value); }
    inline s32 _acc_sHeight$RShiftEq(s32 value)			{ CHCKTHIS; return _acc_sHeightRShiftEq(value); }
    inline s32 _acc_sHeightLShiftEq(s32 value)	{ return _acc_sHeight(_acc_gHeight() << value); }
    inline s32 _acc_sHeight$LShiftEq(s32 value)			{ CHCKTHIS; return _acc_sHeightLShiftEq(value); }
    inline System::String* _acc_gUrl();
    inline System::String* _acc_gUrl$();

    inline System::String* _acc_sUrl(System::String* value);
    inline System::String* _acc_sUrl$(System::String* value);
    static s32* _ext_CKLBUIWebArea_create(s32* pParent,bool mode,float x,float y,float width,float height,s32* url);
    static s32 _ext_CKLBUIWebArea_getWidth(s32* p);
    static void _ext_CKLBUIWebArea_setWidth(s32* p,s32 width);
    static s32 _ext_CKLBUIWebArea_getHeight(s32* p);
    static void _ext_CKLBUIWebArea_setHeight(s32* p,s32 height);
    static s32* _ext_CKLBUIWebArea_getText(s32* p);
    static void _ext_CKLBUIWebArea_setText(s32* p,s32* text);
    static void _ext_CKLBUIWebArea_setScalesPageToFit(s32* p,bool b);
    static void _ext_CKLBUIWebArea_setBgColor(s32* p,u32 argb);
    CKLBUIWebArea(EnginePrototype::CKLBUITask* parent,bool mode,float x,float y,float width,float height,System::String* url,EnginePrototype::_Delegate_Base_CallBack_inner51* callback);
    CKLBUIWebArea();
    virtual void doSetupCallbacks();
    inline void doSetupCallbacks$();
    virtual void setDelegate(System::Delegate* anyDelegate,System::String* delegateName);
    inline void setDelegate$(System::Delegate* anyDelegate,System::String* delegateName);
    virtual void callBackFunction(u32 uint1,s32* url);
    inline void callBackFunction$(u32 uint1,s32* url);
    void getSize(EnginePrototype::Size& size);
    inline void getSize$(EnginePrototype::Size& size);
    void setSize(EnginePrototype::Size size);
    inline void setSize$(EnginePrototype::Size size);
    void setSize(s32 width,s32 height);
    inline void setSize$(s32 width,s32 height);
    void setScalesPageToFit(bool b);
    inline void setScalesPageToFit$(bool b);
    void setBgColor(u32 argb);
    inline void setBgColor$(u32 argb);
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = _TYPE_USEROBJECT | ET_CLASS | 268;
};

void initFramework();

class Program : public System::Object {
public:
    void _ctor_Program();

    Program();
    static void start();
    virtual u32 _processGC();
    virtual void _releaseGC();
    virtual bool _isInstanceOf(u32 typeID);
    virtual inline void _moveAlert(u32 offset);
private:
    static const u32 _TYPEID = 0xFFFFFFFF;
};


#endif // _FRAMEWORK_H

