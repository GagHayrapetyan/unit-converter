//
// Created by Gag Hayrapetyan on 02.06.2022.
//

#include "parser.h"


namespace unit_converter {

    std::vector<std::string> UnitParser::_split_by_division(const std::string &str) {
        auto v = StrExt::split(str, '/');

        if ((v.size() == 1 && StrExt::find_term(str, "/")) || v.size() > 2 || v.empty()) {
            throw Exception("Unit doesn't exist !");
        }

        return v;
    }

    std::pair<std::string, std::uint8_t> UnitParser::_parse_degree(const std::string &str) {
        if (!StrExt::find_term(str, "^")) {
            return {str, 1};
        }

        std::vector<std::string> v = StrExt::split(str, '^');

        if (v.size() != 2 || !StrExt::isInt(v[1])) {
            throw Exception("Unit doesn't exist !");
        }

        return {v[0], std::stoi(v[1])};
    }

    std::vector<std::string> UnitParser::_split_by_multiplication(const std::string &str) {
        return StrExt::split(str, '*');
    }

    MultiUnit UnitParser::parse(const std::string &str) {
        MultiUnit u;
        auto d_v = _split_by_division(str);
        auto m_v = _split_by_multiplication(d_v[0]);
        _processing(u, m_v, MultiUnit::Operator::MULTIPLICATION);

        if (d_v.size() == 2) {
            m_v = _split_by_multiplication(d_v[1]);
            _processing(u, m_v, MultiUnit::Operator::DIVISION);
        }

        return u;
    }

    void UnitParser::_operator(MultiUnit &mu, const Unit &u, const MultiUnit::Operator &op) {
        if (op == MultiUnit::Operator::MULTIPLICATION) {
            mu *= u;
        } else if (op == MultiUnit::Operator::DIVISION) {
            mu /= u;
        }
    }

    void UnitParser::_operator(MultiUnit &mu, const UnitPrefix &u, const MultiUnit::Operator &op) {
        if (op == MultiUnit::Operator::MULTIPLICATION) {
            mu *= u;
        } else if (op == MultiUnit::Operator::DIVISION) {
            mu /= u;
        }
    }

    void UnitParser::_processing(MultiUnit &u, const std::vector<std::string> &v, MultiUnit::Operator op) {
        for (auto &i: v) {
            auto [unit_str, degree] = _parse_degree(i);

            auto unit = *_parse_unit(unit_str);
            auto [e, prefix] = _parse_unit_parser(unit_str);


            for (auto j = 0; j < degree; j++) {
                if (e) {
                    _operator(u, *prefix, op);
                }

                _operator(u, unit, op);
            }
        }
    }

    Unit *UnitParser::_parse_unit(std::string &str) {
        Unit *unit = nullptr;

        for (auto i = 0; i <= 2; i++) {
            try {
                unit = UnitData::find(str.substr(i, str.length()));
            } catch (Exception &e) {
                if (i == 2) {
                    throw e.what();
                }

                continue;
            }

            str.erase(i, str.length());
            break;
        }

        return unit;
    }

    std::pair<bool, UnitPrefix *> UnitParser::_parse_unit_parser(const std::string &str) {
        return UnitData::find_prefix(str);
    }


}