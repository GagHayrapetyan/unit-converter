#include <iostream>

#include "converter.h"


int main() {
    auto c = unit_converter::Converter("km/h", "m/s");

    std::cout << c.convert(1) << std::endl;
    std::cout << c.convert(1, true) << std::endl;



    return 0;
}
