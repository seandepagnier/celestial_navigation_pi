##---------------------------------------------------------------------------
## Author:      Sean D'Epagnier
## Copyright:   
## License:     GPLv3
##---------------------------------------------------------------------------
 

# define minimum cmake version
CMAKE_MINIMUM_REQUIRED(VERSION 2.6.2)

PROJECT(celestial_navigation_pi)

SET(PACKAGE_NAME celestial_navigation_pi)
SET(VERBOSE_NAME CelestialNavigation)
SET(TITLE_NAME CELESTIALNAVIGATION)
SET(CPACK_PACKAGE_CONTACT "Sean D'Epagnier ")

MESSAGE (STATUS "*** Building ${PACKAGE_NAME} ***")

INCLUDE("cmake/PluginConfigure.cmake")

SET(SRC_CELESTIAL_NAVIGATION
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
          src/zuFile.cpp
	)

INCLUDE("cmake/PluginXML.cmake")
INCLUDE("cmake/PluginGL.cmake")

ADD_LIBRARY(${PACKAGE_NAME} SHARED ${SRC_CELESTIAL_NAVIGATION} ${SRC_TINYXML} ${SRC_PLUGINGL})

INCLUDE("cmake/PluginInstall.cmake")
INCLUDE("cmake/PluginLocalization.cmake")
INCLUDE("cmake/PluginPackage.cmake")
