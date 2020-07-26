#include "DeltaClock.h"

sf::Clock DeltaClock::deltaTime;
sf::Time DeltaClock::bufferTime;

void DeltaClock::ResetTimer() {
	bufferTime = deltaTime.restart();
}

float DeltaClock::GetDelta() {
	return bufferTime.asSeconds();
}
