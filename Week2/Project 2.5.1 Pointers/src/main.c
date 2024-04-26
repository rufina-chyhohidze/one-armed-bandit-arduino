#include <util/delay.h> 
#include <avr/io.h> 
#include <usart.h> 

void increment_byref( int* a) //here a is a pointer( pointer ++)
{ 
    printf( "Incrementing a (%d)\n", *a); 
    (*a)++; //use a pointer to the loc where a is , we refer to the memory loc itself ,points to the value in this memory(not the copy)
} 

void increment_byval( int a ) 
{ 
    printf( "Incrementing a (%d)\n", a ); 
    a++; //this func gets a copy of a value,increment ,11,
} 

void array_as_parameter( int* p ) 
{ 
    //how large is the array in bytes? 
    printf( "sizeof array as parameter: %d\n" , sizeof( p )); 
} 

int main() 
{ 
    initUSART(); 
    int a = 10; //DECLARE VAR A 
    int* b = &a; //DECLARING B AS A POINTER,its going to point to the address of the memory of a
    int c[] = { 1,2,3 }; //array length of 3
    int d[] = { 1,2,3,4,5,6 }; //6 elements 

    // print the value of a 
    printf( "Value of a: %d\n", a ); 

    // how many bytes does an int take up? 
    printf( "sizeof a: %d\n", sizeof( a ));//size of variable a, a is int= C its 2 bytes 
 
    // In what memory address is a stored (in hex)? 
    // (you could use %d if you wanted to see the address in decimal, but ignore the warning then...) 
    printf( "Value of &a: %p\n", &a ); //WE DONT REQUEST THE VALUE OF A ,BUT THE ADDRESS LOCATION OF A 

    // b has the address of a 
    printf( "Value of b: %p\n", b ); //will print the location of a 

    //how large is b (how large is an int pointer)? 
    printf( "sizeof b: %d\n", sizeof( b )); //size of the variable b is= 2 bytes 

    // And what is the address of b itself? 
    printf( "Value of &b: %p\n", &b ); 

    // An array is actually a pointer to the first element... 
    printf( "Value of c: %p\n", c ); //always a pointer to the 1st element(return the adress of the the 0 elemtn in array)

    // So, an array is the address of the first element... 
    printf( "Value of &c[0]: %p\n", &c[0] ); //first adress it the adress of 1st(0) element 

    // What's the size of the array in bytes? 
    printf( "sizeof c: %d\n", sizeof( c )); //if we know the number of elements,then we know the size,or number of elem in array*on each number in array)

    // Pass the array as a parameter 
    array_as_parameter( c ); 
    printf( "Value of d: %p\n", d ); 
    printf( "sizeof d: %d\n", sizeof( d )); 

    increment_byval( a ); //it stays 10,stays 10
    printf( "Value of a after by val increment: %d\n", a ); 

    increment_byref( &a ); 
    printf( "Value of a after by ref increment: %d\n", a ); //here prints 11

    return 0; 
}

/*

int a =10;
f1:a++;//in memory location 1,value 10. It gets a copy 10+1=11/but outside of the function it prints of copy,and its still 10 
f2(*a)++;//pointer++. the value at address of a +1 , says change the original value in memory,its become 11
*/