//
// Created by Gag Hayrapetyan on 02.06.2022.
//


#include "unit.h"

namespace unit_converter {

    SIUnits SIUnits::operator+(const SIUnits &obj) {
        temperature += obj.temperature;
        length += obj.length;
        electric_current += obj.electric_current;
        time += obj.time;
        mass += obj.mass;
        amount_of_substance += obj.amount_of_substance;
        intensity += obj.intensity;

        return *this;
    }

    SIUnits SIUnits::operator*(const int &num) {
        temperature *= num;
        length *= num;
        electric_current *= num;
        time *= num;
        mass *= num;
        amount_of_substance *= num;
        intensity *= num;

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


    Unit::Unit(std::string symbol,
               std::string name,
               double coefficient,
               double offset,
               unit_converter::SIUnits si_units) : _name(name),
                                                   _symbol(symbol),
                                                   _coefficient(coefficient),
                                                   _offset(offset),
                                                   _si_units(si_units) {

    }

    Unit::Unit(const Unit &obj) : _name(obj._name),
                                  _symbol(obj._symbol),
                                  _coefficient(obj._coefficient),
                                  _offset(obj._offset),
                                  _si_units(obj._si_units) {

    }

}