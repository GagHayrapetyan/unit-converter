//
// Created by Gag Hayrapetyan on 02.06.2022.
//

#include <iostream>
#include <string>
#include <functional>
#include <vector>

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

        SIUnits pow(const int &num);

        bool operator==(const SIUnits &obj) const;

        bool operator!=(const SIUnits &obj) const;
    };


    class Unit {
    public:
        enum class Direction {
            TO_SI,
            FROM_SI
        };

        typedef std::function<void(double &, Direction)> func_t;

        Unit(const std::string &symbol,
             const std::string &name,
             SIUnits si_unit,
             func_t func);

        Unit(const std::string &symbol,
             const std::string &name,
             SIUnits si_unit,
             double coefficient = 1);

        Unit(const Unit &obj) = default;

    private:
        std::string _symbol;
        std::string _name;
        SIUnits _si_unit;
        func_t _converter_funcs;

        static func_t _converter(double coefficient);

        friend class MultiUnit;
    };


    class MultiUnit {
    public:
        enum class Operator {
            MULTIPLICATION,
            DIVISION
        };

        MultiUnit();

        MultiUnit &operator=(const Unit &obj);

        MultiUnit operator*=(const Unit &obj);

        MultiUnit operator/=(const Unit &obj);

        bool operator==(const MultiUnit &obj);

        bool operator!=(const MultiUnit &obj);

    private:
        SIUnits _si_unit;
        std::vector<std::pair<Unit::func_t, Operator>> _converter_funcs;
    };

}

#endif //UNIT_CONVERTER_UNIT_H
