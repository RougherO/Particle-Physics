#pragma once
#include <SFML/Graphics.hpp>
#include <string_view>
#include <memory>
#include "../Grid/Grid.hpp"
#include "../Physics/Physics.hpp"
#include "../UI/UI.hpp"

class App {
    sf::RenderWindow m_window;
    sf::Event m_eventHandler;
    sf::Clock m_clock {};
    float m_dt { 0.05f };
    Physics m_physics;
    std::unique_ptr<UI> m_ui;
    ImGuiIO& m_io;

public:
    App(
        size_t width,
        size_t height,
        std::string_view title);

    void update();
    void draw();
    void run();
};