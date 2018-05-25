#pragma once

#include <utility>
#include <cmath>
#include <exception>
#include <sstream>
#include "Base.h"
#include "Container.h"


class Shape : public Printable {
private:
    static size_t count;

public:
    Shape() {
        count++;
    }

    Shape(const Shape &other) {
        count++;
    }

    virtual ~Shape() {
        count--;
    }

    static size_t getCount() {
        return count;
    }
};

size_t Shape::count = 0;


class Point : public Shape {
private:

    double xx;
    double yy;

public:
    Point(const double &getX, const double &getY) : xx(getX), yy(getY) {}

    double getX() const {
        return xx;
    }

    double getY() const {
        return yy;
    }

    double distance(const Point &other) {
        double getX = xx - other.getX();
        double getY = yy - other.getY();
        return sqrt(xx * xx + yy * yy);
    }

    std::string toString() const override {
        return "(" + std::to_string(xx) + "; " + std::to_string(yy) + ")";
    }
};


class Circle : public Shape {
private:
	
	Point center;
    double radius;
	const double PI = 3.14;

public:
    class not_positive_radius : public std::logic_error {
    public:
        not_positive_radius() : logic_error("Radius must be a positive number.") {}
    };

    Circle(const Point &center, const double &radius) : center(center), radius(radius) {
        if (radius <= 0) {
            throw not_positive_radius();
        }
	};

    Point getCenter() const {
        return center;
	};

    double getRadius() const {
        return radius;
	};

    double getPerimeter() const {
        return 2 * PI * radius;
	};

    double getArea() const {
        return PI * radius * radius;
	};

    std::string toString() const override {
        return "Circle with the center at " + center.toString() + "and the radius of " + std::to_string(radius);
	};
};


class Rectangle : public Shape {
private:

    Point topLeft;
    Point bottomRight;

public:
    class wrong_diagonal_points : public std::logic_error {
    public:
        wrong_diagonal_points() :
                logic_error("To define a rectangle a top left and a bottom right points must be used.") {}
    };

    Rectangle(const Point &topLeft, const Point &bottomRight) : topLeft(topLeft), bottomRight(bottomRight) {
        if (topLeft.getX() >= bottomRight.getX()) {
            throw wrong_diagonal_points();
        }
        if (topLeft.getY() <= bottomRight.getY()) {
            throw wrong_diagonal_points();
        }
    }

    double getWidth() const {
        return bottomRight.getX() - topLeft.getX();
    }

    double getHeight() const {
        return topLeft.getY() - bottomRight.getY();
    }

    double getArea() const {
        return getWidth() * getHeight();
    }

    double getPerimeter() const {
        return 2 * (getWidth() + getHeight());
    }

    std::string toString() const override {
        return "Rectangle as defined by it's top left point at " + topLeft.toString()
               + "and a bottom right point at " + bottomRight.toString();
    }
};


class Square : public Shape {
private:

    Point topLeft;
    double side;

public:
    class not_positive_side_length : public std::logic_error {
    public:
        not_positive_side_length() : logic_error("Side lenght must be a positive number.") {}
    };

    Square(const Point &topLeft, const double &side) : topLeft(topLeft), side(side) {
        if (side < 0) {
            throw not_positive_side_length();
        }
    }

    double getSide() const {
        return side;
    }

    double getArea() const {
        return side * side;
    }

    double getPerimeter() const {
        return 4 * side;
    }

    std::string toString() const override {
        return "Square with top left point at " + topLeft.toString()
               + " and a side with a length of " + std::to_string(side);
    }
};


class Polyline : public Shape {
private:

    Container<Point> vertices;
    double length;

public:
    Polyline() : length(0) {};

    void addPoint(const Point &point) {
        if (!vertices.is_empty()) {
            length += vertices.getBack().distance(point);
        }
        vertices.push_back(point);
    }

    double getLength() {
        return length;
    }

    std::string toString() const override {
        if (vertices.is_empty()) {
            return "The polyline is empty.";
        }
        std::stringstream ss;
        ss << "Polyline with a length of " << length << " and defined by it's points: " << this->vertices.getFront();

        for (auto i = ++vertices.begin(); i != vertices.end(); ++i) {
            ss << ", " << *i;
        }

        return ss.str();
    }
};


class Polygon : public Shape {
private:

    Container<Point> vertices;

public:
    Polygon() = default;

    void addPoint(const Point &point) {
        vertices.push_back(point);
    }

    std::string toString() const override {
        if (vertices.is_empty()) {
            return "The polygon is empty.";
        }
        std::stringstream ss;
        ss << "Polygon as defined by it's vertices: " << vertices.getFront();
        for (auto i = ++vertices.begin(); i != vertices.cend(); ++i) {
            ss << ", " << *i;
        }

        return ss.str();
    }
};
