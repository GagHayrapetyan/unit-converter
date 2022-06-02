//
// Created by Gag Hayrapetyan on 02.06.2022.
//

#include "parser.h"


namespace unit_converter {

    Unit ParserUnitStr::parse(const std::string &str) {
        auto split_d = _parse_by_divid_syb(str);

        if (split_d.size() != 1 || split_d.size() != 2) {
            throw std::runtime_error("Incorrect unit");
        }

        auto u = _mult_unit(split_d[0]);

        if (split_d.size() == 2) {
            auto u_2 = _mult_unit(split_d[0]);
            u /= u_2;
        }

        return u;
    }

    std::vector<Unit> ParserUnitStr::_parse_by_mult_syb(const std::string &str) {
        std::vector<Unit> units;
        std::vector<std::string> split = StrExt::split(str, '*');

        for (auto &i: split) {
            auto [unit_str, degree] = _parse_degree(i);
            auto unit = *UnitData::find(unit_str);
            unit *= degree;
            units.push_back(unit);
        }

        return units;
    }

    std::pair<std::string, std::uint8_t> ParserUnitStr::_parse_degree(const std::string &str) {
        if (!StrExt::find_term(str, "^")) {
            return {str, 1};
        }

        std::vector<std::string> split = StrExt::split(str, '^');

        if (split.size() != 2 || StrExt::isFloat(split[1])) {
            throw std::runtime_error("Incorrect unit");
        }

        return {split[0], std::stoi(split[1])};
    }

    std::vector<std::string> ParserUnitStr::_parse_by_divid_syb(const std::string &str) {
        return StrExt::split(str, '/');;
    }

    Unit ParserUnitStr::_mult_unit(const std::string &str) {
        auto v = _parse_by_mult_syb(str);
        Unit u("", "", 1, 0, {});

        for (auto &i: v) {
            u *= i;
        }

        return u;
    }

}