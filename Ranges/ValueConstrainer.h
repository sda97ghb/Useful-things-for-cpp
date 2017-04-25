#ifndef VALUECONSTRAINER_H
#define VALUECONSTRAINER_H

template <typename T>
class ValueConstrainer
{
public:
    ValueConstrainer(T min, T max) :
        _min(min),
        _max(max)
    {}

    void setRange(T min, T max)
    {
        _min = min;
        _max = max;
    }

    T min() const { return _min; }
    T max() const { return _max; }

    void setMin(T value) { _min = value; }
    void setMax(T value) { _max = value; }

    void constrain(T value)
    {
        if (value < _min)
            return _min;
        if (value > _max)
            return _max;
        return value;
    }

private:
    T _min;
    T _max;
};

#endif // VALUECONSTRAINER_H
