# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
cmake_minimum_required (VERSION 3.10)

project ("DE_Wrapper")

include("${CMAKE_CURRENT_SOURCE_DIR}/adm/cmake/FindOCCT.cmake")
# Include sub-projects.
add_subdirectory ("src")

option(BUILD_CONSOLE_CPP "Build ConsoleCPP example" ON)

set(CMAKE_CXX_STANDARD 17) # Enable c++17 standard

install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/data/CONF" CONFIGURATIONS Debug DESTINATION "bind")
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/data/CONF" CONFIGURATIONS Release DESTINATION "bin")
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/data/CONF" CONFIGURATIONS RelWithDebInfo DESTINATION "bini")
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/data/CONF" CONFIGURATIONS MinSizeRel DESTINATION "bins")

install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/data/LIBS" CONFIGURATIONS Debug DESTINATION "bind")
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/data/LIBS" CONFIGURATIONS Release DESTINATION "bin")
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/data/LIBS" CONFIGURATIONS RelWithDebInfo DESTINATION "bini")
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/data/LIBS" CONFIGURATIONS MinSizeRel DESTINATION "bins")
