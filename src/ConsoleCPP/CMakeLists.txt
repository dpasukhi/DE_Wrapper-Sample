get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId})

file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/FILES" SOURCE REGEX ".*\\.cxx")
file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/FILES" HEADER REGEX ".*\\.hxx")
file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/FILES" P_HEADER REGEX ".*\\.pxx")

add_executable(${ProjectId})

cmake_policy(SET CMP0076 NEW)
target_sources(${ProjectId} PRIVATE ${SOURCE} PUBLIC ${HEADER} PRIVATE ${P_HEADER})

set_target_properties(${ProjectId} PROPERTIES LINKER_LANGUAGE CXX)

file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/EXTERNLIB" EXTERNLIB)
list(REMOVE_DUPLICATES EXTERNLIB)

target_link_libraries (${ProjectId} ${EXTERNLIB})

# Specify the installation directory
install(TARGETS ${ProjectId} CONFIGURATIONS Debug DESTINATION "bind")
install(TARGETS ${ProjectId} CONFIGURATIONS Release DESTINATION "bin")
install(TARGETS ${ProjectId} CONFIGURATIONS RelWithDebInfo DESTINATION "bini")
install(TARGETS ${ProjectId} CONFIGURATIONS MinSizeRel DESTINATION "bins")
