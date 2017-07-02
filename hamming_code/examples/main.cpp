#include <iostream>

#include "HammingCode.h"

int main()
{
    using std::cout;
    using std::endl;

    using hamming_code::Byte;
    using hamming_code::String;
    using hamming_code::Vector;


    // LOCAL END

    // set a string
    String str = "Hello, Hamming code!";

    // encode the string
    Vector<Byte> encoded = hamming_code::encode(str);


    // CHANEL

    // emulate sending through a noisy chanel
    // add noise (switch str.size() bits)
    const int NUMBER_OF_BITS_TO_SWITCH = str.size();
    encoded = hamming_code::test::noise(encoded, NUMBER_OF_BITS_TO_SWITCH);


    // REMOTE END

    // decode the message and fix errors
    // some of errors can't be fixed
    hamming_code::String decoded = hamming_code::decode(encoded);
    cout << decoded << endl;

    return 0;
}
