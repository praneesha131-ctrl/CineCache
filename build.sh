#!/bin/bash

# CineCache Build Script - Supports macOS, Linux, Windows

echo "=========================================="
echo "  CineCache Build Script"
echo "=========================================="

OS_TYPE="UNKNOWN"
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    OS_TYPE="LINUX"
elif [[ "$OSTYPE" == "darwin"* ]]; then
    OS_TYPE="MAC"
elif [[ "$OSTYPE" == "msys" || "$OSTYPE" == "cygwin" || "$OSTYPE" == "win32" ]]; then
    OS_TYPE="WINDOWS"
fi

echo "[*] Detected OS: $OS_TYPE"

echo "[*] Checking for cmake..."
if ! command -v cmake &> /dev/null; then
    echo "    [!] cmake not found. Installing..."
    if [ "$OS_TYPE" = "MAC" ]; then
        echo "    [*] Installing cmake via brew..."
        if ! command -v brew &> /dev/null; then
            echo "    [!] Homebrew not found. Installing first..."
            /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
        fi
        brew install cmake
    elif [ "$OS_TYPE" = "LINUX" ]; then
        echo "    [*] Installing cmake via apt-get..."
        sudo apt-get update
        sudo apt-get install -y cmake
    elif [ "$OS_TYPE" = "WINDOWS" ]; then
        echo "    [!] Please install cmake manually from: https://cmake.org/download/"
        exit 1
    fi
else
    CMAKE_VERSION=$(cmake --version | head -n1)
    echo "    [✓] $CMAKE_VERSION"
fi

if [ "$OS_TYPE" != "WINDOWS" ]; then
    echo "[*] Checking for make..."
    if ! command -v make &> /dev/null; then
        echo "    [!] make not found. Installing..."
        if [ "$OS_TYPE" = "MAC" ]; then
            echo "    [*] Installing make via brew..."
            brew install make
        elif [ "$OS_TYPE" = "LINUX" ]; then
            echo "    [*] Installing build-essential..."
            sudo apt-get install -y build-essential
        fi
    else
        echo "    [✓] make found"
    fi
fi

echo "[*] Setting up build directory..."
if [ ! -d "build" ]; then
    echo "    [+] Creating build/"
    mkdir -p build
else
    echo "    [✓] build/ exists"
fi

echo "[*] Building project..."
cd build
echo "    [+] Running cmake..."
cmake ..
if [ $? -ne 0 ]; then
    echo "    [!] cmake failed!"
    exit 1
fi

echo "    [+] Running make..."
make
if [ $? -ne 0 ]; then
    echo "    [!] make failed!"
    exit 1
fi

echo "=========================================="
echo "  [✓] Build successful!"
echo "=========================================="
echo "  Starting CineCache..."

./bin/cinecache
x