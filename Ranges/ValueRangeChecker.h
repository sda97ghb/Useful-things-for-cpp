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

#ifndef VALUERANGECHECKER_H
#define VALUERANGECHECKER_H

/// @brief Range behavior on its ends.
enum class RangeType
{
    inclusive, ///< include ends of range
    exclusive  ///< exclude ends of range
};

/// @brief Check if value lies in a range or not.
template <typename T>
class ValueRangeChecker
{
public:
    /// @brief Create checker with given range.
    ValueRangeChecker(T min, T max, RangeType mode = RangeType::inclusive) :
        _min(min),
        _max(max),
        _mode(mode)
    {}

    /// @brief Set range.
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
    void setMin(T min) { _min = min; }

    /// @brief Set maximal value of range.
    void setMax(T max) { _max = max; }

    /// @brief Range behavior on its ends.
    RangeType mode() const { return _mode; }

    /// @brief Set range behavior on its ends.
    void setMode(RangeType mode) { _mode = mode; }

    /// @brief Check if value is in range.
    bool isInRange(T value, RangeType mode)
    {
        switch (mode)
        {
            case RangeType::exclusive :
                return value > _min && value < _max;
            case RangeType::inclusive :
                return value >= _min && value <= _max;
        }
        return false; // remove compiler warning
    }

    /// @brief Check if value is out of range.
    bool isOutOfRange(T value, RangeType mode)
    {
        return !isInRange(value, mode);
    }

    /// @brief Check if value is in range.
    bool isInRange(T value)
    {
        return isInRange(value, _mode);
    }

    /// @brief Check if value is out of range.
    bool isOutOfRange(T value)
    {
        return isOutOfRange(value, _mode);
    }

private:
    T _min; ///< minimal value of range
    T _max; ///< maximal value of range

    RangeType _mode; ///< range behaviour on its ends
};

#endif // VALUERANGECHECKER_H
