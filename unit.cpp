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
               std::function<void(double &, Direction)> func) : _symbol(symbol),
                                                                _name(name),
                                                                _si_unit(si_unit),
                                                                _converter_funcs({func}) {
    }


    Unit::Unit(const std::string &symbol,
               const std::string &name,
               SIUnits si_unit,
               double coefficient) : Unit(symbol, name, si_unit, _converter(coefficient)) {

    }

    std::function<void(double &, Unit::Direction)> Unit::_converter(double coefficient) {
        return [coefficient](double &value, Direction dir) {
            if (dir == Direction::TO_SI) {
                value *= coefficient;
            } else {
                value /= coefficient;
            }
        };
    }

    void Unit::_convert(double &value,
                        const std::vector<std::function<void(double &, Direction)>> &funcs,
                        Direction dir) {
        for (auto &i: funcs) {
            i(value, dir);
        }
    }

    double Unit::convert(double value) {
        _convert(value, _converter_funcs, Direction::TO_SI);

        return value;
    }

    double Unit::convert(double value, const Unit &unit) {
        _convert(value, _converter_funcs, Direction::TO_SI);
        _convert(value, unit._converter_funcs, Direction::FROM_SI);

        return value;
    }


}