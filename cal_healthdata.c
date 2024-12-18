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
	process
		1. open the specified file in write mode.
			- if the file cannot be opened, an error message is displayed. and the function returns
		2. write the exercise history to the file
			- each exercise entry includes the exercise name and calories burned.
			- the total calories burned from all exercises is also written
		3. write the diet history to the file
			- each diet entry includes the food name and calories consumed.
			- the total calories consumed from all diets is also written
		4. write the total reamining calories to the file
			- this is calculated as total calories intake - total calories burned - basal metabolic rate
			- the basal metabolic rate is also recorded for reerence
		5. close the file to ensure all data is saved
	remark
		- handles scenarios where the file cannot be created or written to by displaying a user friendly 
*/

void saveData(const char* HEALTHFILEPATH, const HealthData* health_data) {
	int i;
    FILE* file = fopen(HEALTHFILEPATH, "w");
    if (file == NULL) {
        printf("There is no file for health data.\n");
        return;
    }

    // ToCode: to save the chosen exercise and total calories burned 
    
    //write exercise history to the file 241219
    fprintf(file, "[Exercises] \n");
    
    	for(i=0; i<health_data->exercise_count; i++)
    	{
    		fprintf(file, "%s - %d kcal\n", health_data->exercises[i].exercise_name, health_data->exercises[i].calories_burned_per_minute);
		} // save total exercise in .txt file 241217 
		
		fprintf(file, "Total calories burned: %d kcal\n", health_data->total_calories_burned); // input the total calories_burned in .txt file 241217 
    
    // ToCode: to save the chosen diet and total calories intake 
    // write diet history to the file 241219
    fprintf(file, "\n[Diets] \n");
    
    	for(i=0; i<health_data->diet_count; i++)
    	{
    		fprintf(file, "%s - %d kcal\n", health_data->diet[i].food_name, health_data->diet[i].calories_intake);
		} // save total diet in .txt file 241217
		
		fprintf(file, "Total calories intake: %d kcal\n", health_data->total_calories_intake); // input the total calories_intake in .txt file 241217



    // ToCode: to save the total remaining calrories
    
    //calculate and write the total remaining calories to the file 241219
    fprintf(file, "\n[Total] \n");
    
    int remaining_calories = (health_data->total_calories_intake - health_data->total_calories_burned - BASAL_METABOLIC_RATE); //calculation of residual calories 241217 
    fprintf(file, "Basal metabolic rate - %d kcal\n", BASAL_METABOLIC_RATE);
    fprintf(file, "The remaining calroies - %d kcal\n", remaining_calories); // save the total remaining calrories in .txt file 241217
    
    
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
	process
		1. display the exercise history
			- each entry shows the exercise name and calories burned
			- if no exercises have been logged: a message is displayed
		2. display the diet history
			- each entry shows the food name and calories consumed
			- if no diets have been logged, a message is displayed
		3. display the total calories
			- this includes the basal metabolic rate, total calories burned, total calories consumed, remaining calories
		4. provide personalized recommendations based on the remaining calories:
			- remaining calories = 0: indicates the user has perfectly balanced intake and exercise
			- remaining calories < 0: warns the user about consuming too few calories
			- remaining calories > 0: encourages the user to exercise more
		5. ensure all data is presented in a user friendly format
	remark
		- handles scenarios where no data has been logged by displaying apporpriate message
	
*/

void printHealthData(const HealthData* health_data) {
	int i;
	int remaining_calories = (health_data->total_calories_intake - health_data->total_calories_burned - BASAL_METABOLIC_RATE);
	
	// ToCode: to print out the saved history of exercises
	printf("=========================== History of Exercise =======================\n");
  	for(i=0; i<health_data->exercise_count; i++)
  	{
  		printf("Exercise: %s, Calories burned : %d kcal\n", health_data->exercises[i].exercise_name, health_data->exercises[i].calories_burned_per_minute);	
	} // Load exercise history from a .txt file into the exercise[] array.. 241217
  
    printf("=======================================================================\n");

    // ToCode: to print out the saved history of diets
    printf("============================= History of Diet =========================\n");
	for(i=0; i<health_data->diet_count; i++)
	{
		printf("Food: %s, Calories intake: %d kcal\n", health_data->diet[i].food_name, health_data->diet[i].calories_intake);
	} // Load exercise history from a .txt file into the diet[] array 241217

    printf("=======================================================================\n");


	// ToCode: to print out the saved history of calories including basal metabolic rate, 
	// total calories burned, total calories intake, and the remaining calories
	printf("============================== Total Calories =========================\n");
 		printf("Basal Metabolic Rate: %d kcal\n", BASAL_METABOLIC_RATE);
 		printf("Total calories burned: %d kcal\n", health_data->total_calories_burned);
 		printf("Total calories intake: %d kcal\n", health_data->total_calories_intake);
 		printf("The remaining calories: %d kcal\n", remaining_calories); // simple printing of total calorie information 241217
 	
    printf("=======================================================================\n \n");
    
	
	// ToCode: to print out the recommendtaion depending on the current total calories burned and intake    
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
