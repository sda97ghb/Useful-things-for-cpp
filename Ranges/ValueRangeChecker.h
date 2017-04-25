#ifndef VALUERANGECHECKER_H
#define VALUERANGECHECKER_H

enum class RangeType
{
    inclusive,
    exclusive
};

template <typename T>
class ValueRangeChecker
{
public:
    ValueRangeChecker(T min, T max, RangeType mode = RangeType::inclusive) :
        _min(min),
        _max(max),
        _mode(mode)
    {}

    void setRange(T min, T max)
    {
        _min = min;
        _max = max;
    }

    T min() const { return _min; }
    T max() const { return _max; }

    void setMin(T min) { _min = min; }
    void setMax(T max) { _max = max; }

    RangeType mode() const { return _mode; }
    void setMode(RangeType mode) { _mode = mode; }

    bool isInRange(T value, RangeType mode)
    {
        switch (mode)
        {
            case RangeType::exclusive :
                return value > _min && value < _max;
            case RangeType::inclusive :
                return value >= _min && value <= _max;
        }
    }

    bool isOutOfRange(T value, RangeType mode)
    {
        return !isInRange(value, mode);
    }

    bool isInRange(T value)
    {
        return isInRange(value, _mode);
    }

    bool isOutOfRange(T value)
    {
        return isOutOfRange(value, _mode);
    }

private:
    T _min;
    T _max;

    RangeType _mode;
};

#endif // VALUERANGECHECKER_H
