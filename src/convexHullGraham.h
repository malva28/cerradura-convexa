//
// Created by malva on 19-11-21.
//

#ifndef CERRADURA_CONVEXA_CONVEXHULLGRAHAM_H
#define CERRADURA_CONVEXA_CONVEXHULLGRAHAM_H

#include <convex_hull.h>
#include <elem_geometricos.h>
#include <stdlib.h>
#include <algorithm>


namespace globalGraham{
    template <class T>
    Punto<T> bottomMost;
}

template <class T>
int bottomMostPointIndex(std::vector<Punto<T>>& pointCloud)
{
    auto bottomMostIter{ std::min_element(std::begin(pointCloud), std::end(pointCloud), lexicographicLess<T>) };
    int bottomMostInd{ static_cast<int>(std::distance(pointCloud.begin(), bottomMostIter)) };
    return bottomMostInd;
}

/*
 * Computes the orientation of p2 with respect to the line crossing a pivot
 * (and fixed) point and p1. p2 is "greater" (1) if it lies to the left or if
 * it is colinear and more distant
 */
template <class T>
class OrientationCompare
{
private:
    const Punto<T> m_pivot;

public:
    OrientationCompare(const Punto<T>& pivot):
    m_pivot{ pivot }
    {
    };

    /*
     * Copy constructor
     */
    OrientationCompare(const OrientationCompare<T>& copy):
    m_pivot{ copy.m_pivot }
    {
    };

    bool comparison(const Punto<T>& p1, const Punto<T>& p2) const
    {
        Segmento<T> s1{ m_pivot, p1 };
        if(s1.isPointInLine(p2))
        {
            Segmento<T> s2{ p1, p2 };
            bool cond{ s1.length() >= s2.length() };
            return !cond;
        }
        return !s1.isPointToTheLeft(p2);
    }

    bool operator()(const Punto<T>& p1, const Punto<T>& p2) const {

        return comparison(p1, p2);
    }


    //bool operator()(const void* p1, const void* p2) const
    //{
    //    return comparison(*(Punto<T>)p1, *(Punto<T>)p2);
    //}

};


template <class T>
int orientationCmp(const void* v1, const void* v2)
{
    Punto<T> p1{ *(Punto<T> *) v1 };
    Punto<T> p2{ *(Punto<T> *) v2 };

    Segmento<T> s1{ globalGraham::bottomMost<T>, p1 };
    if(s1.isPointInLine(p2))
    {
        Segmento<T> s2{ p1, p2 };
        bool cond{ s1.length() >= s2.length() };
        return !cond;
    }
    return !s1.isPointToTheLeft(p2);
}

/*
 * Removes points from an ordered by angle list that are consecutive and
 * colinear with the pivot point which is the first element vecIn[0]
 * Keeps only the last repeated instance.
 */
template <class T>
std::vector<Punto<T>> cleanSameAngle(std::vector<Punto<T>>& vecIn)
{
    Punto<T> pivot{ vecIn[0] };
    std::vector<Punto<T>> cleanVec;
    cleanVec.push_back(pivot);

    Punto<T> prevP;
    Segmento<T> prevS;

    for(int j{ 1 }; j < vecIn.size(); j++)
    {
        prevP = { vecIn[j] };
        prevS = { pivot, prevP };

        while (j < vecIn.size()-1 && prevS.isPointInLine(vecIn[j+1]))
        {
            j++;
        }
        // if we are here it's because the previous point was not colinear with
        // the current point and the pivot
        cleanVec.push_back(vecIn[j]);
    }
    return cleanVec;
}

template <class T>
bool consecutivePointsRightTurn(std::vector<Punto<T>>& cloud, std::vector<int> indStack, int currInd)
{
    auto stackSize{ indStack.size() };
    const Punto<T>& prevToTop { cloud[ indStack [stackSize-2]] };
    const Punto<T>& top { cloud[indStack.back()]};
    const Punto<T>& tested { cloud[currInd] };

    return Segmento<T>{ prevToTop, top }.isPointToTheRight(tested);
}


/*
 * Computes the convex hull of a cloud of points. The cloud must at least have
 * three points
 */
template <class T>
std::vector<int> grahamScanIndex(std::vector<Punto<T>> pointCloud) {
    std::vector<int> hullInd;


    int bottomMostInd{ bottomMostPointIndex(pointCloud) };

    // put bottom most point at the beggining
    std::swap(pointCloud[0], pointCloud[bottomMostInd]);
    globalGraham::bottomMost<T> = pointCloud[0];

    //OrientationCompare orientationCmp{ pointCloud[0] };


    //std::sort( std::next(pointCloud.begin(), 1), pointCloud.end(), orientationCmp );
    qsort (&pointCloud[1], pointCloud.size()-1, sizeof(Punto<T>), orientationCmp<T>);


    std::vector<Punto<T>> cleanCloud{ cleanSameAngle(pointCloud) };
    auto m{ cleanCloud.size() };

    if (m < 3) return hullInd; // cannot compute hull with less than 3 non
    // colinear points

    // push p0 and p1
    hullInd.push_back(0);
    hullInd.push_back(1);
    for (int i{ 2 }; i < m; i++)
    {
        while(hullInd.size() >= 2 && consecutivePointsRightTurn(cleanCloud, hullInd, i))
        {
            hullInd.pop_back();
        }
        hullInd.push_back(i);
    }
    return hullInd;

}

template <class T>
Poligono<T> grahamScan(std::vector<Punto<T>>& cloud)
{
    std::vector<Punto<T>> chPoints;
    std::vector<int> indices{ grahamScanIndex(cloud) };
    for(int i: indices)
    {
        chPoints.push_back(cloud[i]);
    }
    Poligono<T> pol{ chPoints };
    return pol;
}


#endif //CERRADURA_CONVEXA_CONVEXHULLGRAHAM_H
