#include "ClassicSprite.h"

bool ClassicSprite::LoadTextureFromFile(std::string fileName) {
	bool loaded = texture.loadFromFile(fileName);
	if(loaded) {
		rect.setTexture(&texture);
	}
	return loaded;
}

void ClassicSprite::SetSize(sf::Vector2f size) {
	rect.setSize(size);
}

void ClassicSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(rect, states);
}