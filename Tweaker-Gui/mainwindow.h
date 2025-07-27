#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QProgressBar>
#include <QTextEdit>
#include <QGroupBox>
#include <QScrollArea>
#include <QStatusBar>
#include <QSplitter>

class UpgradeWidget;
class SystemManager;
class GpuManager;
class KernelManager;
class StorageManager;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onExtractDrivers();
    void onRunUpgrade();
    void onPatchSystem();
    void onRollbackUpgrade();
    void showAbout();
    void showSettings();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    void setupUI();
    void updateDynamicSizes();
    int calculateFontSize(int baseSize);
    void setupMenuBar();
    void setupTabs();
    void setupUpgradeTab();
    void setupImageEditorTab();
    void setupKernelManagerTab();
    void setupGpuManagerTab();
    void setupStorageTab();
    void setupSystemTweaksTab();
    void setupStatusTab();
    
    // UI Components
    QTabWidget *m_tabWidget;
    QWidget *m_upgradeTab;
    QWidget *m_imageEditorTab;
    QWidget *m_kernelManagerTab;
    QWidget *m_gpuManagerTab;
    QWidget *m_storageTab;
    QWidget *m_systemTweaksTab;
    QWidget *m_statusTab;
    
    // Upgrade Tab Components
    UpgradeWidget *m_upgradeWidget;
    QTextEdit *m_statusOutput;
    QProgressBar *m_progressBar;
    QLabel *m_statusLabel;
    
    // Manager Components
    GpuManager *m_gpuManager;
    KernelManager *m_kernelManager;
    StorageManager *m_storageManager;
    
    // Backend
    SystemManager *m_systemManager;
};

#endif // MAINWINDOW_H