#pragma once

#include <QObject>
#include <string>
#include <memory>

// Forward declaration
class Environment;

/**
 * @brief Represents an autonomous agent within the simulation.
 *        This class can be extended to incorporate advanced ML/AI features.
 */
class Agent
{
public:
    explicit Agent(int id);
    virtual ~Agent();

    virtual void update(const Environment& env);
    int id() const { return m_id; }

    // Additional AI/ML integration placeholders
    // e.g., TensorFlow session, model inputs/outputs, etc.

private:
    int m_id;
    // For storing agent state: position, velocity, etc.
};
