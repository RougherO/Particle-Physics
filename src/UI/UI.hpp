#pragma once
#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class UI {
    sf::RenderWindow& m_window;

public:
    UI(sf::RenderWindow& window);
    void processEvent(const sf::Event& event);
    void update(const sf::Time& dt);
    void draw();
    ~UI();
};