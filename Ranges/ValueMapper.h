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

#ifndef VALUEMAPPER_H
#define VALUEMAPPER_H

/// @brief Maps value from one range to another.
/// @example ValueMapper(0, 10, 0, 100).map(5) == 50
template <typename in_t, typename out_t>
class ValueMapper
{
public:
    /// @brief Create mapper with given input and output ranges.
    ValueMapper(in_t minIn, in_t maxIn, out_t minOut, out_t maxOut) :
        _minIn(minIn),
        _maxIn(maxIn),
        _minOut(minOut),
        _maxOut(maxOut)
    {}

    /// @brief Set input range.
    void setInRange(in_t min, in_t max)
    {
        _minIn = min;
        _maxIn = max;
    }

    /// @brief Set output range.
    void setOutRange(out_t min, out_t max)
    {
        _minOut = min;
        _maxOut = max;
    }

    /// @brief Minimal value of input range.
    in_t minIn() const { return _minIn; }

    /// @brief Maximal value of input range.
    in_t maxIn() const { return _maxIn; }

    /// @brief Minimal value of output range.
    out_t minOut() const { return _minOut; }

    /// @brief Maximal value of output range.
    out_t maxOut() const { return _maxOut; }

    /// @brief Set minimal value of input range.
    void setMinIn(in_t value) { _minIn = value; }

    /// @brief Set maximal value of input range.
    void setMaxIn(in_t value) { _maxIn = value; }

    /// @brief Set minimal value of output range.
    void setMinOut(out_t value) { _minOut = value; }

    /// @brief Set maximal value of output range.
    void setMaxOut(out_t value) { _maxOut = value; }

    /// @brief Map value from one range to another.
    out_t map(in_t value)
    {
        double rangeIn = static_cast<double>(_maxIn - _minIn);
        double rangeOut = static_cast<double>(_maxOut - _minOut);

        double fraction = rangeOut / rangeIn;

        double oldValue = static_cast<double>(value - _minIn);
        double newValue = oldValue * fraction;

        return static_cast<out_t>(newValue) + _minOut;
    }

private:
    in_t _minIn;  ///< minimal value of input range
    in_t _maxIn;  ///< maximal value of input range
    out_t _minOut;///< minimal value of output range
    out_t _maxOut;///< maximal value of output range
};

#endif // VALUEMAPPER_H
