#
#   This file is part of Magnum.
#
#   Copyright © 2010, 2011, 2012, 2013, 2014, 2015
#             Vladimír Vondruš <mosra@centrum.cz>
#
#   Permission is hereby granted, free of charge, to any person obtaining a
#   copy of this software and associated documentation files (the "Software"),
#   to deal in the Software without restriction, including without limitation
#   the rights to use, copy, modify, merge, publish, distribute, sublicense,
#   and/or sell copies of the Software, and to permit persons to whom the
#   Software is furnished to do so, subject to the following conditions:
#
#   The above copyright notice and this permission notice shall be included
#   in all copies or substantial portions of the Software.
#
#   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
#   THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
#   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
#   DEALINGS IN THE SOFTWARE.
#

set(MagnumFont_SRCS
    MagnumFont.cpp)

set(MagnumFont_HEADERS
    MagnumFont.h)

# Objects shared between plugin and test library
add_library(MagnumFontObjects OBJECT ${MagnumFont_SRCS})
if(NOT BUILD_PLUGINS_STATIC OR BUILD_STATIC_PIC)
    set_target_properties(MagnumFontObjects PROPERTIES POSITION_INDEPENDENT_CODE ON)
endif()

# MagnumFont plugin
add_plugin(MagnumFont ${MAGNUM_PLUGINS_FONT_DEBUG_INSTALL_DIR} ${MAGNUM_PLUGINS_FONT_RELEASE_INSTALL_DIR}
    MagnumFont.conf
    $<TARGET_OBJECTS:MagnumFontObjects>
    pluginRegistration.cpp)
if(BUILD_STATIC_PIC)
    set_target_properties(MagnumFont PROPERTIES POSITION_INDEPENDENT_CODE ON)
endif()

target_link_libraries(MagnumFont Magnum MagnumText)
if(CORRADE_TARGET_WINDOWS)
    target_link_libraries(MagnumFont TgaImporter)
endif()

install(FILES ${MagnumFont_HEADERS} DESTINATION ${MAGNUM_PLUGINS_INCLUDE_INSTALL_DIR}/MagnumFont)

if(BUILD_GL_TESTS)
    add_library(MagnumMagnumFontTestLib STATIC $<TARGET_OBJECTS:MagnumFontObjects>)
    target_link_libraries(MagnumMagnumFontTestLib Magnum MagnumText MagnumTgaImporterTestLib)
    add_subdirectory(Test)
endif()
