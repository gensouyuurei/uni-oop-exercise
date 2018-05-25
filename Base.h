#pragma once

#include <string>
#include <ostream>

class Printable {
public:
    virtual std::string toString() const = 0;

   friend std::ostream &operator<<(std::ostream &os, const Printable &printable);
};

std::ostream &operator<<(std::ostream &os, const Printable &printable) {
    os << printable.toString();
    return os;
}


class Named : public Printable {
protected:
    std::string name_;

public:
    explicit Named(std::string name) : name_(name) {}

    std::string toString() const override {
        return name_;
    }
};
