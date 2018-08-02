#include "UI/mainwindow.h"
#include "ProjectInfos/configs.h"
#include "ProjectInfos/projectinfos.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    auto returnValue(a.exec());

    if(returnValue == 0)
    {
        ProjectInfos::instance().save();
        Configs::instance().save();
    }

    return returnValue;
}

/*
#include <iostream>
#include <vector>
#include <string>
#include <chrono>

struct Point
{
    float x, y, z;
    Point& operator+=(const Point & other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }
};

void execVector(unsigned int size)
{
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<Point> v{size};

    auto step1 = std::chrono::high_resolution_clock::now();

    for(unsigned int i(0) ; i < size ; i++)
        v[i] = {i, i+1, i+2};

    auto step2 = std::chrono::high_resolution_clock::now();

    Point p{0, 0, 0};
    for(unsigned int i(0) ; i < size ; i++)
        p += v[i];

    auto step3 = std::chrono::high_resolution_clock::now();

    std::cout << "---- Vector ---- size " << size << std::endl;
    std::cout << "Allocation " << std::chrono::duration<double>(step1-start).count() << "s" << std::endl;
    std::cout << "Fill " << std::chrono::duration<double>(step2-step1).count() << "s" << std::endl;
    std::cout << "Use " << std::chrono::duration<double>(step3-step2).count() << "s" << std::endl;
    std::cout << "Total " << std::chrono::duration<double>(step3-start).count() << "s" << std::endl;
    std::cout << p.x << " " << p.y << " " << p.z << std::endl << std::endl;
}

void execTab(unsigned int size)
{
    auto start = std::chrono::high_resolution_clock::now();

    Point* v = new Point[size];

    auto step1 = std::chrono::high_resolution_clock::now();

    for(unsigned int i(0) ; i < size ; i++)
        v[i] = {i, i+1, i+2};

    auto step2 = std::chrono::high_resolution_clock::now();

    Point p{0, 0, 0};
    for(unsigned int i(0) ; i < size ; i++)
        p += v[i];

    auto step3 = std::chrono::high_resolution_clock::now();

    std::cout << "---- Array ---- size " << size << std::endl;
    std::cout << "Allocation " << std::chrono::duration<double>(step1-start).count() << "s" << std::endl;
    std::cout << "Fill " << std::chrono::duration<double>(step2-step1).count() << "s" << std::endl;
    std::cout << "Use " << std::chrono::duration<double>(step3-step2).count() << "s" << std::endl;
    std::cout << "Total " << std::chrono::duration<double>(step3-start).count() << "s" << std::endl;
    std::cout << p.x << " " << p.y << " " << p.z << std::endl << std::endl;

    delete[] v;
}

int main()
{
    execVector(100000);
    execTab(100000);

    execVector(1000000);
    execTab(1000000);

    execVector(10000000);
    execTab(10000000);

    execVector(100000000);
    execTab(100000000);
}
*/
