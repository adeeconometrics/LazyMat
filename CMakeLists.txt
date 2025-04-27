cmake_minimum_required(VERSION 3.16.3)
project(LazyMat
    VERSION 0.0.1
    DESCRIPTION "Generic Lazy Matrix"
    LANGUAGES CXX
)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Find OpenMP and configure it if available
find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    message(STATUS "OpenMP found. Version: ${OpenMP_CXX_VERSION}")
    set(HAVE_OPENMP TRUE)
    add_compile_definitions(HAVE_OPENMP)
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    # Set the target architecture to arm64
    set(CMAKE_OSX_ARCHITECTURES "arm64")
    message("macOS detected " ${CMAKE_OSX_ARCHITECTURES})

    # Set compiler flags for macOS
    set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -Wextra -pedantic -Xclang -pthread -DDEBUG")
    set(CMAKE_CXX_FLAGS_RELEASE " -O3 -Wall -Wextra -pedantic -Xclang -pthread")
else()
    # Set compiler flags for other systems
    set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -Wextra -pedantic -pthread -DDEBUG")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -Wextra -pedantic -pthread -ffast-math -march=native -ftree-vectorize")
endif()

# Add source and include directories
file(GLOB_RECURSE SRC_FILES src/*.cpp)
file(GLOB_RECURSE INC_FILES include/*.hpp)

add_executable(${PROJECT_NAME} ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

# Add library target
add_library(standard_lib INTERFACE)
target_include_directories(standard_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Link OpenMP if available
if(OpenMP_CXX_FOUND)
    target_link_libraries(${PROJECT_NAME} PUBLIC OpenMP::OpenMP_CXX)
endif()

foreach(file ${INC_FILES})
    list(APPEND SOURCE_FILES
        ${PROJECT_INCLUDE_DIR}/${file}
    )
endforeach()

# message(${INC_FILES})
# message(${SOURCE_FILES})

# add_library(${PROJECT_NAME} ${INC_FILES})

# set_target_properties(LazMatLib PROPERTIES LINKER_LANGUAGE CXX)

# Add GoogleTest
add_subdirectory(lib/googletest)

# Add test directory
enable_testing()

# Add tests directory with array_test target
add_subdirectory(test)


# Package configuration
set(CPACK_PACKAGE_NAME "lazymat")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${PROJECT_DESCRIPTION}")
set(CPACK_PACKAGE_VENDOR "LazyMat")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "LazyMat")

# Add component-based installation
set(CPACK_COMPONENTS_ALL libraries headers documentation)
set(CPACK_COMPONENT_LIBRARIES_DISPLAY_NAME "LazyMat Libraries")
set(CPACK_COMPONENT_HEADERS_DISPLAY_NAME "C++ Headers")
set(CPACK_COMPONENT_DOCUMENTATION_DISPLAY_NAME "Documentation")

# Installation configuration
install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION bin COMPONENT libraries
        LIBRARY DESTINATION lib COMPONENT libraries
        ARCHIVE DESTINATION lib COMPONENT libraries)

install(DIRECTORY include/
        DESTINATION include/lazymat
        COMPONENT headers
        FILES_MATCHING PATTERN "*.hpp")

# Install documentation if Doxygen is found
if(DOXYGEN_FOUND)
    install(DIRECTORY ${CMAKE_BINARY_DIR}/docs/
            DESTINATION share/doc/lazymat
            COMPONENT documentation)
endif()

# Generator specific configuration
if(WIN32)
    set(CPACK_GENERATOR "NSIS;ZIP")
    set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)
    set(CPACK_NSIS_PACKAGE_NAME "LazyMat ${PROJECT_VERSION}")
elseif(APPLE)
    set(CPACK_GENERATOR "DragNDrop;TGZ")
else()
    set(CPACK_GENERATOR "TGZ;DEB")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "LazyMat Team")
    set(CPACK_DEBIAN_PACKAGE_DEPENDS "libomp-dev")
endif()

# VCPKG configuration
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg.json")
    set(VCPKG_MANIFEST_MODE ON)
    set(VCPKG_MANIFEST_INSTALL ON)
endif()

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

include(CMakePackageConfigHelpers)

# Generate version file
write_basic_package_version_file(
    "${CMAKE_BINARY_DIR}/LazyMatConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

# Configure config file
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/LazyMatConfig.cmake.in"
    "${CMAKE_BINARY_DIR}/LazyMatConfig.cmake"
    INSTALL_DESTINATION lib/cmake/LazyMat
)

# Install config files
install(FILES
    "${CMAKE_BINARY_DIR}/LazyMatConfig.cmake"
    "${CMAKE_BINARY_DIR}/LazyMatConfigVersion.cmake"
    DESTINATION lib/cmake/LazyMat
)
