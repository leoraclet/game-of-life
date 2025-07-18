cmake_minimum_required(VERSION 3.31)
project(game-of-life)

# C++ compile flags
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++11")
endif()

# Directories
set(IMGUI_SRC_DIR libs/imgui)
set(LIB_SDL_PATH libs/SDL)
set(LIB_DIR libs)
set(INCLUDE_DIR includes)
set(SRC_DIR src)

# Load SDL
find_package(
    SDL2 PATHS ${LIB_SDL_PATH}
)

# Load source and header files
set(SOURCES
    ${SRC_DIR}/main.cpp
)
set(HEADERS
)

# Load ImGUI src files
set(
    IMGUI_LIB_SRC
    ${IMGUI_SRC_DIR}/imgui.cpp
    ${IMGUI_SRC_DIR}/imgui_draw.cpp
    ${IMGUI_SRC_DIR}/imgui_tables.cpp
    ${IMGUI_SRC_DIR}/imgui_widgets.cpp
    ${IMGUI_SRC_DIR}/imgui_impl_sdl.cpp
    ${IMGUI_SRC_DIR}/imgui_impl_sdlrenderer.cpp
)

# Include directories
include_directories(
    ${LIB_DIR}
    ${INCLUDE_DIR}
)

# Executable
add_executable(
    ${CMAKE_PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
    ${IMGUI_LIB_SRC}
)

# Include directory to target
target_include_directories(
    ${CMAKE_PROJECT_NAME} PRIVATE
    ${IMGUI_SRC_DIR}
)

# Link libraries to target
target_link_libraries(
    ${CMAKE_PROJECT_NAME} PRIVATE SDL2
)
