//
// Created by Gag Hayrapetyan on 03.06.2022.
//

#include <iostream>
#include <string>

#include "parser.h"
#include "unit.h"

#ifndef UNIT_CONVERTER_CONVERTER_H
#define UNIT_CONVERTER_CONVERTER_H

namespace unit_converter {

    class Converter {
    public:
        Converter(std::string from, std::string to);

        friend std::ostream &operator<<(std::ostream &os, const Converter &obj);

        double convert(double value, bool conversely = false);

    private:
        std::string _from_str;
        std::string _to_str;
        MultiUnit _from;
        MultiUnit _to;

    };

}

#endif //UNIT_CONVERTER_CONVERTER_H
