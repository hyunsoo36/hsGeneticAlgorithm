#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "functions.h"
#include "setting.h"


static const float F = 1.0f;
static const float CR = 0.5f;


struct Individual {
	double x[DIMENSION + 1];	// +1 is for zero square
	double score;
};

double input[INPUT_SIZE] = { 0, };
struct Individual indi[NP];

double(*solution_func)(double);

// Description : Generate random number between min and max
inline double myRand(double min, double max)
{
	return rand() / (32768.0 / abs(min - max)) + min;
}

// Description : This function is used for crossover
bool isAbleToCrossover()
{
	if (myRand(0.0, 1.0) < CR)
		return false;
	
	return true;
}

// Description : Calculate indi value
inline double calcIndividualScore(int n, double x) {
	double indi_value = 0;
	for (int sq = DIMENSION; sq >= 0; sq--)
	{
		indi_value += indi[n].x[DIMENSION - sq] * pow(x, sq);
	}
	return indi_value;
}

// Description : Initial value setting randomly.
void init()
{
	solution_func = normal_distribution;

	//srand(time(NULL));
	srand(987654321);	// for Debugging

	for (int i = 0; i < NP; i++)
	{
		printf("%d : ", i);
		for (int j = 0; j < DIMENSION; j++)
		{
			indi[i].x[j] = myRand(RANGE_Y_MIN, RANGE_Y_MAX);
			printf("%lf, ", indi[i].x[j]);
			
		}
		indi[i].score = 0;
		double x = RANGE_X_MIN;
		while (x < RANGE_X_MAX)
		{
			indi[i].score = calcIndividualScore(i, x);
			double aaa = ABS(RANGE_X_MIN - RANGE_X_MAX);
			x += EVAL_X_STEP;
		}
		printf(" ---- %lf\n", indi[i].score);
	}

}



void evalution()
{
	double x = RANGE_X_MIN;

	while (x < RANGE_X_MAX)
	{
		for (int n = 0; n < NP; n++)
		{
			// Calculate indi value
			double indi_value = calcIndividualScore(n, x);

			// Calulate solution value
			double sol_value = solution_func(x);

			indi[n].score = pow(indi_value - sol_value, 2);
		}
		x += EVAL_X_STEP;
	}
}

void main()
{
	//generate_input(normal_distribution);

	init();

	long gen_cnt = 0;

	while (gen_cnt < GENERATION_MAX)
	{
		// Mutate, Recombine

		// Evaluate

		// Sort

		// Select

		gen_cnt++;
	}
	
	for (int i = 0; i < INPUT_SIZE; i++)
	{
		//printf("%lf\n", input[i]);
	}

}

// Description : Gernerte input data for test	// Not use...
void generate_input()
{
	//srand(time(NULL));
	srand(987654321);

	for (int i = 0; i < INPUT_SIZE; i++)
	{
		double x = myRand(RANGE_X_MIN, RANGE_X_MAX);
		input[i] = solution_func(x);
	}

}









