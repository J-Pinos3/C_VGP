

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int x, y;
    short int life;
    char* name;
} Man;


void structs() {
    Man man, man2;
    man.x = 50;
    man.y = 50;
    man.life = 100;
    man.name = "Jhon";

    man2.y = 40;
    man2.x = -80;
    man2.life = 100;
    man2.name = "Dani";

    printf("man's2 name: %s\n", man2.name);
    printf("man's2 life: %d\n", man2.life);
    
}

void arrayOfStructs() {
    Man mans[10];

    for (int i = 0; i < 10; i++) {
        if (i<5) {
            mans[i].x = 0;
        }
        else {
            mans[i].x = 200;
        }

        mans[i].y = i * 3;
        mans[i].life = 100 + i;
        mans[i].name = "man";
        //mans[i].name = "man" + i;
    }

    for (int i = 0; i < 10; i++) {
        printf("Name: %s\n", mans[i].name);
        printf("life: %d\n", mans[i].life);
        printf("x: %d\n", mans[i].x);
        printf("y: %d\n\n", mans[i].y);

    }
}



int main()
{
    //structs();

    arrayOfStructs();

    return 0;
}

