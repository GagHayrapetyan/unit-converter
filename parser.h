//
// Created by Gag Hayrapetyan on 02.06.2022.
//

#include <iostream>
#include <string>
#include <vector>

#include "str_extension.cc"

#include "unit.h"
#include "data.h"


#ifndef UNIT_CONVERTER_PARSER_H
#define UNIT_CONVERTER_PARSER_H

namespace unit_converter {

    class UnitParser {
    public:
        static MultiUnit parse(const std::string &str);

    private:
        static void _operator(MultiUnit &mu, const Unit& u, const  MultiUnit::Operator &op);

        static void _processing(MultiUnit &u, const std::vector<std::string> &v, MultiUnit::Operator op);

        static std::vector<std::string> _split_by_division(const std::string &str);

        static std::vector<std::string> _split_by_multiplication(const std::string &str);

        static std::pair<std::string, std::uint8_t> _parse_degree(const std::string &str);

    };

}

#endif //UNIT_CONVERTER_PARSER_H
