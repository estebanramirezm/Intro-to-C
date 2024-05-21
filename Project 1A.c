/*
    Assignment #1 Part A
    Author: Esteban Ramirez
    Course: 3223 section 2
    Date: February 1st, 2024
    Description: This program calculates the total cost of a purchase (including sales tax if applicable).
*/

#include <stdio.h>
#include <stdbool.h>
#define TAX_RATE 0.065

// This function calculates the total cost of a purchase (including sales tax if applicable).
int main()
{
    // Greeting message
    printf("GIFT SHOP PURCHASE CALCULATOR \n\n");

    // Declare variables
    double itemPrice, totalCost, taxAmount;
    int quantity, temp;
    bool isTaxed;

    // Ask the user to input the item price
    printf("What is the cost of the item to be purchased (in dollars)?\n");
    scanf("%lf", &itemPrice);

    // Ask the user to input the item quantity
    printf("How many of the item are you purchasing?\n");
    scanf("%d", &quantity);

    // Ask the user to input the tax status
    printf("Is the item a taxed item? (0 = no, otherwise = yes)\n");
    scanf("%d", &temp);
    isTaxed = temp;

    // Total cost calculation
    taxAmount = itemPrice * quantity * TAX_RATE * isTaxed;
    totalCost = (itemPrice * quantity) + taxAmount;

    // Output the total cost formatted to 2 decimal places
    printf("Your total purchase will cost $%.2f\n", totalCost);

    // Goodbye message and end succesfully
    printf("\nThanks for using this program!");
    return 0;
}
