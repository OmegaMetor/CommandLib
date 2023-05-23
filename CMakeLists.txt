cmake_minimum_required(VERSION 3.0.0)
project(CommandLib VERSION 0.1.0)

include_directories(include)
add_library(CommandLib 
    src/CommandScheduler.cpp
    src/Command.cpp
    src/Trigger.cpp
    src/EventLoop.cpp
)

add_custom_target(buildDocs
    COMMAND doxygen Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM)

add_executable(CommandLibTest test/CommandLib.cpp)
target_link_libraries(CommandLibTest CommandLib)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
