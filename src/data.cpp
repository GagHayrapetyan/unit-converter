//
// Created by Gag Hayrapetyan on 02.06.2022.
//

#include "data.h"

namespace unit_converter {

    std::map<std::string, UnitPrefix *>  UnitData::_unit_prefix = {
            {"y",  new UnitPrefix("y", "yocto", 1E-24)},
            {"z",  new UnitPrefix("z", "zepto", 1E-21)},
            {"a",  new UnitPrefix("a", "atto", 1E-18)},
            {"f",  new UnitPrefix("f", "femto", 1E-15)},
            {"p",  new UnitPrefix("p", "pico", 1E-12)},
            {"n",  new UnitPrefix("n", "nano", 1E-9)},
            {"µ",  new UnitPrefix("µ", "micro", 1E-6)},
            {"m",  new UnitPrefix("m", "milli", 1E-3)},
            {"c",  new UnitPrefix("c", "centi", 1E-2)},
            {"d",  new UnitPrefix("d", "deci", 1E-1)},
            {"da", new UnitPrefix("da", "deca", 1E+1)},
            {"h",  new UnitPrefix("h", "hecto", 1E+2)},
            {"k",  new UnitPrefix("k", "kilo", 1E+3)},
            {"M",  new UnitPrefix("M", "mega", 1E+6)},
            {"G",  new UnitPrefix("G", "giga", 1E+9)},
            {"T",  new UnitPrefix("T", "tera", 1E+12)},
            {"P",  new UnitPrefix("P", "peta", 1E+15)},
            {"E",  new UnitPrefix("E", "exa", 1E+18)},
            {"Z",  new UnitPrefix("Z", "zetta", 1E+21)},
            {"Y",  new UnitPrefix("Y", "yotta", 1E+24)},
    };

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
            {"°F",   new Unit("°F", "fahrenheit",
                              {.temperature=1, .length=0, .electric_current=0, .time=0, .mass=0, .amount_of_substance=0, .intensity=0},
                              [](double &v, Unit::Direction dir) {
                                  if (dir == Unit::Direction::TO_SI) {
                                      v = double((v - 32) * 5) / 9 + 273.15;
                                  } else {
                                      v = double((v - 273.15) * 9) / 5 + 32;
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

    std::pair<bool, UnitPrefix *> UnitData::find_prefix(const std::string &str) {
        auto it = UnitData::_unit_prefix.find(str);

        return {it != UnitData::_unit_prefix.end(), it->second};
    }
}