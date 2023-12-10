// cTesting1.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <stdio.h>

void doSomething() {
    int x = 5, y = 2;
    x = 3;
    printf("X is: %d\n", x);

    x = x + y;
    printf("X + Y is: %d\n", x);

    y = x - y;
    printf("Y - X is: %d\n", y);

    x = x * 5;
    printf("X * 5 is: %d\n", x);

    y = x / 5;
    printf("X / Y is: %d\n", y);


    x += y;
    printf("\n-----\nX += Y is: %d\n", x);

    x *= y;
    printf("X *= Y is: %d\n", x);

    x /= 5;
    printf("X /= Y is: %d\n", x);

    x -= y;
    printf("X -= Y is: %d\n", x);

    x++;
    printf("X++ is: %d\n", x);

    y = x >> 5;
    printf("X >> 5 is: %d\n", y);


}

int main()        
{                 
    printf("Hello World\n\n");
    
    doSomething();
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
