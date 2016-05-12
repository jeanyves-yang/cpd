// cpd - Coherent Point Drift
// Copyright (C) 2016 Pete Gadomski <pete.gadomski@gmail.com>
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

#pragma once

#include <cpd/matrix.hpp>

namespace cpd {
class Normalization {
public:
    Normalization(const MatrixRef source, const MatrixRef target);
    Normalization(const MatrixRef source, const MatrixRef target,
                  double sigma2);

    const Matrix& source() const { return m_source; }
    const Matrix& target() const { return m_target; }
    double sigma2() const { return m_sigma2; }

    template <typename T>
    T denormalize(const T& result) const {
        T out(result);
        out.points = result.points * m_scaling +
                     m_translation.replicate(result.points.rows(), 1);
        return out;
    }

private:
    Matrix m_source;
    Matrix m_target;
    double m_sigma2;
    RowVector m_translation;
    double m_scaling;
};
}