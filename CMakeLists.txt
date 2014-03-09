##---------------------------------------------------------------------------
## Author:      Sean D'Epagnier
## Copyright:   
## License:     GPLv3
##---------------------------------------------------------------------------
 

# define minimum cmake version
CMAKE_MINIMUM_REQUIRED(VERSION 2.6.2)

PROJECT(celestial_navigation_pi)
SET(PACKAGE_NAME celestial_navigation_pi)
SET(CPACK_PACKAGE_CONTACT "Sean D'Epagnier ")

SET(VERSION_MAJOR "1")
SET(VERSION_MINOR "8")

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
          src/geodesic.c
          src/celestial_navigation_pi.cpp

          src/tinyxml/tinyxml.cpp
          src/tinyxml/tinystr.cpp
          src/tinyxml/tinyxmlparser.cpp
          src/tinyxml/tinyxmlerror.cpp
	)

ADD_LIBRARY(${PACKAGE_NAME} SHARED ${SRC_CELESTIAL_NAVIGATION})

INCLUDE("cmake/PluginInstall.cmake")
INCLUDE("cmake/PluginLocalization.cmake")
INCLUDE("cmake/PluginPackage.cmake")
