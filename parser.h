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

    class ParserUnitStr {
    public:
        static Unit parse(const std::string &str);

    private:
        static std::vector<Unit> _parse_by_mult_syb(const std::string &str);

        static Unit _mult_unit(const std::string &str);

        static std::pair<std::string, std::uint8_t> _parse_degree(const std::string &str);

        static std::vector<std::string> _parse_by_divid_syb(const std::string &str);
    };

}

#endif //UNIT_CONVERTER_PARSER_H
