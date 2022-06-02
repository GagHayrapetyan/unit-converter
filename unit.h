//
// Created by Gag Hayrapetyan on 02.06.2022.
//

#include <iostream>
#include <string>


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

        SIUnits operator+(const SIUnits &obj);

        SIUnits operator*(const int &num);

        SIUnits operator*(const SIUnits &obj) = delete;

        bool operator==(const SIUnits &obj) const;

        bool operator!=(const SIUnits &obj) const;
    };

    class Unit {
    public:
        Unit(std::string symbol,
             std::string name,
             double coefficient = 1,
             double offset = 0,
             SIUnits si_units = {});

        Unit(std::string symbol,
             std::string name,
             SIUnits si_units = {});

        Unit(const Unit &obj);

    private:
        std::string _symbol;
        std::string _name;
        double _coefficient;
        double _offset;

        SIUnits _si_units;
    };

}

#endif //UNIT_CONVERTER_UNIT_H
