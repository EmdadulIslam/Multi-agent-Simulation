#pragma once

#include <QMainWindow>
#include <QThread>
#include <QPointer>

class SimulationManager;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void onStartSimulation();
    void onStopSimulation();
    void onUpdateUI();

private:
    QPointer<SimulationManager> m_simulationManager;
    QThread m_simulationThread;
    
    // UI components (buttons, status labels, etc.)
    void setupUI();
    void connectSignals();
};
