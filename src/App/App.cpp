#include "App.hpp"

App::App(
    size_t width,
    size_t height,
    std::string_view title)

    : m_window { sf::VideoMode(width, height), std::string(title), sf::Style::Default }
    , m_physics { m_window.getSize(), m_dt }
    , m_ui { std::make_unique<UI>(m_window) }
    , m_io { ImGui::GetIO() }
{
    m_window.setFramerateLimit(120);
}

void App::update()
{
    while (m_window.pollEvent(m_eventHandler)) {
        ImGui::SFML::ProcessEvent(m_window, m_eventHandler);
        if (m_eventHandler.type == sf::Event::MouseButtonPressed && !m_io.WantCaptureMouse) {
            m_physics.addNewParticle(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)));
        }
        if (m_eventHandler.type == sf::Event::Closed) {
            m_window.close();
        }
    }
    // update ui
    m_ui->update(m_clock.restart());
    // update game logic
    m_physics.solve();
}

void App::draw()
{
    m_window.clear();
    m_window.draw(m_physics);
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