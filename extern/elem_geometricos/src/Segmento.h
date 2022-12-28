//
// Created by malva on 08-10-21.
//

#ifndef ELEM_GEOMETRICOS_SEGMENTO_H
#define ELEM_GEOMETRICOS_SEGMENTO_H

#include "../include/elem_geometricos.h"
#include <iostream>

/*
 * Class for holding segments. A Segmento is a composition of a startpoint
 * (possibly different from the origin) and an endpoint, it's directed and
 * has a length
 */
template <class T>
class Segmento
{
private:
    Vector<T> m_start;
    Vector<T> m_end;

public:
    /*
     * Creates a Segmento given four values: the (x,y) coordinates for the
     * start point and the (x,y) coordinates for the end point
     */
    Segmento(T startX = 0, T startY = 0, T endX = 0, T endY = 0):
            m_start{ Vector<T>{startX, startY}}, m_end{ Vector<T>{ endX, endY }}
    {};

    /*
     * Creates a Segmento with coordinates for its start and end specified by
     * the given points. Both points must match the Segmento type.
     */
    Segmento(const Punto<T> &startPoint, const Punto<T> &endPoint):
            m_start{ Vector<T>{startPoint} }, m_end{ Vector<T>{endPoint} }
    {};

    /*
     * Creates a Segmento given two vectors, one that points to the start and
     * one that points to the end. Both vectors must match the Segmento type.
     */
    Segmento(const Vector<T> &startPoint, const Vector<T> &endPoint):
            m_start{ startPoint }, m_end{ endPoint }
    {};

    /*
     * Copy constructor for segmento
     */
    Segmento(const Vector<T> &copy)
            : Segmento(copy.getStart(), copy.getEnd())
    {};

    /*
     * Returns the Vector corresponding to the start point of the Segmento.
     * This reference may not be edited.
     */
    const Vector<T>& getStart() const { return m_start; }

    /*
     * Returns the Punto corresponding to the end point of the vector.
     * This reference may not be edited.
     */
    const Vector<T>& getEnd() const { return m_end; }

    /*
     * Returns a new Segmento with the same start and end points as this
     * but swapped
    */
    Segmento<T> swapSegmento() const;

    /*
     * Returns the length of the Segmento.
     */
    double length() const;

    /*
     * Returns double of the area enclosed in the triangle formed by this
     * Segmento and the plane origin
     */
    T doubleAreaSegment() const;

    /*
     * Returns double the (signed) area enclosed by the segment and a given
     * point p
     */
    T lineDeterminant(const Punto<T> &p) const;

    /*
     * Returns whether a point p is to the left of this Segmento
     */
    const bool isPointToTheLeft(const Punto<T> &p) const;

    /*
     * Returns whether a point p is to the right of this Segmento
     */
    const bool isPointToTheRight(const Punto<T> &p) const;

    /*
     * Returns whether a point is in the line that passes through this
     * segment.
     */
    bool isPointInLine(const Punto<T> &p) const;

    /*
     * Returns whether this segment straddles some horizontal axis or not
     */
    bool straddleHorizontally(T xAxis = 0) const;

    /*
     * Returns the difference in the X coordinate between the start point and
     * the end point
     */
    T diffX() const { return getStart().getX() - getEnd().getX(); };

    /*
     * Returns the difference in the Y coordinate between the start point and
     * the end point
     */
    T diffY() const { return getStart().getY() - getEnd().getY(); };

    /*
     * Returns the coordinate x of the intersection between the line containing
     * this segment and an axis parallel to axis X (or alternatively, by a line
     * defined as y = xAxis). Can return inf of nan when the segment is either
     * parallel or contained in the horizontal.
     */
    double horizontalIntersect(T xAxis = 0) const;

    Segmento<T>& operator= (const Segmento<T>& segmento);

};

template<class T>
double Segmento<T>::length() const {
    return (getEnd() - getStart()).euclideanNorm();
}

template <class T>
T Segmento<T>::doubleAreaSegment() const {
    return crossProdValue(getStart(), getEnd());
}

template <class T>
T Segmento<T>::lineDeterminant(const Punto<T> &p) const
{
    T doubleAreaS          { doubleAreaSegment() };
    T doubleAreaPointStart { crossProdValue(Vector<T>{ p }, getStart())};
    T doubleAreaEndPoint   { crossProdValue(getEnd(),       Vector<T>{ p } )};
    return doubleAreaS + doubleAreaPointStart + doubleAreaEndPoint;

}

template <class T>
bool const Segmento<T>::isPointToTheLeft(const Punto<T> &p) const
{
    return lineDeterminant(p) > 0;
}

template <class T>
const bool Segmento<T>::isPointToTheRight(const Punto<T> &p) const
{
    return lineDeterminant(p) < 0;
}

template<class T>
bool Segmento<T>::isPointInLine(const Punto<T> &p) const
{
    return lineDeterminant(p) == 0;
}

template<class T>
Segmento<T> Segmento<T>::swapSegmento() const {
    return Segmento<T>( getEnd(), getStart() );
}

template<>
bool Segmento<double>::isPointInLine(const Punto<double> &p) const
{
    return withinEps(lineDeterminant(p), 0.0, 1e-10, 1e-10);
}

template<>
bool Segmento<float>::isPointInLine(const Punto<float> &p) const
{
    return withinEps(lineDeterminant(p), 0.0f, 1e-7f, 1e-7f);
}

template<class T>
Segmento<T>& Segmento<T>::operator=(const Segmento<T> &segmento) {
    m_start = segmento.getStart();
    m_end = segmento.getEnd();

    return *this;
}

template<class T>
bool Segmento<T>::straddleHorizontally(T xAxis) const {
    T pi { getEnd().getY() };
    T pi1{ getStart().getY() };
    return ((pi - xAxis) > 0) && ((pi1 - xAxis) <= 0);
}

template<class T>
double Segmento<T>::horizontalIntersect(T xAxis) const {
    double xIntersect{ (xAxis * diffX() - doubleAreaSegment())/(static_cast<double>(diffY())) };
    return xIntersect;
}

template <class T>
std::ostream& operator<<(std::ostream &out, const Segmento<T> &v)
{
    out << "(start=" << v.getStart().getEnd() <<", end=" <<v.getEnd().getEnd() << ")";
    return out;
}


#endif //ELEM_GEOMETRICOS_SEGMENTO_H
