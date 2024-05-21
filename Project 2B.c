/*
    Assignment #2 Part B
    Author: Esteban Ramirez
    Course: 3223 section 2
    Date: February 24th, 2024
    Description: Read in n, then n lastnames, and check to see if the first in the list is ever repeated again.
*/

#include <stdio.h>
#include <string.h>

int main() 
{
    // Declare variables
    int n;
    
    // Greeting
    printf("Last Name Repetition Checker\n\n");

    // Collect user inputs for n and last names. With basic input validation for n.
    do {
        printf("Enter n, followed by n Last Names (each last name must be a single word):\n");
        scanf("%d", &n);
        
        if (n <= 0) {
            printf("Invalid input. n must be a number greater than 0. Please try again.\n\n");
            while (getchar() != '\n');
        }
    } while (n <= 0);
    
    // Read first last name
    char firstLastName[100];
    scanf("%99s", firstLastName); 

    // Iterate through the list of last names to check if any is identical to the first last name
    int isRepeated = 0;
    for (int i = 1; i < n; i++) {
        char lastName[100];
        scanf("%99s", lastName);
        
        // Compare the current last name with the first. If a match is found, set flag and exit loop.
        if (strcmp(firstLastName, lastName) == 0) {
            isRepeated = 1; 
            break;
        }
    };

    // Display result
    if (isRepeated) {
        printf("First name in list is repeated.\n");
    } else {
        printf("First name in list is not repeated.\n");
    };

    // Goodbye 
    printf("\nThanks for using this program! :)\n");
    
    // Exit program successfully
    return 0;
}


