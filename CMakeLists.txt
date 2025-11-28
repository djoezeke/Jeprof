# ===================================================================
# Copyright © 2025 Sackey Ezekiel Etrue
# Distributed under the terms of the MIT license.
# ===================================================================

cmake_minimum_required(VERSION 3.16...4.1.1 FATAL_ERROR)

#--------------------------------------------------------------------
# Project and version.
#--------------------------------------------------------------------

set (JEPROF_VERSION_STRING "0.1.0")

project(Jeprof
        VERSION ${JEPROF_VERSION_STRING} 
        DESCRIPTION "C/C++ Profiling Library"
        HOMEPAGE_URL "https://github.com/djoezeke/jeprof"
        LANGUAGES  C CXX
)

#--------------------------------------------------------------------
# Preparations depending on the specified build options  
#--------------------------------------------------------------------

# Check if this project is the main project
if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  set(JEPROF_IS_TOP_LEVEL ON)
else()
  set(JEPROF_IS_TOP_LEVEL OFF)
endif()

#--------------------------------------------------------------------
# Configure variables for the library   
#--------------------------------------------------------------------

set(JEPROF_LIB_NAME "jeprof" CACHE STRING "Base name of library output name")
set(JEPROF_TARGET_NAME  ${JEPROF_LIB_NAME})

option(JEPROF_BUILD_EXAMPLES "Build the ${PROJECT_NAME} example applications" ${JEPROF_IS_TOP_LEVEL})
option(JEPROF_BUILD_TESTS "Build the ${PROJECT_NAME} test programs" ${JEPROF_IS_TOP_LEVEL})
option(JEPROF_BUILD_DOCS "Build the ${PROJECT_NAME} documentation" ${JEPROF_IS_TOP_LEVEL})
option(JEPROF_INSTALL "Generate installation target" ${JEPROF_IS_TOP_LEVEL})

# Tooling options
option(JEPROF_ENABLE_CLANG_TIDY "Enable clang-tidy on targets" ${JEPROF_IS_TOP_LEVEL})
option(JEPROF_ENABLE_CLANG_FORMAT "Add clang-format target" ${JEPROF_IS_TOP_LEVEL})

# Set required C standard
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

# Set required C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(JEPROF_CMAKE_CONFIG_NAME "${PROJECT_NAME}Config")
set(JEPROF_CMAKE_TARGET_NAME "${PROJECT_NAME}Target")

set(JEPROF_INCLUDE_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(JEPROF_INCLUDE_INSTALL_DIR "${CMAKE_INSTALL_INCLUDEDIR}")
set(JEPROF_CONFIG_INSTALL_DIR "${CMAKE_INSTALL_DATADIR}/cmake/${PROJECT_NAME}" CACHE INTERNAL "Install directory path for config files.")

set(JEPROF_CMAKE_CONFIG_TEMPLATE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(JEPROF_CMAKE_CONFIG_TEMPLATE "${JEPROF_CMAKE_CONFIG_TEMPLATE_DIR}/${JEPROF_CMAKE_CONFIG_NAME}.cmake.in")
set(JEPROF_CMAKE_VERSION_CONFIG_TEMPLATE "${JEPROF_CMAKE_CONFIG_TEMPLATE_DIR}/${JEPROF_CMAKE_CONFIG_NAME}Version.cmake.in")
set(JEPROF_CMAKE_PACKAGE_CONFIG_TEMPLATE "${JEPROF_CMAKE_CONFIG_TEMPLATE_DIR}/pkg-config.pc.in")

set(JEPROF_CMAKE_CONFIG_DIR  ${CMAKE_CURRENT_BINARY_DIR})
set(JEPROF_CMAKE_CONFIG_FILE  ${JEPROF_CMAKE_CONFIG_DIR}/${PROJECT_NAME}Config.cmake)
set(JEPROF_CMAKE_TARGETS_FILE  ${JEPROF_CMAKE_CONFIG_DIR}/${PROJECT_NAME}Targets.cmake)
set(JEPROF_CMAKE_PACKAGE_FILE  ${JEPROF_CMAKE_CONFIG_DIR}/${PROJECT_NAME}.pc)
set(JEPROF_CMAKE_VERSION_CONFIG_FILE  ${JEPROF_CMAKE_CONFIG_DIR}/${PROJECT_NAME}ConfigVersion.cmake)

#--------------------------------------------------------------------
# Build library targets
#--------------------------------------------------------------------

add_library(${JEPROF_LIB_NAME} INTERFACE)
add_library(Jeprof::Jeprof ALIAS ${JEPROF_LIB_NAME})

target_compile_definitions(${JEPROF_LIB_NAME} INTERFACE cxx_std_11)

target_include_directories(${JEPROF_LIB_NAME} 
    INTERFACE 
        $<BUILD_INTERFACE:${JEPROF_INCLUDE_BUILD_DIR}>
        $<BUILD_INTERFACE:${JEPROF_INCLUDE_BUILD_DIR}>
        $<INSTALL_INTERFACE:${JEPROF_INCLUDE_INSTALL_DIR}>
)

#--------------------------------------------------------------------
# Configurations
#--------------------------------------------------------------------

# Default to build type "Release" unless tests are being built
if(NOT CMAKE_BUILD_TYPE)
	if (NOT JEPROF_BUILD_TESTS)
		message(STATUS "No build type selected, default to Release")
		set(CMAKE_BUILD_TYPE "Release")
	else()
		message(STATUS "No build type selected but tests are being built, default to Debug")
		set(CMAKE_BUILD_TYPE "Debug")
	endif()
endif()

# Output directories for a build tree
if(NOT DEFINED CMAKE_RUNTIME_OUTPUT_DIRECTORY)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
    # set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
endif()

#--------------------------------------------------------------------
# Add Project subdirectories
#--------------------------------------------------------------------

# Build the documentation   
if(JEPROF_BUILD_DOCS)
    add_subdirectory(docs)
endif()

# Build the example apps   
if(JEPROF_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# Build the test apps   
if(JEPROF_BUILD_TESTS)
    include(CTest)
    enable_testing()
    add_subdirectory(tests)

    # Set the unit test app project as the Visual Studio startup project
    # if the target compiler is some version of Microsoft Visual C++ and
    # if this project is the main project.
    if(MSVC AND CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
        set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT JeprofUnitTest)
    endif()
endif()

#--------------------------------------------------------------------
# Integrate with tools.
#--------------------------------------------------------------------

# Optional: enable clang-tidy integration
if(JEPROF_ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY_EXE NAMES clang-tidy)
    if(CLANG_TIDY_EXE)
        add_custom_target(clang-tidy
            COMMAND ${CLANG_TIDY_EXE} --config-file=.clang-tidy ${JEPROF_SOURCES} ${JEPROF_INCLUDE_BUILD_DIR}/*
            COMMENT "Tidy project sources with clang-tidy"
        )
    else()
        message(WARNING "clang-tidy requested but not found on PATH")
    endif()
endif()

# Optional: clang-format target to format sources
if(JEPROF_ENABLE_CLANG_FORMAT)
    find_program(CLANG_FORMAT_EXE NAMES clang-format)
    if(CLANG_FORMAT_EXE)
        add_custom_target(clang-format
            COMMAND ${CLANG_FORMAT_EXE} -i --style=file ${JEPROF_SOURCES} ${JEPROF_INCLUDE_BUILD_DIR}/*
            COMMENT "Format project sources with clang-format"
        )
    else()
        message(WARNING "clang-format requested but not found on PATH")
    endif()
endif()

#--------------------------------------------------------------------
# Install a pkg-config file
#--------------------------------------------------------------------

# we use the paths from the cmake GNUInstallDirs module as defaults
# you can override these if you like
# https://cmake.org/cmake/help/latest/module/GNUInstallDirs.html
include(GNUInstallDirs)

#--------------------------------------------------------------------
# Configure package.
#--------------------------------------------------------------------
include(CMakePackageConfigHelpers)

configure_file(
    ${JEPROF_CMAKE_CONFIG_TEMPLATE}
    ${JEPROF_CMAKE_CONFIG_FILE}
    @ONLY
)

configure_file(
    ${JEPROF_CMAKE_VERSION_CONFIG_TEMPLATE}
    ${JEPROF_CMAKE_VERSION_CONFIG_FILE}
    @ONLY
)

configure_file(
    "${JEPROF_CMAKE_PACKAGE_CONFIG_TEMPLATE}"
    "${JEPROF_CMAKE_PACKAGE_FILE}"
)

#--------------------------------------------------------------------
# Install package.
#--------------------------------------------------------------------
if(JEPROF_INSTALL)
    install(
        DIRECTORY ${JEPROF_INCLUDE_BUILD_DIR}
        DESTINATION ${JEPROF_INCLUDE_INSTALL_DIR}
    )

    install(
        FILES ${JEPROF_CMAKE_CONFIG_FILE} ${JEPROF_CMAKE_VERSION_CONFIG_FILE}
        DESTINATION ${JEPROF_CONFIG_INSTALL_DIR}
    )

    export(
        TARGETS ${JEPROF_TARGET_NAME}
        NAMESPACE ${PROJECT_NAME}::
        FILE ${JEPROF_CMAKE_TARGETS_FILE}
    )

    install(
        TARGETS ${JEPROF_TARGET_NAME}
        EXPORT ${JEPROF_CMAKE_TARGET_NAME}
    )

    install(
        EXPORT ${JEPROF_CMAKE_TARGET_NAME}
        NAMESPACE ${PROJECT_NAME}::
        DESTINATION ${JEPROF_CONFIG_INSTALL_DIR}
    )

    install(
        FILES "${JEPROF_CMAKE_PACKAGE_FILE}"
        DESTINATION ${JEPROF_CONFIG_INSTALL_DIR}
    )

endif()

install(FILES LICENSE DESTINATION ${CMAKE_INSTALL_DOCDIR})
install(FILES README.md DESTINATION ${CMAKE_INSTALL_DOCDIR})

#--------------------------------------------------------------------
# Package with CPack.
#--------------------------------------------------------------------
# TODO : Add Packing with CPack

#--------------------------------------------------------------------
# Uninstall Files
#--------------------------------------------------------------------
# TODO : Add Uninstall Target
