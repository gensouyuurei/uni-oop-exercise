#include <iostream>
#include "Container.h"
#include "Shapes.h"
#include "Factory.h"

using namespace std;


int main() {

    Container<Shape *> shapes;
    for (int i = 0; i < 30; i++) {
        shapes.push_back(Factory::getShape());
    }

    cout << "Amount before cleaning: " << Shape::getCount() << endl;

    cout << endl;

	cout << "Cleaning..." << endl;
    for (Shape *shape : shapes) {
        cout << *shape << endl;
    }

    for (Shape *shape : shapes) {
        delete shape;
    }
    shapes.clear();

    cout << endl;

    cout << "Amount after cleaning: " << Shape::getCount() << endl;

    return 0;
}
