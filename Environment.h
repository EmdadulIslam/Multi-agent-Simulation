#pragma once

#include <vector>
#include <QObject>
#include <QMutex>

class Environment
{
public:
    Environment();
    ~Environment();
    
    void update();

    // E.g., define environment data structures: grids, obstacles, etc.
    // Provide getters/setters for agent queries
private:
    // Implementation details for environment state
    // For instance, a grid or map data
};
