/*
* MIT License
*
* Copyright (c) 2017 Dmitry Smirnov
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:

* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

#ifndef VALUECONSTRAINER_H
#define VALUECONSTRAINER_H

/// @brief Constrains values.
template <typename T>
class ValueConstrainer
{
public:
    /// @brief Create ValueConstrainer with given range of constrainment.
    ValueConstrainer(T min, T max) :
        _min(min),
        _max(max)
    {}

    /// @brief Set range of constrainment.
    void setRange(T min, T max)
    {
        _min = min;
        _max = max;
    }

    /// @brief Minimal value of range.
    T min() const { return _min; }

    /// @brief Maximal value of range.
    T max() const { return _max; }

    /// @brief Set minimal value of range.
    void setMin(T value) { _min = value; }

    /// @brief Set maximal value of range.
    void setMax(T value) { _max = value; }

    /// @brief Constrain value.
    void constrain(T value)
    {
        if (value < _min)
            return _min;
        if (value > _max)
            return _max;
        return value;
    }

private:
    T _min; ///< minimal value of range of constrainment.
    T _max; ///< maximal value of range of constrainment
};

#endif // VALUECONSTRAINER_H
