#ifndef OBJECT_COUNTER_H
#define OBJECT_COUNTER_H

#include <algorithm>
#include <list>

/**
 *  @brief This class can count the number of objects of specified type
 *  and give you the list of them.
 *
 *  Usage:
 *  -# In each of your class constructors:
 *      @code ObjectCounter<your class name>::addObject(this); @endcode
 *
 *  -# In your class destructor:
 *      @code ObjectCounter<your class name>::removeObject(this); @endcode
 *
 *  -# And then in any place where you need:
 *      - Get count of objects of your class:
 *          @code ObjectCounter<your class name>::count() @endcode
 *      - Get list of all objects of your class:
 *          @code ObjectCounter<your class name>::objects()
 *                  // => std::list<your class name pointer> @endcode
 *
 *  @note
 *      This class can't count the number of objects which don't use
 *      @ref addObject and @ref removeObject in their constructors and destructor.
 *      This means that you can't count the number of objects such as strings
 *      or int which are used in your program.
 */

template <typename T>
class ObjectCounter
{
public:
    /// @brief List of objects of specified type.
    static const std::list<T*> objects()
    {
        return _objects;
    }

    /// @brief Remember new object.
    static void addObject(T* object)
    {
        _objects.push_back(object);
    }

    /// @brief Forget object.
    static void removeObject(T* object)
    {
        _objects.erase(std::find(_objects.begin(), _objects.end(), object));
    }

    /// @brief Give count of objects of specified class.
    static size_t count()
    {
        return _objects.size();
    }

private:
    static std::list<T*> _objects; ///< all remembered objects of specified class
};

template <typename T>
std::list<T*> ObjectCounter<T>::_objects;

#endif // OBJECT_COUNTER_H
