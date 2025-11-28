# ===================================================================
# Copyright © 2025 Sackey Ezekiel Etrue
# Distributed under the terms of the MIT license.
# ===================================================================

#--------------------------------------------------------------------
# Basic Tests Configures   
#--------------------------------------------------------------------

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug)
endif()


include_directories("." "../" "include/")

#--------------------------------------------------------------------
# Test Functions
#--------------------------------------------------------------------

# add a new target which is a test
# example: jeprof_add_example(main-examples main.example.cpp "")
function(jeprof_add_test target SOURCES DEPENDS)

    # set a source group for the source files
    source_group("" FILES ${SOURCES})

    # create the target
    add_executable(${target} ${SOURCES})

    # set the target's folder (for IDEs that support it, e.g. Visual Studio)
    set_target_properties(${target} PROPERTIES FOLDER "Tests")

    # set the Visual Studio startup path for debugging
    set_target_properties(${target} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

    # link the target to its dependencies
    target_link_libraries(${target} PRIVATE ${DEPENDS} Jeprof::Jeprof)

    # Enable support for UTF-8 characters in source code
    if(MSVC)
        target_compile_options(${target} PRIVATE /utf-8)
    endif()
endfunction()


#--------------------------------------------------------------------
# Manually or Recursively add Tests
#--------------------------------------------------------------------

# Automatically add all .c tests in the src folder
file(GLOB C_TEST_SOURCES "src/*.c")
foreach(TEST_FILE ${C_TEST_SOURCES})
  	get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
  	jeprof_add_test("${TEST_NAME}" "${TEST_FILE}" "")
endforeach()

# Automatically add all .cpp tests in the src folder
file(GLOB CPP_TEST_SOURCES "src/*.cpp")
foreach(TEST_FILE ${CPP_TEST_SOURCES})
  	get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
  	jeprof_add_test("${TEST_NAME}" "${TEST_FILE}" "")
endforeach()

# TODO: Add Convenience for building and running tests in a single command
