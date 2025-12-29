cmake_minimum_required(VERSION 3.28)
project(timber LANGUAGES CXX)

# -----------------------------
# Global build settings
# -----------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# -----------------------------
# SFML (FetchContent)
# -----------------------------
include(FetchContent)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.2
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM
)

FetchContent_MakeAvailable(SFML)

# -----------------------------
# Executable
# -----------------------------
add_executable(timber
        src/Main.cpp
        src/GameObject.cpp
        src/GameObject.hpp
        src/Cloud.cpp
        src/Cloud.hpp
        src/Bee.cpp
        src/Bee.hpp
        src/Random.hpp
        src/TextureManager.cpp
        src/TextureManager.hpp
)

target_link_libraries(timber
        PRIVATE
        SFML::Graphics
        SFML::Audio
)

# -----------------------------
# Asset directories
# -----------------------------
set(ASSET_DIRS
        graphics
        sounds
        fonts
)

foreach (dir IN LISTS ASSET_DIRS)
    add_custom_command(
            TARGET timber POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/${dir}
            $<TARGET_FILE_DIR:timber>/${dir}
    )
endforeach ()

