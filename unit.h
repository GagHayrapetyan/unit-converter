//
// Created by Gag Hayrapetyan on 02.06.2022.
//

#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <ostream>

#ifndef UNIT_CONVERTER_UNIT_H
#define UNIT_CONVERTER_UNIT_H

namespace unit_converter {

    struct SIUnits {
        int temperature = 0;
        int length = 0;
        int electric_current = 0;
        int time = 0;
        int mass = 0;
        int amount_of_substance = 0;
        int intensity = 0;

        SIUnits operator+=(const SIUnits &obj);

        SIUnits operator-=(const SIUnits &obj);

        SIUnits pow(const int &num);

        bool operator==(const SIUnits &obj) const;

        bool operator!=(const SIUnits &obj) const;

        friend std::ostream &operator<<(std::ostream &os, const SIUnits &obj);
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

        double convert(double value, Unit::Direction dir);

    private:
        SIUnits _si_unit;
        std::vector<std::pair<Unit::func_t, Operator>> _converter_funcs;

        static Unit::Direction _detect_dir(const Unit::Direction &dir, const Operator &op);

        static void _convert(double &value,
                             const std::vector<std::pair<Unit::func_t, Operator>> &f_list,
                             const Unit::Direction &dir);
    };

}

#endif //UNIT_CONVERTER_UNIT_H
