#include <ctime>
#include <iostream>

#include "HammingCode.h"

namespace hamming_code
{
    Byte encodeByteLowerHalf(Byte byte)
    {
        // For explanation see https://en.wikipedia.org/wiki/Hamming(7,4).

        Byte d1 = (byte & 0b00000001) == 0 ? 0 : 1;
        Byte d2 = (byte & 0b00000010) == 0 ? 0 : 1;
        Byte d3 = (byte & 0b00000100) == 0 ? 0 : 1;
        Byte d4 = (byte & 0b00001000) == 0 ? 0 : 1;

        Byte p1 = d1 ^ d2 ^ d4;
        Byte p2 = d1 ^ d3 ^ d4;
        Byte p3 = d2 ^ d3 ^ d4;
        Byte p4 = d1 ^ d2 ^ d3 ^ d4 ^ p1 ^ p2 ^ p3;

        return p1 | (p2 << 1) | (d1 << 2) | (p3 << 3) | (d2 << 4) | (d3 << 5) |
                (d4 << 6) | (p4 << 7);
    }

    Array<Byte, 2> encode(Byte byte)
    {
        return { encodeByteLowerHalf(byte >> 4), encodeByteLowerHalf(byte) };
    }

    Vector<Byte> encode(String str)
    {
        Vector<Byte> v(str.size() * 2);
        int i = 0;
        for (char c : str)
        {
            Array<Byte, 2> e = encode((Byte)c);
            v.at(i++) = e.at(0);
            v.at(i++) = e.at(1);
        }
        return v;
    }

    Byte decodeByteLowerHalf(Byte byte)
    {
        // For explanation see https://en.wikipedia.org/wiki/Hamming(7,4).

        // get data and parity bits
        Byte p1 = (byte & 0b00000001);
        Byte p2 = (byte & 0b00000010) >> 1;
        Byte d1 = (byte & 0b00000100) >> 2;
        Byte p3 = (byte & 0b00001000) >> 3;
        Byte d2 = (byte & 0b00010000) >> 4;
        Byte d3 = (byte & 0b00100000) >> 5;
        Byte d4 = (byte & 0b01000000) >> 6;
//        Byte p4 = (byte & 0b10000000) >> 7;

        // check parities
        bool p1Correctness = p1 == (d1 ^ d2 ^ d4);
        bool p2Correctness = p2 == (d1 ^ d3 ^ d4);
        bool p3Correctness = p3 == (d2 ^ d3 ^ d4);

        // fix parities
        if (!p1Correctness && !p2Correctness && !p3Correctness)
            d4 = ((d4 == 0) ? 1 : 0);
        else if (!p1Correctness && !p2Correctness)
            d1 = ((d1 == 0) ? 1 : 0);
        else if (!p1Correctness && !p3Correctness)
            d2 = ((d2 == 0) ? 1 : 0);
        else if (!p2Correctness && !p3Correctness)
            d3 = ((d3 == 0) ? 1 : 1);

        // return fixed byte
        return d1 | (d2 << 1) | (d3 << 2) | (d4 << 3);
    }

    Byte decode(const Array<Byte, 2>& code)
    {
        return (decodeByteLowerHalf(code.at(0)) << 4) |
                decodeByteLowerHalf(code.at(1));
    }

    String decode(Vector<Byte> v)
    {
        String str;
        unsigned strSize = v.size() / 2;
        for (unsigned i = 0; i < strSize; ++ i)
        {
            Array<Byte, 2> e = { v.at(i * 2), v.at(i * 2 + 1) };
            Byte d = decode(e);
            str.append({(char)d});
        }
        return str;
    }

    namespace test
    {
        void init()
        {
            srand(time(nullptr));
        }

        /// @brief Switch n random bits.
        template <typename Container>
        Container noise(Container sequence, int n)
        {
            for (int i = 0; i < n; ++ i)
                sequence.at(rand() % sequence.size()) ^= (1 << (rand() % 8));
            return sequence;
        }

        /// @returns String with binary representation of the byte.
        String bits(Byte byte)
        {
            String result;
            for (int i = 7; i >= 0; -- i)
                result += ((byte & (1 << i)) == 0) ? '0' : '1';
            return result;
        }

        /// @brief Print all codewords.
        void test1()
        {
            using namespace std;
            cout << "//---- Test 1 (codewords) ----//" << endl;
            for (Byte i = 0; i < 16; ++ i)
            {
                Byte b = i;
                Array<Byte, 2> e = encode(b);
                Byte d = decode(e);
                cout << (int)b << " " << bits(b) << " " << bits(e.at(0)) << " " << bits(e.at(1)) << " " << bits(d) << endl;
            }
            for (Byte i = 0; i < 16; ++ i)
            {
                Byte b = i << 4;
                Array<Byte, 2> e = encode(b);
                Byte d = decode(e);
                cout << (int)b << " " << bits(b) << " " << bits(e.at(0)) << " " << bits(e.at(1)) << " " << bits(d) << endl;
            }
        }

        /// @brief Apply noise and count errors.
        void test2()
        {
            using namespace std;
            cout << "//---- Test 2 (noise) ----//" << endl;
            const int NUMBER_OF_TESTS = 100000;
            const int NOISE_BIT_COUNT = 1;
            int errorCounter = 0;
            for (int i = 0; i < NUMBER_OF_TESTS; ++ i)
            {
                Byte b = rand() % 256;
                Array<Byte, 2> e = encode(b);
                e = noise(e, NOISE_BIT_COUNT);
                Byte d = decode(e);
                if (d != b)
                    ++ errorCounter;
            }
            double percent = static_cast<double>(errorCounter) /
                    static_cast<double>(NUMBER_OF_TESTS) * 100.0;
            cout << "Tested " << NUMBER_OF_TESTS << " times." << endl;
            cout << "Noise bit count is " << NOISE_BIT_COUNT << "." << endl;
            cout << "Got " << errorCounter << " errors. (" << percent << "%)" << endl;
        }

        /// @brief Encode and decode string.
        void test3()
        {
            using namespace std;
            cout << "//---- Test 3 (string) ----//" << endl;

            for (int i = 0; i < 10; ++ i)
            {
//                String str = "Hello, Hamming code!";
                String str = "0123456789";
                Vector<Byte> e = encode(str);
                Vector<Byte> eNoised = noise(e, str.size() * 1 / 2);
                String d = decode(eNoised);
                cout << "Original string is \"" << str << "\"" << endl;
                cout << "Decoded string is  \"" << d << "\"" << endl;
            }
        }

        /// @brief Run all tests.
        void test()
        {
            init();

            using namespace std;

            test1();
            cout << endl;

            test2();
            cout << endl;

            test3();
            cout << endl;
        }
    }
}
