#!/bin/bash

# Build script for GNUSki
# Supports Linux and macOS cross-platform compilation

set -e

BUILD_DIR="build"
BUILD_TYPE="${BUILD_TYPE:-Release}"

# Clean previous build
if [ -d "$BUILD_DIR" ]; then
    rm -rf "$BUILD_DIR"
fi

# Create build directory
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

# Configure with CMake
cmake .. -DCMAKE_BUILD_TYPE="$BUILD_TYPE"

# Build
cmake --build . --config "$BUILD_TYPE"

echo "Build completed successfully!"
echo "Executable: $BUILD_DIR/gnuski"

# Test the build
if [ -f "./gnuski" ]; then
    echo "Testing executable..."
    file ./gnuski
    ldd ./gnuski 2>/dev/null || otool -L ./gnuski 2>/dev/null || true
fi
