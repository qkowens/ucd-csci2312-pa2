// Quinn Owens
// Intermediate Programming PA2
// Prof. Ivo Georgiev
// 2/3/2016

#include"Point.h"
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<cmath>

namespace Clustering
{
	unsigned int Point::__idGen = 0;

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
		for (int pos = 0; pos < __dim; pos++)
			__values[pos] = bCloned.getValue(pos);
		__id = bCloned.__id;
	}

	Point & Point::operator=(const Point &otherPoint)
	{
		__dim = otherPoint.__dim;
		__id = otherPoint.__id;
		__values = new double[otherPoint.__dim];
		for (int pos = 0; pos < __dim; pos++)
			__values[pos] = otherPoint.__values[pos];
		return *this;
	}

	Point::~Point()
	{
		delete[] __values;
	}

	int Point::getId() const
	{
		return __id;
	}

	int Point::getDims() const
	{
		return __dim;
	}

	void Point::setValue(int dim, double newVal)
	{
		__values[dim] = newVal;
	}

	double Point::getValue(int dim) const
	{
		return __values[dim];
	}

	double Point::distanceTo(const Point & secPoint) const
	{

		double sum = 0;
		for (int pos = 0; pos < this->__dim; pos++)
		{
			sum += pow(secPoint.__values[pos] - this->__values[pos], 2);
		}
		return sqrt(sum);
	}

	Point & Point::operator*=(double operand)
	{
		for (int pos = 0; pos < this->__dim; pos++)
			__values[pos] *= operand;
		return *this;
	}

	Point & Point::operator/=(double operand)
	{
		for (int pos = 0; pos < this->__dim; pos++)
			__values[pos] /= operand;
		return *this;
	}

	const Point Point::operator*(double operand) const
	{
		return Point(*this) *= operand;
	}

	const Point Point::operator/(double operand) const
	{
		return Point(*this) /= operand;
	}

	double & Point::operator[](int index)
	{
		return __values[index];
	}

	Point &operator+=(Point & change, const Point & addend)
	{
		for (int pos = 0; pos < change.getDims(); pos++)
			change.setValue(pos, change.getValue(pos) + addend.getValue(pos));
		return change;
	}

	Point &operator-=(Point & change, const Point & addend)
	{
		for (int pos = 0; pos < change.getDims(); pos++)
			change.setValue(pos, change.getValue(pos) - addend.getValue(pos));
		return change;
	}

	const Point operator+(const Point & addOne, const Point & addTwo)
	{
		Point temp(addOne.getDims());
		for (int pos = 0; pos < addOne.getDims(); pos++)
			temp.setValue(pos, addOne.getValue(pos) + addTwo.getValue(pos));
		return temp;
	}

	const Point operator-(const Point & addOne, const Point & addTwo)
	{
		Point temp(addOne.getDims());
		for (int pos = 0; pos < addOne.getDims(); pos++)
			temp.setValue(pos, addOne.getValue(pos) - addTwo.getValue(pos));
		return temp;
	}

	bool operator==(const Point & equalOne, const Point & equalTwo)
	{
		if (equalOne.__id != equalTwo.__id)
			return false;
		if (equalOne.getDims() == equalTwo.getDims())
			for (int pos = 0; pos < equalOne.getDims(); pos++)
				if (equalOne.getValue(pos) != equalTwo.getValue(pos))
					return false;
		return true;
	}

	bool operator!=(const Point & equalOne, const Point & equalTwo)
	{
		return(!(equalOne == equalTwo));
	}

	bool operator<(const Point & compOne, const Point & compTwo)
	{
		for (int pos = 0; pos < compOne.getDims(); pos++)
		{
			if (compOne.getValue(pos) < compTwo.getValue(pos))
				return true;
			if (compOne.getValue(pos) > compTwo.getValue(pos))
				return false;
		}
		return false;
	}

	bool operator>(const Point & compOne, const Point & compTwo)
	{
		for (int pos = 0; pos < compOne.getDims(); pos++)
		{
			if (compOne.getValue(pos) < compTwo.getValue(pos))
				return false;
			if (compOne.getValue(pos) > compTwo.getValue(pos))
				return true;
		}
		return false;
	}

	bool operator<=(const Point & compOne, const Point & compTwo)
	{
		for (int pos = 0; pos < compOne.getDims(); pos++)
		{
			if (compOne.getValue(pos) < compTwo.getValue(pos))
				return true;
			if (compOne.getValue(pos) > compTwo.getValue(pos))
				return false;
		}
		return true;
	}

	bool operator>=(const Point & compOne, const Point & compTwo)
	{
		for (int pos = 0; pos < compOne.getDims(); pos++)
		{
			if (compOne.getValue(pos) < compTwo.getValue(pos))
				return false;
			if (compOne.getValue(pos) > compTwo.getValue(pos))
				return true;
		}
		return true;
	}

	std::ostream & operator<<(std::ostream & out, const Point & outPoint)
	{
		int pos = 0;
		for (; pos < outPoint.__dim - 1; pos++)
		{
			out << outPoint.getValue(pos) << ", ";
		}
		out << outPoint.__values[pos];
		return out;
	}

	std::istream & operator>>(std::istream & in, Point & inPoint)
	{
		std::string temp;
		int i = 0;
		while (getline(in, temp, ','))
		{
			double d;

			d = std::stod(temp);

			std::cout << "Value: " << d << std::endl;

			inPoint.setValue(i++, d);
		}


		return in;
	}
}
