#include "functions.h"
#include <math.h>

double normal_distribution(double x)
{

	return (1.0 / sqrt(2.0 * 3.141592)) * pow(2.728281, -(x * x / 2.0));
}

