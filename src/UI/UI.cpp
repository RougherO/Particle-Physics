#include "UI.hpp"
#include "../Physics/Physics.hpp"

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
    ImGui::SetWindowSize({ 500, 300 });
    // Widgets
    // Particles
    ImGui::Text("Particle Configurations");
    ImGui::Checkbox("Random Radius", &Physics::randomRadius);
    if (!Physics::randomRadius) {
        ImGui::SliderFloat("Radius of Particle", &Physics::radius, Physics::randomRadiusllimit, Physics::randomRadiusulimit);
    } else {
        ImGui::SliderFloat(
            "Lower limit of random radius",
            &Physics::randomRadiusllimit,
            5.f, 50.f);
        ImGui::SliderFloat(
            "Upper limit of random radius",
            &Physics::randomRadiusulimit,
            5.f, 50.f);
    }
    ImGui::SliderFloat("Mass of Particle", &Physics::density, 10.f, 50.f);
    ImGui::Checkbox("Random Color", &Physics::circleColorRandom);
    if (!Physics::circleColorRandom) {
        ImGui::ColorEdit4("Particle Color", &Physics::circleColor[0]);
    }
    ImGui::SliderFloat("Coeff. of Restitution", &Physics::coeffOfRest, 0.f, 1.f);
    ImGui::SliderFloat("Friction of Particles", &Physics::friction, 0.f, 1.f);
    // Shooter
    ImGui::Text("Shooter Configuration");
    ImGui::SliderFloat("Velocity Of Eject", &Physics::velOfEject, 10.f, 1000.f);
    ImGui::SliderAngle("Angle Of Eject", &Physics::angleOfEject, 0, 360);
    ImGui::Text("Total Particles : %u", Physics::m_world.GetBodyCount());

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
