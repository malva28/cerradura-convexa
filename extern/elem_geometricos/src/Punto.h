//
// Created by malva on 01-05-21.
//

#ifndef ELEM_GEOMETRICOS_PUNTO_H
#define ELEM_GEOMETRICOS_PUNTO_H

#include "FloatComparison.h"
#include <iostream>

/*
 * Creates a 3D object Punto3D with X,Y and Z coordinates.
 */
template <class T>
class Punto3D
{
private:
    T m_x;
    T m_y;
    T m_z;
private:

};

/*
 * Creates a 2D object punto with X and Y coordinates.
 */
template <class T>
class Punto
{
private:
    T m_x;
    T m_y;

public:
    /*
     * Creates a point Punto given the X and Y coordinates.
     * X and Y's types must be the same.
     */
    Punto(T x = 0, T y=0)
            :  m_x{ x }, m_y{ y }
    {
    };

    /*
     * Copy constructor. Generates a new Punto with the same (x,y) coordinates
     * as copy argument
     */
    Punto(const Punto<T>& copy)
            : m_x { copy.m_x }, m_y { copy.m_y }
    {
    };


    T getX() const { return m_x; }
    T getY() const { return m_y; }

    // reminder that it's not ok to use Punto& here since we are creating a new
    // object that will be out of scope and become garbage when the function
    // returns
    Punto<T> operator- () const;

    // reminder that it's ok to use Punto& here since we are returning this and
    // this will be properly destroyed when the (default) destructor is called
    Punto<T>& operator= (const Punto<T>& punto);

    /*
     * Returns a new Punto with same X and Y coordinates as this Punto but
     * swapped
     */
    Punto<T> swapCoordinates() const;

};

/*
 * Assignment operator for Punto through another punto. Returns the newly
 * updated object to chain the = operator.
 */
template<class T>
Punto<T>& Punto<T>::operator=(const Punto<T> &punto) {
    m_x = punto.m_x;
    m_y = punto.m_y;

    return *this;
}

/*
 * Unary minus for Punto
 * Returns a new Punto with coordinates whose signs where swapped
 */
template<class T>
Punto<T> Punto<T>::operator-() const {
    return Punto<T>(-getX(), -getY());
}

template<class T>
Punto<T> Punto<T>::swapCoordinates() const {
    return Punto<T>(getY(), getX());
}

/*
 * Addition between two points. The resulting Punto is obtained through
 * addition of the corresponding coordinates.
 * Both Punto can have different types. The result will be of whatever type
 * given by the implicit conversion (if there's any)
 */
template <class T, class S>
auto operator+(const Punto<T> &p1, const Punto<S> &p2) {
    auto sumX{ p1.getX()+p2.getX() };
    Punto<decltype(sumX)> res{ sumX, p1.getY()+p2.getY() };
    return res;
}


/*
 * Binary substraction between two points.
 */
template <class T, class S>
auto operator-(const Punto<T> &p1, const Punto<S> &p2) {
    return p1 + (-p2);
}

/*
 * Product between a point and a scalar s.
 * The result is a Punto with it's coordinates multiplied by s.
 */
template <class T, class S>
auto operator*(const Punto<T> &p, S s) {
    auto prodX{ p.getX()*s };
    Punto<decltype(prodX)> res{ prodX, p.getY()*s };
    return res;
}



/*
 * Make scalar product commutative
 */
template <class T, class S>
auto operator*(S s, const Punto<T> &p) {
    return p*s;
}

/*
 * Returns whether or not p1 is less than p2, comparing x coordinates first,
 * then y coordinates if the former are equal
 */
template <class T>
bool operator < (const Punto<T>& p1, const Punto<T>& p2)
{
    if (p1.getX() == p2.getX())
    {
        return p1.getY() < p2.getY();
    }
    return p1.getX() < p2.getX();
}

template <>
bool operator < (const Punto<float>& p1, const Punto<float>& p2)
{
    if (withinEps(p1.getX(), p2.getX(), 1e-7f, 1e-7f))
    {
        return p1.getY() < p2.getY();
    }
    return p1.getX() < p2.getX();
}


template <>
bool operator < (const Punto<double>& p1, const Punto<double>& p2)
{
    if (withinEps(p1.getX(), p2.getX(), 1e-10, 1e-10))
    {
        return p1.getY() < p2.getY();
    }
    return p1.getX() < p2.getX();
}

/*
 * Returns whether p1 is less than p2 in lexicographic order
 * (compares first Y coordinates, then X coordinates if the former are equal)
 */
template <class T>
bool lexicographicLess(const Punto<T>& p1, const Punto<T>& p2)
{
    return p1.swapCoordinates() < p2.swapCoordinates();
}


/*
 * Punto equality. Two points are equal if their coordinates are the same.
 */
template <class T>
bool operator==(const Punto<T> &p1, const Punto<T> &p2) {
    return ((p1.getX() == p2.getX()) && (p2.getY() == p2.getY()));
}

/*
 * Specialization of equality for double Punto.
 * Both coordinates must be close enough (by 1e-10) to be considered equal.
 */
template<>
bool operator==(const Punto<double> &p1, const Punto<double> &p2)
{
    return (withinEps(p1.getX(), p2.getX(), 1e-10, 1e-10)
    && withinEps(p1.getY(), p2.getY(), 1e-10, 1e-10));
}

/*
 * Specialization of equality for float Punto.
 * Both coordinates must be close enough (by 1e-7) to be considered equal.
 */
template<>
bool operator==(const Punto<float> &p1, const Punto<float> &p2)
{
    return (withinEps(p1.getX(), p2.getX(), 1e-7f, 1e-7f)
            && withinEps(p1.getY(), p2.getY(), 1e-7f, 1e-7f));
}

template<class T>
std::ostream& operator<< (std::ostream &out, const Punto<T> &p)
{
    out << "(" << p.getX() << ", " << p.getY() << ")";
    return out;
}



#endif //ELEM_GEOMETRICOS_PUNTO_H
