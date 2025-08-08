cmake_minimum_required(VERSION 3.16)
project(gnuski VERSION 0.3.0 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Find ncurses
find_package(PkgConfig REQUIRED)
pkg_check_modules(NCURSES REQUIRED ncurses)

# Set default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Compiler flags
set(CMAKE_C_FLAGS_DEBUG "-g -Wall -Wextra")
set(CMAKE_C_FLAGS_RELEASE "-O2 -DNDEBUG")

# Source files
set(SOURCES
    src/main.c
    src/objects.c
)

# Create executable
add_executable(gnuski ${SOURCES})

# Link libraries
target_link_libraries(gnuski ${NCURSES_LIBRARIES})
target_include_directories(gnuski PRIVATE ${NCURSES_INCLUDE_DIRS})
target_compile_options(gnuski PRIVATE ${NCURSES_CFLAGS_OTHER})

# Installation
install(TARGETS gnuski
    RUNTIME DESTINATION bin
)

# CPack configuration for packaging
set(CPACK_PACKAGE_NAME "gnuski")
set(CPACK_PACKAGE_VENDOR "Rudolf Olah")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "GNUSki - an open source clone of Skifree")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_PACKAGE_INSTALL_DIRECTORY "gnuski")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")

# Platform-specific packaging
if(APPLE)
    set(CPACK_GENERATOR "DragNDrop")
    set(CPACK_DMG_FORMAT "UDBZ")
    set(CPACK_DMG_VOLUME_NAME "GNUSki")
elseif(UNIX)
    set(CPACK_GENERATOR "TGZ;DEB")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Rudolf Olah")
    set(CPACK_DEBIAN_PACKAGE_DEPENDS "libncurses6")
    set(CPACK_DEBIAN_PACKAGE_SECTION "games")
endif()

include(CPack)
