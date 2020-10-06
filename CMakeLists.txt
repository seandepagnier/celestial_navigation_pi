##---------------------------------------------------------------------------
## Author:      Sean D'Epagnier
## Copyright:   
## License:     GPLv3
##---------------------------------------------------------------------------
# Frontend2 Author: Jon Gough  
# Frontend2: v1.0.137.0
# ---------------------------------------------------------------------------
## ----- When changing this file do NOT change the order in which sections occur        ----- ##
## ----- Changes should only be made between the section blocks that identify where     ----- ##
## ----- these changes should be. The whole configuration process relies on this        ----- ##
## ----- sequence to be successful                                                      ----- ##
##  

##
##----- Modify section below to include all the details for your plugin ----- ##
##

set(CMLOC "CMakeLists: ")
# define minimum cmake version
cmake_minimum_required(VERSION 3.1.1)
if(COMMAND cmake_policy)
    if(POLICY CMP0043)
        cmake_policy(SET CMP0043 NEW)
    endif(POLICY CMP0043)
    cmake_policy(SET CMP0048 NEW)
    if(POLICY CMP0077)
        cmake_policy(SET CMP0077 NEW)
    endif(POLICY CMP0077)
endif(COMMAND cmake_policy)

set(VERBOSE_NAME "Celestial_Navigation")
set(COMMON_NAME "Celestial Navigation")  # Search "getcommonname"in <plugin_pi>.cpp
set(TITLE_NAME "CELESTIALNAVIGATION")
set(PACKAGE_CONTACT  "Sean D'Epagnier ")
set(PACKAGE "celestial_navigation")
set(SHORT_DESCRIPTION "Celestial Navigation Plugin for OpenCPN")
set(LONG_DESCRIPTION "Implements nautical almanac for sun, moon, planets and various navigational stars. Compute position fix from celestial measurements.")

set(VERSION_MAJOR "2")
set(VERSION_MINOR "3")
set(VERSION_PATCH "3")
set(VERSION_TWEAK "2")
set(VERSION_DATE "2020-10-06")
set(OCPN_MIN_VERSION "ov52")
set(OCPN_API_VERSION_MAJOR "1")
set(OCPN_API_VERSION_MINOR "16")
set(TP_COMMENT "  * Release for O5 using CI")

set(PARENT "opencpn")

#Used to set up a local webserver with git loaded, for testing purposes.
# The default is shown below, but it is done in cmake/pluginconfigure.cmake now.
# This default is needed to build locally and to build flatpak.
#set(GIT_REPOSITORY_SERVER "github.com")

#No longer needed, queried.
#set(GIT_USER "rgleason")
#set(GIT_REPOSITORY_NAME "celestial_navigation_pi")

# Specifies Cloudsmith upload repository suffix for each catalog
set(PROD "prod") # Standard Repos
set(BETA "beta") # Standard Repos
set(ALPHA "alpha") # Standard Repos

#set(CLOUDSMITH_USER "jon-gough")
#set(CLOUDSMITH_USER "rick-gleason")
set(CLOUDSMITH_USER "opencpn")

# Set if yourCloudsmith Base Repository name does not match your Git Repository name.
# set(CLOUDSMITH_BASE_REPOSITORY "celestial_navigation_pi")
# set(CLOUDSMITH_BASE_REPOSITORY "opencpn-plugins") #Rick's customization
set (CLOUDSMITH_BASE_REPOSITORY "celestial-navigation")  #without the pi 

set(XML_INFO_URL "https://opencpn.org/OpenCPN/plugins/celestialnav.html")
set(XML_SUMMARY ${SHORT_DESCRIPTION})
set(XML_DESCRIPTION ${LONG_DESCRIPTION})

##
## ----- Modify section above to include all the details for your plugin ----- ##
## ----- Modify section below if there are special requirements for the plugin ----- ##
##

option(PLUGIN_USE_SVG "Use SVG graphics" ON)

set(CMAKE_CXX_STANDARD 11)

# Prefer libGL.so to libOpenGL.so, see CMP0072
set(OpenGL_GL_PREFERENCE "LEGACY")

# Don't use local version of GLU library
set(USE_LOCAL_GLU FALSE)

option(USE_GL "Enable OpenGL support" ON)
message(STATUS "${CMLOC}USE_GL: ${USE_GL}")

if("${CMAKE_BUILD_TYPE}" STREQUAL "")
    set(CMAKE_BUILD_TYPE
        "Release"
        CACHE STRING "Choose the type of build" FORCE)
endif("${CMAKE_BUILD_TYPE}" STREQUAL "")
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "" "Debug" "Release" "RelWithDebInfo" "MinSizeRel")
message(STATUS "${CMLOC}Build type: ${CMAKE_BUILD_TYPE}")

##
## ----- The statements below are used to setup standard variables that are required by the CMAKE process - do not remove ----- ##
##

project(${PACKAGE})
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake;")

##==================================
include("PluginSetup")
##==================================
##
## ----- The above is used to setup standard variables that are required by the CMAKE process - do not remove ----- ##
## ----- Modify section below if there are special requirements for the plugin ----- ##
##
set(CMAKE_VERBOSE_MAKEFILE ON)

option(Plugin_CXX11 "Use c++11" OFF)

#--- For Weatherfax insert Portaudio Section here  

##
## ----- Modify section above if there are special requirements for the plugin ----- ##
## ----- do not change next section - needed to configure build process ----- ##
##
##==================================
include("PluginConfigure")
##==================================
##
## ----- do not change section above - needed to configure build process ----- ##
# ----- Change below to match project requirements for source, headers, etc. ----- ##
# 

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
          api-16/ocpn_plugin.h		  
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
		
		api-16/ocpn_plugin.h
	)	

#added for android
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

		
IF(WIN32)
SET(SRC_TINYXML
            src/tinyxml/tinyxml.cpp
            src/tinyxml/tinyxmlparser.cpp
            src/tinyxml/tinyxmlerror.cpp
)
ENDIF(WIN32)

set(EXTINCLUDE extinclude/nlohmann/json.hpp extinclude/ODAPI.h)

set(LIBSSRC libs/wxJSON/src/jsonreader.cpp libs/wxJSON/src/jsonval.cpp libs/wxJSON/src/jsonwriter.cpp)
											if(APPLE)
    option(PI_JSON_SCHEMA_VALIDATOR "Use JSON Schema validator" OFF)
else(APPLE)
    option(PI_JSON_SCHEMA_VALIDATOR "Use JSON Schema validator" ON)
endif(APPLE)

if(PI_JSON_SCHEMA_VALIDATOR)
    message(STATUS "${CMLOC}Using JSON Schema validation - warning this changes the 'flavour' of the executable and it may not be compatible with OpenCPN")
    add_definitions(-DPI_JSON_SCHEMA_VALIDATOR)
    message(STATUS "${CMLOC}Adding JSON Schema validation")

    set(EXTSRC ${EXTSRC} extsrc/json-schema-validator/json-schema-draft7.json.cpp extsrc/json-schema-validator/json-uri.cpp extsrc/json-schema-validator/json-validator.cpp)
    set(EXTINCLUDE ${EXTINCLUDE} extinclude/nlohmann/json.hpp extinclude/json-schema-validator/json-schema.hpp)
    include_directories(BEFORE ${PROJECT_SOURCE_DIR}/extinclude/json-schema-validator)
else(PI_JSON_SCHEMA_VALIDATOR)
    message(STATUS "${CMLOC}Not using JSON Schema validation - warning invalid JSON 'may' cause unexpected crashes")
endif(PI_JSON_SCHEMA_VALIDATOR)

##
# Modify/configure 'Include' Directories below for the Plugin
##

include_directories(BEFORE ${PROJECT_SOURCE_DIR}/ocpninclude)
include_directories(BEFORE ${PROJECT_SOURCE_DIR}/extinclude)
#include_directories(BEFORE ${PROJECT_SOURCE_DIR}/libs/)
#include_directories(BEFORE ${PROJECT_SOURCE_DIR}/libs/wx/include)
#include_directories(BEFORE ${PROJECT_SOURCE_DIR}/ocpninclude/wxcurl)
#include_directories(BEFORE ${PROJECT_SOURCE_DIR}/ocpninclude/wxcurl/include)
#include_directories(BEFORE ${PROJECT_SOURCE_DIR}/ocpnsrc/lz4)
#include_directories(BEFORE ${PROJECT_SOURCE_DIR}/ocpnsrc/bitmaps)

include_directories(BEFORE ${PROJECT_SOURCE_DIR}/src)  #nor so sure this is needed, trying to fix cnav.
include_directories(BEFORE ${PROJECT_SOURCE_DIR}/src/astrolabe)
include_directories(BEFORE ${PROJECT_SOURCE_DIR}/src/geomag)
include_directories(BEFORE ${PROJECT_SOURCE_DIR}/src/tinyxml)
include_directories(BEFORE ${PROJECT_SOURCE_DIR}/api-16)
include_directories(BEFORE ${PROJECT_SOURCE_DIR}/libs)
include_directories(BEFORE ${PROJECT_SOURCE_DIR}/libs/GL)

##
## Statement below is required to collect all the set( headers and SRCS  - Adjust as required
## This add_library  can be used in conditionals below.
##
##    SET(EXTSRC  ${EXTSRC}   etc   Can be in an if statement as below
##
##==================================
ADD_LIBRARY(${PACKAGE_NAME} SHARED ${SRCS} ${HDRS} ${LIBHDRS} ${SRC_TINYXML})
##==================================

ADD_DEFINITIONS(-DTIXML_USE_STL)

#needed only if glshim project is included.
if(QT_ANDROID)
  target_link_libraries(${PACKAGE_NAME}  GL_static)
endif(QT_ANDROID)  


# Every plugin that uses JSON for passing messages should use a validator. The validator  allows the system to ignore non-conformant messages. 

if(UNIX AND NOT APPLE AND NOT QT_ANDROID)
    if(PI_JSON_SCHEMA_VALIDATOR)
        # Change OS/ABI to be UNIX - System V to make it run with OCPN
        set(lib_name lib${PACKAGE_NAME}.so)
        message(STATUS "${CMLOC}lib-name: ${lib_name}")
        find_file(elfedit elfedit)
        if(NOT (${elfedit} STREQUAL "elfedit-NOTFOUND"))
            message(STATUS "${CMLOC}Will ensure OS/ABI is set to 0 to match OCPN")
            add_custom_command(
                TARGET ${PACKAGE_NAME}
                POST_BUILD
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                DEPENDS ${PACKAGE_NAME}
                COMMENT " Running post build action on ${lib_name}."
                COMMAND sh -c 'elfedit --input-osabi=Linux --output-osabi=none ${lib_name} || (echo 0) ')
        else(NOT (${elfedit} STREQUAL "elfedit-NOTFOUND"))
            message(STATUS "${CMLOC}Cannot correct OS/ABI to match OCPN if it is generated incorrectly. Package binutils needed")
        endif(NOT (${elfedit} STREQUAL "elfedit-NOTFOUND"))
    endif(PI_JSON_SCHEMA_VALIDATOR)
endif(UNIX AND NOT APPLE AND NOT QT_ANDROID)

##These are NOT used in Testplugin, used for other plugins
##==================================
#include("PluginJSON")
#include("PluginXML")
#include("PluginGL")
##==================================

##
## ----- Change above to match project requirements ----- ##
## ----- do not change next section - needed to configure build process ----- ##
##
##==================================
include("PluginInstall")
include("PluginLocalization")
include("PluginPackage")
##==================================
##
## ----- do not change section above - needed to configure build process ----- ##
##
