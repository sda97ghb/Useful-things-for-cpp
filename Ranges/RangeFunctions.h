#ifndef RANGEFUNCTIONS_H
#define RANGEFUNCTIONS_H

template <typename T>
T constrain(T value, T min, T max)
{
    if (value < min)
        return min;
    if (value > max)
        return max;
    return value;
}

template <typename in_t, typename out_t>
out_t map(in_t value, in_t minIn, in_t maxIn, out_t minOut, out_t maxOut)
{
    double rangeIn = static_cast<double>(maxIn - minIn);
    double rangeOut = static_cast<double>(maxOut - minOut);

    double fraction = rangeOut / rangeIn;

    double oldValue = static_cast<double>(value - minIn);
    double newValue = oldValue * fraction;

    return static_cast<out_t>(newValue) + minOut;
}

template <typename T>
bool isValueInRange(T value, T min, T max)
{
    return value >= min && value <= max;
}

template <typename T>
bool isValueOutOfRange(T value, T min, T max)
{
    return value < min || value > max;
}

template <typename T>
bool isValueInRangeEx(T value, T min, T max)
{
    return value > min && value < max;
}

template <typename T>
bool isValueOutOfRangeEx(T value, T min, T max)
{
    return value <= min || value >= max;
}

#endif // RANGEFUNCTIONS_H
