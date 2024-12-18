//
//  cal_healthdata.c
//	functions to save and display health data, including exercise and diet histories

//	updated with enhanced error handling and more detailed comments

//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"


/*
    description : enter the exercise and diet history in "health_data.txt" 
    input parameters : health_data - data object in which the selected exercise and diet is stored
    return value : No
    
    operation : 1. save the chosen exercise and total calories burned 
    			2. save the chosen diet and total calories intake 
    			3. save the total remaining calrories
*/

/*	241219
	function <saveData>
	input
		- HEALTHEFILEPATH: path to the file where data will be saved.
		- health_data: pointer to the Healthdata structure containing the exercise and diet records
	returns: NONE (void function)
	process
		1. open the specified file in write mode.
			- if the file cannot be opened, an error message is displayed. and the function returns
		2. write the exercise history to the file
			- include the name of each exercise and the calories burned per minute
			- write the total calories burned across all exercises
		3. write the diet history to the file
			- include the name of each food item and the calories consumed
			- write the total calories consumed across all diets
		4. calculate and write the remaining calories
			- remaining calories = total intake - total burend - basal metabolic rate
			- include the basal metabolic rate as part of the output for reference
		5. close the file to ensure all data is saved
	remark
		- error handling is provided to manage file access issues
		- data is written in a clear and organized format to facilitate readability
*/

void saveData(const char* HEALTHFILEPATH, const HealthData* health_data) {
	// PROCESS1 : attempt to open the file for writing
	// fopen returns a pointer to the file if successful, or NULL if the operation fails
	int i;
    FILE* file = fopen(HEALTHFILEPATH, "w");
    if (file == NULL) {
        printf("There is no file for health data.\n"); // if file cannot be opened display an error
        return;  // exit the function without performing further operations
    }

    // ToCode: to save the chosen exercise and total calories burned 
    
    // PROCESS2: write exercise history to the file 241219
    fprintf(file, "[Exercises] \n"); // header for the exercise section
    
    	for(i=0; i<health_data->exercise_count; i++)
    	{
    		//write each exercies name and calories burned per minute
    		// data is retrieved from the exercises array in health_data
    		fprintf(file, "%s - %d kcal\n", health_data->exercises[i].exercise_name, health_data->exercises[i].calories_burned_per_minute);
		} // save total exercise in .txt file 241217 
		
		fprintf(file, "Total calories burned: %d kcal\n", health_data->total_calories_burned); // input the total calories_burned in .txt file 241217 
    
    // ToCode: to save the chosen diet and total calories intake 
    // PROCESS3 : write diet history to the file 241219
    fprintf(file, "\n[Diets] \n");
    
    	for(i=0; i<health_data->diet_count; i++)
    	{
    		fprintf(file, "%s - %d kcal\n", health_data->diet[i].food_name, health_data->diet[i].calories_intake); // write each food item's name and the corresponding calories consumed
		} // save total diet in .txt file 241217
		
		//write the total calories consumed across all food item
		fprintf(file, "Total calories intake: %d kcal\n", health_data->total_calories_intake); // input the total calories_intake in .txt file 241217



    // ToCode: to save the total remaining calrories
    
    //PROCESS 4: calculate and write the total remaining calories to the file 241219
    fprintf(file, "\n[Total] \n"); // header for the summary section
    
    int remaining_calories = (health_data->total_calories_intake - health_data->total_calories_burned - BASAL_METABOLIC_RATE); //calculation of residual calories 241217 
    fprintf(file, "Basal metabolic rate - %d kcal\n", BASAL_METABOLIC_RATE); // write the basal metabolic rate for context
    fprintf(file, "The remaining calroies - %d kcal\n", remaining_calories); // save the total remaining calrories in .txt file 241217
    
    // PROCESS 5
    fclose(file); // close the file to save all data 241219
}

/*
    description : print the history of exercised and diets
    input parameters : health_data - data object in which the history of the exercise and diet is to be printed
    return value : No
    
    operation : 1. print out the saved history of exercises
    			2. print out the saved history of diets
    			3. print out the saved history of calories
*/

/*	241219
	function <printhealthdata>
	input: health_data- pointer to the healthdata structure containing the data to be displayed
	returns: NONE (void function)
	process
		1. display the exercise history
			- list each exercise with its name and calories burned per minute
			- if no exercises have been logged: a message is displayed
		2. display the diet history
			- list each food item with its name and calories consumed
			- if no diets have been logged, a message is displayed
		3. display the total calories
			- include the basal metabolic rate, total calories burned, total calories consumed, remaining calories
		4. provide personalized recommendations based on the remaining calories:
			- remaining calories = 0: indicates the user has perfectly balanced intake and exercise
			- remaining calories < 0: warns the user about consuming too few calories
			- remaining calories > 0: encourages the user to exercise more
		5. ensure all data is presented in a user friendly format
	remark
		- handles scenarios where no data exists with apporpriate message
		- presents data in a structured and readable format
	
*/

void printHealthData(const HealthData* health_data) {
	// PROCESS 1: calculate remaining calories for use in this function
	int i;
	int remaining_calories = (health_data->total_calories_intake - health_data->total_calories_burned - BASAL_METABOLIC_RATE);
	
	// ToCode: to print out the saved history of exercises
	// PROCESS 2: print the exercise history
	printf("=========================== History of Exercise =======================\n");
  	for(i=0; i<health_data->exercise_count; i++)
  	{
  		printf("Exercise: %s, Calories burned : %d kcal\n", health_data->exercises[i].exercise_name, health_data->exercises[i].calories_burned_per_minute);	
	} // print each exercise's name and calories burned per minute.. 241217
  
    printf("=======================================================================\n");

    // ToCode: to print out the saved history of diets
    // PROCESS 3: print the diet history
    printf("============================= History of Diet =========================\n");
	for(i=0; i<health_data->diet_count; i++)
	{
		printf("Food: %s, Calories intake: %d kcal\n", health_data->diet[i].food_name, health_data->diet[i].calories_intake);
	} // print each food item's name and calories consumed 241217

    printf("=======================================================================\n");


	// ToCode: to print out the saved history of calories including basal metabolic rate, 
	// PROCESS 4: total calories burned, total calories intake, and the remaining calories
	printf("============================== Total Calories =========================\n");
 		printf("Basal Metabolic Rate: %d kcal\n", BASAL_METABOLIC_RATE);
 		printf("Total calories burned: %d kcal\n", health_data->total_calories_burned);
 		printf("Total calories intake: %d kcal\n", health_data->total_calories_intake);
 		printf("The remaining calories: %d kcal\n", remaining_calories); // simple printing of total calorie information 241217
 	
    printf("=======================================================================\n \n");
    
	
	// ToCode: to print out the recommendtaion depending on the current total calories burned and intake    
    // PROCESS 5: provide recommendations based on calorie balance
	if (remaining_calories == 0)
    {
    	printf("You have consumed all your calories for today!\n");
	}
    	else if(remaining_calories<0)
    	{
    		printf("[Warining] Too few calories!\n");
    		if(health_data->total_calories_intake==DAILY_CALORIE_GOAL)
    		{
    			printf("Your total calorie intake for today has reached your goal!\n");
			}
			else if(health_data->total_calories_intake<DAILY_CALORIE_GOAL)
			{
				printf("Your total calorie intake for today has not reached your goal, remember to eat more!!\n");
			}
			else if(health_data->total_calories_intake>DAILY_CALORIE_GOAL)
			{
				printf("You have eaten more calories than planned today, but you have exercised too much!\n");
			}
    	}	
    	else
    	{
    		printf("Please exercise for your health!\n");
    		
    		if(health_data->total_calories_intake==DAILY_CALORIE_GOAL)
    		{
    			printf("Your total calorie intake for today has reached your goal!\n");
			}
			else if((health_data->total_calories_intake)<DAILY_CALORIE_GOAL)
			{
				printf("Your total calorie intake for today has not reached your goal, remember to eat more!!\n");
			}
		}
     // setting output options 241217 
	 printf("=======================================================================\n");
}
