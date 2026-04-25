#!/bin/bash

# Project : xHexGen Build
# Author  : William Hsiao
# Descript: Auto Build xHexGen and Execute or Clean

# Variable Declare
APP_NAME="xHexGen"
BUILD_DIR="Build"

# Clean
if [ "$1" == "clean" ]; then
  # Remove Build Folder
  if [ -d "$BUILD_DIR" ]; then
    rm -rf "$BUILD_DIR"
    echo -e "Removed ${BUILD_DIR}/"
  fi

  # Remove Executable
  if [[ "$OSTYPE" == "msys" || "$OSTYPE" == "cygwin" ]]; then
    rm -f ${APP_NAME}.exe
  else
    find . -maxdepth 1 -type f -name "${APP_NAME}" ! -name "*.c" ! -name "*.h" ! -name "*.sh" -delete
  fi
  exit 0
fi


# Create Build Folder
if [ ! -d "$BUILD_DIR" ]; then
  mkdir "$BUILD_DIR"
fi

# Enter Build Folder
cd "$BUILD_DIR" || exit
cmake ..

# Check CMake is Success
if [ $? -ne 0 ]; then
  echo -e "CMake Configuration Failed!"
  exit 1
fi

# build
make -j$(nproc 2>/dev/null || echo 1)

# Check Build Result
if [ $? -eq 0 ]; then
  echo -e "Build Successful!"
else
  echo -e "Build Failed!"
  exit 1
fi