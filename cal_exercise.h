//
//  cal_exercise.h
//  Excercise for Calorie Diary
//
//  Created by Eunju Cha
//

#ifndef cal_exercise_h
#define cal_exercise_h

#include "cal_diets.h"
#include "cal_healthdata.h"

#define MAX_EXERCISES 100  			// Maximum number of exercises
#define MAX_EXERCISE_NAME_LEN 50	// Maximum length of the name of exercise
#define MAX_DIETS 100      			// Maximum number of diets
#define MAX_FOOD_NAME_LEN 50		// Maximum length of the name of food
#define DAILY_CALORIE_GOAL 2000  	// Recommended daily calorie intake for adult women
#define BASAL_METABOLIC_RATE 1300 	// Basal metabolic rate of adult women

void loadExercises(const char* EXERCISEFILEPATH);

#endif /* cal_exercise_h */
