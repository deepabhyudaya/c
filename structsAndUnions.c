#include <stdio.h>
#include <string.h>

struct toyCar // multiple values co exist
{
    char name[20]; // own memory
    int wheels;    // own memory
    float price;   // own memory
}; // size = wheels + price + name;
// vs
union ToyCar // one value at a time
{
    char name[20]; // same memory
    int wheels;    // same memory
    float price;   // same memory
}; // size = name[20], as its the largest

int main()
{

    struct toyCar car;
    strcpy(car.name, "Ferrari");
    car.price = 29.99;
    car.wheels = 1;
    printf("%.2f %s", car.price, car.name);
    car.price = 30.99;
    printf("%.2f %s", car.price, car.name);

    // vs

    union ToyCar tcar;
    strcpy(tcar.name, "Ferrari");
    printf("%s", car.name);
    tcar.price = 29.99;
    printf("%.2f", tcar.price);
    printf("%s", tcar.name); // corrupted
}