# ARNL, SONARNL and MOGS - MobileRobots Research and Academic Customer Support

  

# ARNL, SONARNL and MOGS

ARNL is a set of software packages built on top of ARIA for intelligent
navigation and localization. "Localization" allows the program to keep track
of where the robot is and "navigation" allows the robot to get to a given
destination. The libraries run and coordinates these two tasks, with the
localization task automatically correcting robot pose, and the navigation task
driving the robot to a goal you specify either in your control program via the
programming interface, or from a remote control client such as
[MobileEyes](http://robots.mobilerobots.com/wiki/MobileEyes "MobileEyes") via
the ArNetworking protocol.

The libraries provide a native C++ API, as well as Python and Java APIs
through a wrapper interface layers. The packages include the shared
libraries/DLLs, header files, API reference manuals, and example programs with
source code.

Three seperate localization techniques are available, implemented in three
separate libraries:

  

  * Laser Localization -- **ARNL** \-- uses a [laser rangefinder](http://robots.mobilerobots.com/wiki/Laser_rangefinder "Laser rangefinder") and [map](http://robots.mobilerobots.com/wiki/Map "Map") to perform precise localization 
  * Sonar Localization -- **SONARNL** \-- uses the built in [sonar](http://robots.mobilerobots.com/wiki/Sonar "Sonar") sensors for approximate localization 
  * GPS Localization -- **MOGS** \-- uses a [GPS receiver](http://robots.mobilerobots.com/wiki/GPS_receiver "GPS receiver") to position the robot within a map 

Laser and GPS localization are only available to customers who have purchased
the laser mapping and navigation or outdoor navigation options. SONARNL sonar
localization is available to all customers.

In addition to the localization libraries, the **BaseArnl** library contains
the navigation component, base utilities used by the localization libraries,
and ARIA and ArNetworking are used by these libraries as well (the BaseArnl
installation package includes the ARIA and ArNetworking libraries required.)

  

  

  

## Contents

[hide]

  * [1 Download](http://robots.mobilerobots.com/wiki/ARNL,_SONARNL_and_MOGS#Download)
    * [1.1 Ubuntu 16.04 (xenial)](http://robots.mobilerobots.com/wiki/ARNL,_SONARNL_and_MOGS#Ubuntu_16.04_.28xenial.29)
    * [1.2 Ubuntu 12.04 (precise)](http://robots.mobilerobots.com/wiki/ARNL,_SONARNL_and_MOGS#Ubuntu_12.04_.28precise.29)
    * [1.3 Windows 32-bit](http://robots.mobilerobots.com/wiki/ARNL,_SONARNL_and_MOGS#Windows_32-bit)
    * [1.4 Windows 64-bit](http://robots.mobilerobots.com/wiki/ARNL,_SONARNL_and_MOGS#Windows_64-bit)
    * [1.5 Documentation](http://robots.mobilerobots.com/wiki/ARNL,_SONARNL_and_MOGS#Documentation)
    * [1.6 Previous Versions](http://robots.mobilerobots.com/wiki/ARNL,_SONARNL_and_MOGS#Previous_Versions)
  * [2 Recommended Additional Downloads](http://robots.mobilerobots.com/wiki/ARNL,_SONARNL_and_MOGS#Recommended_Additional_Downloads)

  
---  
  
##  Download

You must install BaseArnl (arnl-base, containing navigation and misc.
utilities) and then one or more of the ARNL (for accurate indoor laser
localization and docking), MOGS (GPS outdoor positioning) or SONARNL
(approximate indoor sonar localization) libraries.

  

###  Ubuntu 16.04 (xenial)

Built for **32-bit (i386) architecture** :

[ ![noteattachment1][6019a34a40e52e5b32b823ea17d1f2a2]  
](http://robots.mobilerobots.com/wiki/File:Download_icon_bw.png
"Image:Download_icon_bw.png") [Base ARNL Library 1.9.2 - Ubuntu 16.04 (xenial)
or later, 32-bit i386
architecture](http://robots.mobilerobots.com/BaseArnl/download/current/arnl-
base_1.9.2+ubuntu16_i386.deb
"http://robots.mobilerobots.com/BaseArnl/download/current/arnl-
base_1.9.2+ubuntu16_i386.deb") (arnl-base_1.9.2+ubuntu16_i386.deb)

  * Open file to install with Ubuntu Software Center, or use `dpkg -i`

[ ![noteattachment1][6019a34a40e52e5b32b823ea17d1f2a2]  
](http://robots.mobilerobots.com/wiki/File:Download_icon_bw.png
"Image:Download_icon_bw.png") [ARNL Laser Localization Library 1.9.2 - Ubuntu
16.04 (xenial) or later, 32-bit i386
architecture](http://robots.mobilerobots.com/ARNL/download/current/libarnl_1.9.2+ubuntu16_i386.deb
"http://robots.mobilerobots.com/ARNL/download/current/libarnl_1.9.2+ubuntu16_i386.deb")
(libarnl_1.9.2+ubuntu16_i386.deb)

  * Open file to install with Ubuntu Software Center, or use `dpkg -i`

[ ![noteattachment1][6019a34a40e52e5b32b823ea17d1f2a2]  
](http://robots.mobilerobots.com/wiki/File:Download_icon_bw.png
"Image:Download_icon_bw.png") [SONARNL Sonar Localization Library 1.9.2 -
Ubuntu 16.04 (xenial) or later, 32-bit i386
architecture](http://robots.mobilerobots.com/SONARNL/download/current/libsonarnl_1.9.2+ubuntu16_i386.deb
"http://robots.mobilerobots.com/SONARNL/download/current/libsonarnl_1.9.2+ubuntu16_i386.deb")
(libsonarnl_1.9.2+ubuntu16_i386.deb)

  * Open file to install with Ubuntu Software Center, or use `dpkg -i`

[ ![noteattachment1][6019a34a40e52e5b32b823ea17d1f2a2]  
](http://robots.mobilerobots.com/wiki/File:Download_icon_bw.png
"Image:Download_icon_bw.png") [MOGS GPS Localization Library 1.9.2 - Ubuntu
16.04 (xenial) or later, 32-bit i386
architecture](http://robots.mobilerobots.com/MOGS/download/current/libmogs_1.9.2+ubuntu16_i386.deb
"http://robots.mobilerobots.com/MOGS/download/current/libmogs_1.9.2+ubuntu16_i386.deb")
(libmogs_1.9.2+ubuntu16_i386.deb)

  * Open file to install with Ubuntu Software Center, or use `dpkg -i`

  
Built for **64-bit (amd64) architecture** :

[ ![noteattachment1][6019a34a40e52e5b32b823ea17d1f2a2]  
](http://robots.mobilerobots.com/wiki/File:Download_icon_bw.png
"Image:Download_icon_bw.png") [Base ARNL Library 1.9.2 - Ubuntu 16.04 (xenial)
or later, amd 64-bit
architecture](http://robots.mobilerobots.com/BaseArnl/download/current/arnl-
base_1.9.2+ubuntu16_amd64.deb
"http://robots.mobilerobots.com/BaseArnl/download/current/arnl-
base_1.9.2+ubuntu16_amd64.deb") (arnl-base_1.9.2+ubuntu16_amd64.deb)

  * Open file to install with Ubuntu Software Center or use `dpkg -i`

[ ![noteattachment1][6019a34a40e52e5b32b823ea17d1f2a2]  
](http://robots.mobilerobots.com/wiki/File:Download_icon_bw.png
"Image:Download_icon_bw.png") [ARNL Laser Localization Library 1.9.2 - Ubuntu
16.04 (xenial) or later, amd 64-bit
architecture](http://robots.mobilerobots.com/ARNL/download/current/libarnl_1.9.2+ubuntu16_amd64.deb
"http://robots.mobilerobots.com/ARNL/download/current/libarnl_1.9.2+ubuntu16_amd64.deb")
(libarnl_1.9.2+ubuntu16_amd64.deb)

  * Open file to install with Ubuntu Software Center or use `dpkg -i`

[ ![noteattachment1][6019a34a40e52e5b32b823ea17d1f2a2]  
](http://robots.mobilerobots.com/wiki/File:Download_icon_bw.png
"Image:Download_icon_bw.png") [SONARNL Sonar Localization Library 1.9.2 -
Ubuntu 16.04 (xenial) or later, amd 64-bit
architecture](http://robots.mobilerobots.com/SONARNL/download/current/libsonarnl_1.9.2+ubuntu16_amd64.deb
"http://robots.mobilerobots.com/SONARNL/download/current/libsonarnl_1.9.2+ubuntu16_amd64.deb")
(libsonarnl_1.9.2+ubuntu16_amd64.deb)

  * Open file to install with Ubuntu Software Center or use `dpkg -i`

[ ![noteattachment1][6019a34a40e52e5b32b823ea17d1f2a2]  
](http://robots.mobilerobots.com/wiki/File:Download_icon_bw.png
"Image:Download_icon_bw.png") [MOGS GPS Localization Library 1.9.2 - Ubuntu
16.04 (xenial) or later, amd 64-bit
architecture](http://robots.mobilerobots.com/MOGS/download/current/libmogs_1.9.2+ubuntu16_amd64.deb
"http://robots.mobilerobots.com/MOGS/download/current/libmogs_1.9.2+ubuntu16_amd64.deb")
(libmogs_1.9.2+ubuntu16_amd64.deb)

  * Open file to install with Ubuntu Software Center or use `dpkg -i`

  

  

###  Ubuntu 12.04 (precise)

Built for **32-bit (i386) architecture** :

These packages may be used on any version of Ubuntu, 12.04 (precise) or later
(32-bit/i386 architecture).

[ ![noteattachment1][6019a34a40e52e5b32b823ea17d1f2a2]  
](http://robots.mobilerobots.com/wiki/File:Download_icon_bw.png
"Image:Download_icon_bw.png") [Base ARNL Library 1.9.2 - Ubuntu 12.04.2
(precise) or later, 32-bit i386
architecture](http://robots.mobilerobots.com/BaseArnl/download/current/arnl-
base_1.9.2+ubuntu12_i386.deb
"http://robots.mobilerobots.com/BaseArnl/download/current/arnl-
base_1.9.2+ubuntu12_i386.deb") (arnl-base_1.9.2+ubuntu12_i386.deb)

  * Open file to install with Ubuntu Software Center, or use `dpkg -i`

[ ![noteattachment1][6019a34a40e52e5b32b823ea17d1f2a2]  
](http://robots.mobilerobots.com/wiki/File:Download_icon_bw.png
"Image:Download_icon_bw.png") [ARNL Laser Localization Library 1.9.2 - Ubuntu
12.04.2 (precise) or later, 32-bit i386
architecture](http://robots.mobilerobots.com/ARNL/download/current/libarnl_1.9.2+ubuntu12_i386.deb
"http://robots.mobilerobots.com/ARNL/download/current/libarnl_1.9.2+ubuntu12_i386.deb")
(libarnl_1.9.2+ubuntu12_i386.deb)

  * Open file to install with Ubuntu Software Center, or use `dpkg -i`

[ ![noteattachment1][6019a34a40e52e5b32b823ea17d1f2a2]  
](http://robots.mobilerobots.com/wiki/File:Download_icon_bw.png
"Image:Download_icon_bw.png") [SONARNL Sonar Localization Library 1.9.2 -
Ubuntu 12.04.2 (precise) or later, 32-bit i386
architecture](http://robots.mobilerobots.com/SONARNL/download/current/libsonarnl_1.9.2+ubuntu12_i386.deb
"http://robots.mobilerobots.com/SONARNL/download/current/libsonarnl_1.9.2+ubuntu12_i386.deb")
(libsonarnl_1.9.2+ubuntu12_i386.deb)

  * Open file to install with Ubuntu Software Center, or use `dpkg -i`

[ ![noteattachment1][6019a34a40e52e5b32b823ea17d1f2a2]  
](http://robots.mobilerobots.com/wiki/File:Download_icon_bw.png
"Image:Download_icon_bw.png") [MOGS GPS Localization Library 1.9.2 - Ubuntu
12.04.2 (precise) or later, 32-bit i386
architecture](http://robots.mobilerobots.com/MOGS/download/current/libmogs_1.9.2+ubuntu12_i386.deb
"http://robots.mobilerobots.com/MOGS/download/current/libmogs_1.9.2+ubuntu12_i386.deb")
(libmogs_1.9.2+ubuntu12_i386.deb)

  * Open file to install with Ubuntu Software Center, or use `dpkg -i`

  
Built for **64-bit (amd64) architecture** :

These packages may be used on any version of Ubuntu, 12.04 (precise) or later
(64-bit/amd64 architecture).

[ ![noteattachment1][6019a34a40e52e5b32b823ea17d1f2a2]  
](http://robots.mobilerobots.com/wiki/File:Download_icon_bw.png
"Image:Download_icon_bw.png") [Base ARNL Library 1.9.2 - Ubuntu 12.04.2
(precise) or later, amd 64-bit
architecture](http://robots.mobilerobots.com/BaseArnl/download/current/arnl-
base_1.9.2+ubuntu12_amd64.deb
"http://robots.mobilerobots.com/BaseArnl/download/current/arnl-
base_1.9.2+ubuntu12_amd64.deb") (arnl-base_1.9.2+ubuntu12_amd64.deb)

  * Open file to install with Ubuntu Software Center or use `dpkg -i`

[ ![noteattachment1][6019a34a40e52e5b32b823ea17d1f2a2]  
](http://robots.mobilerobots.com/wiki/File:Download_icon_bw.png
"Image:Download_icon_bw.png") [ARNL Laser Localization Library 1.9.2 - Ubuntu
12.04.2 (precise) or later, amd 64-bit
architecture](http://robots.mobilerobots.com/ARNL/download/current/libarnl_1.9.2+ubuntu12_amd64.deb
"http://robots.mobilerobots.com/ARNL/download/current/libarnl_1.9.2+ubuntu12_amd64.deb")
(libarnl_1.9.2+ubuntu12_amd64.deb)

  * Open file to install with Ubuntu Software Center or use `dpkg -i`

[ ![noteattachment1][6019a34a40e52e5b32b823ea17d1f2a2]  
](http://robots.mobilerobots.com/wiki/File:Download_icon_bw.png
"Image:Download_icon_bw.png") [SONARNL Sonar Localization Library 1.9.2 -
Ubuntu 12.04.2 (precise) or later, amd 64-bit
architecture](http://robots.mobilerobots.com/SONARNL/download/current/libsonarnl_1.9.2+ubuntu12_amd64.deb
"http://robots.mobilerobots.com/SONARNL/download/current/libsonarnl_1.9.2+ubuntu12_amd64.deb")
(libsonarnl_1.9.2+ubuntu12_amd64.deb)

  * Open file to install with Ubuntu Software Center or use `dpkg -i`

[ ![noteattachment1][6019a34a40e52e5b32b823ea17d1f2a2]  
](http://robots.mobilerobots.com/wiki/File:Download_icon_bw.png
"Image:Download_icon_bw.png") [MOGS GPS Localization Library 1.9.2 - Ubuntu
12.04.2 (precise) or later, amd 64-bit
architecture](http://robots.mobilerobots.com/MOGS/download/current/libmogs_1.9.2+ubuntu12_amd64.deb
"http://robots.mobilerobots.com/MOGS/download/current/libmogs_1.9.2+ubuntu12_amd64.deb")
(libmogs_1.9.2+ubuntu12_amd64.deb)

  * Open file to install with Ubuntu Software Center or use `dpkg -i`

  

  

###  Windows 32-bit

[ ![noteattachment1][6019a34a40e52e5b32b823ea17d1f2a2]  
](http://robots.mobilerobots.com/wiki/File:Download_icon_bw.png
"Image:Download_icon_bw.png") [Base ARNL Library 1.9.2-1 -
Windows](http://robots.mobilerobots.com/BaseArnl/download/current/BaseArnl-1.9.2-1.exe
"http://robots.mobilerobots.com/BaseArnl/download/current/BaseArnl-1.9.2-1.exe")
(BaseArnl-1.9.2-1.exe)

  * Run installer program as administrator account to install 

[ ![noteattachment1][6019a34a40e52e5b32b823ea17d1f2a2]  
](http://robots.mobilerobots.com/wiki/File:Download_icon_bw.png
"Image:Download_icon_bw.png") [ARNL Laser Localization Library 1.9.2-1 -
Windows](http://robots.mobilerobots.com/ARNL/download/current/ARNL-1.9.2-1.exe
"http://robots.mobilerobots.com/ARNL/download/current/ARNL-1.9.2-1.exe")
(ARNL-1.9.2-1.exe)

  * Run installer program as administrator account to install 

[ ![noteattachment1][6019a34a40e52e5b32b823ea17d1f2a2]  
](http://robots.mobilerobots.com/wiki/File:Download_icon_bw.png
"Image:Download_icon_bw.png") [SONARNL Sonar Localization Library 1.9.2-1 -
Windows](http://robots.mobilerobots.com/SONARNL/download/current/SONARNL-1.9.2-1.exe
"http://robots.mobilerobots.com/SONARNL/download/current/SONARNL-1.9.2-1.exe")
(SONARNL-1.9.2-1.exe)

  * Run installer program as administrator account to install 

[ ![noteattachment1][6019a34a40e52e5b32b823ea17d1f2a2]  
](http://robots.mobilerobots.com/wiki/File:Download_icon_bw.png
"Image:Download_icon_bw.png") [MOGS GPS Localization Library 1.9.2-1 -
Windows](http://robots.mobilerobots.com/MOGS/download/current/MOGS-1.9.2-1.exe
"http://robots.mobilerobots.com/MOGS/download/current/MOGS-1.9.2-1.exe")
(MOGS-1.9.2-1.exe)

  * Run installer program as administrator account to install 

  

###  Windows 64-bit

[ ![noteattachment1][6019a34a40e52e5b32b823ea17d1f2a2]  
](http://robots.mobilerobots.com/wiki/File:Download_icon_bw.png
"Image:Download_icon_bw.png") [Base ARNL Library 1.9.2-1 - Windows
64-bit](http://robots.mobilerobots.com/BaseArnl/download/current/BaseArnl-1.9.2-1-x64.exe
"http://robots.mobilerobots.com/BaseArnl/download/current/BaseArnl-1.9.2-1-x64.exe")
(BaseArnl-1.9.2-1-x64.exe)

  * Run installer program as administrator account to install 

[ ![noteattachment1][6019a34a40e52e5b32b823ea17d1f2a2]  
](http://robots.mobilerobots.com/wiki/File:Download_icon_bw.png
"Image:Download_icon_bw.png") [ARNL Laser Localization Library 1.9.2-1 -
Windows
64-bit](http://robots.mobilerobots.com/ARNL/download/current/ARNL-1.9.2-1-x64.exe
"http://robots.mobilerobots.com/ARNL/download/current/ARNL-1.9.2-1-x64.exe")
(ARNL-1.9.2-1-x64.exe)

  * Run installer program as administrator account to install 

[ ![noteattachment1][6019a34a40e52e5b32b823ea17d1f2a2]  
](http://robots.mobilerobots.com/wiki/File:Download_icon_bw.png
"Image:Download_icon_bw.png") [SONARNL Sonar Localization Library 1.9.2-1 -
Windows
64-bit](http://robots.mobilerobots.com/SONARNL/download/current/SONARNL-1.9.2-1-x64.exe
"http://robots.mobilerobots.com/SONARNL/download/current/SONARNL-1.9.2-1-x64.exe")
(SONARNL-1.9.2-1-x64.exe)

  * Run installer program as administrator account to install 

[ ![noteattachment1][6019a34a40e52e5b32b823ea17d1f2a2]  
](http://robots.mobilerobots.com/wiki/File:Download_icon_bw.png
"Image:Download_icon_bw.png") [MOGS GPS Localization Library 1.9.2-1 - Windows
64-bit](http://robots.mobilerobots.com/MOGS/download/current/MOGS-1.9.2-1-x64.exe
"http://robots.mobilerobots.com/MOGS/download/current/MOGS-1.9.2-1-x64.exe")
(MOGS-1.9.2-1-x64.exe)

  * Run installer program as administrator account to install 

  

###  Documentation

  * [ ![noteattachment25][72ed9c2e52fb073419bd011cfd2a09ea]  
](http://robots.mobilerobots.com/wiki/File:Doc_icon_bw.png
"Image:Doc_icon_bw.png") [Change
History](http://robots.mobilerobots.com/BaseArnl/download/current/Changes.txt
"http://robots.mobilerobots.com/BaseArnl/download/current/Changes.txt") for
ARNL libraries

  * [ ![noteattachment25][72ed9c2e52fb073419bd011cfd2a09ea]  
](http://robots.mobilerobots.com/wiki/File:Doc_icon_bw.png
"Image:Doc_icon_bw.png") [Change
History](http://robots.mobilerobots.com/ARIA/download/current/Changes.txt
"http://robots.mobilerobots.com/ARIA/download/current/Changes.txt") for ARIA
2.9.1

  * [ ![noteattachment25][72ed9c2e52fb073419bd011cfd2a09ea]  
](http://robots.mobilerobots.com/wiki/File:Doc_icon_bw.png
"Image:Doc_icon_bw.png") [ARNL introductory "getting started"
guide](http://robots.mobilerobots.com/docs/all_docs/ARNL-introduction.pdf
"http://robots.mobilerobots.com/docs/all_docs/ARNL-introduction.pdf")

  * [ ![noteattachment25][72ed9c2e52fb073419bd011cfd2a09ea]  
](http://robots.mobilerobots.com/wiki/File:Doc_icon_bw.png
"Image:Doc_icon_bw.png") [SONARNL introductory "getting started"
guide](http://robots.mobilerobots.com/docs/all_docs/SONARNL-introduction.pdf
"http://robots.mobilerobots.com/docs/all_docs/SONARNL-introduction.pdf")

  * [ ![noteattachment29][9dfda1d392edac115bbc68d56e4cbfb4]  
](http://robots.mobilerobots.com/wiki/File:Documents_icon_bw.png
"Image:Documents_icon_bw.png") [BaseArnl 1.9.2 API Reference
Documentation](http://robots.mobilerobots.com/docs/api/ARNL/1.9.2/BaseArnl-
Reference/index.html
"http://robots.mobilerobots.com/docs/api/ARNL/1.9.2/BaseArnl-
Reference/index.html")

  * [ ![noteattachment29][9dfda1d392edac115bbc68d56e4cbfb4]  
](http://robots.mobilerobots.com/wiki/File:Documents_icon_bw.png
"Image:Documents_icon_bw.png") [ARNL 1.9.2 API Reference
Documentation](http://robots.mobilerobots.com/docs/api/ARNL/1.9.2/ARNL-
Reference/index.html "http://robots.mobilerobots.com/docs/api/ARNL/1.9.2/ARNL-
Reference/index.html")

  * [ ![noteattachment29][9dfda1d392edac115bbc68d56e4cbfb4]  
](http://robots.mobilerobots.com/wiki/File:Documents_icon_bw.png
"Image:Documents_icon_bw.png") [MOGS 1.9.2 API Reference
Documentation](http://robots.mobilerobots.com/docs/api/ARNL/1.9.2/MOGS-
Reference/index.html "http://robots.mobilerobots.com/docs/api/ARNL/1.9.2/MOGS-
Reference/index.html")

  * [ ![noteattachment29][9dfda1d392edac115bbc68d56e4cbfb4]  
](http://robots.mobilerobots.com/wiki/File:Documents_icon_bw.png
"Image:Documents_icon_bw.png") [SONARNL 1.9.2 API Reference
Documentation](http://robots.mobilerobots.com/docs/api/ARNL/1.9.2/SONARNL-
Reference/index.html
"http://robots.mobilerobots.com/docs/api/ARNL/1.9.2/SONARNL-
Reference/index.html")

  * [GPS receiver](http://robots.mobilerobots.com/wiki/GPS_receiver "GPS receiver") configuration and use 
  * [Laser Rangefinder](http://robots.mobilerobots.com/wiki/Laser_Rangefinder "Laser Rangefinder") configuration and use 
  * [Maps](http://robots.mobilerobots.com/wiki/Maps "Maps")
  * [Getting Started with MOGS](http://robots.mobilerobots.com/wiki/Getting_Started_with_MOGS "Getting Started with MOGS")

  

###  Previous Versions

Note, before version 1.7.0, only ARNL and SONARNL packages were released.

[ ![noteattachment33][d80cee00d5741dfcfd771ef89331a8dc]  
](http://robots.mobilerobots.com/wiki/File:Folder_icon_bw.png
"Image:Folder_icon_bw.png")[Archived versions of
ARNL](http://robots.mobilerobots.com/ARNL/download/archives/
"http://robots.mobilerobots.com/ARNL/download/archives/")

[ ![noteattachment33][d80cee00d5741dfcfd771ef89331a8dc]  
](http://robots.mobilerobots.com/wiki/File:Folder_icon_bw.png
"Image:Folder_icon_bw.png")[Archived versions of
SONARNL](http://robots.mobilerobots.com/SONARNL/download/archives/
"http://robots.mobilerobots.com/SONARNL/download/archives/")

[ ![noteattachment33][d80cee00d5741dfcfd771ef89331a8dc]  
](http://robots.mobilerobots.com/wiki/File:Folder_icon_bw.png
"Image:Folder_icon_bw.png")[Archived versions of
BaseArnl](http://robots.mobilerobots.com/BaseArnl/download/archives/
"http://robots.mobilerobots.com/BaseArnl/download/archives/")

[ ![noteattachment33][d80cee00d5741dfcfd771ef89331a8dc]  
](http://robots.mobilerobots.com/wiki/File:Folder_icon_bw.png
"Image:Folder_icon_bw.png")[Archived versions of
MOGS](http://robots.mobilerobots.com/MOGS/download/archives/
"http://robots.mobilerobots.com/MOGS/download/archives/")

##  Recommended Additional Downloads

[Mapper3](http://robots.mobilerobots.com/wiki/Mapper3 "Mapper3") or
[Mapper3Basic](http://robots.mobilerobots.com/wiki/Mapper3Basic
"Mapper3Basic")

    To work with ARNL you will also need to download the Mapper3 application so that you can make maps for ARNL to navigate and localize in. [Mapper3](http://robots.mobilerobots.com/wiki/Mapper3 "Mapper3") will take laser scan log files (.2d) (generated by arnlServer or sickLogger) and transform them into maps (.map files) for use with ARNL and then let you edit them, including placing goals and forbidden lines and moving the robots home position. [Mapper3Basic](http://robots.mobilerobots.com/wiki/Mapper3Basic "Mapper3Basic") can also be used to edit maps, but cannot process laser scans. It is, however, available to all customers. 

[MobileEyes](http://robots.mobilerobots.com/wiki/MobileEyes "MobileEyes")

    You will also want to download the [MobileEyes](http://robots.mobilerobots.com/wiki/MobileEyes "MobileEyes") application so that you can have a GUI to watch what the robot is doing. MobileEyes connects to servers run from an ARNL program across a network, letting you view the robot's movements and environment without slowing them down. 

[ARIA](http://robots.mobilerobots.com/wiki/ARIA "ARIA")

    While not required (ARNL is self contained), [ARIA](http://robots.mobilerobots.com/wiki/ARIA "ARIA") may also be used for its examples and source code 

[MobileSim](http://robots.mobilerobots.com/wiki/MobileSim "MobileSim")

    While it is not required, it is recommended that you also download [MobileSim](http://robots.mobilerobots.com/wiki/MobileSim "MobileSim") so that you can use the simulator for developing, debugging, and simulating your code. 

**What do you think of this page?**

_Please take a moment to rate this page below. Your feedback is valuable and
helps us improve our website.[Contact
us](http://robots.mobilerobots.com/wiki/Contact_us "Contact us") if you have a
suggestion for correcting or improving this page._

**Accuracy :**  **Completeness :**  **Clarity :**

  

  


---
### ATTACHMENTS
[6019a34a40e52e5b32b823ea17d1f2a2]: media/ARNL_SONARNL_and_MOGS_-_MobileRobots_Research_and_Academic_Customer_Support.png
[ARNL_SONARNL_and_MOGS_-_MobileRobots_Research_and_Academic_Customer_Support.png](media/ARNL_SONARNL_and_MOGS_-_MobileRobots_Research_and_Academic_Customer_Support.png)
[72ed9c2e52fb073419bd011cfd2a09ea]: media/ARNL_SONARNL_and_MOGS_-_MobileRobots_Research_and_Academic_Customer_Support-2.png
[ARNL_SONARNL_and_MOGS_-_MobileRobots_Research_and_Academic_Customer_Support-2.png](media/ARNL_SONARNL_and_MOGS_-_MobileRobots_Research_and_Academic_Customer_Support-2.png)
[9dfda1d392edac115bbc68d56e4cbfb4]: media/ARNL_SONARNL_and_MOGS_-_MobileRobots_Research_and_Academic_Customer_Support-3.png
[ARNL_SONARNL_and_MOGS_-_MobileRobots_Research_and_Academic_Customer_Support-3.png](media/ARNL_SONARNL_and_MOGS_-_MobileRobots_Research_and_Academic_Customer_Support-3.png)
[d80cee00d5741dfcfd771ef89331a8dc]: media/ARNL_SONARNL_and_MOGS_-_MobileRobots_Research_and_Academic_Customer_Support-4.png
[ARNL_SONARNL_and_MOGS_-_MobileRobots_Research_and_Academic_Customer_Support-4.png](media/ARNL_SONARNL_and_MOGS_-_MobileRobots_Research_and_Academic_Customer_Support-4.png)

---
### TAGS
{AI*MR概述}

---
### NOTE ATTRIBUTES
>Created Date: 2017-04-12 07:01:06  
>Last Evernote Update Date: 2017-04-20 14:26:09  
>source: web.clip  
>source-url: http://robots.mobilerobots.com/wiki/ARNL,_SONARNL_and_MOGS  
>source-application: evernote.win32  