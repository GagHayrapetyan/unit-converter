//
// Created by Gag Hayrapetyan on 02.06.2022.
//


#include "unit.h"

#include "data.h"

namespace unit_converter {

    SIUnits SIUnits::operator+=(const SIUnits &obj) {
        T += obj.T;
        i += obj.i;
        I += obj.I;
        t += obj.t;
        m += obj.m;
        n += obj.n;
        i += obj.i;

        return *this;
    }

    SIUnits SIUnits::operator-=(const SIUnits &obj) {
        T -= obj.T;
        i -= obj.i;
        I += obj.I;
        t -= obj.t;
        m -= obj.m;
        n -= obj.n;
        i -= obj.i;

        return *this;
    }

    SIUnits SIUnits::pow(const int &num) {
        T += num;
        i += num;
        I += num;
        t += num;
        m += num;
        n += num;
        i += num;

        return *this;
    }

    bool SIUnits::operator==(const SIUnits &obj) const {
        return T == obj.T &&
               i == obj.i &&
               I == obj.I &&
               t == obj.t &&
               m == obj.m &&
               n == obj.n &&
               i == obj.i;
    }

    bool SIUnits::operator!=(const SIUnits &obj) const {
        return !operator==(obj);
    }

    std::ostream &operator<<(std::ostream &os, const SIUnits &obj) {
        return os << obj.T << " " << obj.m << " " << obj.n << " " << obj.I
                  << " " << obj.i << " " << obj.i << " " << obj.t << std::endl;
    }


    UnitPrefix::UnitPrefix(const std::string &symbol,
                           const std::string &name,
                           double factor) : _symbol(symbol),
                                            _name(name),
                                            _factor(factor),
                                            _func(converter(factor)) {

    }


    Unit::Unit(const std::string &symbol,
               const std::string &name,
               SIUnits si_unit,
               Unit::func_t func) : _symbol(symbol),
                                    _name(name),
                                    _si_unit(si_unit),
                                    _converter_funcs(func) {
        UnitData::find(symbol);
    }


    Unit::Unit(const std::string &symbol,
               const std::string &name,
               SIUnits si_unit,
               double coefficient) : Unit(symbol, name, si_unit, converter(coefficient)) {

    }

    Unit::func_t UnitInterface::converter(double coefficient) {
        return [coefficient](double &value, Direction op) {
            if (op == Direction::TO_SI) {
                value *= coefficient;
            } else {
                value /= coefficient;
            }
        };
    }


    MultiUnit::MultiUnit() : _si_unit({}),
                             _converter_funcs({}) {

    }

    MultiUnit MultiUnit::operator*=(const Unit &obj) {
        _si_unit += obj._si_unit;
        _converter_funcs.emplace_back(obj._converter_funcs, Operator::MULTIPLICATION);

        return *this;
    }

    MultiUnit MultiUnit::operator/=(const Unit &obj) {
        _si_unit -= obj._si_unit;
        _converter_funcs.emplace_back(obj._converter_funcs, Operator::DIVISION);

        return *this;
    }

    MultiUnit &MultiUnit::operator=(const Unit &obj) {
        _si_unit = obj._si_unit;
        _converter_funcs.emplace_back(obj._converter_funcs, Operator::MULTIPLICATION);

        return *this;
    }

    MultiUnit MultiUnit::operator*=(const UnitPrefix &obj) {
        _converter_funcs.emplace_back(obj._func, Operator::MULTIPLICATION);

        return *this;
    }

    MultiUnit MultiUnit::operator/=(const UnitPrefix &obj) {
        _converter_funcs.emplace_back(obj._func, Operator::DIVISION);

        return *this;
    }

    MultiUnit &MultiUnit::operator=(const UnitPrefix &obj) {
        _converter_funcs.emplace_back(obj._func, Operator::MULTIPLICATION);

        return *this;
    }

    bool MultiUnit::operator==(const MultiUnit &obj) {
        return _si_unit == obj._si_unit;
    }

    bool MultiUnit::operator!=(const MultiUnit &obj) {
        return !operator==(obj);
    }

    Unit::Direction MultiUnit::_detect_dir(const Unit::Direction &dir, const MultiUnit::Operator &op) {
        if (dir == Unit::Direction::TO_SI && op == Operator::MULTIPLICATION) {
            return Unit::Direction::TO_SI;
        }

        if (dir == Unit::Direction::TO_SI && op == Operator::DIVISION) {
            return Unit::Direction::FROM_SI;
        }

        if (dir == Unit::Direction::FROM_SI && op == Operator::MULTIPLICATION) {
            return Unit::Direction::FROM_SI;
        }

        if (dir == Unit::Direction::FROM_SI && op == Operator::DIVISION) {
            return Unit::Direction::TO_SI;
        }

        return Unit::Direction::TO_SI;
    }

    void MultiUnit::_convert(double &value,
                             const std::vector<std::pair<Unit::func_t, Operator>> &f_list,
                             const Unit::Direction &dir) {
        for (auto &[f, o]: f_list) {
            f(value, _detect_dir(dir, o));
        }
    }

    double MultiUnit::convert(double value, Unit::Direction dir) {
        _convert(value, _converter_funcs, dir);

        return value;
    }

    bool MultiUnit::is_same_dimension(const MultiUnit &unit) {
        return unit._si_unit != _si_unit;
    }


}