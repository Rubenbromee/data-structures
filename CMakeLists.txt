cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(YourProjectName VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the output directory for the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Collect all source files
file(GLOB_RECURSE SOURCES "src/*")

# Add the executable
add_executable(YourExecutableName ${SOURCES})

# Custom target for building and running
add_custom_target(run
    COMMAND YourExecutableName
    DEPENDS YourExecutableName
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)

# Include directories
target_include_directories(YourExecutableName PRIVATE src)