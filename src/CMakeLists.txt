# Add the main core to use DE_Wrapper funcionality
add_subdirectory (CoreDE)

if (BUILD_CONSOLE_CPP)
  add_subdirectory (ConsoleCPP)
endif()
