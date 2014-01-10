#ifndef Magnum_MeshTools_FullScreenTriangle_h
#define Magnum_MeshTools_FullScreenTriangle_h
/*
    This file is part of Magnum.

    Copyright © 2010, 2011, 2012, 2013 Vladimír Vondruš <mosra@centrum.cz>

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

/** @file
 * @brief Function @ref Magnum::MeshTools::fullScreenTriangle()
 */

#include <memory>
#include <utility>

#include "Magnum/Magnum.h"
#include "Magnum/MeshTools/visibility.h"

namespace Magnum { namespace MeshTools {

/**
@brief Create full screen triangle mesh

Returns pre-configured mesh along with vertex buffer which can be used for
full-screen post-processing effects. The mesh is single triangle covering whole
screen area (@f$ (-1, -1) - (1, 1) @f$ on both dimensions) and provides only
vertex positions, as other attributes (such as texture coordinates) can be
computed from them. The vertex positions are, in order:
@f[
    \begin{pmatrix} -1 \\ 1 \end{pmatrix},
    \begin{pmatrix} -1 \\ -3 \end{pmatrix},
    \begin{pmatrix} 3 \\ 1 \end{pmatrix}
@f]

Based on @p version parameter, on OpenGL 2.1 and OpenGL ES 2.0 the vertex
positions are passed explicitly as attribute `0`, contained in the buffer. On
OpenGL 3.0+ and OpenGL ES 3.0+ the mesh is attribute-less and the vertex
positions can be computed using `gl_VertexID` builtin shader variable, thus
`nullptr` is returned instead of vertex buffer.

Computing positions in vertex shader in a portable way might be done like this.
For OpenGL 2.1 and OpenGL ES 2.0 you then need to bind the location of `position`
attribute to `0`.
@code
#if (!defined(GL_ES) && __VERSION__ >= 130) || (defined(GL_ES) && __VERSION__ >= 300)
#define NEW_GLSL
#endif

#ifndef NEW_GLSL
attribute lowp vec4 position;
#endif

void main() {
    #ifdef NEW_GLSL
    gl_Position = vec4((gl_VertexID == 2) ?  3.0 : -1.0,
                       (gl_VertexID == 1) ? -3.0 :  1.0, 0.0, 1.0);
    #else
    gl_Position = position;
    #endif
}
@endcode
*/
std::pair<std::unique_ptr<Buffer>, Mesh> MAGNUM_MESHTOOLS_EXPORT fullScreenTriangle(Version version);

/**
@overload

This function implicitly uses current context version.
*/
std::pair<std::unique_ptr<Buffer>, Mesh> MAGNUM_MESHTOOLS_EXPORT fullScreenTriangle();

}}

#endif
