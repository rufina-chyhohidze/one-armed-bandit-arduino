#include <stdio.h>
#include <stdlib.h> // For malloc, free
#include <string.h> // For strlen, strcpy
#include <display.h>
#include <buttons.h>


int heapMemoryUsed = 0;

// Function to allocate memory on the heap and copy the string
void writeLinesOnHeap(const char sentence[]) {
    // Calculate the length of the sentence, including the null terminator
    size_t sentenceLength = strlen(sentence) + 1;

    // Allocate memory on the heap
    char* heapCopy = (char*)malloc(sentenceLength);

    if (heapCopy != NULL) {
        // Copy the sentence to the allocated memory
        strcpy(heapCopy, sentence);

        // Update the total heap memory usage
        heapMemoryUsed += sentenceLength;

        // Print information about the heap allocation
        printf("\"%s\" is on the heap...\n", heapCopy);
        printf("%d bytes are now occupied on the heap...\n", heapMemoryUsed);

        // Free the allocated memory
        free(heapCopy); // It's important to free memory after use
    } else {
        printf("Memory allocation failed.\n");
    }
}
   

// Function prototype for heap allocation
void writeLinesOnHeap(const char sentence[0]);

int main() {
   initUSART();
    enableAllButtons();
   #define button1 PC1
   int displayValue=0;
 
    // The sentence to be allocated on the heap
    const char* sentence = "I am not allowed to speak in class.";
    

    // Loop to call the function 100 times
    while (1) {
        if (buttonPushed(button1)) {
          buttonPushed(button1); //additional it shows 1 on the screen when the button is pressed.
          displayValue+=1;
          writeNumber(displayValue); 

          _delay_ms(0.100);
    for (int i = 1; i <= 100; i++) {
        printf("%d: %s\n", i, sentence); // Output the sentence with an index
        writeLinesOnHeap(sentence); // Allocate and copy the sentence on the heap
        

    return 0; // End of the main function
}}}}