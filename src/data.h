//
// Created by Gag Hayrapetyan on 02.06.2022.
//

#include <map>
#include <iostream>
#include <exception>

#include "unit.h"
#include "exception.h"


#ifndef UNIT_CONVERTER_DATA_H
#define UNIT_CONVERTER_DATA_H

namespace unit_converter {

    class UnitData {
    private:
        static std::map<std::string, Unit *> _unit_data;

    public:
        static void add_new_unit(std::string symbol,
                                 std::string name,
                                 SIUnits si_unit,
                                 Unit::func_t func);

        static void add_new_unit(std::string symbol,
                                 std::string name,
                                 SIUnits si_unit,
                                 double coefficient);

        static Unit *find(const std::string &str);
    };

}

#endif //UNIT_CONVERTER_DATA_H
