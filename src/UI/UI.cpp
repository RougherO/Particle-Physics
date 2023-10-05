#include "UI.hpp"
// #include "../Physics/Physics.hpp"

UI::UI(sf::RenderWindow& window)
    : m_window { window }
{
    if (!ImGui::SFML::Init(window)) {
        throw "Error in initialising ImGui context";
    }
}

void UI::processEvent(const sf::Event& event)
{
    ImGui::SFML::ProcessEvent(m_window, event);
}

void UI::update(const sf::Time& dt)
{
    ImGui::SFML::Update(m_window, dt);
    // Window Begin
    ImGui::Begin("Controls", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
    // Window Config
    ImGui::SetWindowPos({ 0, 0 });
    // Widgets
    // ImGui::SliderFloat("Radius of Particle", &Physics::particleRadius, 10.f, 50.f);
    // ImGui::SliderFloat("Mass of Particle", &Physics::particleMass, 10.f, 50.f);
    // ImGui::Checkbox("Random Color", &Physics::randomColor);
    // if (!Physics::randomColor) {
    //     ImGui::ColorEdit4("Particle Color", &Physics::particleColor[0]);
    // }
    // Window End
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
