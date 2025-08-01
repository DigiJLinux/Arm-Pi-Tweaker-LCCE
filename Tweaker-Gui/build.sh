#!/bin/bash

echo "Building Arm-Pi Tweaker C++ Standalone Application..."

# Check if Qt5 development packages are installed
echo "Checking Qt5 development packages..."
if ! dpkg -l | grep -q qt5-default 2>/dev/null && ! dpkg -l | grep -q qtbase5-dev; then
    echo "Installing Qt5 development packages..."
    sudo apt update
    sudo apt install -y qtbase5-dev qtbase5-dev-tools cmake build-essential
    if [ $? -ne 0 ]; then
        echo "❌ Failed to install Qt5 development packages!"
        exit 1
    fi
fi

# Create build directory
mkdir -p build
cd build

# Configure with CMake
echo "Configuring with CMake..."
cmake ..

# Build the application
echo "Building application..."
make -j$(nproc)

if [ $? -eq 0 ]; then
    echo "✅ Build successful!"
    echo "Executable location: $(pwd)/bin/arm-pi-tweaker"
    echo ""
    echo "To run the application:"
    echo "  cd $(pwd)"
    echo "  ./bin/arm-pi-tweaker"
else
    echo "❌ Build failed!"
    exit 1
fi