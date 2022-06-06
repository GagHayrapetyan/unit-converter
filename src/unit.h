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
        int T = 0; //temperature
        int l = 0; //length
        int I = 0; //electric current
        int t = 0; //time
        int m = 0; //mass
        int n = 0; //amount of substance
        int i = 0; //intensity

        SIUnits operator+=(const SIUnits &obj);

        SIUnits operator-=(const SIUnits &obj);

        SIUnits pow(const int &num);

        bool operator==(const SIUnits &obj) const;

        bool operator!=(const SIUnits &obj) const;

        friend std::ostream &operator<<(std::ostream &os, const SIUnits &obj);
    };


    class UnitInterface {
    public:
        enum class Direction {
            TO_SI,
            FROM_SI
        };

        typedef std::function<void(double &, Direction)> func_t;

        static func_t converter(double coefficient);
    };


    class UnitPrefix : public UnitInterface {
    public:
        UnitPrefix(const std::string &symbol,
                   const std::string &name,
                   double factor);

    private:
        std::string _symbol;
        std::string _name;
        double _factor;
        func_t _func;

        friend class MultiUnit;
    };


    class Unit : public UnitInterface {
    public:
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

        MultiUnit &operator=(const UnitPrefix &obj);

        MultiUnit operator*=(const UnitPrefix &obj);

        MultiUnit operator/=(const UnitPrefix &obj);

        bool operator==(const MultiUnit &obj);

        bool operator!=(const MultiUnit &obj);

        double convert(double value, Unit::Direction dir);

        bool is_same_dimension(const MultiUnit &unit);

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
