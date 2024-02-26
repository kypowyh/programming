#include <iostream>

using namespace std;

class Box {
private:
    double length;
    double width;
    double height;

public:
    Box() {
        length = 0;
        width = 0;
        height = 0;
    }

    Box(double l, double w, double h) {
        length = l;
        width = w;
        height = h;
    }

    void setLength(double l) { 
        length = l; 
    }
    void setWidth(double w) { 
        width = w; 
    }
    void setHeight(double h) { 
        height = h; 
    }

    double getLength() const { 
        return length; 
    }
    double getWidth() const { 
        return width; 
    }
    double getHeight() const { 
        return height; 
    }

    double Volume() const { 
        return length * width * height; 
    }

    double Surface() const {
        return 2 * (length * width + length * height + width * height);
    }

    string isCube() const {
        if (length == width && width == height)
            return "Это куб";
        else
            return "Это не куб";
    }

    double Diagonal() const {
        return sqrt(pow(length, 2) + pow(width, 2) + pow(height, 2));
    }

    void displayInfo() const {
        cout << "Длина = " << length << endl;
        cout << "Ширина = " << width << endl;
        cout << "Высота = " << height << endl;
        cout << "Объем: " << Volume() << endl;
        cout << "Площадь поверхности: " << Surface() << endl;
        cout << "Проверка на куб: " << isCube() << endl;
        cout << "Длина диагонали: " << Diagonal() << endl;
    }

};

int main() {
    setlocale(LC_ALL, "rus");

    Box myBox(2.5, 3.0, 4.0);

    myBox.displayInfo();

    myBox.setLength(3.0);
    myBox.setWidth(4.0);
    myBox.setHeight(5.0);

    myBox.displayInfo();

    Box box(1, 1, 1);

    box.displayInfo();

    return 0;
}
