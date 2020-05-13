#include "DeltaClock.h"

sf::Clock DeltaClock::deltaTime;
float DeltaClock::bufferDelta = 0.0f;


void DeltaClock::update() {
	bufferDelta = deltaTime.restart().asSeconds();
}

float DeltaClock::getDelta() {
	return bufferDelta;
}