The wizard # Arm-Pi Tweaker C++ Standalone Application

This is the C++ Qt version of the Arm-Pi Tweaker standalone application, converted from the original Rust/Iced implementation.

## Features

- **Ubuntu Upgrade Mode**: Upgrade from Ubuntu 22.04 to 24.10 while preserving Orange Pi 5+ specific drivers and kernel
- **Driver Extraction**: Extract Orange Pi 5+ drivers and kernel from upgrade images
- **System Patching**: Apply Orange Pi specific files to upgraded systems
- **Backup & Rollback**: Automatic backup creation and rollback functionality
- **Modern Qt GUI**: Clean, dark-themed interface with progress tracking

## Requirements

- Qt5 (Core, Widgets)
- CMake 3.16+
- C++17 compiler (GCC/Clang)
- Linux system (designed for Orange Pi 5+)

## Building

### Install Dependencies (Ubuntu/Debian)
```bash
sudo apt update
sudo apt install qtbase5-dev qtbase5-dev-tools cmake build-essential
```

### Build the Application
```bash
cd cpp_standalone
./build.sh
```

Or manually:
```bash
mkdir build && cd build
cmake ..
make -j$(nproc)
```

## Running

After building:
```bash
cd build
./bin/armpi-tweaker-cpp
```

## Application Structure

### Core Components

- **MainWindow**: Main application window with menu bar and tab management
- **UpgradeWidget**: Ubuntu upgrade interface with step-by-step process
- **SystemManager**: Backend system operations manager

### Key Features

1. **Step-by-Step Upgrade Process**:
   - Extract Orange Pi 5+ drivers and kernel files
   - Run standard Ubuntu distribution upgrade
   - Patch upgraded system with Orange Pi support
   - Automatic backup creation before patching

2. **Safety Features**:
   - Prerequisite checking (root access, mount points)
   - Automatic backup before system modifications
   - Rollback functionality to restore previous state
   - Progress tracking and detailed logging

3. **User Interface**:
   - Dark theme optimized for system administration
   - Real-time progress tracking
   - Detailed operation logging
   - Warning notifications for critical operations

## Usage

### Ubuntu Upgrade Process

1. **Prerequisites**: Ensure upgrade.img is mounted or upgrade files are available
2. **Extract Drivers**: Click "🔧 Extract Drivers & Kernel" to copy Orange Pi files
3. **Run Upgrade**: Click "🚀 Start Ubuntu Upgrade" to upgrade to 24.10
4. **Patch System**: Click "🛠️ Patch Upgraded System" to apply Orange Pi support
5. **Reboot**: Restart system to complete the upgrade

### Safety & Recovery

- **Automatic Backup**: System files are backed up before patching
- **Rollback**: Use "⚠️ Rollback Changes" if issues occur
- **Status Monitoring**: Check the Status Log tab for detailed operation logs

## File Locations

- **Upgrade Files**: `/home/snake/Arm-Pi-Tweaker/upgrade/`
- **Backup Files**: `/home/snake/Arm-Pi-Tweaker/backup_YYYYMMDD_HHMMSS/`
- **Application Logs**: Available in the Status Log tab

## Differences from Rust Version

This C++ version provides:
- Native Qt widgets instead of Iced framework
- Better integration with system themes
- More responsive UI during long operations
- Enhanced signal/slot architecture for better event handling
- Improved error handling and user feedback

## Development

### Adding New Features

1. Add UI components in the appropriate widget classes
2. Implement backend functionality in SystemManager
3. Connect signals and slots in MainWindow
4. Update CMakeLists.txt if adding new source files

### Testing

The application includes built-in safety checks and simulation modes for testing without affecting the actual system.

## License

MIT License - See main project LICENSE file.

## Support

This tool is specifically designed for Orange Pi 5 Plus with RK3588S chip. Using it on other hardware may cause issues.

For issues and feature requests, please use the main project repository.