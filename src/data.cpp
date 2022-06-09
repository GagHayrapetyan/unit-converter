//
// Created by Gag Hayrapetyan on 02.06.2022.
//

#include "unit.h"

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
            {"m",   new Unit("m", "meter", {.T=0, .l=1, .I=0, .t=0, .m=0, .n=0, .i=0})},
            {"kg",  new Unit("kg", "kilogram", {.T=0, .l=0, .I=0, .t=0, .m=1, .n=0, .i=0})},
            {"s",   new Unit("s", "second", {.T=0, .l=0, .I=0, .t=1, .m=0, .n=0, .i=0})},
            {"A",   new Unit("A", "ampere", {.T=0, .l=0, .I=1, .t=0, .m=0, .n=0, .i=0})},
            {"K",   new Unit("K", "kelvin", {.T=1, .l=0, .I=0, .t=0, .m=0, .n=0, .i=0})},
            {"mol", new Unit("mol", "mole", {.T=0, .l=0, .I=0, .t=0, .m=0, .n=1, .i=0})},
            {"cd",  new Unit("cd", "candela", {.T=0, .l=0, .I=0, .t=0, .m=0, .n=0, .i=1})},

            {"Hz",  new Unit("Hz", "hertz", {.T=0, .l=0, .I=0, .t=-1, .m=0, .n=0, .i=0})},
            {"N",   new Unit("N", "newton", {.T=0, .l=1, .I=0, .t=-2, .m=1, .n=0, .i=0})},
            {"Pa",  new Unit("Pa", "pascal", {.T=0, .l=-1, .I=0, .t=-2, .m=1, .n=0, .i=0})},
            {"J",   new Unit("J", "joule", {.T=0, .l=2, .I=0, .t=-2, .m=1, .n=0, .i=0})},
            {"W",   new Unit("W", "watt", {.T=0, .l=2, .I=0, .t=-3, .m=1, .n=0, .i=0})},
            {"C",   new Unit("C", "coulomb", {.T=0, .l=0, .I=1, .t=1, .m=0, .n=0, .i=0})},
            {"V",   new Unit("V", "volt", {.T=0, .l=2, .I=-1, .t=-3, .m=1, .n=0, .i=0})},
            {"Ω",   new Unit("Ω", "ohm", {.T=0, .l=2, .I=-2, .t=-3, .m=1, .n=0, .i=0})},
            {"S",   new Unit("S", "siemens", {.T=0, .l=-2, .I=2, .t=3, .m=-1, .n=0, .i=0})},
            {"F",   new Unit("F", "farad", {.T=0, .l=-2, .I=2, .t=4, .m=-1, .n=0, .i=0})},
            {"T",   new Unit("T", "tesla", {.T=0, .l=0, .I=-1, .t=-2, .m=1, .n=0, .i=0})},
            {"Wb",  new Unit("Wb", "weber", {.T=0, .l=2, .I=-1, .t=-2, .m=1, .n=0, .i=0})},
            {"H",   new Unit("H", "henry", {.T=0, .l=2, .I=-2, .t=-2, .m=1, .n=0, .i=0})},
            {"°C",  new Unit("°C", "celsius", {.T=1, .l=0, .I=0, .t=0, .m=0, .n=0, .i=0},
                             [](double &v, Unit::Direction dir) {
                                 if (dir == Unit::Direction::TO_SI) {
                                     v += 273.15;
                                 } else {
                                     v -= 273.15;
                                 }
                             })},
            {"lm",  new Unit("lm", "lumen", {.T=0, .l=0, .I=0, .t=0, .m=0, .n=0, .i=1})},
            {"lx",  new Unit("lx", "lux", {.T=0, .l=-2, .I=0, .t=0, .m=0, .n=0, .i=1})},
            {"Bq",  new Unit("Bq", "becquerel", {.T=0, .l=0, .I=0, .t=-1, .m=0, .n=0, .i=0})},
            {"Gy",  new Unit("Gy", "gray", {.T=0, .l=2, .I=0, .t=-2, .m=0, .n=0, .i=0})},
            {"Sv",  new Unit("Sv", "sievert", {.T=0, .l=2, .I=0, .t=-2, .m=0, .n=0, .i=0})},
            {"kat", new Unit("kat", "katal", {.T=0, .l=0, .I=0, .t=-1, .m=0, .n=1, .i=0})},

            {"°F",  new Unit("°F", "fahrenheit", {.T=1, .l=0, .I=0, .t=0, .m=0, .n=0, .i=0},
                             [](double &v, Unit::Direction dir) {
                                 if (dir == Unit::Direction::TO_SI) {
                                     v = double((v - 32) * 5) / 9 + 273.15;
                                 } else {
                                     v = double((v - 273.15) * 9) / 5 + 32;
                                 }
                             })},
            {"th",  new Unit("th", "thou", {.T=0, .l=1, .I=0, .t=0, .m=0, .n=0, .i=0}, 2.54E-5)},
            {"in",  new Unit("in", "inch", {.T=0, .l=1, .I=0, .t=0, .m=0, .n=0, .i=0}, 2.54E-2)},
            {"ft",  new Unit("ft", "foot", {.T=0, .l=1, .I=0, .t=0, .m=0, .n=0, .i=0}, 3.048E-1)},
            {"yd",  new Unit("yd", "yard", {.T=0, .l=1, .I=0, .t=0, .m=0, .n=0, .i=0}, 9.144E-1)},
            {"ch",  new Unit("ch", "chain", {.T=0, .l=1, .I=0, .t=0, .m=0, .n=0, .i=0}, 20.1168)},
            {"fur", new Unit("fur", "furlong", {.T=0, .l=1, .I=0, .t=0, .m=0, .n=0, .i=0}, 20.1168)},
            {"ml",  new Unit("ml", "mile", {.T=0, .l=1, .I=0, .t=0, .m=0, .n=0, .i=0}, 1609.344)},
            {"lea", new Unit("lea", "league", {.T=0, .l=1, .I=0, .t=0, .m=0, .n=0, .i=0}, 4828.032)},

            {"bar", new Unit("bar", "bar", {.T=0, .l=-1, .I=0, .t=-2, .m=1, .n=0, .i=0}, 1E5)},
            {"min", new Unit("min", "minute", {.T=0, .l=0, .I=0, .t=1, .m=0, .n=0, .i=0}, 60)},
            {"h",   new Unit("h", "hour", {.T=0, .l=0, .I=0, .t=1, .m=0, .n=0, .i=0}, 3600)},
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

    void UnitData::check_if_already_exists(const std::string &str) {
        auto it = UnitData::_unit_data.find(str);

        if (it != UnitData::_unit_data.end()) {
            throw Exception("Unit " + str + " already exist !");
        }
    }
}