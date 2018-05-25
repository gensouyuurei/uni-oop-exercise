#pragma once

#include <random>
#include "Shapes.h"

class Factory {
    static std::random_device random_device;
    static std::default_random_engine random_engine;

    static double generateReal(double a, double b) {
        std::uniform_real_distribution<double> dist_real(a, b);
        return dist_real(random_engine);
    }

    static int generateInteger(int a, int b) {
        std::uniform_int_distribution<int> dist_int(a, b);
        return dist_int(random_engine);
    }

    static Point generatePoint() {
        return Point(generateReal(-10, 10), generateReal(-10, 10));
    }

public:
    static Point *getPoint() {
        return new Point(generateReal(-10, 10), generateReal(-10, 10));
    }

    static Circle *getCircle() {
        return new Circle(generatePoint(), generateReal(1, 10));
    }

    static Rectangle *getRectangle() {
		double length = generateReal(1, 10);
		double height = generateReal(1, 10);
		Point topLeft = generatePoint();
		Point bottomRight(topLeft.getX() + length, topLeft.getY() - height);

        return new Rectangle(topLeft, bottomRight);
    }

    static Square *getSquare() {
        return new Square(generatePoint(), generateReal(1, 10));
    }

    static Polyline *getPolyline() {
        Polyline *polyline = new Polyline;
        int n = generateInteger(3, 10);

        for (int i = 0; i < n; ++i) {
            polyline->addPoint(generatePoint());
        }
        return polyline;
    }

    static Polygon *getPolygon() {
        Polygon *polygon = new Polygon;
        int n = generateInteger(3, 10);

        for (int i = 0; i < n; ++i) {
            polygon->addPoint(generatePoint());
        }
        return polygon;
    }


    static Shape *getShape() {
        int shp = generateInteger(0, 5);
        switch (shp) {
            case 0:
                return getPoint();
            case 1:
                return getCircle();
            case 2:
                return getRectangle();
            case 3:
                return getSquare();
            case 4:
                return getPolyline();
            case 5:
                return getPolygon();
        }
        return nullptr;
    }
};

std::random_device Factory::random_device;
std::default_random_engine Factory::random_engine(Factory::random_device());