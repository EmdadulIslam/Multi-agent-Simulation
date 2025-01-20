#include "SimulationManager.h"
#include <QThread>
#include <QDebug>

SimulationManager::SimulationManager(QObject* parent)
    : QObject(parent),
      m_environment(std::make_unique<Environment>())
{
    // Example: create a few agents
    for(int i = 0; i < 10; ++i) {
        m_agents.push_back(std::make_unique<Agent>(i));
    }
}

SimulationManager::~SimulationManager()
{
    stopSimulation();
}

void SimulationManager::startSimulation()
{
    if (!m_running.load()) {
        m_running.store(true);
        QtConcurrent::run([this]() { simulationLoop(); }); // or std::thread
    }
}

void SimulationManager::stopSimulation()
{
    m_running.store(false);
}

void SimulationManager::simulationLoop()
{
    // Example: main simulation update loop
    while (m_running.load()) {
        {
            QMutexLocker locker(&m_dataMutex);
            // Update environment
            m_environment->update();

            // Update each agent
            for (auto& agent : m_agents) {
                agent->update(*m_environment);
            }
        }

        // Notify UI about updates
        emit simulationUpdated();

        QThread::msleep(16); // ~60 FPS
    }
}
