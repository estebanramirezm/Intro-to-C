/*
    Assignment #1 Part B
    Author: Esteban Ramirez
    Course: 3223 section 2
    Date: February 1st, 2024
    Description: This program calculates the net calories burned from walking, standing, drinking, and eating, and converts that to pounds lost or gained.
*/

#include <stdio.h>
#define WALK_CAL 5
#define STAND_CAL 2
#define DRINK_CAL 20
#define FOOD_CAL 40
#define CALS_PER_POUND 3500

// This function calculates the net calories burned and converts that to pounds lost or gained.
int main()
{

    // Greeting message
    printf("POUND LOSS/GAIN CALCULATOR\n\n");

    // Declare variables
    int walking, standing, drinking, eating;
    double poundsLost;

    // Ask user for minutes spent on each activity
    printf("How many minutes were you walking?\n");
    scanf("%d", &walking);
    printf("How many minutes were you standing?\n");
    scanf("%d", &standing);
    printf("How many minutes were you drinking?\n");
    scanf("%d", &drinking);
    printf("How many minutes were you eating?\n");
    scanf("%d", &eating);

    // Calculate total calories burned and consumed
    int totalBurned = (walking * WALK_CAL) + (standing * STAND_CAL);
    int totalConsumed = (drinking * DRINK_CAL) + (eating * FOOD_CAL);

    // Calculate net calories and convert to pounds
    int netCalories = totalBurned - totalConsumed;
    poundsLost = (double)netCalories / CALS_PER_POUND;

    // Output the result (depending on pounds lost or gained)
    if (poundsLost >= 0) {
        printf("You lost %.3f pounds today!\n", poundsLost);
    } else {
        printf("Weight lost is %.3f pounds.\n", poundsLost);
    }

    // Goodbye message and end successfully
    printf("\nThank you for using this program. Stay healthy!\n");
    return 0;
}
