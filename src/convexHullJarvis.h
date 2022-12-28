//
// Created by malva on 18-11-21.
//

#ifndef CERRADURA_CONVEXA_CONVEXHULLJARVIS_H
#define CERRADURA_CONVEXA_CONVEXHULLJARVIS_H

#include <convex_hull.h>
#include <elem_geometricos.h>
#include <algorithm>

/*
 * Computes the convex hull of a cloud of points. The cloud must at least have
 * three points
 */
template <class T>
std::vector<int> giftWrappingIndex(std::vector<Punto<T>> pointCloud)
{
    std::vector<int> hullInd;
    auto n{ pointCloud.size() };

    if (n < 3) return hullInd;

    // leftMostInd;
    auto leftMostIter{std::min_element(std::begin(pointCloud), std::end(pointCloud)) };
    int leftMostInd{static_cast<int>(std::distance(pointCloud.begin(), leftMostIter)) };

    int leftInd;
    int pInHullInd{leftMostInd };

    do
    {
        hullInd.push_back(pInHullInd);
        leftInd = (pInHullInd+1)%n;
        for(int i{ }; i < n; i++)
        {
            Segmento<T> s{ pointCloud[pInHullInd], pointCloud[leftInd] };
            if(s.isPointToTheLeft(pointCloud[i]))
            {
                leftInd = i;
            }
        }
        pInHullInd = leftInd;
    } while (pInHullInd != leftMostInd);

    return hullInd;
}

template <class T>
Poligono<T> giftWrapping(std::vector<Punto<T>>& cloud)
{
    std::vector<Punto<T>> chPoints;
    std::vector<int> indices{ giftWrappingIndex(cloud) };
    for(int i: indices)
    {
        chPoints.push_back(cloud[i]);
    }
    Poligono<T> pol{ chPoints };
    return pol;
}

#endif //CERRADURA_CONVEXA_CONVEXHULLJARVIS_H
