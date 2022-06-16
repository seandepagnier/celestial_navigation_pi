##---------------------------------------------------------------------------
## Author:      Sean D'Epagnier
## Copyright:   
## License:     GPLv3
##---------------------------------------------------------------------------
# Frontend2  TP 1.0.212.1  15/06/2022  Author: Jon Gough  
# ---------------------------------------------------------------------------

## ----- When changing this file do NOT change the order in which sections occur        ----- ##
## ----- Changes should only be made between the section blocks that identify where     ----- ##
## ----- these changes should be. The whole configuration process relies on this        ----- ##
## ----- sequence to be successful                                                      ----- ##
##

##
## ----- Modify section below to include all the details for your plugin ----- ##
##

set(CMLOC "CMakeLists: ")

# define minimum cmake version
cmake_minimum_required(VERSION 3.5.1)
if(COMMAND cmake_policy)
    if(POLICY CMP0043)
        cmake_policy(SET CMP0043 NEW)
    endif(POLICY CMP0043)
    cmake_policy(SET CMP0048 NEW)
# Need cmake 3.13 to implement this, but raspbian builds are at 3.7.2 and bionic at 3.10 and xenial builds at 3.5.1
#    cmake_policy(SET CMP0076 NEW)
    if(POLICY CMP0077)
        cmake_policy(SET CMP0077 NEW)
    endif(POLICY CMP0077)
endif(COMMAND cmake_policy)

# define plugin name, owner and versions
set(VERBOSE_NAME Celestial_Navigation)
set(COMMON_NAME "Celestial Navigation")  
set(TITLE_NAME "CELESTIALNAVIGATION")
set(PACKAGE_CONTACT  "Sean D'Epagnier ")
set(PACKAGE "celestial_navigation")
set(SHORT_DESCRIPTION "Celestial Navigation Plugin for OpenCPN")
set(LONG_DESCRIPTION "Nautical almanac: sun, moon, planets and navigational stars. Compute position fix from celestial measurements.")

set(VERSION_MAJOR "2")
set(VERSION_MINOR "3")
set(VERSION_PATCH "14")
set(VERSION_TWEAK "0")
set(VERSION_DATE "16/05/2022")  # DD/MM/YYYY format
set(OCPN_MIN_VERSION "ov52")
set(OCPN_API_VERSION_MAJOR "1")
set(OCPN_API_VERSION_MINOR "16")
set(TP_COMMENT "  * Release for O5 using CI")

set(PARENT "opencpn")

# The next line allows for setting up your own local webserver with git on it for testing purposes, the default is github.com
# This line is turned on in pluginconfigure.cmake because the flatpak build and building locally depends on it.
# set(GIT_REPOSITORY_SERVER "github.com")

# Specifies Cloudsmith upload repository suffix
set(PROD "prod") # Standard Repos
set(BETA "beta") # Standard Repos
set(ALPHA "alpha") # Standard Repos

# Set if yourCloudsmith Base Repository name does not match your Git Repository name.
#set(CLOUDSMITH_BASE_REPOSITORY "${GIT_REPOSITORY_NAME}")
set (CLOUDSMITH_BASE_REPOSITORY "celestial-navigation")  #without the pi 

# Set the following to use OpenCPN cloudsmith repositories instead of own repositories
set(CLOUDSMITH_USER "opencpn")
#set(CLOUDSMITH_USER "rick-gleason")

# Set Plugin info-url, summary and description
set(XML_INFO_URL "https://opencpn.org/OpenCPN/plugins/celestialnav.html")
set(XML_SUMMARY ${SHORT_DESCRIPTION})
set(XML_DESCRIPTION ${LONG_DESCRIPTION})

##
## ----- Modify section above to include all the details for your plugin ----- ##
## ----- Modify section below if there are special requirements for the plugin ----- ##
##

option(PLUGIN_USE_SVG "Use SVG graphics" ON)

set(CMAKE_CXX_STANDARD 11)

# Use local version of GLU library requires libs/glu directory
#set(USE_LOCAL_GLU TRUE)
# Don't use local version of GLU library
set(USE_LOCAL_GLU FALSE)
# Prefer libGL.so to libOpenGL.so, see CMP0072
set(OpenGL_GL_PREFERENCE "LEGACY")

option(USE_GL "Enable OpenGL support" ON)
message(STATUS "${CMLOC}USE_GL: ${USE_GL}")

if("${CMAKE_BUILD_TYPE}" STREQUAL "")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build" FORCE)
endif("${CMAKE_BUILD_TYPE}" STREQUAL "")
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "" "Debug" "Release" "RelWithDebInfo" "MinSizeRel")
message(STATUS "${CMLOC}Build type: ${CMAKE_BUILD_TYPE}")

##
## ----- The statements below are used to setup standard variables that are required by the CMAKE process - do not remove ----- ##
##

project(${PACKAGE})
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

##==================================
include("PluginSetup")
##==================================
## ----- The above is used to setup standard variables that are required by the CMAKE process - do not remove ----- ##
## ----- Modify section below if there are special requirements for the plugin ----- ##
##

set(CMAKE_VERBOSE_MAKEFILE "Activate verbose mode for make files" ON)

option(Plugin_CXX11 "Use c++11" OFF)

##
## ----- Modify section above if there are special requirements for the plugin ----- ##
## ----- do not change next section - needed to configure build process ----- ##
##==================================
include("PluginConfigure")
##==================================
## ----- do not change section above - needed to configure build process ----- ##
# ----- Change below to match project requirements for source, headers, etc. ----- ##
# 

add_definitions(-DUSE_S57)

SET(SRCS
          src/astrolabe/astrolabe.hpp
          src/astrolabe/calendar.cpp
          src/astrolabe/dicts.cpp
          src/astrolabe/dynamical.cpp
          src/astrolabe/elp2000.cpp
          src/astrolabe/equinox.cpp
          src/astrolabe/globals.cpp
          src/astrolabe/nutation.cpp
          src/astrolabe/riseset.cpp
          src/astrolabe/sun.cpp
          src/astrolabe/util.cpp
          src/astrolabe/vsop87d.cpp
          src/geomag/geomag.c
    	  src/CelestialNavigationDialog.cpp
    	  src/CelestialNavigationUI.cpp
          src/SightDialog.cpp
          src/Sight.cpp
          src/icons.cpp
          src/FindBodyDialog.cpp
          src/FixDialog.cpp
          src/ClockCorrectionDialog.cpp
          src/geodesic.c
          src/transform_star.cpp
          src/epv00.cpp
          src/celestial_navigation_pi.cpp
	)

SET(HDRS
        src/celestial_navigation_pi.h
        src/CelestialNavigationDialog.h
        src/CelestialNavigationUI.h
        src/ClockCorrectionDialog.h
        src/FindBodyDialog.h
		src/FixDialog.h
		src/geodesic.h
		src/icons.h
		src/Sight.h
		src/SightDialog.h
        libs/ocpn-api/ocpn_plugin.h
		
  	)	
#set(LIBSSRC libs/wxJSON/src/jsonreader.cpp libs/wxJSON/src/jsonval.cpp libs/wxJSON/src/jsonwriter.cpp)

# Added for android
set(LIBHDRS
    libs/GL/gl.h
    libs/GL/gl_private.h
    libs/GL/glext.h
    libs/GL/glu.h
#    libs/wx/include/wx/json_defs.h
#    libs/wx/include/wx/jsonreader.h
#    libs/wx/include/wx/jsonval.h
#    libs/wx/include/wx/jsonwriter.h
	)

add_definitions(-DPLUGIN_USE_SVG)

set(EXTINCLUDE_DIR ${EXTINCLUDE_DIR} extinclude libs/ocpn-api/)

#
# ----- If using JSON validation in plugin section below is needed ----- ##
#

# Not doing JSON validation

#
# ----- If using JSON validation in plugin section above is needed ----- ##
#

##
# Modify/configure 'Include' Directories below for the Plugin
##

include_directories(BEFORE ${PROJECT_SOURCE_DIR}/include)
include_directories(BEFORE ${PROJECT_SOURCE_DIR}/ocpninclude)
include_directories(BEFORE ${PROJECT_SOURCE_DIR}/${EXTINCLUDE_DIR})
include_directories(BEFORE ${PROJECT_SOURCE_DIR}/src/astrolabe)
include_directories(BEFORE ${PROJECT_SOURCE_DIR}/src/geomag)
include_directories(BEFORE ${PROJECT_SOURCE_DIR}/libs)
include_directories(BEFORE ${PROJECT_SOURCE_DIR}/libs/tinyxml)
include_directories(BEFORE ${PROJECT_SOURCE_DIR}/libs/bzip2)
include_directories(BEFORE ${PROJECT_SOURCE_DIR}/libs/GL)
include_directories(BEFORE ${PROJECT_SOURCE_DIR}/libs/ocpn-api)
include_directories(BEFORE ${PROJECT_SOURCE_DIR}/libs/wxJSON/include)

#
# ----- Change below to match project requirements for android build ----- ##
#

if(QT_ANDROID)
    include_directories( ${PROJECT_SOURCE_DIR}/extinclude/GLES2)
endif(QT_ANDROID)

##
## ----- Change above to match project requirements for android build ----- ##
##

## Statement below is required to collect all the set( headers and SRCS  - Adjust as required
##==================================
target_sources(${PACKAGE_NAME} PUBLIC ${SRCS} ${HDRS} ${LIBHDRS} ${OCPNSRC} ${EXTSRC} ${LIBSSRC})
##==================================


IF(PLUGIN_USE_SVG)
  ADD_DEFINITIONS(-DCELESTIAL_NAVIGATION_USE_SVG)
ENDIF(PLUGIN_USE_SVG)

if(NOT OCPN_FLATPAK_CONFIG)
    # Build environment not available when flatpak is being configured so following statements will not work
    message(STATUS "${CMLOC}Adding target link libraries to ${PACKAGE_NAME}")

    add_subdirectory(libs/tinyxml)

    target_link_libraries(${PACKAGE_NAME} ocpn::tinyxml)
   
    add_subdirectory(libs/bzip2)
    target_link_libraries(${PACKAGE_NAME} ocpn::bzip2)   
      
endif(NOT OCPN_FLATPAK_CONFIG)

add_definitions(-DTIXML_USE_STL)

#
# ----- If using JSON validation in plugin section below is needed ----- ##
#

# Not doing JSON Validator

#
# ----- If using JSON validation in plugin section above is needed ----- ##
#

##
## ----- Change above to match project requirements ----- ##
## ----- do not change next section - needed to configure build process ----- ##
##
##==================================
# Needed for android builds
if(QT_ANDROID)
    include_directories(BEFORE ${qt_android_include})
endif(QT_ANDROID)

# Needed for all builds
include("PluginInstall")
include("PluginLocalization")
include("PluginPackage")
##==================================

##
## ----- do not change section above - needed to configure build process ----- ##
##
message(STATUS "${CMLOC}include directories: ")
get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
    message(STATUS "${CMLOC}dir='${dir}'")
endforeach()
