#include <stdio.h>

void changeIntoUltraTreasure(int *treasure)
{
    *treasure = 1215752192;
}

int main()
{
    int treasure = 1000000;
    int *mapOfTreasure = &treasure;

    // dont need to copy value just to find it;

    printf("%d \n", treasure);       // 1000000
    printf("%p \n", &treasure);      // 000000DF0F9FF9B4
    printf("%p \n", mapOfTreasure);  // 000000DF0F9FF9B4
    printf("%d \n", *mapOfTreasure); // 1000000

    *mapOfTreasure = 5000000;

    // uses map to change the treasure

    printf("%d \n", treasure);

    // Using Arrays

    int treasures[] = {500000, 50000, 500};
    int *mapOfTreasures = &treasure;

    printf("%d \n", *mapOfTreasures);       // pointer at first box
    printf("%d \n", *(mapOfTreasures + 1)); // pointer moves to the next box
    printf("%d \n", *(mapOfTreasures + 2)); // pointer moves to the next box

    int ultraTreasure = 1215752192;
    int *mapOfUltraTreasure = &ultraTreasure;
    int **mapToMapOfUltraTreasure = &mapOfUltraTreasure;

    printf("%d \n", ultraTreasure);
    printf("%p \n", mapOfUltraTreasure);
    printf("%p \n", mapToMapOfUltraTreasure);
    printf("%d \n", *mapOfUltraTreasure);
    printf("%d \n", **mapToMapOfUltraTreasure);

    int notUltraTreasure = 500;
    printf("%d \n", notUltraTreasure);
    changeIntoUltraTreasure(&treasure);
    printf("%d \n", notUltraTreasure);
}
