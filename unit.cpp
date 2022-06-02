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

    SIUnits SIUnits::operator*=(const int &num) {
        temperature *= num;
        length *= num;
        electric_current *= num;
        time *= num;
        mass *= num;
        amount_of_substance *= num;
        intensity *= num;

        return *this;
    }

    SIUnits SIUnits::operator/=(const int &num) {
        temperature *= num * (-1);
        length *= num * (-1);
        electric_current *= num * (-1);
        time *= num * (-1);
        mass *= num * (-1);
        amount_of_substance *= num * (-1);
        intensity *= num * (-1);

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





}