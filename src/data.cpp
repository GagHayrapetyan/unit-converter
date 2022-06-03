//
// Created by Gag Hayrapetyan on 02.06.2022.
//

#include "data.h"

namespace unit_converter {

    std::map<std::string, Unit *>  UnitData::_unit_data = {
            {"m",    new Unit("m", "meter",
                              {.temperature=0, .length=1, .electric_current=0, .time=0, .mass=0, .amount_of_substance=0, .intensity=0})},
            {"kg",   new Unit("kg", "kilogram",
                              {.temperature=0, .length=0, .electric_current=0, .time=0, .mass=1, .amount_of_substance=0, .intensity=0})},
            {"s",    new Unit("s", "second",
                              {.temperature=0, .length=0, .electric_current=0, .time=1, .mass=0, .amount_of_substance=0, .intensity=0})},
            {"A",    new Unit("A", "ampere",
                              {.temperature=0, .length=0, .electric_current=1, .time=0, .mass=0, .amount_of_substance=0, .intensity=0})},
            {"K",    new Unit("K", "kelvin",
                              {.temperature=1, .length=0, .electric_current=0, .time=0, .mass=0, .amount_of_substance=0, .intensity=0})},
            {"mol",  new Unit("mol", "mole",
                              {.temperature=0, .length=0, .electric_current=0, .time=0, .mass=0, .amount_of_substance=1, .intensity=0})},
            {"cd",   new Unit("cd", "candela",
                              {.temperature=0, .length=0, .electric_current=0, .time=0, .mass=0, .amount_of_substance=0, .intensity=1})},

            {"inch", new Unit("in", "inch",
                              {.temperature=0, .length=1, .electric_current=0, .time=0, .mass=0, .amount_of_substance=0, .intensity=0},
                              2.54E-2)},
            {"km",   new Unit("km", "kilometer",
                              {.temperature=0, .length=1, .electric_current=0, .time=0, .mass=0, .amount_of_substance=0, .intensity=0},
                              1E+3)},
            {"h",    new Unit("h", "hour",
                              {.temperature=0, .length=0, .electric_current=0, .time=1, .mass=0, .amount_of_substance=0, .intensity=0},
                              3600)},
            {"Hz",   new Unit("Hz", "hertz",
                              {.temperature=0, .length=0, .electric_current=0, .time=-1, .mass=0, .amount_of_substance=0, .intensity=0})},
            {"N",    new Unit("N", "newton",
                              {.temperature=0, .length=1, .electric_current=0, .time=-2, .mass=1, .amount_of_substance=0, .intensity=0})},
            {"Pa",   new Unit("Pa", "pascal",
                              {.temperature=0, .length=-1, .electric_current=0, .time=-2, .mass=1, .amount_of_substance=0, .intensity=0})},
            {"°C",   new Unit("°C", "celsius",
                              {.temperature=1, .length=0, .electric_current=0, .time=0, .mass=0, .amount_of_substance=0, .intensity=0},
                              [](double &v, Unit::Direction dir) {
                                  if (dir == Unit::Direction::TO_SI) {
                                      v += 273.15;
                                  } else {
                                      v -= 273.15;
                                  }
                              })},

    };

    Unit *UnitData::find(const std::string &str) {
        auto it = UnitData::_unit_data.find(str);

        if (it == UnitData::_unit_data.end()) {
            throw Exception("Unit " + str + " doesn't exist !");
        }

        return it->second;
    }

    bool UnitData::add_new_unit(std::string symbol, std::string name, SIUnits si_unit, Unit::func_t func) {
        if (!_is_exist(symbol)) {
            UnitData::_unit_data.insert({symbol, new Unit(symbol, name, si_unit, func)});

            return true;
        }

        return false;
    }

    bool UnitData::add_new_unit(std::string symbol, std::string name, SIUnits si_unit, double coefficient) {
        if (!_is_exist(symbol)) {
            UnitData::_unit_data.insert({symbol, new Unit(symbol, name, si_unit, coefficient)});

            return true;
        }

        return false;
    }

    bool UnitData::_is_exist(const std::string &symbol) {
        auto it = UnitData::_unit_data.find(symbol);

        return it != UnitData::_unit_data.end();
    }
}