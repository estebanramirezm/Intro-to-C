/*
    Assignment #1 Part C
    Author: Esteban Ramirez
    Course: 3223 section 2
    Date: February 1st, 2024
    Description: This program calculates the maximum passenger capacity for a ride.
*/

#include <stdio.h>
#define FIRST_CAR_LENGTH 10
#define NORMAL_CAR_LENGTH 8
#define CAR_CAPACITY 4
#define MAX_TRACK_OCCUPANCY 0.25

// This function calculates the maximum passenger capacity for a ride.
int main()
{
    // Greeting message
    printf("MAXIMUM PASSENGER CAPACITY CALCULATOR\n\n");

    // Define variables for the program
    int N, trackLength, maxTrainLength;

    // Ask the user how many cases will the program test
    printf("Enter the number of test cases (N):\n");
    scanf("%d", &N);

    // Testing cases
    for (int i = 0; i < N; i++) {
        printf("\nTest Case #%d:\n", i + 1);
        printf("What is the total length of the track, in feet?\n");
        scanf("%d", &trackLength);
        printf("What is the maximum length of a train, in feet?\n");
        scanf("%d", &maxTrainLength);

        // Calculate the length and number of cars for each train
        int actualTrainLength = FIRST_CAR_LENGTH;
        int cars = 1;
        while (actualTrainLength + NORMAL_CAR_LENGTH <= maxTrainLength) {
            actualTrainLength += NORMAL_CAR_LENGTH;
            cars++;
        }

        // Calculate maximum number of trains on the track
        int maxTrains = (int)(trackLength * MAX_TRACK_OCCUPANCY / actualTrainLength);

        // Calculate passenger capacity
        int totalCapacity = cars * CAR_CAPACITY * maxTrains;

        // Output passenger capacity
        printf("Your ride can have at most %d people on it at one time.\n", totalCapacity);

        // Check for any surplus length
        int surplus = maxTrainLength - actualTrainLength;
        if (surplus > 0) {
            printf("Maximum Length has a surplus of %d feet.\n", surplus);
        } else {
            printf("Maximum Length fits exactly.\n");
        }
    }

    // Goodbye message and end successfully
    printf("\nThank you for using the Maximum Passenger Capacity Calculator! :)\n");
    return 0;
}
