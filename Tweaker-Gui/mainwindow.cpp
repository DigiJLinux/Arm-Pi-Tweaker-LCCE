#include "mainwindow.h"
#include "upgradewidget.h"
#include "systemmanager.h"
#include "gpumanager.h"
#include "kernelmanager.h"
#include "storagemanager.h"
#include <QApplication>
#include <QMessageBox>
#include <QFileDialog>
#include <QGridLayout>
#include <QFrame>
#include <QFont>
#include <QDialogButtonBox>
#include <QDialog>
#include <QLineEdit>
#include <QResizeEvent>
#include <QScreen>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_tabWidget(nullptr)
    , m_upgradeWidget(nullptr)
    , m_statusOutput(nullptr)
    , m_progressBar(nullptr)
    , m_statusLabel(nullptr)
    , m_gpuManager(nullptr)
    , m_kernelManager(nullptr)
    , m_storageManager(nullptr)
    , m_systemManager(nullptr)
{
    setWindowTitle("Arm-Pi Tweaker - Orange Pi 5+ Optimization Tool");
    setMinimumSize(1000, 700);
    resize(1200, 800);
    
    m_systemManager = new SystemManager(this);
    
    setupUI();
    setupMenuBar();
    
    // Apply initial dynamic sizing
    updateDynamicSizes();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    m_tabWidget = new QTabWidget(this);
    setCentralWidget(m_tabWidget);
    
    setupTabs();
    
    // Status bar
    statusBar()->showMessage("Ready - Orange Pi 5+ Tweaker");
    
    // Set initial tab
    m_tabWidget->setCurrentIndex(0);
}

void MainWindow::setupMenuBar()
{
    QMenuBar *menuBar = this->menuBar();
    
    // Settings Menu
    QMenu *settingsMenu = menuBar->addMenu("&Settings");
    QAction *systemTweaksAction = settingsMenu->addAction("System &Tweaks");
    QAction *preferencesAction = settingsMenu->addAction("&Preferences");
    settingsMenu->addSeparator();
    QAction *exitAction = settingsMenu->addAction("E&xit");
    
    connect(systemTweaksAction, &QAction::triggered, [this]() { m_tabWidget->setCurrentIndex(5); });
    connect(preferencesAction, &QAction::triggered, this, &MainWindow::showSettings);
    connect(exitAction, &QAction::triggered, this, &QWidget::close);
    
    // Tools Menu
    QMenu *toolsMenu = menuBar->addMenu("&Tools");
    QAction *upgradeAction = toolsMenu->addAction("Ubuntu &Upgrade");
    QAction *imageEditorAction = toolsMenu->addAction("&Image Editor");
    QAction *kernelManagerAction = toolsMenu->addAction("&Kernel Manager");
    QAction *gpuManagerAction = toolsMenu->addAction("&GPU Manager");
    QAction *storageManagerAction = toolsMenu->addAction("&Storage Manager");
    
    connect(upgradeAction, &QAction::triggered, [this]() { m_tabWidget->setCurrentIndex(0); });
    connect(imageEditorAction, &QAction::triggered, [this]() { m_tabWidget->setCurrentIndex(1); });
    connect(kernelManagerAction, &QAction::triggered, [this]() { m_tabWidget->setCurrentIndex(2); });
    connect(gpuManagerAction, &QAction::triggered, [this]() { m_tabWidget->setCurrentIndex(3); });
    connect(storageManagerAction, &QAction::triggered, [this]() { m_tabWidget->setCurrentIndex(4); });
    
    // View Menu
    QMenu *viewMenu = menuBar->addMenu("&View");
    QAction *statusLogAction = viewMenu->addAction("Status &Log");
    QAction *refreshAction = viewMenu->addAction("&Refresh");
    
    connect(statusLogAction, &QAction::triggered, [this]() { m_tabWidget->setCurrentIndex(6); });
    
    // Help Menu
    QMenu *helpMenu = menuBar->addMenu("&Help");
    QAction *aboutAction = helpMenu->addAction("&About");
    QAction *docsAction = helpMenu->addAction("&Documentation");
    
    connect(aboutAction, &QAction::triggered, this, &MainWindow::showAbout);
}

void MainWindow::setupTabs()
{
    setupUpgradeTab();
    setupImageEditorTab();
    setupKernelManagerTab();
    setupGpuManagerTab();
    setupStorageTab();
    setupSystemTweaksTab();
    setupStatusTab();
}

void MainWindow::setupUpgradeTab()
{
    m_upgradeTab = new QWidget();
    m_tabWidget->addTab(m_upgradeTab, "🔄 Ubuntu Upgrade");
    
    QVBoxLayout *layout = new QVBoxLayout(m_upgradeTab);
    
    // Title
    QLabel *title = new QLabel("Ubuntu Upgrade Mode");
    QFont titleFont = title->font();
    titleFont.setPointSize(18);
    titleFont.setBold(true);
    title->setFont(titleFont);
    title->setStyleSheet("color: #000000; margin: 10px;");
    layout->addWidget(title);
    
    // Description
    QLabel *description = new QLabel(
        "Upgrade Ubuntu 22.04 to 24.10 with Orange Pi 5+ drivers and kernel support.\n"
        "First extract the correct drivers from the mounted upgrade.img, then run the upgrade."
    );
    description->setWordWrap(true);
    description->setStyleSheet("margin: 5px; padding: 10px;");
    layout->addWidget(description);
    
    // Create upgrade widget
    m_upgradeWidget = new UpgradeWidget(this);
    layout->addWidget(m_upgradeWidget);
    
    // Connect signals
    connect(m_upgradeWidget, &UpgradeWidget::extractDriversRequested, this, &MainWindow::onExtractDrivers);
    connect(m_upgradeWidget, &UpgradeWidget::runUpgradeRequested, this, &MainWindow::onRunUpgrade);
    connect(m_upgradeWidget, &UpgradeWidget::patchSystemRequested, this, &MainWindow::onPatchSystem);
    connect(m_upgradeWidget, &UpgradeWidget::rollbackRequested, this, &MainWindow::onRollbackUpgrade);
    
    // Connect system manager signals to upgrade widget
    connect(m_systemManager, &SystemManager::progressUpdated, m_upgradeWidget, &UpgradeWidget::updateProgress);
    connect(m_systemManager, &SystemManager::statusUpdated, m_upgradeWidget, &UpgradeWidget::updateStatus);
    connect(m_systemManager, &SystemManager::operationCompleted, [this](bool success, const QString &message) {
        m_upgradeWidget->setButtonsEnabled(true);
        statusBar()->showMessage(success ? "Operation completed successfully" : "Operation failed");
    });
}

void MainWindow::setupImageEditorTab()
{
    m_imageEditorTab = new QWidget();
    m_tabWidget->addTab(m_imageEditorTab, "🖼️ Image Editor");
    
    QVBoxLayout *layout = new QVBoxLayout(m_imageEditorTab);
    
    QLabel *title = new QLabel("Live Linux Image Editor");
    QFont titleFont = title->font();
    titleFont.setPointSize(18);
    titleFont.setBold(true);
    title->setFont(titleFont);
    title->setStyleSheet("color: #000000; margin: 10px;");
    layout->addWidget(title);
    
    QLabel *placeholder = new QLabel("Image Editor functionality will be implemented here.");
    placeholder->setAlignment(Qt::AlignCenter);
    placeholder->setStyleSheet("color: #666; font-size: 14px; margin: 50px;");
    layout->addWidget(placeholder);
}

void MainWindow::setupKernelManagerTab()
{
    m_kernelManagerTab = new QWidget();
    m_tabWidget->addTab(m_kernelManagerTab, "🐧 Kernel Manager");
    
    QVBoxLayout *layout = new QVBoxLayout(m_kernelManagerTab);
    
    // Create the actual Kernel Manager widget
    m_kernelManager = new KernelManager(m_systemManager, this);
    layout->addWidget(m_kernelManager);
}

void MainWindow::setupSystemTweaksTab()
{
    m_systemTweaksTab = new QWidget();
    m_tabWidget->addTab(m_systemTweaksTab, "⚙️ System Tweaks");
    
    QVBoxLayout *layout = new QVBoxLayout(m_systemTweaksTab);
    
    QLabel *title = new QLabel("System Tweaks & Configuration");
    QFont titleFont = title->font();
    titleFont.setPointSize(18);
    titleFont.setBold(true);
    title->setFont(titleFont);
    title->setStyleSheet("color: #000000; margin: 10px;");
    layout->addWidget(title);
    
    QLabel *placeholder = new QLabel("System Tweaks functionality will be implemented here.");
    placeholder->setAlignment(Qt::AlignCenter);
    placeholder->setStyleSheet("color: #666; font-size: 14px; margin: 50px;");
    layout->addWidget(placeholder);
}

void MainWindow::setupStatusTab()
{
    m_statusTab = new QWidget();
    m_tabWidget->addTab(m_statusTab, "📋 Status Log");
    
    QVBoxLayout *layout = new QVBoxLayout(m_statusTab);
    
    QLabel *title = new QLabel("System Status & Logs");
    QFont titleFont = title->font();
    titleFont.setPointSize(18);
    titleFont.setBold(true);
    title->setFont(titleFont);
    title->setStyleSheet("color: #000000; margin: 10px;");
    layout->addWidget(title);
    
    m_statusOutput = new QTextEdit();
    m_statusOutput->setReadOnly(true);
    m_statusOutput->setFont(QFont("Consolas", 10));
    layout->addWidget(m_statusOutput);
}

void MainWindow::onExtractDrivers()
{
    statusBar()->showMessage("Extracting Orange Pi 5+ drivers and kernel...");
    m_upgradeWidget->setButtonsEnabled(false);
    m_systemManager->extractDrivers();
}

void MainWindow::onRunUpgrade()
{
    statusBar()->showMessage("Running Ubuntu upgrade to 24.10...");
    m_upgradeWidget->setButtonsEnabled(false);
    m_systemManager->runUbuntuUpgrade();
}

void MainWindow::onPatchSystem()
{
    statusBar()->showMessage("Patching system with Orange Pi 5+ support...");
    m_upgradeWidget->setButtonsEnabled(false);
    m_systemManager->patchSystem();
}

void MainWindow::onRollbackUpgrade()
{
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Confirm Rollback",
        "Are you sure you want to rollback the upgrade? This will restore the previous system state.",
        QMessageBox::Yes | QMessageBox::No,
        QMessageBox::No
    );
    
    if (reply == QMessageBox::Yes) {
        statusBar()->showMessage("Rolling back upgrade...");
        m_upgradeWidget->setButtonsEnabled(false);
        m_systemManager->rollbackUpgrade();
    }
}

void MainWindow::setupGpuManagerTab()
{
    m_gpuManagerTab = new QWidget();
    m_tabWidget->addTab(m_gpuManagerTab, "🎮 GPU Manager");
    
    QVBoxLayout *layout = new QVBoxLayout(m_gpuManagerTab);
    
    // Create the actual GPU Manager widget
    m_gpuManager = new GpuManager(m_systemManager, this);
    layout->addWidget(m_gpuManager);
    
    // Connect GPU Manager signals to SystemManager
    connect(m_gpuManager, &GpuManager::installDriverRequested, 
            m_systemManager, &SystemManager::installGpuDriver);
    connect(m_gpuManager, &GpuManager::removeDriverRequested, 
            m_systemManager, &SystemManager::removeGpuDriver);
    connect(m_gpuManager, &GpuManager::switchDriverRequested, 
            m_systemManager, &SystemManager::switchGpuDriver);
}

void MainWindow::setupStorageTab()
{
    m_storageTab = new QWidget();
    m_tabWidget->addTab(m_storageTab, "💾 Storage Manager");
    
    QVBoxLayout *layout = new QVBoxLayout(m_storageTab);
    
    // Create the actual Storage Manager widget
    m_storageManager = new StorageManager(m_systemManager, this);
    layout->addWidget(m_storageManager);
}

void MainWindow::showAbout()
{
    QMessageBox::about(this, "About Arm-Pi Tweaker",
        "<h3>Arm-Pi Tweaker v0.1.0</h3>"
        "<p>Advanced GUI tool for Orange Pi 5+ optimization and Linux image editing.</p>"
        "<p>Features:</p>"
        "<ul>"
        "<li>Ubuntu distribution upgrade (22.04 → 24.10)</li>"
        "<li>Kernel management and optimization</li>"
        "<li>Hardware acceleration configuration</li>"
        "<li>Live Linux image editing</li>"
        "</ul>"
        "<p>© 2024 Setec Labs</p>"
    );
}

void MainWindow::showSettings()
{
    QDialog settingsDialog(this);
    settingsDialog.setWindowTitle("Application Settings");
    settingsDialog.setFixedSize(500, 300);
    settingsDialog.setStyleSheet("background-color: #DCDCDC;");
    
    QVBoxLayout *layout = new QVBoxLayout(&settingsDialog);
    
    // Title
    QLabel *titleLabel = new QLabel("Application Settings");
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(14);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("color: #000000; margin: 10px;");
    layout->addWidget(titleLabel);
    
    // Default Directories Group
    QGroupBox *dirGroup = new QGroupBox("Default Directories");
    dirGroup->setStyleSheet(
        "QGroupBox { font-weight: bold; color: #000000; border: 2px solid #000000; "
        "border-radius: 5px; margin: 5px; padding-top: 10px; background-color: #DCDCDC; }"
        "QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 5px 0 5px; }"
    );
    
    QVBoxLayout *dirLayout = new QVBoxLayout(dirGroup);
    
    // Kernel Directory Setting
    QLabel *kernelDirLabel = new QLabel("Default Kernel Directory:");
    kernelDirLabel->setStyleSheet("color: #000000;");
    dirLayout->addWidget(kernelDirLabel);
    
    QHBoxLayout *kernelDirEditLayout = new QHBoxLayout();
    QLineEdit *kernelDirEdit = new QLineEdit(m_kernelManager->getKernelDirectory());
    kernelDirEdit->setStyleSheet("background-color: #F0F0F0; color: #000000; border: 1px solid #000000;");
    kernelDirEditLayout->addWidget(kernelDirEdit);
    
    QPushButton *browseDirButton = new QPushButton("📁 Browse");
    browseDirButton->setStyleSheet("QPushButton { background-color: #F0F0F0; color: #000000; border: 2px solid #000000; padding: 4px; } QPushButton:hover { background-color: #E0E0E0; }");
    connect(browseDirButton, &QPushButton::clicked, [&kernelDirEdit, this]() {
        QString dir = QFileDialog::getExistingDirectory(this, "Select Default Kernel Directory", kernelDirEdit->text());
        if (!dir.isEmpty()) {
            kernelDirEdit->setText(dir);
        }
    });
    kernelDirEditLayout->addWidget(browseDirButton);
    
    dirLayout->addLayout(kernelDirEditLayout);
    
    layout->addWidget(dirGroup);
    
    // Spacer
    layout->addStretch();
    
    // Button box
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    buttonBox->setStyleSheet(
        "QPushButton { background-color: #F0F0F0; color: #000000; border: 2px solid #000000; padding: 8px; }"
        "QPushButton:hover { background-color: #E0E0E0; }"
    );
    
    connect(buttonBox, &QDialogButtonBox::accepted, [&settingsDialog, &kernelDirEdit, this]() {
        // Save settings
        m_kernelManager->setKernelDirectory(kernelDirEdit->text());
        settingsDialog.accept();
    });
    connect(buttonBox, &QDialogButtonBox::rejected, &settingsDialog, &QDialog::reject);
    
    layout->addWidget(buttonBox);
    
    settingsDialog.exec();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    updateDynamicSizes();
}

void MainWindow::updateDynamicSizes()
{
    // Update font sizes for all tabs based on window size
    if (m_upgradeWidget) {
        m_upgradeWidget->setStyleSheet(QString(
            "QLabel { font-size: %1pt; }"
            "QPushButton { font-size: %2pt; }"
            "QGroupBox { font-size: %2pt; }"
        ).arg(calculateFontSize(10)).arg(calculateFontSize(9)));
    }
    
    // Update GPU Manager font sizes
    if (m_gpuManager) {
        m_gpuManager->setStyleSheet(QString(
            "QLabel { font-size: %1pt; }"
            "QPushButton { font-size: %2pt; }"
            "QGroupBox { font-size: %2pt; }"
        ).arg(calculateFontSize(10)).arg(calculateFontSize(9)));
    }
    
    // Update tab widget font
    m_tabWidget->setStyleSheet(QString(
        "QTabBar::tab { font-size: %1pt; }"
    ).arg(calculateFontSize(10)));
}

int MainWindow::calculateFontSize(int baseSize)
{
    // Get current window size
    QSize windowSize = size();
    
    // Get screen size for reference
    QScreen *screen = QApplication::primaryScreen();
    QSize screenSize = screen->size();
    
    // Calculate scaling factor based on window width (minimum 800, reference 1200)
    double scaleFactor = qBound(0.8, (double)windowSize.width() / 1200.0, 1.5);
    
    // Apply additional scaling for very large screens
    if (screenSize.width() > 2560) {
        scaleFactor *= 1.2;
    }
    
    return qRound(baseSize * scaleFactor);
}