#ifndef MYTOOL_H
#define MYTOOL_H

#include<cmath>

//---------------------------------point----------------------------------
template<typename Type>
struct point {
	Type x, y;
	point() { x = y = (Type)0; };
	point(const Type x,const Type y);
	point & operator*=(const Type size);
	point operator*(const Type size) const;
	Type operator*(const point & other) const;
	point & operator+=(const point & other);
	point operator+(const point & other) const;
	Type abs() const;
};

template<typename Type>
point<Type>::point(const Type x,const Type y)
{
	this->x = x;
	this->y = y;
}

template<typename Type>
point<Type> & point<Type>::operator*=(const Type size) 
{
	x *= size;
	y *= size;
	return *this;
}

template<typename Type>
point<Type> point<Type>::operator*(const Type size) const
{
	point temp = *this;
	temp *= size;
	return temp;
}

template<typename Type>
Type point<Type>::operator*(const point<Type> & other) const
{
	return x * other.x + y * other.y;
}

template<typename Type>
point<Type> & point<Type>::operator+=(const point<Type> & other)
{
	x += other.x;
	y += other.y;
	return *this;
}

template<typename Type>
point<Type> point<Type>::operator+(const point<Type> & other) const
{
	point temp = *this;
	temp += other;
	return temp;
}

template<typename Type>
Type point<Type>::abs() const
{
	return sqrt(x * x + y * y);
}

//---------------------------------Circle---------------------------------
template<typename Type>
point<Type> CirclePoint(int this_count, int sum_count)
{
	const Type PI = (Type)3.1415926;
	if (sum_count <= 0)
		throw"Count Error";
	point<Type> Pt;
	Pt.x = cos(this_count * 2 * PI / sum_count);
	Pt.y = sin(this_count * 2 * PI / sum_count);
	return Pt;
}

#endif // !MYTOOL_H
//NOT DEFINE