// ctesting3.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <stdio.h>

void printArrayV1(int arr[], int sizeN) {
    for (int i = 0; i < sizeN; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}


void printArrayV2(int* arr, int sizeN) {
    for (int i = 0; i < sizeN; i++) {
        printf("%d ", *(arr + i) );
    }
    printf("\n");
}


void qs(int lista[], int limite_izq, int limite_der) {
    int izq = 0, der = 0, temporal = 0, pivote = 0;
    
    izq = limite_izq;
    der = limite_der;
    pivote = lista[(izq + der) / 2];

    do {
        while (lista[izq] < pivote && izq < limite_der) { izq++; }
        while (pivote < lista[der] && der > limite_izq){ der--; }

        if (izq <= der) {
            temporal = lista[izq];
            lista[izq] = lista[der];
            lista[der] = temporal;
            izq++;
            der--;
        }

    } while (izq <= der);

    if (limite_izq < der) {
        qs(lista, limite_izq, der);
    }

    if (limite_der > izq) {
        qs(lista, izq, limite_der);
    }
}


void QuickSort(int lista[], int n) {
    qs(lista, 0, n-1);
}


int main()
{
    int array[10] = {7,5,9,0,1,-5,4,11,2,6};
    int tamanio = sizeof(array) / sizeof(array[0]); 

    printf("Lista Desornendada");
    printArrayV2(array, tamanio);

    QuickSort(array, tamanio);

    printf("Lista Ornendada");
    printArrayV1(array, tamanio);

    /*
    for (int i = 0; i < sizeof(array) / sizeof(array[0]); i++) {
        printf("%d ", array[i]);
    }
    */


}

