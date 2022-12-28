//
// Created by malva on 02-05-21.
//
#include <elem_geometricos.h>
#include <tinytest.h>

void testVectorInit()
{
    Vector<double> v1{ 5.3, 2.9 };
    // testing const-ness of getters as well
    const Vector<int> v2{ 3, 2 };
    // testing the Punto constructor for Vector as well
    Punto<long> plong{ 1000000L, 2147483648L };
    Vector<long> v3{ plong };

    Punto<double> expected1{ 5.3,2.9 };
    ASSERT_EQUALS(expected1, v1.getEnd());

    Punto<int> expected2{ 3, 2 };
    ASSERT_EQUALS(expected2, v2.getEnd());

    const Punto<long> expected3{1000000L, 2147483648L };
    ASSERT_EQUALS(expected3, v3.getEnd());
}

void testVectorDotProduct()
{
    Vector<int> v1{ -6, 8 };
    const Vector<int> v2{ 5, 12};

    Vector<int> v3{ -7, 48 };
    Vector<double> v4{ 0.3, 0.04};

    int expected1{ 66 };
    ASSERT_EQUALS( expected1, dotProduct(v1, v2));

    double expected2{ -0.18 };
    // double equality cannot be overloaded in Vector file since doubles are
    // fundamental types, so we have to call withinEps directly
    ASSERT_EQUALS( true, withinEps(expected2, dotProduct(v3, v4), 1e-10, 1e-10));
    ASSERT_EQUALS( true, withinEps(expected2, dotProduct(v4, v3), 1e-10, 1e-10));
}

void testVectorEuclideanNorm()
{
    Vector<int> v1{ 3, 4 };
    Vector<float> v2{ 1.0, 0.0 };
    Vector<double> v3{ 2.1, 3.2 };

    double expected1{ 5.0 };
    ASSERT_EQUALS( true, withinEps(expected1, v1.euclideanNorm(), 1e-10, 1e-10));

    double expected2{ 1.0 };
    ASSERT_EQUALS( true, withinEps(expected2, v2.euclideanNorm(), 1e-10, 1e-10));

    double expected3{ 3.82753184180 };
    ASSERT_EQUALS( true, withinEps(expected3, v3.euclideanNorm(), 1e-10, 1e-10));

}

void testVectorScale()
{
    Vector<float> v1{ 1.1, 1.1 };
    Vector<double> v2{ 3.3, 3.3 };
    Vector<int> v3{ 3, 3 };

    int s1{ 2 };
    double s2{ 0.5 };

    Vector<float> res1{ v1*s1 };
    Vector<float> expected1{ 2.2, 2.2 };
    ASSERT_EQUALS(expected1, res1);

    Vector<double> res2{ s2*v3 };
    Vector<double> expected2{ 1.5, 1.5 };
    ASSERT_EQUALS(expected2, res2);

    Vector<double> res3{ s1*v2*s2 };
    ASSERT_EQUALS(v2, res3);
}

void testVectorNormalize()
{
    Vector<int> v1{ 3, 4 };
    Vector<float> v2{ 1.0, 0.0 };
    Vector<double> v3{ 2.1, 3.2 };

    Vector<double> expected1{ 0.6, 0.8 };
    ASSERT_EQUALS(expected1, v1.vecNorm());

    Vector<double> expected2{ 1.0, 0.0};
    ASSERT_EQUALS(expected2, v2.vecNorm());

    Vector<double> expected3{ 0.54865644148, 0.83604791083 };
    ASSERT_EQUALS(expected3, v3.vecNorm());

    const Vector<int> v4{ 31121, 31123 };
    //std::cout << v4.vecNorm();
    const Vector<double> expected4{ 0.707084060341452, 0.7071295013015974 };
    ASSERT_EQUALS(expected4, v4.vecNorm());


}

void testVectorCrossProdValue()
{
    Vector<float> v1a{ 35.8, 1.0 };
    Vector<int> v1b{ 1, 0 };

    Vector<int> v2a{ 2,3 };
    Vector<int> v2b{ 5,6 };

    const Vector<int> v3a{ -7, 48 };
    const Vector<double> v3b{ 0.3, 0.04};

    float expected1{ -1.0 };
    ASSERT_EQUALS(true, withinEps(expected1, crossProdValue(v1a, v1b), 1e-7f, 1e-7f));

    int expected2{ -3 };
    ASSERT_EQUALS(expected2, crossProdValue(v2a, v2b));

    double expected3{ -14.68 };
    ASSERT_EQUALS(true, withinEps(expected3, crossProdValue(v3a, v3b), 1e-10, 1e-10));
}

int main() {
    RUN(testVectorInit);
    RUN(testVectorDotProduct);
    RUN(testVectorEuclideanNorm);
    RUN(testVectorScale);
    RUN(testVectorNormalize);
    RUN(testVectorCrossProdValue);

    return TEST_REPORT();
}
