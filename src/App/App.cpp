#include "App.hpp"

App::App(
    size_t width,
    size_t height,
    std::string_view title)

    : m_window { sf::VideoMode(width, height), std::string(title), sf::Style::Default }
    , m_ui { std::make_unique<UI>(m_window) }
    , m_io { ImGui::GetIO() }
{
    Physics::setMaxLength(m_window.getSize().x);
    Physics::createBoundary(0, 0, m_window.getSize().x, m_window.getSize().y);
    m_window.setFramerateLimit(120);
}

void App::update()
{
    while (m_window.pollEvent(m_eventHandler)) {
        ImGui::SFML::ProcessEvent(m_window, m_eventHandler);
        // if (m_eventHandler.type == sf::Event::MouseButtonPressed && !m_io.WantCaptureMouse) {
        //     Physics::spawnCircle();
        // }
        if (m_eventHandler.type == sf::Event::Closed) {
            m_window.close();
        }
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !m_io.WantCaptureMouse) {
        Physics::spawnCircle();
    }
    Physics::updateShooterPos(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)));
    // update ui
    m_ui->update(m_clock.restart());
    Physics::update(m_dt);
    // update game logic
}

void App::draw()
{
    m_window.clear();
    Physics::draw(m_window);
    m_ui->draw();
    m_window.display();
}

void App::run()
{
    while (m_window.isOpen()) {
        update();
        draw();
    }
}