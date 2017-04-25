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

#include "MyUtf8.h"

#include <algorithm>
#include <codecvt>
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <locale>

void my_utf8::setConsoleToUtf8()
{
    _setmode(_fileno(stdout), _O_U8TEXT);
    _setmode(_fileno(stdin),  _O_U8TEXT);
    _setmode(_fileno(stderr), _O_U8TEXT);
}

bool my_utf8::needChangingEndianness()
{
    uint16_t number1 = 0xABCD;

    uint8_t* number2Arr[2];
    number2Arr[0] = 0xAB;
    number2Arr[1] = 0XCD;
    uint16_t number2 = *reinterpret_cast<uint16_t>(number2Arr);

    return number1 != number2;
}

void changeEndianness(std::wstring& string)
{
    for (wchar_t& c : string)
    {
        uint8_t* d = reinterpret_cast<uint8_t*>(&c);
        std::swap(d[0], d[1]);
    }
}

std::wstring my_utf8::convertToWString(const char* bytes,
                                       bool needChangingEndianness)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;
    std::wstring wstr = convert.from_bytes(bytes);

    if (needChangingEndianness)
        changeEndianness(wstr);

    return wstr;
}

std::wstring my_utf8::convertToWString(const std::string& bytes,
                                       bool needChangingEndianness)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;
    std::wstring wstr = convert.from_bytes(bytes);

    if (needChangingEndianness)
        changeEndianness(wstr);

    return wstr;
}

std::string my_utf8::convertToBytes(std::wstring string,
                                    bool needChangeEndianness)
{
    if (needChangeEndianness)
        changeEndianness(string);

    std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;

    return convert.to_bytes(string);
}
