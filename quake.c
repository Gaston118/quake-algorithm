
// Quake III es un juego de disparos en primera persona desarrollado por id Software 
// y publicado por Activision. Como muchos otros juegos, Quake III utiliza fisicas simuladas,
// y la raíz cuadrada inversa permite calcular la distancia entre dos puntos en el espacio 
// tridimensional y asi poder determinar si un jugador puede ver a otro. 

// Magnitud de un vector: ||V|| = sqrt(x²+ x² + z²)
// Vector normalizado = sqrt((x² + y² + z²)/||V||²) = 1
// Se tiene un vector V = (x, y, z), su vector normalizado es:
// (x/sqrt(x² + y² + z²), y/sqrt(x² + y² + z²), z/sqrt(x² + y² + z²))

// El estadar IEEE 754 define un formato de 32 bits para representar un número en punto flotante.
// El formato de 32 bits se divide en tres campos: el bit de signo, 
// el campo de exponente y el campo de mantisa.

// Mdecimal = M/2⁽²³⁾
// Mantisa = 1 + Mdecimal
// Exponente = E - 127

// Decimal original = (1 + M/2⁽²³⁾) * 2^(E-127) = EQ1
// Xbits = E*2²³ + M = EQ2

// log2(EQ1) = log2((1 + M/2⁽²³⁾) * 2^(E-127)) = log2(1 + M/2⁽²³⁾) + (E-127)
// log2(EQ1) = (M/2⁽²³⁾ + S) + (E-127)          Se realiza una aproximación logaritmica
// log2(EQ1) = E + (M/2⁽²³⁾) - 127 + S
// log2(EQ1) = 1/2²³ * (2²³*E + M) - 127 + S

// log2(EQ1) = 1/2²³ * Xbits - 127 + S = EQ3    reemplzando EQ2

// Ybits = 3/2 * (127 - S)*2²³ - Xbits*1/2
// Ybits = 1.5*(127-S)*2²³ - Xbits*0.5 

// Xbits: entrada  Ybits: salida

#include <stdio.h>
#include <math.h>

float RaizCuadradaInversa(float x);
float RaizCuadradaInversaQuake(float num);

int main(){
    return 0;
}

float RaizCuadradaInversa(float x){
    return 1.0f/sqrt(x);
}

float RaizCuadradaInversaQuake(float num){
    long i;
    float x2, y;
    const float tresmedios = 1.5f;

    x2 = num * 0.5f;
    y = num;

    i = *(long *)&y; // &y es la dirección de memoria de y 
                     // (long*) es un cast, entonces cambia el tipo de la dirección de memoria
                     // *(long*) extrae los datos de la dirección de memoria sin modificarlos

    i = 0x5f3759df - (i >> 1);  // (i >> 1) es un corrimiento de bits a la derecha
                                // 0x5f3759df es un número mágico
                                // Se realiza una resta de los bits de i con el número mágico
                                // 0x5f3759df (16) = 1597463007 (10)
                                // 1597463007 - Xbits*0.5 = Ybits
                                // Ybits = 1.5*(127-S)*2²³ - Xbits*0.5
                                // S = 0.0450466 valor de S que eligieron los creados 
                                // para hacer la aproximación logaritmica

    y = *(float *)&i; // Se convierte el número entero a un número flotante

    y = y * (tresmedios - (x2 * y * y)); // Metodo de Newton-Raphson

    return y;
}

