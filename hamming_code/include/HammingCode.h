#ifndef HAMMINGCODE_H
#define HAMMINGCODE_H

#include <array>
#include <cstdint>
#include <string>
#include <vector>

namespace hamming_code
{
    template <typename T, size_t N>
    using Array = std::array<T, N>;

    using Byte = uint8_t;

    using String = std::string;

    template <typename T>
    using Vector = std::vector<T>;

    Array<Byte, 2> encode(Byte byte);
    Vector<Byte> encode(String str);

    Byte decode(const Array<Byte, 2>& code);
    String decode(Vector<Byte> v);

    namespace test
    {
        /// @brief Switch n random bits.
        template <typename Container>
        Container noise(Container sequence, int n);

        /// @returns String with binary representation of the byte.
        String bits(Byte byte);

        /// @brief Print all codewords.
        void test1();

        /// @brief Apply noise and count errors.
        void test2();

        /// @brief Encode and decode string.
        void test3();

        /// @brief Run all tests.
        void test();
    }
}

#endif // HAMMINGCODE_H
