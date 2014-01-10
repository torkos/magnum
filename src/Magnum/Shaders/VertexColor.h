#ifndef Magnum_Shaders_VertexColor_h
#define Magnum_Shaders_VertexColor_h
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
 * @brief Class Magnum::Shaders::VertexColor
 */

#include "Magnum/Color.h"
#include "Magnum/DimensionTraits.h"
#include "Magnum/Math/Matrix3.h"
#include "Magnum/Math/Matrix4.h"
#include "Magnum/Shaders/Generic.h"
#include "Magnum/Shaders/visibility.h"

namespace Magnum { namespace Shaders {

/**
@brief Vertex color shader

Draws vertex-colored mesh.
@see VertexColor2D, VertexColor3D
*/
template<UnsignedInt dimensions> class MAGNUM_SHADERS_EXPORT VertexColor: public AbstractShaderProgram {
    public:
        /** @brief Vertex position */
        typedef typename Generic<dimensions>::Position Position;

        /** @brief Vertex color */
        typedef Attribute<3, Color3> Color;

        explicit VertexColor();

        /**
         * @brief Set transformation and projection matrix
         * @return Reference to self (for method chaining)
         *
         * Default is identity matrix.
         */
        VertexColor<dimensions>& setTransformationProjectionMatrix(const typename DimensionTraits<dimensions, Float>::MatrixType& matrix) {
            setUniform(transformationProjectionMatrixUniform, matrix);
            return *this;
        }

    private:
        Int transformationProjectionMatrixUniform;
};

/** @brief 2D vertex color shader */
typedef VertexColor<2> VertexColor2D;

/** @brief 3D vertex color shader */
typedef VertexColor<3> VertexColor3D;

}}

#endif
