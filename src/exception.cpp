//
// Created by Gag Hayrapetyan on 03.06.2022.
//

#include "exception.h"

namespace unit_converter {

    Exception::Exception(std::string message)
            : _msg(std::move(message)) {

    }

    Exception::Exception(const char *message)
            : _msg(message) {}


    const char *Exception::what() const noexcept {
        return _msg.c_str();
    }

}