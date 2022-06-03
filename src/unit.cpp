//
// Created by Gag Hayrapetyan on 02.06.2022.
//


#include "unit.h"

namespace unit_converter {

    SIUnits SIUnits::operator+=(const SIUnits &obj) {
        temperature += obj.temperature;
        length += obj.length;
        electric_current += obj.electric_current;
        time += obj.time;
        mass += obj.mass;
        amount_of_substance += obj.amount_of_substance;
        intensity += obj.intensity;

        return *this;
    }

    SIUnits SIUnits::operator-=(const SIUnits &obj) {
        temperature -= obj.temperature;
        length -= obj.length;
        electric_current += obj.electric_current;
        time -= obj.time;
        mass -= obj.mass;
        amount_of_substance -= obj.amount_of_substance;
        intensity -= obj.intensity;

        return *this;
    }

    SIUnits SIUnits::pow(const int &num) {
        temperature += num;
        length += num;
        electric_current += num;
        time += num;
        mass += num;
        amount_of_substance += num;
        intensity += num;

        return *this;
    }

    bool SIUnits::operator==(const SIUnits &obj) const {
        return temperature == obj.temperature &&
               length == obj.length &&
               electric_current == obj.electric_current &&
               time == obj.time &&
               mass == obj.mass &&
               amount_of_substance == obj.amount_of_substance &&
               intensity == obj.intensity;
    }

    bool SIUnits::operator!=(const SIUnits &obj) const {
        return !operator==(obj);
    }

    std::ostream &operator<<(std::ostream &os, const SIUnits &obj) {
        return os << obj.temperature << " " << obj.mass << " " << obj.amount_of_substance << " " << obj.electric_current
                  << " " << obj.intensity << " " << obj.length << " " << obj.time << std::endl;
    }


    Unit::Unit(const std::string &symbol,
               const std::string &name,
               SIUnits si_unit,
               Unit::func_t func) : _symbol(symbol),
                                    _name(name),
                                    _si_unit(si_unit),
                                    _converter_funcs(func) {
    }


    Unit::Unit(const std::string &symbol,
               const std::string &name,
               SIUnits si_unit,
               double coefficient) : Unit(symbol, name, si_unit, _converter(coefficient)) {

    }

    Unit::func_t Unit::_converter(double coefficient) {
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

    bool MultiUnit::operator==(const MultiUnit &obj) {
//        std::cout << _si_unit << obj._si_unit;
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