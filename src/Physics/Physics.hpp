#pragma once
#include <SFML/Graphics.hpp>
#include "../Particles/Particles.hpp"
#include "../Grid/Grid.hpp"
#include <list>
#include <vector>

struct Physics : sf::Drawable {

    Physics(const sf::Vector2u& windowSize, float dt);

    void addNewParticle(
        const sf::Vector2f& pos,
        Particles particle);

    void verletIntegrate();
    void solveCollisions();
    void solveConstraints();
    void enableGravity(bool val);
    void solve();

    float coeffOfRest { 1.f };

private:
    void m_solveWallCollisions(Particles* particle);
    void m_solveCellCollisions(std::vector<Particles*>& cell1, std::vector<Particles*>& cell2);
    void m_checkParticleCollision(Particles* particle1, Particles* particle2);
    void m_solveParticleCollision(Particles* particle1, Particles* particle2, const sf::Vector2f& axis, float t_leftAfterCollision);
    float m_justBeforeCollision(Particles* particle1, Particles* particle2, const sf::Vector2f& collisionAxis, float dist);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    float m_magOfVec(const sf::Vector2f& vec);
    float m_dotProduct(const sf::Vector2f& vec1, const sf::Vector2f& vec2);
    sf::Vector2f m_unitVec(const sf::Vector2f& vec);

    sf::Vector2u m_windowSize;
    Grid m_grid;
    bool m_gravityOn { true };
    float m_dt;
    std::list<Particles> m_particleCollection;
};