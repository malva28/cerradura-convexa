#include <elem_geometricos.h>
#include <iostream>


int main() {
    Punto<int> p1{ 1,2 };
    Punto<double> p2 {0.3, 5.8};
    Punto<double> p3 { p1+p2 };

    Vector<double> v1{ p2 };
    Vector<double> v2{ v1*2 };
    const Poligono<float> pol1{{-3.4, 0.4}, {2, -0.5}, {-1.6, -0.5}};
    const Segmento<int> s1{ 1,0,5,0 };
    const Segmento<float> s2{-3.4f, 0.4f, 2.0f, -0.5f };

    Segmento<float> s3;
    if (1)
    {
        const Segmento<float> s4{1.0f,2.0f,3.0f,4.0f};
        s3 = s4.swapSegmento();
    }

    std::cout << "Punto " << p3 << '\n';
    std::cout << "Vector " << v2 << '\n';
    std::cout << "Poligono " << pol1 << '\n';
    std::cout << "Segmento " << s1 << '\n';
    std::cout << "Segmento<long> Length " << s2.length() << '\n';
    return 0;
}
