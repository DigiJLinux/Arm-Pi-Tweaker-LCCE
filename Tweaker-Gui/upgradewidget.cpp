#include "upgradewidget.h"
#include <QScrollArea>
#include <QFrame>
#include <QFont>
#include <QTime>

UpgradeWidget::UpgradeWidget(QWidget *parent)
    : QWidget(parent)
    , m_extractGroup(nullptr)
    , m_upgradeGroup(nullptr)
    , m_patchGroup(nullptr)
    , m_rollbackGroup(nullptr)
    , m_warningGroup(nullptr)
    , m_extractButton(nullptr)
    , m_upgradeButton(nullptr)
    , m_patchButton(nullptr)
    , m_rollbackButton(nullptr)
    , m_progressBar(nullptr)
    , m_statusLabel(nullptr)
    , m_logOutput(nullptr)
{
    setupUI();
}

void UpgradeWidget::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // Create scroll area for the content
    QScrollArea *scrollArea = new QScrollArea();
    QWidget *scrollContent = new QWidget();
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollContent);
    
    // Warning section
    m_warningGroup = new QGroupBox("⚠️ IMPORTANT WARNINGS");
    m_warningGroup->setStyleSheet(
        "QGroupBox { font-weight: bold; color: #FF00FF; border: 2px solid #000000; "
        "border-radius: 5px; margin: 5px; padding-top: 10px; background-color: #DCDCDC; }"
        "QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 5px 0 5px; }"
    );
    
    QVBoxLayout *warningLayout = new QVBoxLayout(m_warningGroup);
    
    QLabel *warn1 = new QLabel("• GPU drivers will be auto-detected from /gpu directory");
    warn1->setStyleSheet("color: #FF00FF; font-weight: bold;");
    warningLayout->addWidget(warn1);
    
    QLabel *warn2 = new QLabel("• System backup is created automatically before patching");
    warn2->setStyleSheet("color: #FF00FF; font-weight: bold;");
    warningLayout->addWidget(warn2);
    
    QLabel *warn3 = new QLabel("• Internet connection required for Ubuntu upgrade");
    warn3->setStyleSheet("color: #FF00FF; font-weight: bold;");
    warningLayout->addWidget(warn3);
    
    QLabel *warn4 = new QLabel("• Process may take 30-60 minutes total");
    warn4->setStyleSheet("color: #FF00FF; font-weight: bold;");
    warningLayout->addWidget(warn4);
    
    QLabel *warn5 = new QLabel("• Use rollback if something goes wrong");
    warn5->setStyleSheet("color: #FF00FF; font-weight: bold;");
    warningLayout->addWidget(warn5);
    
    scrollLayout->addWidget(m_warningGroup);
    
    // Step 1: Extract drivers
    m_extractButton = new QPushButton("🔧");
    m_extractButton->setFixedSize(50, 50);
    m_extractButton->setStyleSheet("QPushButton { background-color: #F0F0F0; color: #000000; border: 2px solid #000000; font-weight: bold; font-size: 16px; } QPushButton:hover { background-color: #E0E0E0; }");
    m_extractGroup = createStepGroup(
        "📦 Step 1: Extract Orange Pi 5+ Files",
        "Extract drivers and kernel from /gpu and /upgrade directories",
        m_extractButton,
        "This will copy the Orange Pi 5+ specific files needed for 24.10"
    );
    scrollLayout->addWidget(m_extractGroup);
    
    connect(m_extractButton, &QPushButton::clicked, this, &UpgradeWidget::extractDriversRequested);
    
    // Step 2: Run upgrade
    m_upgradeButton = new QPushButton("🚀");
    m_upgradeButton->setFixedSize(50, 50);
    m_upgradeButton->setStyleSheet("QPushButton { background-color: #F0F0F0; color: #000000; border: 2px solid #000000; font-weight: bold; font-size: 16px; } QPushButton:hover { background-color: #E0E0E0; }");
    m_upgradeGroup = createStepGroup(
        "⬆️ Step 2: Run Ubuntu Upgrade",
        "Upgrade from Ubuntu 22.04 to 24.10 using standard process",
        m_upgradeButton,
        "This will run do-release-upgrade to Ubuntu 24.10"
    );
    scrollLayout->addWidget(m_upgradeGroup);
    
    connect(m_upgradeButton, &QPushButton::clicked, this, &UpgradeWidget::runUpgradeRequested);
    
    // Step 3: Patch system
    m_patchButton = new QPushButton("🛠️");
    m_patchButton->setFixedSize(50, 50);
    m_patchButton->setStyleSheet("QPushButton { background-color: #F0F0F0; color: #000000; border: 2px solid #000000; font-weight: bold; font-size: 16px; } QPushButton:hover { background-color: #E0E0E0; }");
    m_patchGroup = createStepGroup(
        "🔧 Step 3: Patch with Orange Pi 5+ Support",
        "Apply extracted drivers and kernel to the upgraded system",
        m_patchButton,
        "This will install the Orange Pi 5+ specific files on Ubuntu 24.10"
    );
    scrollLayout->addWidget(m_patchGroup);
    
    connect(m_patchButton, &QPushButton::clicked, this, &UpgradeWidget::patchSystemRequested);
    
    // Rollback section
    m_rollbackButton = new QPushButton("⚠️");
    m_rollbackButton->setFixedSize(50, 50);
    m_rollbackButton->setStyleSheet("QPushButton { background-color: #F0F0F0; color: #FF00FF; border: 2px solid #000000; font-weight: bold; font-size: 16px; } QPushButton:hover { background-color: #E0E0E0; }");
    m_rollbackGroup = createStepGroup(
        "🔙 Rollback: Restore Pre-Upgrade State",
        "Restore system to state before patching (if backup exists)",
        m_rollbackButton,
        "This will restore backed up files and undo Orange Pi 5+ patches"
    );
    scrollLayout->addWidget(m_rollbackGroup);
    
    connect(m_rollbackButton, &QPushButton::clicked, this, &UpgradeWidget::rollbackRequested);
    
    // Progress and status section
    QGroupBox *statusGroup = new QGroupBox("📊 Progress & Status");
    statusGroup->setStyleSheet(
        "QGroupBox { font-weight: bold; color: #000000; border: 2px solid #000000; "
        "border-radius: 5px; margin: 5px; padding-top: 10px; background-color: #DCDCDC; }"
        "QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 5px 0 5px; }"
    );
    
    QVBoxLayout *statusLayout = new QVBoxLayout(statusGroup);
    
    m_statusLabel = new QLabel("Ready - Select an operation above");
    m_statusLabel->setStyleSheet("font-weight: bold; color: #000000;");
    statusLayout->addWidget(m_statusLabel);
    
    m_progressBar = new QProgressBar();
    m_progressBar->setStyleSheet(
        "QProgressBar { border: 2px solid #000000; border-radius: 5px; background-color: #F0F0F0; color: #000000; }"
        "QProgressBar::chunk { background-color: #000000; }"
    );
    m_progressBar->setVisible(false);
    statusLayout->addWidget(m_progressBar);
    
    m_logOutput = new QTextEdit();
    m_logOutput->setMaximumHeight(200);
    m_logOutput->setReadOnly(true);
    m_logOutput->setFont(QFont("Consolas", 9));
    m_logOutput->setStyleSheet("background-color: #F0F0F0; color: #000000; border: 2px solid #000000;");
    statusLayout->addWidget(m_logOutput);
    
    scrollLayout->addWidget(statusGroup);
    
    // Set up scroll area
    scrollContent->setLayout(scrollLayout);
    scrollArea->setWidget(scrollContent);
    scrollArea->setWidgetResizable(true);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    
    mainLayout->addWidget(scrollArea);
}

QGroupBox* UpgradeWidget::createStepGroup(const QString &title, const QString &description, 
                                         QPushButton *button, const QString &helpText)
{
    QGroupBox *group = new QGroupBox(title);
    group->setStyleSheet(
        "QGroupBox { font-weight: bold; color: #000000; border: 2px solid #000000; "
        "border-radius: 5px; margin: 5px; padding-top: 10px; background-color: #DCDCDC; }"
        "QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 5px 0 5px; }"
    );
    
    QHBoxLayout *mainLayout = new QHBoxLayout(group);
    
    // Left side: button
    mainLayout->addWidget(button);
    
    // Right side: text content
    QVBoxLayout *textLayout = new QVBoxLayout();
    
    QLabel *descLabel = new QLabel(description);
    descLabel->setWordWrap(true);
    descLabel->setStyleSheet("color: #000000; font-size: 14px; font-weight: bold;");
    textLayout->addWidget(descLabel);
    
    QLabel *helpLabel = new QLabel(helpText);
    helpLabel->setStyleSheet("color: #00FFFF; font-size: 11px;");
    helpLabel->setWordWrap(true);
    textLayout->addWidget(helpLabel);
    
    mainLayout->addLayout(textLayout);
    
    return group;
}

void UpgradeWidget::updateProgress(int value)
{
    m_progressBar->setValue(value);
    if (value > 0 && !m_progressBar->isVisible()) {
        m_progressBar->setVisible(true);
    }
    if (value >= 100) {
        m_progressBar->setVisible(false);
    }
}

void UpgradeWidget::updateStatus(const QString &message)
{
    m_statusLabel->setText(message);
    m_logOutput->append(QString("[%1] %2").arg(QTime::currentTime().toString()).arg(message));
    
    // Auto-scroll to bottom
    QTextCursor cursor = m_logOutput->textCursor();
    cursor.movePosition(QTextCursor::End);
    m_logOutput->setTextCursor(cursor);
}

void UpgradeWidget::setButtonsEnabled(bool enabled)
{
    m_extractButton->setEnabled(enabled);
    m_upgradeButton->setEnabled(enabled);
    m_patchButton->setEnabled(enabled);
    m_rollbackButton->setEnabled(enabled);
}