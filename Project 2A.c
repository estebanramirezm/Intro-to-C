/*
    Assignment #2 Part A
    Author: Esteban Ramirez
    Course: 3223 section 2
    Date: February 24th, 2024
    Description: This program calculates the maximum passenger capacity for a ride. Based on Assignment #1 Part C
*/

#include <stdio.h>
#define FIRST_CAR_LENGTH 10
#define NORMAL_CAR_LENGTH 8
#define CAR_CAPACITY 4
#define MAX_TRACK_OCCUPANCY 0.25

int main() 
{
    // Declare and define variables
    int trackLength, maxTrainLength, totalPeople, cars, actualTrainLength;
    int maxPeople = 0, optimalCars = 0, configurations = 0;
    float avgRatio = 0.0, totalRatio = 0.0, ratio;
    
    // Greeting
    printf("Roller Coaster Redesigned Calculator\n\n");

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
    
    // Goodbye 
    printf("\nThanks for using this program! :)\n");
    
    // Exit program successfully
    return 0;
}


