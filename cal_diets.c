//
//  cal_diets.c
//  Diets for Calorie Diary
//	loadDiets(파일 포인터) - ‘diets.txt’ 파일을 읽고 저장
// inputDiet(healthdata 구조체 포인터) - 사용자가 식사 옵션 선택시, 해당 식사 및 섭취하는 칼로리를 healthdata 구조체에 저장

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
static int diet_list_size = 0;


/*
    description : read the information in "diets.txt"
*/

void loadDiets(const char* DIETFILEPATH) {
    FILE *file = fopen(DIETFILEPATH, "r");
    if (file == NULL) {
        printf("There is no file for diets! \n");
        return;
    }

     // ToCode: to read a list of the diets from the given file
    while (fscanf(file, "%S %d", diet_list[diet_list_size].food_name, &diet_list[diet_list_size].calories_intake)!=EOF) 
	{
    	
        if (diet_list_size >= MAX_DIETS){
        	break;
		}
		
		diet_list_size++; // increment the value each time it is saved 241217
    }
    fclose(file);
}

/*
    description : to enter the selected diet and the total calories intake in the health data
    input parameters : health_data - data object to which the selected diet and its calories are added 
    return value : No
    
    operation : 1. provide the options for the diets to be selected
    			2. enter the selected diet and the total calories intake in the health data
*/

void inputDiet(HealthData* health_data) {
    int choice, i;
    
    // ToCode: to provide the options for the diets to be selected
    printf("The list of diets:\n");
    for(i=0; i<diet_list_size; i++);
	{
		printf("%d: %s (%d kcal per min.)\n", i+1, diet_list[i].food_name,diet_list[i].calories_intake); // print out a diet list 241217
	}
    
	// ToCode: to enter the diet to be chosen with exit option
    printf("Enter 0 to exit."); //present exit options 241217
	scanf("%d", &choice); //scan a user's choice number 241217
	if (choice == 0)
	{
		return;
	} //exit

    // ToCode: to enter the selected diet in the health data
    strcpy(health_data->diet[health_data->diet_count].food_name, diet_list[choice-1].food_name); // save selected food 241127

    // ToCode: to enter the total calories intake in the health data


}

