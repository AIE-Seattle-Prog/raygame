#pragma once

#include <cmath>

inline float Min(float A, float B)
{
	// if A is less than B, return A, otherwise B
	return A < B ? A : B;
}

inline float MinSign(float A, float B)
{
	// if A is less than B, return A, otherwise B
	return abs(A) < abs(B) ? A : B;
}

inline bool NearlyEquals(float A, float B, float Tolerance = FLT_EPSILON)
{
	return abs(A - B) < Tolerance;
}

inline bool CheckThreshold(float A, float Threshold)
{
	float Dist = Threshold - A;

	// Dist is negative when A is larger than Threshold
	return Dist <= 0.0f;
}

inline bool CheckThreshold(float A, float Threshold, float & Exceeded)
{
	float Dist = Threshold - A;
	Exceeded = -Dist;

	// Dist is negative when A is larger than Threshold (i.e., met or exceeded threshold)
	return Dist <= 0.0f;
}
