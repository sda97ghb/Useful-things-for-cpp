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
