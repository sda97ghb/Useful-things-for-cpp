# Useful-things-for-cpp
Small things that can make c++ programming little nicer.

## Features

### New loops
#### repeat n times
##### Example:
```
// print "click!" five times
repeat(5)
	printf("click!\n");
```

#### forever
##### Example:
```
// print q until the program is stopped
forever
	printf("q");
```

### <i>Instance of</i> check:
```
instanceof<ClassName>(objectName)
```
True if objectName if instance of ClassName, false otherwise.

### Utf8 support
#### my_utf8::setConsoleToUtf8()
Set console in wchar mode. Use std::wcout and std::wcin until this command.

#### my_utf8::needChangingEndianness()
True if your system is small-endian, false if big-endian

#### my_utf8::convertToWString(bytes)
Convert byte sequence to std::wstring. Byte sequence can be represented as const char* or std::string. Useful when you work with library that doesn't support std::wstring, such as TinyXml2.

##### Example:
```
XMLElement* elem = root->FirstChildElement("elem");
std::wstring str = my_utf8::convertToWString(elem->GetText());
```

#### my_utf8::convertToBytes(std::wstring)
Antipode of convertToWString, it is passing wide character string and returns byte sequnce as std::string.

### Object counter:
Provide access to all instances of some class.
#### Usage:
* In each of your class constructors:
```
ObjectCounter<your class name>::addObject(this);
```
* In your class destructor:
```
ObjectCounter<your class name>::removeObject(this);
```
* And then in any place where you need:
  * Get count of objects of your class:
  ```
  ObjectCounter<your class name>::count()
  ```
  * Get list of all objects of your class:
  ```
  ObjectCounter<your class name>::objects() // => std::list<your class name pointer>
  ```
