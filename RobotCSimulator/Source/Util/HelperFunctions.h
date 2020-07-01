/*****************************************************************//**
 * \file   HelperFunctions.h
 * \brief  A bunch of general purpose functions.
 *********************************************************************/

#pragma once
#include <iostream>
#include <sstream>
#include <string>
#define M_PI 3.14159265359

/**
 * Returns the greatest raw value between two absolute values.
 * 
 * \param a A numerical type to be absoluted.
 * \param b A numerical type to be absoluted.
 * \return The raw value of the greatest number.
 */
template <typename T>
static T amax(T a, T b) {
	if (abs(a) > abs(b)) {
		return a;
	}
	return b;
}

/**
 * Given a angle in degrees, convert it into radians.
 * 
 * \param degrees An angle, in degrees.
 * \return A float representing the radians equivalent to
 * the degree.
 */
static float GetRadians(float degrees) {
	return degrees * (M_PI / 180.0f);
}