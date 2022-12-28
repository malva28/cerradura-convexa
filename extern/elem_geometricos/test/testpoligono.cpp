//
// Created by malva on 02-05-21.
//

#include <elem_geometricos.h>
#include <tinytest.h>

/*
 * Defines the polygons that will be tested.
 * You can see how these looks in a 2D plane in the folder img.
 */
namespace setup
{
    const Poligono<double> polA {{   1,1.8}, {-0.3,2.3}, {  -2,2.2 }, {-2.6,1.2}, {-1.6,  1},
                                 {-0.9,1.6}, {-0.2,1.3}, {-0.7,-0.3}, {-1.6,-0.2},{-1.6,0.4},
                                 {-2.5,0.3}, {-1.5,-1.9},{0.02727272727,-1.3}, {1.3,-0.8}};

    const std::vector<Punto<int>> vectorB {{5,0}, {6,4}, {4,5}, {1,5}, {1,0}};
    const Poligono<int> polB {vectorB};

    const Poligono<float> polC{{-3.4, 0.4}, {2, -0.5}, {-1.6, -0.5}};
}

void testPoligonoInit()
{
    std::vector<Punto<double>> cloudA {setup::polA.getPointCloud()};
    std::vector<Punto<int>>    cloudB {setup::polB.getPointCloud()};


    Punto<double> p1A{ -0.3, 2.3 };
    ASSERT_EQUALS(p1A, setup::polA[1]);
    ASSERT_EQUALS(p1A, cloudA[1]);

    Punto<double> p7A{ -0.7, -0.3 };
    ASSERT_EQUALS(p7A, setup::polA[7]);
    ASSERT_EQUALS(p7A, cloudA[7]);

    Punto<double> p12A{ 0.02727272727,-1.3 };
    ASSERT_EQUALS(p12A, setup::polA[12]);
    ASSERT_EQUALS(p12A, cloudA[12]);

    Punto<int> p0B{ 5, 0 };
    ASSERT_EQUALS(p0B, setup::polB[0]);
    ASSERT_EQUALS(p0B, cloudB[0]);

    Punto<int> p3B{ 1,5 };
    ASSERT_EQUALS(p3B, setup::polB[3]);
    ASSERT_EQUALS(p3B, cloudB[3]);

    // test that lenghts are correct as well
    ASSERT_EQUALS(14, setup::polA.getLength());
    ASSERT_EQUALS(5, setup::polB.getLength());
    ASSERT_EQUALS(3, setup::polC.getLength());
}

void testSignedAngle()
{
    const int lenB = 5 ;
    int expectedB[lenB]{ 16, 9, 3, 15, 20 };
    for(int i{}; i < lenB; ++i)
    {
        ASSERT_EQUALS(expectedB[i], setup::polB.signedAngle(i));
    }

}

void testDoubleSignedArea()
{
    int expectedAreaB{ 44 };
    ASSERT_EQUALS(expectedAreaB, setup::polB.doubleSignedArea());

    double expectedAreaA{ 19.11 };
    ASSERT_EQUALS(true, withinEps(expectedAreaA, setup::polA.doubleSignedArea(), 1e-10,1e-10));

    float expectedAreaC{ -3.24f };
    ASSERT_EQUALS(true, withinEps(expectedAreaC, setup::polC.doubleSignedArea(), 1e-7f,1e-7f));
}

void testArea()
{
    double expectedAreaB{ 22 };
    //std::cout << setup::polB.area() << '\n';
    ASSERT_EQUALS(true, withinEps(expectedAreaB, setup::polB.area(), 1e-10,1e-10));

    double expectedAreaA{ 9.555 };
    ASSERT_EQUALS(true, withinEps(expectedAreaA, setup::polA.area(), 1e-10,1e-10));

    double expectedAreaC{ 1.62 };
    ASSERT_EQUALS(true, withinEps(expectedAreaC, setup::polC.area(), 1e-7,1e-7));
}

void testPointInPolygon()
{
    // integer precision
    // point inside
    ASSERT_EQUALS(true, setup::polB.pointInside(Punto<int>{ 2, 1 }));
    // point inside line
    ASSERT_EQUALS(true, setup::polB.pointInside(Punto<int>{ 2, 0 }));
    // point equal to vertex
    ASSERT_EQUALS(true, setup::polB.pointInside(Punto<int>{ 1, 0 }));
    // point outside to the left
    ASSERT_EQUALS(false, setup::polB.pointInside(Punto<int>{ 0, 1 }));
    // point outside to the right
    ASSERT_EQUALS(false, setup::polB.pointInside(Punto<int>{ 6, 1 }));

    // float precision
    ASSERT_EQUALS(true, setup::polC.pointInside(Punto<float>{ -2.0f, 0.0f }));
    ASSERT_EQUALS(true, setup::polC.pointInside(Punto<float>{ 0.0f, -0.5f }));
    ASSERT_EQUALS(true, setup::polC.pointInside(Punto<float>{ -1.6f, -0.5f }));
    ASSERT_EQUALS(false, setup::polC.pointInside(Punto<float>{ -1.6000001f, -0.5f }));
    ASSERT_EQUALS(false, setup::polC.pointInside(Punto<float>{  1.99999999f, -0.5f }));
}

void testCCW()
{
    ASSERT_EQUALS(true, setup::polA.isCCW());
    ASSERT_EQUALS( true, setup::polB.isCCW());
    ASSERT_EQUALS( false, setup::polC.isCCW());
}




int main() {
    RUN(testPoligonoInit);
    RUN(testSignedAngle);
    RUN(testDoubleSignedArea);
    RUN(testArea);
    RUN(testCCW);
    RUN(testPointInPolygon);

    return TEST_REPORT();
}
