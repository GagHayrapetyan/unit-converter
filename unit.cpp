//
// Created by Gag Hayrapetyan on 02.06.2022.
//


#include "unit.h"

namespace unit_converter {

    SIUnits SIUnits::operator+=(const SIUnits &obj) {
        temperature += obj.temperature;
        length += obj.length;
        electric_current += obj.electric_current;
        time += obj.time;
        mass += obj.mass;
        amount_of_substance += obj.amount_of_substance;
        intensity += obj.intensity;

        return *this;
    }

    SIUnits SIUnits::operator-=(const SIUnits &obj) {
        temperature -= obj.temperature;
        length -= obj.length;
        electric_current += obj.electric_current;
        time -= obj.time;
        mass -= obj.mass;
        amount_of_substance -= obj.amount_of_substance;
        intensity -= obj.intensity;

        return *this;
    }

    SIUnits SIUnits::pow(const int &num) {
        temperature += num;
        length += num;
        electric_current += num;
        time += num;
        mass += num;
        amount_of_substance += num;
        intensity += num;

        return *this;
    }

    bool SIUnits::operator==(const SIUnits &obj) const {
        return temperature == obj.temperature &&
               length == obj.length &&
               electric_current == obj.electric_current &&
               time == obj.time &&
               mass == obj.mass &&
               amount_of_substance == obj.amount_of_substance &&
               intensity == obj.intensity;
    }

    bool SIUnits::operator!=(const SIUnits &obj) const {
        return !operator==(obj);
    }


    Unit::Unit(const std::string &symbol,
               const std::string &name,
               SIUnits si_unit,
               Unit::func_t func) : _symbol(symbol),
                                    _name(name),
                                    _si_unit(si_unit),
                                    _converter_funcs(func) {
    }


    Unit::Unit(const std::string &symbol,
               const std::string &name,
               SIUnits si_unit,
               double coefficient) : Unit(symbol, name, si_unit, _converter(coefficient)) {

    }

    Unit::func_t Unit::_converter(double coefficient) {
        return [coefficient](double &value, Direction op) {
            if (op == Direction::TO_SI) {
                value *= coefficient;
            } else {
                value /= coefficient;
            }
        };
    }


    MultiUnit::MultiUnit() : _si_unit({}),
                             _converter_funcs({}) {

    }

    MultiUnit MultiUnit::operator*=(const Unit &obj) {
        _si_unit += obj._si_unit;
        _converter_funcs.emplace_back(obj._converter_funcs, Operator::MULTIPLICATION);

        return *this;
    }

    MultiUnit MultiUnit::operator/=(const Unit &obj) {
        _si_unit -= obj._si_unit;
        _converter_funcs.emplace_back(obj._converter_funcs, Operator::DIVISION);

        return *this;
    }

    MultiUnit &MultiUnit::operator=(const Unit &obj) {
        _si_unit = obj._si_unit;
        _converter_funcs.emplace_back(obj._converter_funcs, Operator::MULTIPLICATION);

        return *this;
    }

    bool MultiUnit::operator==(const MultiUnit &obj) {
        return _si_unit == obj._si_unit;
    }

    bool MultiUnit::operator!=(const MultiUnit &obj) {
        return !operator==(obj);
    }
}