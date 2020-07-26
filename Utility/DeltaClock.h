/*****************************************************************//**
 * \file   DeltaClock.h
 * \brief  A clock used for delta timing.
 *********************************************************************/

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

namespace DeltaClock {
	extern sf::Clock deltaTime;
	extern sf::Time bufferTime;

	extern void ResetTimer();
	extern float GetDelta();
}