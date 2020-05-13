#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

/*
	A global clock used for delta time.
*/

class DeltaClock {
public:
	/**
	*  \brief Resets the clock's timer.
	*/
	static void update();

	/**
	*  \brief Returns the delta time collected by the previous cycle.
	*  \return float The delta time collected by the previous cycle.
	*/
	static float getDelta();

private:
	static sf::Clock deltaTime;
	static float bufferDelta;
};