//
//  cal_exercise.c
//  Excercise for Calorie Diary
//loadExercises(파일 포인터) - ‘exercises.txt’ 파일을 읽고 저장
// inputExercise(healthdata 구조체 포인터) - 사용자가 운동 옵션선택 시, 운동 종목 및 해당 운동을 통해 소모하는 칼로리를 계산하여 healthdata 구조체에 저장
//  Created by Eunju Cha
//

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
int exercise_list_size = 0;


/*
    description : read the information in "excercises.txt"
*/

void loadExercises(const char* EXERCISEFILEPATH) {
    FILE *file = fopen(EXERCISEFILEPATH, "r");
    if (file == NULL) {
        printf("There is no file for exercises! \n");
        return;
    }

    // ToCode: to read a list of the exercises from the given file
    while ( fscanf(file, "%s %d", exercise_list[exercise_list_size].exercise_name, &exercise_list[exercise_list_size].calories_burned_per_minute)!=EOF) 
	{
    	
        if (exercise_list_size >= MAX_EXERCISES){
        	break;
		}
		
		exercise_list_size ++; //increment the value each time it is saved 241217
    }

    fclose(file);
}


/*
    description : to enter the selected exercise and the total calories burned in the health data
    input parameters : health_data - data object to which the selected exercise and its calories are added 
    return value : No
    
    operation : 1. provide the options for the exercises to be selected
    			2. enter the duration of the exercise
    			3. enter the selected exercise and the total calories burned in the health data
*/

void inputExercise(HealthData* health_data) {
    int choice, duration, i;
    
    // ToCode: to provide the options for the exercises to be selected
    printf("The list of exercises: \n");
	for(i=0; i<exercise_list_size; i++);
	{
		printf("%d: %s (%d kcal per min.)\n", i+1, exercise_list[i].exercise_name,exercise_list[i].calories_burned_per_minute); // print out an exercise list 241217
	}
	if(choice > exercise_list_size)
	{
		printf("Invalid choice.\n");
		return;
	} // if an option is chosen that does not have

    // ToCode: to enter the exercise to be chosen with exit option
    printf("Enter 0 to exit."); //present exit options 241217
	scanf("%d", &choice); //scan a user's choice number 241217
	if (choice == 0)
	{
		return;
	} //exit
 
    
    // To enter the duration of the exercise
    printf("Enter the duration of the exercise (in min.): ");
    scanf("%d", &duration);

    // ToCode: to enter the selected exercise and total calcories burned in the health data
    int consumed_calories;
    consumed_calories = duration* exercise_list[choice -1].calories_burned_per_minute;
	
	strcpy(health_data->exercises[health_data->exercise_count].exercise_name, exercise_list[choice-1].exercise_name); //save the exercise name selected by the user 241217
	health_data->exercise_count++; // increase exercise count 241218 
	health_data->exercises[health_data->exercise_count -1].calories_burned_per_minute= consumed_calories; // a record of calorie consumption 241218
	health_data->total_calories_burned += consumed_calories; // summarizing total calorie consumption 241218
	
	printf("Exercise : %s, Calories burned: %d kcal\n", exercise_list[choice -1].exercise_name, calories_burned); // print out of exercise 241218
	
	 
}
