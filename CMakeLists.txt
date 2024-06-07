cmake_minimum_required(VERSION 3.16.3)
project(LazyMat
    VERSION 0.0.1
    DESCRIPTION "Generic Lazy Matrix"
    LANGUAGES CXX
)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Set output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Find OpenMP
# find_package(OpenMP REQUIRED)
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    # Set the target architecture to arm64
    set(CMAKE_OSX_ARCHITECTURES "arm64")
    message("macOS detected " ${CMAKE_OSX_ARCHITECTURES})

    # Set compiler flags for macOS
    set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -Wextra -pedantic -Xclang -pthread")
    set(CMAKE_CXX_FLAGS_RELEASE " -O3 -Wall -Wextra -pedantic -Xclang -pthread")
else()
    # Set compiler flags for other systems
    set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -Wextra -pedantic -pthread")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -Wextra -pedantic -pthread -ffast-math -march=native -ftree-vectorize")
endif()

# Add source and include directories
file(GLOB_RECURSE SRC_FILES src/*.cpp)
file(GLOB_RECURSE INC_FILES include/*.hpp)

add_executable(${PROJECT_NAME} ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

# Link OpenMP
# if(OpenMP_CXX_FOUND)
# target_link_libraries(${PROJECT_NAME} PUBLIC OpenMP::OpenMP_CXX)
# endif()
foreach(file ${INC_FILES})
    list(APPEND SOURCE_FILES
        ${PROJECT_INCLUDE_DIR}/${file}
    )
endforeach()

# message(${INC_FILES})
# message(${SOURCE_FILES})

# add_library(${PROJECT_NAME} ${INC_FILES})

# set_target_properties(LazMatLib PROPERTIES LINKER_LANGUAGE CXX)

# Fetch GTest library
set(CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib/googletest)
find_package(GTest REQUIRED CONFIG)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

if(WIN32)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif()

# Add test directory
enable_testing()

add_executable(unittest ${CMAKE_CURRENT_SOURCE_DIR}/test/unittest.cpp)
target_link_libraries(unittest PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(unittest)

# Specify the packaging information
set(CPACK_PACKAGE_NAME "lazymat")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_GENERATOR "ZIP")
include(CPack)

# Doxygen

# look for Doxygen package
find_package(Doxygen)

if(DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs_doxy/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.out)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # Note: do not put "ALL" - this builds docs together with application EVERY TIME!
    add_custom_target(docs
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)
else(DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate the doxygen documentation")
endif(DOXYGEN_FOUND)
