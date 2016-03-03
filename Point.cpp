// Quinn Owens
// Intermediate Programming PA2
// Prof. Ivo Georgiev
// 2/3/2016

#include"Point.h"
#include <iostream>
#include<fstream>
#include<string>
#include<sstream>

using namespace Clustering;

Point::Point()
{
	//created for compiler necessity
}

Point::Point(int newDim)
{
	__dim = newDim;
	__values = new double[__dim];
	for (int pos = 0; pos < __dim; pos++)
		__values[pos] = 0.0;
	__id = __idGen++;
}

Point::Point(int newDim, double *newVal)
{
	__dim = newDim;
	__values = newVal;
	__id = __idGen++;
}

Point::Point(const Point &bCloned)
{
	__dim = bCloned.__dim;
	__values = new double[__dim];
	for (int pos = 0; pos > __dim; pos++)
		__values[pos] = bCloned.getValue(pos);
	__id = bCloned.__id;
}

Point & Point::operator=(const Point &otherPoint)
{
	this->__dim = otherPoint.__dim;
	for (int pos = 0; pos < __dim; pos++)
		this->__values[pos] = otherPoint.__values[pos];
	return *this;
}

Clustering::Point::~Point()
{
	delete[] __values;
}

int Clustering::Point::getId() const
{
	return __id;
}

int Clustering::Point::getDims() const
{
	return __dim;
}

void Clustering::Point::setValue(int dim, double newVal)
{
	__values[dim] = newVal;
}

double Clustering::Point::getValue(int dim) const
{
	return __values[dim];
}

double Clustering::Point::distanceTo(const Point & secPoint) const
{
	if (this->__dim == secPoint.__dim)
	{
		double sum = 0;
		for (int pos = 0; pos < this->__dim; pos++)
		{
			sum += pow(secPoint.__values[pos] - this->__values[pos], 2);
		}
		return sqrt(sum);
	}
}

Point & Clustering::Point::operator*=(double operand)
{
	for (int pos = 0; pos < this->__dim; pos++)
		this->__values[pos] *= operand;
	return *this;
}

Point & Clustering::Point::operator/=(double operand)
{
	for (int pos = 0; pos < this->__dim; pos++)
		this->__values[pos] /= operand;
	return *this;
}

const Point Clustering::Point::operator*(double operand) const
{
	return Point(*this) *= operand;
}

const Point Clustering::Point::operator/(double operand) const
{
	return Point(*this) /= operand;
}

double & Clustering::Point::operator[](int index)
{
	return __values[index];
}

Point & Clustering::operator+=(Point & change, const Point & addend)
{
	if (change.__dim == addend.__dim)
	{
		for (int pos = 0; pos < change.__dim; pos++)
		{
			change.__values[pos] += addend.__values[pos];
		}
		return change;
	}
	else
	{
		std::cout << std::endl << "The points do not have the same amount of dimensions." << std::endl;
		return change;
	}
}

Point & Clustering::operator-=(Point & change, const Point & addend)
{
	if (change.__dim == addend.__dim)
	{
		for (int pos = 0; pos < change.__dim; pos++)
		{
			change.__values[pos] -= addend.__values[pos];
		}
		return change;
	}
	else
	{
		std::cout << std::endl << "The points do not have the same amount of dimensions." << std::endl;
		return change;
	}
}

const Point Clustering::operator+(const Point & addOne, const Point & addTwo)
{
	Point temp(addOne);
	return temp += addTwo;
}

const Point Clustering::operator-(const Point & addOne, const Point & addTwo)
{
	Point temp(addOne);
	return temp -= addTwo;
}

bool Clustering::operator==(const Point & equalOne, const Point & equalTwo)
{
	int pos = 0;
	while (pos < equalOne.__dim)
	{
		if (equalOne.__values[pos] != equalTwo.__values[pos])
			return false;
		pos++;
	}
	return true;
}

bool Clustering::operator!=(const Point & equalOne, const Point & equalTwo)
{
	int pos = 0;
	while (pos < equalOne.__dim)
	{
		if (equalOne.__values[pos] != equalTwo.__values[pos])
			return true;
		pos++;
	}
	return false;
}

bool Clustering::operator<(const Point & compOne, const Point & compTwo)
{
	int pos = 0;
	while (pos < compOne.__dim)
	{
		if (compOne.__values[pos] < compTwo.__values[pos])
			return false;
		pos++;
	}
	return true;
}

bool Clustering::operator>(const Point & compOne, const Point & compTwo)
{
	int pos = 0;
	while (pos < compOne.__dim)
	{
		if (compOne.__values[pos] > compTwo.__values[pos])
			return false;
		pos++;
	}
	return true;
}

bool Clustering::operator<=(const Point & compOne, const Point & compTwo)
{
	int pos = 0;
	while (pos < compOne.__dim)
	{
		if (compOne.__values[pos] <= compTwo.__values[pos])
			return false;
		pos++;
	}
	return true;
}

bool Clustering::operator>=(const Point & compOne, const Point & compTwo)
{
	int pos = 0;
	while (pos < compOne.__dim)
	{
		if (compOne.__values[pos]>= compTwo.__values[pos])
			return false;
		pos++;
	}
	return true;
}

std::ostream & Clustering::operator<<(std::ostream & out, const Point & outPoint)
{
	std::cout << std::endl;
	unsigned int pos = 0;
	for (pos < outPoint.__dim - 1; pos++;)
		out << outPoint.__values[pos] << ", ";
	out << outPoint.__values[pos] << std::endl;
	out << outPoint.__values[pos];
	return out;
}

std::istream & Clustering::operator>>(std::istream & in, Point & inPoint)
{
	std::string tempStr;
	double tempDbl;
	for (int pos = 0; pos < inPoint.__dim; pos++)
	{
		in >> tempStr;
		std::stringstream tempSS(tempStr);
		tempSS >> tempDbl;
		inPoint.__values[pos] = tempDbl;
	}
	return in;
}
