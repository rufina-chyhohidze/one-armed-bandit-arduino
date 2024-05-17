/*
#include <stdlib.h>
#include <usart.h>
#include <util/delay.h>
#include <string.h> //you need to include this in order to work with printf and strings 

//we define our own datatype:CAR  with three values: year,model,type.
typedef struct{
  int year; //take 2 bytes
  char model[10]; //takes 10 bytes //no more than 10 characters long
  char type[10];//10 bytes
} CAR; //declare the data type

#define NUMCARS 3

void printCar(CAR * car){
  printf("Car model: %s\n\tType: %s\n\t year: %d",car->model,car->type,car->year);

}

int main(){
  initUSART(); //essential

CAR * car; //POINTER TO A CAR 
car = malloc(sizeeof(CAR));
car.year = 2023;
strcpy(car->type, "Ford");

CAR * cars [NUMCARS];
for (int i =0; i<NUMCARS;i++){
  cars[i] = calloc(sizeof(CAR),1);
  cars[i]->year=200;
  strcpy(cars[i]->model,"FORD");
  strcpy(cars[i]->type,"MALBOR");
}

  CAR car ={ 1965,"Renault","R4"};
  printf("My old car frpm %d,model %s and type %s\n",car.year,car.model,car.type);
  CAR car2;
  car2=car;
  //make a changed copy 
  strcpy (car2.type,"Scenic");
   printf("My old car from %d\n,model %s,\n and type %s\n",car.year,car.model,car.type);
  printf("My old car from %d,model %s and type %s\n",car2.year,car2.model,car2.type);
  printf("The size of the car object is %d \n",sizeof(CAR)); //22 BYTES were used 

CAR listOfCars[NUMCARS]={
  {1900,"Ferrari","AQ22"},
  {2000,"Mustang","ALO1"},
  {1002,"BIBI","no-type"}};
  for (int i = 0; i < NUMCARS;i++){
    printf("Car %d,\n year:%d,\n model: %s\ntype:%s \n",i,listOfCars[i].year,listOfCars[i].model,listOfCars[i].type);
    printf("The size of the array of car is:%d\n",sizeof(listOfCars));
  }
  for (int i = 0; i< NUMCARS;i++)
  {
    printCar(&listOfCars[i]); //give the referense on the adress of
    //(*g).name reference to the actual value OR g->name 
  }
  return 0;
};
*/
#include <avr/io.h>
#include <stdlib.h>
#include <usart.h>
#include <util/delay.h>
#include <string.h>
 
//We define our own CARD with 3 fields: year, model and type
typedef struct
{
   int year;
   char model[10];
   char type[10];
} CAR;
 
#define NUMCARS 3
 
void printCar(CAR * car)
{
    printf("Car Model: %s\n\tType: %s\tYear: %d\n",
          car->model, car->type, car->year);
    car->year = 1900;
}
int main()
{
    initUSART();
    CAR * cars[NUMCARS] ; //INITIALISE THE ARRAY OF POINTERS(3 pointers)2 bytes each=6 bytes for array
    //now create 22 bytes and have this first entry point to this byte
    //copy some entries(ford focud..)
    //so each pointer points to car object 
    for (int i = 0; i < NUMCARS; i++)
    {
        cars[i] = calloc(sizeof(CAR),1);
        cars[i]->year = 2000;
        strcpy(cars[i]->model, "Ford"); //-> pointing to the field of car object
        strcpy(cars[i]->type, "Focus");
        printCar(cars[i]);
    }
    //to free the memory use free
    for (int i = 0; i < NUMCARS; i++)
    {
      free(cars[i]); //objects that not being used 
    }
 
    // printf("Size of a car: %d\nSize of the array: %d", sizeof(CAR), sizeof(cars));
    // printf("#cars in array: %d\n", sizeof(cars) / sizeof(CAR));
 
    return 0;
}






