#pragma once

#include <QObject>
#include <QMutex>
#include <atomic>
#include <vector>
#include <memory>
#include "Agent.h"
#include "Environment.h"

/**
 * @brief Manages the simulation lifecycle, agent updates, threading logic, and communication
 */
class SimulationManager : public QObject
{
    Q_OBJECT
public:
    explicit SimulationManager(QObject* parent = nullptr);
    ~SimulationManager();

signals:
    void simulationUpdated();

public slots:
    void startSimulation();
    void stopSimulation();

private:
    void simulationLoop();
    std::atomic_bool m_running{false};

    QMutex m_dataMutex;
    std::unique_ptr<Environment> m_environment;
    std::vector<std::unique_ptr<Agent>> m_agents;
};
