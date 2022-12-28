//
// Created by malva on 01-05-21.
//

#ifndef ELEM_GEOMETRICOS_VECTOR_H
#define ELEM_GEOMETRICOS_VECTOR_H

#include "Punto.h"
#include <math.h>


/*
 * Class for holding vectors with 3D coordinates
 */
template <class T>
class Vector3D
{
private:
    Punto<T> m_end;
public:

};

/*
 * Class for holding vectors. A Vector has sense of direction from start to end
 * defined by an endpoint. The start point is always at the origin and thus is
 * omitted from the data structure.
 */
template <class T>
class Vector
        {
private:
    Punto<T> m_end;

public:
    /*
     * Creates a Vector given the x and y coordinates of the endpoint
     */
    Vector(T endX = 0, T endY = 0):
    m_end{ Punto<T>{ endX, endY }}
    {
    };

    /*
     * Creates a Vector with coordinates for its endpoint specified by the
     * given point argument. Endpoint Punto type must match the vector type.
     */
    Vector(const Punto<T> &endPoint):
    m_end{ Punto<T>{ endPoint.getX(), endPoint.getY() }}
    {};

    /*
     * Copy constructor for Vector
     */
    Vector(const Vector<T> &copy)
            : Vector(copy.getEnd())
    {};

    /*
     * Returns the Punto corresponding to the end point of the vector.
     * This reference may not be edited.
     */
    const Punto<T>& getEnd() const { return m_end; }

    /*
     * Returns the X coordinate of the endpoint
     */
    T getX() const { return getEnd().getX(); }

    /*
     * Returns the Y coordinate of the endpoint
     */
    T getY() const { return getEnd().getY(); }

    /*
     * Returns the euclidean Norm of the Vector.
     */
    double euclideanNorm() const;

    /*
     * Returns the Vector obtained after performing normalization on this
     * vector.
     */
    Vector<double> vecNorm() const;

    Vector<T>& operator= (const Vector<T>& vector);
};

template<class T>
double Vector<T>::euclideanNorm() const {
    return std::sqrt(dotProduct(*this, *this));
}

template<class T>
Vector<double> Vector<T>::vecNorm() const {
    return (*this)*(1/((*this).euclideanNorm()));
}

/*
* Vector addition done coordinate-wise of the endpoints.
* Both Vector can have different types. The result will be of whatever type
* given by the implicit conversion (if there's any)
*/
template<class T, class S>
auto operator+(const Vector<T> &v1, const Vector<S> &v2) {
    auto sumV{ v1.getEnd() + v2.getEnd() };
    Vector<decltype(sumV.getX())> res{ sumV };
    return res;
}

/*
* Vector subtraction done coordinate-wise of the endpoints.
* Both Vector can have different types. The result will be of whatever type
* given by the implicit conversion (if there's any)
*/
template<class T, class S>
auto operator-(const Vector<T> &v1, const Vector<S> &v2) {
    auto minV{ -v2.getEnd() };
    Vector<decltype(minV.getX())> res{ v1+Vector(minV) };
    return res;
}

/*
 * Calculates the dot product between two vectors. The result is a scalar
 * corresponding to the sum of the products between all coordinates.
 */
template <class T, class S>
auto dotProduct(const Vector<T> &v1, const Vector<S> &v2)
{
    auto prodX{ v1.getEnd().getX() * v2.getEnd().getX() };
    auto prodY { v1.getEnd().getY() * v2.getEnd().getY() };
    return prodX + prodY;
}

/*
 * Scalar product between a vector and a value s.
 * see: scalar product between Punto and values.
 */
template <class T, class S>
auto operator*(const Vector<T> &v, S s)
{
    auto scaledPoint{ v.getEnd()*s };
    auto scaledVec = Vector(scaledPoint);
    return scaledVec;
}

template <class T, class S>
auto operator*(S s, const Vector<T> &v)
{
    return v*s;
}

/*
 * Returns the value in coordinate Z after performing cross product between two
 * vectors (considering them as 3D with Z=0). This is equivalent as just taking
 * the determinant between v1 and v2.
 */
template <class T, class S>
auto crossProdValue(const Vector<T> &v1, const Vector<S> &v2)
{
    auto firstCross{ v1.getEnd().getX() * v2.getEnd().getY() };
    auto secondCross{ v1.getEnd().getY() * v2.getEnd().getX() };
    return firstCross - secondCross;
}

/*
 * Vector equality. Endpoints must match to be considered equal.
 */
template <class T>
bool operator==(const Vector<T> &v1, const Vector<T> &v2) {
    return (v1.getEnd() == v2.getEnd());
}

template<class T>
Vector<T>& Vector<T>::operator=(const Vector<T> &vector) {
    m_end = vector.getEnd();

    return *this;
}

template <class T>
std::ostream& operator<<(std::ostream &out, const Vector<T> &v)
{
    out << "(start=(0,0), end=" <<v.getEnd() << ")";
    return out;
}

#endif //ELEM_GEOMETRICOS_VECTOR_H
