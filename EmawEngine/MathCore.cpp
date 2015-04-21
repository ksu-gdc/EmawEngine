#include "MathCore.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>

const f64 PI64 = M_PI;
const f32 PI = (f32)M_PI;

const f64 EPISLON64 = 0.00000001;
const f32 EPSILON = 0.000001f;

f32 RandomFloat(f32 min, f32 max)
{
	return ((f32)rand() / (f32)RAND_MAX) * (max - min) + min;
}