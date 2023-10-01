#include "Physics.hpp"
#include <cmath>
#include <iostream>

Physics::Physics(const sf::Vector2u& windowSize, float dt)
    : m_windowSize { windowSize }
    , m_grid { windowSize }
    , m_dt { dt }
{
}

void Physics::addNewParticle(const sf::Vector2f& pos)
{
    size_t row = std::floor(pos.y / m_grid.divs);
    size_t col = std::floor(pos.x / m_grid.divs);
    if (row < m_grid.rows && col < m_grid.cols) {
        Particles particle = Particles(particleRadius, particleMass);
        sf::Color color {};
        if (!randomColor) {
            color = sf::Color(
                static_cast<int>(particleColor[0] * 255),
                static_cast<int>(particleColor[1] * 255),
                static_cast<int>(particleColor[2] * 255),
                static_cast<int>(particleColor[3] * 255));
        } else {
            color = sf::Color(
                rand() % 255,
                rand() % 255,
                rand() % 255, 255);
        }
        particle.setFillColor(color);
        particle.setPosition(pos);
        m_particleCollection.push_back(particle);
        m_grid.gridOfParticles[row * m_grid.cols + col].push_back(&m_particleCollection.back());
    }
}

void Physics::verletIntegrate()
{
    for (size_t row {}; row < m_grid.rows; ++row) {

        for (size_t col {}; col < m_grid.cols; ++col) {

            for (auto particle : m_grid.gridOfParticles[row * m_grid.cols + col]) {
                particle->Pos += particle->Vel * m_dt + 0.5f * particle->Acc * m_dt * m_dt;
                auto acc = particle->Acc;
                // particle->Acc = something
                particle->Acc.y += gravity;
                particle->prevVel = particle->Vel;
                particle->Vel += (particle->Acc + acc) * 0.5f * m_dt;
                particle->Acc *= 0.f; // resetting acc for next frame
            }
        }
    }
}

void Physics::solveConstraints()
{
    // top and bottom border
    for (size_t col {}; col < m_grid.cols; ++col) {
        for (auto particle : m_grid.gridOfParticles[0 * m_grid.cols + col]) {
            m_solveWallCollisions(particle);
        }
    }

    for (size_t col {}; col < m_grid.cols; ++col) {
        for (auto particle : m_grid.gridOfParticles[(m_grid.rows - 1) * m_grid.cols + col]) {
            m_solveWallCollisions(particle);
        }
    }

    // left and right border
    for (size_t row { 1 }; row < m_grid.rows - 1; ++row) {
        for (auto particle : m_grid.gridOfParticles[row * m_grid.cols + 0]) {
            m_solveWallCollisions(particle);
        }
        for (auto particle : m_grid.gridOfParticles[row * m_grid.cols + m_grid.cols - 1]) {
            m_solveWallCollisions(particle);
        }
    }
}

void Physics::m_solveWallCollisions(Particles* particle)
{
    float radius = particle->getRadius(), t {};
    if (particle->Pos.x < radius) {
        if (particle->prevVel.x < 0) {
            t = (radius - particle->Pos.x) / particle->prevVel.x;
            particle->Vel.x = particle->prevVel.x * -coeffOfRest;
        }
        particle->Pos.x = radius + particle->Vel.x * t;
    } else if (particle->Pos.x > m_windowSize.x - radius) {
        if (particle->prevVel.x > 0) {
            t = (particle->Pos.x + radius - m_windowSize.x) / particle->prevVel.x;
            particle->Vel.x = particle->prevVel.x * -coeffOfRest;
        }
        particle->Pos.x = m_windowSize.x - radius - particle->Vel.x * t;
    }
    if (particle->Pos.y < radius) {
        if (particle->prevVel.y < 0) {
            t = (radius - particle->Pos.y) / particle->prevVel.y;
            particle->Vel.y = particle->prevVel.y * -coeffOfRest;
        }
        particle->Pos.y = radius + particle->Vel.y * t;
    } else if (particle->Pos.y > m_windowSize.y - radius) {
        if (particle->prevVel.y > 0) {
            t = (particle->Pos.y - m_windowSize.y + radius) / particle->prevVel.y;
            particle->Vel.y = particle->prevVel.y * -coeffOfRest;
        }
        particle->Pos.y = m_windowSize.y - radius - particle->Vel.y * t;
    }
}

void Physics::solveCollisions()
{
    for (size_t row {}; row < m_grid.rows; ++row) {

        for (size_t col {}; col < m_grid.cols; ++col) {

            auto& cell1 = m_grid.gridOfParticles[row * m_grid.cols + col];
            for (ssize_t idrow { -1 }; idrow <= 1; ++idrow) {
                if (row + idrow >= 0 && row + idrow < m_grid.rows) {
                    for (ssize_t idcol { -1 }; idcol <= 1; ++idcol) {
                        if (col + idcol >= 0 && col + idcol < m_grid.cols) {
                            auto& cell2 = m_grid.gridOfParticles[(row + idrow) * m_grid.cols + (col + idcol)];
                            m_solveCellCollisions(cell1, cell2);
                        }
                    }
                }
            }
        }
    }
}

void Physics::m_solveCellCollisions(std::vector<Particles*>& cell1, std::vector<Particles*>& cell2)
{
    for (auto& particle1 : cell1) {
        for (auto& particle2 : cell2) {
            if (particle1 != particle2) {
                m_checkParticleCollision(particle1, particle2);
            }
        }
    }
}

void Physics::m_checkParticleCollision(Particles* particle1, Particles* particle2)
{
    sf::Vector2f collisionAxis { m_unitVec(particle2->Pos - particle1->Pos) };
    float dist = m_magOfVec(particle2->Pos - particle1->Pos);
    if (dist < particle1->getRadius() + particle2->getRadius() && m_dotProduct(particle1->prevVel, collisionAxis) > 0) {
        float t_leftAferCollision = m_justBeforeCollision(particle1, particle2, collisionAxis, dist);
        m_solveParticleCollision(particle1, particle2, collisionAxis, t_leftAferCollision);
    }
}

float Physics::m_justBeforeCollision(Particles* particle1, Particles* particle2, const sf::Vector2f& collisionAxis, float dist)
{
    float vel1MagOnAxis = std::abs(m_dotProduct(particle1->prevVel, collisionAxis));
    float vel2MagOnAxis = std::abs(m_dotProduct(particle2->prevVel, collisionAxis));
    float t_beforeIntersect {};
    if (vel1MagOnAxis + vel2MagOnAxis > 0)
        t_beforeIntersect = (particle1->getRadius() + particle1->getRadius() - dist) / (vel1MagOnAxis + vel2MagOnAxis);
    particle1->Pos -= particle1->prevVel * t_beforeIntersect;
    particle2->Pos -= particle2->prevVel * t_beforeIntersect;
    return t_beforeIntersect;
}

void Physics::m_solveParticleCollision(Particles* particle1, Particles* particle2, const sf::Vector2f& collisionAxis, float t_leftAfterCollision)
{
    float m1 = particle1->mass, m2 = particle2->mass;
    sf::Vector2f perpAxis { -collisionAxis.y, collisionAxis.x };
    // storing previous velocity along perpendicularAxis of collision since they are conserved
    auto u1_ = m_dotProduct(particle1->Vel, perpAxis) * perpAxis;
    auto u2_ = m_dotProduct(particle2->Vel, perpAxis) * perpAxis;
    // initial velocity along collision axis
    auto u1 = m_dotProduct(particle1->Vel, collisionAxis) * collisionAxis;
    auto u2 = m_dotProduct(particle2->Vel, collisionAxis) * collisionAxis;
    // final velocity along collision axis
    auto v1 = ((m1 - m2 * coeffOfRest) / (m1 + m2)) * u1 + (m2 * (1 + coeffOfRest)) / (m1 + m2) * u2;
    auto v2 = ((m2 - m1 * coeffOfRest) / (m1 + m2)) * u2 + (m1 * (1 + coeffOfRest)) / (m1 + m2) * u1;
    particle1->Vel = u1_ + v1;
    particle2->Vel = u2_ + v2;
    particle1->Pos += particle1->Vel * t_leftAfterCollision;
    particle2->Pos += particle2->Vel * t_leftAfterCollision;
}

void Physics::solve()
{
    verletIntegrate();
    solveConstraints();
    solveCollisions();
    solveConstraints();
    m_grid.updateGrid();
}

void Physics::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_grid);
}

inline float Physics::m_magOfVec(const sf::Vector2f& vec)
{
    return std::sqrt(vec.x * vec.x + vec.y * vec.y);
}

inline float Physics::m_dotProduct(const sf::Vector2f& vec1, const sf::Vector2f& vec2)
{
    return vec1.x * vec2.x + vec1.y * vec2.y;
}

sf::Vector2f Physics::m_unitVec(const sf::Vector2f& vec)
{
    float dist = m_magOfVec(vec);
    if (dist > 0)
        return vec / dist;
    return { 0.f, 0.f };
}
