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
using System;

namespace EnginePrototype
{
    /// <summary>
    /// Generic exception.
    /// </summary>
	public class CKLBException : Exception
	{
		public CKLBException(String msg = "") : base(msg)
		{
		}
	}

    /// <summary>
    /// Design a class or method which is not implemented yet.
    /// </summary>
	public class CKLBExceptionNotImplemented : CKLBException
	{
		public CKLBExceptionNotImplemented(String msg = "Not implemented") : base(msg)
		{
		}
	}

    /// <summary>
    /// Design a method which cannot not be used.
    /// </summary>
	public class CKLBExceptionForbiddenMethod : CKLBException
	{
		public CKLBExceptionForbiddenMethod(String msg = "Forbidden Method") : base(msg)
		{
		}
	}

    /// <summary>
    /// Used when an object tries to use a method on its C++ object when the CppObject pointer is null.
    /// </summary>
	public class CKLBExceptionNullCppObject : CKLBException
	{
		public CKLBExceptionNullCppObject(String msg = "Null CppObject Pointer.") : base(msg)
		{
		}
	}

    /// <summary>
    /// Used when an iterator or a related object is used whereas it is too old to be used.
    /// That means you must create another one.
    /// </summary>
    public class CKLBExceptionTooOld : CKLBException
    {
		public CKLBExceptionTooOld(String msg = "Use iterator or related object created in a different time frame / call back.") : base(msg)
		{
		}
    }
}

