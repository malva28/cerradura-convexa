//
// Although named Float Comparison, these functions are suitable for doubles as
// well.
// Created by malva on 02-05-21.
//

#ifndef ELEM_GEOMETRICOS_FLOATCOMPARISON_H
#define ELEM_GEOMETRICOS_FLOATCOMPARISON_H

#include<math.h>

/*
 * Returns the distance between x and y
 */
template <class T>
T distance(T x, T y)
{
    return std::fabs(x-y);
}

/*
 * Suitable to perform float comparison. It checks if x and y are close enough
 * within an epsilon of difference. Preferred over equality and over relative
 * comparison when x and y are close to zero, but otherwise use a relative
 * epsilon to the magnitude of the variables instead.
 */
template <class T>
bool withinEpsAbs(T x, T y, T absEpsilon)
{
    T d{distance(x,y)};
    return (d < absEpsilon);
}

/*
 * Suitable to perform float comparison. It checks if x and y are close enough
 * by a percentage epsilon of the biggest of the magnitud of either x or y.
 * This method adjusts to both tiny and large values.
 * Won't work properly when x and y are close to zero
 */
template <class T>
bool withinEpsRel(T x,T y, T relEpsilon)
{
    T d{distance(x,y)};
    return (d <= (std::max(std::fabs(x), std::fabs(y)) * relEpsilon));
}

/*
 * Compares proximity for x and y combining and absolute and relative epsilon
 * approach. If the absolute epsilon comparison fails it uses the relative
 * method.
 */
template <class T>
bool withinEps(T x, T y, T absEpsilon, T relEpsilon)
{
    if (withinEpsAbs(x,y,absEpsilon))
    {
        return true;
    } else {
        return withinEpsRel(x,y,relEpsilon);
    }
}

#endif //ELEM_GEOMETRICOS_FLOATCOMPARISON_H
