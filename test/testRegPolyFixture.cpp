#include <gtest/gtest.h>
#include "reg_poly_gen.cpp"


class RegPolyClass: public ::testing::Test {
protected:
    int n;
    int p;
    Poligono<double> poly;
    std::vector<Punto<double>> interiorPts;

    void SetUp() override {
        interiorPts = {gen_reg_points_inside(n, p, MyRandom::mersenne)};
        auto first = interiorPts.begin();
        auto last = interiorPts.begin() + n;
        poly = {std::vector<Punto<double>>(first, last)};
    }
    //void TearDown() override {};
};


struct regPolyState
{
    int n;
    int p;
    bool success;
};


struct PointsInsideTest : RegPolyClass, testing::WithParamInterface<regPolyState>
{
    PointsInsideTest()
    {
        n = GetParam().n;
        p = GetParam().p;
    }
};


TEST_P(PointsInsideTest, FinalInside)
{
    auto as = GetParam();
    bool success = true;
    for(int i{ n }; i < n+p; i++)
    {
        success = success && poly.pointInside(interiorPts[i]);
    }
    EXPECT_EQ(as.success,success);
}

INSTANTIATE_TEST_CASE_P(Default, PointsInsideTest,
                        testing::Values(
                                regPolyState{3,0,true},
                                regPolyState{3,1,true},
                                regPolyState{3,10,true},
                                regPolyState{3,100,true},
                                regPolyState{6,100,true},
                                regPolyState{30,100,true}
                        ));




int main(int ac, char* av[])
{
    testing::InitGoogleTest(&ac, av);
    return RUN_ALL_TESTS();
}