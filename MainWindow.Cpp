#include "MainWindow.h"
#include "SimulationManager.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QTimer>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      m_simulationManager(new SimulationManager)
{
    setupUI();
    connectSignals();

    // Move the SimulationManager to its own thread for concurrent processing
    m_simulationManager->moveToThread(&m_simulationThread);

    // Start the thread
    m_simulationThread.start();
}

MainWindow::~MainWindow()
{
    m_simulationThread.quit();
    m_simulationThread.wait();
}

void MainWindow::setupUI()
{
    auto* centralWidget = new QWidget(this);
    auto* layout = new QVBoxLayout(centralWidget);

    // Example: Start/Stop buttons
    auto* btnStart = new QPushButton("Start Simulation", this);
    auto* btnStop  = new QPushButton("Stop Simulation", this);
    layout->addWidget(btnStart);
    layout->addWidget(btnStop);

    // Example: Status label
    auto* statusLabel = new QLabel("Status: Idle", this);
    layout->addWidget(statusLabel);

    setCentralWidget(centralWidget);
    resize(400, 200);
}

void MainWindow::connectSignals()
{
    // We use queued connections to interact with the manager in another thread
    connect(this, &MainWindow::onStartSimulation, m_simulationManager, &SimulationManager::startSimulation);
    connect(this, &MainWindow::onStopSimulation,  m_simulationManager, &SimulationManager::stopSimulation);

    // Connect signals from the manager back to the UI
    connect(m_simulationManager, &SimulationManager::simulationUpdated, this, &MainWindow::onUpdateUI);
}

void MainWindow::onStartSimulation()
{
    // Signal SimulationManager in another thread
    emit m_simulationManager->startSimulation();
}

void MainWindow::onStopSimulation()
{
    // Signal SimulationManager in another thread
    emit m_simulationManager->stopSimulation();
}

void MainWindow::onUpdateUI()
{
    // Here you would update your UI elements (e.g., charts, agent positions)
    // based on the latest data from SimulationManager
}
