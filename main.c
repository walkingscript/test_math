// Compile: gcc math/math_base.c math/vector.c math/matrix.c main.c -o main

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "math.h"

int main() {
    char out[300];

    /* Матрицы 2-ого порядка */
    
    // необходимые переменные
    mat2_t mat2;
    vec2_t v1, v2;

    // заполнение переменных
    Mat2Set4f( &mat2, 1.0f, 0.0f, 
                      0.0f, 1.0f );

    if( Mat2IsIdent(&mat2) ) {
        printf("%s", "2 - Ident\n");
    } else {
        printf("%s", "2 - NOT ident\n");
    }
    

    Vec2Set( &v1, 5.0f, 3.0f );

    // умножение матрицы mat2 на вектор v1
    // Mat2MulVec2( &v2, &mat2, &v1 ); 
    // Vec2MulMat2( &v2, &v1, &mat2 );

    // вывод переменных
    Vec2ToStr( out, &v1, 0 ); printf( "%s\n", out ); // вектор
    Mat2ToPrettyStr( out, &mat2, 0 ); printf( "X\n%s\n", out ); // матрица
    Vec2ToStr( out, &v2, 0 ); printf( "=\n%s\n", out ); // результат умножения
    
    /*
    Mat2Inv( &mat2 );

    Mat2ToPrettyStr( out, &mat2, 5 );
    printf( "Matrix\n%s\n\n", out );
    */

    /*------------------------------------------------------------------------*/

    /* Матрицы 3-го порядка */
    
    mat3_t mat3;
    Mat3Set9f( &mat3, 1.0f + FLOAT_EPSILON, 0.0f, 0.0f, 
                      0.0f, 1.0f - FLOAT_EPSILON, 0.0f,
                      0.0f, 0.0f, 1.0f - FLOAT_EPSILON );
    
    if( Mat3IsIdent(&mat3) ) {
        printf("%s", "3 - Ident\n");
    } else {
        printf("%s", "3 - NOT ident\n");
    }

    /*

    float det_mat3 = Mat3Det( &mat3 ); // детерминант
    printf("det = %.*f\n", 3, det_mat3);

    Mat3ToStr( out, &mat3, 3 ); // вывод
    printf( "%s\n", out );

    Mat3Inv( &mat3 ); // обратить матрицу

    Mat3ToPrettyStr( out, &mat3, 5 ); // вывод
    printf( "%s\n", out );
    */
    /*----------------------------------------------------------------------*/


    /* Матрицы 4-ого порядка */
    
    mat4_t mat4;
    /*
    Mat4Set16f( &mat4, 6.0f, 8.0f, 2.0f, 9.0f,
                       2.0f, 3.0f, 2.0f, 1.0f,
                       5.0f, 7.0f, 6.0f, 8.0f,
                       7.0f, 3.0f, 9.0f, 4.0f );
    */

    Mat4Set16f( &mat4, 1.0f + FLOAT_EPSILON, 0.0f, 0.0f, 0.0f,
                       0.0f, 1.0f + FLOAT_EPSILON, 0.0f, 0.0f,
                       0.0f, 0.0f, 1.0f - FLOAT_EPSILON, 0.0f,
                       0.0f, 0.0f, 0.0f, 1.0f + FLOAT_EPSILON);

    if( Mat4IsIdent(&mat4) ) {
        printf("%s", "4 - Ident\n");
    } else {
        printf("%s", "4 - NOT ident\n");
    }


    
    Mat4Set16f( &mat4, 6.0f, 8.0f, 2.0f, 9.0f,
                       2.0f, 3.0f, 2.0f, 1.0f,
                       5.0f, 7.0f, 6.0f, 8.0f,
                       7.0f, 3.0f, 9.0f, 4.0f );
   
     
    Mat4ToPrettyStr( out, &mat4, 0 );
    printf("%s\n", out);
    
    mat4_t test_mat;
    Mat4Copy(&test_mat, &mat4);

    Mat4Inv( &test_mat );

    Mat4ToPrettyStr( out, &test_mat, 5 );
    printf("%s\n", out);

    mat4_t test_mat_res;
    Mat4Mul( &test_mat_res, &mat4, &test_mat );

    Mat4ToPrettyStr( out, &test_mat_res, 5 );
    printf("%s\n", out);

    

    /*----------------------------------------------------------------------*/

    return 0;
}
