/*****************************************************************//**
 * \file   DeltaClock.h
 * \brief  A clock used for delta timing.
 *********************************************************************/

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

/**
 * A global clock that provides the delta time every frame.
 */
class DeltaClock {
public:
	DeltaClock() = default;

	/**
	 * Updates the clock.
	 */
	static void Update();

	/**
	 * Get the delta of the current frame, as a float. This 
	 * delta time is represented in seconds.
	 * 
	 * \return A float representing the delta time.
	 */
	static float GetDelta();

	/**
	 * Get a copy of the current state of the clock.
	 * 
	 * \return The copy of the current clock as a sf::Clock.
	 */
	static sf::Clock GetClock();

	/**
	 * Don't want the delta time to be in seconds? Get the current 
	 * delta clock as a sf::Time.
	 * 
	 * \return 
	 */
	static sf::Time GetTime();

private:
	/**
	 * A sf::Clock used to measure the delta time.
	 */
	static sf::Clock deltaTime;

	/**
	 * A buffer used to "save" the current delta time as
	 * a sf::Time.
	 */
	static sf::Time bufferTime;
};