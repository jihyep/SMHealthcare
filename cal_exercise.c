// cal_exercise.c
// Excercise for Calorie Diary
// exercise management module for the calorie diary application
// functions to load exercise data and log exercise activities into health data

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"

#define MAX_EXERCISES 100  			// Maximum number of exercises
#define MAX_EXERCISE_NAME_LEN 50	// Maximum length of the name of exercise


// To declare the structure of the exercises
static Exercise exercise_list[MAX_EXERCISES];
int exercise_list_size = 0; // the current number of exercise loaded 241218


/*
    description : read the information in "excercises.txt"
*/

/* 241218
	function <loadexercises>
	input: EXERCISEFILEPATH- path to the file contaning exercise data
	process
		1. attempt to open the specified file in read mode
		2. use fscanf to read each line of the file 
			each line contains - a string representing the name of an exercise, an t=integer representing the calories burned per minute for the exercise.
		3. ensure the number of loaded exercise does not exceed MAX_EXERCISES
		4. close the file after reading all entries
	remark
		1. if the file cannot be opened, a message is displayed. and the function returns
		2. if the file contains more entries than MAX_EXERCISES, excess entries are ignored
*/

void loadExercises(const char* EXERCISEFILEPATH) {
    FILE *file = fopen(EXERCISEFILEPATH, "r");
    if (file == NULL) {
        printf("There is no file for exercises!\n");
        return;
    }

    // ToCode: to read a list of the exercises from the given file
    while ( fscanf(file, "%s %d", exercise_list[exercise_list_size].exercise_name, &exercise_list[exercise_list_size].calories_burned_per_minute)!=EOF) 
	{
    	
        if (exercise_list_size >= MAX_EXERCISES){
        	break; // prevent array overflow 241218
		}
		
		exercise_list_size ++; // increment the count of loaded exercises 241218
    }

    fclose(file); // close the file after reading 241218
}


/*
    description : to enter the selected exercise and the total calories burned in the health data
    input parameters : health_data - data object to which the selected exercise and its calories are added 
    return value : No
    
    operation : 1. provide the options for the exercises to be selected
    			2. enter the duration of the exercise
    			3. enter the selected exercise and the total calories burned in the health data
*/


/* 241218
	function <inputExercise>
	input: health_data: pointer to the healthdata structure
	process
		1. display all loaded exercise, showing their index, name, and calories burned per minute
		2. prompt the user to select an exercise by its displayed index or enter 0 to exit
		3. validate the users selection
			- ensure the choice is within the valid range (1 to exercise_list_size)
			- handle invalid inputs gracefully by displaying an error message
		4. if the user does not exit
			a. prompt the user to enter the duration of the exercise in minutes
			b. validate the duration (must be a positive integer)
			c. calculate the total calories burned: multiply the duration by the calories burned per minute for the selected exercise
			d. upate the health data
				- add the exercise name and calories burned to the exercise history
				- increment the exercise count
				- update the total calories burned
		5. display a summary of the logged exercise, including name, duration, and calories burned.
	remark
		- handles invalid user inputs (out of range index, non-positive duration.. etc)
		- gracefully exits if the user chooses 0
			
*/			
void inputExercise(HealthData* health_data) {
    int choice, duration, i;
    
    // ToCode: to provide the options for the exercises to be selected
    // display the list of exercises 241218
    printf("The list of exercises: \n");
	for(i=0; i<exercise_list_size; i++)
	{
		printf("%d: %s (%d kcal per min.)\n", i+1, exercise_list[i].exercise_name,exercise_list[i].calories_burned_per_minute); // print out an exercise list 241217
	}
	
	// ToCode: to enter the exercise to be chosen with exit option
	//prompt the user for their choice 241218
	printf("Enter the number of the exercise to log (0 to exit)");
	scanf("%d", &choice); //scan a user's choice number 241217
	
	if(choice<0||choice>exercise_list_size)
	{
		printf("Invalid choice.\n"); // if an option is chosen that does not have
		return;
	}
	
	if (choice == 0)
	{
		return; //user chose to exit 241218
	}
 
    
    // To enter the duration of the exercise
    printf("Enter the duration of the exercise (in min.): ");
    scanf("%d", &duration);
    
    if (duration<=0)
    {
    	printf("Invalid duration.\n");\
    	return;
	}

    // ToCode: to enter the selected exercise and total calcories burned in the health data
    //calculate calories burned and update health data 241218
	int consumed_calories;
    consumed_calories = duration*exercise_list[choice -1].calories_burned_per_minute;
	
	// add exercise name and calories burned to health data 241217
	strcpy(health_data->exercises[health_data->exercise_count].exercise_name, exercise_list[choice-1].exercise_name); 
	health_data->exercises[health_data->exercise_count -1].calories_burned_per_minute= consumed_calories; // a record of calorie consumption 241218
	
	health_data->exercise_count++; // increment the exercise count 241218 
	health_data->total_calories_burned += consumed_calories; // update total calories burned 241218
	
	//display a summary of the logged exercise 241218
	printf("Exercise : %s, Calories burned: %d kcal (duration: %d minutes)\n", exercise_list[choice -1].exercise_name, consumed_calories, duration); 
	
}
