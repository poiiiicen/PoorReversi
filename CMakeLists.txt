project(PoorReversi)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(cpr)

include_directories(${CPR_INCLUDE_DIRS})

add_executable(PoorReversi main.cpp MCT.cpp MCT.h node.h logic.cpp logic.h timer.h exceptions.h)

target_link_libraries(PoorReversi ${CPR_LIBRARIES})
