#| libmapuid - map random OpenShift 3 container UIDs to well-known UID
#| Copyright (C) 2016  Daniel Tschan
#|
#| This program is free software; you can redistribute it and/or
#| modify it under the terms of the GNU General Public License
#| Version 2 as published by the Free Software Foundation.
#|
#| This program is distributed in the hope that it will be useful,
#| but WITHOUT ANY WARRANTY; without even the implied warranty of
#| MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#| GNU General Public License for more details.
#|
#| You should have received a copy of the GNU General Public License
#| along with this program; if not, write to the Free Software
#| Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

#INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

ADD_DEFINITIONS(-D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE)

ADD_LIBRARY(
	mapuid SHARED
	libmapuid.c
)

TARGET_LINK_LIBRARIES(mapuid dl)
