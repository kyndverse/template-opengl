cmake_minimum_required(VERSION 3.25)

project(OpenGLProject
    VERSION 1.0
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

# ============================================================
# GLFW
# ============================================================

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.5.1
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(glfw)


# ============================================================
# GLAD 2
# ============================================================

FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG v2.0.8
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(glad)

add_subdirectory(
    ${glad_SOURCE_DIR}/cmake
    glad_cmake
)

glad_add_library(
    glad_gl_core_46
    STATIC
    API gl:core=4.6
)

# ============================================================
# GLM
# ============================================================

FetchContent_Declare(
	glm
	GIT_REPOSITORY	https://github.com/g-truc/glm.git
	GIT_TAG 1.0.3
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(glm)

# ============================================================
# Application
# ============================================================

add_executable(OpenGLProject
    src/main.cpp
    src/ShaderManager.cpp
)


# ============================================================
# Include directories
# ============================================================

target_include_directories(OpenGLProject
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}
)


# ============================================================
# Libraries
# ============================================================

target_link_libraries(OpenGLProject
    PRIVATE
        glfw
        glad_gl_core_46
        glm::glm
)