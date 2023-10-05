#pragma once
#include <SFML/Graphics.hpp>
#include <string_view>
#include <memory>
#include "../Physics/Physics.hpp"
#include "../UI/UI.hpp"

class App {
    sf::RenderWindow m_window;
    sf::Event m_eventHandler;
    sf::Clock m_clock {};
    float m_dt { 0.05f };
    std::unique_ptr<UI> m_ui;
    ImGuiIO& m_io;
    Physics phx;

public:
    App(
        size_t width,
        size_t height,
        std::string_view title);

    void update();
    void draw();
    void run();
};