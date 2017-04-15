#ifndef OBJECT_COUNTER_H
#define OBJECT_COUNTER_H

#include <algorithm>
#include <list>

/*
 * This class can count the number of objects of specified type
 * and give you list of them.
 *
 * Usage:
 *     In each of your class constructors:
 *         ObjectCounter<your class name>::addObject(this);
 *
 *     In your class destructor:
 *         ObjectCounter<your class name>::removeObject(this);
 *
 *     And then in any place where you need:
 *         Know count of objects of your class:
 *             ObjectCounter<your class name>::count()
 *         Get list of all objects of your class:
 *             ObjectCounter<your class name>::objects()
 *                 // => std::list<your class name pointer>
 *
 * None:
 *     This class can't count the number of objects which don't use
 *     addObject and removeObject in their constructors and destructor.
 *     This means that you can't count the number of strings or int for example
 *     which are used in your program.
 */

template <typename T>
class ObjectCounter
{
public:
    static const std::list<T*> objects()
    {
        return _objects;
    }

    static void addObject(T* object)
    {
        _objects.push_back(object);
    }

    static void removeObject(T* object)
    {
        _objects.erase(std::find(_objects.begin(), _objects.end(), object));
    }

    static size_t count()
    {
        return _objects.size();
    }

private:
    static std::list<T*> _objects;
};

template <typename T>
std::list<T*> ObjectCounter<T>::_objects;

#endif // OBJECT_COUNTER_H
