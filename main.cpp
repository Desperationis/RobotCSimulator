#include "stdafx.h"
#include "Window.h"

int main()
{
	Window::CreateWindow(sf::VideoMode(800, 800), "Hello", sf::Style::Close);

	std::shared_ptr<sf::RectangleShape> shape = std::make_shared<sf::RectangleShape>();
	shape->setFillColor(sf::Color::Red);
	shape->setPosition(sf::Vector2f(100, 100));
	shape->setSize(sf::Vector2f(100, 100));

	Window::AddObject<sf::RectangleShape>(shape);

	while (Window::rawWindow->isOpen()) {
		Window::Render();
	}

	system("pause");
}
