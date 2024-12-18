//
//  main.c
//  Calorie Diary
//	건강관리 프로그램의 주요 동착 흐름 실현 
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"

#define EXERCISEFILEPATH "exercises.txt"
#define DIETFILEPATH "diets.txt"
#define HEALTHFILEPATH "health_data.txt"

static int choice;

int main() {
	// To initialize the health data object
    HealthData health_data = {0};
    
    int remaining_calories; //variable to calculate remaining calories 241215
    
    
	// Tocode: to read the list of the exercises and diets
    	loadExercises(EXERCISEFILEPATH); //read the information in "excercises.txt" 241215
    	loadDiets(DIETFILEPATH); //read the information in "diets.txt" 241215

    // ToCode: to run the "Healthcare Management Systems" until all calories are used up or the user wants to exit the system
    do {
    	remaining_calories= health_data.total_calories_intake - health_data.total_calories_burned - BASAL_METABOLIC_RATE; // update remaining calories dynamically 241219
    	
    	// check if remaining calories are zero 241219
    	if (remaining_calories==0){
            printf("You have consumed all your calories for today! \n");
            
            break; // exit the loop 241219
		} 
		
		else{
			printf("\n=======================================================================\n");
        	printf("[Healthcare Management Systems] \n");
        	printf("1. Exercise \n");
        	printf("2. Diet \n");
        	printf("3. Show logged information \n");
        	printf("4. Exit \n");
        	printf("Select the desired number: ");
        	scanf("%d", &choice);
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
            	printHealthData(&health_data); // display health data 241215
                break;
                
            case 4:
            	
    			printf("Exit the system.\n");
    			printf("=======================================================================\n");
                break;
                
            default:
                printf("[Error] Invalid option. \n");
                printf("Please try again! \n");
        }
    } while (choice!=4); //setting exit conditions 241217

    return 0;
}

