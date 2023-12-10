// cTesting2.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <stdio.h>

int doubleIt(int number) {  return number * 2;  }


int halveIt(int number) {  return number / 2;  }


void printTriangles(int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            printf("%d ", j);
        }
        printf("\n");
    }

    for (int i = n-1; i >= 1; i--) {
        for (int j = 1; j <= i; j++) {
            printf("%d ", j);
        }
        printf("\n");
    }
}


int main()
{
    printf("Hello World!\n");
    int x = 78;
    if (x == 8) {
        x = doubleIt(x);
        printf("x*2 = %d", x);
    }
    else {
        printf("Can not double %d", x);
    }
    
    

    x = 8;
    x = halveIt(x);
    printf("\nx/2 = %d\n\n", x);


    for (int i = 0; i < 11; i++) {
        if (i % 2 == 0) {
            printf("%d\n",i);
        }
    }

    printf("\n\n");

    int n = 7;
    printTriangles(n);
    return 0;
}


