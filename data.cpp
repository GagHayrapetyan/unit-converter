//
// Created by Gag Hayrapetyan on 02.06.2022.
//

#include "data.h"

namespace unit_converter {

    const std::map<std::string, Unit *>  UnitData::m = {
            {"m",    new Unit("m", "meter", {.length=1})},
            {"kg",   new Unit("kg", "kilogram", {.mass=1})},
            {"s",    new Unit("s", "second", {.time=1})},
            {"A",    new Unit("A", "ampere", {.electric_current=1})},
            {"K",    new Unit("K", "kelvin", {.temperature=1})},
            {"mol",  new Unit("mol", "mole", {.amount_of_substance=1})},
            {"cd",   new Unit("cd", "candela", {.intensity=1})},

            {"inch", new Unit("in", "inch", {.length = 1}, 2.54E-2)},
            {"km",   new Unit("km", "kilometer", {.length = 1}, 1E+3)}
    };

    Unit *UnitData::find(const std::string &str) {
        auto it = UnitData::m.find(str);

        if (it == UnitData::m.find(str)) {
            throw std::runtime_error("Unit not found");
        }

        return it->second;
    }
}