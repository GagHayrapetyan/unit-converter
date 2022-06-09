//
// Created by Gag Hayrapetyan on 02.06.2022.
//

#include <map>
#include <iostream>

#include "exception.h"


#ifndef UNIT_CONVERTER_DATA_H
#define UNIT_CONVERTER_DATA_H

namespace unit_converter {

    class UnitData {
    private:
        static std::map<std::string, Unit *> _unit_data;

        static std::map<std::string, UnitPrefix *> _unit_prefix;

        static bool _is_exist(const std::string &symbol);

    public:
        static bool add_new_unit(std::string symbol,
                                 std::string name,
                                 SIUnits si_unit,
                                 Unit::func_t func);

        static bool add_new_unit(std::string symbol,
                                 std::string name,
                                 SIUnits si_unit,
                                 double coefficient = 1);

        static Unit *find(const std::string &str);

        static std::pair<bool, UnitPrefix *> find_prefix(const std::string &str);

        static void check_if_already_exists(const std::string &str);
    };

}

#endif //UNIT_CONVERTER_DATA_H
