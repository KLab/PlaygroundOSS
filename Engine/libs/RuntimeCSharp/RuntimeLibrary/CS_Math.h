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
#ifndef _CS_Math_h_
#define _CS_Math_h_

#include <cmath>
#include "CS_Object.h"

namespace System {

enum MidpointRounding {
	ToEven			= 0,
	AwayFromZero	= 1,
};

/*static*/ class Math {
public:
	static	const double	E;
	static	const double	PI;

	inline static double	Abs				(double value)										{ return fabs(value);	}
	inline static float		Abs				(float  value)										{ return fabs(value);	}
	inline static s32		Abs				(s32	value)										{ return abs(value);	}
	inline static s64		Abs				(s64	value)										{ return abs(value);	}
	inline static s8		Abs				(s8		value)										{ return abs(value);	}
	inline static s16		Abs				(s16	value)										{ return abs(value);	}
	inline static double	Acos			(double d)											{ return acos(d);		}
	inline static double	Asin			(double d)											{ return asin(d);		}
	inline static double	Atan			(double d)											{ return atan(d);		}
	inline static double	Atan2			(double y, double x)								{ return atan2(y, x);	}
	inline static s64		BigMul			(s32 a, s32 b)										{ s64 s = (s64)a; return s * (s64)b;	}
	inline static double	Ceiling			(double a)											{ return ceil(a);		}
	inline static double	Cos				(double d)											{ return cos(d);		}
	inline static double	Cosh			(double value)										{ return cosh(value);	}
	inline static s32		DivRem			(s32 a, s32 b, /*out*/ s32* result)					{ if(!b) { THROW(CS_NEW System::DivideByZeroException()); } *result = a%b; return a/b; }
	inline static s64		DivRem			(s64 a, s64 b, /*out*/ s64* result)					{ if(!b) { THROW(CS_NEW System::DivideByZeroException()); } *result = a%b; return a/b; }
	inline static double	Exp				(double d)											{ return exp(d);		}
	inline static double	Floor			(double d)											{ return floor(d);		}
	inline static double	IEEERemainder	(double x, double y)								{ return x - (y * Round(x / y)); }
	inline static double	Log				(double d)											{ return log(d);		}
	inline static double	Log				(double a, double newBase)							{ return log(a)/log(newBase);	}
	inline static double	Log10			(double d)											{ return log10(d);		}
	inline static u8		Max				(u8 val1, u8 val2)									{ return (((val1) > (val2)) ? (val1) : (val2));	}
	inline static double	Max				(double val1, double val2)							{ return (((val1) > (val2)) ? (val1) : (val2));	}
	inline static float		Max				(float val1,  float val2)							{ return (((val1) > (val2)) ? (val1) : (val2));	}
	inline static s32		Max				(s32 val1,	s32 val2)								{ return (((val1) > (val2)) ? (val1) : (val2));	}
	inline static s64		Max				(s64 val1,	s64 val2)								{ return (((val1) > (val2)) ? (val1) : (val2));	}
	inline static s8		Max				(s8 val1,	s8  val2)								{ return (((val1) > (val2)) ? (val1) : (val2));	}
	inline static s16		Max				(s16 val1,	s16 val2)								{ return (((val1) > (val2)) ? (val1) : (val2));	}
	inline static u32		Max				(u32 val1,	u32 val2)								{ return (((val1) > (val2)) ? (val1) : (val2));	}
	inline static u64		Max				(u64 val1,	u64 val2)								{ return (((val1) > (val2)) ? (val1) : (val2));	}
	inline static u16		Max				(u16 val1,	u16 val2)								{ return (((val1) > (val2)) ? (val1) : (val2));	}
	inline static u8		Min				(u8 val1,	u8  val2)								{ return (((val1) < (val2)) ? (val1) : (val2));	}
	inline static double	Min				(double val1, double val2)							{ return (((val1) < (val2)) ? (val1) : (val2));	}
	inline static float		Min				(float	val1, float  val2)							{ return (((val1) < (val2)) ? (val1) : (val2));	}
	inline static s32		Min				(s32 val1,	s32 val2)								{ return (((val1) < (val2)) ? (val1) : (val2));	}
	inline static s64		Min				(s64 val1,	s64 val2)								{ return (((val1) < (val2)) ? (val1) : (val2));	}
	inline static s8		Min				(s8 val1,	s8  val2)								{ return (((val1) < (val2)) ? (val1) : (val2));	}
	inline static s16		Min				(s16 val1,	s16 val2)								{ return (((val1) < (val2)) ? (val1) : (val2));	}
	inline static u32		Min				(u32 val1,	u32 val2)								{ return (((val1) < (val2)) ? (val1) : (val2));	}
	inline static u64		Min				(u64 val1,	u64 val2)								{ return (((val1) < (val2)) ? (val1) : (val2));	}
	inline static u16		Min				(u16 val1,	u16 val2)								{ return (((val1) < (val2)) ? (val1) : (val2));	}
	inline static double	Pow				(double x, double y)								{ return pow(x, y);								}
	inline static double	Round			(double a)											{ return Round(a, MidpointRounding::ToEven);	}
	inline static double	Round			(double value, s32 digits)							{ return Round(value, digits, MidpointRounding::ToEven); } 
	inline static double	Round			(double value, MidpointRounding mode)				{
		double fvalue = floor(value);
		double cvalue = ceil(value);
		if(value > 0) {
			if(value - fvalue == 0.5) { return (mode == ToEven) ? ((floor((fvalue/2.0)*2) == fvalue) ? fvalue : cvalue) : cvalue; }
			else { return floor(value + 0.5); }
		} else {
			if(value - fvalue == 0.5) { return (mode == ToEven) ? ((floor((cvalue/2.0)*2) == cvalue) ? cvalue : fvalue) : fvalue; }
			else { return ceil(value - 0.5); }
		}
	}
	inline static double	Round			(double value, s32 digits, MidpointRounding mode)	{
		if((u32)digits > 15) { THROW(CS_NEW System::ArgumentOutOfRangeException()); }
		double p = pow(10.0, digits); return Round(value * p, mode) / p;
	}
	inline static s32		Sign			(double value)										{ return ((value == 0) ? 0 : ((value > 0) ? 1 : -1));	}
	inline static s32		Sign			(float	value)										{ return ((value == 0) ? 0 : ((value > 0) ? 1 : -1));	}
	inline static s32		Sign			(s32 value)											{ return ((value == 0) ? 0 : ((value > 0) ? 1 : -1));	}
	inline static s32		Sign			(s64 value)											{ return ((value == 0) ? 0 : ((value > 0) ? 1 : -1));	}
	inline static s32		Sign			(s8 value)											{ return ((value == 0) ? 0 : ((value > 0) ? 1 : -1));	}
	inline static s32		Sign			(s16 value)											{ return ((value == 0) ? 0 : ((value > 0) ? 1 : -1));	}
	inline static double	Sin				(double a)											{ return sin(a);										}
	inline static double	Sinh			(double value)										{ return sinh(value);									}
	inline static double	Sqrt			(double d)											{ return sqrt(d);										}
	inline static double	Tan				(double a)											{ return tan(a);										}
	inline static double	Tanh			(double value)										{ return tanh(value);									}
	inline static double	Truncate		(double d)											{ return (d > 0.0) ? floor(d) : ceil(d);				}

};

/*static*/ const double	Math::E		= 2.71828;
/*static*/ const double	Math::PI	= 3.14159;

}

#endif
