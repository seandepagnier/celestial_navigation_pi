Celestial Navigation Plugin for OpenCPN
=======================================

automatically perform sight reductions, and plot position from celestial sights.

Source Repository: https://github.com/seandepagnier/celestial_navigation_pi
Maintainence Repository: https://github.com/rgleason/celestial_navigation_pi
Please make PR's to both repositories. Thank you.

Compiling
=========

* git clone git://github.com/seandepagnier/celestial_navigation_pi.git

Under windows, you must find the file "opencpn.lib" (Visual Studio) or "libopencpn.dll.a" (mingw) which is built in the build directory after compiling opencpn.  This file must be copied to the plugin directory.

Build as normally:

* cd ..
* cd build
* cmake ..
* make
* make install

License
=======
The plugin code is licensed under the terms of the GPL v3 or, at your will, later.
