# Set CMake minimum version and CMake policy required by Urho3D-CMake-common module
if (WIN32)
    cmake_minimum_required (VERSION 3.2.3)      # Going forward all platforms will use this as minimum version
else ()
    cmake_minimum_required (VERSION 2.8.6)
endif ()
if (COMMAND cmake_policy)
    cmake_policy (SET CMP0003 NEW)
    if (CMAKE_VERSION VERSION_GREATER 2.8.12 OR CMAKE_VERSION VERSION_EQUAL 2.8.12)
        # INTERFACE_LINK_LIBRARIES defines the link interface
        cmake_policy (SET CMP0022 NEW)
    endif ()
    if (CMAKE_VERSION VERSION_GREATER 3.0.0 OR CMAKE_VERSION VERSION_EQUAL 3.0.0)
        # Disallow use of the LOCATION target property - so we set to OLD as we still need it
        cmake_policy (SET CMP0026 OLD)
        # MACOSX_RPATH is enabled by default
        cmake_policy (SET CMP0042 NEW)
    endif ()
endif ()
# Set project name
project (AirFighter)
# Set CMake modules search path
set (CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake/Modules)
# Set the Urho3d_home enviroment
set (ENV{URHO3D_HOME} E:/!Package/Urho3D-Build)
# Include Urho3D Cmake common module
include (Urho3D-CMake-common)
# Define target name
set (TARGET_NAME AirFighter)
# Define source files
define_source_files ()
# Setup target with resource copying
setup_main_executable ()