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
#include "MemoryTests.h"
#include "CS_Object.h"
#include "CS_Memory.h"
#include "CS_Array.h"
#include "CS_String.h"
#include "CS_List.h"
#include "CS_Dictionary.h"

namespace InternalTests {

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


	/*static*/
	void RefSetValueTests() {
		//printf("#########################################\n");
		//printf("#########################################\n");
		//printf("############# Memory Tests ##############\n");
		//printf("#########################################\n");
		//printf("#########################################\n");
	
		System::Object* _obj	= NULL;
		System::Object* _obj1	= NULL;
		System::Object* _obj2	= NULL;
		System::Object* _obj3	= NULL;
		System::Object* _obj4	= NULL;
		System::Object* _obj5	= NULL;
		System::Object* _obj6	= NULL;
		System::Object* _obj7	= NULL;
		System::Object* _obj8	= NULL;
		System::Object* _obj9	= NULL;


		// Adding	1 refs on _obj
		// Removing 1 ref
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);

		// Adding	2 refs on _obj
		// Removing 2 refs
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);

		// Adding	3 refs on _obj
		// Removing 3 refs
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);

		// Adding	4 refs on _obj
		// Removing 4 refs
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);


		// Adding 5 refs
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);

		// Adding 10 values
		// Removing the 2nde page
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); 
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); 
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj5, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj6, _obj); 
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj7, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj8, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj9, _obj); 
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj5, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj6, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj7, NULL);

		// Adding 10 values
		// Removing the 1st page
		// Removing the 3rd page (now 2nd)
		// Removing the last one -> return to __GCObject pointers in __GCObject.
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object); 
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, _obj); 
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj5, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj6, _obj); 
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj7, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj8, _obj); System::__GCObject::_RefSetValue((System::__GCObject**)&_obj9, _obj); 
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj,  NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj2, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj3, NULL);
		
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj8, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj9, NULL);

		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj4, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj5, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj6, NULL);
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj7, NULL);
	}


	/*static*/
	void GCTest1() {

		System::Object* _obj	= NULL;
		System::Object* _obj1	= NULL;
		System::Object* _obj2	= NULL;
		System::Object* _obj3	= NULL;
		System::Object* _obj4	= NULL;
		System::Object* _obj5	= NULL;
		System::Object* _obj6	= NULL;
		System::Object* _obj7	= NULL;
		System::Object* _obj8	= NULL;
		System::Object* _obj9	= NULL;

		// Create 1 object and set 10 pointers to it.
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj, CS_NEW System::Object);	// add new Object [obj0]
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, CS_NEW System::Object);	// add new Object [obj1]
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, CS_NEW System::Object);	// remove [obj1] add new Object [obj2]
		System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, NULL);					// remove [obj2]
		//System::__GCObject::_RefSetValue((System::__GCObject**)&_obj1, CS_NEW System::Object);	// add new Object [obj3]
		

		/*
		printf("#########################################\n");
		printf("#########################################\n");
		printf("#### Mark & Sweep without compaction ####\n");
		printf("#########################################\n");
		printf("#########################################\n");

		System::Memory::compactionMS((System::Memory::COMPACT_GEN0 | System::Memory::COMPACT_GEN1));
		*/
		
		printf("#########################################\n");
		printf("#########################################\n");
		printf("###### Mark & Sweep with compaction #####\n");
		printf("#########################################\n");
		printf("#########################################\n");

		System::Memory::compactionMS((System::Memory::COMPACT_GEN0 | System::Memory::COMPACT_GEN1 | System::Memory::COMPACT_NOW));
		

		/*
		printf("#########################################\n");
		printf("#########################################\n");
		printf("# Compaction based on Reference Counting#\n");
		printf("#########################################\n");
		printf("#########################################\n");

		System::Memory::compactionSmall();
		*/
	}

	/*static*/
	void GCTestArray() {		
		// Array of String
		System::Array<System::String*> * strArray	= NULL;
		strArray = CS_NEW System::Array<System::String*>(3);
		System::String* s = (CS_NEW System::String())->_appendC('S')->_appendC('T')->_appendC('R')->_appendClose();
		strArray->_idx$_s(0, s);
		strArray->_idx$_s(1, System::String::Empty);
		strArray->_idx$_s(2, s);
		
		// Fake static array
		System::Array<System::String*> * _static_strArray	= NULL;
		_static_strArray = CS_NEW System::Array<System::String*>(3);
		_static_strArray->_idx$_s(0, (CS_NEW System::String())->_appendC('s')->_appendC('0')->_appendClose());
		_static_strArray->_idx$_s(1, System::String::Empty);
		_static_strArray->_idx$_s(2, System::String::Copy(s));

		System::Memory::registerGCRoot(&_static_strArray);

		// Array of int
		
		System::Array<s32> * intArray	= NULL;
		intArray = CS_NEW System::Array<s32>(3);
		intArray->_idx$_s(0, 4);
		intArray->_idx$_s(1, 2);
		intArray->_idx$_s(2, 1);
		
		/*
		printf("#########################################\n");
		printf("#########################################\n");
		printf("###### Mark & Sweep with compaction #####\n");
		printf("#########################################\n");
		printf("#########################################\n");

		System::Memory::compactionMS((System::Memory::COMPACT_GEN0 | System::Memory::COMPACT_GEN1 | System::Memory::COMPACT_NOW));
		*/
		
		printf("#########################################\n");
		printf("#########################################\n");
		printf("#### Mark & Sweep without compaction ####\n");
		printf("#########################################\n");
		printf("#########################################\n");

		System::Memory::compactionMS();
		
		printf("#########################################\n");
		printf("#########################################\n");
		printf("# Compaction based on Reference Counting#\n");
		printf("#########################################\n");
		printf("#########################################\n");

		System::Memory::compactionSmall((System::Memory::COMPACT_GEN0 | System::Memory::COMPACT_GEN1));
		

		DisplayArray(_static_strArray);
	}

	/*static*/
	void GCTestList() {	
		System::Collections::Generic::List<s32>				*intList = NULL;
		System::Collections::Generic::List<System::String*> *strList = NULL;
		System::Collections::Generic::List<System::String*> *_static_strList = NULL;

		System::__GCObject::_RefSetValue((System::__GCObject**)&intList, CS_NEW System::Collections::Generic::List<s32>(3));
		System::__GCObject::_RefSetValue((System::__GCObject**)&strList, CS_NEW System::Collections::Generic::List<System::String*>());

		_static_strList = CS_NEW System::Collections::Generic::List<System::String*>(1);
		for(int i = 0; i < 9; ++i) {
			_static_strList->Add((CS_NEW System::String())->_appendC('s')->_appendC('t')->_appendC('r')->_appendI(i*2)->_appendClose());
		}
		printf("Static String List : ");
		DisplayListInfos(_static_strList);    printf("\n");
		DisplayList(_static_strList);         printf("\n");


		for(int i = 0; i < 8; ++i) {
			intList->Add(i*2);
			strList->Add((CS_NEW System::String())->_appendC('s')->_appendC('t')->_appendC('r')->_appendI(i*2)->_appendClose());
		}

		printf("Int List : ");
		DisplayListInfos(intList);    printf("\n");
		DisplayList(intList);         printf("\n");
		printf("String List : ");
		DisplayListInfos(strList);    printf("\n");
		DisplayList(strList);         printf("\n");

		System::Memory::registerGCRoot(&_static_strList);
		

		/*
		printf("#########################################\n");
		printf("#########################################\n");
		printf("###### Mark & Sweep with compaction #####\n");
		printf("#########################################\n");
		printf("#########################################\n");

		System::Memory::compactionMS((System::Memory::COMPACT_GEN0 | System::Memory::COMPACT_GEN1 | System::Memory::COMPACT_NOW));
		*/
		

		printf("#########################################\n");
		printf("#########################################\n");
		printf("#### Mark & Sweep without compaction ####\n");
		printf("#########################################\n");
		printf("#########################################\n");

		System::Memory::compactionMS();

		printf("#########################################\n");
		printf("#########################################\n");
		printf("# Compaction based on Reference Counting#\n");
		printf("#########################################\n");
		printf("#########################################\n");

		System::Memory::compactionSmall((System::Memory::COMPACT_GEN0 | System::Memory::COMPACT_GEN1));
		
		printf("Static String List : ");
		DisplayListInfos(_static_strList);    printf("\n");
		DisplayList(_static_strList);         printf("\n");

	}

		/*static*/
	void GCTestDictionary() {	
		
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

		// Test - Contructor
		System::Collections::Generic::Dictionary<System::String*,System::String*>* dic = NULL;
		dic = CS_NEW System::Collections::Generic::Dictionary<System::String*,System::String*>(1);
		System::Memory::registerGCRoot(&dic);
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

		
		printf("#########################################\n");
		printf("#########################################\n");
		printf("###### Mark & Sweep with compaction #####\n");
		printf("#########################################\n");
		printf("#########################################\n");

		System::Memory::compactionMS((System::Memory::COMPACT_GEN0 | System::Memory::COMPACT_GEN1 | System::Memory::COMPACT_NOW));
		
		/*
		printf("#########################################\n");
		printf("#########################################\n");
		printf("#### Mark & Sweep without compaction ####\n");
		printf("#########################################\n");
		printf("#########################################\n");

		System::Memory::compactionMS((System::Memory::COMPACT_GEN0 | System::Memory::COMPACT_GEN1));

		printf("#########################################\n");
		printf("#########################################\n");
		printf("# Compaction based on Reference Counting#\n");
		printf("#########################################\n");
		printf("#########################################\n");

		System::Memory::compactionSmall();
		*/

		DisplayDictionary(dic);
	}
}
