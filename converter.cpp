//
// Created by Gag Hayrapetyan on 03.06.2022.
//
#include "converter.h"

namespace unit_converter {

    Converter::Converter(std::string from, std::string to)
            : _from_str(from),
              _to_str(to),
              _from({}),
              _to({}) {
        _from = UnitParser::parse(_from_str);
        _to = UnitParser::parse(_to_str);

        if (_from.is_same_dimension(_to)) {
            throw std::runtime_error("Units are not of the same dimension !");
        }
    }

    std::ostream &operator<<(std::ostream &os, const Converter &obj) {
        return os << obj._from_str << " -> " << obj._to_str << std::endl;
    }

    double Converter::convert(double value, bool conversely) {
        if (conversely) {
            value = _to.convert(value, Unit::Direction::TO_SI);
            value = _from.convert(value, Unit::Direction::FROM_SI);
        } else {
            value = _from.convert(value, Unit::Direction::TO_SI);
            value = _to.convert(value, Unit::Direction::FROM_SI);
        }

        return value;
    }
}
