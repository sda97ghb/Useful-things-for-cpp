#ifndef VALUEMAPPER_H
#define VALUEMAPPER_H

template <typename in_t, typename out_t>
class ValueMapper
{
public:
    ValueMapper(in_t minIn, in_t maxIn, out_t minOut, out_t maxOut) :
        _minIn(minIn),
        _maxIn(maxIn),
        _minOut(minOut),
        _maxOut(maxOut)
    {}

    void setInRange(in_t min, in_t max)
    {
        _minIn = min;
        _maxIn = max;
    }

    void setOutRange(out_t min, out_t max)
    {
        _minOut = min;
        _maxOut = max;
    }

    in_t minIn() const { return _minIn; }
    in_t maxIn() const { return _maxIn; }
    out_t minOut() const { return _minOut; }
    out_t maxOut() const { return _maxOut; }

    void setMinIn(in_t value) { _minIn = value; }
    void setMaxIn(in_t value) { _maxIn = value; }
    void setMinOut(out_t value) { _minOut = value; }
    void setMaxOut(out_t value) { _maxOut = value; }

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
    in_t _minIn;
    in_t _maxIn;
    out_t _minOut;
    out_t _maxOut;
};

#endif // VALUEMAPPER_H
