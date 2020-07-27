/*****************************************************************//**
 * \file   WindowObject.h
 * \brief  Base class for objects.
 * 
 * \author smart
 * \date   July 2020
 *********************************************************************/

#pragma once
#include <SFML/Graphics.hpp>

/**
 * Base class for all window objects. Derived from
 * sf::Drawable.
 */
struct WindowObject : public sf::Drawable {

	/**
	 * Called before draw().
	 */
	virtual void Update() {

	};

	/**
	 * Draws the object onto the screen using sf::Drawable's
	 * .draw() function.
	 * 
	 * \param target
	 * \param states
	 */
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {

	}

	/**
	 * Render stuff in ImGui without the restraints of
	 * const.
	 */
	virtual void ImGuiDraw() {
	
	};
};