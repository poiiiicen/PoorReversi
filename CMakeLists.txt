project(PoorReversi)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(cpr)

include_directories(${CPR_INCLUDE_DIRS})

add_executable(PoorReversi main.cpp)

target_link_libraries(PoorReversi ${CPR_LIBRARIES})