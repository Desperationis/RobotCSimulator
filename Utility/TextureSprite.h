/*****************************************************************//**
 * \file   ClassicSprite.h
 * \brief  A sf::Drawable with sprite properties.
 *********************************************************************/

#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "../WindowObjects/WindowObject.h"

class TextureSprite : public sf::Transformable, public WindowObject {
public:
	TextureSprite() = default;

	virtual void Update() = 0;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		states.transform *= getTransform();
		target.draw(rectangleShape, states);
	};

protected:

	bool LoadTextureFromFile(std::string fileName) {
		bool loaded = texture.loadFromFile(fileName);
		if (loaded) {
			rectangleShape.setTexture(&texture);
		}
		return loaded;
	};

	void SetRectSize(sf::Vector2f size) {
		rectangleShape.setSize(size);
	};

	sf::RectangleShape rectangleShape;

private:
	sf::Texture texture;
};