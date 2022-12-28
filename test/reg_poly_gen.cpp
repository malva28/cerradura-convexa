//
// Created by malva on 08-11-21.
//

#include <elem_geometricos.h>
#include<set>
#include <random> // for std::mt19937
#include <ctime> // for std::time
#include <cmath>

enum Distribution{
    uniform_real
};

/*
 * Converts an angle given in rads in range [-pi, pi] to [0, 2pi]
 */
double convert_to_positive_rad(double angle_rad)
{
    if(angle_rad >= 0)
    {
        return angle_rad;
    } else
    {
        return M_PI + (M_PI + angle_rad);
    }
}

namespace MyRandom
{
    // Initialize our mersenne twister with a random seed based on the clock (once at system startup)
    //std::mt19937 mersenne{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
    std::mt19937 mersenne{ static_cast<std::mt19937::result_type>(3) };
}

/*
 * Generates a vector of n vertices that form a regular polygon.
 * The polygon is inscribed in a circle of radius 1
 */
std::vector<Punto<double>> gen_reg_pol_list(int n)
{
    double radius{ 1.0 };
    double circ{ 2*M_PI };

    std::vector<Punto<double>> contour_pts;
    for (int i{ 0 }; i < n; i++)
    {
        double ang{ circ*i/n };
        Punto<double> p { radius*cos(ang), radius*sin(ang) };
        contour_pts.push_back(p);
    }

    return contour_pts;
}


/*
 * Fills a vector with n vertices that form a regular polygon.
 * The polygon is inscribed in a circle of radius 1
 */
std::vector<Punto<double>>& fill_reg_pol_list(int n, std::vector<Punto<double>>& v)
{
    double radius{ 1.0 };
    double circ{ 2*M_PI };

    for (int i{ 0 }; i < n; i++)
    {
        double ang{ circ*i/n };
        Punto<double> p { radius*cos(ang), radius*sin(ang) };
        v.push_back(p);
    }

    return v;
}

/*
 * Generates a regular (and thus convex) polygon of n points with a random
 * cloud of p points in its interior (and possibly in the borders).
 * The entire output is given as a cloud of points of size n+p
 */
std::vector<Punto<double>> gen_reg_points_inside(int n, int p, std::mt19937 randGen){
    double radius{ 1.0 };
    double circ{ 2*M_PI };

    // creación del contorno
    std::vector<Punto<double>> contour_pts{ gen_reg_pol_list(n) };

    // inserción nube random de puntos
    std::uniform_real_distribution p_range{-radius, radius};
    std::set<Punto<double>> pointCloud;

    if (n >= 3)
    {
        std::vector<Segmento<double>> contour_s{ puntosAsSegmentos<double>(contour_pts) };
        while(pointCloud.size() < p )
        {
            Punto<double> p{ p_range(randGen), p_range(randGen) };
            double ang{ convert_to_positive_rad(atan2(p.getY(), p.getX()))};
            int k{ static_cast <int>(floor(n*ang/circ))};

            // corresponding border to angle
            if (contour_s[k].isPointToTheLeft(p))
            {
                // note that the pointCloud size won't increase if the point
                // was already inserted
                pointCloud.insert(p);
            }
        }
    } else
    {
        while(pointCloud.size() < p )
        {
            Punto<double> p{p_range(randGen), p_range(randGen)};
            pointCloud.insert(p);
        }
    }

    // fill vec with set content
    for(Punto<double> pInCloud: pointCloud)
    {
        contour_pts.push_back(pInCloud);
    }
    return contour_pts;
};

/*
 * Generates a regular (and thus convex) polygon of n points with p points
 * inserted in (or close to) the borders.
 * n must be at least 3
 * The entire output is given as a cloud of points
 */
std::vector<Punto<double>> gen_reg_points_in_border(int n, int p, std::mt19937 randGen)
{
    double radius{ 1.0 };
    double circ{ 2*M_PI };

    // creación del contorno
    //std::vector<Punto<double>> contour_pts{ gen_reg_pol_list(n) };
    std::vector<Punto<double>> contour_pts;
    contour_pts.reserve(n);
    fill_reg_pol_list(n, contour_pts);

    std::uniform_real_distribution ang_range{ 0.0, circ };
    std::set<Punto<double>> pointCloud;

    if(n>= 3)
    {
        while(pointCloud.size() < p )
        {
            double ang{ ang_range(randGen) };
            int k{ static_cast <int>(floor(n*ang/circ))};

            double sliceOfCirc{ circ/(2*n) };
            double u { cos(ang - ((2*k+1) * sliceOfCirc)) };
            double p_x{ radius * cos(ang) * cos(sliceOfCirc)/u };
            double p_y{ radius * sin(ang) * cos(sliceOfCirc)/u };

            Punto<double> p{ p_x, p_y };
            pointCloud.insert(p);
        }

        // fill vec with set content
        for(Punto<double> pInCloud: pointCloud)
        {
            contour_pts.push_back(pInCloud);
        }
    }

    return contour_pts;
}

/*
 * Shuffle points generated here in order to avoid having the contour points
 * at the beggining of the vector
 */
void shuffle(std::vector<Punto<double>>& cloud)
{
    std::shuffle(cloud.begin(), cloud.end(), MyRandom::mersenne);
}
