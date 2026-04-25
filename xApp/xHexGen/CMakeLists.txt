# CMake Version
cmake_minimum_required(VERSION 3.28)

# Variable
set(APP_PROJECT_NAME      "xHexGen")
set(APP_PROJECT_VER       "1.0.6")
set(APP_PROJECT_LANGUAGE  "C")

# Prjoect Name
project(${APP_PROJECT_NAME}                   # Project Name
        VERSION ${APP_PROJECT_VER}            # Project Version
        LANGUAGES ${APP_PROJECT_LANGUAGE})    # Project Language

# CFLAG
add_compile_options(-std=c99 -Wall -Wextra -O3)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Executable
add_executable(${APP_PROJECT_NAME} xHexGen.c)

# Include Path
target_include_directories(xHexGen PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/../.."
)

# Executable Output
# CMAKE_CURRENT_SOURCE_DIR: Source Code Path
set_target_properties(xHexGen PROPERTIES
  OUTPUT_NAME              "${APP_PROJECT_NAME}"            # Output Name
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"    # Output Path
)
