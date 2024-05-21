/*
    Assignment #4
    Author: Esteban Ramirez
    Course: 3223 section 2
    Date: April 6th, 2024
    Description: This program implements a Payroll – W2 Form generator based on clock data
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_EMPLOYEES 20
#define MAX_LEN 30

// Employee struct (based on requirements)
struct employee {
    char first[MAX_LEN];
    char last[MAX_LEN];
    double payperhr;
    double gross;
    double taxes;
    double hours_in_week;
};

// Function declarations
void readEmployeeData(struct employee employees[], int *numEmployees, FILE *fp);
void calculateWeeklyHours(struct employee employees[], int numEmployees, FILE *fp, int totalWeeks);
void calculatePayAndTaxes(struct employee *emp);
void writeOutput(struct employee employees[], int numEmployees);

// Function that implements a Payroll – W2 Form generator based on clock data
int main() 
{
   // Declare and define variable and structs the program will use
    struct employee employees[MAX_EMPLOYEES];
    int numEmployees = 0;
    
    // Greeting 
    printf("PAYROLL – W2 FORM GENERATOR\n\n");
        
    // Open the files the program will work with
    FILE *inputFile = fopen("clock.txt", "r");
    FILE *outputFile = fopen("w2.txt", "w");
    printf("Files opened successfully\n");
    
    // Error handler for an invalid input/output file read
    if (!inputFile || !outputFile) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Read initial employee data
    printf("Reading data...\n\n");
    readEmployeeData(employees, &numEmployees, inputFile);

    // Process each week's data
    int totalWeeks;
    fscanf(inputFile, "%d", &totalWeeks);
    calculateWeeklyHours(employees, numEmployees, inputFile, totalWeeks);
    
    // Write the output to "w2.txt"
    printf("Data read successfully\nGenerating W2 forms...\n\n");
    writeOutput(employees, numEmployees);

    // Close files
    fclose(inputFile);
    fclose(outputFile);
    printf("W2 forms have been successfully generated in 'w2.txt'\n\n");

    // Finish program successfully
    printf("Thanks for using this program! :)");
    return EXIT_SUCCESS;
}

// Function that reads employee data
void readEmployeeData(struct employee employees[], int *numEmployees, FILE *fp) 
{
    // Read the number of employees
    fscanf(fp, "%d", numEmployees); 
    
    // Initialize the fields
    for(int i = 0; i < *numEmployees; i++) 
    {
        fscanf(fp, "%s %s %lf", employees[i].first, employees[i].last, &employees[i].payperhr);
        employees[i].gross = 0;
        employees[i].taxes = 0;
        employees[i].hours_in_week = 0;
    }
    
    // Go back to main
    return;
}

// Function that calculates hours per week worked for each employee
void calculateWeeklyHours(struct employee employees[], int numEmployees, FILE *fp, int totalWeeks) 
{
    // Declare variables for the function
    int weekRecords, i, j;
    char firstName[MAX_LEN], lastName[MAX_LEN];
    int hrIn, minIn, hrOut, minOut;
    double hoursWorked, overtimeHours;

    // Read the number of employee records (weekRecords) for each week
    for (i = 0; i < totalWeeks; i++) {
        fscanf(fp, "%d", &weekRecords);
        for (j = 0; j < weekRecords; j++) {
            fscanf(fp, "%s %s %d %d %d %d", lastName, firstName, &hrIn, &minIn, &hrOut, &minOut);

            // Calculate hours worked
            hoursWorked = (hrOut + minOut / 60.0) - (hrIn + minIn / 60.0);
            for (int k = 0; k < numEmployees; k++) {
                if (strcmp(employees[k].first, firstName) == 0 && strcmp(employees[k].last, lastName) == 0) {
                    employees[k].hours_in_week += hoursWorked;
                    break;
                }
            }
        }
        
        // Calculate pay and taxes for each employee after all records are processed for a week
        for (int k = 0; k < numEmployees; k++) 
        {
            calculatePayAndTaxes(&employees[k]);
            
            // Reset hours for the next week
            employees[k].hours_in_week = 0;
        }
    }
    
    // Go back to main
    return;
}

// Function that calculates the pay and taxes for each employee
void calculatePayAndTaxes(struct employee *emp) 
{
    // Calculate the hours worked by the employee. Any hours worked beyond 40 are considered overtime.
    double regularHours = emp->hours_in_week > 40 ? 40 : emp->hours_in_week;
    double overtimeHours = emp->hours_in_week > 40 ? emp->hours_in_week - 40 : 0;

    // Compute the pay for regular and overtime hours separately
    double regularPay = regularHours * emp->payperhr;
    double overtimePay = overtimeHours * emp->payperhr * 1.5;

    // Update the employee's cumulative gross pay
    emp->gross += regularPay + overtimePay;
    emp->taxes += regularPay * 0.1 + overtimePay * 0.2;
}

// Function that writes to the output file
void writeOutput(struct employee employees[], int numEmployees) 
{
    // Open output file + error handler
    FILE *outputFile = fopen("w2.txt", "w");
    if (!outputFile) {
        perror("Error opening output file");
        return;
    }

    // Write the output to "w2.txt"
    fprintf(outputFile, "Number of employees: %d\n\n", numEmployees);
    for (int i = 0; i < numEmployees; i++) {
        fprintf(outputFile, "W2 Form\n-------\n");
        fprintf(outputFile, "Name: %s %s\n", employees[i].first, employees[i].last);
        fprintf(outputFile, "Gross Pay: %.2f\n", employees[i].gross);
        fprintf(outputFile, "Taxes Withheld: %.2f\n", employees[i].taxes);
        fprintf(outputFile, "Net Pay: %.2f\n\n\n", employees[i].gross - employees[i].taxes);
    }

    // Close output file
    fclose(outputFile);
    
    // Go back to main
    return;
}

