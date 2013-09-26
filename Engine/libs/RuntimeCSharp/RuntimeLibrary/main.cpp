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
#ifdef _WIN32
#pragma warning disable 4820, 4986
#include <Windows.h>
#endif

#include <stdio.h>

#include "CS_Object.h"
#include "CS_String.h"
#include "Collections/Generic/CS_List.h"
#include "Collections/Generic/CS_Dictionary.h"
#include "MarshallingUtils.h"
#include "CS_Console.h"
#include "CS_Math.h"

// Tests
#include "MemoryTests.h"

// BENCHMARK

#pragma comment (lib,"Winmm.lib")
#include <windows.h>
#include <mmsystem.h>
#include <iostream>

class cTime
{
public:
	static cTime*	Instance();
	static void		Destroy();

	void	operator()();
	UINT64	GetDTime(){return mDTime;}

private:
	cTime():mDTime(0)
	{
		mLastGameTime = (UINT64)timeGetTime();
	}
	~cTime() {}

	static cTime *mInstance;
	UINT64 mLastGameTime;
	UINT64 mDTime;
};

cTime *cTime::mInstance	=	0;

cTime *cTime::Instance()
{
	if(mInstance)
		return mInstance;
	return mInstance = new cTime;
}

void cTime::Destroy()
{
	if(mInstance)
		delete mInstance;
}

void cTime::operator()()
{
	UINT64 ticks = (UINT64)timeGetTime();

	mDTime = ticks - mLastGameTime;

	mLastGameTime = ticks;
}

void DisplayUniCharArray(System::Array<uniChar>* _array) {
	for(int i = 0; i < _array->_acc_gLength(); ++i) {
		printf("%c",_array->_idx_g(i));
	}
}

template <class T>
void DisplayArray(System::Array<T>* _array) {
	printf("|");
	for(int i = 0; i < _array->_acc_gLength(); ++i) {
		printf("%s|", (_array->_idx_g(i)) ? _array->_idx_g(i)->ToString()->_toCStr() : "");
	}
}
template <> void DisplayArray(System::Array<s64>* _array) {
	printf("|");
	for(int i = 0; i < _array->_acc_gLength(); ++i) {
		printf("%i|", _array->_idx_g(i));
	}
}
template <> void DisplayArray(System::Array<u64>* _array) {
	printf("|");
	for(int i = 0; i < _array->_acc_gLength(); ++i) {
		printf("%i|", _array->_idx_g(i));
	}
}
template <> void DisplayArray(System::Array<s32>* _array) {
	printf("|");
	for(int i = 0; i < _array->_acc_gLength(); ++i) {
		printf("%i|", _array->_idx_g(i));
	}
}
template <> void DisplayArray(System::Array<u32>* _array) {
	printf("|");
	for(int i = 0; i < _array->_acc_gLength(); ++i) {
		printf("%i|", _array->_idx_g(i));
	}
}
template <> void DisplayArray(System::Array<s16>* _array) {
	printf("|");
	for(int i = 0; i < _array->_acc_gLength(); ++i) {
		printf("%i|", _array->_idx_g(i));
	}
}
template <> void DisplayArray(System::Array<u16>* _array) {
	printf("|");
	for(int i = 0; i < _array->_acc_gLength(); ++i) {
		printf("%i|", _array->_idx_g(i));
	}
}
template <> void DisplayArray(System::Array<s8>* _array) {
	printf("|");
	for(int i = 0; i < _array->_acc_gLength(); ++i) {
		printf("%i|", _array->_idx_g(i));
	}
}
template <> void DisplayArray(System::Array<u8>* _array) {
	printf("|");
	for(int i = 0; i < _array->_acc_gLength(); ++i) {
		printf("%i|", _array->_idx_g(i));
	}
}
template <> void DisplayArray(System::Array<float>* _array) {
	printf("|");
	for(int i = 0; i < _array->_acc_gLength(); ++i) {
		printf("%G|", _array->_idx_g(i));
	}
}
template <> void DisplayArray(System::Array<double>* _array) {
	printf("|");
	for(int i = 0; i < _array->_acc_gLength(); ++i) {
		printf("%G|", _array->_idx_g(i));
	}
}
template <> void DisplayArray(System::Array<bool>* _array) {
	printf("|");
	for(int i = 0; i < _array->_acc_gLength(); ++i) {
		printf("%s|", (_array->_idx_g(i)) ? "True":"False" );
	}
}

template<class T> 
void DisplayArrayInfos(System::Array<T>* _array) {
	printf("Length = %i \t Rank = %i", _array->_acc_gLength(), _array->_acc_gRank());
}

template <class T>
void DisplayList(System::Collections::Generic::List<T>* _list) {
	printf("|");
	for(int i = 0; i < _list->_acc_gCount(); ++i) {
		printf("%s|", _list->_idx_g(i)->ToString()->_toCStr());
	}
}
template <> void DisplayList(System::Collections::Generic::List<s64>* _list) {
	printf("|");
	for(int i = 0; i < _list->_acc_gCount(); ++i) {
		printf("%i|", _list->_idx_g(i));
	}
}
template <> void DisplayList(System::Collections::Generic::List<u64>* _list) {
	printf("|");
	for(int i = 0; i < _list->_acc_gCount(); ++i) {
		printf("%i|", _list->_idx_g(i));
	}
}
template <> void DisplayList(System::Collections::Generic::List<s32>* _list) {
	printf("|");
	for(int i = 0; i < _list->_acc_gCount(); ++i) {
		printf("%i|", _list->_idx_g(i));
	}
}
template <> void DisplayList(System::Collections::Generic::List<u32>* _list) {
	printf("|");
	for(int i = 0; i < _list->_acc_gCount(); ++i) {
		printf("%i|", _list->_idx_g(i));
	}
}
template <> void DisplayList(System::Collections::Generic::List<u16>* _list) {
	printf("|");
	for(int i = 0; i < _list->_acc_gCount(); ++i) {
		printf("%i|", _list->_idx_g(i));
	}
}
template <> void DisplayList(System::Collections::Generic::List<s16>* _list) {
	printf("|");
	for(int i = 0; i < _list->_acc_gCount(); ++i) {
		printf("%i|", _list->_idx_g(i));
	}
}
template <> void DisplayList(System::Collections::Generic::List<u8>* _list) {
	printf("|");
	for(int i = 0; i < _list->_acc_gCount(); ++i) {
		printf("%i|", _list->_idx_g(i));
	}
}
template <> void DisplayList(System::Collections::Generic::List<s8>* _list) {
	printf("|");
	for(int i = 0; i < _list->_acc_gCount(); ++i) {
		printf("%i|", _list->_idx_g(i));
	}
}
template <> void DisplayList(System::Collections::Generic::List<float>* _list) {
	printf("|");
	for(int i = 0; i < _list->_acc_gCount(); ++i) {
		printf("%G|", _list->_idx_g(i));
	}
}
template <> void DisplayList(System::Collections::Generic::List<double>* _list) {
	printf("|");
	for(int i = 0; i < _list->_acc_gCount(); ++i) {
		printf("%G|", _list->_idx_g(i));
	}
}
template <> void DisplayList(System::Collections::Generic::List<bool>* _list) {
	printf("|");
	for(int i = 0; i < _list->_acc_gCount(); ++i) {
		printf("%s|", (_list->_idx_g(i)) ? "True":"False");
	}
}

template<class T> 
void DisplayListInfos(System::Collections::Generic::List<T>* _list) {
	printf("Capacity = %i \t Count = %i", _list->_acc_gCapacity(), _list->_acc_gCount());
}

template<class TKey, class TValue>
inline void DisplayDictionary(System::Collections::Generic::Dictionary<TKey,TValue>* _dictionary) {
	printf("DIPLAY NOT IMPLEMENTED FOR THESE TYPES.\n");
}

template<>
inline void DisplayDictionary(System::Collections::Generic::Dictionary<System::String*,System::String*>* _dictionary) {
	_dictionary->_display();
}

int main_tests()
{
	// Benchmark
	/*
	cTime &TimeRef = *cTime::Instance();
	TimeRef();

	TimeRef();
	std::cout<<"Benchmark1 - : "<<TimeRef.GetDTime() << std::endl;
	*/	

	//InternalTests::RefSetValueTests();

	printf("#########################################\n");
	printf("#########################################\n");
	printf("############# String Tests ##############\n");
	printf("#########################################\n");
	printf("#########################################\n");
	printf("\n\n");
    
    System::String								*s, *s1, *s2, *s3, *s4, *s5, *s6, *s7, *s8, *s9, *a, *b, *c, *d, *hw;
	System::Array<System::String*>				*strArray, *strArray2;
	System::Array<uniChar> *charArray,			*charArray2;
	System::Array<System::Object*>				*objArray;
	System::Array<s32>							*intArray, *intArray2;
	System::Object* obj;
	System::Collections::Generic::List<s32>		*intList, *intList2;
	System::Collections::Generic::List<System::String*> *strList, *strList2;

	const uniChar c_a[6]			= {'a','b','c','d','e'};
    const uniChar c_b[6]			= {'q','w','e','r','t', 'y'};
    const uniChar c_c[6]			= {'Q','W','e','r','T', 'Y'};
	const uniChar c_hw[12]			= {'H','e','l','l','o',' ','W','o','r','l','d','!'};
	const uniChar c_hello[5]		= {'H','e','l','l','o'};
	const uniChar c_world[5]		= {'W','o','r','l','d'};
	const uniChar c_digits[11]		= {'0',' ','1',' ','2',' ','3',' ','4',' ','5'};
	const uniChar c_hw_toTrim[27]	= {' ',' ',' ',' ',' ','H','e','l','l','o',' ','W','o','r','l','d','!',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}; 
	const uniChar c_badGuy[10]		= {0xDBFF, 0xDFFF};


	//const char*   char_hw			= "Hello World";
	//s = __MarshallingUtils::StringFromNativeUtf8((int *)char_hw);

	//char**  char_array = (char**)CS_MALLOC(3 * sizeof(const char*));
	//char_array[0] = "Hi";
	//char_array[1] = "Hello !";
	//char_array[2] = "and Yo ! :D";

	//strArray = __MarshallingUtils::StringArrayFromNativeUtf8IntPtr((int*) char_array, 3);

	//System::Console::WriteLine(s);

	hw = CS_NEW System::String(c_hw, 12);
	s = CS_NEW System::String(c_badGuy, 2);
	//printf("%s", s->_toCStr());

    //Test - warning zone
	//printf("[StringTest] Allocator - Warning Zone\n");
    //for(int i = 0; i < 200; ++i) {
    //    s = CS_NEW(System::String);
    //    s->_appendI(i)->_appendC(' ')->_appendClose();
    //}

	// Test - Ctor + _appendC + _appendClose
	uniChar* cArr = CS_NEWA(uniChar,10);
	cArr[0] = 'H'; cArr[1] = 'e'; cArr[2] = 'l'; cArr[3] = 'l'; cArr[4] = 'o';
	charArray = CS_NEW System::Array<uniChar>(6);
	charArray->_idx$_s(0, 'C');
	charArray->_idx$_s(1, 'h');
	charArray->_idx$_s(2, 'a');
	charArray->_idx$_s(3, 'r');
	charArray->_idx$_s(4, '[');
	charArray->_idx$_s(5, ']');
	printf("[StringTest] Constructor INTERNAL 0 - result = %s\n", (CS_NEW System::String)->_toCStr());
	printf("[StringTest] Constructor INTERNAL 1 - result = %s\n", (CS_NEW System::String(cArr, 5))->_toCStr());
	printf("[StringTest] Constructor INTERNAL 2 - result = %s\n", (CS_NEW System::String(cArr, 1,2))->_toCStr());
	printf("[StringTest] Constructor 1.0 - result = %s\n", (CS_NEW System::String(charArray))->_toCStr());
	printf("[StringTest] Constructor 1.1 - result = %s\n", (CS_NEW System::String('a',10))->_toCStr());
	printf("[StringTest] Constructor 1.2 - result = %s\n", (CS_NEW System::String(charArray, 1,4))->_toCStr());
	printf("\n");

	printf("[StringTest] operator+\n");
	s = CS_NEW(System::String);
	(*s) = (*s)+(uniChar)'H'+(uniChar)'e'+(uniChar)'l'+(uniChar)'l'+(uniChar)'o';
	s->_appendClose();
	printf("\n");

	s = CS_NEW(System::String);
	s->_appendC('H')->_appendC('e')->_appendC('l')->_appendC('l')->_appendC('o')->_appendC(' ')
	 ->_appendC('W')->_appendC('o')->_appendC('r')->_appendC('l')->_appendC('d')->_appendC('!')->_appendClose();

	// Test - Ctor + _appendC + _appendClose
	s = CS_NEW(System::String);
	s->_appendC('S')->_appendC('e')->_appendC('c')->_appendC('o')->_appendC('n')->_appendC('d')->_appendC(' ')
	 ->_appendC('H')->_appendC('e')->_appendC('l')->_appendC('l')->_appendC('o')->_appendC(' ')
	 ->_appendC('W')->_appendC('o')->_appendC('r')->_appendC('l')->_appendC('d')->_appendC('!')->_appendClose();

	// Test - _appendI
	s = CS_NEW(System::String);
	(*s)+(-1021);
	s->_appendClose();

	// Test - _appendU
	s = CS_NEW(System::String);
	s->_appendU(123)->_appendClose();

	// Test - _appendF
	s = CS_NEW(System::String);
	s->_appendC(' ')->_appendF(1234.0f)
     ->_appendC(' ')->_appendF(123456789.0f)
	 ->_appendC(' ')->_appendF(0.00123456f)
	 ->_appendClose();

	// Test - _appendS
	s = CS_NEW(System::String);
	s->_appendS(32767)->_appendClose();
	
	// Test - _appendUS
	s = CS_NEW(System::String);
	s->_appendU(42)->_appendClose();

	// Test - _appendS8
	s = CS_NEW(System::String);
	s->_appendS8(123)->_appendClose();

	// Test - _appendU8
	s = CS_NEW(System::String);
	s->_appendU8(45)->_appendClose();

	// Test - _appendB
	s = CS_NEW(System::String);
	s->_appendB(true)->_appendB(false)->_appendClose();

	// Test - _appendL
	s = CS_NEW(System::String);
	s->_appendL(9223372036854775807)->_appendClose();

	// Test - _appendUL
	s = CS_NEW(System::String);
	s->_appendUL(18446744073709551615)->_appendClose();

	// Test - _appendD
    s = CS_NEW(System::String);
	s->_appendD(123456.12345678901234567890)->_appendClose();
    
    //　Test - _appendStr
    s2 = CS_NEW(System::String);
	(*s2) = (*s2) + ' ' + ' ' + ' ' + (*s) + ' ' + ' ' + ' ';
    
    // Test - _appendCte
	a = CS_NEW(System::String);
    a->_appendCte(c_a, 5)->_appendClose();

	// Test - Operators
	// TODO

	// Test - Compare
	a = CS_NEW System::String(c_a, 5);			// "abcde"
	b = System::String::Copy(a);				// "abcde"
    c = CS_NEW System::String(c_b, 6);			// "qwerty"
    d = CS_NEW System::String(c_c, 6);			// "QWerTY"

    printf("[StringTest] Compare 1.0 - result = %i\n",	System::String::Compare(a, b));
    printf("[StringTest] Compare 1.1 - result = %i\n",	System::String::Compare(a, c));
    printf("[StringTest] Compare 1.2 - result = %i\n",	System::String::Compare(c, a));
    printf("[StringTest] Compare 1.3 - result = %i\n",	System::String::Compare(c, d));
    printf("[StringTest] Compare 1.4 - result = %i\n",	System::String::Compare(c, NULL));
    printf("[StringTest] Compare 1.5 - result = %i\n",	System::String::Compare(NULL, d));
    printf("[StringTest] Compare 1.6 - result = %i\n",	System::String::Compare(NULL, NULL));
	printf("\n");
    
    printf("[StringTest] Compare 2.0 - result = %i\n",	System::String::Compare(a, b, true));
    printf("[StringTest] Compare 2.1 - result = %i\n",	System::String::Compare(a, c, true));
    printf("[StringTest] Compare 2.2 - result = %i\n",	System::String::Compare(c, a, true));
    printf("[StringTest] Compare 2.3 - result = %i\n",	System::String::Compare(c, d, true));
    printf("[StringTest] Compare 2.4 - result = %i\n",	System::String::Compare(c, NULL, true));
    printf("[StringTest] Compare 2.5 - result = %i\n",	System::String::Compare(NULL, d, true));
    printf("[StringTest] Compare 2.6 - result = %i\n",	System::String::Compare(NULL, NULL, true));
	printf("\n");
    
    // Test - Concat
	obj = CS_NEW System::Object();
	objArray = CS_NEW System::Array<System::Object*>(2);
	objArray->_idx$_s(0, obj);
	objArray->_idx$_s(1, hw);
	strArray = CS_NEW System::Array<System::String*>(4);
	strArray->_idx$_s(0, CS_NEW System::String(c_hello, 5));
	strArray->_idx$_s(1, (CS_NEW System::String())->_appendC(' ')->_appendClose());
	strArray->_idx$_s(2, CS_NEW System::String(c_world, 5));
	strArray->_idx$_s(3, (CS_NEW System::String())->_appendC('!')->_appendClose());
	
	s = System::String::Concat(obj);
	printf("[StringTest] Concat 1.0 - result = %s\n", s->_toCStr());
	printf("\n");
	s = System::String::Concat(objArray);
	printf("[StringTest] Concat 2.0 - result = %s\n", s->_toCStr());
	printf("\n");
	s = System::String::Concat(strArray);
	printf("[StringTest] Concat 3.0 - result = %s\n", s->_toCStr());
	printf("\n");
   
	// Test - Copy
	s1 = (CS_NEW System::String())->_appendC('a')->_appendC('b')->_appendC('c')->_appendClose();	// "abc"
	s2 = (CS_NEW System::String())->_appendC('x')->_appendC('y')->_appendC('z')->_appendClose();	// "xyz"
	printf("[StringTest] Copy 1.0 - before - s1 = %s\n", s1->_toCStr());
	printf("[StringTest] Copy 1.0 - before - s2 = %s\n", s2->_toCStr());
	s2 = System::String::Copy(s1);
	printf("[StringTest] Copy 1.0 - result - s1 = %s\n", s1->_toCStr());
	printf("[StringTest] Copy 1.0 - result - s2 = %s\n", s2->_toCStr());
	printf("\n");

	// Test - Equals (static)
	a = CS_NEW System::String(c_a,5);	// "abcde"
	b = System::String::Copy(a);		// "abcde"
	c = CS_NEW System::String(c_b,6);	// "qwerty"
	d = CS_NEW System::String(c_c,6);	// "QWerTY"
	printf("[StringTest] Equals 1.0 - result = %s\n",	(System::String::Equals(a,a)) ? "True" : "False");
	printf("[StringTest] Equals 1.1 - result = %s\n",	(System::String::Equals(a,b)) ? "True" : "False");
	printf("[StringTest] Equals 1.2 - result = %s\n",	(System::String::Equals(a,c)) ? "True" : "False");
	printf("[StringTest] Equals 1.3 - result = %s\n",	(System::String::Equals(a,d)) ? "True" : "False");
	printf("\n");

	// Test - Format


	
    // Test - IsNullOrEmpty
    s = CS_NEW(System::String);
    printf("[StringTest] IsNullOrEmpty 1.0 - result = %s\n",	System::String::IsNullOrEmpty(a)	? "True" : "False");
    printf("[StringTest] IsNullOrEmpty 1.1 - result = %s\n",	System::String::IsNullOrEmpty(NULL) ? "True" : "False");
    printf("[StringTest] IsNullOrEmpty 1.2 - result = %s\n",	System::String::IsNullOrEmpty(s)	? "True" : "False");
	printf("\n");
    
	// Test - Join 
	strArray = CS_NEW System::Array<System::String*>(3);
	strArray->_idx_s(0, CS_NEW System::String(c_hello, 5));								// "Hello"
	strArray->_idx_s(1, CS_NEW System::String(c_world, 5));								// "World"
	strArray->_idx_s(2, (CS_NEW System::String())->_appendC('!')->_appendClose());		// "!"
	printf("[StringTest] Join 1.0 - result = %s\n", System::String::Join(NULL, strArray)->_toCStr());
	printf("[StringTest] Join 1.1 - result = %s\n", System::String::Join((CS_NEW System::String())->_appendC(' ')->_appendC('-')->_appendC(' ')->_appendClose(), strArray)->_toCStr());
	printf("\n");
	printf("[StringTest] Join 2.0 - result = %s\n", System::String::Join(NULL, strArray, 1, 2)->_toCStr());
	printf("[StringTest] Join 2.1 - result = %s\n", System::String::Join((CS_NEW System::String())->_appendC(' ')->_appendC('-')->_appendC(' ')->_appendClose(), strArray, 1, 2)->_toCStr());
	printf("\n");

	// Test - Clone
	s1 = (CS_NEW System::String())->_appendC('a')->_appendC('b')->_appendC('c')->_appendClose();	// "abc"
	s2 = (CS_NEW System::String())->_appendC('x')->_appendC('y')->_appendC('z')->_appendClose();	// "xyz"
	printf("[StringTest] Clone 1.0 - before - s1 = %s\n", s1->_toCStr());
	printf("[StringTest] Clone 1.0 - before - s2 = %s\n", s2->_toCStr());
	obj = s1->Clone();
	printf("[StringTest] Clone 1.0 - result - s1  = %s\n", s1->_toCStr());
	printf("[StringTest] Clone 1.0 - result - obj = %s\n", obj->ToString()->_toCStr());
	printf("\n");

    // Test - CompareTo
    a = CS_NEW System::String(c_a,5);	// "abcde"
	b = System::String::Copy(a);		// "abcde"
	c = CS_NEW System::String(c_b,6);	// "qwerty"
	d = CS_NEW System::String(c_c,6);	// "QWerTY"
	s = System::String::Empty;
	printf("[StringTest] CompareTo 1.0 - result = %i\n",	a->CompareTo((System::Object*)a));
    printf("[StringTest] CompareTo 1.1 - result = %i\n",	a->CompareTo((System::Object*)c));
    printf("\n");
    printf("[StringTest] CompareTo 2.0 - result = %i\n",	a->CompareTo(b));
    printf("[StringTest] CompareTo 2.1 - result = %i\n",	a->CompareTo(c));
    printf("[StringTest] CompareTo 2.2 - result = %i\n",	c->CompareTo(a));
    printf("[StringTest] CompareTo 2.3 - result = %i\n",	c->CompareTo(d));
    printf("[StringTest] CompareTo 2.4 - result = %i\n",	c->CompareTo((System::String*)NULL));
    printf("[StringTest] CompareTo 2.5 - result = %i\n",	s->CompareTo((System::String*)NULL));
    printf("\n");
    
    // Test - Contains
	s = System::String::Copy(hw);																// "Hello World!"
	s1 = (CS_NEW System::String())->_appendStr(hw, 1, 11)->_appendClose();						// "ello World!"
	s2 = (CS_NEW System::String())->_appendC(' ')->_appendStr(hw, 0, 12)->_appendClose();		// " Hello World!"
	s3 = (CS_NEW System::String())->_appendC('o')->_appendClose();								// "o"
	s4 = (CS_NEW System::String())->_appendC('a')->_appendClose();								// "a"
	printf("[StringTest] Contains 1.0 - result = %s\n",	s->Contains(hw) ? "True" : "False");
	printf("[StringTest] Contains 1.1 - result = %s\n",	s->Contains(s1) ? "True" : "False");
	printf("[StringTest] Contains 1.2 - result = %s\n",	s->Contains(s2) ? "True" : "False");
	printf("[StringTest] Contains 1.3 - result = %s\n",	s->Contains(s3) ? "True" : "False");
	printf("[StringTest] Contains 1.4 - result = %s\n",	s->Contains(s4) ? "True" : "False");
	printf("\n");

	// Test - CopyTo
	charArray = CS_NEW System::Array<uniChar>(7);
	charArray->_idx$_s(0, 'I');
	charArray->_idx$_s(1, 'n');
	charArray->_idx$_s(2, 'i');
	charArray->_idx$_s(3, 't');
	charArray->_idx$_s(4, 'i');
	charArray->_idx$_s(5, 'a');
	charArray->_idx$_s(6, 'l');
	s = (CS_NEW System::String())->_appendC('M')->_appendC('o')->_appendC('d')->_appendC('i')->_appendC('f')->_appendC('i')->_appendC('e')->_appendC('d')->_appendClose();
	printf("[StringTest] CopyTo 1.0 - initial char array = ");
	DisplayUniCharArray(charArray);
	printf("\n");
	s->CopyTo(0, charArray, 0, s->_acc_gLength() - 1);
	printf("[StringTest] CopyTo - base string = %s\n", s->_toCStr());
	printf("[StringTest] CopyTo 1.0 - result = ");	DisplayUniCharArray(charArray);	printf("\n");
	s->CopyTo(2, charArray, 4, 1);
	printf("[StringTest] CopyTo 1.1 - result = ");	DisplayUniCharArray(charArray);	printf("\n");
	printf("\n");

	// Test - EndsWith
	s = System::String::Copy(hw);
	s1 = (CS_NEW System::String())->_appendCte(c_world, 5)->_appendC('!')->_appendClose();		// "World!"
	s2 = (CS_NEW System::String(c_world, 5));													// "World"
	printf("[StringTest] EndsWith 1.0 - result = %s\n",	s->EndsWith(s1) ? "True" : "False");
	printf("[StringTest] EndsWith 1.1 - result = %s\n",	s->EndsWith(s2) ? "True" : "False");
	printf("\n");

	// Test - Equals
	const uniChar _obj_str[] =			{'S','y','s','t','e','m','.','O','b','j','e','c','t'};
	const uniChar _obj_str_upper[] =	{'S','Y','S','T','E','M','.','O','B','J','E','C','T'};
	s	= CS_NEW System::String(_obj_str, 13);
	s2	= CS_NEW System::String(_obj_str_upper, 13);
	obj = CS_NEW System::Object();
	printf("[StringTest] Equals 1.0 - result = %s\n", s->Equals(obj) ? "True" : "False");
	printf("\n");
	printf("[StringTest] Equals 2.0 - result = %s\n", s->Equals(obj->ToString()) ? "True" : "False");
	printf("\n");
	// TODO
	/*printf("[StringTest] Equals 3.0 - result = %s\n", s->Equals(s2) ? "True" : "False");
	printf("[StringTest] Equals 3.0 - result = %s\n",	s->Equals(s2) ? "True" : "False");
	printf("\n");*/

	// Test - GetHashCode
	s = System::String::Copy(hw);
	printf("[StringTest] GetHashCode - result = %i\n", s->GetHashCode());
	printf("\n");

	// Test - IndexOf
	s = System::String::Copy(hw);
	printf("[StringTest] IndexOf 1.0 - result = %i\n",	s->IndexOf('a'));
	printf("[StringTest] IndexOf 1.1 - result = %i\n",	s->IndexOf('o'));
	printf("[StringTest] IndexOf 1.2 - result = %i\n",	s->IndexOf('O'));
	printf("\n");
	printf("[StringTest] IndexOf 2.0 - result = %i\n",	s->IndexOf((CS_NEW System::String())->_appendC('t')->_appendClose()));					// "t"
	printf("[StringTest] IndexOf 2.1 - result = %i\n",	s->IndexOf((CS_NEW System::String())->_appendC('l')->_appendC('l')->_appendClose()));	// "ll"
	printf("\n");
	printf("[StringTest] IndexOf 3.0 - result = %i\n",	s->IndexOf('t', 5));
	printf("[StringTest] IndexOf 3.1 - result = %i\n",	s->IndexOf('o', 5));
	printf("[StringTest] IndexOf 3.2 - result = %i\n",	s->IndexOf('o', 9));
	printf("\n");
	printf("[StringTest] IndexOf 4.0 - result = %i\n",	s->IndexOf((CS_NEW System::String())->_appendC('t')->_appendClose(), 5));
	printf("[StringTest] IndexOf 4.1 - result = %i\n",	s->IndexOf((CS_NEW System::String())->_appendC('o')->_appendClose(), 5));
	printf("[StringTest] IndexOf 4.2 - result = %i\n",	s->IndexOf((CS_NEW System::String())->_appendC('o')->_appendClose(), 9));
	printf("\n");
	printf("[StringTest] IndexOf 5.0 - result = %i\n",	s->IndexOf('t', 2, 3));
	printf("[StringTest] IndexOf 5.1 - result = %i\n",	s->IndexOf('o', 2, 3));
	printf("[StringTest] IndexOf 5.2 - result = %i\n",	s->IndexOf('o', 2, 1));
	printf("\n");
	printf("[StringTest] IndexOf 6.0 - result = %i\n",	s->IndexOf((CS_NEW System::String())->_appendC('t')->_appendClose(), 2, 3));
	printf("[StringTest] IndexOf 6.1 - result = %i\n",	s->IndexOf((CS_NEW System::String())->_appendC('o')->_appendClose(), 2, 3));
	printf("[StringTest] IndexOf 6.2 - result = %i\n",	s->IndexOf((CS_NEW System::String())->_appendC('o')->_appendClose(), 2, 1));
	printf("\n");

	// Test - IndexOfAny
	s = System::String::Copy(hw);
	charArray = CS_NEW System::Array<uniChar>(2);
	charArray->_idx$_s(0, 'a');
	charArray->_idx$_s(1, 'b');
	charArray2 = CS_NEW System::Array<uniChar>(4);
	charArray2->_idx$_s(0, 'a');
	charArray2->_idx$_s(1, 'b');
	charArray2->_idx$_s(2, 'o');
	charArray2->_idx$_s(3, 'l');
	printf("[StringTest] IndexOfAny 1.0 - result = %i\n",	s->IndexOfAny(charArray));
    printf("[StringTest] IndexOfAny 1.1 - result = %i\n",	s->IndexOfAny(charArray2));
    printf("\n");
    printf("[StringTest] IndexOfAny 2.0 - result = %i\n",	s->IndexOfAny(charArray, 5));
    printf("[StringTest] IndexOfAny 2.1 - result = %i\n",	s->IndexOfAny(charArray2, 5));
    printf("\n");
    printf("[StringTest] IndexOfAny 3.0 - result = %i\n",	s->IndexOfAny(charArray, 5, 1));
    printf("[StringTest] IndexOfAny 3.1 - result = %i\n",	s->IndexOfAny(charArray2, 5, 1));
	printf("[StringTest] IndexOfAny 3.2 - result = %i\n",	s->IndexOfAny(charArray2, 5, 3));
	printf("\n");

	// Test - Insert
	s =		(CS_NEW System::String())->_appendC('H')->_appendC('e')->_appendC('o')->_appendC('r')->_appendC('l')->_appendC('d')->_appendC('!')->_appendClose();	// "Heorld!"
	s1 =	(CS_NEW System::String())->_appendC('l')->_appendC('l')->_appendC('o')->_appendC(' ')->_appendC('W')->_appendClose();								// "llo W"
	printf("[StringTest] Insert 1.0 - before = %s\n",	s->_toCStr());
	printf("[StringTest] Insert 1.0 - result = %s\n",	s->Insert(2, s1)->_toCStr());
	printf("\n");

	// Test - LastIndexOf
	s	= System::String::Copy(hw);
	s1	= (CS_NEW System::String())->_appendC('t')->_appendClose();
	s2	= (CS_NEW System::String())->_appendC('o')->_appendClose();
    printf("[StringTest] LastIndexOf 1.0 - result = %i\n",	s->LastIndexOf('a'));
    printf("[StringTest] LastIndexOf 1.1 - result = %i\n",	s->LastIndexOf('o'));
    printf("[StringTest] LastIndexOf 1.2 - result = %i\n",	s->LastIndexOf('O'));
    printf("\n");
    printf("[StringTest] LastIndexOf 1.0 - result = %i\n",	s->LastIndexOf(s1));
    printf("[StringTest] LastIndexOf 2.1 - result = %i\n",	s->LastIndexOf(s2));
    printf("\n");
    printf("[StringTest] LastIndexOf 3.0 - result = %i\n",	s->LastIndexOf(s1, 5));
    printf("[StringTest] LastIndexOf 3.1 - result = %i\n",	s->LastIndexOf(s2, 5));
    printf("[StringTest] LastIndexOf 3.2 - result = %i\n",	s->LastIndexOf(s2, 9));
    printf("\n");
    printf("[StringTest] LastIndexOf 4.0 - result = %i\n",	s->LastIndexOf(s1, 5));
    printf("[StringTest] LastIndexOf 4.1 - result = %i\n",	s->LastIndexOf(s2, 5));
    printf("[StringTest] LastIndexOf 4.2 - result = %i\n",	s->LastIndexOf(s2, 9));
    printf("\n");
    printf("[StringTest] LastIndexOf 5.0 - result = %i\n",	s->LastIndexOf('t', 9, 3));
    printf("[StringTest] LastIndexOf 5.1 - result = %i\n",	s->LastIndexOf('o', 9, 3));
    printf("[StringTest] LastIndexOf 5.2 - result = %i\n",	s->LastIndexOf('o', 9, 1));
    printf("\n");
    printf("[StringTest] LastIndexOf 6.0 - result = %i\n",	s->LastIndexOf(s1, 9, 3));
    printf("[StringTest] LastIndexOf 6.1 - result = %i\n",	s->LastIndexOf(s2, 9, 3));
    printf("[StringTest] LastIndexOf 6.2 - result = %i\n",	s->LastIndexOf(s2, 9, 1));
    printf("\n");

	// Test - LastIndexOfany
	s = System::String::Copy(hw);
	charArray = CS_NEW System::Array<uniChar>(2);
	charArray->_idx$_s(0, 'a');
	charArray->_idx$_s(1, 'b');
	charArray2 = CS_NEW System::Array<uniChar>(4);
	charArray2->_idx$_s(0, 'a');
	charArray2->_idx$_s(1, 'b');
	charArray2->_idx$_s(2, 'o');
	charArray2->_idx$_s(3, 'l');
	printf("[StringTest] LastIndexOfAny 1.0 - result = %i\n",	s->LastIndexOfAny(charArray));
    printf("[StringTest] LastIndexOfAny 1.1 - result = %i\n",	s->LastIndexOfAny(charArray2));
    printf("\n");
    printf("[StringTest] LastIndexOfAny 2.0 - result = %i\n",	s->LastIndexOfAny(charArray, 6));
    printf("[StringTest] LastIndexOfAny 2.1 - result = %i\n",	s->LastIndexOfAny(charArray2, 6));
    printf("\n");
    printf("[StringTest] LastIndexOfAny 3.0 - result = %i\n",	s->LastIndexOfAny(charArray, 9, 1));
    printf("[StringTest] LastIndexOfAny 3.1 - result = %i\n",	s->LastIndexOfAny(charArray2, 9, 1));
    printf("[StringTest] LastIndexOfAny 3.2 - result = %i\n",	s->LastIndexOfAny(charArray2, 6, 3));
    printf("\n");

	// Test - PadLeft
	s = System::String::Copy(hw);
	printf("[StringTest] PadLeft 1.0 - before = |%s|\n",	s->_toCStr());
	printf("[StringTest] PadLeft 1.0 - result = |%s|\n",	s->PadLeft(0)->_toCStr());
    printf("[StringTest] PadLeft 1.1 - before = |%s|\n",	s->_toCStr());
	printf("[StringTest] PadLeft 1.1 - result = |%s|\n",	s->PadLeft(15)->_toCStr());
    printf("\n");
    printf("[StringTest] PadLeft 2.0 - before = |%s|\n",	s->_toCStr());
    printf("[StringTest] PadLeft 2.0 - result = |%s|\n",	s->PadLeft(0, '-')->_toCStr());
	printf("[StringTest] PadLeft 2.1 - before = |%s|\n",	s->_toCStr());
    printf("[StringTest] PadLeft 2.1 - result = |%s|\n",	s->PadLeft(15, '-')->_toCStr());
    printf("\n");

	// Test - PadRight
	s = System::String::Copy(hw);
	printf("[StringTest] PadRight 1.0 - before = |%s|\n",	s->_toCStr());
	printf("[StringTest] PadRight 1.0 - result = |%s|\n",	s->PadRight(0)->_toCStr());
	printf("[StringTest] PadRight 1.1 - before = |%s|\n",	s->_toCStr());
    printf("[StringTest] PadRight 1.1 - result = |%s|\n",	s->PadRight(15)->_toCStr());
    printf("\n");
    printf("[StringTest] PadRight 2.0 - before = |%s|\n",	s->_toCStr());
    printf("[StringTest] PadRight 2.0 - result = |%s|\n",	s->PadRight(0, '-')->_toCStr());
	printf("[StringTest] PadRight 2.1 - before = |%s|\n",	s->_toCStr());
    printf("[StringTest] PadRight 2.1 - result = |%s|\n",	s->PadRight(15, '-')->_toCStr());
    printf("\n");

	// Test - Remove
	s = System::String::Copy(hw);
	printf("[StringTest] Remove 1.0 - before = %s\n",	s->_toCStr());
	printf("[StringTest] Remove 1.0 - result = %s\n",	s->Remove(5)->_toCStr());
	printf("\n");
	printf("[StringTest] Remove 2.0 - before = %s\n",	s->_toCStr());
	printf("[StringTest] Remove 2.0 - result = %s\n",	s->Remove(5, 1)->_toCStr());
	printf("\n");

	// Test - Replace	
	s = CS_NEW System::String(c_digits, 11);
	s1 = (CS_NEW System::String())->_appendC('1')->_appendC(' ')->_appendC('2')->_appendC(' ')->_appendC('a')->_appendClose();
	s2 = (CS_NEW System::String())->_appendC('1')->_appendC(' ')->_appendC('2')->_appendClose();
	s3 = (CS_NEW System::String())->_appendC('@')->_appendC('_')->_appendC('@')->_appendClose();
	printf("[StringTest] Replace 1.0 - before = %s\n", s->_toCStr());
	printf("[StringTest] Replace 1.0 - result = %s\n", s->Replace('a', '-')->_toCStr());
	s = CS_NEW System::String(c_digits, 11);
	printf("[StringTest] Replace 1.1 - before = %s\n", s->_toCStr());
	printf("[StringTest] Replace 1.1 - result = %s\n", s->Replace(' ', '-')->_toCStr());
	printf("\n");
	s = CS_NEW System::String(c_digits, 11);
	printf("[StringTest] Replace 2.0 - before = %s\n", s->_toCStr());
	printf("[StringTest] Replace 2.0 - result = %s\n", s->Replace(s1, s3)->_toCStr());
	s = CS_NEW System::String(c_digits, 11);
	printf("[StringTest] Replace 2.1 - before = %s\n", s->_toCStr());
	printf("[StringTest] Replace 2.1 - result = %s\n", s->Replace(s2, s3)->_toCStr());
	printf("\n");

	// Test - Split
	charArray = CS_NEW System::Array<uniChar>(2);			// {' ','2'}
	charArray->_idx$_s(0, ' ');
	charArray->_idx$_s(1, '2');
	charArray2 = CS_NEW System::Array<uniChar>(1);			// {'a'}
	charArray2->_idx$_s(0,'a');
	strArray = CS_NEW System::Array<System::String*>(2);	// {"2","3"}
	strArray->_idx$_s(0, (CS_NEW System::String())->_appendC('2')->_appendC(' ')->_appendClose());
	strArray->_idx$_s(1, (CS_NEW System::String())->_appendC('3')->_appendClose());

	s = CS_NEW System::String(c_digits, 11);
	printf("[StringTest] Split 1.0 - before = %s\n", s->_toCStr());
	printf("[StringTest] Split 1.0 - result = ");	DisplayArray(s->Split(charArray2));	printf("\n");

	s = CS_NEW System::String(c_digits, 11);
	printf("[StringTest] Split 1.1 - before = %s\n", s->_toCStr());
	printf("[StringTest] Split 1.1 - result = ");	DisplayArray(s->Split(NULL));		printf("\n");
	
	s = CS_NEW System::String(c_digits, 11);
	printf("[StringTest] Split 1.2 - before = %s\n", s->_toCStr());	
	printf("[StringTest] Split 1.2 - result = ");	DisplayArray(s->Split(charArray));	printf("\n");
	printf("\n");

	s = CS_NEW System::String(c_digits, 11);
	printf("[StringTest] Split 2.0 - before = %s\n", s->_toCStr());
	printf("[StringTest] Split 2.0 - result = ");	DisplayArray(s->Split(charArray, 3));	printf("\n");
	printf("\n");

	s = CS_NEW System::String(c_digits, 11);
	printf("[StringTest] Split 3.0 - before = %s\n", s->_toCStr());
	printf("[StringTest] Split 3.0 - result = ");	DisplayArray(s->Split(charArray, System::StringSplitOptions::None));					printf("\n");

	s = CS_NEW System::String(c_digits, 11);
	printf("[StringTest] Split 3.1 - before = %s\n", s->_toCStr());
	printf("[StringTest] Split 3.1 - result = ");	DisplayArray(s->Split(charArray, System::StringSplitOptions::RemoveEmptyEntries));		printf("\n");
	printf("\n");

	s = CS_NEW System::String(c_digits, 11);
	printf("[StringTest] Split 4.0 - before = %s\n", s->_toCStr());
	printf("[StringTest] Split 4.0 - result = ");	DisplayArray(s->Split(strArray, System::StringSplitOptions::None));						printf("\n");

	s = CS_NEW System::String(c_digits, 11);
	printf("[StringTest] Split 4.1 - before = %s\n", s->_toCStr());
	printf("[StringTest] Split 4.1 - result = ");	DisplayArray(s->Split(strArray, System::StringSplitOptions::RemoveEmptyEntries));		printf("\n");
	printf("\n");
	
	s = CS_NEW System::String(c_digits, 11);
	printf("[StringTest] Split 5.0 - before = %s\n", s->_toCStr());
	printf("[StringTest] Split 5.0 - result = ");	DisplayArray(s->Split(charArray, 3, System::StringSplitOptions::None));					printf("\n");

	s = CS_NEW System::String(c_digits, 11);
	printf("[StringTest] Split 5.1 - before = %s\n", s->_toCStr());
	printf("[StringTest] Split 5.1 - result = ");	DisplayArray(s->Split(charArray, 3, System::StringSplitOptions::RemoveEmptyEntries));	printf("\n");
	printf("\n");

	s = CS_NEW System::String(c_digits, 11);
	printf("[StringTest] Split 6.0 - before = %s\n", s->_toCStr());
	printf("[StringTest] Split 6.0 - result = ");	DisplayArray(s->Split(strArray, 2, System::StringSplitOptions::None));					printf("\n");

	s = CS_NEW System::String(c_digits, 11);
	printf("[StringTest] Split 6.1 - before = %s\n", s->_toCStr());
	printf("[StringTest] Split 6.1 - result = ");	DisplayArray(s->Split(strArray, 2, System::StringSplitOptions::RemoveEmptyEntries));	printf("\n");
	printf("\n");

	// Test - StartsWith
	s = System::String::Copy(hw);
	s1 = (CS_NEW System::String())->_appendC('h')->_appendC('e')->_appendC('l')->_appendC('l')->_appendC('o')->_appendClose();
	printf("[StringTest] StartsWith 1.0 - result = %s\n",	s->StartsWith(s1) ? "True" : "False");
	printf("[StringTest] StartsWith 1.1 - result = %s\n",	s->StartsWith(s)  ? "True" : "False");
	printf("\n");

	// Test Substring
	s = System::String::Copy(hw);
	printf("[StringTest] Substring 1.0 - result = %s\n",	s->Substring(0)->_toCStr());
    printf("[StringTest] Substring 1.1 - result = %s\n",	s->Substring(6)->_toCStr());		printf("\n");
    printf("[StringTest] Substring 2.0 - result = %s\n",	s->Substring(6,5)->_toCStr());		printf("\n");

	// Test - ToCharArray
	s = System::String::Copy(hw);
	printf("[StringTest] ToCharArray 1.0 - result = ");	DisplayUniCharArray(s->ToCharArray());		printf("\n");
	printf("\n");
    printf("[StringTest] ToCharArray 2.0 - result = "); DisplayUniCharArray(s->ToCharArray(6,5));	printf("\n");
	printf("\n");

	// Test - ToLower
	s = System::String::Copy(hw);
	printf("[StringTest] ToLower 1.0 - before = %s\n", s->_toCStr());
	printf("[StringTest] ToLower 1.0 - result = %s\n", s->ToLower()->_toCStr());
	printf("\n");

	// Test - ToString
	s = System::String::Copy(hw);
	printf("[StringTest] ToString 1.0 - result = %s\n", s->ToString()->_toCStr());
	printf("\n");

	// Test - ToUpper
	s = System::String::Copy(hw);
	printf("[StringTest] ToUpper 1.0 - before = %s\n", s->_toCStr());
	printf("[StringTest] ToUpper 1.0 - result = %s\n", s->ToUpper()->_toCStr());
	printf("\n");

	// Test - Trim
	s = CS_NEW System::String(c_hw_toTrim, 27);
	charArray = CS_NEW System::Array<uniChar>(3);
	charArray->_idx$_s(0, ' ');
	charArray->_idx$_s(1, 'H');
	charArray->_idx$_s(2, '!');
	printf("[StringTest] Trim 1.0 - before = |%s|\n",	s->_toCStr());
	printf("[StringTest] Trim 1.0 - result = |%s|\n",	s->Trim()->_toCStr());
	printf("\n");
	printf("[StringTest] Trim 2.0 - before = |%s|\n",	s->_toCStr());
	printf("[StringTest] Trim 2.0 - result = |%s|\n",	s->Trim(charArray)->_toCStr());
	printf("\n");

	// Test - TrimEnd
	s = CS_NEW System::String(c_hw_toTrim, 27);
	charArray = CS_NEW System::Array<uniChar>(3);
	charArray->_idx$_s(0, ' ');
	charArray->_idx$_s(1, 'H');
	charArray->_idx$_s(2, '!');
	printf("[StringTest] TrimEnd 1.0 - before = |%s|\n",	s->_toCStr());
	printf("[StringTest] TrimEnd 1.0 - result = |%s|\n",	s->TrimEnd()->_toCStr());
	printf("\n");
	printf("[StringTest] TrimEnd 2.0 - before = |%s|\n",	s->_toCStr());
	printf("[StringTest] TrimEnd 2.0 - result = |%s|\n",	s->TrimEnd(charArray)->_toCStr());
	printf("\n");

	// Test - TrimStart
	s = CS_NEW System::String(c_hw_toTrim, 27);
	charArray = CS_NEW System::Array<uniChar>(3);
	charArray->_idx$_s(0, ' ');
	charArray->_idx$_s(1, 'H');
	charArray->_idx$_s(2, '!');
	printf("[StringTest] TrimStart 1.0 - before = |%s|\n",	s->_toCStr());
	printf("[StringTest] TrimStart 1.0 - result = |%s|\n",	s->TrimStart()->_toCStr());
	printf("\n");
	printf("[StringTest] TrimStart 2.0 - before = |%s|\n",	s->_toCStr());
	printf("[StringTest] TrimStart 2.0 - result = |%s|\n",	s->TrimStart(charArray)->_toCStr());
	printf("\n");
	
	//#########################################
	//#########################################
	//############## List Tests ###############
	//#########################################
	//#########################################
	
	printf("#########################################\n");
	printf("#########################################\n");
	printf("############## List Tests ###############\n");
	printf("#########################################\n");
	printf("#########################################\n");
	printf("\n\n");

	// Test - Ctor
	intList = CS_NEW System::Collections::Generic::List<s32>(3);
	strList = CS_NEW System::Collections::Generic::List<System::String*>();

	printf("[ListTest] Constructor 1.0 - result = "); DisplayListInfos(intList); printf("\n");
	printf("[ListTest] Constructor 2.0 - result = "); DisplayListInfos(strList); printf("\n");
	printf("\n");

	// Test - Add
	printf("[ListTest] Add 1.0 - before = "); DisplayListInfos(intList); printf("\n");
    printf("[ListTest] Add 1.0 - before = "); DisplayList(intList);      printf("\n");
    for(int i = 0; i < 16; ++i)
        intList->Add(i);
    printf("[ListTest] Add 1.0 - result = "); DisplayListInfos(intList); printf("\n");
    printf("[ListTest] Add 1.0 - result = "); DisplayList(intList);      printf("\n");
            
    printf("[ListTest] Add 1.1 - before = "); DisplayListInfos(strList); printf("\n");
    printf("[ListTest] Add 1.1 - before = "); DisplayList(strList);      printf("\n");
    for(int i = 0; i < 16; ++i)
        strList->Add((CS_NEW System::String())->_appendC('H')->_appendC('i')->_appendClose());
    printf("[ListTest] Add 1.1 - result = "); DisplayListInfos(strList); printf("\n");
    printf("[ListTest] Add 1.1 - result = "); DisplayList(strList);      printf("\n");
    printf("\n");

	// Test - AddRange


	// Test - AsReadOnly


	// Test - BinarySearch
	intList = CS_NEW System::Collections::Generic::List<s32>();
    strList = CS_NEW System::Collections::Generic::List<System::String*>();
    for(int i = 0; i < 8; ++i) {
        intList->Add(i*2);
        strList->Add((CS_NEW System::String())->_appendC('s')->_appendC('t')->_appendC('r')->_appendI(i*2)->_appendClose());
    }
    printf("[ListTest] BinarySearch 1.0+ - infos = "); DisplayListInfos(intList);    printf("\n");
    printf("[ListTest] BinarySearch 1.0+ - infos = "); DisplayList(intList);         printf("\n");
    printf("[ListTest] BinarySearch 1.0 - result = %i\n", intList->BinarySearch(4));
    printf("[ListTest] BinarySearch 1.1 - result = %i\n", intList->BinarySearch(42));
    printf("[ListTest] BinarySearch 1.3 - result = %i\n", intList->BinarySearch(7));
    printf("[ListTest] BinarySearch 1.4+ - infos = "); DisplayListInfos(strList);    printf("\n");
    printf("[ListTest] BinarySearch 1.4+ - infos = "); DisplayList(strList);         printf("\n"); 
    printf("[ListTest] BinarySearch 1.4 - result = %i\n", strList->BinarySearch((CS_NEW System::String())->_appendC('s')->_appendC('t')->_appendC('r')->_appendI(4)->_appendClose()));
    printf("[ListTest] BinarySearch 1.5 - result = %i\n", strList->BinarySearch((CS_NEW System::String())->_appendC('s')->_appendC('t')->_appendC('r')->_appendI(42)->_appendClose()));
    printf("[ListTest] BinarySearch 1.6 - result = %i\n", strList->BinarySearch((CS_NEW System::String())->_appendC('s')->_appendC('t')->_appendC('r')->_appendI(7)->_appendClose()));
    printf("\n");
    // TODO 2 et 3

	// Test - Clear
	intList = CS_NEW System::Collections::Generic::List<s32>();
    strList = CS_NEW System::Collections::Generic::List<System::String*>();
    for(int i = 0; i < 8; ++i) {
        intList->Add(i*2);
        strList->Add((CS_NEW System::String())->_appendC('s')->_appendC('t')->_appendC('r')->_appendI(i*2)->_appendClose());
    }
	printf("[ListTest] Clear 1.0 - infos = ");	DisplayListInfos(intList);  printf("\n");
    printf("[ListTest] Clear 1.0 - infos = ");	DisplayList(intList);       printf("\n");
    intList->Clear();
    printf("[ListTest] Clear 1.0 - result = "); DisplayListInfos(intList);	printf("\n");
    printf("[ListTest] Clear 1.0 - result = "); DisplayList(intList);       printf("\n");
            
    printf("[ListTest] Clear 1.1 - infos = ");  DisplayListInfos(strList);  printf("\n");
    printf("[ListTest] Clear 1.1 - infos = ");  DisplayList(strList);       printf("\n");
    strList->Clear();
    printf("[ListTest] Clear 1.1 - result = "); DisplayListInfos(strList);  printf("\n");
    printf("[ListTest] Clear 1.1 - result = "); DisplayList(strList);       printf("\n");
    printf("\n");

	// Test - Contains
	intList = CS_NEW System::Collections::Generic::List<s32>();
    strList = CS_NEW System::Collections::Generic::List<System::String*>();
    for(int i = 0; i < 8; ++i) {
        intList->Add(i*2);
        strList->Add((CS_NEW System::String())->_appendC('s')->_appendC('t')->_appendC('r')->_appendI(i*2)->_appendClose());
    }
	printf("[ListTest] Contains 1.0+ - infos = ");   DisplayListInfos(intList);    printf("\n");
    printf("[ListTest] Contains 1.0+ - infos = ");   DisplayList(intList);         printf("\n");
    printf("[ListTest] Contains 1.0 - result = %s\n", (intList->Contains(6)) ? "True":"False");
    printf("[ListTest] Contains 1.1 - result = %s\n", (intList->Contains(7)) ? "True":"False");
    printf("[ListTest] Contains 1.2+ - infos = ");   DisplayListInfos(strList);    printf("\n");
    printf("[ListTest] Contains 1.2+ - infos = ");   DisplayList(strList);         printf("\n");
    printf("[ListTest] Contains 1.2 - result = %s\n", (strList->Contains((CS_NEW System::String())->_appendC('s')->_appendC('t')->_appendC('r')->_appendI(6)->_appendClose())) ? "True":"False");
    printf("[ListTest] Contains 1.3 - result = %s\n", (strList->Contains((CS_NEW System::String())->_appendC('s')->_appendC('t')->_appendC('r')->_appendI(7)->_appendClose())) ? "True":"False");
    printf("\n");

	// Test - ConvertAll


	// Test CopyTo
	intList = CS_NEW System::Collections::Generic::List<s32>();
    strList = CS_NEW System::Collections::Generic::List<System::String*>();
    for(int i = 0; i < 5; ++i) {
        intList->Add(i*2);
        strList->Add((CS_NEW System::String())->_appendC('s')->_appendC('t')->_appendC('r')->_appendI(i*2)->_appendClose());
    }
    intArray = CS_NEW System::Array<int>(20);
    strArray = CS_NEW System::Array<System::String*>(20);
    printf("[ListTest] CopyTo 1.0+ - infos  = ");    DisplayListInfos(intList);  printf("\n");
    printf("[ListTest] CopyTo 1.0+ - infos  = ");    DisplayList(intList);       printf("\n");
    intList->CopyTo(intArray);
    printf("[ListTest] CopyTo 1.0 - result = ");     DisplayArray(intArray);     printf("\n");
    printf("[ListTest] CopyTo 1.1+ - infos  = ");    DisplayListInfos(strList);  printf("\n");
    printf("[ListTest] CopyTo 1.1+ - infos  = ");    DisplayList(strList);       printf("\n");
    strList->CopyTo(strArray);
    printf("[ListTest] CopyTo 1.1 - result = ");     DisplayArray(strArray);     printf("\n");
    intList->CopyTo(intArray, 6);
    printf("[ListTest] CopyTo 2.0 - result = ");     DisplayArray(intArray);     printf("\n");
    strList->CopyTo(strArray, 6);
    printf("[ListTest] CopyTo 2.1 - result = ");     DisplayArray(strArray);     printf("\n");
    intList->CopyTo(1, intArray, 13, 3);
    printf("[ListTest] CopyTo 2.0 - result = ");     DisplayArray(intArray);     printf("\n");
    strList->CopyTo(3, strArray, 15, 2);
    printf("[ListTest] CopyTo 2.1 - result = ");     DisplayArray(strArray);     printf("\n");
    printf("\n");

	// Test - Exists


	// Test - Find


	// Test - FindAll


	// Test - FindIndex


	// Test - FindLast


	// Test - FindLastIndex


	// Test - Foreach


	// Test - GetEnumerator

	
	// Test - GetRange
	intList = CS_NEW System::Collections::Generic::List<s32>();
    strList = CS_NEW System::Collections::Generic::List<System::String*>();
    for(int i = 0; i < 8; ++i) {
        intList->Add(i*2);
        strList->Add((CS_NEW System::String())->_appendC('s')->_appendC('t')->_appendC('r')->_appendI(i*2)->_appendClose());
    }
	intList2 = intList->GetRange(3,3);
    strList2 = strList->GetRange(3,3);
    printf("[ListTest] GetRange 1.0 - infos  = ");   DisplayListInfos(intList);    printf("\n");
    printf("[ListTest] GetRange 1.0 - infos  = ");   DisplayList(intList);         printf("\n");
    printf("[ListTest] GetRange 1.0 - result = ");   DisplayListInfos(intList2);   printf("\n");
    printf("[ListTest] GetRange 1.0 - result = ");   DisplayList(intList2);        printf("\n");
    printf("[ListTest] GetRange 1.1 - infos  = ");   DisplayListInfos(strList);    printf("\n");
    printf("[ListTest] GetRange 1.1 - infos  = ");   DisplayList(strList);         printf("\n");
    printf("[ListTest] GetRange 1.1 - result = ");   DisplayListInfos(strList2);   printf("\n");
    printf("[ListTest] GetRange 1.1 - result = ");   DisplayList(strList2);        printf("\n");
    printf("\n");
	
	// Test - IndexOf
	intList = CS_NEW System::Collections::Generic::List<s32>();
    strList = CS_NEW System::Collections::Generic::List<System::String*>();
    for(int i = 0; i < 8; ++i) {
        intList->Add(i*2);
        strList->Add((CS_NEW System::String())->_appendC('s')->_appendC('t')->_appendC('r')->_appendI(i*2)->_appendClose());
    }
	printf("[ListTest] IndexOf 1.0+ - infos = ");   DisplayListInfos(intList);    printf("\n");
    printf("[ListTest] IndexOf 1.0+ - infos = ");   DisplayList(intList);         printf("\n");
    printf("[ListTest] IndexOf 1.0 - result = %i\n", intList->IndexOf(4));
    printf("[ListTest] IndexOf 1.1 - result = %i\n", intList->IndexOf(5));
    printf("[ListTest] IndexOf 1.2+ - infos = ");   DisplayListInfos(strList);    printf("\n");
    printf("[ListTest] IndexOf 1.2+ - infos = ");   DisplayList(strList);         printf("\n");
    printf("[ListTest] IndexOf 1.2 - result = %i\n", strList->IndexOf((CS_NEW System::String())->_appendC('s')->_appendC('t')->_appendC('r')->_appendI(4)->_appendClose()));
    printf("[ListTest] IndexOf 1.3 - result = %i\n", strList->IndexOf((CS_NEW System::String())->_appendC('s')->_appendC('t')->_appendC('r')->_appendI(5)->_appendClose()));
    printf("\n");
    printf("[ListTest] IndexOf 2.0 - result = %i\n", intList->IndexOf(4, 0));
    printf("[ListTest] IndexOf 2.1 - result = %i\n", intList->IndexOf(4, 4));
    printf("[ListTest] IndexOf 2.2 - result = %i\n", intList->IndexOf(5, 0));
    printf("[ListTest] IndexOf 2.3 - result = %i\n", strList->IndexOf((CS_NEW System::String())->_appendC('s')->_appendC('t')->_appendC('r')->_appendI(4)->_appendClose(), 0));
    printf("[ListTest] IndexOf 2.4 - result = %i\n", strList->IndexOf((CS_NEW System::String())->_appendC('s')->_appendC('t')->_appendC('r')->_appendI(4)->_appendClose(), 4));
    printf("[ListTest] IndexOf 2.5 - result = %i\n", strList->IndexOf((CS_NEW System::String())->_appendC('s')->_appendC('t')->_appendC('r')->_appendI(5)->_appendClose(), 0));
    printf("\n");
    printf("[ListTest] IndexOf 2.0 - result = %i\n", intList->IndexOf(4, 0, 1));
    printf("[ListTest] IndexOf 2.1 - result = %i\n", intList->IndexOf(4, 0, 4));
    printf("[ListTest] IndexOf 2.2 - result = %i\n", intList->IndexOf(5, 0, 8));
    printf("[ListTest] IndexOf 2.3 - result = %i\n", strList->IndexOf((CS_NEW System::String())->_appendC('s')->_appendC('t')->_appendC('r')->_appendI(4)->_appendClose(), 0, 1));
    printf("[ListTest] IndexOf 2.4 - result = %i\n", strList->IndexOf((CS_NEW System::String())->_appendC('s')->_appendC('t')->_appendC('r')->_appendI(4)->_appendClose(), 0, 4));
    printf("[ListTest] IndexOf 2.5 - result = %i\n", strList->IndexOf((CS_NEW System::String())->_appendC('s')->_appendC('t')->_appendC('r')->_appendI(5)->_appendClose(), 0, 8));
    printf("\n");
	
	// Test - Insert
	intList = CS_NEW System::Collections::Generic::List<s32>();
    strList = CS_NEW System::Collections::Generic::List<System::String*>();
    for(int i = 0; i < 8; ++i) {
        intList->Add(i*2);
        strList->Add((CS_NEW System::String())->_appendC('s')->_appendC('t')->_appendC('r')->_appendI(i*2)->_appendClose());
    }
	printf("[ListTest] Insert 1.0 - infos  = ");   DisplayListInfos(intList);    printf("\n");
    printf("[ListTest] Insert 1.0 - infos  = ");   DisplayList(intList);         printf("\n");
    intList->Insert(4,7);
    intList->Insert(0,-1);
    intList->Insert(10,20);
    printf("[ListTest] Insert 1.0 - result = ");   DisplayListInfos(intList);    printf("\n");
    printf("[ListTest] Insert 1.0 - result = ");   DisplayList(intList);         printf("\n");
    printf("[ListTest] Insert 1.1 - infos  = ");   DisplayListInfos(strList);    printf("\n");
    printf("[ListTest] Insert 1.1 - infos  = ");   DisplayList(strList);         printf("\n");
    strList->Insert(4,(CS_NEW System::String())->_appendC('s')->_appendC('t')->_appendC('r')->_appendI(7)->_appendClose());
    strList->Insert(0,(CS_NEW System::String())->_appendC('s')->_appendC('t')->_appendC('r')->_appendI(-1)->_appendClose());
    strList->Insert(10,(CS_NEW System::String())->_appendC('s')->_appendC('t')->_appendC('r')->_appendI(20)->_appendClose());
    printf("[ListTest] Insert 1.1 - result = ");   DisplayListInfos(strList);    printf("\n");
    printf("[ListTest] Insert 1.1 - result = ");   DisplayList(strList);         printf("\n");
    printf("\n");


	// GC TEST
	System::Collections::Generic::List<System::String*>* _static_strList = CS_NEW System::Collections::Generic::List<System::String*>();
	System::Memory::registerGCRoot(&_static_strList);
	for(int i = 0; i < 8; ++i) {
        _static_strList->Add((CS_NEW System::String())->_appendC('s')->_appendC('t')->_appendC('a')->_appendC('t')->_appendI(i*2)->_appendClose());
    }
	// END GC TEST


	// Test - InsertRange

	
	// Test - LastIndexOf
	intList = CS_NEW System::Collections::Generic::List<s32>();
    strList = CS_NEW System::Collections::Generic::List<System::String*>();
    for(int i = 0; i < 8; ++i) {
        intList->Add(i*2);
        strList->Add((CS_NEW System::String())->_appendC('s')->_appendC('t')->_appendC('r')->_appendI(i*2)->_appendClose());
    }
	printf("[ListTest] LastIndexOf 1.0+ - infos = ");   DisplayListInfos(intList);    printf("\n");
    printf("[ListTest] LastIndexOf 1.0+ - infos = ");   DisplayList(intList);         printf("\n");
    printf("[ListTest] LastIndexOf 1.0 - result = %i\n", intList->LastIndexOf(4));
    printf("[ListTest] LastIndexOf 1.1 - result = %i\n", intList->LastIndexOf(5));
    printf("[ListTest] LastIndexOf 1.2+ - infos = ");   DisplayListInfos(strList);    printf("\n");
    printf("[ListTest] LastIndexOf 1.2+ - infos = ");   DisplayList(strList);         printf("\n");
    printf("[ListTest] LastIndexOf 1.2 - result = %i\n", strList->LastIndexOf((CS_NEW System::String())->_appendC('s')->_appendC('t')->_appendC('r')->_appendI(4)->_appendClose()));
    printf("[ListTest] LastIndexOf 1.3 - result = %i\n", strList->LastIndexOf((CS_NEW System::String())->_appendC('s')->_appendC('t')->_appendC('r')->_appendI(5)->_appendClose()));
    printf("\n");
    printf("[ListTest] LastIndexOf 2.0 - result = %i\n", intList->LastIndexOf(4, 7));
    printf("[ListTest] LastIndexOf 2.1 - result = %i\n", intList->LastIndexOf(4, 1));
    printf("[ListTest] LastIndexOf 2.2 - result = %i\n", intList->LastIndexOf(5, 7));
    printf("[ListTest] LastIndexOf 2.3 - result = %i\n", strList->LastIndexOf((CS_NEW System::String())->_appendC('s')->_appendC('t')->_appendC('r')->_appendI(4)->_appendClose(), 7));
    printf("[ListTest] LastIndexOf 2.4 - result = %i\n", strList->LastIndexOf((CS_NEW System::String())->_appendC('s')->_appendC('t')->_appendC('r')->_appendI(4)->_appendClose(), 1));
    printf("[ListTest] LastIndexOf 2.5 - result = %i\n", strList->LastIndexOf((CS_NEW System::String())->_appendC('s')->_appendC('t')->_appendC('r')->_appendI(5)->_appendClose(), 7));
    printf("\n");
    printf("[ListTest] LastIndexOf 2.0 - result = %i\n", intList->LastIndexOf(4, 7, 4));
    printf("[ListTest] LastIndexOf 2.1 - result = %i\n", intList->LastIndexOf(4, 7, 8));
    printf("[ListTest] LastIndexOf 2.2 - result = %i\n", intList->LastIndexOf(5, 7, 8));
    printf("[ListTest] LastIndexOf 2.3 - result = %i\n", strList->LastIndexOf((CS_NEW System::String())->_appendC('s')->_appendC('t')->_appendC('r')->_appendI(4)->_appendClose(), 7, 4));
    printf("[ListTest] LastIndexOf 2.4 - result = %i\n", strList->LastIndexOf((CS_NEW System::String())->_appendC('s')->_appendC('t')->_appendC('r')->_appendI(4)->_appendClose(), 7, 8));
    printf("[ListTest] LastIndexOf 2.5 - result = %i\n", strList->LastIndexOf((CS_NEW System::String())->_appendC('s')->_appendC('t')->_appendC('r')->_appendI(5)->_appendClose(), 7, 8));
    printf("\n");

	// Test - Remove
	intList = CS_NEW System::Collections::Generic::List<s32>();
    strList = CS_NEW System::Collections::Generic::List<System::String*>();
    for(int i = 0; i < 8; ++i) {
        intList->Add(i*2);
        strList->Add((CS_NEW System::String())->_appendC('s')->_appendC('t')->_appendC('r')->_appendI(i*2)->_appendClose());
    }
	printf("[ListTest] Remove 1.0+ - infos  = ");   DisplayListInfos(intList);		printf("\n");
    printf("[ListTest] Remove 1.0+ - infos  = ");   DisplayList(intList);			printf("\n");
    printf("[ListTest] Remove 1.0 - result  = %s\n", (intList->Remove(4)) ? "True":"False");
    printf("[ListTest] Remove 1.1 - result  = %s\n", (intList->Remove(5)) ? "True":"False");
    printf("[ListTest] Remove 1.0+ - result = ");   DisplayListInfos(intList);		printf("\n");
    printf("[ListTest] Remove 1.0+ - result = ");   DisplayList(intList);			printf("\n");
    printf("[ListTest] Remove 1.2+ - infos  = ");   DisplayListInfos(strList);		printf("\n");
    printf("[ListTest] Remove 1.2+ - infos  = ");   DisplayList(strList);			printf("\n");
    printf("[ListTest] Remove 1.2 - result  = %s\n", (strList->Remove((CS_NEW System::String())->_appendC('s')->_appendC('t')->_appendC('r')->_appendI(4)->_appendClose())) ? "True":"False");
    printf("[ListTest] Remove 1.3 - result  = %s\n", (strList->Remove((CS_NEW System::String())->_appendC('s')->_appendC('t')->_appendC('r')->_appendI(5)->_appendClose())) ? "True":"False");
    printf("[ListTest] Remove 1.2+ - result = ");   DisplayListInfos(strList);		printf("\n");
    printf("[ListTest] Remove 1.2+ - result = ");   DisplayList(strList);			printf("\n");
    printf("\n");

	// Test - RemoveAll

	
	// Test - RemoveAt
	intList = CS_NEW System::Collections::Generic::List<s32>();
    strList = CS_NEW System::Collections::Generic::List<System::String*>();
    for(int i = 0; i < 8; ++i) {
        intList->Add(i*2);
        strList->Add((CS_NEW System::String())->_appendC('s')->_appendC('t')->_appendC('r')->_appendI(i*2)->_appendClose());
    }
	printf("[ListTest] RemoveAt 1.0 - infos  = ");   DisplayListInfos(intList);		printf("\n");
    printf("[ListTest] RemoveAt 1.0 - infos  = ");   DisplayList(intList);			printf("\n");
    intList->RemoveAt(4);
    printf("[ListTest] RemoveAt 1.0 - result = ");   DisplayListInfos(intList);		printf("\n");
    printf("[ListTest] RemoveAt 1.0 - result = ");   DisplayList(intList);			printf("\n");
    printf("[ListTest] RemoveAt 1.1 - infos  = ");   DisplayListInfos(strList);		printf("\n");
    printf("[ListTest] RemoveAt 1.1 - infos  = ");   DisplayList(strList);			printf("\n");
    strList->RemoveAt(4);
    printf("[ListTest] RemoveAt 1.1 - result = ");   DisplayListInfos(strList);		printf("\n");
    printf("[ListTest] RemoveAt 1.1 - result = ");   DisplayList(strList);			printf("\n");
    printf("\n");
	
	// Test - RemoveRange
	intList = CS_NEW System::Collections::Generic::List<s32>();
    strList = CS_NEW System::Collections::Generic::List<System::String*>();
    for(int i = 0; i < 8; ++i) {
        intList->Add(i*2);
        strList->Add((CS_NEW System::String())->_appendC('s')->_appendC('t')->_appendC('r')->_appendI(i*2)->_appendClose());
    }
	printf("[ListTest] RemoveRange 1.0 - infos  = ");   DisplayListInfos(intList);  printf("\n");
    printf("[ListTest] RemoveRange 1.0 - infos  = ");   DisplayList(intList);       printf("\n");
    intList->RemoveRange(4,2);
    printf("[ListTest] RemoveRange 1.0 - result = ");   DisplayListInfos(intList);  printf("\n");
    printf("[ListTest] RemoveRange 1.0 - result = ");   DisplayList(intList);       printf("\n");
    printf("[ListTest] RemoveRange 1.1 - infos  = ");   DisplayListInfos(strList);  printf("\n");
    printf("[ListTest] RemoveRange 1.1 - infos  = ");   DisplayList(strList);       printf("\n");
    strList->RemoveRange(4,2);
    printf("[ListTest] RemoveRange 1.1 - result = ");   DisplayListInfos(strList);	printf("\n");
    printf("[ListTest] RemoveRange 1.1 - result = ");   DisplayList(strList);       printf("\n");
    printf("\n");
	
	// Test - Reverse
	intList = CS_NEW System::Collections::Generic::List<s32>();
    strList = CS_NEW System::Collections::Generic::List<System::String*>();
    for(int i = 0; i < 8; ++i) {
        intList->Add(i*2);
        strList->Add((CS_NEW System::String())->_appendC('s')->_appendC('t')->_appendC('r')->_appendI(i*2)->_appendClose());
    }
	printf("[ListTest] Reverse 1.0 - infos  = ");   DisplayListInfos(intList);  printf("\n");
    printf("[ListTest] Reverse 1.0 - infos  = ");   DisplayList(intList);       printf("\n");
    intList->Reverse();
    printf("[ListTest] Reverse 1.0 - result = ");   DisplayListInfos(intList);  printf("\n");
    printf("[ListTest] Reverse 1.0 - result = ");   DisplayList(intList);       printf("\n");
    printf("[ListTest] Reverse 1.1 - infos  = ");   DisplayListInfos(strList);  printf("\n");
    printf("[ListTest] Reverse 1.1 - infos  = ");   DisplayList(strList);       printf("\n");
    strList->Reverse();
    printf("[ListTest] Reverse 1.1 - result = ");   DisplayListInfos(strList);  printf("\n");
    printf("[ListTest] Reverse 1.1 - result = ");   DisplayList(strList);       printf("\n");
    printf("\n");
    intList->Reverse(4,3);
    strList->Reverse(3,2);
    printf("[ListTest] Reverse 2.0 - result = ");   DisplayListInfos(intList);  printf("\n");
    printf("[ListTest] Reverse 2.0 - result = ");   DisplayList(intList);       printf("\n");
    printf("[ListTest] Reverse 2.1 - result = ");   DisplayListInfos(strList);  printf("\n");
    printf("[ListTest] Reverse 2.1 - result = ");   DisplayList(strList);		printf("\n");
    printf("\n");

	// Test - Sort
	intList = CS_NEW System::Collections::Generic::List<s32>();
	intList->Add(42); intList->Add(1337); intList->Add(7); intList->Add(23); intList->Add(2);
    strList = CS_NEW System::Collections::Generic::List<System::String*>();
	strList->Add((CS_NEW System::String())->_appendC('q')->_appendClose());
	strList->Add((CS_NEW System::String())->_appendC('w')->_appendClose());
	strList->Add((CS_NEW System::String())->_appendC('e')->_appendClose());
	strList->Add((CS_NEW System::String())->_appendC('r')->_appendClose());
	strList->Add((CS_NEW System::String())->_appendC('t')->_appendClose());
	strList->Add((CS_NEW System::String())->_appendC('y')->_appendClose());
    printf("[ListTest] Sort 1.0 - infos  = ");   DisplayListInfos(intList);		printf("\n");
    printf("[ListTest] Sort 1.0 - infos  = ");   DisplayList(intList);			printf("\n");
    intList->Sort();
    printf("[ListTest] Sort 1.0 - result = ");   DisplayListInfos(intList);		printf("\n");
    printf("[ListTest] Sort 1.0 - result = ");   DisplayList(intList);			printf("\n");
    printf("[ListTest] Sort 1.1 - infos  = ");   DisplayListInfos(strList);		printf("\n");
    printf("[ListTest] Sort 1.1 - infos  = ");   DisplayList(strList);			printf("\n");
    strList->Sort();
    printf("[ListTest] Sort 1.1 - result = ");   DisplayListInfos(strList);		printf("\n");
    printf("[ListTest] Sort 1.1 - result = ");   DisplayList(strList);			printf("\n");
    printf("\n");
    // TODO other Sort methods.

	// Test - ToArray
	intList = CS_NEW System::Collections::Generic::List<s32>();
    strList = CS_NEW System::Collections::Generic::List<System::String*>();
    for(int i = 0; i < 5; ++i) {
        intList->Add(i*2);
        strList->Add((CS_NEW System::String())->_appendC('s')->_appendC('t')->_appendC('r')->_appendI(i*2)->_appendClose());
    }
	printf("[ListTest] ToArray 1.0 - infos  = ");   DisplayListInfos(intList);  printf("\n");
    printf("[ListTest] ToArray 1.0 - infos  = ");   DisplayList(intList);       printf("\n");
    intArray = intList->ToArray();
    printf("[ListTest] ToArray 1.0 - result = ");   DisplayArray(intArray);		printf("\n");
    printf("[ListTest] ToArray 1.1 - infos  = ");   DisplayListInfos(strList);  printf("\n");
    printf("[ListTest] ToArray 1.1 - infos  = ");   DisplayList(strList);       printf("\n");
    strArray = strList->ToArray();
    printf("[ListTest] ToArray 1.1 - result = ");   DisplayArray(strArray);		printf("\n");
    printf("\n");

	// Test - TrimExcess
	intList = CS_NEW System::Collections::Generic::List<s32>();
    strList = CS_NEW System::Collections::Generic::List<System::String*>();
    for(int i = 0; i < 5; ++i) {
        intList->Add(i*2);
        strList->Add((CS_NEW System::String())->_appendC('s')->_appendC('t')->_appendC('r')->_appendI(i*2)->_appendClose());
    }
	printf("[ListTest] TrimExcess 1.0 - infos  = ");   DisplayListInfos(intList);	printf("\n");
    printf("[ListTest] TrimExcess 1.0 - infos  = ");   DisplayList(intList);        printf("\n");
    intList->TrimExcess();
    printf("[ListTest] TrimExcess 1.0 - result = ");   DisplayListInfos(intList);   printf("\n");
    printf("[ListTest] TrimExcess 1.0 - result = ");   DisplayList(intList);        printf("\n");
    printf("[ListTest] TrimExcess 1.1 - infos  = ");   DisplayListInfos(strList);   printf("\n");
    printf("[ListTest] TrimExcess 1.1 - infos  = ");   DisplayList(strList);        printf("\n");
    strList->TrimExcess();
    printf("[ListTest] TrimExcess 1.1 - result = ");   DisplayListInfos(strList);   printf("\n");
    printf("[ListTest] TrimExcess 1.1 - result = ");   DisplayList(strList);        printf("\n");
    printf("\n");

	// Test - TrueForAll
	

	
	//#########################################
	//#########################################
	//############# Array Tests ###############
	//#########################################
	//#########################################
	
	printf("#########################################\n");
	printf("#########################################\n");
    printf("############## Array Tests ##############\n");
	printf("#########################################\n");
    printf("#########################################\n");
    printf("\n");
    printf("\n");
	printf("#########################################\n");
    printf("############ Abstract Array #############\n");
	printf("#########################################\n");
    printf("\n");
    printf("\n");

    // Test - Constructors (normal arrays)
	intArray = CS_NEW System::Array<s32>(6); 
	intArray->_idx$_s(0, 0); intArray->_idx$_s(1, 2); intArray->_idx$_s(2, 4); 
	intArray->_idx$_s(3, 6); intArray->_idx$_s(4, 8); intArray->_idx$_s(5, 10);
    strArray = CS_NEW System::Array<System::String*>(3);
	strArray->_idx$_s(0, (CS_NEW System::String())->_appendC('s')->_appendC('0')->_appendClose());
	strArray->_idx$_s(1, (CS_NEW System::String())->_appendC('s')->_appendC('1')->_appendClose());
	strArray->_idx$_s(2, (CS_NEW System::String())->_appendC('s')->_appendC('2')->_appendClose());

	printf("[AbstractArrayTest] Constructors 1.0 - infos = "); DisplayArrayInfos(intArray); printf("\n");
    printf("[AbstractArrayTest] Constructors 1.0 - infos = "); DisplayArray(intArray);      printf("\n");
    printf("[AbstractArrayTest] Constructors 1.1 - infos = "); DisplayArrayInfos(strArray); printf("\n");
    printf("[AbstractArrayTest] Constructors 1.1 - infos = "); DisplayArray(strArray);      printf("\n");
	printf("\n");

    // Test - BinarySearch
    intArray = CS_NEW System::Array<s32>(6); 
	intArray->_idx$_s(0, 0); intArray->_idx$_s(1, 2); intArray->_idx$_s(2, 4);
	intArray->_idx$_s(3, 6); intArray->_idx$_s(4, 8); intArray->_idx$_s(5, 10);
    strArray = CS_NEW System::Array<System::String*>(3);
	strArray->_idx$_s(0, (CS_NEW System::String())->_appendC('s')->_appendC('0')->_appendClose());
	strArray->_idx$_s(1, (CS_NEW System::String())->_appendC('s')->_appendC('1')->_appendClose());
	strArray->_idx$_s(2, (CS_NEW System::String())->_appendC('s')->_appendC('2')->_appendClose());

    printf("[AbstractArrayTest] BinarySearch 1.0+ - infos = "); DisplayArrayInfos(intArray); printf("\n");
    printf("[AbstractArrayTest] BinarySearch 1.0+ - infos = "); DisplayArray(intArray);      printf("\n");
    printf("[AbstractArrayTest] BinarySearch 1.2+ - infos = "); DisplayArrayInfos(strArray); printf("\n");
    printf("[AbstractArrayTest] BinarySearch 1.2+ - infos = "); DisplayArray(strArray);      printf("\n");
    printf("[AbstractArrayTest] BinarySearch 1.0 - result = %i\n", System::AbstractArray::BinarySearch(intArray, 3));
    printf("[AbstractArrayTest] BinarySearch 1.1 - result = %i\n", System::AbstractArray::BinarySearch(intArray, 4));
    printf("[AbstractArrayTest] BinarySearch 1.2 - result = %i\n", System::AbstractArray::BinarySearch(strArray, (CS_NEW System::String())->_appendC('t')->_appendClose()));
    printf("[AbstractArrayTest] BinarySearch 1.3 - result = %i\n", System::AbstractArray::BinarySearch(strArray, (CS_NEW System::String())->_appendC('s')->_appendI(0)->_appendClose()));
    printf("\n");
    printf("[AbstractArrayTest] BinarySearch 2.0 - result = %i\n", System::AbstractArray::BinarySearch(intArray, 0, 6, 3));
    printf("[AbstractArrayTest] BinarySearch 2.1 - result = %i\n", System::AbstractArray::BinarySearch(intArray, 1, 1, 4));
    printf("[AbstractArrayTest] BinarySearch 2.2 - result = %i\n", System::AbstractArray::BinarySearch(intArray, 1, 2, 4));
    printf("[AbstractArrayTest] BinarySearch 2.3 - result = %i\n", System::AbstractArray::BinarySearch(strArray, 0, 3, (CS_NEW System::String())->_appendC('s')->_appendI(9)->_appendClose()));
    printf("[AbstractArrayTest] BinarySearch 2.4 - result = %i\n", System::AbstractArray::BinarySearch(strArray, 0, 1, (CS_NEW System::String())->_appendC('s')->_appendI(1)->_appendClose()));
    printf("[AbstractArrayTest] BinarySearch 2.5 - result = %i\n", System::AbstractArray::BinarySearch(strArray, 0, 3, (CS_NEW System::String())->_appendC('s')->_appendI(1)->_appendClose()));
    printf("\n");

    // Test - Clear
    intArray = CS_NEW System::Array<s32>(6);
	intArray->_idx$_s(0, 0); intArray->_idx$_s(1, 2); intArray->_idx$_s(2, 4); 
	intArray->_idx$_s(3, 6); intArray->_idx$_s(4, 8); intArray->_idx$_s(5, 10);
    strArray = CS_NEW System::Array<System::String*>(3);
	strArray->_idx$_s(0, (CS_NEW System::String())->_appendC('s')->_appendC('0')->_appendClose());
	strArray->_idx$_s(1, (CS_NEW System::String())->_appendC('s')->_appendC('1')->_appendClose());
	strArray->_idx$_s(2, (CS_NEW System::String())->_appendC('s')->_appendC('2')->_appendClose());

    printf("[AbstractArrayTest] Clear 1.0 - infos  = "); DisplayArrayInfos(intArray); printf("\n");
    printf("[AbstractArrayTest] Clear 1.0 - infos  = "); DisplayArray(intArray);      printf("\n");
    System::AbstractArray::Clear(intArray, 0, intArray->_acc_gLength());
    printf("[AbstractArrayTest] Clear 1.0 - result = "); DisplayArrayInfos(intArray); printf("\n");
    printf("[AbstractArrayTest] Clear 1.0 - result = "); DisplayArray(intArray);      printf("\n");
    printf("[AbstractArrayTest] Clear 1.1 - infos  = "); DisplayArrayInfos(strArray); printf("\n");
    printf("[AbstractArrayTest] Clear 1.1 - infos  = "); DisplayArray(strArray);      printf("\n");
    System::AbstractArray::Clear(strArray, 1, 1);
    printf("[AbstractArrayTest] Clear 1.1 - result = "); DisplayArrayInfos(strArray); printf("\n");
    printf("[AbstractArrayTest] Clear 1.1 - result = "); DisplayArray(strArray);      printf("\n");
    printf("\n");

    // Test - Clone
    intArray = CS_NEW System::Array<s32>(6); 
	intArray->_idx$_s(0, 0); intArray->_idx$_s(1, 2); intArray->_idx$_s(2, 4); 
	intArray->_idx$_s(3, 6); intArray->_idx$_s(4, 8); intArray->_idx$_s(5, 10);
    
    printf("[AbstractArrayTest] Clone 1.0 - infos  = "); DisplayArrayInfos(intArray);            printf("\n");
    printf("[AbstractArrayTest] Clone 1.0 - infos  = "); DisplayArray(intArray);                 printf("\n");
    intArray2 = (System::Array<s32>*)intArray->Clone();
    printf("[AbstractArrayTest] Clone 1.0 - clone  = "); DisplayArrayInfos(intArray2);           printf("\n");
    printf("[AbstractArrayTest] Clone 1.0 - clone  = "); DisplayArray(intArray2);                printf("\n");
	intArray->_idx$_s(3, intArray->_idx$_g(3) +1);
    printf("[AbstractArrayTest] Clone 1.0 - after original = "); DisplayArrayInfos(intArray);    printf("\n");
    printf("[AbstractArrayTest] Clone 1.0 - after original = "); DisplayArray(intArray);         printf("\n");
    printf("[AbstractArrayTest] Clone 1.0 - after clone    = "); DisplayArrayInfos(intArray2);   printf("\n");
    printf("[AbstractArrayTest] Clone 1.0 - after clone    = "); DisplayArray(intArray2);        printf("\n");

    strArray = CS_NEW System::Array<System::String*>(3);
	strArray->_idx$_s(0, (CS_NEW System::String())->_appendC('s')->_appendC('0')->_appendClose());
	strArray->_idx$_s(1, (CS_NEW System::String())->_appendC('s')->_appendC('1')->_appendClose());
	strArray->_idx$_s(2, (CS_NEW System::String())->_appendC('s')->_appendC('2')->_appendClose());


	// GC TEST
	System::Array<System::String*>* _static_strArray = CS_NEW System::Array<System::String*>(3);
	System::Memory::registerGCRoot(&_static_strArray);
	_static_strArray->_idx$_s(0, (CS_NEW System::String())->_appendC('s')->_appendC('t')->_appendC('a')->_appendC('t')->_appendC('i')->_appendC('c')->_appendC('0')->_appendClose());
	_static_strArray->_idx$_s(1, (CS_NEW System::String())->_appendC('s')->_appendC('t')->_appendC('a')->_appendC('t')->_appendC('i')->_appendC('c')->_appendC('1')->_appendClose());
	_static_strArray->_idx$_s(2, (CS_NEW System::String())->_appendC('s')->_appendC('t')->_appendC('a')->_appendC('t')->_appendC('i')->_appendC('c')->_appendC('2')->_appendClose());
	// END GC TEST
	


    printf("[AbstractArrayTest] Clone 1.1 - infos  = "); DisplayArrayInfos(strArray);            printf("\n");
    printf("[AbstractArrayTest] Clone 1.1 - infos  = "); DisplayArray(strArray);                 printf("\n");
    strArray2 = (System::Array<System::String*>*)strArray->Clone();
    printf("[AbstractArrayTest] Clone 1.1 - clone  = "); DisplayArrayInfos(strArray);            printf("\n");
    printf("[AbstractArrayTest] Clone 1.1 - clone  = "); DisplayArray(strArray);                 printf("\n");
	strArray->_idx$_s(1, CS_NEW System::String(c_hello, 5));
    printf("[AbstractArrayTest] Clone 1.1 - after original = "); DisplayArrayInfos(strArray);    printf("\n");
    printf("[AbstractArrayTest] Clone 1.1 - after original = "); DisplayArray(strArray);         printf("\n");
    printf("[AbstractArrayTest] Clone 1.1 - after clone    = "); DisplayArrayInfos(strArray2);   printf("\n");
    printf("[AbstractArrayTest] Clone 1.1 - after clone    = "); DisplayArray(strArray2);        printf("\n");
    printf("\n");

    // Test - ConstrainedCopy


    // Test - Copy


    // Test - CopyTo


    // Test - CreateInstance


    // Test - GetEnumerator


    // Test - IndexOf
    intArray = CS_NEW System::Array<int>(6); 
	intArray->_idx$_s(0, 0); intArray->_idx$_s(1, 2); intArray->_idx$_s(2, 4); 
	intArray->_idx$_s(3, 2); intArray->_idx$_s(4, 4); intArray->_idx$_s(5, 0);
    strArray = CS_NEW System::Array<System::String*>(3);
	strArray->_idx$_s(0, (CS_NEW System::String())->_appendC('s')->_appendC('0')->_appendClose());
	strArray->_idx$_s(1, (CS_NEW System::String())->_appendC('s')->_appendC('1')->_appendClose());
	strArray->_idx$_s(2, (CS_NEW System::String())->_appendC('s')->_appendC('0')->_appendClose());

    printf("[AbstractArrayTest] IndexOf 1.0+ - infos = "); DisplayArrayInfos(intArray);    printf("\n");
    printf("[AbstractArrayTest] IndexOf 1.0+ - infos = "); DisplayArray(intArray);         printf("\n");
    printf("[AbstractArrayTest] IndexOf 1.2+ - infos = "); DisplayArrayInfos(strArray);    printf("\n");
    printf("[AbstractArrayTest] IndexOf 1.2+ - infos = "); DisplayArray(strArray);         printf("\n");

    printf("[AbstractArrayTest] IndexOf 1.0 - result = %i\n", System::AbstractArray::IndexOf(intArray, 0));
    printf("[AbstractArrayTest] IndexOf 1.1 - result = %i\n", System::AbstractArray::IndexOf(intArray, 1));
    printf("[AbstractArrayTest] IndexOf 1.2 - result = %i\n", System::AbstractArray::IndexOf(strArray, (CS_NEW System::String())->_appendC('s')->_appendI(0)->_appendClose()));
    printf("[AbstractArrayTest] IndexOf 1.3 - result = %i\n", System::AbstractArray::IndexOf(strArray, 1));
    printf("[AbstractArrayTest] IndexOf 1.4 - result = %i\n", System::AbstractArray::IndexOf(strArray, CS_NEW System::Collections::Generic::List<s32>()));
    printf("\n");
    printf("[AbstractArrayTest] IndexOf 2.0 - result = %i\n", System::AbstractArray::IndexOf(intArray, 2, 0));
    printf("[AbstractArrayTest] IndexOf 2.1 - result = %i\n", System::AbstractArray::IndexOf(intArray, 2, 2));
    printf("[AbstractArrayTest] IndexOf 2.2 - result = %i\n", System::AbstractArray::IndexOf(intArray, 2, 4));
    printf("[AbstractArrayTest] IndexOf 2.3 - result = %i\n", System::AbstractArray::IndexOf(intArray, 1, 0));
    printf("[AbstractArrayTest] IndexOf 2.4 - result = %i\n", System::AbstractArray::IndexOf(strArray, (CS_NEW System::String())->_appendC('s')->_appendI(0)->_appendClose(), 0));
    printf("[AbstractArrayTest] IndexOf 2.5 - result = %i\n", System::AbstractArray::IndexOf(strArray, (CS_NEW System::String())->_appendC('s')->_appendI(0)->_appendClose(), 1));
    printf("[AbstractArrayTest] IndexOf 2.6 - result = %i\n", System::AbstractArray::IndexOf(strArray, 2, 0));
    printf("\n");
    printf("[AbstractArrayTest] IndexOf 3.0 - result = %i\n", System::AbstractArray::IndexOf(intArray, 2, 0, 1));
    printf("[AbstractArrayTest] IndexOf 3.1 - result = %i\n", System::AbstractArray::IndexOf(intArray, 2, 0, 2));
    printf("[AbstractArrayTest] IndexOf 3.2 - result = %i\n", System::AbstractArray::IndexOf(strArray, (CS_NEW System::String())->_appendC('s')->_appendI(0)->_appendClose(), 1, 2));
    printf("[AbstractArrayTest] IndexOf 3.3 - result = %i\n", System::AbstractArray::IndexOf(strArray, 's', 1, 2));
    printf("\n");

    // Test - Initialize


    // Test - LastIndexOf
    intArray = CS_NEW System::Array<int>(6); 
	intArray->_idx$_s(0, 0); intArray->_idx$_s(1, 2); intArray->_idx$_s(2, 4); 
	intArray->_idx$_s(3, 2); intArray->_idx$_s(4, 4); intArray->_idx$_s(5, 0);
    strArray = CS_NEW System::Array<System::String*>(3);
	strArray->_idx$_s(0, (CS_NEW System::String())->_appendC('s')->_appendC('0')->_appendClose());
	strArray->_idx$_s(1, (CS_NEW System::String())->_appendC('s')->_appendC('1')->_appendClose());
	strArray->_idx$_s(2, (CS_NEW System::String())->_appendC('s')->_appendC('0')->_appendClose());

    printf("[AbstractArrayTest] LastIndexOf 1.0+ - infos = "); DisplayArrayInfos(intArray);    printf("\n");
    printf("[AbstractArrayTest] LastIndexOf 1.0+ - infos = "); DisplayArray(intArray);         printf("\n");
    printf("[AbstractArrayTest] LastIndexOf 1.2+ - infos = "); DisplayArrayInfos(strArray);    printf("\n");
    printf("[AbstractArrayTest] LastIndexOf 1.2+ - infos = "); DisplayArray(strArray);         printf("\n");

    printf("[AbstractArrayTest] LastIndexOf 1.0 - result = %i\n", System::AbstractArray::LastIndexOf(intArray, 0));
    printf("[AbstractArrayTest] LastIndexOf 1.1 - result = %i\n", System::AbstractArray::LastIndexOf(intArray, 1));
    printf("[AbstractArrayTest] LastIndexOf 1.2 - result = %i\n", System::AbstractArray::LastIndexOf(strArray, (CS_NEW System::String())->_appendC('s')->_appendI(0)->_appendClose()));
    printf("[AbstractArrayTest] LastIndexOf 1.3 - result = %i\n", System::AbstractArray::LastIndexOf(strArray, 1));
    printf("[AbstractArrayTest] LastIndexOf 1.4 - result = %i\n", System::AbstractArray::LastIndexOf(strArray, CS_NEW System::Collections::Generic::List<s32>()));
    printf("\n");
    printf("[AbstractArrayTest] LastIndexOf 2.0 - result = %i\n", System::AbstractArray::LastIndexOf(intArray, 2, 5));
    printf("[AbstractArrayTest] LastIndexOf 2.1 - result = %i\n", System::AbstractArray::LastIndexOf(intArray, 2, 2));
    printf("[AbstractArrayTest] LastIndexOf 2.2 - result = %i\n", System::AbstractArray::LastIndexOf(intArray, 2, 0));
    printf("[AbstractArrayTest] LastIndexOf 2.3 - result = %i\n", System::AbstractArray::LastIndexOf(intArray, 1, 5));
    printf("[AbstractArrayTest] LastIndexOf 2.4 - result = %i\n", System::AbstractArray::LastIndexOf(strArray, (CS_NEW System::String())->_appendC('s')->_appendI(0)->_appendClose(), 2));
    printf("[AbstractArrayTest] LastIndexOf 2.5 - result = %i\n", System::AbstractArray::LastIndexOf(strArray, (CS_NEW System::String())->_appendC('s')->_appendI(1)->_appendClose(), 0));
    printf("[AbstractArrayTest] LastIndexOf 2.6 - result = %i\n", System::AbstractArray::LastIndexOf(strArray, 2, 2));
    printf("\n");
    printf("[AbstractArrayTest] LastIndexOf 3.0 - result = %i\n", System::AbstractArray::LastIndexOf(intArray, 2, 5, 6));
    printf("[AbstractArrayTest] LastIndexOf 3.1 - result = %i\n", System::AbstractArray::LastIndexOf(intArray, 2, 5, 2));
    printf("[AbstractArrayTest] LastIndexOf 3.2 - result = %i\n", System::AbstractArray::LastIndexOf(strArray, (CS_NEW System::String())->_appendC('s')->_appendI(1)->_appendClose(), 2, 2));
    printf("[AbstractArrayTest] LastIndexOf 3.3 - result = %i\n", System::AbstractArray::LastIndexOf(strArray, 's', 2, 2));
    printf("\n");

    // Test - Reverse
    intArray = CS_NEW System::Array<s32>(6); 
	intArray->_idx$_s(0, 0); intArray->_idx$_s(1, 2); intArray->_idx$_s(2, 4); 
	intArray->_idx$_s(3, 6); intArray->_idx$_s(4, 8); intArray->_idx$_s(5, 10);
    strArray = CS_NEW System::Array<System::String*>(3);
	strArray->_idx$_s(0, (CS_NEW System::String())->_appendC('s')->_appendC('0')->_appendClose());
	strArray->_idx$_s(1, (CS_NEW System::String())->_appendC('s')->_appendC('1')->_appendClose());
	strArray->_idx$_s(2, (CS_NEW System::String())->_appendC('s')->_appendC('2')->_appendClose());

    printf("[AbstractArrayTest] Reverse 1.0 - infos  = "); DisplayArrayInfos(intArray);    printf("\n");
    printf("[AbstractArrayTest] Reverse 1.0 - infos  = "); DisplayArray(intArray);         printf("\n");
    System::AbstractArray::Reverse(intArray);
    printf("[AbstractArrayTest] Reverse 1.0 - result = "); DisplayArrayInfos(intArray);    printf("\n");
    printf("[AbstractArrayTest] Reverse 1.0 - result = "); DisplayArray(intArray);         printf("\n");
    printf("[AbstractArrayTest] Reverse 1.1 - infos  = "); DisplayArrayInfos(strArray);    printf("\n");
    printf("[AbstractArrayTest] Reverse 1.1 - infos  = "); DisplayArray(strArray);         printf("\n");
    System::AbstractArray::Reverse(strArray);
    printf("[AbstractArrayTest] Reverse 1.1 - result = "); DisplayArrayInfos(strArray);    printf("\n");
    printf("[AbstractArrayTest] Reverse 1.1 - result = "); DisplayArray(strArray);         printf("\n");
    printf("\n");

    intArray = CS_NEW System::Array<s32>(6); 
	intArray->_idx$_s(0, 0); intArray->_idx$_s(1, 2); intArray->_idx$_s(2, 4); 
	intArray->_idx$_s(3, 6); intArray->_idx$_s(4, 8); intArray->_idx$_s(5, 10);
    strArray = CS_NEW System::Array<System::String*>(3);
	strArray->_idx$_s(0, (CS_NEW System::String())->_appendC('s')->_appendC('0')->_appendClose());
	strArray->_idx$_s(1, (CS_NEW System::String())->_appendC('s')->_appendC('1')->_appendClose());
	strArray->_idx$_s(2, (CS_NEW System::String())->_appendC('s')->_appendC('2')->_appendClose());

    printf("[AbstractArrayTest] Reverse 2.0 - infos  = "); DisplayArrayInfos(intArray);    printf("\n");
    printf("[AbstractArrayTest] Reverse 2.0 - infos  = "); DisplayArray(intArray);         printf("\n");
    System::AbstractArray::Reverse(intArray, 1, 5);
    printf("[AbstractArrayTest] Reverse 2.0 - result = "); DisplayArrayInfos(intArray);    printf("\n");
    printf("[AbstractArrayTest] Reverse 2.0 - result = "); DisplayArray(intArray);         printf("\n");
    printf("[AbstractArrayTest] Reverse 2.1 - infos  = "); DisplayArrayInfos(strArray);    printf("\n");
    printf("[AbstractArrayTest] Reverse 2.1 - infos  = "); DisplayArray(strArray);         printf("\n");
    System::AbstractArray::Reverse(strArray, 1, 2);
    printf("[AbstractArrayTest] Reverse 2.1 - result = "); DisplayArrayInfos(strArray);    printf("\n");
    printf("[AbstractArrayTest] Reverse 2.1 - result = "); DisplayArray(strArray);         printf("\n");
    printf("\n");

    // Test - Sort
	intArray = CS_NEW System::Array<s32>(6); 
	intArray->_idx$_s(0, 42); intArray->_idx$_s(1, 1337); intArray->_idx$_s(2, 7); 
	intArray->_idx$_s(3, 23); intArray->_idx$_s(4, 2); intArray->_idx$_s(5, 14);
    strArray = CS_NEW System::Array<System::String*>(7);
	strArray->_idx$_s(0, (CS_NEW System::String())->_appendC('q')->_appendClose());
	strArray->_idx$_s(1, (CS_NEW System::String())->_appendC('w')->_appendClose());
	strArray->_idx$_s(2, (CS_NEW System::String())->_appendC('e')->_appendClose());
	strArray->_idx$_s(3, (CS_NEW System::String())->_appendC('r')->_appendClose());
	strArray->_idx$_s(4, (CS_NEW System::String())->_appendC('t')->_appendClose());
	strArray->_idx$_s(5, (CS_NEW System::String())->_appendC('y')->_appendClose());
	strArray->_idx$_s(6, (CS_NEW System::String())->_appendC('Q')->_appendClose());
	
    printf("[AbstractArrayTest] Sort 1.0 - infos  = "); DisplayArrayInfos(intArray);    printf("\n");
    printf("[AbstractArrayTest] Sort 1.0 - infos  = "); DisplayArray(intArray);         printf("\n");
    System::AbstractArray::Sort(intArray);
    printf("[AbstractArrayTest] Sort 1.0 - result = "); DisplayArrayInfos(intArray);    printf("\n");
    printf("[AbstractArrayTest] Sort 1.0 - result = "); DisplayArray(intArray);         printf("\n");
    printf("[AbstractArrayTest] Sort 1.1 - infos  = "); DisplayArrayInfos(strArray);    printf("\n");
    printf("[AbstractArrayTest] Sort 1.1 - infos  = "); DisplayArray(strArray);         printf("\n");
    System::AbstractArray::Sort(strArray);
    printf("[AbstractArrayTest] Sort 1.1 - result = "); DisplayArrayInfos(strArray);    printf("\n");
    printf("[AbstractArrayTest] Sort 1.1 - result = "); DisplayArray(strArray);         printf("\n");
    printf("\n");
    
	intArray = CS_NEW System::Array<s32>(6); 
	intArray->_idx$_s(0, 42); intArray->_idx$_s(1, 1337); intArray->_idx$_s(2, 7); 
	intArray->_idx$_s(3, 23); intArray->_idx$_s(4, 2); intArray->_idx$_s(5, 14);
    strArray = CS_NEW System::Array<System::String*>(7);
	strArray->_idx$_s(0, (CS_NEW System::String())->_appendC('q')->_appendClose());
	strArray->_idx$_s(1, (CS_NEW System::String())->_appendC('w')->_appendClose());
	strArray->_idx$_s(2, (CS_NEW System::String())->_appendC('e')->_appendClose());
	strArray->_idx$_s(3, (CS_NEW System::String())->_appendC('r')->_appendClose());
	strArray->_idx$_s(4, (CS_NEW System::String())->_appendC('t')->_appendClose());
	strArray->_idx$_s(5, (CS_NEW System::String())->_appendC('y')->_appendClose());
	strArray->_idx$_s(6, (CS_NEW System::String())->_appendC('Q')->_appendClose());

    printf("[AbstractArrayTest] Sort 2.0 - infos  = "); DisplayArrayInfos(intArray);    printf("\n");
    printf("[AbstractArrayTest] Sort 2.0 - infos  = "); DisplayArray(intArray);         printf("\n");
    System::AbstractArray::Sort(intArray, 1, 3);
    printf("[AbstractArrayTest] Sort 2.0 - result = "); DisplayArrayInfos(intArray);    printf("\n");
    printf("[AbstractArrayTest] Sort 2.0 - result = "); DisplayArray(intArray);         printf("\n");
    printf("[AbstractArrayTest] Sort 2.1 - infos  = "); DisplayArrayInfos(strArray);    printf("\n");
    printf("[AbstractArrayTest] Sort 2.1 - infos  = "); DisplayArray(strArray);         printf("\n");
    System::AbstractArray::Sort(strArray, 3, 4);
    printf("[AbstractArrayTest] Sort 2.1 - result = "); DisplayArrayInfos(strArray);    printf("\n");
    printf("[AbstractArrayTest] Sort 2.1 - result = "); DisplayArray(strArray);         printf("\n");
    printf("\n");
    // TODO : Other sorts.



	printf("\n");
	printf("#########################################\n");
    printf("############### Array<T> ################\n");
	printf("#########################################\n");
    printf("\n");
    printf("\n");

    // Test - Constructor
    // Test - Constructors (normal arrays)
    intArray = CS_NEW System::Array<s32>(6); 
	intArray->_idx$_s(0, 0); intArray->_idx$_s(1, 2); intArray->_idx$_s(2, 4); 
	intArray->_idx$_s(3, 6); intArray->_idx$_s(4, 8); intArray->_idx$_s(5, 10);
    strArray = CS_NEW System::Array<System::String*>(3);
	strArray->_idx$_s(0, (CS_NEW System::String())->_appendC('s')->_appendC('0')->_appendClose());
	strArray->_idx$_s(1, (CS_NEW System::String())->_appendC('s')->_appendC('1')->_appendClose());
	strArray->_idx$_s(2, (CS_NEW System::String())->_appendC('s')->_appendC('2')->_appendClose());

    printf("[ArrayTest] Constructors 1.0 - infos = "); DisplayArrayInfos(intArray); printf("\n");
    printf("[ArrayTest] Constructors 1.0 - infos = "); DisplayArray(intArray);      printf("\n");
    printf("[ArrayTest] Constructors 1.1 - infos = "); DisplayArrayInfos(strArray); printf("\n");
    printf("[ArrayTest] Constructors 1.1 - infos = "); DisplayArray(strArray);      printf("\n");
    printf("\n");

    // Test - BinarySearch
    intArray = CS_NEW System::Array<s32>(6); 
	intArray->_idx$_s(0, 0); intArray->_idx$_s(1, 2); intArray->_idx$_s(2, 4); 
	intArray->_idx$_s(3, 6); intArray->_idx$_s(4, 8); intArray->_idx$_s(5, 10);
    strArray = CS_NEW System::Array<System::String*>(3);
	strArray->_idx$_s(0, (CS_NEW System::String())->_appendC('s')->_appendC('0')->_appendClose());
	strArray->_idx$_s(1, (CS_NEW System::String())->_appendC('s')->_appendC('1')->_appendClose());
	strArray->_idx$_s(2, (CS_NEW System::String())->_appendC('s')->_appendC('2')->_appendClose());

    printf("[ArrayTest] BinarySearch 1.0+ - infos = "); DisplayArrayInfos(intArray); printf("\n");
    printf("[ArrayTest] BinarySearch 1.0+ - infos = "); DisplayArray(intArray);      printf("\n");
    printf("[ArrayTest] BinarySearch 1.2+ - infos = "); DisplayArrayInfos(strArray); printf("\n");
    printf("[ArrayTest] BinarySearch 1.2+ - infos = "); DisplayArray(strArray);      printf("\n");
    printf("[ArrayTest] BinarySearch 1.0 - result = %i\n", System::AbstractArray::BinarySearch(intArray, 3));
	printf("[ArrayTest] BinarySearch 1.1 - result = %i\n", System::AbstractArray::BinarySearch(intArray, 4));
    printf("[ArrayTest] BinarySearch 1.2 - result = %i\n", System::AbstractArray::BinarySearch(strArray, (CS_NEW System::String())->_appendC('t')->_appendClose()));
    printf("[ArrayTest] BinarySearch 1.3 - result = %i\n", System::AbstractArray::BinarySearch(strArray, (CS_NEW System::String())->_appendC('s')->_appendI(0)->_appendClose()));
    printf("\n");
    printf("[ArrayTest] BinarySearch 2.0 - result = %i\n", System::AbstractArray::BinarySearch(intArray, 0, 6, 3));
    printf("[ArrayTest] BinarySearch 2.1 - result = %i\n", System::AbstractArray::BinarySearch(intArray, 1, 1, 4));
    printf("[ArrayTest] BinarySearch 2.2 - result = %i\n", System::AbstractArray::BinarySearch(intArray, 1, 2, 4));
    printf("[ArrayTest] BinarySearch 2.3 - result = %i\n", System::AbstractArray::BinarySearch(strArray, 0, 3, (CS_NEW System::String())->_appendC('s')->_appendI(9)->_appendClose()));
    printf("[ArrayTest] BinarySearch 2.4 - result = %i\n", System::AbstractArray::BinarySearch(strArray, 0, 1, (CS_NEW System::String())->_appendC('s')->_appendI(1)->_appendClose()));
    printf("[ArrayTest] BinarySearch 2.5 - result = %i\n", System::AbstractArray::BinarySearch(strArray, 0, 3, (CS_NEW System::String())->_appendC('s')->_appendI(1)->_appendClose()));
    printf("\n");

    // Test - ConvertAll


    // Test - Exists


    // Test - Find


    // Test - FindAll


    // Test - FindIndex


    // Test - FindLast


    // Test - FindLastIndex


    // Test - ForEach


    // Test - IndexOf
	intArray = CS_NEW System::Array<s32>(6); 
	intArray->_idx$_s(0, 0); intArray->_idx$_s(1, 2); intArray->_idx$_s(2, 4); 
	intArray->_idx$_s(3, 2); intArray->_idx$_s(4, 4); intArray->_idx$_s(5, 0);
    strArray = CS_NEW System::Array<System::String*>(3);
	strArray->_idx$_s(0, (CS_NEW System::String())->_appendC('s')->_appendC('0')->_appendClose());
	strArray->_idx$_s(1, (CS_NEW System::String())->_appendC('s')->_appendC('1')->_appendClose());
	strArray->_idx$_s(2, (CS_NEW System::String())->_appendC('s')->_appendC('0')->_appendClose());

    printf("[ArrayTest] IndexOf 1.0+ - infos = "); DisplayArrayInfos(intArray);    printf("\n");
    printf("[ArrayTest] IndexOf 1.0+ - infos = "); DisplayArray(intArray);         printf("\n");
    printf("[ArrayTest] IndexOf 1.2+ - infos = "); DisplayArrayInfos(strArray);    printf("\n");
    printf("[ArrayTest] IndexOf 1.2+ - infos = "); DisplayArray(strArray);         printf("\n");

    printf("[ArrayTest] IndexOf 1.0 - result = %i\n", System::AbstractArray::IndexOf(intArray, 0));
    printf("[ArrayTest] IndexOf 1.1 - result = %i\n", System::AbstractArray::IndexOf(intArray, 1));
    printf("[ArrayTest] IndexOf 1.2 - result = %i\n", System::AbstractArray::IndexOf(strArray, (CS_NEW System::String())->_appendC('s')->_appendI(0)->_appendClose()));
    printf("[ArrayTest] IndexOf 1.3 - result = %i\n", System::AbstractArray::IndexOf(strArray, 1));
	printf("[ArrayTest] IndexOf 1.4 - result = %i\n", System::AbstractArray::IndexOf(strArray, CS_NEW System::Collections::Generic::List<s32>()));
    printf("\n");
    printf("[ArrayTest] IndexOf 2.0 - result = %i\n", System::AbstractArray::IndexOf(intArray, 2, 0));
    printf("[ArrayTest] IndexOf 2.1 - result = %i\n", System::AbstractArray::IndexOf(intArray, 2, 2));
    printf("[ArrayTest] IndexOf 2.2 - result = %i\n", System::AbstractArray::IndexOf(intArray, 2, 4));
    printf("[ArrayTest] IndexOf 2.3 - result = %i\n", System::AbstractArray::IndexOf(intArray, 1, 0));
    printf("[ArrayTest] IndexOf 2.4 - result = %i\n", System::AbstractArray::IndexOf(strArray, (CS_NEW System::String())->_appendC('s')->_appendI(0)->_appendClose(), 0));
    printf("[ArrayTest] IndexOf 2.5 - result = %i\n", System::AbstractArray::IndexOf(strArray, (CS_NEW System::String())->_appendC('s')->_appendI(0)->_appendClose(), 1));
    printf("[ArrayTest] IndexOf 2.6 - result = %i\n", System::AbstractArray::IndexOf(strArray, 2, 0));
    printf("\n");
    printf("[ArrayTest] IndexOf 3.0 - result = %i\n", System::AbstractArray::IndexOf(intArray, 2, 0, 1));
    printf("[ArrayTest] IndexOf 3.1 - result = %i\n", System::AbstractArray::IndexOf(intArray, 2, 0, 2));
    printf("[ArrayTest] IndexOf 3.2 - result = %i\n", System::AbstractArray::IndexOf(strArray, (CS_NEW System::String())->_appendC('s')->_appendI(0)->_appendClose(), 1, 2));
    printf("[ArrayTest] IndexOf 3.3 - result = %i\n", System::AbstractArray::IndexOf(strArray, 's', 1, 2));
    printf("\n");


    // Test - LastIndexOf
    intArray = CS_NEW System::Array<s32>(6); 
	intArray->_idx$_s(0, 0); intArray->_idx$_s(1, 2); intArray->_idx$_s(2, 4); 
	intArray->_idx$_s(3, 2); intArray->_idx$_s(4, 4); intArray->_idx$_s(5, 0);
    strArray = CS_NEW System::Array<System::String*>(3);
	strArray->_idx$_s(0, (CS_NEW System::String())->_appendC('s')->_appendC('0')->_appendClose());
	strArray->_idx$_s(1, (CS_NEW System::String())->_appendC('s')->_appendC('1')->_appendClose());
	strArray->_idx$_s(2, (CS_NEW System::String())->_appendC('s')->_appendC('0')->_appendClose());

    printf("[ArrayTest] LastIndexOf 1.0+ - infos = "); DisplayArrayInfos(intArray);    printf("\n");
    printf("[ArrayTest] LastIndexOf 1.0+ - infos = "); DisplayArray(intArray);         printf("\n");
    printf("[ArrayTest] LastIndexOf 1.2+ - infos = "); DisplayArrayInfos(strArray);    printf("\n");
    printf("[ArrayTest] LastIndexOf 1.2+ - infos = "); DisplayArray(strArray);         printf("\n");

    printf("[ArrayTest] LastIndexOf 1.0 - result = %i\n", System::AbstractArray::LastIndexOf(intArray, 0));
    printf("[ArrayTest] LastIndexOf 1.1 - result = %i\n", System::AbstractArray::LastIndexOf(intArray, 1));
    printf("[ArrayTest] LastIndexOf 1.2 - result = %i\n", System::AbstractArray::LastIndexOf(strArray, (CS_NEW System::String())->_appendC('s')->_appendI(0)->_appendClose()));
    printf("[ArrayTest] LastIndexOf 1.3 - result = %i\n", System::AbstractArray::LastIndexOf(strArray, 1));
    printf("[ArrayTest] LastIndexOf 1.4 - result = %i\n", System::AbstractArray::LastIndexOf(strArray, CS_NEW System::Collections::Generic::List<s32>()));
    printf("\n");
    printf("[ArrayTest] LastIndexOf 2.0 - result = %i\n", System::AbstractArray::LastIndexOf(intArray, 2, 5));
    printf("[ArrayTest] LastIndexOf 2.1 - result = %i\n", System::AbstractArray::LastIndexOf(intArray, 2, 2));
    printf("[ArrayTest] LastIndexOf 2.2 - result = %i\n", System::AbstractArray::LastIndexOf(intArray, 2, 0));
    printf("[ArrayTest] LastIndexOf 2.3 - result = %i\n", System::AbstractArray::LastIndexOf(intArray, 1, 5));
    printf("[ArrayTest] LastIndexOf 2.4 - result = %i\n", System::AbstractArray::LastIndexOf(strArray, (CS_NEW System::String())->_appendC('s')->_appendI(0)->_appendClose(), 2));
    printf("[ArrayTest] LastIndexOf 2.5 - result = %i\n", System::AbstractArray::LastIndexOf(strArray, (CS_NEW System::String())->_appendC('s')->_appendI(1)->_appendClose(), 0));
    printf("[ArrayTest] LastIndexOf 2.6 - result = %i\n", System::AbstractArray::LastIndexOf(strArray, 2, 2));
    printf("\n");
    printf("[ArrayTest] LastIndexOf 3.0 - result = %i\n", System::AbstractArray::LastIndexOf(intArray, 2, 5, 6));
    printf("[ArrayTest] LastIndexOf 3.1 - result = %i\n", System::AbstractArray::LastIndexOf(intArray, 2, 5, 2));
    printf("[ArrayTest] LastIndexOf 3.2 - result = %i\n", System::AbstractArray::LastIndexOf(strArray, (CS_NEW System::String())->_appendC('s')->_appendI(1)->_appendClose(), 2, 2));
    printf("[ArrayTest] LastIndexOf 3.3 - result = %i\n", System::AbstractArray::LastIndexOf(strArray, 's', 2, 2));
    printf("\n");

    // Test - Resize
    intArray = CS_NEW System::Array<s32>(6); 
	intArray->_idx$_s(0, 0); intArray->_idx$_s(1, 2); intArray->_idx$_s(2, 4); 
	intArray->_idx$_s(3, 6); intArray->_idx$_s(4, 8); intArray->_idx$_s(5, 10);
    strArray = CS_NEW System::Array<System::String*>(3);
	strArray->_idx$_s(0, (CS_NEW System::String())->_appendC('s')->_appendC('0')->_appendClose());
	strArray->_idx$_s(1, (CS_NEW System::String())->_appendC('s')->_appendC('1')->_appendClose());
	strArray->_idx$_s(2, (CS_NEW System::String())->_appendC('s')->_appendC('2')->_appendClose());

    printf("[ArrayTest] Resize 1.0+ - infos = "); DisplayArrayInfos(intArray);   printf("\n");
    printf("[ArrayTest] Resize 1.0+ - infos = "); DisplayArray(intArray);        printf("\n");
    System::AbstractArray::Resize(intArray, 10);
    printf("[ArrayTest] Resize 1.1 - result = "); DisplayArrayInfos(intArray);   printf("\n");
    printf("[ArrayTest] Resize 1.1 - result = "); DisplayArray(intArray);        printf("\n");
    System::AbstractArray::Resize(intArray, 3);
    printf("[ArrayTest] Resize 1.2 - result = "); DisplayArrayInfos(intArray);   printf("\n");
    printf("[ArrayTest] Resize 1.2 - result = "); DisplayArray(intArray);        printf("\n");
            
    printf("[ArrayTest] Resize 1.3+ - infos = "); DisplayArrayInfos(strArray);   printf("\n");
    printf("[ArrayTest] Resize 1.3+ - infos = "); DisplayArray(strArray);        printf("\n");
    System::AbstractArray::Resize(strArray, 10);
    printf("[ArrayTest] Resize 1.3 - result = "); DisplayArrayInfos(strArray);   printf("\n");
    printf("[ArrayTest] Resize 1.3 - result = "); DisplayArray(strArray);        printf("\n");
    System::AbstractArray::Resize(strArray, 3);
    printf("[ArrayTest] Resize 1.4 - result = "); DisplayArrayInfos(strArray);   printf("\n");
    printf("[ArrayTest] Resize 1.4 - result = "); DisplayArray(strArray);        printf("\n");
            
    // Test - Sort
    intArray = CS_NEW System::Array<s32>(6); 
	intArray->_idx$_s(0, 42); intArray->_idx$_s(1, 1337); intArray->_idx$_s(2, 7); 
	intArray->_idx$_s(3, 23); intArray->_idx$_s(4, 2); intArray->_idx$_s(5, 14);
    strArray = CS_NEW System::Array<System::String*>(7);
	strArray->_idx$_s(0, (CS_NEW System::String())->_appendC('q')->_appendClose());
	strArray->_idx$_s(1, (CS_NEW System::String())->_appendC('w')->_appendClose());
	strArray->_idx$_s(2, (CS_NEW System::String())->_appendC('e')->_appendClose());
	strArray->_idx$_s(3, (CS_NEW System::String())->_appendC('r')->_appendClose());
	strArray->_idx$_s(4, (CS_NEW System::String())->_appendC('t')->_appendClose());
	strArray->_idx$_s(5, (CS_NEW System::String())->_appendC('y')->_appendClose());
	strArray->_idx$_s(6, (CS_NEW System::String())->_appendC('Q')->_appendClose());

    printf("[ArrayTest] Sort 1.0 - infos  = "); DisplayArrayInfos(intArray);    printf("\n");
    printf("[ArrayTest] Sort 1.0 - infos  = "); DisplayArray(intArray);         printf("\n");
    System::AbstractArray::Sort(intArray);
    printf("[ArrayTest] Sort 1.0 - result = "); DisplayArrayInfos(intArray);    printf("\n");
    printf("[ArrayTest] Sort 1.0 - result = "); DisplayArray(intArray);         printf("\n");
    printf("[ArrayTest] Sort 1.1 - infos  = "); DisplayArrayInfos(strArray);    printf("\n");
    printf("[ArrayTest] Sort 1.1 - infos  = "); DisplayArray(strArray);         printf("\n");
    System::AbstractArray::Sort(strArray);
    printf("[ArrayTest] Sort 1.1 - result = "); DisplayArrayInfos(strArray);    printf("\n");
    printf("[ArrayTest] Sort 1.1 - result = "); DisplayArray(strArray);         printf("\n");
    printf("\n");
    
	intArray = CS_NEW System::Array<s32>(6); 
	intArray->_idx$_s(0, 42); intArray->_idx$_s(1, 1337); intArray->_idx$_s(2, 7); 
	intArray->_idx$_s(3, 23); intArray->_idx$_s(4, 2); intArray->_idx$_s(5, 14);
    strArray = CS_NEW System::Array<System::String*>(7);
	strArray->_idx$_s(0, (CS_NEW System::String())->_appendC('q')->_appendClose());
	strArray->_idx$_s(1, (CS_NEW System::String())->_appendC('w')->_appendClose());
	strArray->_idx$_s(2, (CS_NEW System::String())->_appendC('e')->_appendClose());
	strArray->_idx$_s(3, (CS_NEW System::String())->_appendC('r')->_appendClose());
	strArray->_idx$_s(4, (CS_NEW System::String())->_appendC('t')->_appendClose());
	strArray->_idx$_s(5, (CS_NEW System::String())->_appendC('y')->_appendClose());
	strArray->_idx$_s(6, (CS_NEW System::String())->_appendC('Q')->_appendClose());

    printf("[ArrayTest] Sort 2.0 - infos  = "); DisplayArrayInfos(intArray);    printf("\n");
    printf("[ArrayTest] Sort 2.0 - infos  = "); DisplayArray(intArray);         printf("\n");
    System::AbstractArray::Sort(intArray, 1, 3);
    printf("[ArrayTest] Sort 2.0 - result = "); DisplayArrayInfos(intArray);    printf("\n");
    printf("[ArrayTest] Sort 2.0 - result = "); DisplayArray(intArray);         printf("\n");
    printf("[ArrayTest] Sort 2.1 - infos  = "); DisplayArrayInfos(strArray);    printf("\n");
    printf("[ArrayTest] Sort 2.1 - infos  = "); DisplayArray(strArray);         printf("\n");
    System::AbstractArray::Sort(strArray, 3, 4);
    printf("[ArrayTest] Sort 2.1 - result = "); DisplayArrayInfos(strArray);    printf("\n");
    printf("[ArrayTest] Sort 2.1 - result = "); DisplayArray(strArray);         printf("\n");
    printf("\n");
    // TODO : Other sorts.

    // Test - TrueForAll


	//#########################################
	//#########################################
	//########## Dictionary Tests #############
	//#########################################
	//#########################################
	
	// Test - Constructor
	printf("#########################################\n");
	printf("#########################################\n");
    printf("########### Dictionary Tests ############\n");
	printf("#########################################\n");
    printf("#########################################\n");
    printf("\n");
    printf("\n");

	System::String* s_red			= (CS_NEW System::String())->_appendC('r')->_appendC('e')->_appendC('d')->_appendClose();
	System::String* s_air			= (CS_NEW System::String())->_appendC('a')->_appendC('i')->_appendC('r')->_appendClose();
	System::String* s_blue			= (CS_NEW System::String())->_appendC('b')->_appendC('l')->_appendC('u')->_appendC('e')->_appendClose();
	System::String* s_green			= (CS_NEW System::String())->_appendC('g')->_appendC('r')->_appendC('e')->_appendC('e')->_appendC('n')->_appendClose();
	System::String* s_water			= (CS_NEW System::String())->_appendC('w')->_appendC('a')->_appendC('t')->_appendC('e')->_appendC('r')->_appendClose();
	System::String* s_yellow		= (CS_NEW System::String())->_appendC('y')->_appendC('e')->_appendC('l')->_appendC('l')->_appendC('o')->_appendC('w')->_appendClose();
	System::String* s_friend		= (CS_NEW System::String())->_appendC('f')->_appendC('r')->_appendC('i')->_appendC('e')->_appendC('n')->_appendC('d')->_appendClose();
	System::String* s_Hitokage		= (CS_NEW System::String())->_appendC('H')->_appendC('i')->_appendC('t')->_appendC('o')->_appendC('k')->_appendC('a')->_appendC('g')->_appendC('e')->_appendClose();
	System::String* s_Zenigame		= (CS_NEW System::String())->_appendC('Z')->_appendC('e')->_appendC('n')->_appendC('i')->_appendC('g')->_appendC('a')->_appendC('m')->_appendC('e')->_appendClose();
	System::String* s_Fushigidane	= (CS_NEW System::String())->_appendC('F')->_appendC('u')->_appendC('s')->_appendC('h')->_appendC('i')->_appendC('g')->_appendC('i')->_appendC('d')->_appendC('a')->_appendC('n')->_appendC('e')->_appendClose();
	System::String* s_Pikachu		= (CS_NEW System::String())->_appendC('P')->_appendC('i')->_appendC('k')->_appendC('a')->_appendC('c')->_appendC('h')->_appendC('u')->_appendClose();
	System::String* s_Lizardo		= (CS_NEW System::String())->_appendC('L')->_appendC('i')->_appendC('z')->_appendC('a')->_appendC('r')->_appendC('d')->_appendC('o')->_appendClose();
	System::String* s_Poppo			= (CS_NEW System::String())->_appendC('P')->_appendC('o')->_appendC('p')->_appendC('p')->_appendC('o')->_appendClose();
	System::String* s_Mew			= (CS_NEW System::String())->_appendC('M')->_appendC('e')->_appendC('w')->_appendClose();



	// GC TEST
	System::Collections::Generic::Dictionary<System::String*,System::String*>* _static_dic = CS_NEW System::Collections::Generic::Dictionary<System::String*,System::String*>();
    _static_dic->Add(s_red   , s_Hitokage);
    _static_dic->Add(s_blue  , s_Zenigame);
    _static_dic->Add(s_green , s_Fushigidane);
    _static_dic->Add(s_yellow, s_Pikachu);
    _static_dic->Add(s_friend, s_Pikachu);
	System::Memory::registerGCRoot(&_static_dic);
	// END GC TEST


    // Test - Contructor
    System::Collections::Generic::Dictionary<System::String*,System::String*>* dic = CS_NEW System::Collections::Generic::Dictionary<System::String*,System::String*>();
    printf("[DictionaryTest] Constructors 1.0 - Count = %i\n", dic->_acc_gCount());
    printf("[DictionaryTest] Constructors 1.0 - Display\n");  
    DisplayDictionary(dic);
    printf("\n");
            
    // Test - Add
    printf("[DictionaryTest] Add 1.0+ - before - Count = %i\n", dic->_acc_gCount());
    printf("[DictionaryTest] Add 1.0+ - before - Display\n");  
    DisplayDictionary(dic);
    printf("\n");
            
    dic->Add(s_red   , s_Hitokage);
    dic->Add(s_blue  , s_Zenigame);
    dic->Add(s_green , s_Fushigidane);
    dic->Add(s_yellow, s_Pikachu);
    dic->Add(s_friend, s_Pikachu);
            
    printf("[DictionaryTest] Add 1.0 - result - Count = %i\n", dic->_acc_gCount());
    printf("[DictionaryTest] Add 1.0 - result - Display\n");  
    DisplayDictionary(dic);
	
    TRY
        dic->Add(s_red, s_Lizardo);
	CTRY
    FIRSTCATCH(System::ArgumentException, ex)
        printf("[DictionaryTest] Add 1.1 - An element with Key = \"red\" already exists.\n");
	FINALLY
    ETRY
    printf("\n");
	
    // Test - Item
    printf("[DictionaryTest] Item 1.0+ - before - Count = %i\n", dic->_acc_gCount());
    printf("[DictionaryTest] Item 1.0+ - before - Display\n");  
    DisplayDictionary(dic);

	printf("[DictionaryTest] Item 1.0 - dic[\"red\"]    - result = %s\n", dic->_idx_g(s_red)->_toCStr());
    printf("[DictionaryTest] Item 1.1 - dic[\"yellow\"] - result = %s\n", dic->_idx_g(s_yellow)->_toCStr());

    dic->_idx_s(s_red, s_Lizardo);
    printf("[DictionaryTest] Item 1.2 - dic[\"red\"]    - result = %s\n", dic->_idx_g(s_red)->_toCStr());
            
    dic->_idx_s(s_air, s_Poppo);
            
    printf("[DictionaryTest] Item 1.0-1.2 - result - Count = %i\n", dic->_acc_gCount());
    printf("[DictionaryTest] Item 1.0-1.2 - result - Display\n");  
    DisplayDictionary(dic);
	
    TRY
        printf("[DictionaryTest] Item 1.3 - dic[\"water\"] - result = %s\n", dic->_idx_g(s_water)->_toCStr());
    CTRY
	FIRSTCATCH(System::Collections::Generic::KeyNotFoundException, ex)
        printf("[DictionaryTest] Item 1.3 - dic[\"water\"] - result = Not found.\n");
    FINALLY
	ETRY
    printf("\n");
	
    // Test - Clear
    printf("[DictionaryTest] Clear 1.0 - before - Count = %i\n", dic->_acc_gCount());
    printf("[DictionaryTest] Clear 1.0 - before - Display\n");  
    DisplayDictionary(dic);

    dic->Clear();

    printf("[DictionaryTest] Clear 1.0 - result - Count = %i\n", dic->_acc_gCount());
    printf("[DictionaryTest] Clear 1.0 - result - Display\n");  
    DisplayDictionary(dic);
    printf("\n");

    // Test - ContainsKey
	dic->Add(s_red   , s_Hitokage);
    dic->Add(s_blue  , s_Zenigame);
    dic->Add(s_green , s_Fushigidane);
    dic->Add(s_yellow, s_Pikachu);
    dic->Add(s_friend, s_Pikachu);

    printf("[DictionaryTest] ContainsKey 1.0+ - before - Count = %i\n", dic->_acc_gCount());
    printf("[DictionaryTest] ContainsKey 1.0+ - before - Display\n");  
    DisplayDictionary(dic);

    printf("[DictionaryTest] ContainsKey 1.0 - ContainsKey(\"red\")   - result = %s\n", (dic->ContainsKey(s_red))	? "True":"False");
    printf("[DictionaryTest] ContainsKey 1.1 - ContainsKey(\"water\") - result = %s\n", (dic->ContainsKey(s_water)) ? "True":"False");
    printf("\n");

        // Test - ContainsValue
    printf("[DictionaryTest] ContainsValue 1.0+ - before - Count = %i\n", dic->_acc_gCount());
    printf("[DictionaryTest] ContainsValue 1.0+ - before - Display\n");  
    DisplayDictionary(dic);

    printf("[DictionaryTest] ContainsValue 1.0 - ContainsValue(\"Pikachu\") - result = %s\n", (dic->ContainsValue(s_Pikachu)) ? "True":"False");
    printf("[DictionaryTest] ContainsValue 1.1 - ContainsValue(\"Mew\")     - result = %s\n", (dic->ContainsValue(s_Mew))	  ? "True":"False");
    printf("\n");

    // Test - Remove
    printf("[DictionaryTest] Remove 1.0+ - before - Count = %i\n", dic->_acc_gCount());
    printf("[DictionaryTest] Remove 1.0+ - before - Display\n");  
    DisplayDictionary(dic);

    dic->Remove(s_friend);

    printf("[DictionaryTest] Remove 1.0 - result - Count = %i\n", dic->_acc_gCount());
    printf("[DictionaryTest] Remove 1.0 - result - Display\n");  
    DisplayDictionary(dic);
    printf("\n");

    // Test - TryGetValue
	s = NULL;
    if(dic->TryGetValue(s_red, s)) {
		printf("[DictionaryTest] TryGetValue 1.0 - TryGetValue(\"red\")   - result = %s\n", s->_toCStr()); 
    } else {
        printf("[DictionaryTest] TryGetValue 1.0 - TryGetValue(\"red\")   - result = Not found.\n");
    }

    if(dic->TryGetValue(s_water, s)) {
		printf("[DictionaryTest] TryGetValue 1.1 - TryGetValue(\"water\") - result = %s\n", s->_toCStr()); 
    } else {
        printf("[DictionaryTest] TryGetValue 1.1 - TryGetValue(\"water\") - result = Not found.\n");
    }
    printf("\n");
	

	// GC TEST
	// Garbage Collection
	System::Memory::compactionMS((System::Memory::COMPACT_GEN0 | System::Memory::COMPACT_GEN1 | System::Memory::COMPACT_NOW));
	
	DisplayList(_static_strList);	printf("\n");
	DisplayArray(_static_strArray); printf("\n");
	DisplayDictionary(_static_dic); printf("\n");
	
	// SECOND COMPACTION
	System::Memory::compactionSmall((System::Memory::COMPACT_GEN0 | System::Memory::COMPACT_GEN1 | System::Memory::COMPACT_NOW));
	
	DisplayList(_static_strList);	printf("\n");
	DisplayArray(_static_strArray); printf("\n");
	DisplayDictionary(_static_dic); printf("\n");

	// END GC TEST

	return 0;
}

bool init() {
	__InternalUtils::init();
	System::_x_StringGlobalAllocator::init(500);
	System::String::init();
	
	return true;
}

// TODO D : Assignment of struct from code, via var, member.
// TODO E : Verifiy struct with Delegate
// TODO F : Verify ref & related.

#include "inline/generated.inl"

int main() {
	if (System::Memory::setGlobalMemory(1500000, 500,4096,4096)) {
		int i = 0;
		TRY
			init();
			//main_tests();
			registerWorldGC();
			CSharpTests::Program::Main(NULL);
			//InternalTests::GCTestArray();
			//InternalTests::GCTestList();
			//InternalTests::GCTestDictionary();


			// GC TEST
			// Garbage Collection
			System::Memory::compactionMS((System::Memory::COMPACT_GEN0 | System::Memory::COMPACT_GEN1 | System::Memory::COMPACT_NOW));
	
			printf("--------------------------------\n");
			printf("--------------------------------\n");
			printf("-------------       ------------\n");
			printf("--------------------------------\n");
			printf("--------------------------------\n");

			// SECOND COMPACTION
			System::Memory::compactionSmall((System::Memory::COMPACT_GEN0 | System::Memory::COMPACT_GEN1 | System::Memory::COMPACT_NOW));
	
			// END GC TEST

		CTRY
		FIRSTCATCH(System::Exception, ex)
			System::Console::WriteLine();
			printf("EXCEPTION");
			System::Console::WriteLine();
			System::Console::WriteLine(ex->ToString$());
			System::Console::WriteLine(ex->_acc_gMessage$());
		FINALLY
		ETRY

	#ifdef _WIN32
		system("pause");
	#endif
	}

	return 0;
}
