//
//  cal_diets.c
//  Diets for Calorie Diary
//	functions to load diet data and log diet activities into health data
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"

#define MAX_DIETS 100      			// Maximum number of diets
#define MAX_FOOD_NAME_LEN 50		// Maximum length of the name of food


// list of diets 
static Diet diet_list[MAX_DIETS];
static int diet_list_size = 0; //the current number of deits loaded 241218


/*
    description : read the information in "diets.txt"
*/

/* 241218
	function <loadDiets>
	input: DIEFILEPATH -  path to the file cantaining diet data
	process
		1. attempt to open the specified file in read mode
		2. use fscanf to read each line of the file. each line contains
			- a string representing the name of the diet
			- an integer representing the calories intake for the diet
		3. ensure the number of loaded diets does not exceed MAX_DIETS
		4. close the file after reading all entries
	remark
		- if the file cannot be loaded, a message is displayed. and the function returns
		- if the file contains more entries than MAX_DIETS, excess entries are ignored
	
*/
void loadDiets(const char* DIETFILEPATH) {
    FILE *file = fopen(DIETFILEPATH, "r");
    if (file == NULL) {
        printf("There is no file for diets! \n");
        return;
    }

     // ToCode: to read a list of the diets from the given file
    while (fscanf(file, "%s %d", diet_list[diet_list_size].food_name, &diet_list[diet_list_size].calories_intake)!=EOF) 
	{
        if (diet_list_size >= MAX_DIETS){
        	break; // prevent array overflow 241218
		}
		diet_list_size++; // increment the count of loaded diets 241217
    }
    
    fclose(file); //close the file after reading 241218
}

/*
    description : to enter the selected diet and the total calories intake in the health data
    input parameters : health_data - data object to which the selected diet and its calories are added 
    return value : No
    
    operation : 1. provide the options for the diets to be selected
    			2. enter the selected diet and the total calories intake in the health data
*/

/*
	function <inputDiet>
	input: health_data - pointer to the healthdata structure
	process
		1. display all loaded diets, showing their index, name, and calories intake.
		2. prompt the user to select a diet by its displayed index or enter 0 to exit
		3. validate the users selection
			- ensure the choice is within the valid range (1 to diet-list-size)
			- handle invalid inputs gracefully by displaying error message
		4. if the user does not exit
			a. retrieve the selected diet's name and calorie intake
			b. update the health data
				- add the diet name and calorie intake to the diet history
				- increment the diet count
				- update the total calories intake
		5. display a summary of the logged diet including name and calories intake
	remark
		- handles invalid user inputs (out of range index etc...)
		- gracefully exits if the user chooses 0

*/
void inputDiet(HealthData* health_data) {
    int choice, i;
    
    // ToCode: to provide the options for the diets to be selected
    printf("The list of diets:\n");
    for(i=0; i<diet_list_size; i++)
	{
		printf("%d: %s (%d kcal per min.)\n", i+1, diet_list[i].food_name , diet_list[i].calories_intake); // print out a diet list 241217
	}
    
	// ToCode: to enter the diet to be chosen with exit option
	// prompt the user for their choice
    printf("Enter the number of the diet to log (0 to exit): "); //present exit options 241217
	scanf("%d", &choice); //scan a user's choice number 241217
	
	if(choice<0 || choice> diet_list_size)
	{
		printf("Invalid choice.\n");
		return;
	}
	if (choice == 0)
	{
		return; // user chose to exit 241217
	}

	// update the selected diet's data
	int intake;
	intake = diet_list[choice-1].calories_intake;
	
    // ToCode: to enter the selected diet in the health data
    strcpy(health_data->diet[health_data->diet_count].food_name, diet_list[choice-1].food_name); // save selected food 241127
	health_data->diet[health_data->diet_count].calories_intake = intake;
	 
	
    // ToCode: to enter the total calories intake in the health data
    health_data -> diet_count++; // increment the diet count 241218
	health_data->total_calories_intake += intake; //update total calories intake 241218
	
	//display a summary of the logged diet 241218
	printf("Food: %s, Calories intake: %d kcal\n", choice, diet_list[choice-1].food_name,diet_list[choice-1].calories_intake);

}

