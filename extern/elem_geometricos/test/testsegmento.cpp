//
// Created by malva on 11-10-21.
//

#include <elem_geometricos.h>
#include <tinytest.h>

namespace setup
{
    const Segmento<double> s1{  -0.3, 2.3,  -2, 2.2 };
    // testing const-ness of getters as well
    const Segmento<int> s2{ 1,0,5,0 };
    const Segmento<int> s2a { 5, 0, 6, 4 };
    const Segmento<int> s2b { 6, 4, 4, 5 };
    const Segmento<int> s2c { 1, 5, 1, 0 };
    // testing the Punto constructor for Vector as well
    const Punto<long> plong1{ 1000000L, 2147483648L };
    const Punto<long> plong2{ 0L, -4294967296L };
    const Vector<float> v1{ -3.4f, 0.4f };
    const Vector<float> v2{2.0f, -0.5f };

    const Segmento<long> s3{ plong1, plong2 };
    const Segmento<float> s4{ v1, v2 };
    const Segmento<float> s4a{ Vector<float>{ -1.6f, -0.5f}, v1 };
}

void testSegmentoInit()
{

    Vector<double> expectedS1{ -0.3, 2.3 };
    Vector<double> expectedE1{ -2, 2.2 };
    Vector<int> expectedS2{ 1,0 };
    Vector<int> expectedE2{ 5,0 };

    ASSERT_EQUALS(expectedS1, setup::s1.getStart());
    ASSERT_EQUALS(expectedE1, setup::s1.getEnd());

    ASSERT_EQUALS(expectedS2, setup::s2.getStart());
    ASSERT_EQUALS(expectedE2, setup::s2.getEnd());

    ASSERT_EQUALS(Vector<long>{ setup::plong1 }, setup::s3.getStart());
    ASSERT_EQUALS(Vector<long>{ setup::plong2 }, setup::s3.getEnd());

    ASSERT_EQUALS(setup::v1, setup::s4.getStart());
    ASSERT_EQUALS(setup::v2, setup::s4.getEnd());
}

void testLength()
{
    // let's test first that it works like the vec euclidean norm
    // when origin is (0,0)
    Vector<int>      v1{ 3, 4 };
    Vector<float>    v2{ 1.0, 0.0 };
    Vector<double>   v3{ 2.1, 3.2 };

    Segmento<int>    s1{ Vector<int>{}, v1 };
    Segmento<float>  s2{ Vector<float>{}, v2 };
    Segmento<double> s3{ Vector<double>{}, v3 };

    ASSERT_EQUALS( s1.length(), v1.euclideanNorm());
    ASSERT_EQUALS( s2.length(), v2.euclideanNorm());
    ASSERT_EQUALS( s3.length(), v3.euclideanNorm());

    // let's now test the lengths of the common segments

    double expected1{ 1.70293863659 };
    double expected2{ 4.0 };
    double expected4{ 5.47448627726 };

    ASSERT_EQUALS( true, withinEps(expected1, setup::s1.length(), 1e-10, 1e-10));
    ASSERT_EQUALS( true, withinEps(expected2, setup::s2.length(), 1e-10, 1e-10));
    ASSERT_EQUALS( true, withinEps(expected4, setup::s4.length(), 1e-7, 1e-7));

}

void testOrientation()
{
    const Punto<float> p1{ -1.6f, -0.5f };

    ASSERT_EQUALS( false,  setup::s4.isPointToTheLeft(p1));
    ASSERT_EQUALS( true,  setup::s4.isPointToTheRight(p1));

    const Punto<int> p2{ 6, 4 };
    ASSERT_EQUALS( true,  setup::s2.isPointToTheLeft(p2));
    ASSERT_EQUALS( false,  setup::s2.isPointToTheRight(p2));

    ASSERT_EQUALS( true,  setup::s2.isPointInLine(Punto<int>{ 2,0 }));
    ASSERT_EQUALS( true,  setup::s2.isPointInLine(Punto<int>{ 2,0 }));

    ASSERT_EQUALS( true,  setup::s4.isPointInLine(setup::v2.getEnd()));
}

void testDiffs()
{
    ASSERT_EQUALS(1.7, setup::s1.diffX());
    ASSERT_EQUALS(true, withinEps(0.1, setup::s1.diffY(), 1e-10, 1e-10));

    ASSERT_EQUALS(-4, setup::s2.diffX());
    ASSERT_EQUALS(0, setup::s2.diffY());
}

void testStraddle()
{
    int xAx{ 1 };
    ASSERT_EQUALS(true, setup::s2a.straddleHorizontally(xAx));
    ASSERT_EQUALS(false, setup::s2a.swapSegmento().straddleHorizontally(xAx));
    ASSERT_EQUALS(false, (setup::s2.straddleHorizontally(xAx) || setup::s2.swapSegmento().straddleHorizontally(xAx)));
    ASSERT_EQUALS(false, (setup::s2b.straddleHorizontally(xAx) || setup::s2b.swapSegmento().straddleHorizontally(xAx)));
    ASSERT_EQUALS(false, (setup::s2c.straddleHorizontally(xAx)));
    ASSERT_EQUALS(true, setup::s2c.swapSegmento().straddleHorizontally(xAx));
}

void testIntersect()
{
    int y1{ 2 };
    //std::cout << setup::s4.horizontalIntersect(0.0f) << '\n';
    ASSERT_EQUALS(5.5,setup::s2a.horizontalIntersect(y1) );
    ASSERT_EQUALS(10.0,setup::s2b.horizontalIntersect(y1) );
    ASSERT_EQUALS(1.0,setup::s2c.horizontalIntersect(y1) );

    float y2{ };
    ASSERT_EQUALS(true, withinEps(-1.0,setup::s4.horizontalIntersect(y2), 1e-7, 1e-7));
    ASSERT_EQUALS(true, withinEps(-2.6,setup::s4a.horizontalIntersect(y2), 1e-7, 1e-7));

}

void testPrecision()
{
    // big primes, these numbers compose 4,294,967,291
    const Segmento<int> s1 {-2147483647, -2147483647, 2147483644, 2147483644 };
    const Punto<int> p1 { 7, 7 };
    ASSERT_EQUALS( true,  s1.isPointInLine(p1));

}

int main() {
    RUN(testSegmentoInit);
    RUN(testLength);
    RUN(testOrientation);
    RUN(testStraddle);
    RUN(testDiffs);
    RUN(testIntersect);
    RUN(testPrecision);

    return TEST_REPORT();
}