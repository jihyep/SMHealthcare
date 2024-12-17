//
//  cal_healthdata.c
//  Diets for Calorie Diary
//  printHealthData(healthdata 구조체 포인터) - healthdata 구조체에 저장된 정보를 기반으로 사용자에게 건강 관리 히스토리 및 추천사항 제공
// saveData(파일 포인터, healthdata 구조체 포인터) - 시스템 종료시, healthdata 구조체에 저장된 정보를 ‘health_data’ 파일로 백업

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

void saveData(const char* HEALTHFILEPATH, const HealthData* health_data) {
	int i;
    FILE* file = fopen(HEALTHFILEPATH, "w");
    if (file == NULL) {
        printf("There is no file for health data.\n");
        return;
    }

    // ToCode: to save the chosen exercise and total calories burned 
    fprintf(file, "[Exercises] \n");
    
    	for(i=0; i<health_data->exercise_count; i++)
    	{
    		fprintf(file, "%s - %d kcal\n", health_data->exercises[i].exercise_name, health_data->exercises[i].calories_burned_per_minute);
		} // save total exercise in .txt file 241217 
		
		fprintf(file, "Total calories burned: %d kcal\n", health_data->total_calories_burned); // input the total calories_burned in .txt file 241217 
    
    // ToCode: to save the chosen diet and total calories intake 
    fprintf(file, "\n[Diets] \n");
    
    	for(i=0; i<health_data->diet_count; i++)
    	{
    		fprintf(file, "%s - %d kcal\n", health_data->diet[i].food_name, health_data->diet[i].calories_intake);
		} // save total diet in .txt file 241217
		
		fprintf(file, "Total calories intake: %d kcal\n", health_data->total_calories_intake); // input the total calories_intake in .txt file 241217



    // ToCode: to save the total remaining calrories
    fprintf(file, "\n[Total] \n");
    
    int remaining_calories = (health_data->total_calories_intake - health_data->total_calories_burned - BASAL_METABOLIC_RATE); //calculation of residual calories 241217 
    fprintf(file, "Basal metabolic rate - %d kcal\n", BASAL_METABOLIC_RATE);
    fprintf(file, "The remaining calroies - %d kcal\n", remaining_calories); // save the total remaining calrories in .txt file 241217
    
    
    fclose(file);
}

/*
    description : print the history of exercised and diets
    input parameters : health_data - data object in which the history of the exercise and diet is to be printed
    return value : No
    
    operation : 1. print out the saved history of exercises
    			2. print out the saved history of diets
    			3. print out the saved history of calories
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
    	else if(remaining_calories>0)
    	{
    		printf("Please exercise for your health!\n");
    		
    		if(health_data->total_calories_intake==DAILY_CALORIE_GOAL)
    		{
    			printf("Your total calorie intake for today has reached your goal!\n");
			}
			if else(health_data->total_calories_intake<DAILY_CALOIRE_GOAL)
			{
				printf("Your total calorie intake for today has not reached your goal, remember to eat more!!\n");
			}
		}
     // setting output options 241217 
	 printf("=======================================================================\n");
}
