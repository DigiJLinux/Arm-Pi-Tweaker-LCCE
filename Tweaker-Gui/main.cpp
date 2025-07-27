#include <QApplication>
#include <QStyleFactory>
#include <QDir>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    // Set application properties
    app.setApplicationName("Arm-Pi Tweaker");
    app.setApplicationVersion("0.1.0");
    app.setOrganizationName("Setec Labs");
    app.setOrganizationDomain("seteclabs.com");
    
    // Set application style
    app.setStyle(QStyleFactory::create("Fusion"));
    
    // Apply custom ARM-Pi theme
    QPalette armPiPalette;
    armPiPalette.setColor(QPalette::Window, QColor(220, 220, 220));     // Background: Light Grey
    armPiPalette.setColor(QPalette::WindowText, QColor(0, 0, 0));       // Text: Black
    armPiPalette.setColor(QPalette::Base, QColor(240, 240, 240));       // Input backgrounds: Lighter grey
    armPiPalette.setColor(QPalette::AlternateBase, QColor(200, 200, 200)); // Alternate backgrounds
    armPiPalette.setColor(QPalette::ToolTipBase, QColor(240, 240, 240));
    armPiPalette.setColor(QPalette::ToolTipText, QColor(0, 0, 0));
    armPiPalette.setColor(QPalette::Text, QColor(0, 0, 0));             // Text: Black
    armPiPalette.setColor(QPalette::Button, QColor(200, 200, 200));     // Button background: Grey
    armPiPalette.setColor(QPalette::ButtonText, QColor(0, 0, 0));       // Button text: Black
    armPiPalette.setColor(QPalette::BrightText, QColor(255, 0, 255));   // Important text: #FF00FF
    armPiPalette.setColor(QPalette::Link, QColor(0, 0, 255));           // Links: Blue
    armPiPalette.setColor(QPalette::Highlight, QColor(0, 0, 0));        // Selection: Black
    armPiPalette.setColor(QPalette::HighlightedText, QColor(255, 255, 255)); // Selected text: White
    app.setPalette(armPiPalette);
    
    MainWindow window;
    window.show();
    
    return app.exec();
}