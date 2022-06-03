//
// Created by Gag Hayrapetyan on 03.06.2022.
//

#include <iostream>
#include <exception>
#include <string>


#ifndef UNIT_CONVERTER_EXCEPTION_H
#define UNIT_CONVERTER_EXCEPTION_H

namespace unit_converter {

    class Exception : public std::exception {
    public:
        explicit Exception(std::string message);

        explicit Exception(const char *message);

        const char *what() const noexcept override;

    protected:
        std::string _msg;

    };

}

#endif //UNIT_CONVERTER_EXCEPTION_H
