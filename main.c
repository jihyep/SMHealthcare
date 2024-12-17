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
    
    int remaining_calories; //declare the remaining calorie variables 241215
    remaining_calories= health_data.total_calories_intake - health_data.total_calories_burned - BASAL_METABOLIC_RATE;
    // Tocode: to read the list of the exercises and diets
    	loadExercises(EXERCISEFILEPATH); //read the information in "excercises.txt" 241215
    	loadDiets(DIETFILEPATH); //read the information in "diets.txt" 241215

    // ToCode: to run the "Healthcare Management Systems" until all calories are used up or the user wants to exit the system
    do {
    	if (remaining_calories==0){
            printf("You have consumed all your calories for today! \n");
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
            	inputExercise(&health_data); //display the list of exercise through inputExercise if the user selects 1 241215
                break;
                
            case 2:
            	inputDiet(&health_data); //display the list of diet through inputDiet if the user selects 2 241215
                break;
                
            case 3:
            	printHealthData(&health_data); // print out the saved history if the user selects 3 241215
                break;
                
            case 4:
            	
    			printf("Exit the system.\n");
    			printf("=======================================================================\n");
                break;
                
            default:
                printf("[Error] Invalid option. \n");
                printf("Please try again! \n");
        }
    } while (choice!=4 && remaining_calories==0); //setting exit conditions 241217

    return 0;
}

