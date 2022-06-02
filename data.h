//
// Created by Gag Hayrapetyan on 02.06.2022.
//

#include <map>
#include <iostream>
#include <tuple>

#include "unit.h"


#ifndef UNIT_CONVERTER_DATA_H
#define UNIT_CONVERTER_DATA_H

namespace unit_converter {

    class UnitData {
    public:
        static std::map<std::string, Unit *> m;

        static std::tuple<bool,Unit*> find(const std::string &str);
    };

}

#endif //UNIT_CONVERTER_DATA_H
