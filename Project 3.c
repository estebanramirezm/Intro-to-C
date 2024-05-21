/*
    Assignment #3
    Author: Esteban Ramirez
    Course: COP 3223 section 2
    Date: March 14th, 2024
    Description: This program manages a food bank's inventory system via an interactive menu. It allows users to add donations,
    add requests, fulfill the earliest request, and print a status report showing current stock and pending requests.
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAX_TYPES 100
#define MAX_NAME_LEN 19

// Arrays for donations
char donationsType[MAX_TYPES][MAX_NAME_LEN + 1];
int donationsValue[MAX_TYPES];
int donationCounter = 0;

// Arrays for requests
char requestType[MAX_TYPES][MAX_NAME_LEN + 1];
int requestValue[MAX_TYPES];
int requestCounter = 0;

// Function declarations
void addDonation (void);
void addRequest (void);
void fulfillRequest (void);
void printStatusReport (void);
void exitProgram (void);

// This function manages a food bank's inventory system via an interactive menu
int main ()
{
  // Declare variables for the program
  int choice, repeat = 1;

  // Greeting
  printf ("Welcome!!!\n");

  // Loop that repeats the menu until the user wants to exit
  while (repeat == 1)
	{
	  // Print the available options
	  printf ("\nFood Bank Program\n\n");
	  printf ("1. Add a donation\n");
	  printf ("2. Add a request\n");
	  printf ("3. Fulfill the earliest request\n");
	  printf ("4. Print status report\n");
	  printf ("5. Exit\n\n");
	  printf ("Enter your choice: ");

	  // Ask user to input their choice
	  scanf ("%d", &choice);

	  // Direct the program to the appropriate path depending on the choice 
	  switch (choice)
		{
		case 1:
		  addDonation ();
		  break;
		case 2:
		  addRequest ();
		  break;
		case 3:
		  fulfillRequest ();
		  break;
		case 4:
		  printStatusReport ();
		  break;
		case 5:
		  repeat = 0;
		  break;
		default:
		  printf ("Invalid choice, please enter a number between 1 and 5.\n");
		  break;
		}
	}

  // Goodbye
  printf ("\nThanks for using this program!");

  // Exit program successfully
  return 0;
}

// Function that adds a donation
void addDonation ()
{
  // Variables to hold the donation type and amount
  char type[MAX_NAME_LEN + 1];
  int amount;

  // Prompt and read in the inventory type from the user
  printf ("\nEnter inventory type: ");
  scanf ("%s", type);

  // Prompt and read in the donation amount from the user
  printf ("Enter the amount: ");
  scanf ("%d", &amount);

  // Flag to check if the donation type already exists in the inventory
  bool found = false;

  // Loop through the existing donation types to check for a match
  for (int i = 0; i < donationCounter; i++)
	{
	  // If a matching donation type is found, update its amount
	  if (strcmp (donationsType[i], type) == 0)
		{
		  donationsValue[i] += amount;
		  found = true;
		  break;
		}
	}

  // If no matching donation type is found, add a new entry
  if (!found)
	{
	  strcpy (donationsType[donationCounter], type);
	  donationsValue[donationCounter] = amount;
	  donationCounter++;
	}

  // Notify the user that the donation was successfully added
  printf ("Donation Added!\n");

  // Go back to main menu
  return;
}

// Function that adds a request
void addRequest ()
{
  // Variables to hold the request type and amount
  char type[MAX_NAME_LEN + 1];
  int amount;

  // Prompt and read in the inventory type for the request from the user
  printf ("\nEnter inventory type: ");
  scanf ("%s", type);

  // Prompt and read in the amount for the request from the user
  printf ("Enter the amount: ");
  scanf ("%d", &amount);

  // Copy the requested type into the requests queue
  strcpy (requestType[requestCounter], type);

  // Set the requested amount for the new entry and increment the count of total requests
  requestValue[requestCounter] = amount;
  requestCounter++;

  // Notify the user that the request was successfully added
  printf ("Request Added!\n");

  // Go back to main menu
  return;
}

// Function that fulfills a request
void fulfillRequest ()
{
  // Check if there are any requests to fulfill
  if (requestCounter == 0)
	{
	  printf ("No requests to fulfill\n");
	  return;
	}

  // Iterate through donations to find a matching type for the first request
  for (int i = 0; i < donationCounter; i++)
	{
	  // Check if the current donation can fulfill the request
	  if (strcmp (donationsType[i], requestType[0]) == 0)
		{
		  // If the donation amount is equal to or greater than the request
		  if (donationsValue[i] >= requestValue[0])
			{
			  printf ("Request Fulfilled\n");
			  // Deduct the request amount from the donation
			  donationsValue[i] -= requestValue[0];

			  // If the donation is depleted, remove it from the donations list
			  if (donationsValue[i] == 0)
				{
				  // Shift remaining donations forward to fill the gap
				  for (int j = i; j < donationCounter - 1; j++)
					{
					  strcpy (donationsType[j],
							  donationsType[j + 1]);
					  donationsValue[j] = donationsValue[j + 1];
					}
				  donationCounter--;
				}

			  // Remove the fulfilled request from the queue
			  for (int j = 0; j < requestCounter - 1; j++)
				{
				  strcpy (requestType[j], requestType[j + 1]);
				  requestValue[j] = requestValue[j + 1];
				}
			  requestCounter--;
			}
		  else
			{
			  // If the donation amount is less than the request, partially fulfill it
			  printf ("Partially Fulfilled\n");
			  requestValue[0] -= donationsValue[i];
			  donationsValue[i] = 0;

			  // Remove the donation from the donations list
			  for (int j = i; j < donationCounter - 1; j++)
				{
				  strcpy (donationsType[j], donationsType[j + 1]);
				  donationsValue[j] = donationsValue[j + 1];
				}
			  donationCounter--;
			}
		  return;
		}
	}

  // If no matching donations are found, the request cannot be fulfilled
  printf ("Cannot be Fulfilled\n");

  // Go back to main menu
  return;
}

// Function that prints the status report
void printStatusReport ()
{
  // Begin printing the donations table with a header
  printf ("\nPrinting the Donations Table...\n");

  // Iterate over all donations to print each donation type and its amount
  for (int i = 0; i < donationCounter; i++)
	{
	  printf ("%s %d\n", donationsType[i], donationsValue[i]);
	}

  // Check if there's current donations, indicate if not
  if (!donationCounter)
	{
	  printf ("EMPTY\n");
	}

  // Print a header for the requests table
  printf ("\nPrinting the Requests Table...\n");

  // Check if there's current requests, indicate if not
  if (!requestCounter)
	{
	  printf ("EMPTY\n");
	}

  // Iterate over all requests to print each request type and its amount
  for (int i = 0; i < requestCounter; i++)
	{
	  printf ("%s %d\n", requestType[i], requestValue[i]);
	}
	
  // Go back to main menu
  return;
}
