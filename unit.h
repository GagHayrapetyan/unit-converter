//
// Created by Gag Hayrapetyan on 02.06.2022.
//

#include <iostream>
#include <string>
#include <functional>

#ifndef UNIT_CONVERTER_UNIT_H
#define UNIT_CONVERTER_UNIT_H

namespace unit_converter {

    struct SIUnits {
        uint8_t temperature = 0;
        uint8_t length = 0;
        uint8_t electric_current = 0;
        uint8_t time = 0;
        uint8_t mass = 0;
        uint8_t amount_of_substance = 0;
        uint8_t intensity = 0;

        SIUnits operator+=(const SIUnits &obj);

        SIUnits operator-=(const SIUnits &obj);

        SIUnits operator*=(const int &num);

        SIUnits operator*=(const SIUnits &obj) = delete;

        SIUnits operator/=(const int &num);

        SIUnits operator/=(const SIUnits &obj) = delete;

        bool operator==(const SIUnits &obj) const;

        bool operator!=(const SIUnits &obj) const;
    };


    class Unit {
    public:
        enum class Direction {
            TO_SI,
            FROM_SI
        };

        Unit(const std::string &symbol,
             const std::string &name,
             SIUnits si_unit,
             std::function<void(double &, Direction)> func);

        Unit(const std::string &symbol,
             const std::string &name,
             SIUnits si_unit,
             double coefficient = 1);

    private:
        std::string _symbol;
        std::string _name;
        SIUnits _si_unit;
        std::function<void(double &, Direction)> _converter_func;

        static std::function<void(double &, Direction)> _converter(double coefficient);
    };


}

#endif //UNIT_CONVERTER_UNIT_H
