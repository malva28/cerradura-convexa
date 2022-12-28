#include <elem_geometricos.h>
#include <tinytest.h>


/*
 * Test proper construction and member value initialization
 */
void testPuntoInit()
{
    Punto<double> p1{ 1.3, 1.2 };
    Punto<int> p2{ 1, 2 };
    Punto<long> p3{ };

    ASSERT_EQUALS(1.3, p1.getX());
    ASSERT_EQUALS(1.2, p1.getY());

    ASSERT_EQUALS(1, p2.getX());
    ASSERT_EQUALS(2, p2.getY());

    ASSERT_EQUALS(0, p3.getX());
    ASSERT_EQUALS(0, p3.getY());
}

void testPuntoAdd()
{
    Punto<float> p1{ 1.1, 1.1 };
    Punto<double> p2{ 1.1, 1.1 };
    Punto<int> p3{ 3, 4 };

    Punto<float> res1{ p1 + p1};
    Punto<float> expected1{ 2.2, 2.2 };
    ASSERT_EQUALS(expected1, res1);

    Punto<double> res2{ p2 + p2 + p2 };
    Punto<double> expected2{ 3.3, 3.3 };
    ASSERT_EQUALS(expected2, res2);

    Punto<float> res3{ p1 + p3 };
    Punto<float> expected3{ 4.1, 5.1 };
    ASSERT_EQUALS(expected3, res3);

    Punto<float> res4{ p3 + p1 };
    ASSERT_EQUALS(expected3, res4);

}

void testPuntoSubstract()
{
    Punto<float> p1{ 1.1, 1.1 };
    Punto<float> p2{ 2.2, 2.2 };
    Punto<double> p3{ 1.1, 1.1 };
    Punto<double> p4{ 3.3, 3.3 };
    Punto<int> p5{ 3, 3 };

    Punto<float> res1{ p2 - p1};
    Punto<float> expected1{ 1.1, 1.1 };
    ASSERT_EQUALS(expected1, res1);

    Punto<double> res2{ p4 - p3 -p3 - p3 };
    Punto<double> expected2{ };
    ASSERT_EQUALS(expected2, res2);

    Punto<double> res3{ p5 - p4 };
    Punto<double> expected3{ -0.3, -0.3 };
    ASSERT_EQUALS(expected3, res3);

    Punto<double> res4{ p5 - p4 };
    ASSERT_EQUALS(expected3, res4);

    Punto<double> res5{ p4 - p3 -p3 - p3 -p3};
    ASSERT_EQUALS(-p3, res5);
}

void testPuntoScalarProduct()
{
    Punto<float> p1{ 1.1, 1.1 };
    Punto<double> p2{ 3.3, 3.3 };
    Punto<int> p3{ 3, 3 };

    int s1{ 2 };
    double s2{ 0.5 };

    Punto<float> res1{ p1*s1 };
    Punto<float> expected1{ 2.2, 2.2 };
    ASSERT_EQUALS(expected1, res1);

    Punto<double> res2{ s2*p3 };
    Punto<double> expected2{ 1.5, 1.5 };
    ASSERT_EQUALS(expected2, res2);

    Punto<double> res3{ s1*p2*s2 };
    ASSERT_EQUALS(p2, res3);
}

int main() {
    RUN(testPuntoInit);
    RUN(testPuntoAdd);
    RUN(testPuntoSubstract);
    RUN(testPuntoScalarProduct);

    return TEST_REPORT();
}