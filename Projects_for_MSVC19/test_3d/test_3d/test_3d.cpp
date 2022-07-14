// test_3d.cpp :

#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstdint>
#include <typeinfo>
#include <memory>
#include <thread>
#include <mutex>
#include "shapeapi.h"


using namespace std;


void Radius(vector< shared_ptr<Circle>>& vShape, int begin, int end, double* sum);
vector<int> Span(uint32_t size, int div);
int Task_execute(vector< shared_ptr<Circle>>& vShape, int div, double* sum);


mutex m;


int main()
{
    vector< shared_ptr<Shape>> vShape;
    vector< shared_ptr<Circle>> vShape2;

    const uint32_t quantity = 100;// 10000000; // Количество элементов
    const uint32_t max = 100; //
    const uint32_t div = 4; // Количество потоков
    const double t = M_Pi / 4; // Параметр


    // 2.
    for (uint32_t i = 0; i < quantity; ++i)
    {
        switch (rand() % 3)
        {
        case 0: vShape.push_back(make_unique < Circle>((rand() % max) + 1)); break;
        case 1: vShape.push_back(make_unique < Ellipse>((rand() % max) + 1, (rand() % max) + 1)); break;
        case 2: vShape.push_back(make_unique < Spiral>((rand() % max) + 1, (rand() % max) + 1)); break;
        }
    }


    // 3.
    for (const auto& x : vShape)
        x->print(t, 1);


    // 4.
    for_each(vShape.cbegin(), vShape.cend(),
        [&vShape2](const auto& c) {if (typeid(*c.get()) == typeid(Circle)) vShape2.push_back(dynamic_pointer_cast<Circle>(c)); });


    // 5.
    sort(vShape2.begin(), vShape2.end(),
        [](const auto& a, const auto& b) {return a->get_radius() < b->get_radius(); });

    cout << endl << "++++++++++++++++++++++++ Circle ++++++++++++++++++++++++ " << endl << endl;

    for (const auto& x : vShape2)
        x->print(t, 1);





    // 6, 8.
    double sum = 0.0;

    Task_execute(vShape2, div, &sum);

    cout << endl << "sum = " << sum << endl;



    //// Проверка связонных указателей
    //for_each(vShape2.begin(), vShape2.end(),
    //    [](auto& c) {c->move(Point(10, -10, 5)); });

    //for (const auto& x : vShape)
    //    x->print(t, 1);



    cin.get();
}







void Radius(vector< shared_ptr<Circle>>& vShape, int begin, int end, double* sum)
{
    double tmp = 0;
    for_each(vShape.cbegin() + begin, vShape.cbegin() + end,
        [&tmp](const auto& c) {tmp += c->get_radius(); });


    m.lock();
    *sum += tmp;
    m.unlock();
}


vector<int> Span(uint32_t size, int div)
{
    int step = size / div;
    vector<int> tmp;

    for (int i = 0; i < div; ++i)
    {
        tmp.push_back(i * step);
        tmp.push_back(i * step + step - 1);
    }
    tmp.back() = size - 1;
    return tmp;
}


int Task_execute(vector< shared_ptr<Circle>>& vShape, int div, double* sum)
{
    vector< thread> vtr;
    vector<int> sp = Span(vShape.size(), div);

    for (uint32_t i = 0; i < sp.size(); i += 2)
        //vtr.push_back(thread(Radius, vector< shared_ptr<Circle>>(vShape.begin() + sp[i], vShape.begin() + sp[i + 1] + 1), sum));
        vtr.push_back(thread(Radius, ref(vShape), sp[i], sp[i + 1] + 1, sum));

    for (auto& x : vtr)
        x.join();

    return 0;
}
