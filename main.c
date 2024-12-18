//
//  main.c
//  Calorie Diary
//	health management systems main flow implementation


//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"

#define EXERCISEFILEPATH "exercises.txt" // path to the exercise data file
#define DIETFILEPATH "diets.txt" // path to the diet data file
#define HEALTHFILEPATH "health_data.txt" // path to the health data file

static int choice; // variable to store user's menu choice

// main function for the healthcare management system
int main() {
	// To initialize the health data object. setting all fields to 0 initially
	// the reason for defining health_data here is that we need it initialized
	// before we can start calculating and updating the remaining calories
    HealthData health_data = {0};
    
    int remaining_calories; //variable to calculate remaining calories 241215
    
    
	// Tocode: to read the list of the exercises and diets
	// load exercise and diet information from files into the system
	// these functions read from predefined files to set up available exercises and diet options
    	loadExercises(EXERCISEFILEPATH); //read exercise data from excercises.txt 241215
    	loadDiets(DIETFILEPATH); //read diet data from diets.txt 241215

    // ToCode: to run the "Healthcare Management Systems" until all calories are used up or the user wants to exit the system
    // main loop for the healthcare management system, continues until remaining calories are zero or the user chooses to exit
    do {
    	// calculate remaining calories based on total intake, calories burned, basal metabolic rate
    	// it's essential to calculate remaining_calories here as health_data is already initialized
    	// the reason i separate the health_data initialization and remaining calories is because the health_data structure contains necessary fields for this calculation (total_calories_intake, total_calories_burned ...etc)
    	remaining_calories= health_data.total_calories_intake - health_data.total_calories_burned - BASAL_METABOLIC_RATE; // update remaining calories dynamically 241219
    	
    	// if remaining calories are 0, alert the user and stop the loop 241219
    	if (remaining_calories==0){
            printf("You have consumed all your calories for today! \n");
            
            break; // exit the loop 241219
		} 
		
		// if there are still calories remaining, display the menu and prompt the user for input
		else{
			printf("\n=======================================================================\n");
        	printf("[Healthcare Management Systems] \n");
        	printf("1. Exercise \n");
        	printf("2. Diet \n");
        	printf("3. Show logged information \n");
        	printf("4. Exit \n");
        	printf("Select the desired number: ");
        	scanf("%d", &choice); // store users choice 241219
        	printf("=======================================================================\n");
        }
        
		// ToCode: to run the sysmtem based on the user's choice
        switch (choice) {
            case 1:
            	inputExercise(&health_data); // log exercise information 241215
                break;
                
            case 2:
            	inputDiet(&health_data); // log diet information 241215
                break;
                
            case 3:
            	printHealthData(&health_data); // display all logged health data 241215
                break;
                
            case 4:
            	// exit message and loop termination
    			printf("Exit the system.\n");
    			printf("=======================================================================\n");
                break;
                
            default:
            	// handle invalid choices
                printf("[Error] Invalid option. \n");
                printf("Please try again! \n");
        }
    } while (choice!=4); //the loop will continue until the user chooses option 4(exit) 241217

    return 0; // exit the program
}

