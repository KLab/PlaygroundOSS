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
namespace System
{
	//Object Class
	public class Object
	{
        public Object() {}
		public virtual	bool	Equals			(Object obj){}
		public static	bool	Equals			(Object objA, Object objB){}
		public virtual int		GetHashCode		(){}
		/*public Type GetType(){}	Not Supported for now, but should be in the future : allow data loader using reflection*/
		// This is NOT a correct definition, but it allows to use this method for debug in C#.
		public string 			GetType			(){}
		public virtual int		CompareTo		(Object obj){} // Implementation of IComparable
		public static bool		ReferenceEquals	(Object objA, Object objB){}
		public virtual String	ToString		(){}
	}
	
	public class IntPtr : Object
	{
		public static const IntPtr Zero = null;  // Value set to null by compiler, works !
		public static const int    Size = 0;
	}
	
	//Exceptions
	public class Exception : Object {
		public string Message { get {} }
		public string StackTrace { get {} }
	}
	public class SystemException 				: Exception {}
	public class NullReferenceException 		: SystemException {}
	public class IndexOutOfRangeException 		: SystemException {}
	public class OutOfMemoryException 			: SystemException {}
	public class ArgumentException 				: SystemException {}
	public class ArgumentOutOfRangeException 	: ArgumentException {}
	public class ArgumentNullException 			: ArgumentException {}
	public class RankException 					: SystemException {}
	public class CppNotComparable 				: SystemException {}
	public class InvalidOperationException 		: SystemException {}
	public class ArrayTypeMismatchException 	: SystemException {}
	public class ArithmeticException 			: SystemException {}
	public class DivideByZeroException 			: ArithmeticException {}
	
	//Array
    public abstract class Array<T> : Object
    {
        //AbstractArray Part

		//public bool IsFixedSize { get{} }
		//public bool IsReadOnly { get{} }
		//public bool IsSynchronized { get{} }
		public int Length { get{} }
		public long LongLength { get{} }
		public int Rank { get{} }
		//public Object SyncRoot { get{} }
        
        //[Hint replace Array -> AbstractArray]
		public static int BinarySearch(Array Array, Object value){}
		public static int BinarySearch(Array Array, sbyte value){}
		public static int BinarySearch(Array Array, byte value){}
		public static int BinarySearch(Array Array, short value){}
		public static int BinarySearch(Array Array, ushort value){}
		public static int BinarySearch(Array Array, int value){}
		public static int BinarySearch(Array Array, uint value){}
		public static int BinarySearch(Array Array, long value){}
		public static int BinarySearch(Array Array, ulong value){}
		public static int BinarySearch(Array Array, float value){}
		public static int BinarySearch(Array Array, double value){}
		public static int BinarySearch(Array Array, bool value){}		
		//public static int BinarySearch(Array Array, Object value, IComparer comparer){}		
		public static int BinarySearch(Array Array, int index, int length, Object value){}
		public static int BinarySearch(Array Array, int index, int length, sbyte value){}
		public static int BinarySearch(Array Array, int index, int length, byte value){}
		public static int BinarySearch(Array Array, int index, int length, short value){}
		public static int BinarySearch(Array Array, int index, int length, ushort value){}
		public static int BinarySearch(Array Array, int index, int length, int value){}
		public static int BinarySearch(Array Array, int index, int length, uint value){}
		public static int BinarySearch(Array Array, int index, int length, long value){}
		public static int BinarySearch(Array Array, int index, int length, ulong value){}
		public static int BinarySearch(Array Array, int index, int length, float value){}
		public static int BinarySearch(Array Array, int index, int length, double value){}
		public static int BinarySearch(Array Array, int index, int length, bool value){}
		//public static int BinarySearch(Array Array, int index, int length, Object value, IComparer comparer){}
		public static void Clear(Array Array, int index, int length){}
		public Object Clone(){}
		//public static void ConstrainedCopy(Array sourceArray, int sourceIndex, Array destinationArray, int destinationIndex, int length){}
		//public static void Copy(Array sourceArray, Array destinationArray, int length){}
		//public static void Copy(Array sourceArray, Array destinationArray, long length){}
		//public static void Copy(Array sourceArray, int sourceIndex, Array destinationArray, int destinationIndex, int length){}
		//public static void Copy(Array sourceArray, long sourceIndex, Array destinationArray, long destinationIndex, long length){}
		//public void CopyTo(Array Array, int index){}
		//public void CopyTo(Array Array, long index){}
		//public static Array CreateInstance(Type elementType, int length){}
		//public static Array CreateInstance(Type elementType, params int[] lengths){}
		//public static Array CreateInstance(Type elementType, params long[] lengths){}
		//public static Array CreateInstance(Type elementType, int length1, int length2){}
		//public static Array CreateInstance(Type elementType, int[] lengths, int[] lowerBounds){}
		//public static Array CreateInstance(Type elementType, int length1, int length2, int length3){}
		public IEnumerator<T> GetEnumerator(){}
		public int GetLength(int dimension){}
		public long GetLongLength(int dimension){}
		public int GetLowerBound(int dimension){}
		public int GetUpperBound(int dimension){}

        // GetValue() functions will never be implemented
		//public Object GetValue(int index){}
		//public Object GetValue(long index){}
		//public Object GetValue(params int[] indices){}
		//public Object GetValue(params long[] indices){}
		//public Object GetValue(int index1, int index2){}
		//public Object GetValue(long index1, long index2){}
		//public Object GetValue(int index1, int index2, int index3){}
		//public Object GetValue(long index1, long index2, long index3){}

		public static int IndexOf(Array Array, Object   value) { }
        public static int IndexOf(Array Array, sbyte    value) { }
        public static int IndexOf(Array Array, byte     value) { }
        public static int IndexOf(Array Array, short    value) { }
        public static int IndexOf(Array Array, ushort   value) { }
        public static int IndexOf(Array Array, int      value) { }
        public static int IndexOf(Array Array, uint     value) { }
        public static int IndexOf(Array Array, long     value) { }
        public static int IndexOf(Array Array, ulong    value) { }
        public static int IndexOf(Array Array, double   value) { }
        public static int IndexOf(Array Array, float    value) { }
        public static int IndexOf(Array Array, bool     value) { }

        public static int IndexOf(Array Array, Object   value, int startIndex) { }
        public static int IndexOf(Array Array, sbyte    value, int startIndex) { }
        public static int IndexOf(Array Array, byte     value, int startIndex) { }
        public static int IndexOf(Array Array, short    value, int startIndex) { }
        public static int IndexOf(Array Array, ushort   value, int startIndex) { }
        public static int IndexOf(Array Array, int      value, int startIndex) { }
        public static int IndexOf(Array Array, uint     value, int startIndex) { }
        public static int IndexOf(Array Array, long     value, int startIndex) { }
        public static int IndexOf(Array Array, ulong    value, int startIndex) { }
        public static int IndexOf(Array Array, double   value, int startIndex) { }
        public static int IndexOf(Array Array, float    value, int startIndex) { }
        public static int IndexOf(Array Array, bool     value, int startIndex) { }

        public static int IndexOf(Array Array, Object   value, int startIndex, int count) { }
        public static int IndexOf(Array Array, sbyte    value, int startIndex, int count) { }
        public static int IndexOf(Array Array, byte     value, int startIndex, int count) { }
        public static int IndexOf(Array Array, short    value, int startIndex, int count) { }
        public static int IndexOf(Array Array, ushort   value, int startIndex, int count) { }
        public static int IndexOf(Array Array, int      value, int startIndex, int count) { }
        public static int IndexOf(Array Array, uint     value, int startIndex, int count) { }
        public static int IndexOf(Array Array, long     value, int startIndex, int count) { }
        public static int IndexOf(Array Array, ulong    value, int startIndex, int count) { }
        public static int IndexOf(Array Array, double   value, int startIndex, int count) { }
        public static int IndexOf(Array Array, float    value, int startIndex, int count) { }
        public static int IndexOf(Array Array, bool     value, int startIndex, int count) { }

		//public void Initialize(){}
        public static int LastIndexOf(Array Array, Object value) { }
        public static int LastIndexOf(Array Array, sbyte value) { }
        public static int LastIndexOf(Array Array, byte value) { }
        public static int LastIndexOf(Array Array, short value) { }
        public static int LastIndexOf(Array Array, ushort value) { }
        public static int LastIndexOf(Array Array, int value) { }
        public static int LastIndexOf(Array Array, uint value) { }
        public static int LastIndexOf(Array Array, long value) { }
        public static int LastIndexOf(Array Array, ulong value) { }
        public static int LastIndexOf(Array Array, double value) { }
        public static int LastIndexOf(Array Array, float value) { }
        public static int LastIndexOf(Array Array, bool value) { }

        public static int LastIndexOf(Array Array, Object value, int startIndex) { }
        public static int LastIndexOf(Array Array, sbyte value, int startIndex) { }
        public static int LastIndexOf(Array Array, byte value, int startIndex) { }
        public static int LastIndexOf(Array Array, short value, int startIndex) { }
        public static int LastIndexOf(Array Array, ushort value, int startIndex) { }
        public static int LastIndexOf(Array Array, int value, int startIndex) { }
        public static int LastIndexOf(Array Array, uint value, int startIndex) { }
        public static int LastIndexOf(Array Array, long value, int startIndex) { }
        public static int LastIndexOf(Array Array, ulong value, int startIndex) { }
        public static int LastIndexOf(Array Array, double value, int startIndex) { }
        public static int LastIndexOf(Array Array, float value, int startIndex) { }
        public static int LastIndexOf(Array Array, bool value, int startIndex) { }

        public static int LastIndexOf(Array Array, Object value, int startIndex, int count) { }
        public static int LastIndexOf(Array Array, sbyte value, int startIndex, int count) { }
        public static int LastIndexOf(Array Array, byte value, int startIndex, int count) { }
        public static int LastIndexOf(Array Array, short value, int startIndex, int count) { }
        public static int LastIndexOf(Array Array, ushort value, int startIndex, int count) { }
        public static int LastIndexOf(Array Array, int value, int startIndex, int count) { }
        public static int LastIndexOf(Array Array, uint value, int startIndex, int count) { }
        public static int LastIndexOf(Array Array, long value, int startIndex, int count) { }
        public static int LastIndexOf(Array Array, ulong value, int startIndex, int count) { }
        public static int LastIndexOf(Array Array, double value, int startIndex, int count) { }
        public static int LastIndexOf(Array Array, float value, int startIndex, int count) { }
        public static int LastIndexOf(Array Array, bool value, int startIndex, int count) { }
		public static void Reverse(Array Array){}
		public static void Reverse(Array Array, int index, int length){}

        // SetValue should never be implemented
		//public void SetValue(Object value, int index){}
		//public void SetValue(Object value, long index){}
		//public void SetValue(Object value, params int[] indices){}
		//public void SetValue(Object value, params long[] indices){}
		//public void SetValue(Object value, int index1, int index2){}
		//public void SetValue(Object value, long index1, long index2){}
		//public void SetValue(Object value, int index1, int index2, int index3){}
		//public void SetValue(Object value, long index1, long index2, long index3){}

		public static void Sort(Array Array){}
		//public static void Sort(Array keys, Array items){}
		//public static void Sort(Array Array, IComparer comparer){}		
		//public static void Sort(Array keys, Array items, IComparer comparer){}
		public static void Sort(Array Array, int index, int length){}	
		//public static void Sort(Array keys, Array items, int index, int length){}
		//public static void Sort(Array Array, int index, int length, IComparer comparer){}	
		//public static void Sort(Array keys, Array items, int index, int length, IComparer comparer){}

        //public static void Sort<TKey, TValue>(TKey[] keys, TValue[] items) { }
        //public static void Sort<TKey, TValue>(TKey[] keys, TValue[] items, IComparer<TKey> comparer){}
        //public static void Sort<TKey, TValue>(TKey[] keys, TValue[] items, int index, int length){}
        //public static void Sort<TKey, TValue>(TKey[] keys, TValue[] items, int index, int length, IComparer<TKey> comparer){}

	    //Array Part

        public T this[int index] { get { } set { } }
        public static int BinarySearch(T[] array, T value) { }
        //public static int BinarySearch<T>(T[] array, T value, IComparer<T> comparer){}
        public static int BinarySearch<T>(T[] array, int index, int length, T value) { }
        //public static int BinarySearch<T>(T[] array, int index, int length, T value, IComparer<T> comparer){}
        //public static TOutput[] ConvertAll<TInput, TOutput>(TInput[] array, Converter<TInput, TOutput> converter){}
        //public static bool Exists<T>(T[] array, Predicate<T> match){}
        //public static T Find<T>(T[] array, Predicate<T> match){}
        //public static T[] FindAll<T>(T[] array, Predicate<T> match){}
        //public static int FindIndex<T>(T[] array, Predicate<T> match){}
        //public static int FindIndex<T>(T[] array, int startIndex, Predicate<T> match){}
        //public static int FindIndex<T>(T[] array, int startIndex, int count, Predicate<T> match){}
        //public static T FindLast<T>(T[] array, Predicate<T> match){}
        //public static int FindLastIndex<T>(T[] array, Predicate<T> match){}
        //public static int FindLastIndex<T>(T[] array, int startIndex, Predicate<T> match){}
        //public static int FindLastIndex<T>(T[] array, int startIndex, int count, Predicate<T> match){}
        //public static void ForEach<T>(T[] array, Action<T> action){}
        public static int IndexOf<T>(T[] array, T value) { }
        public static int IndexOf<T>(T[] array, T value, int startIndex) { }
        public static int IndexOf<T>(T[] array, T value, int startIndex, int count) { }
        public static int LastIndexOf<T>(T[] array, T value) { }
        public static int LastIndexOf<T>(T[] array, T value, int startIndex) { }
        public static int LastIndexOf<T>(T[] array, T value, int startIndex, int count) { }
        public static void Resize<T>(ref T[] array, int newSize) { }
        public static void Sort<T>(T[] array) { }
        //public static void Sort<T>(T[] array, Comparison<T> comparison){}
        //public static void Sort<T>(T[] array, IComparer<T> comparer){}
        public static void Sort<T>(T[] array, int index, int length) { }
        //public static void Sort<T>(T[] array, int index, int length, IComparer<T> comparer){}
        //public static bool TrueForAll<T>(T[] array, Predicate<T> match){}
	}
	
	//String
    public sealed class String : Object
    {
		public static readonly string Empty{}

		//public String(char* value){}
		public String(char[] value){}
		//public String(sbyte* value){}
		public String(char c, int count){}
		//public String(char* value, int startIndex, int length){}
		public String(char[] value, int startIndex, int length){}
		//public String(sbyte* value, int startIndex, int length){}
		//public String(sbyte* value, int startIndex, int length, Encoding enc){}

//	    COMPILER ERROR : overloading not supported yet. Functions are implemented though.
//		public static bool operator !=(string a, string b){}
//		public static bool operator ==(string a, string b){}

		public int Length { get{} }

		public char this[int index] { get{} }

		public Object Clone(){}
		public static int Compare(string strA, string strB){}
		public static int Compare(string strA, string strB, bool ignoreCase){}
		//public static int Compare(string strA, string strB, StringComparison comparisonType){}
		//public static int Compare(string strA, string strB, bool ignoreCase, CultureInfo culture){}
		//public static int Compare(string strA, string strB, CultureInfo culture, CompareOptions options){}
		//public static int Compare(string strA, int indexA, string strB, int indexB, int length){}
		//public static int Compare(string strA, int indexA, string strB, int indexB, int length, bool ignoreCase){}
		//public static int Compare(string strA, int indexA, string strB, int indexB, int length, StringComparison comparisonType){}
		//public static int Compare(string strA, int indexA, string strB, int indexB, int length, bool ignoreCase, CultureInfo culture){}
		//public static int Compare(string strA, int indexA, string strB, int indexB, int length, CultureInfo culture, CompareOptions options){}
		//public static int CompareOrdinal(string strA, string strB){}
		//public static int CompareOrdinal(string strA, int indexA, string strB, int indexB, int length){}
		public int CompareTo(Object value){}
		public int CompareTo(string strB){}
		//public static string Concat(IEnumerable<string> values){}
		//public static string Concat<T>(IEnumerable<T> values){}
		public static string Concat(Object arg0){}
		public static string Concat(/*params*/ Object[] args){}
		public static string Concat(/*params*/ string[] values){}
		//public static string Concat(Object arg0, Object arg1){}
		//public static string Concat(string str0, string str1){}
		//public static string Concat(Object arg0, Object arg1, Object arg2){}
		//public static string Concat(string str0, string str1, string str2){}
		//public static string Concat(Object arg0, Object arg1, Object arg2, Object arg3){}
		//public static string Concat(string str0, string str1, string str2, string str3){}
		public bool Contains(string value){}
		public static string Copy(string str){}
		public void CopyTo(int sourceIndex, char[] destination, int destinationIndex, int count){}
		public bool EndsWith(string value){}
		//public bool EndsWith(string value, StringComparison comparisonType){}
		//public bool EndsWith(string value, bool ignoreCase, CultureInfo culture){}
		public override bool Equals(Object obj){}
		public bool Equals(string value){}
		public static bool Equals(string a, string b){}
		public bool Equals(string value, StringComparison comparisonType){}
		//public static bool Equals(string a, string b, StringComparison comparisonType){}
		//public static string Format(string format, Object arg0){}
		//public static string Format(string format, params Object[] args){}
		//public static string Format(IFormatProvider provider, string format, params Object[] args){}
		//public static string Format(string format, Object arg0, Object arg1){}
		//public static string Format(string format, Object arg0, Object arg1, Object arg2){}
		public IEnumerator<char> GetEnumerator(){}
		public override int GetHashCode(){}
		//public TypeCode GetTypeCode(){}
		public int IndexOf(char value){}
		public int IndexOf(string value){}
		public int IndexOf(char value, int startIndex){}
		public int IndexOf(string value, int startIndex){}
		//public int IndexOf(string value, StringComparison comparisonType){}
		public int IndexOf(char value, int startIndex, int count){}
		public int IndexOf(string value, int startIndex, int count){}
		//public int IndexOf(string value, int startIndex, StringComparison comparisonType){}
		//public int IndexOf(string value, int startIndex, int count, StringComparison comparisonType){}
		public int IndexOfAny(char[] anyOf){}
		public int IndexOfAny(char[] anyOf, int startIndex){}
		public int IndexOfAny(char[] anyOf, int startIndex, int count){}
		public string Insert(int startIndex, string value){}
		//public static string Intern(string str){}
		//public static string IsInterned(string str){}
		//public bool IsNormalized(){}
		//public bool IsNormalized(NormalizationForm normalizationForm){}
		public static bool IsNullOrEmpty(string value){}
		//public static bool IsNullOrWhiteSpace(string value){}
		//public static string Join(string separator, IEnumerable<string> values){}
		//public static string Join<T>(string separator, IEnumerable<T> values){}
		//public static string Join(string separator, params Object[] values){}
		public static string Join(string separator, /*params*/ string[] value){}
		public static string Join(string separator, string[] value, int startIndex, int count){}
		public int LastIndexOf(char value){}
		public int LastIndexOf(string value){}
		public int LastIndexOf(char value, int startIndex){}
		public int LastIndexOf(string value, int startIndex){}
		//public int LastIndexOf(string value, StringComparison comparisonType){}
		public int LastIndexOf(char value, int startIndex, int count){}
		public int LastIndexOf(string value, int startIndex, int count){}
		//public int LastIndexOf(string value, int startIndex, StringComparison comparisonType){}
		//public int LastIndexOf(string value, int startIndex, int count, StringComparison comparisonType){}
		public int LastIndexOfAny(char[] anyOf){}
		public int LastIndexOfAny(char[] anyOf, int startIndex){}
		public int LastIndexOfAny(char[] anyOf, int startIndex, int count){}
		//public string Normalize(){}
		//public string Normalize(NormalizationForm normalizationForm){}
		public string PadLeft(int totalWidth){}
		public string PadLeft(int totalWidth, char paddingChar){}
		public string PadRight(int totalWidth){}
		public string PadRight(int totalWidth, char paddingChar){}
		public string Remove(int startIndex){}
		public string Remove(int startIndex, int count){}
		public string Replace(char oldChar, char newChar){}
		public string Replace(string oldValue, string newValue){}
		public string[] Split(/*params*/char[] separator){}
		public string[] Split(char[] separator, int count){}
		public string[] Split(char[] separator, StringSplitOptions options){}
		public string[] Split(string[] separator, StringSplitOptions options){}
	    public string[] Split(char[] separator, int count, StringSplitOptions options){}
		public string[] Split(string[] separator, int count, StringSplitOptions options){}
		public bool StartsWith(string value){}
		//public bool StartsWith(string value, StringComparison comparisonType){}
		//public bool StartsWith(string value, bool ignoreCase, CultureInfo culture){}
		public string Substring(int startIndex){}
		public string Substring(int startIndex, int length){}
		public char[] ToCharArray(){}
		public char[] ToCharArray(int startIndex, int length){}
		public string ToLower(){}
		//public string ToLower(CultureInfo culture){}
		//public string ToLowerInvariant(){}
		public override string ToString(){}
		//public string ToString(IFormatProvider provider){}
		public string ToUpper(){}
		//public string ToUpper(CultureInfo culture){}
		//public string ToUpperInvariant(){}
		public string Trim(){}
		public string Trim(/*params*/ char[] trimChars){}
		public string TrimEnd(/*params*/ char[] trimChars = null){}
		public string TrimStart(/*params*/ char[] trimChars = null){}
    }
	
	public enum StringComparison
	{
		CurrentCulture = 0,
		CurrentCultureIgnoreCase = 1,
		InvariantCulture = 2,
		InvariantCultureIgnoreCase = 3,
		Ordinal = 4,
		OrdinalIgnoreCase = 5,
	}

	public enum StringSplitOptions
	{
		None = 0,
		RemoveEmptyEntries = 1,
	}
	
	//Collections
	namespace Collections {
		public class IEnumerator
		{
			//public virtual bool MoveNext(){}
			//public virtual void Reset(){}
		}

		public class IEnumerable
		{
			//public virtual IEnumerator* GetEnumerator(){}
		}
		
		namespace Generic {
            public class IEnumerator</*out*/T>
            {
                public bool MoveNext(){}
                public T Current{ get{} }
                public void Dispose(){}
            }
			public class IEnumerable </*out*/T> {}
            public class IComparer </*in*/T> {}
			
			public class List<T> : Object
			{
				public List(){}
				//public List(IEnumerable<T> collection){}
				public List(int capacity){}
				public int Capacity { get{} set{} }
				public int Count { get{} }
				public T this[int index] { get{} set{} }
				public void Add(T item){}
				//public void AddRange(IEnumerable<T> collection){}
				//public ReadOnlyCollection<T> AsReadOnly(){}
				public int BinarySearch(T item){}
				//public int BinarySearch(T item, IComparer<T> comparer){}
				//public int BinarySearch(int index, int count, T item, IComparer<T> comparer){}
				public void Clear(){}
				public bool Contains(T item){}
				//public List<TOutput> ConvertAll<TOutput>(Converter<T, TOutput> converter){}
				public void CopyTo(T[] array){}
				public void CopyTo(T[] array, int arrayIndex){}
				public void CopyTo(int index, T[] array, int arrayIndex, int count){}
				//public bool Exists(Predicate<T> match){}
				//public T Find(Predicate<T> match){}
				//public List<T> FindAll(Predicate<T> match){}
				//public int FindIndex(Predicate<T> match){}
				//public int FindIndex(int startIndex, Predicate<T> match){}
				//public int FindIndex(int startIndex, int count, Predicate<T> match){}
				//public T FindLast(Predicate<T> match){}
				//public int FindLastIndex(Predicate<T> match){}
				//public int FindLastIndex(int startIndex, Predicate<T> match){}
				//public int FindLastIndex(int startIndex, int count, Predicate<T> match){}
				//public void ForEach(Action<T> action){}
				// It is better to return struct Enumerator.
				public IEnumerator<T> GetEnumerator(){}
				public List<T> GetRange(int index, int count){}
				public int IndexOf(T item){}
				public int IndexOf(T item, int index){}
				public int IndexOf(T item, int index, int count){}
				public void Insert(int index, T item){}
				//public void InsertRange(int index, IEnumerable<T> collection){}
				public int LastIndexOf(T item){}
				public int LastIndexOf(T item, int index){}
				public int LastIndexOf(T item, int index, int count){}
				public bool Remove(T item){}
				//public int RemoveAll(Predicate<T> match){}
				public void RemoveAt(int index){}
				public void RemoveRange(int index, int count){}
				public void Reverse(){}
				public void Reverse(int index, int count){}
		        public void Sort(){}
				//public void Sort(Comparison<T> comparison){}
				//public void Sort(IComparer<T> comparer){}
				//public void Sort(int index, int count, IComparer<T> comparer){}
				public T[] ToArray(){}
				public void TrimExcess(){}
				//public bool TrueForAll(Predicate<T> match){}
                //public struct Enumerator
                //{
                //    public T Current { get{} }
                //    public void Dispose(){}
                //    public bool MoveNext(){}
                //}
            }
            
            // Value types are not supported yet...
            public class KeyValuePair<TKey,TValue> : Object
            {
                public KeyValuePair(TKey key, TValue value) {}
                public TKey Key { get{} }
                public TValue Value { get{} }
            }
            
            public class Dictionary<TKey, TValue> : Object
            {
                public Dictionary() { }
                //public Dictionary(IDictionary<TKey, TValue> dictionary);
                //public Dictionary(IEqualityComparer<TKey> comparer);
                public Dictionary(int capacity) { }
                //public Dictionary(IDictionary<TKey, TValue> dictionary, IEqualityComparer<TKey> comparer);
                //public Dictionary(int capacity, IEqualityComparer<TKey> comparer);
                //protected Dictionary(SerializationInfo info, StreamingContext context);
                
                //public IEqualityComparer<TKey> Comparer { get; }
                public int Count { get { } }
                //public Dictionary<TKey, TValue>.KeyCollection Keys { get; }
                //public Dictionary<TKey, TValue>.ValueCollection Values { get; }

                public TValue this[TKey key] { get { } set { } }

                public void Add(TKey key, TValue value) { }
                public void Clear() { }
                public bool ContainsKey(TKey key) { }
                public bool ContainsValue(TValue value) { }
                // It is better to return struct Enumerator.
                public IEnumerator<KeyValuePair<TKey, TValue>> GetEnumerator();
                //public virtual void GetObjectData(SerializationInfo info, StreamingContext context);
                //public virtual void OnDeserialization(object sender);
                public bool Remove(TKey key) { }
                public bool TryGetValue(TKey key, out TValue value) { }

                //public sealed class KeyCollection 
                //{
                //    public KeyCollection(Dictionary<TKey, TValue> dictionary);
                    
                //    public int Count { get; }
                    
                //    public void CopyTo(TKey[] array, int index);
                //    public Dictionary<TKey, TValue>.KeyCollection.Enumerator GetEnumerator()
                    
                //    public struct Enumerator
                //    {
                //        public TKey Current { get; }
                        
                //        public void Dispose();
                //        public bool MoveNext();
                //    }
                //}

                //public sealed class ValueCollection
                //{
                //    public ValueCollection(Dictionary<TKey, TValue> dictionary);
                    
                //    public int Count { get; }
                    
                //    public void CopyTo(TValue[] array, int index);
                //    public Dictionary<TKey, TValue>.ValueCollection.Enumerator GetEnumerator();
                    
                //    public struct Enumerator
                //    {
                //        public TValue Current { get; }
                        
                //        public void Dispose();
                //        public bool MoveNext();
                //    }
                //}

                //public struct Enumerator
                //{
                //    public KeyValuePair<TKey, TValue> Current { get; }
                    
                //    public void Dispose();
                //    public bool MoveNext();
                //}
            }
            
            public class KeyValuePair<TKey, TValue> : Object {
            	public TKey Key { get{} }
            	public TValue Value { get{} }
            	public KeyValuePair(TKey key, TValue value) {}
            }
			
			public class KeyNotFoundException : Exception { }
		}
	}

    public static class Console
    {
        //public static ConsoleColor BackgroundColor { get{} set{} }
        //public static int BufferHeight { get{} set{} }
        //public static int BufferWidth { get{} set{} }
        //public static bool CapsLock { get{} }
        //public static int CursorLeft { get{} set{} }
        //public static int CursorSize { get{} set{} }
        //public static int CursorTop { get{} set{} }
        //public static bool CursorVisible { get{} set{} }
        //public static TextWriter Error { get{} }
        //public static ConsoleColor ForegroundColor { get{} set{} }
        //public static TextReader In { get{} }
        //public static Encoding InputEncoding { get{} set{} }
        //public static bool KeyAvailable { get{} }
        //public static int LargestWindowHeight { get{} }
        //public static int LargestWindowWidth { get{} }
        //public static bool NumberLock { get{} }
        //public static TextWriter Out { get{} }
        //public static Encoding OutputEncoding { get{} set{} }
        //public static string Title { get{} set{} }
        //public static bool TreatControlCAsInput { get{} set{} }
        //public static int WindowHeight { get{} set{} }
        //public static int WindowLeft { get{} set{} }
        //public static int WindowTop { get{} set{} }
        //public static int WindowWidth { get{} set{} }

        //public static event ConsoleCancelEventHandler CancelKeyPress{}

        //public static void Beep(){}
        //public static void Beep(int frequency, int duration){}
        //public static void Clear(){}
        //public static void MoveBufferArea(int sourceLeft, int sourceTop, int sourceWidth, int sourceHeight, int targetLeft, int targetTop){}
        //public static void MoveBufferArea(int sourceLeft, int sourceTop, int sourceWidth, int sourceHeight, int targetLeft, int targetTop, char sourceChar, ConsoleColor sourceForeColor, ConsoleColor sourceBackColor){}
        //public static Stream OpenStandardError(){}
        //public static Stream OpenStandardError(int bufferSize){}
        //public static Stream OpenStandardInput(){}
        //public static Stream OpenStandardInput(int bufferSize){}
        //public static Stream OpenStandardOutput(){}
        //public static Stream OpenStandardOutput(int bufferSize){}
        //public static int Read(){}
        //public static ConsoleKeyInfo ReadKey(){}
        //public static ConsoleKeyInfo ReadKey(bool intercept){}
        //public static string ReadLine(){}
        //public static void ResetColor(){}
        //public static void SetBufferSize(int width, int height){}
        //public static void SetCursorPosition(int left, int top){}
        //public static void SetError(TextWriter newError){}
        //public static void SetIn(TextReader newIn){}
        //public static void SetOut(TextWriter newOut){}
        //public static void SetWindowPosition(int left, int top){}
        //public static void SetWindowSize(int width, int height){}
        public static void Write(bool value) { }
        public static void Write(char value) { }
        public static void Write(char[] buffer) { }
        //public static void Write(decimal value) { }
        public static void Write(double value) { }
        public static void Write(float value) { }
        public static void Write(int value) { }
        public static void Write(long value) { }
        public static void Write(object value) { }
        public static void Write(string value) { }
        public static void Write(uint value) { }
        public static void Write(ulong value) { }
        //public static void Write(string format, object arg0) { }
        //public static void Write(string format, /*params*/ object[] arg) { }
        //public static void Write(char[] buffer, int index, int count) { }
        //public static void Write(string format, object arg0, object arg1) { }
        //public static void Write(string format, object arg0, object arg1, object arg2) { }
        //public static void Write(string format, object arg0, object arg1, object arg2, object arg3) { }
        public static void WriteLine() { }
        public static void WriteLine(bool value) { }
        public static void WriteLine(char value) { }
        public static void WriteLine(char[] buffer) { }
        //public static void WriteLine(decimal value) { }
        public static void WriteLine(double value) { }
        public static void WriteLine(float value) { }
        public static void WriteLine(int value) { }
        public static void WriteLine(long value) { }
        public static void WriteLine(object value) { }
        public static void WriteLine(string value) { }
        public static void WriteLine(uint value) { }
        public static void WriteLine(ulong value) { }
        //public static void WriteLine(string format, object arg0) { }
        //public static void WriteLine(string format, /*params*/ object[] arg) { }
        public static void WriteLine(char[] buffer, int index, int count) { }
        //public static void WriteLine(string format, object arg0, object arg1) { }
        //public static void WriteLine(string format, object arg0, object arg1, object arg2) { }
        //public static void WriteLine(string format, object arg0, object arg1, object arg2, object arg3) { }
    }

	public abstract class Attribute : _Attribute {}
	
	namespace Runtime {
		namespace InteropServices {
			public interface _Attribute {}
		
			public enum CharSet
			{
				None = 1,
				Ansi = 2,
				Unicode = 3,
				Auto = 4,
			}
		
			public enum LayoutKind
			{
				Sequential = 0,
				Explicit = 2,
				Auto = 3,
			}
		
			public static class Marshal {
				public static int ReadInt32(IntPtr ptr) {}
			}
			
			public sealed class StructLayoutAttribute : Attribute
			{
				public CharSet CharSet {}
				public int Pack {}
				public int Size {}
				
				public StructLayoutAttribute(LayoutKind layoutKind) {}
				public StructLayoutAttribute(short layoutKind) {}
				
				public LayoutKind Value { get {} }
			}
		}
	}
	
	public interface IDisposable {}
	public interface ICloneable {}
	
	public abstract class Delegate : Object
	{
		//protected Delegate(object target, string method) { }
        //protected Delegate(Type target, string method) { }
	    
        //public static bool operator !=(Delegate d1, Delegate d2) { } 
        //public static bool operator ==(Delegate d1, Delegate d2) { }
        
        //public MethodInfo Method { get { } }
        //public object Target { get { } }
        
        //public virtual object Clone() { }
        //public static Delegate Combine(params Delegate[] delegates) { }
        //public static Delegate Combine(Delegate a, Delegate b) { }
        //protected virtual Delegate CombineImpl(Delegate d) { }
        //public static Delegate CreateDelegate(Type type, MethodInfo method) { }
        //public static Delegate CreateDelegate(Type type, MethodInfo method, bool throwOnBindFailure) { }
        //public static Delegate CreateDelegate(Type type, object firstArgument, MethodInfo method) { }
        //public static Delegate CreateDelegate(Type type, object target, string method) { }
        //public static Delegate CreateDelegate(Type type, Type target, string method) { }
        //public static Delegate CreateDelegate(Type type, object firstArgument, MethodInfo method, bool throwOnBindFailure) { }
        //public static Delegate CreateDelegate(Type type, object target, string method, bool ignoreCase) { }
        //public static Delegate CreateDelegate(Type type, Type target, string method, bool ignoreCase) { }
        //public static Delegate CreateDelegate(Type type, object target, string method, bool ignoreCase, bool throwOnBindFailure) { }
        //public static Delegate CreateDelegate(Type type, Type target, string method, bool ignoreCase, bool throwOnBindFailure) { }
        //public object DynamicInvoke(params object[] args) { }
        //protected virtual object DynamicInvokeImpl(object[] args) { }
        //public override bool Equals(object obj) { }
        //public override int GetHashCode() { }
        //public virtual Delegate[] GetInvocationList() { }
        //protected virtual MethodInfo GetMethodImpl() { }
        //public virtual void GetObjectData(SerializationInfo info, StreamingContext context) { }
        //public static Delegate Remove(Delegate source, Delegate value) { }
        //public static Delegate RemoveAll(Delegate source, Delegate value) { }
        //protected virtual Delegate RemoveImpl(Delegate d) { }
	}
}
