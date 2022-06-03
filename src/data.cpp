//
// Created by Gag Hayrapetyan on 02.06.2022.
//

#include "data.h"

namespace unit_converter {

    const std::map<std::string, Unit *>  UnitData::m = {
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
        auto it = UnitData::m.find(str);

        if (it == UnitData::m.end()) {
            throw Exception("Unit doesn't exist !");
        }

        return it->second;
    }
}