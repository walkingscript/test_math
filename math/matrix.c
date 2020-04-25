#include "matrix.h"

/*
Mat2Set

Установка значений матрицы m из значений векторов.
*/
void Mat2Set( mat2_t* m, const vec2_t* a, const vec2_t* b ) {
    m->a = *a;
    m->b = *b;
}

/*
Mat2Copy

Установка значений из матрицы src в матрицу m.
*/
void Mat2Copy( mat2_t* m, const mat2_t* a ) {
    m->m[0] = a->m[0];
    m->m[1] = a->m[1];
    m->m[2] = a->m[2];
    m->m[3] = a->m[3];
}

/*
Mat2Set4f

Установить значения матрицы m.
*/
void Mat2Set4f( mat2_t* m, float ax, float ay, float bx, float by ) {
    m->m[0] = ax;
    m->m[1] = ay;
    m->m[2] = bx;
    m->m[3] = by;
}

/*
Mat2Zero


*/
void Mat2Zero( mat2_t* m ) {
    Vec2Zero( &m->a );
    Vec2Zero( &m->b );
}

/*
Mat2Ident


*/
void Mat2Ident( mat2_t* m ) {
    // по главной диагонали ставим 1.0f
    m->a.x = 1.0f;
    m->b.y = 1.0f;

    // остальные значения устанавливаем в 0.0f
    m->a.y = 0.0f;
    m->b.x = 0.0f;
}

/*
Mat2Neg


*/
void Mat2Neg( mat2_t* m ) {
    m->m[0] = -m->m[0];
    m->m[1] = -m->m[1];
    m->m[2] = -m->m[2];
    m->m[3] = -m->m[3];
}

/*
Mat2Inv

Вычисление обратной матрицы
*/
mbool_t Mat2Inv( mat2_t* m ) {
    float det = Mat2Det( m );

    // если матрица является вырожденной
    if( det == 0.0f ) { 
        return mfalse;
    }

    float inv_det = 1 / det;

    // делим алгебраическое дополнение на детерминант
    mat2_t buf; 
    buf.m[0] = m->b.y * inv_det;
    buf.m[1] = (-m->b.x) * inv_det;
    buf.m[2] = (-m->a.y) * inv_det; 
    buf.m[3] = m->a.x * inv_det;

    Mat2Transp( &buf ); // транспонируем матрицу
    Mat2Copy( m, &buf ); // пишем результат в исходную матрицу

    return mtrue; // детерминант != 0, значит обратная матрица посчитана и не является вырожденной
}


/*
Mat2Scale

Умножить каждое значение матрицы на s.
*/
void Mat2Scale( mat2_t* m, float s ) {
    m->m[0] *= s;
    m->m[1] *= s;
    m->m[2] *= s;
    m->m[3] *= s;
}

/*
Mat2MulVec2

Умножение матрицы 2-ого порядка на вектор-столбец.
*/
void Mat2MulVec2( vec2_t* out, const mat2_t* m, const vec2_t* v ) {
    out->x = m->m[0] * v->m[0] + m->m[1] * v->m[1];
    out->y = m->m[2] * v->m[0] + m->m[3] * v->m[1];
}

/*
Vec2MulMat2

Умножение вектора-строки на матрицу 2-ого порядка.
*/
void Vec2MulMat2( vec2_t* out, const vec2_t* v, const mat2_t* m ) {
    out->x = v->m[0] * m->m[0] + v->m[1] * m->m[2];
    out->y = v->m[0] * m->m[1] + v->m[1] * m->m[3];
}

void Mat2Mul( mat2_t* out, const mat2_t* a, const mat2_t* b ) {
    out->m[0] = a->m[0] * b->m[0];
    out->m[1] = a->m[1] * b->m[1];
    out->m[2] = a->m[2] * b->m[2];
    out->m[3] = a->m[3] * b->m[3];
}

void Mat2Add( mat2_t* out, const mat2_t* a, const mat2_t* b ) {
    out->m[0] = a->m[0] + b->m[0];
    out->m[1] = a->m[1] + b->m[1];
    out->m[2] = a->m[2] + b->m[2];
    out->m[3] = a->m[3] + b->m[3];
}

void Mat2Sub( mat2_t* out, const mat2_t* a, const mat2_t* b ) {
    out->m[0] = a->m[0] - b->m[0];
    out->m[1] = a->m[1] - b->m[1];
    out->m[2] = a->m[2] - b->m[2];
    out->m[3] = a->m[3] - b->m[3];
}

/*
Mat2Cmp

Сравнение матриц.
*/
mbool_t Mat2Cmp( const mat2_t* a, const mat2_t* b ) {
    return Vec2Cmp(&a->a, &b->a) && Vec2Cmp(&a->b, &b->b);
}

mbool_t Mat2CmpEps( const mat2_t* a, const mat2_t* b, float eps ) {
    if( Vec2CmpEps( &a->a, &b->a, eps ) &&
        Vec2CmpEps( &a->b, &b->b, eps ) 
    ) {
        return mtrue;
    }
    return mfalse;
}

mbool_t Mat2IsDiag( const mat2_t* m ) {

}

/*
Mat2IsIdent

Вернуть mtrue если матрица m является единичной (используется eps). 
Иначе вернуть mfalse.
Матрица является единичной, если все элементы стоящие не на главной 
диагонали равны 0.
*/
mbool_t Mat2IsIdent( const mat2_t* m ) {
    if( ( ( ( m->a.x <= 1.0f + FLOAT_EPSILON ) && ( m->a.x >= 1.0f - FLOAT_EPSILON ) )
       && ( ( m->b.y <= 1.0f + FLOAT_EPSILON ) && ( m->b.y >= 1.0f - FLOAT_EPSILON ) ) )
      && ( ( m->m[1] == 0.0f ) && ( m->m[2] == 0.0f ) )
    ) {
        return mtrue;
    }
    return mfalse;
}

/*
Mat2Det

Вычисление детерминанта (определителя) матрицы 2-ого порядка.
*/
float Mat2Det( const mat2_t* m ) {
    return m->m[0] * m->m[3] - m->m[1] * m->m[2];
}

/*
Mat2Transp

Транспонирование матрицы второго порядка.
*/
void Mat2Transp( mat2_t* m ) {
    // просто меняем местами элементы побочной диагонали
    float buf = m->a.y;
    m->a.y = m->b.x;
    m->b.x = buf;
}

void Mat2ToStr( char* out, const mat2_t* m, int prec ) {
    sprintf( out, "%.*f %.*f %.*f %.*f", prec, m->m[0], prec, m->m[1], prec, m->m[2], prec, m->m[3] );
}

/*
Mat2ToPrettyStr

Формирование табличного представления матрицы m. 
Запись в строку out.
*/
void Mat2ToPrettyStr( char* out, const mat2_t* m, int prec ) {
    sprintf( out, "%.*f %.*f\n%.*f %.*f", prec, m->m[0], prec, m->m[1], prec, m->m[2], prec, m->m[3] );
}

void Mat2ToMat3( mat3_t* out, const mat2_t* m ) {
    Vec2ToVec3(&out->a, &m->a);
    Vec2ToVec3(&out->b, &m->b);
    Vec3Zero(&out->c);
}

void Mat2ToMat4( mat4_t* out, const mat2_t* m ) {
    Vec2ToVec4(&out->a, &m->a);
    Vec2ToVec4(&out->b, &m->b);
    Vec4Zero(&out->c);
    Vec4Zero(&out->d);
}

/*
Mat3Set

Установка значений матрицы из значений векторов.
*/
void Mat3Set( mat3_t* m, const vec3_t* a, const vec3_t* b, const vec3_t* c ) {
    m->a = *a;
    m->b = *b;
    m->c = *c;
}

/*
Mat3Set9f

Установка значений матрицы m из значений аргументов функции.
*/
void Mat3Set9f( mat3_t* m, 
                float ax, float ay, float az, 
                float bx, float by, float bz, 
                float cx, float cy, float cz ) {
    m->m[0] = ax;
    m->m[1] = ay;
    m->m[2] = az;
    m->m[3] = bx;
    m->m[4] = by;
    m->m[5] = bz;
    m->m[6] = cx;
    m->m[7] = cy;
    m->m[8] = cz;
}

/*
Mat3Set9fv

Установка значений матрицы m из массива src.
*/
void Mat3Set9fv( mat3_t* m, const float* src ) {
    m->m[0]  = src[0];
    m->m[1]  = src[1];
    m->m[2]  = src[2];
    m->m[3]  = src[3];
    m->m[4]  = src[4];
    m->m[5]  = src[5];
    m->m[6]  = src[6];
    m->m[7]  = src[7];
    m->m[8]  = src[8];
}

/*
Mat3Copy

Устанавливает значения матрицы a в матрицу m.
*/
void Mat3Copy( mat3_t* m, const mat3_t* a ) {
    m->m[0] = a->m[0];
    m->m[1] = a->m[1];
    m->m[2] = a->m[2];
    m->m[3] = a->m[3];
    m->m[4] = a->m[4];
    m->m[5] = a->m[5];
    m->m[6] = a->m[6];
    m->m[7] = a->m[7];
    m->m[8] = a->m[8];
}

/*
Mat3Zero

Установка нулевой матрицы.
*/
void Mat3Zero( mat3_t* m ) {
    Vec3Zero( &m->a );
    Vec3Zero( &m->b );
    Vec3Zero( &m->c );
}

/*
Mat3Ident

Установка единичной матрицы.
*/
void Mat3Ident( mat3_t* m ) {
    // устанавливаем 1.0f по главной диагонали
    m->a.x = 1.0f;
    m->b.y = 1.0f;
    m->c.z = 1.0f;
    // остальные значения устанавливаем в 0.0f
    m->a.y = 0.0f;
    m->a.z = 0.0f;
    m->b.x = 0.0f;
    m->b.z = 0.0f;
    m->c.x = 0.0f;
    m->c.y = 0.0f;
}

/*
Mat3Neg

Смена знака для каждого элемента матрицы.
*/
void Mat3Neg( mat3_t* m ) {
    m->m[0] = -m->m[0];
    m->m[1] = -m->m[1];
    m->m[2] = -m->m[2];
    m->m[3] = -m->m[3];
    m->m[4] = -m->m[4];
    m->m[5] = -m->m[5];
    m->m[6] = -m->m[6];
    m->m[7] = -m->m[7];
    m->m[8] = -m->m[8];
}

/*
Mat3Inv

Вычисление обратной матрицы.
*/
mbool_t Mat3Inv( mat3_t* m ) {
    // вычисление определителя матрицы ( детерминант )
    float det = Mat3Det( m );

    if( det == 0.0f ) {
        return mfalse;
    }

    float inv_det = 1 / det;

    // деление алгебраического дополнения на определитель
    mat3_t buf;
    buf.m[0] = ( m->b.y * m->c.z - m->b.z * m->c.y ) * inv_det;
    buf.m[1] = -( m->b.x * m->c.z - m->b.z * m->c.x ) * inv_det;
    buf.m[2] = ( m->b.x * m->c.y - m->b.y * m->c.x ) * inv_det;
    buf.m[3] = -( m->a.y * m->c.z - m->a.z * m->c.y ) * inv_det;
    buf.m[4] = ( m->a.x * m->c.z - m->a.z * m->c.x ) * inv_det;
    buf.m[5] = -( m->a.x * m->c.y - m->a.y * m->c.x ) * inv_det;
    buf.m[6] = ( m->a.y * m->b.z - m->a.z * m->b.y ) * inv_det;
    buf.m[7] = -( m->a.x * m->b.z - m->a.z * m->b.x ) * inv_det;
    buf.m[8] = ( m->a.x * m->b.y - m->a.y * m->b.x ) * inv_det;

    Mat3Transp( &buf ); // транспонирование матрицы
    Mat3Copy( m, &buf ); // запись результата в исходную матрицу

    return mtrue;
}

/*
Mat3Scale

Умножает каждый элемент матрицы m на s.
*/
void Mat3Scale( mat3_t* m, float s ) {
    m->m[0] *= s;
    m->m[1] *= s;
    m->m[2] *= s;
    m->m[3] *= s;
    m->m[4] *= s;
    m->m[5] *= s;
    m->m[6] *= s;
    m->m[7] *= s;
    m->m[8] *= s;
}

/*
Mat3MulVec3

Умножение матрицы 3-го порядка на вектор-столбец.
*/
void Mat3MulVec3( vec3_t* out, const mat3_t* m, const vec3_t* v ) {
    out->x = m->m[0] * v->m[0] + m->m[1] * v->m[1] + m->m[2] * v->m[2];
    out->y = m->m[3] * v->m[0] + m->m[4] * v->m[1] + m->m[5] * v->m[2];
    out->z = m->m[6] * v->m[0] + m->m[7] * v->m[1] + m->m[8] * v->m[2];
}

/*
Vec3MulMat3

Умножение вектора-строки на матрицу 3-го порядка.
*/
void Vec3MulMat3( vec3_t* out, const vec3_t* v, const mat3_t* m ) {
    out->x = v->m[0] * m->m[0] + v->m[1] * m->m[3] + v->m[2] * m->m[6];
    out->y = v->m[0] * m->m[1] + v->m[1] * m->m[4] + v->m[2] * m->m[7];
    out->z = v->m[0] * m->m[2] + v->m[1] * m->m[5] + v->m[2] * m->m[8];
}

/*
Mat3Mul

Умножение матриц.
*/
void Mat3Mul( mat3_t* out, const mat3_t* a, const mat3_t* b ) {
    out->m[0] = a->m[0] * b->m[0];
    out->m[1] = a->m[1] * b->m[1];
    out->m[2] = a->m[2] * b->m[2];
    out->m[3] = a->m[3] * b->m[3];
    out->m[4] = a->m[4] * b->m[4];
    out->m[5] = a->m[5] * b->m[5];
    out->m[6] = a->m[6] * b->m[6];
    out->m[7] = a->m[7] * b->m[7];
    out->m[8] = a->m[8] * b->m[8];
}

/*
Mat3Add

Сложение матриц.
*/
void Mat3Add( mat3_t* out, const mat3_t* a, const mat3_t* b ) {
    out->m[0] = a->m[0] + b->m[0];
    out->m[1] = a->m[1] + b->m[1];
    out->m[2] = a->m[2] + b->m[2];
    out->m[3] = a->m[3] + b->m[3];
    out->m[4] = a->m[4] + b->m[4];
    out->m[5] = a->m[5] + b->m[5];
    out->m[6] = a->m[6] + b->m[6];
    out->m[7] = a->m[7] + b->m[7];
    out->m[8] = a->m[8] + b->m[8];
}

/*
Mat3Sub

Вычитание матрицы a из матрицы b;
*/
void Mat3Sub( mat3_t* out, const mat3_t* a, const mat3_t* b ) {
    out->m[0] = b->m[0] - a->m[0];
    out->m[1] = b->m[1] - a->m[1];
    out->m[2] = b->m[2] - a->m[2];
    out->m[3] = b->m[3] - a->m[3];
    out->m[4] = b->m[4] - a->m[4];
    out->m[5] = b->m[5] - a->m[5];
    out->m[6] = b->m[6] - a->m[6];
    out->m[7] = b->m[7] - a->m[7];
    out->m[8] = b->m[8] - a->m[8];
}

/*
Mat3Cmp

Сравнение матриц a и b.
*/
mbool_t Mat3Cmp( const mat3_t* a, const mat3_t* b ) {
    return Vec3Cmp(&a->a, &b->a) && Vec3Cmp(&a->b, &b->b) && Vec3Cmp(&a->c, &b->c);
}

/*
Mat3CmpEps

Сравнить две матрицы a и b с использованием епсилона eps. 
Если значения обеих матриц лежат в пределах eps, 
то результат - mtrue, иначе - mfalse.
*/
mbool_t Mat3CmpEps( const mat3_t* a, const mat3_t* b, float eps ) {
    if( Vec3CmpEps( &a->a, &b->a, eps ) &&
        Vec3CmpEps( &a->b, &b->b, eps ) && 
        Vec3CmpEps( &a->c, &b->c, eps ) 
    ) {
        return mtrue;
    }
    return mfalse;
}

/*
Mat3IsDiag

Возвращает mtrue если матрица m является диагональной (используется eps).
Иначе возвращает mfalse.
*/
mbool_t Mat3IsDiag( const mat3_t* m ) {

}

/*
Mat3IsIdent

Вернуть mtrue если матрица m является единичной (используется eps). Иначе вернуть mfalse.
*/
mbool_t Mat3IsIdent( const mat3_t* m ) {
    if( ( ( ( m->a.x <= 1.0f + FLOAT_EPSILON ) && ( m->a.x >= 1.0f - FLOAT_EPSILON ) )
       && ( ( m->b.y <= 1.0f + FLOAT_EPSILON ) && ( m->b.y >= 1.0f - FLOAT_EPSILON ) )
       && ( ( m->c.z <= 1.0f + FLOAT_EPSILON ) && ( m->c.z >= 1.0f - FLOAT_EPSILON ) ) )
     && ( ( m->m[1] == 0.0f ) && ( m->m[2] == 0.0f )
       && ( m->m[3] == 0.0f ) && ( m->m[5] == 0.0f )
       && ( m->m[6] == 0.0f ) && ( m->m[7] == 0.0f ) )
    ) {
        return mtrue;
    }
    return mfalse;
}

/*
Mat3Det

Вычисление определителя матрицы (детерминанта).
*/
float Mat3Det( const mat3_t* m ) {
    return m->m[0] * m->m[4] * m->m[8] + m->m[1] * m->m[5] * m->m[6] + m->m[2] * m->m[3] * m->m[7]
           - m->m[2] * m->m[4] * m->m[6] - m->m[3] * m->m[1] * m->m[8] - m->m[0] * m->m[5] * m->m[7];
}

/*
Mat3Transp

Транспонирование матрицы 3-го порядка.
*/
void Mat3Transp( mat3_t* m ) {
    mat3_t buf;
    buf.m[0] = m->m[0];
    buf.m[1] = m->m[3];
    buf.m[2] = m->m[6];
    buf.m[3] = m->m[1];
    buf.m[4] = m->m[4];
    buf.m[5] = m->m[7];
    buf.m[6] = m->m[2];
    buf.m[7] = m->m[5];
    buf.m[8] = m->m[8];
    Mat3Copy( m, &buf );
}

/*
Mat3ToStr

Формирование строкового представления матрицы.
Вывод элементов матрицы осуществляется в одну строку.
*/
void Mat3ToStr( char* out, const mat3_t* m, int prec ) {
    sprintf( out, "%.*f %.*f %.*f %.*f %.*f %.*f %.*f %.*f %.*f", 
             prec, m->m[0], prec, m->m[1], prec, m->m[2],
             prec, m->m[3], prec, m->m[4], prec, m->m[5],
             prec, m->m[6], prec, m->m[7], prec, m->m[8] );
}

/*
Mat3ToPrettyStr

Запись матрицы в строку. 
Строка будет выводиться в виде кватратной матрицы.
*/
void Mat3ToPrettyStr( char* out, const mat3_t* m, int prec ) {
    sprintf( out, "%.*f %.*f %.*f\n%.*f %.*f %.*f\n%.*f %.*f %.*f", 
             prec, m->m[0], prec, m->m[1], prec, m->m[2],
             prec, m->m[3], prec, m->m[4], prec, m->m[5],
             prec, m->m[6], prec, m->m[7], prec, m->m[8] );
}

/*
Mat3ToMat2

Преобразование матрицы из типа mat3_t в mat2_t.
*/
void Mat3ToMat2( mat2_t* out, const mat3_t* m ) {
    Vec3ToVec2(&out->a, &m->a);
    Vec3ToVec2(&out->b, &m->b);
}

/*
Mat3ToMat2

Преобразование матрицы из типа mat3_t в mat4_t.
*/
void Mat3ToMat4( mat4_t* out, const mat3_t* m ) {
    Vec3ToVec4(&out->a, &m->a);
    Vec3ToVec4(&out->b, &m->b);
    Vec3ToVec4(&out->c, &m->c);
    Vec4Zero(&out->d);
}

/*
Mat4Set

Установка матрицы из значений векторов
*/
void Mat4Set( mat4_t* m, const vec4_t* a, const vec4_t* b, const vec4_t* c, const vec4_t* d ) {
    m->a = *a;
    m->b = *b;
    m->c = *c;
    m->d = *d;
}

/*
Mat4Set16f

Установка матрицы по значениям.
*/
void Mat4Set16f( mat4_t* m, float ax, float ay, float az, float aw, 
                            float bx, float by, float bz, float bw,
                            float cx, float cy, float cz, float cw,
                            float dx, float dy, float dz, float dw ) {
    m->m[0]  = ax;
    m->m[1]  = ay;
    m->m[2]  = az;
    m->m[3]  = aw;
    m->m[4]  = bx;
    m->m[5]  = by;
    m->m[6]  = bz;
    m->m[7]  = bw;
    m->m[8]  = cx;
    m->m[9]  = cy;
    m->m[10] = cz;
    m->m[11] = cw;
    m->m[12] = dx;
    m->m[13] = dy;
    m->m[14] = dz;
    m->m[15] = dw;
}

/*
Mat4Set16fv

Заполнение матрицы 4-ого порядка из массива src.
*/
void Mat4Set16fv( mat4_t* m, const float* src ) {
    m->m[0]  = src[0];
    m->m[1]  = src[1];
    m->m[2]  = src[2];
    m->m[3]  = src[3];
    m->m[4]  = src[4];
    m->m[5]  = src[5];
    m->m[6]  = src[6];
    m->m[7]  = src[7];
    m->m[8]  = src[8];
    m->m[9]  = src[9];
    m->m[10] = src[10];
    m->m[11] = src[11];
    m->m[12] = src[12];
    m->m[13] = src[13];
    m->m[14] = src[14];
    m->m[15] = src[15];
}

/*
Mat4Zero

Обнуление матрицы.
*/
void Mat4Zero( mat4_t* m ) {
    Vec4Zero( &m->a );
    Vec4Zero( &m->b );
    Vec4Zero( &m->c );
    Vec4Zero( &m->d );
}

/*
Mat4Ident

Установка единичной матрицы.
*/
void Mat4Ident( mat4_t* m ) {
    // 1.0f по главной диагонали
    m->m[0]  = 1.0f;
    m->m[5]  = 1.0f;
    m->m[10] = 1.0f;
    m->m[15] = 1.0f;
    // остальные элементы в 0.0f
    m->m[1]  = 0.0f;
    m->m[2]  = 0.0f;
    m->m[3]  = 0.0f;
    m->m[4]  = 0.0f;
    m->m[6]  = 0.0f;
    m->m[7]  = 0.0f;
    m->m[8]  = 0.0f;
    m->m[9]  = 0.0f;
    m->m[11] = 0.0f;
    m->m[12] = 0.0f;
    m->m[13] = 0.0f;
    m->m[14] = 0.0f;
}

/*
Mat4Neg

Сделать каждое значение отрицательным
*/
void Mat4Neg( mat4_t* m ) {
    m->m[0]  = -m->m[0];
    m->m[1]  = -m->m[1];
    m->m[2]  = -m->m[2];
    m->m[3]  = -m->m[3];
    m->m[4]  = -m->m[4];
    m->m[5]  = -m->m[5];
    m->m[6]  = -m->m[6];
    m->m[7]  = -m->m[7];
    m->m[8]  = -m->m[8];
    m->m[9]  = -m->m[9];
    m->m[10] = -m->m[10];
    m->m[11] = -m->m[11];
    m->m[12] = -m->m[12];
    m->m[13] = -m->m[13];
    m->m[14] = -m->m[14];
    m->m[15] = -m->m[15];
}

/*
Mat4Inv

Вычисление обратной матрицы 4-ого порядка.
*/
mbool_t Mat4Inv( mat4_t* m ) { 
    float det = Mat4Det( m ); // определитель матрицы

    if( det == 0.0f ) {
        return mfalse;
    }

    float inv_det = 1 / det;

    mat4_t buf; // матрица алгебраических дополнений
    buf.m[0] = ( m->m[5] * m->m[10] * m->m[15] + m->m[6] * m->m[11] * m->m[13] + m->m[7] * m->m[9] * m->m[14] 
               - m->m[7] * m->m[10] * m->m[13] - m->m[6] * m->m[9] * m->m[15] - m->m[5] * m->m[11] * m->m[14] ) * inv_det;
    buf.m[1] = -( m->m[4] * m->m[10] * m->m[15] + m->m[6] * m->m[11] * m->m[12] + m->m[7] * m->m[8] * m->m[14] 
                - m->m[7] * m->m[10] * m->m[12] - m->m[6] * m->m[8] * m->m[15] - m->m[4] * m->m[11] * m->m[14] ) * inv_det;
    buf.m[2] = ( m->m[4] * m->m[9] * m->m[15] + m->m[5] * m->m[11] * m->m[12] + m->m[7] * m->m[8] * m->m[13] 
               - m->m[7] * m->m[9] * m->m[12] - m->m[5] * m->m[8] * m->m[15] - m->m[4] * m->m[11] * m->m[13] ) * inv_det;
    buf.m[3] = -( m->m[4] * m->m[9] * m->m[14] + m->m[5] * m->m[10] * m->m[12] + m->m[6] * m->m[8] * m->m[13] 
                - m->m[6] * m->m[9] * m->m[12] - m->m[5] * m->m[8] * m->m[14] - m->m[4] * m->m[10] * m->m[13] ) * inv_det;
    buf.m[4] = -( m->m[1] * m->m[10] * m->m[15] + m->m[2] * m->m[11] * m->m[13] + m->m[3] * m->m[9] * m->m[14] 
                - m->m[3] * m->m[10] * m->m[13] - m->m[2] * m->m[9] * m->m[15] - m->m[1] * m->m[11] * m->m[14] ) * inv_det;
    buf.m[5] = ( m->m[0] * m->m[10] * m->m[15] + m->m[2] * m->m[11] * m->m[12] + m->m[3] * m->m[8] * m->m[14] 
               - m->m[3] * m->m[10] * m->m[12] - m->m[2] * m->m[8] * m->m[15] - m->m[0] * m->m[11] * m->m[14] ) * inv_det;
    buf.m[6] = -( m->m[0] * m->m[9] * m->m[15] + m->m[1] * m->m[11] * m->m[12] + m->m[3] * m->m[8] * m->m[13] 
                - m->m[3] * m->m[9] * m->m[12] - m->m[1] * m->m[8] * m->m[15] - m->m[0] * m->m[11] * m->m[13] ) * inv_det;
    buf.m[7] = ( m->m[0] * m->m[9] * m->m[14] + m->m[1] * m->m[10] * m->m[12] + m->m[2] * m->m[8] * m->m[13] 
               - m->m[2] * m->m[9] * m->m[12] - m->m[1] * m->m[8] * m->m[14] - m->m[0] * m->m[10] * m->m[13] ) * inv_det;
    buf.m[8] = ( m->m[1] * m->m[6] * m->m[15] + m->m[2] * m->m[7] * m->m[13] + m->m[3] * m->m[5] * m->m[14] 
               - m->m[3] * m->m[6] * m->m[13] - m->m[2] * m->m[5] * m->m[15] - m->m[1] * m->m[7] * m->m[14] ) * inv_det;
    buf.m[9] = -( m->m[0] * m->m[6] * m->m[15] + m->m[2] * m->m[7] * m->m[12] + m->m[3] * m->m[4] * m->m[14] 
                - m->m[3] * m->m[6] * m->m[12] - m->m[2] * m->m[4] * m->m[15] - m->m[0] * m->m[7] * m->m[14] ) * inv_det;
    buf.m[10] = ( m->m[0] * m->m[5] * m->m[15] + m->m[1] * m->m[7] * m->m[12] + m->m[3] * m->m[4] * m->m[13] 
                - m->m[3] * m->m[5] * m->m[12] - m->m[1] * m->m[4] * m->m[15] - m->m[0] * m->m[7] * m->m[13] ) * inv_det;
    buf.m[11] = -( m->m[0] * m->m[5] * m->m[14] + m->m[1] * m->m[6] * m->m[12] + m->m[2] * m->m[4] * m->m[13]
                 - m->m[2] * m->m[5] * m->m[12] - m->m[1] * m->m[4] * m->m[14] - m->m[0] * m->m[6] * m->m[13] ) * inv_det;   
    buf.m[12] = -( m->m[1] * m->m[6] * m->m[11] + m->m[2] * m->m[7] * m->m[9] + m->m[3] * m->m[5] * m->m[10]
                 - m->m[3] * m->m[6] * m->m[9] - m->m[2] * m->m[5] * m->m[11] - m->m[1] * m->m[7] * m->m[10] ) * inv_det;
    buf.m[13] = ( m->m[0] * m->m[6] * m->m[11] + m->m[2] * m->m[7] * m->m[8] + m->m[3] * m->m[4] * m->m[10] 
                - m->m[3] * m->m[6] * m->m[8] - m->m[2] * m->m[4] * m->m[11] - m->m[0] * m->m[7] * m->m[10] ) * inv_det;
    buf.m[14] = -( m->m[0] * m->m[5] * m->m[11] + m->m[1] * m->m[7] * m->m[8] + m->m[3] * m->m[4] * m->m[9] 
                 - m->m[3] * m->m[5] * m->m[8] - m->m[1] * m->m[4] * m->m[11] - m->m[0] * m->m[9] * m->m[7] ) * inv_det;
    buf.m[15] = ( m->m[0] * m->m[5] * m->m[10] + m->m[1] * m->m[6] * m->m[8] + m->m[2] * m->m[4] * m->m[9] 
                - m->m[2] * m->m[5] * m->m[8] - m->m[1] * m->m[4] * m->m[10] - m->m[0] * m->m[6] * m->m[9] ) * inv_det;

    Mat4Transp( &buf );
    Mat4Copy( m, &buf);
    return mtrue;
}


/*
Mat4Scale

Умножить каждый элемент матрицы на s.
*/
void Mat4Scale( mat4_t* m, float s ) {
    m->m[0]  *= s;
    m->m[1]  *= s;
    m->m[2]  *= s;
    m->m[3]  *= s;
    m->m[4]  *= s;
    m->m[5]  *= s;
    m->m[6]  *= s;
    m->m[7]  *= s;
    m->m[8]  *= s;
    m->m[9]  *= s;
    m->m[10] *= s;
    m->m[11] *= s;
    m->m[12] *= s;
    m->m[13] *= s;
    m->m[14] *= s;
    m->m[15] *= s;
}

/*
Mat4MulVec4

Умножить матрицу 4-ого порядка на вектор столбец 4-ого порядка.
*/
void Mat4MulVec4( vec4_t* out, const mat4_t* m, const vec4_t* v ) {
    out->x = m->m[0] * v->m[0] + m->m[1] * v->m[1] + m->m[2] * v->m[2] + m->m[3] * v->m[3];
    out->y = m->m[4] * v->m[0] + m->m[5] * v->m[1] + m->m[6] * v->m[2] + m->m[7] * v->m[3]; 
    out->z = m->m[8] * v->m[0] + m->m[9] * v->m[1] + m->m[10] * v->m[2] + m->m[11] * v->m[3]; 
    out->w = m->m[12] * v->m[0] + m->m[13] * v->m[1] + m->m[14] * v->m[2] + m->m[15] * v->m[3]; 
}

/*
Mat4MulVec3

Умножить матрицу 4-ого порядка на вектор-столбец 3-го порядка.
*/
void Mat4MulVec3( vec3_t* out, const mat4_t* m, const vec3_t* v ) {
    vec4_t buf;

    buf.x = m->a.x * v->x + m->a.y * v->y + m->a.z * v->z + m->a.w * 1.0f;
    buf.y = m->b.x * v->x + m->b.y * v->y + m->b.z * v->z + m->b.w * 1.0f;
    buf.z = m->c.x * v->x + m->c.y * v->y + m->c.z * v->z + m->c.w * 1.0f;
    buf.w = m->d.x * v->x + m->d.y * v->y + m->d.z * v->z + m->d.w * 1.0f;

    if ( buf.w == 0.0f ) {
        buf.w = 1.0f;
    }

    Vec4ToVec3( out, &buf );
}

/*
Vec4MulMat4

Умножить вектор-строку 4-ого порядка на матрицу 4-ого порядка.
*/
void Vec4MulMat4( vec4_t* out, const vec4_t* v, const mat4_t* m ) {
    out->x = v->m[0] * m->m[0] + v->m[1] * m->m[4] + v->m[0] * m->m[8] + v->m[0] * m->m[12];
    out->y = v->m[0] * m->m[1] + v->m[1] * m->m[5] + v->m[0] * m->m[9] + v->m[0] * m->m[13];
    out->z = v->m[0] * m->m[2] + v->m[1] * m->m[6] + v->m[0] * m->m[10] + v->m[0] * m->m[14];
    out->w = v->m[0] * m->m[3] + v->m[1] * m->m[7] + v->m[0] * m->m[11] + v->m[0] * m->m[15];
}


/*
Mat4Mul

Умножить матрицу a на матрицу b.
*/
void Mat4Mul( mat4_t* out, const mat4_t* a, const mat4_t* b ) {
    out->m[0]  = a->m[0] * b->m[0];
    out->m[1]  = a->m[1] * b->m[1];
    out->m[2]  = a->m[2] * b->m[2];
    out->m[3]  = a->m[3] * b->m[3];
    out->m[4]  = a->m[4] * b->m[4];
    out->m[5]  = a->m[5] * b->m[5];
    out->m[6]  = a->m[6] * b->m[6];
    out->m[7]  = a->m[7] * b->m[7];
    out->m[8]  = a->m[8] * b->m[8];
    out->m[9]  = a->m[9] * b->m[9];
    out->m[10] = a->m[10] * b->m[10];
    out->m[11] = a->m[11] * b->m[11];
    out->m[12] = a->m[12] * b->m[12];
    out->m[13] = a->m[13] * b->m[13];
    out->m[14] = a->m[14] * b->m[14];
    out->m[15] = a->m[15] * b->m[15];
}

/*
Mat3Add

Сложение матриц.
*/
void Mat4Add( mat4_t* out, const mat4_t* a, const mat4_t* b ) {
    out->m[0]  = a->m[0] + b->m[0];
    out->m[1]  = a->m[1] + b->m[1];
    out->m[2]  = a->m[2] + b->m[2];
    out->m[3]  = a->m[3] + b->m[3];
    out->m[4]  = a->m[4] + b->m[4];
    out->m[5]  = a->m[5] + b->m[5];
    out->m[6]  = a->m[6] + b->m[6];
    out->m[7]  = a->m[7] + b->m[7];
    out->m[8]  = a->m[8] + b->m[8];
    out->m[9]  = a->m[9] + b->m[9];
    out->m[10] = a->m[10] + b->m[10];
    out->m[11] = a->m[11] + b->m[11];
    out->m[12] = a->m[12] + b->m[12];
    out->m[13] = a->m[13] + b->m[13];
    out->m[14] = a->m[14] + b->m[14];
    out->m[15] = a->m[15] + b->m[15];
}

/*
Mat4Sub

Вычитание из матрицы b матрицы a.
*/
void Mat4Sub( mat4_t* out, const mat4_t* a, const mat4_t* b ) {
    out->m[0]  = b->m[0] - a->m[0];
    out->m[1]  = b->m[1] - a->m[1];
    out->m[2]  = b->m[2] - a->m[2];
    out->m[3]  = b->m[3] - a->m[3];
    out->m[4]  = b->m[4] - a->m[4];
    out->m[5]  = b->m[5] - a->m[5];
    out->m[6]  = b->m[6] - a->m[6];
    out->m[7]  = b->m[7] - a->m[7];
    out->m[8]  = b->m[8] - a->m[8];
    out->m[9]  = b->m[9] - a->m[9];
    out->m[10] = b->m[10] - a->m[10];
    out->m[11] = b->m[11] - a->m[11];
    out->m[12] = b->m[12] - a->m[12];
    out->m[13] = b->m[13] - a->m[13];
    out->m[14] = b->m[14] - a->m[14];
    out->m[15] = b->m[15] - a->m[15];
}

/*
Mat4Copy

Установка значений матрицы a в матрицу m.
*/
void Mat4Copy( mat4_t* m, const mat4_t* a ) {
    m->m[0]  = a->m[0];
    m->m[1]  = a->m[1];
    m->m[2]  = a->m[2];
    m->m[3]  = a->m[3];
    m->m[4]  = a->m[4];
    m->m[5]  = a->m[5];
    m->m[6]  = a->m[6];
    m->m[7]  = a->m[7];
    m->m[8]  = a->m[8];
    m->m[9]  = a->m[9];
    m->m[10] = a->m[10];
    m->m[11] = a->m[11];
    m->m[12] = a->m[12];
    m->m[13] = a->m[13];
    m->m[14] = a->m[14];
    m->m[15] = a->m[15];
}

/*
Mat4Cmp

Сравнение матриц a и b.
*/
mbool_t Mat4Cmp( const mat4_t* a, const mat4_t* b ) {
    return Vec4Cmp(&a->a, &b->a) && Vec4Cmp(&a->b, &b->b) && Vec4Cmp(&a->c, &b->c) && Vec4Cmp(&a->d, &b->d);
}

/*
Mat4CmpEps

Сравнение матриц a и b с использованием епсилона eps. 
Если значения обеих матриц лежат в пределах eps, 
то результат - mtrue, иначе - mfalse.
*/
mbool_t Mat4CmpEps( const mat4_t* a, const mat4_t* b, float eps ) {
    if( Vec4CmpEps( &a->a, &b->a, eps ) &&
        Vec4CmpEps( &a->b, &b->b, eps ) && 
        Vec4CmpEps( &a->c, &b->c, eps ) &&
        Vec4CmpEps( &a->d, &b->d, eps )
    ) {
        return mtrue;
    }
    return mfalse;
}

/*
Mat4IsDiag

Возвращает mtrue если матрица m является диагональной (используется eps). 
Иначе возвращает mfalse.
*/
mbool_t Mat4IsDiag( const mat4_t* m ) {

}

/*
Mat4IsIdent

Вернуть mtrue если матрица m является единичной (используется eps). 
Иначе вернуть mfalse.
*/
mbool_t Mat4IsIdent( const mat4_t* m ) {
    if( ( ( ( m->a.x <= 1.0f + FLOAT_EPSILON ) && ( m->a.x >= 1.0f - FLOAT_EPSILON ) )
       && ( ( m->b.y <= 1.0f + FLOAT_EPSILON ) && ( m->b.y >= 1.0f - FLOAT_EPSILON ) )
       && ( ( m->c.z <= 1.0f + FLOAT_EPSILON ) && ( m->c.z >= 1.0f - FLOAT_EPSILON ) )
       && ( ( m->d.w <= 1.0f + FLOAT_EPSILON ) && ( m->d.w >= 1.0f - FLOAT_EPSILON ) ) )
       && ( ( m->m[1] == 0.0f ) && ( m->m[2] == 0.0f ) && ( m->m[3] == 0.0f ) 
         && ( m->m[4] == 0.0f ) && ( m->m[6] == 0.0f ) && ( m->m[7] == 0.0f ) 
         && ( m->m[8] == 0.0f ) && ( m->m[9] == 0.0f ) && ( m->m[11] == 0.0f )
         && ( m->m[12] == 0.0f ) && ( m->m[13] == 0.0f ) && ( m->m[14] == 0.0f ) )
    ) {
        return mtrue;
    }
    return mfalse;
}

/*
Mat4Det

Вычисление определителя матрицы 4-ого порядка.
Определителем матрицы 4-ого порядка является сумма
произведений элементов любой строки или столбца и 
их алгебраических дополнений.
*/
float Mat4Det( const mat4_t* m ) {
    // можно вычислять алгебраические дополнения из любой строки или столбца
    // я начну с 3-ей строки, потому что я так хочу

    float a31, a32, a33, a34;

    a31 = m->m[1] * m->m[6] * m->m[15] + m->m[2] * m->m[7] * m->m[13] + m->m[3] * m->m[5] * m->m[14] 
        - m->m[3] * m->m[6] * m->m[13] - m->m[2] * m->m[5] * m->m[15] - m->m[1] * m->m[7] * m->m[14];
    a32 = -( m->m[0] * m->m[6] * m->m[15] + m->m[2] * m->m[7] * m->m[12] + m->m[3] * m->m[4] * m->m[14]
           - m->m[3] * m->m[6] * m->m[12] - m->m[2] * m->m[4] * m->m[15] - m->m[0] * m->m[7] * m->m[14] );
    a33 = m->m[0] * m->m[5] * m->m[15] + m->m[1] * m->m[7] * m->m[12] + m->m[3] * m->m[4] * m->m[13]
        - m->m[3] * m->m[5] * m->m[12] - m->m[1] * m->m[4] * m->m[15] - m->m[0] * m->m[7] * m->m[13];
    a34 = -( m->m[0] * m->m[5] * m->m[14] + m->m[1] * m->m[6] * m->m[12] + m->m[2] * m->m[4] * m->m[13]
           - m->m[2] * m->m[5] * m->m[12] - m->m[1] * m->m[4] * m->m[14] - m->m[0] * m->m[6] * m->m[13] );   

    return m->m[8] * a31 + m->m[9] * a32 + m->m[10] * a33 + m->m[11] * a34;
}


/*
Mat4Transp

Транспонирование матрицы 4-ого порядка.
*/
void Mat4Transp( mat4_t* m ) {
    mat4_t buf;
    buf.m[0] = m->m[0];
    buf.m[1] = m->m[4];
    buf.m[2] = m->m[8];
    buf.m[3] = m->m[12];
    buf.m[4] = m->m[1];
    buf.m[5] = m->m[5];
    buf.m[6] = m->m[9];
    buf.m[7] = m->m[13];
    buf.m[8] = m->m[2];
    buf.m[9] = m->m[6];
    buf.m[10] = m->m[10];
    buf.m[11] = m->m[14];
    buf.m[12] = m->m[3];
    buf.m[13] = m->m[7];
    buf.m[14] = m->m[11];
    buf.m[15] = m->m[15];
    Mat4Copy( m, &buf );
}

/*
Mat4ToStr

Формирование строкового представления матрицы m. 
Значения выводятся с точностью prec.
Память под указатель out необходимо выделять вручную.
*/
void Mat4ToStr( char* out, const mat4_t* m, int prec ) {
    sprintf( out, "%.*f %.*f %.*f %.*f %.*f %.*f %.*f %.*f %.*f %.*f %.*f %.*f %.*f %.*f %.*f %.*f",
             prec, m->m[0],  prec, m->m[1],  prec, m->m[2],  prec, m->m[3],
             prec, m->m[4],  prec, m->m[5],  prec, m->m[6],  prec, m->m[7],
             prec, m->m[8],  prec, m->m[9],  prec, m->m[10], prec, m->m[11],
             prec, m->m[12], prec, m->m[13], prec, m->m[14], prec, m->m[15] );
}

/*
Mat4ToPrettyStr

Формирование табличного представления матрицы m.
Значения выводятся с точностью prec.
Память под указатель out необходимо выделять вручную.
*/
void Mat4ToPrettyStr( char* out, const mat4_t* m, int prec ) {
    sprintf( out, "%.*f %.*f %.*f %.*f\n%.*f %.*f %.*f %.*f\n%.*f %.*f %.*f %.*f\n%.*f %.*f %.*f %.*f",
             prec, m->m[0],  prec, m->m[1],  prec, m->m[2],  prec, m->m[3],
             prec, m->m[4],  prec, m->m[5],  prec, m->m[6],  prec, m->m[7],
             prec, m->m[8],  prec, m->m[9],  prec, m->m[10], prec, m->m[11],
             prec, m->m[12], prec, m->m[13], prec, m->m[14], prec, m->m[15] );
}

void Mat4ToMat2( mat2_t* out, const mat4_t* m ) {
    Vec4ToVec2(&out->a, &m->a);
    Vec4ToVec2(&out->b, &m->b);
}

void Mat4ToMat3( mat3_t* out, const mat4_t* m ) {
    Vec4ToVec3(&out->a, &m->a);
    Vec4ToVec3(&out->b, &m->b);
    Vec4ToVec3(&out->c, &m->c);
}
