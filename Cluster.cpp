// Quinn Owens
// Intermediate Programming PA2
// Prof. Ivo Georgiev
// 2/3/2016

#include"Cluster.h"
#include"Point.h"
#include<iostream>
#include<string>
#include<sstream>

using namespace Clustering;

Clustering::LNode::LNode(const Point & p, LNodePtr n)
{
	Point point(p);
	point = p;
	next = n;
}

void Clustering::Cluster::__del()
{
	
}

void Clustering::Cluster::__cpy(LNodePtr pts)
{
	
}

//bool Clustering::Cluster::__in(const Point &p) const
//{
//}

Clustering::Cluster::Cluster()
{
	__size = 0;
	__points = nullptr;
}

Clustering::Cluster::Cluster(const Cluster & group)
{
	Cluster();
	for (int pos = 0; pos < group.__size; pos++)
		add(group[pos]);
}

Cluster & Clustering::Cluster::operator=(const Cluster & group)
{
	LNodePtr tempPtr;

	if (this == &group)
		return *this;
	else
	{
		while (__points != nullptr) {
			tempPtr = __points;
			__points = __points->next;
			delete tempPtr;
			__size--;
		}
		for (int i = 0; i < group.__size; i++)
			add(group[i]);
	}
	return *this;
}

Clustering::Cluster::~Cluster()
{
	LNodePtr point, keep;
	point = __points;
	for (int pos = 0; pos < __size; pos++)
	{
		keep = point->next;
		delete point;
		point = keep;
	}
}

int Clustering::Cluster::getSize() const
{
	return __size;
}

void Cluster::add(const Point& coord)
{
	Point temp(coord);
	if (__size == 0)
	{
		LNode tempNode(temp, NULL);
		__points = &tempNode;
	}

	else if (temp < __points->point)
	{
		LNode tempNode(temp, __points->next);
		__points = &tempNode;
	}
	else
	{
		LNodePtr point1 = __points;
		while (temp > (point1->next)->point && point1->next != NULL)
			point1 = point1->next;
		LNode tempNode(temp, point1->next->next);
		point1 = &tempNode;
	}
}

const Point & Clustering::Cluster::remove(const Point & remov)
{
	Point temp(remov);

	if (this->contains(remov))
	{
		LNodePtr remover, temp;
		temp = __points->next;
		while (temp->point != remov)
		{
			temp = temp->next;
			if (temp->point == remov)
			{
				remover = temp;
				temp = temp->next;
				delete temp;
				__size--;
			}
		}
	}
	return remov;
}


bool Clustering::Cluster::contains(const Point& point)
{
	for (int i = 0; i < __size; i++)
		if (point == (*this)[i])
			return true;
	return false;
}

const Point & Clustering::Cluster::operator[](unsigned int index) const
{
	LNodePtr holder;
    holder = __points;
    for(int i = 0; i < index; i++)
        holder = holder->next;
    return holder->point;
}

Cluster & Clustering::Cluster::operator+=(const Point & point)
{
	this->add(point);
	return *this;
}

Cluster & Clustering::Cluster::operator-=(const Point & point)
{
	this->add(point);
	return *this;
}

Cluster & Clustering::Cluster::operator+=(const Cluster & cluster)
{
	for (int pos = 0; pos < cluster.__size; pos++)
		this->add(cluster[pos]);
	return *this;
}

Cluster & Clustering::Cluster::operator-=(const Cluster & cluster)
{
	for (int pos = 0; pos < cluster.__size; pos++)
		this->remove(cluster[pos]);
	return *this;
}

std::ostream & Clustering::operator<<(std::ostream & out, const Cluster & cluster)
{
	for (int pos = 0; pos < cluster.__size; pos++)
		out << cluster[pos];
	return out;
}

std::istream & Clustering::operator>>(std::istream & in, Cluster & cluster)
{
	std::string tempStr;
	while (getline(in, tempStr))
	{
		std::stringstream tempSS(tempStr);
		int dims = (int)std::count(tempStr.begin(), tempStr.end(), ',') + 1;
		Point *tempPoint = new Point(dims);
		tempSS >> *tempPoint;
		cluster.add(*tempPoint);
	}
	return in;
}

bool Clustering::operator==(const Cluster & cluster1, const Cluster & cluster2)
{
	if (cluster1.__size != cluster2.__size)
		return false;
	for (int i = 0; i < cluster2.__size; i++)
	{
		if ((cluster1.__points[i]).point != (cluster2.__points[i]).point)
			return false;
	}

	return true;
}

bool Clustering::operator!=(const Cluster & cluster1, const Cluster & cluster2)
{
	return !(cluster1 == cluster2);
}

const Cluster Clustering::operator+(const Cluster & cluster1, const Point & cluster2)
{
	Cluster tempCluster(cluster1);
	tempCluster += cluster2;
	return tempCluster;
}

const Cluster Clustering::operator-(const Cluster & cluster1, const Point & cluster2)
{
	Cluster tempCluster(cluster1);
	tempCluster -= cluster2;
	return tempCluster;
}

const Cluster Clustering::operator+(const Cluster & cluster, const Cluster & point)
{
	Cluster tempCluster(cluster);
	tempCluster += point;
	return tempCluster;
}

const Cluster Clustering::operator-(const Cluster & cluster, const Cluster & point)
{
	Cluster tempCluster(cluster);
	tempCluster -= point;
	return tempCluster;
}
