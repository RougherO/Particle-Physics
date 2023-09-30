#include "UI.hpp"

UI::UI(sf::RenderWindow& window)
    : m_window { window }
{
    ImGui::SFML::Init(window);
}

void UI::processEvent(const sf::Event& event)
{
    ImGui::SFML::ProcessEvent(m_window, event);
}

void UI::update(const sf::Time& dt)
{
    ImGui::SFML::Update(m_window, dt);

    ImGui::Begin("Controls", nullptr);
    ImGui::Text("Control Center");
    ImGui::End();
}

void UI::draw()
{
    ImGui::SFML::Render(m_window);
}

UI::~UI()
{
    ImGui::SFML::Shutdown();
}
