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
