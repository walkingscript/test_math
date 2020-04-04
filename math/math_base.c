/* File math_base.c */
#include "math_base.h"

const float  PI = 3.14159265358979323846f;           // pi
const float  TWO_PI = 6.283185307179586f;            // pi * 2
const float  HALF_PI = 1.5707963267948966f;          // pi / 2
const float  INV_PI = 0.3183098861837907f;           // 1 / pi
const float  E = 2.71828182845904523536f;            // e
const float  SQRT_TWO = 1.41421356237309504880f;     // sqrt( 2 )
const float  SQRT_THREE = 1.73205080756887729352f;   // sqrt( 3 )
const float  SQRT_HALF = 0.70710678118654752440f;    // sqrt( 1 / 2 )
const float  FLOAT_INFINITY = 1e30f;                 // бесконечность
const float  FLOAT_EPSILON = 1.192092896e-07f;       // минимальное число, для которого
                                                     // выполняется условие 1.0f + FLOAT_EPSILON != 1.0f

void MathInit( ) {

}

void MathRelease( ) {

}

/*
isqrt1f

Возвращает обратный квадратный корень числа x.
Если x == 0.0f, то возвращаемое значение будет очень большим.
*/
float isqrt1f( float x ) {
    const float x2 = x * 0.5f;
    const float threehalfs = 1.5f;

    union {
        float f;
        unsigned long i;
    } conv = {x}; // member 'f' set to value of 'x'.

    conv.i = 0x5f3759df - ( conv.i >> 1 );
    conv.f *= ( threehalfs - ( x2 * conv.f * conv.f ) );
    return conv.f;
}


/*
sqrt1f

Возвращает квадрат числа x.
*/
float sqr1f( float x ) {
    return x * x;
}

/*
sqrt1f

Возвращает обратный квадратный корень числа x.
*/
float sqrt1f( float x ) {
    return sqrt( x );
}

/*
sin1f

Возвращает синус угла a.
Угол a задаётся в радианах.
Возвращаемое значение будет в пределах [-1, +1].
*/
float sin1f( float a ) {
    return sinf( a );
}

/*
cos1f 

Возвращает косинус угла a.
Угол a задаётся в радианах.
Возвращаемое значение будет в пределах [-1, +1].
*/
float cos1f( float a ) {
    return cosf( a );
}

/*
sincosf

Функция sincosf возвращает синус и косинус угла a.
Угол a задаётся в радианах.
Синус будет записан по указателю s, а косинус будет записан по указателю с.
s и c не должны быть NULL.
*/
void sincosf( float a, float* s, float* c ) {
    *s = sin1f( a );
    *c = cos1f( a );
}

/*
tan1f

Возвращает тангенс угла a. Угол a задаётся в радианах.
*/
float tan1f( float a ) {
    return tanf( a );
}

/*
asin1f

Функция asin1f возвращает арксинус синуса a.
a должно быть в пределах [-1, +1].
Возвращаемое значение будет в пределах [-PI/2, +PI/2].
*/
float asin1f( float a ) {
    return asinf( a );
}

/*
acos1f

Функция acos1f возвращает арккосинус косинуса a.
a должно быть в пределах [-1, +1].
Возвращаемое значение будет в пределах [0, PI].
*/
float acos1f( float a ) {
    return acosf( a );
}

/*
atan1f

Функция atan1f возвращает арктангенс тангенса a.
Возвращаемое значение будет в пределах [-PI/2, +PI/2].
*/
float atan1f( float a ) {
    return atanf( a );
}

/*
atan2f

Возвращает арктангенс тангенса по координатам x и y в плоскости.
Возвращаемое значение будет в пределах [-PI/2, +PI/2].
*/
float atan2f( float y, float x ) {
    return atan2( y, x );
}

/*
pow2f

Возвращает x возведённый в степень y.
*/
float pow2f( float x, float y ) {
    return pow( x, y );
}

/*
exp1f

Возвращает экспоненту числа f.
Экспонента это число E возведённое в степень f.
*/
float exp1f( float f ) {
    return pow2f( f, E );
}

/*
log1f

Возвращает натуральный логарифм от f.
*/
float log1f( float f ) {
    return log( f );
}

/*
pow2i

Возвращает x возведённую в степень y. 
*/
int pow2i( int x, int y ) {
    return pow( x, y );
}


/*
min2f

Возвращает минимальное число из двух чисел a и b.
*/
float min2f( float a, float b ) {
    if( a < b ) {
        return a;
    }
    return b;
}

/*
min2i

Возвращает минимальное число из двух чисел a и b.
*/
int min2i( int a, int b ) {
    if( a < b ) {
        return a;
    }
    return b;
}


/*
max2f

Возвращает максимальное число из двух чисел a и b.
*/
float max2f( float a, float b ) {
    if( a > b ) {
        return a;
    }
    return b;
}


/*
max2i

Возвращает максимальное число из двух чисел a и b.
*/
int max2i( int a, int b ) {
    if( a > b ) {
        return a;
    }
    return b;
}

/*
abs1i

Возвращает абсолютное значение числа x.
*/
int abs1i( int x ) {
    if( x < 0 ) {
        return -x;
    }
    return x;
}

/*
abs1f

Возвращает абсолютное значение числа x.
*/
float abs1f( float x ) {
    if( x < 0 ) {
        return -x;
    }
    return x;
}

/*
floor1f

Возвращает целое число, которое меньше или равно числу f. 
Округление к меньшему целому.
*/
float floor1f( float f ) {
    return floor( f );
}

/*
ceil1f

Возвращает целое число, которое больше или равно числу f.
Округление к большему целому.
*/
float ceil1f( float f ) {
    return ceil( f );
}

/*
round1f

Возвращает целое число, округленное по математическим законам.
*/
float round1f( float f ) {
    return round( f );
}

/*
trunc1f


*/
float trunc1f( float f ) {
    return trunc( f );
}

/*
frac1f

Отбрасывает дробную часть числа f и возвращает целое значение.
*/
float frac1f( float f ) {
    return f - floor1f( f );
}

/*
clamp3i

Возвращает число min если val меньше чем min.
Возвращает число max, если val больше чем max. 
Иначе функция возвращает val.
*/
int clamp3i( int min, int max, int val ) {
    if( val < min ) {
        return min;
    }
    else if( val > max ) {
        return max;
    }
    else {
        return val;
    }
}

/*
clamp3f

Возвращает число min если val меньше чем min.
Возвращает число max, если val больше чем max. 
Иначе функция возвращает val.
*/
float clamp3f( float min, float max, float val ) {
    if( val < min ) {
        return min;
    }
    else if( val > max ) {
        return max;
    }
    else {
        return val;
    }
}

/*
lerpi

Возвращает линейную между двумя числами a и b с коэффициентом scale.
*/
int lerpi( int a, int b, float scale ) {
    return scale * a + b;
}


/*
lerpf

Возвращает линейную между двумя числами a и b с коэффициентом scale.
*/
float lerpf( float a, float b, float scale ) {
    return scale * a + b;
}
