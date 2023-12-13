find_package(OpenCASCADE QUIET PATHS "${OpenCASCADE_DIR}" "${OpenCASCADE_INSTALL_PREFIX}" NO_DEFAULT_PATH)

if (NOT OpenCASCADE_FOUND)
  message (FATAL_ERROR "could not find OpenCASCADE, please set OpenCASCADE_DIR variable" )
else()
  set (OpenCASCADE_DIR "${OpenCASCADE_INSTALL_PREFIX}" CACHE PATH "OpenCASCADE directory" FORCE)
  message (STATUS "Using OpenCASCADE from \"${OpenCASCADE_DIR}\"" )
endif()
