/*
    Assignment #2 Part C
    Author: Esteban Ramirez
    Course: 3223 section 2
    Date: February 24th, 2024
    Description: This program implements Assignment #2 Part A and B in a menu.
*/

#include <stdio.h>
#include <string.h>
#define FIRST_CAR_LENGTH 10
#define NORMAL_CAR_LENGTH 8
#define CAR_CAPACITY 4
#define MAX_TRACK_OCCUPANCY 0.25

// Function declarations
void partA();
void partB();

// Acts as a menu for the other functions
int main() 
{
    // Declare variables
    int choice;
    
    // Menu loop 
    do 
    {
        // Displays options
        printf("MENU\n\n");
        printf("1. Roller Coaster Redesigned Calculator\n");
        printf("2. Last Name Repetition Checker\n");
        printf("3. Exit\n");
        
        // Collects user input for the chosen option
        printf("Enter your choice: ");
        scanf("%d", &choice);
        while (getchar() != '\n');
        
        // Directs the program to the appropiate code block depending on the chosen option.
        switch (choice) 
        {
            case 1:
                partA();
                break;
            case 2:
                partB();
                break;
            case 3:
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);
    
    // Goodbye 
    printf("\nThanks for using this program! :)\n");
    
    // Exit program successfully
    return 0;
}

// Function definitions

// Function A: Roller Coaster Redesigned Calculator
void partA() 
{
    // Declare and define variables
    int trackLength, maxTrainLength, totalPeople, cars, actualTrainLength;
    int maxPeople = 0, optimalCars = 0, configurations = 0;
    float avgRatio = 0.0, totalRatio = 0.0, ratio;
    
    // Greeting
    printf("\nRoller Coaster Redesigned Calculator\n\n");

    // Collect user inputs for track length and maximum train length. With input validation.
    do {
        printf("What is the total length of the track, in feet? (must be less than 10000)\n");
        scanf("%d", &trackLength);
        if (trackLength <= 0 || trackLength >= 10000) {
            printf("Invalid input. Please try again\n\n");
        }
    } while (trackLength <= 0 || trackLength >= 10000);
    do {
        printf("What is the maximum length of a train, in feet? (must be between 10 and 100)\n");
        scanf("%d", &maxTrainLength);
        if (maxTrainLength < 10 || maxTrainLength > 100) {
            printf("Invalid input. Please try again\n\n"); 
        }
    } while (maxTrainLength < 10 || maxTrainLength > 100);
    
    // Find the optimal configuration
    for (actualTrainLength = FIRST_CAR_LENGTH; actualTrainLength <= maxTrainLength; actualTrainLength += NORMAL_CAR_LENGTH) 
    {
        // Calculate the number of cars and total people for each train configuration
        cars = (actualTrainLength - FIRST_CAR_LENGTH) / NORMAL_CAR_LENGTH + 1;
        int maxTrains = (int)(trackLength * MAX_TRACK_OCCUPANCY / actualTrainLength);
        totalPeople = cars * CAR_CAPACITY * maxTrains;
        
        // Update maximum people and optimal car count if a better configuration is found
        if (totalPeople > maxPeople) {
            maxPeople = totalPeople;
            optimalCars = cars;
        };
        
        // Calculate the passenger-to-length ratio for this configuration. Keep track of the number of configurations.
        ratio = (float)totalPeople / (actualTrainLength * maxTrains);
        totalRatio += ratio;
        configurations++;
    };

    // Calculate the average ratio 
    avgRatio = totalRatio / configurations;

    // Display the results
    printf("\nYour ride can have at most %d people on it at one time.\n", maxPeople);
    printf("This can be achieved with trains of %d cars.\n", optimalCars);
    printf("AVG Ratio: %.3f\n", avgRatio);
    
    // Clear the buffer before returning to main menu
    while (getchar() != '\n');
    
    // Return to main menu 
    printf("\nReturning to main menu...\n\n");
    return;
}

// Function B: Last Name Repetition Checker
void partB() 
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
    
    // Clear the buffer before returning to main menu
    while (getchar() != '\n');
    
    // Return to main menu 
    printf("\nReturning to main menu...\n\n");
    return;
}
