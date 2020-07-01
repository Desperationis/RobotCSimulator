/*****************************************************************//**
 * \file   ClassicSprite.h
 * \brief  A sf::Drawable with sprite properties.
 *********************************************************************/

#pragma once
#include <SFML/Graphics.hpp>
#include <string>

/**
 * A sf::Drawable with properties needed for a sprite. Differs from 
 * sf::Sprite by providing a sizeable, textured, sf::RectangleShape. 
 */
class ClassicSprite : public sf::Drawable, public sf::Transformable {
public:
	/**
	 * Construct the sprite. No parameters necessary.
	 */
	ClassicSprite() = default;

	/**
	 * Loads a texture from a file in the root directory.
	 * 
	 * \param fileName A string representing the name of the file.
	 * \return A bool stating whether or not the texture successfully 
	 * loaded.
	 */
	bool LoadTextureFromFile(std::string fileName);

	/**
	 * Sets the size, in pixels, of the sprite's texture.
	 * 
	 * \param size A sf::Vector2f representing the dimensions of the texture.
	 */
	void SetSize(sf::Vector2f size);

	/**
	 * Internal sf::Drawable draw() function.
	 * 
	 * \param target
	 * \param states
	 */
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

protected:
	/**
	 * sf::RectangleShape representing the sprite's texture.
	 */
	sf::RectangleShape rect;

private:
	/**
	 * sf::Texture held in memory for use with rect.
	 */
	sf::Texture texture;
};