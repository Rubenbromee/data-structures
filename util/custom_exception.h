#ifndef CUSTOM_EXCEPTION_H
#define CUSTOM_EXCEPTION_H

#include <iostream>
#include <exception>
#include <string>

// To be able to write custom exceptions, this class was created
// I personally don't like this pattern but it's the way custom exceptions are created in C++
class custom_exception : public std::exception {
    private:
        std::string message;
    public:
        explicit custom_exception(const std::string& msg) : message(msg) {}
    
    virtual const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif