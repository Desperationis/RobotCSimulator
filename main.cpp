#include "stdafx.h"
#include "Window.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "Test.h"

int main()
{
	// Initialize window and ImGui
	Window::CreateWindow(sf::VideoMode(800, 800), "RobotCSimulator", sf::Style::Close);
	ImGui::SFML::Init(*Window::rawWindow);

	std::shared_ptr<sf::RectangleShape> shape = std::make_shared<sf::RectangleShape>();
	shape->setFillColor(sf::Color::Red);
	shape->setPosition(sf::Vector2f(100, 100));
	shape->setSize(sf::Vector2f(100, 100));

	std::shared_ptr<Test> test = std::make_shared<Test>();

	Window::AddObject(test);
	Window::AddObject(shape);

	sf::Clock deltaClock;
	while (Window::rawWindow->isOpen()) {
		Window::PollEvents();
		ImGui::SFML::Update(*Window::rawWindow, deltaClock.restart());
		Window::Render();
	}
}
