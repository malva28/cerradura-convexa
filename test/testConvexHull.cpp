#include <convex_hull.h>
#include <gtest/gtest.h>
#include "reg_poly_gen.cpp"
#include <algorithm>



/*
 * Checks that the Poligono pol is indeed a hull, meaning that all points that
 * are not part of the hull (given by their indices) are inside pol
 */
bool validHull(std::vector<Punto<double>>& cloud, std::vector<int>& indices, Poligono<double>& pol)
{
    auto n{ cloud.size() };
    bool valid = true;
    for(auto i{ n }; i < cloud.size(); i++)
    {
        if(std::find(begin(indices), end(indices), i) != std::end(indices))
        {
            valid = valid && pol.pointInside(cloud[i]);
        }
    }
    return valid;
}


class ConvexClass: public ::testing::Test {
protected:
    int                         cloudSize;
    std::vector<Punto<double>>  pointCloud;
    std::vector<int>            chIndices;
    Poligono<double> poly;

    void SetUp() override {
        cloudSize = pointCloud.size();
    }

    void setPolyContour() {
        std::vector<Punto<double>> arg;
        for(int ind: chIndices)
        {
            arg.push_back(pointCloud[ind]);
        }
        poly = { arg };
    };
};

struct aGenFunction
{
    std::string funName;
    std::function<std::vector<Punto<double>>(int, int, std::mt19937)> fun;
};

struct anIndexConvexHullFunction
{
    std::string funName;
    std::function<std::vector<int>(std::vector<Punto<double>>)> fun;
};

struct convexState
{
    int nReg;              // Number of vertices in regular polygon
    int nInOrBorder;       // Number of vertices in interior or border of polygon
    int expectedHullN;      // Expected number of pts in convex hull
    std::mt19937 randGen;  // The generator for random numbers

    aGenFunction genFun;
    //std::function<std::vector<Punto<double>>(int, int, std::mt19937)> genFun;
      // The fun that generates the cloud of points

    //std::function<std::vector<int>(std::vector<Punto<double>>)> convexIndicesFun;
    anIndexConvexHullFunction convexIndicesFun;
    bool validCH;   // whether the hull is valid
    bool convex;    // whether the hull is convex

    friend std::ostream& operator<<(std::ostream& os, const convexState& obj)
    {
        return os
                << "Points in regular Polygon: " << obj.nReg
                << " Points inside or in borders: " << obj.nInOrBorder
                << "Points in convex hull: " << obj.expectedHullN
                << " Generation Function: " << obj.genFun.funName
                << " Convex Hull Function: " << obj.convexIndicesFun.funName
                << " Valid Hull: " << obj.validCH
                << " Convex Hull: " << obj.convex;
    }
};


class ConvexStateSet : public ConvexClass, public testing::WithParamInterface<convexState>
{
public:
    ConvexStateSet(){
        auto pa = GetParam();
        pointCloud = pa.genFun.fun(pa.nReg, pa.nInOrBorder, pa.randGen);
        shuffle(pointCloud);
        chIndices = pa.convexIndicesFun.fun(pointCloud);
        setPolyContour();
    }
};


class ConvexBorderStateSet : public ConvexStateSet
{};

TEST_P(ConvexStateSet, ValidConvexHull)
{
    auto as = GetParam();
    EXPECT_EQ(as.expectedHullN, chIndices.size()) << "Number of points in hull test failed! Tested data:\n   " << as;

    bool valid{validHull(pointCloud, chIndices, poly) };
    EXPECT_EQ(as.validCH, valid) << "Points inside Hull test failed! Tested data:\n   " << as;

    bool convex{ poly.isConvexCCW() };
    EXPECT_EQ(as.convex, convex);
}

TEST_P(ConvexBorderStateSet, ValidBorderConvexHull)
{
    auto as = GetParam();
    EXPECT_TRUE(chIndices.size() >= as.nReg &&  as.expectedHullN >= chIndices.size()) << "Number of points in hull test failed! Tested data:\n   " << as;

    bool valid{validHull(pointCloud, chIndices, poly) };
    EXPECT_EQ(as.validCH, valid) << "Points inside Hull test failed! Tested data:\n   " << as;

    bool convex{ poly.isConvexCCW() };
    EXPECT_EQ(as.convex, convex);
}

aGenFunction regPInside{"gen_reg_points_inside", gen_reg_points_inside};
aGenFunction regPBorder{"gen_reg_points_in_border", gen_reg_points_in_border };
anIndexConvexHullFunction giftWrap{ "giftWrappingIndex", giftWrappingIndex<double>};
anIndexConvexHullFunction grahamScanF{"grahamScanIndex", grahamScanIndex<double> };


INSTANTIATE_TEST_CASE_P(chPointsInsideTest, ConvexStateSet,
        testing::Values(
                convexState{ 3,   0,  3,  MyRandom::mersenne, regPInside, giftWrap, true, true},
                convexState{ 3,   1,  3,  MyRandom::mersenne, regPInside, giftWrap, true, true},
                convexState{ 3,  10,  3,  MyRandom::mersenne, regPInside, giftWrap, true, true},
                convexState{ 3, 100,  3,  MyRandom::mersenne, regPInside, giftWrap, true, true},
                convexState{ 6, 100,  6,  MyRandom::mersenne, regPInside, giftWrap, true, true},
                convexState{30, 100, 30,  MyRandom::mersenne, regPInside, giftWrap, true, true},

                // GRAHAM SCAN
                convexState{3, 0, 3, MyRandom::mersenne, regPInside, grahamScanF, true, true},
                convexState{3, 1, 3, MyRandom::mersenne, regPInside, grahamScanF, true, true},
                convexState{3, 10, 3, MyRandom::mersenne, regPInside, grahamScanF, true, true},
                convexState{3, 100, 3, MyRandom::mersenne, regPInside, grahamScanF, true, true},
                convexState{6, 100, 6, MyRandom::mersenne, regPInside, grahamScanF, true, true},
                convexState{30, 100, 30, MyRandom::mersenne, regPInside, grahamScanF, true, true},
                convexState{90, 999, 90, MyRandom::mersenne, regPInside, grahamScanF, true, true},

                convexState{  1000,  9000,  1000, MyRandom::mersenne, regPInside, grahamScanF, true, true},
                convexState{ 10000, 90000, 10000, MyRandom::mersenne, regPInside, grahamScanF, true, true}

));

INSTANTIATE_TEST_CASE_P(chPointsBorderTest, ConvexBorderStateSet,
                        testing::Values(
                                // GIFT WRAP
                                convexState{    3,   190,    193, MyRandom::mersenne, regPBorder, giftWrap, true, true},
                                convexState{ 10,  90,  100, MyRandom::mersenne, regPBorder, giftWrap, true, true},

                                // GRAHAM SCAN
                                convexState{    3,   190,    193, MyRandom::mersenne, regPBorder, grahamScanF, true, true},
                                convexState{ 10,  90,  100, MyRandom::mersenne, regPBorder, grahamScanF, true, true}
                        ));


int main(int ac, char* av[])
{
    testing::InitGoogleTest(&ac, av);
    return RUN_ALL_TESTS();
}