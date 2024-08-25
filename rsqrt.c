#include <stdio.h>
#include <math.h>

float Q_rsqrt(float number);

int main(){

    float number = 4.0f;
    float result = Q_rsqrt(number);
    float result2 = 1.0f / sqrt(number);

    printf("The result is: %f\n", result);
    printf("The result2 is: %f\n", result2);

    return 0;
}

float Q_rsqrt(float number){
    long i;
    float x2, y;
    const float tresmedios = 1.5f;

    x2 = number * 0.5f;
    y = number;

    i = *(long *)&y;

    i = 0x5f3759df - (i >> 1);

    y = *(float *)&i;

    y = y * (tresmedios - (x2 * y * y)); // 1st iteration result = 0.499154
    y = y * (tresmedios - (x2 * y * y)); // 2nd iteration result = 0.499998
    y = y * (tresmedios - (x2 * y * y)); // 3rd iteration result = 0.500000

    return y;
}