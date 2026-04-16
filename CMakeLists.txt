cmake_minimum_required(VERSION 3.10)
project(CineCache)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/engine)

set(SOURCES
    src/main.cpp
    engine/utils.cpp
    engine/ui.cpp
)

# Create executable
add_executable(cinecache ${SOURCES})

# Output directory
set_target_properties(cinecache PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

message(STATUS "CineCache - Distributed Movie Cache CLI")
message(STATUS "|- Consistent Hashing Ring  (src/hashing/)")
message(STATUS "|- LRU Cache per node       (src/cache/)")
message(STATUS "|- Custom Hash Table + DLL  (src/data_structures/)")
message(STATUS "|- Simulated DB             (src/database/)")
message(STATUS "|- Load Simulator & Scaling (src/scaling/)")


