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
struct Individual indi2[NP];

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
inline double calcIndividualValue(struct Individual indi_inst, double x) {
	double indi_value = 0;
	for (int sq = DIMENSION; sq >= 0; sq--)
	{
		indi_value += indi_inst.x[DIMENSION - sq] * pow(x, sq);
	}
	return indi_value;
}

double evalutionIndi(struct Individual indi_inst)
{
	indi_inst.score = 0;
	double x = RANGE_X_MIN;
	while (x < RANGE_X_MAX)
	{
		//double test = calcIndividualValue(i, x);
		double tmp = normal_distribution(x) - calcIndividualValue(indi_inst, x);
		indi_inst.score += pow(tmp, 2);

		if (indi_inst.score < 0)
			printf("asdf");
		//double aaa = ABS(RANGE_X_MIN - RANGE_X_MAX);
		x += EVAL_X_STEP;
	}
	return indi_inst.score;
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
		for (int j = 0; j < DIMENSION+1; j++)
		{
			indi[i].x[j] = myRand(RANGE_Y_MIN, RANGE_Y_MAX);
			printf("%lf, ", indi[i].x[j]);
			
		}
		indi[i].score = evalutionIndi(indi[i]);
		printf(" ---- %lf\n", indi[i].score);
	}

}




void main()
{
	//generate_input(normal_distribution);

	init();

	long gen_cnt = 0;

	while (gen_cnt < GENERATION_MAX)
	{
		for (int i = 0; i < NP; i++)
		{
			struct Individual trial;

			// Mutate, Recombine
			int a, b, c;
			do a = myRand(0, NP); while (a == i);
			do b = myRand(0, NP); while (b == i || b == a);
			do c = myRand(0, NP); while (c == i || c == a || c == b);

			int k = myRand(0, DIMENSION);
			for (int j = 0; j < DIMENSION+1; j++) 
			{
				if (isAbleToCrossover() || j == k) 
				{
					trial.x[j] = indi[c].x[j] + F * (indi[a].x[j] - indi[b].x[j]);
				}
				else 
				{
					trial.x[j] = indi[i].x[j];
				}
			}

			// Evaluate
			trial.score = evalutionIndi(trial);
			if (trial.score <= indi[i].score)
			{
				for (int j = 0; j < DIMENSION+1; j++)
				{
					indi2[i].x[j] = trial.x[j];
				}
				indi2[i].score = trial.score;
			}
			else
			{
				for (int j = 0; j < DIMENSION+1; j++)
				{
					indi2[i].x[j] = indi[i].x[j];
				}
				indi2[i].score = evalutionIndi(indi2[i]);
			}
			
		}

		// Copy population for next generation
		for (int i = 0; i < NP; i++)
		{
			for (int j = 0; j < DIMENSION+1; j++)
			{
				indi[i].x[j] = indi2[i].x[j];
				indi[i].score = indi2[i].score;

			}
		}

		// Output best individual for viewer
		double best_score = 987654231.0;
		int best_index = -1;
		for (int i = 0; i < NP; i++)
		{
			if (best_score > indi[i].score)
			{
				best_score = indi[i].score;
				best_index = i;
			}
			//printf("%d -> %d : %lf, %lf, %lf, ----- %lf\n", gen_cnt, i, indi[i].x[0], indi[i].x[1], indi[i].x[2], indi[i].score);
		}

		gen_cnt++;
		printf("\rbest of %d : ", gen_cnt);
		for (int j = 0; j < DIMENSION + 1; j++)
		{
			printf("%lf, ", indi[best_index].x[j]);
		}
		printf(" --> score : %lf\n", indi[best_index].score);
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





void evalution()
{
	double x = RANGE_X_MIN;

	while (x < RANGE_X_MAX)
	{
		for (int n = 0; n < NP; n++)
		{
			// Calculate indi value
			double indi_value = calcIndividualValue(indi[n], x);

			// Calulate solution value
			double sol_value = solution_func(x);

			indi[n].score = pow(indi_value - sol_value, 2);
		}
		x += EVAL_X_STEP;
	}
}



