#include "vector.h"

/*
Vec2Set

Установить значение вектора v.
*/
void Vec2Set( vec2_t* v, float x, float y ) {
    v->x = x;
    v->y = y;
}

/*
Vec2Cpy

Скопировать вектор v в out.
*/
void Vec2Cpy( vec2_t* out, const vec2_t* v ) {
    out->x = v->x;
    out->y = v->y;
}

/*
Vec2Zero

Установить вектор в 0.
*/
void Vec2Zero( vec2_t* v ) {
    v->x = 0.0f;
    v->y = 0.0f;
}

/*
Vec2Neg

Сделать негативным каждое значение вектора v.
*/
void Vec2Neg( vec2_t* v ) {
    v->x = -v->x;
    v->y = -v->y;
}

/*
Vec2Inv

Сделать обратным каждое значение вектора v (обратное значение для n – это 1/n).
*/
void Vec2Inv( vec2_t* v ) {
    v->x = 1.0f / v->x;
    v->y = 1.0f / v->y;
}

/*
Vec2Scale

Отмасштабировать вектор v. 
Каждое значение вектора v перемножить на соответствующие значения вектора s
и записать результат в v. 
*/
void Vec2Scale( vec2_t* v, const vec2_t* s ) {
    v->x *= s->x;
    v->y *= s->y;
}

/*
Vec2Scale1f

Отмасштабировать вектор v. 
Каждое значение вектора v перемножить f и записать результат в v. 
*/
void Vec2Scale1f( vec2_t* v, float f ){
    v->x *= f;
    v->y *= f;
}


/*
Vec2Add

Сложить два вектора a и b, результат записать в out.
*/
void Vec2Add( vec2_t* out, const vec2_t* a, const vec2_t* b ) {
    out->x = a->x + b->x;
    out->y = a->y + b->y;
}

/*
Vec2Sub

Вычесть вектор b из вектора a, результат записать в out.
*/
void Vec2Sub( vec2_t* out, const vec2_t* a, const vec2_t* b ) {
    out->x = a->x - b->x;
    out->y = a->y - b->y;
}

/*
Vec2Cmp

Сравнить два вектора a и b. 
Если оба вектора равны, то возвращаемое значение будет mtrue, 
если не равны, то возвращаемое значение будет mfalse.
*/
mbool_t Vec2Cmp( const vec2_t* a, const vec2_t* b ) {
    if( ( a->x == b->x ) && ( a->y == b->y ) ) {
        return mtrue;
    }
    return mfalse;
}

/*
Vec2CmpEps

Сравнить два вектора a и b с использованием епсилона eps.
Если значения обеих векторов лежат в пределах eps, то возвращаемое
значение будет mtrue, иначе возвращаемое значение будет mfalse.
*/
mbool_t Vec2CmpEps( const vec2_t* a, const vec2_t* b, float eps ) {
    float x = ( a->x > b->x ? a->x : b->x ) - ( a->x < b->x ? a->x : b->x );
    float y = ( a->y > b->y ? a->y : b->y ) - ( a->y < b->y ? a->y : b->y );
    if( ( x > eps ) || ( y > eps ) ) {
        return mfalse;
    }
    return mtrue;
}

/*
Vec2Len

Вернуть расстояние от вектора a вектора b.
*/
float Vec2Len( const vec2_t* a, const vec2_t* b ) {
    return sqrt1f( sqr1f( a->x - b->x ) + sqr1f( a->y - b->y ) );
}

/*
Vec2SqrLen

Вернуть расстояние от вектора a вектора b в квадрате.
*/
float Vec2SqrLen( const vec2_t* a, const vec2_t* b ) {
    return sqr1f( Vec2Len( a, b ) );
}

/*
Vec2Norm

Нормализовать вектор v и вернуть размер вектора v.
Нормализованный вектор записывается в v.
*/
float Vec2Norm( vec2_t* v ) {
    float len = sqrt1f( sqr1f( v->x ) + sqr1f( v->y ) );
    if( len == 0 ) {
       v->x = 1;
       v->y = 0;
    }
    else {
       v->x /= len;
       v->y /= len;
    }
    return len;
}

/*
Vec2Dot

Вернуть скалярное произведение векторов a и b.
*/
float Vec2Dot( const vec2_t* a, const vec2_t* b ) {
    return a->x * b->x + a->y * b->y;
}

/*
Vec2Cos

Вернуть косинус угла между двумя векторами a и b.
*/
float Vec2Cos( const vec2_t* a, const vec2_t* b ) {
    return Vec2Dot( a, b ) / ( sqrt1f( sqr1f( a->x ) + sqr1f( a->y ) ) 
                             * sqrt1f( sqr1f( b->x ) + sqr1f( b->y ) ) );
}

/*
Vec2Angle

Вернуть угол в радианах между двумя векторами a и b.
*/
float Vec2Angle( const vec2_t* a, const vec2_t* b ) {
    float len_a = sqrt1f( sqr1f( a->x ) + sqr1f( a->y ) );
    float len_b = sqrt1f( sqr1f( b->x ) + sqr1f( b->y ) );
    float cos_ab = Vec2Dot( a, b ) / len_a * len_b;
    return acos1f( cos_ab );
}

/*
Vec2Clamp

«Зажать» значения вектора v между минимальными min и 
максимальными max значениями. Результат записать в v.
*/
void Vec2Clamp( vec2_t* v, const vec2_t* min, const vec2_t* max ) {
    if( v->x < min->x ) {
        v->x = min->x;
    }
    if( v->x > max->x ) {
        v->x = max->x;
    }
    if( v->y < min->y ) {
        v->y = min->y;
    }
    if( v->y > max->y ) {
        v->y = max->y;
    }
}

/*
Vec2Lerp

Выполнить линейную интерполяцию между двумя векторами a и b
с коэффициентом scale. Результат записать в out.
*/
void Vec2Lerp( vec2_t* out, const vec2_t* a, const vec2_t* b, float s ) {
    out->x = b->x * s + a->x * ( 1.0f - s );
    out->y = b->y * s + a->y * ( 1.0f - s );
}

/*
Vec2ToStr

Записать в строку out значения вектора v
с количеством знаков после запятой prec.
*/
void Vec2ToStr( char* out, const vec2_t* v, int prec ) {
    sprintf( out, "%.*f %.*f", prec, v[0], prec, v[1] );
}

/*
Vec2ToVec3

Преобразование из двухмерного вектора в трёхмерный.
*/
void Vec2ToVec3( vec3_t* out, const vec2_t* v ) {
    out->x = v->x;
    out->y = v->y;
    out->z = 0.0f;
}

/*
Vec2ToVec4

Преобразование из двумерного вектора в четырёхмерный.
*/
void Vec2ToVec4( vec4_t* out, const vec2_t* v ) {
    out->x = v->x;
    out->y = v->y;
    out->z = 0.0f;
    out->w = 0.0f;
}

/*
Vec3Set

Установить значение вектора v.
*/
void Vec3Set( vec3_t* v, float x, float y, float z ) {
    v->x = x;
    v->y = y;
    v->z = z;
}

/*
Vec3Cpy

Скопировать вектор v в out.
*/
void Vec3Cpy( vec3_t* out, const vec3_t* v ) {
    out->x = v->x;
    out->y = v->y;
    out->z = v->z;
}

/*
Vec3Zero

Установить вектор в 0.
*/
void Vec3Zero( vec3_t* v ) {
    v->x = 0.0f;
    v->y = 0.0f;
    v->z = 0.0f;
}

/*
Vec3Neg

Сделать негативным каждое значение вектора v.
*/
void Vec3Neg( vec3_t* v ) {
    v->x = -v->x;
    v->y = -v->y;
    v->z = -v->z;
}

/*
Vec3Inv

Сделать обратным каждое значение вектора v (обратное значение для n – это 1/n).
*/
void Vec3Inv( vec3_t* v ) {
    v->x = 1.0f / v->x;
    v->y = 1.0f / v->y;
    v->z = 1.0f / v->z;
}

/*
Vec3Scale

Отмасштабировать вектор v. 
Каждое значение вектора v перемножить на соответствующие значения вектора s
и записать результат в v. 
*/
void Vec3Scale( vec3_t* v, const vec3_t* s ) {
    v->x *= s->x;
    v->y *= s->y;
    v->z *= s->z;
}

/*
Vec3Scale1f

Отмасштабировать вектор v. 
Каждое значение вектора v перемножить f и записать результат в v. 
*/
void Vec3Scale1f( vec3_t* v, float f ){
    v->x *= f;
    v->y *= f;
    v->z *= f;
}

/*
Vec3Add

Сложить два вектора a и b, результат записать в out.
*/
void Vec3Add( vec3_t* out, const vec3_t* a, const vec3_t* b ) {
    out->x = a->x + b->x;
    out->y = a->y + b->y;
    out->z = a->z + b->z;
}

/*
Vec3Sub

Вычесть вектор b из вектора a, результат записать в out.
*/
void Vec3Sub( vec3_t* out, const vec3_t* a, const vec3_t* b ) {
    out->x = a->x - b->x;
    out->y = a->y - b->y;
    out->z = a->z - b->z;
}

/*
Vec3Cross

Выполнить векторное произведение векторов a и b, результат записать в out.
*/
void Vec3Cross( vec3_t* out, const vec3_t* a, const vec3_t* b ) {
    out->x = a->y * b->z - a->z * b->y;
    out->y = a->z * b->x - a->x * b->z;
    out->z = a->x * b->y - a->y * b->x;
}

/*
Vec3Cmp

Сравнить два вектора a и b. 
Если оба вектора равны, то возвращаемое значение будет mtrue, 
если не равны, то возвращаемое значение будет mfalse.
*/
mbool_t Vec3Cmp( const vec3_t* a, const vec3_t* b ) {
    if( ( a->x == b->x ) && ( a->y == b->y ) && ( a->z == b->z ) ) {
        return mtrue;
    }
    return mfalse;
}

/*
Vec3CmpEps

Сравнить два вектора a и b с использованием епсилона eps.
Если значения обеих векторов лежат в пределах eps, то возвращаемое
значение будет mtrue, иначе возвращаемое значение будет mfalse.
*/
mbool_t Vec3CmpEps( const vec3_t* a, const vec3_t* b, float eps ) {
    float x = ( a->x > b->x ? a->x : b->x ) - ( a->x < b->x ? a->x : b->x );
    float y = ( a->y > b->y ? a->y : b->y ) - ( a->y < b->y ? a->y : b->y );
    float z = ( a->z > b->z ? a->z : b->z ) - ( a->z < b->z ? a->z : b->z );
    if( ( x > eps ) || ( y > eps ) || ( z > eps ) ) {
        return mfalse;
    }
    return mtrue;
}

/*
Vec3Len

Вернуть расстояние от вектора a вектора b.
*/
float Vec3Len( const vec3_t* a, const vec3_t* b ) {
    return sqrt1f( sqr1f( a->x - b->x) + sqr1f( a->y - b->y ) + sqr1f( a->z - b->z ) );
}

/*
Vec3SqrLen

Вернуть расстояние от вектора a вектора b в квадрате.
*/
float Vec3SqrLen( const vec3_t* a, const vec3_t* b ) {
    return sqrt1f( Vec3Len( a, b ) );
}

/*
Vec3Norm

Нормализовать вектор v и вернуть размер вектора v.
Нормализованный вектор записывается в v.
*/
float Vec3Norm( vec3_t* v ) {
    float len = sqrt1f( sqr1f( v->x ) + sqr1f( v->y ) + sqrt1f( v->z ) );
    if( len == 0.0f ) {
       v->x = 1.0f;
       v->y = 0.0f;
       v->z = 0.0f;
    }
    else {
       v->x /= len;
       v->y /= len;
       v->z /= len;
    }
    return len;
}

/*
Vec3Dot

Вернуть скалярное произведение векторов a и b.
*/
float Vec3Dot( const vec3_t* a, const vec3_t* b ) {
    return a->x * b->x + a->y * b->y + a->z * b->z;
}

/*
Vec3Cos

Вернуть косинус угла между двумя векторами a и b.
*/
float Vec3Cos( const vec3_t* a, const vec3_t* b ) {
    return Vec3Dot( a, b ) / ( sqrt1f( sqr1f( a->x ) + sqr1f( a->y ) + sqr1f( a->z ) )
                            *  sqrt1f( sqr1f( b->x ) + sqr1f( b->y ) + sqr1f( b->z ) ) );
}

/*
Vec3Angle

Вернуть угол в радианах между двумя векторами a и b.
*/
float Vec3Angle( const vec3_t* a, const vec3_t* b ) {
    float len_a = sqrt1f( sqr1f( a->x ) + sqr1f( a->y ) + sqr1f( a->z ) );
    float len_b = sqrt1f( sqr1f( b->x ) + sqr1f( b->y ) + sqr1f( b->z ) );
    float cos_ab = Vec3Dot( a, b ) / len_a * len_b;
    return acos1f( cos_ab );
}

/*
Vec3Clamp

«Зажать» значения вектора v между минимальными min и 
максимальными max значениями. Результат записать в v.
*/
void Vec3Clamp( vec3_t* v, const vec3_t* min, const vec3_t* max ) {
    if( v->x < min->x ) {
        v->x = min->x;
    }
    if( v->x > max->x ) {
        v->x = max->x;
    }
    if( v->y < min->y ) {
        v->y = min->y;
    }
    if( v->y > max->y ) {
        v->y = max->y;
    }
    if( v->z < min->z ) {
        v->z = min->z;
    }
    if( v->z > max->z ) {
        v->z = max->z;
    }
}

/*
Vec3Lerp

Выполнить линейную интерполяцию между двумя векторами a и b
с коэффициентом scale. Результат записать в out.
*/
void Vec3Lerp( vec3_t* out, const vec3_t* a, const vec3_t* b, float s ) {
    out->x = b->x * s + a->x * ( 1.0f - s );
    out->y = b->y * s + a->y * ( 1.0f - s );
    out->z = b->z * s + a->z * ( 1.0f - s );
}

/*
Vec3ToStr

Записать в строку out значения вектора v
с количеством знаков после запятой prec.
*/
void Vec3ToStr( char* out, const vec3_t* v, int prec ) {
    sprintf( out, "%.*f %.*f %.*f", prec, v[0], prec, v[1], prec, v[2] );
}

/*
Vec3ToVec2

Преобразование из трёхмерного вектора в двумерный вектор.
*/
void Vec3ToVec2( vec2_t* out, const vec3_t* v ) {
    out->x = v->x;
    out->y = v->y;
}

/*
Vec3ToVec4

Преобразование из трёхмерного вектора в четырёхмерный.
*/
void Vec3ToVec4( vec4_t* out, const vec3_t* v ) {
    out->x = v->x;
    out->y = v->y;
    out->z = v->z;
    out->w = 0.0f;
}

/*
Vec4Set

Установить значение вектора v.
*/
void Vec4Set( vec4_t* v, float x, float y, float z, float w ) {
    v->x = x;
    v->y = y;
    v->z = z;
    v->w = w;
}

/*
Vec4Cpy

Скопировать вектор v в out.
*/
void Vec4Cpy( vec4_t* out, const vec4_t* v ) {
    out->x = v->x;
    out->y = v->y;
    out->z = v->z;
    out->w = v->w;
}

/*
Vec4Zero

Установить вектор в 0.
*/
void Vec4Zero( vec4_t* v ) {
    v->x = 0.0f;
    v->y = 0.0f;
    v->z = 0.0f;
    v->w = 0.0f;
}

/*
Vec4Neg

Сделать негативным каждое значение вектора v.
*/
void Vec4Neg( vec4_t* v ) {
    v->x = -v->x;
    v->y = -v->y;
    v->z = -v->z;
    v->w = -v->w;
}

/*
Vec4Inv

Сделать обратным каждое значение вектора v (обратное значение для n – это 1/n).
*/
void Vec4Inv( vec4_t* v ) {
    v->x = 1.0f / v->x;
    v->y = 1.0f / v->y;
    v->z = 1.0f / v->z;
    v->w = 1.0f / v->w;
}

/*
Vec4Scale

Отмасштабировать вектор v. 
Каждое значение вектора v перемножить на соответствующие значения вектора s
и записать результат в v. 
*/
void Vec4Scale( vec4_t* v, const vec4_t* s ) {
    v->x *= s->x;
    v->y *= s->y;
    v->z *= s->z;
    v->w *= s->w;
}

/*
Vec4Scale1f

Отмасштабировать вектор v. 
Каждое значение вектора v перемножить f и записать результат в v. 
*/
void Vec4Scale1f( vec4_t* v, float f ) {
    v->x *= f;
    v->y *= f;
    v->z *= f;
    v->w *= f;
}

/*
Vec4Add

Сложить два вектора a и b, результат записать в out.
*/
void Vec4Add( vec4_t* out, const vec4_t* a, const vec4_t* b ) {
    out->x = a->x + b->x;
    out->y = a->y + b->y;
    out->z = a->z + b->z;
    out->w = a->w + b->w;
}

/*
Vec4Sub

Вычесть вектор b из вектора a, результат записать в out.
*/
void Vec4Sub( vec4_t* out, const vec4_t* a, const vec4_t* b ) {
    out->x = a->x - b->x;
    out->y = a->y - b->y;
    out->z = a->z - b->z;
    out->w = a->w - b->w;
}

/*
Vec4Cmp

Сравнить два вектора a и b. 
Если оба вектора равны, то возвращаемое значение будет mtrue, 
если не равны, то возвращаемое значение будет mfalse.
*/
mbool_t Vec4Cmp( const vec4_t* a, const vec4_t* b ) {
    if( ( a->x == b->x ) && ( a->y == b->y ) &&
        ( a->z == b->z ) && ( a->w == b->w ) ) {
        return mtrue;
    }
    return mfalse;
}

/*
Vec4CmpEps

Сравнить два вектора a и b с использованием епсилона eps.
Если значения обеих векторов лежат в пределах eps, то возвращаемое
значение будет mtrue, иначе возвращаемое значение будет mfalse.
*/
mbool_t Vec4CmpEps( const vec4_t* a, const vec4_t* b, float eps ) {
    float x = ( a->x > b->x ? a->x : b->x ) - ( a->x < b->x ? a->x : b->x );
    float y = ( a->y > b->y ? a->y : b->y ) - ( a->y < b->y ? a->y : b->y );
    float z = ( a->z > b->z ? a->z : b->z ) - ( a->z < b->z ? a->z : b->z );
    float w = ( a->w > b->w ? a->w : b->w ) - ( a->w < b->w ? a->w : b->w );
    if( ( x > eps ) || ( y > eps ) || ( z > eps ) || ( w > eps ) ) {
        return mfalse;
    }
    return mtrue;
}

/*
Vec4Len

Вернуть расстояние от вектора a вектора b.
*/
float Vec4Len( const vec4_t* a, const vec4_t* b ) {
    return sqrt1f( sqr1f( a->x - b->x ) + sqr1f( a->y - b->y ) +
                   sqr1f( a->z - b->z ) + sqr1f( a->w - b->w ) );
}

/*
Vec4SqrLen

Вернуть расстояние от вектора a вектора b в квадрате.
*/
float Vec4SqrLen( const vec4_t* a, const vec4_t* b ) {
    return sqr1f( Vec4Len( a, b ) );
}

/*
Vec4Norm

Нормализовать вектор v и вернуть размер вектора v.
Нормализованный вектор записывается в v.
*/
float Vec4Norm( vec4_t* v ) {
    float len = sqrt1f( sqr1f( v->x ) + sqr1f( v->y ) + sqr1f(v->z) + sqr1f(v->w) );
    if( len == 0.0f ) {
       v->x = 1.0f;
       v->y = 0.0f;
       v->z = 0.0f;
       v->w = 0.0f;
    }
    else {
       v->x /= len;
       v->y /= len;
       v->z /= len;
       v->w /= len;
    }
    return len;
}

/*
Vec4Dot

Вернуть скалярное произведение векторов a и b.
*/
float Vec4Dot( const vec4_t* a, const vec4_t* b ) {
    return a->x * b->x + a->y * b->y + a->z * b->z + a->w * b->w;
}

/*
Vec4Clamp

«Зажать» значения вектора v между минимальными min и 
максимальными max значениями. Результат записать в v.
*/
void Vec4Clamp( vec4_t* v, const vec4_t* min, const vec4_t* max ) {
    if( v->x < min->x ) {
        v->x = min->x;
    }
    if( v->x > max->x ) {
        v->x = max->x;
    }
    if( v->y < min->y ) {
        v->y = min->y;
    }
    if( v->y > max->y ) {
        v->y = max->y;
    }
    if( v->z < min->z ) {
        v->z = min->z;
    }
    if( v->z > max->z ) {
        v->z = max->z;
    }
    if( v->w < min->w ) {
        v->w = min->w;
    }
    if( v->w > max->w ) {
        v->w = max->w;
    }
}

/*
Vec4Lerp

Выполнить линейную интерполяцию между двумя векторами a и b
с коэффициентом scale. Результат записать в out.
*/
void Vec4Lerp( vec4_t* out, const vec4_t* a, const vec4_t* b, float s ) {
    out->x = b->x * s + a->x * ( 1.0f - s );
    out->y = b->y * s + a->y * ( 1.0f - s );
    out->z = b->z * s + a->z * ( 1.0f - s );
    out->w = b->w * s + a->w * ( 1.0f - s );
}

/*
Vec4ToStr

Записать в строку out значения вектора v
с количеством знаков после запятой prec.
*/
void Vec4ToStr( char* out, const vec4_t* v, int prec ) {
    sprintf( out, "%.*f %.*f %.*f %.*f",
             prec, v[0], prec, v[1], prec, v[2], prec, v[3] );
}

/*
Vec4ToVec2

Преобразование из четырёхмерного вектора в двумерный.
*/
void Vec4ToVec2( vec2_t* out, const vec4_t* v ) {
    out->x = v->x;
    out->y = v->y;
}

/*
Vec4ToVec3

Преобразование из четырёхмерного вектора в трёхмерный.
*/
void Vec4ToVec3( vec3_t* out, const vec4_t* v ) {
    out->x = v->x;
    out->y = v->y;
    out->z = v->z;
}
