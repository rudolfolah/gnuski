#!/bin/bash

# Package script for GNUSki
# Creates distribution packages for Linux and macOS

set -e

BUILD_DIR="build"
PACKAGE_DIR="packages"

# Ensure we have a built binary
if [ ! -f "$BUILD_DIR/gnuski" ]; then
    echo "No built binary found. Running build first..."
    ./build.sh
fi

# Clean previous packages
if [ -d "$PACKAGE_DIR" ]; then
    rm -rf "$PACKAGE_DIR"
fi

mkdir -p "$PACKAGE_DIR"
cd "$BUILD_DIR"

echo "Creating packages..."

# Create packages using CPack
cpack

# Move packages to package directory
mv *.tar.gz *.deb *.dmg "../$PACKAGE_DIR/" 2>/dev/null || true

cd ..

echo "Packaging completed!"
echo "Packages available in: $PACKAGE_DIR/"
ls -la "$PACKAGE_DIR/"
