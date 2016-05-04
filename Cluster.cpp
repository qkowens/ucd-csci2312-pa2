// Quinn Owens
// Intermediate Programming PA2
// Prof. Ivo Georgiev
// 2/3/2016

#include"Cluster.h"
#include"Point.h"
#include<iostream>
#include<string>
#include<sstream>

namespace Clustering
{
	typedef Point * PointPtr;

	LNode::LNode(const Point & p, LNodePtr n) : point(p), next(n)
	{
	}


	void Cluster::__del()
	{
	}

	void Cluster::__cpy(LNodePtr pts)
	{
	}

	bool Clustering::Cluster::__in(const Point &p) const
	{
	}

	Cluster::Cluster()
	{
		__size = 0;
		__points = NULL;
	}

	Cluster::Cluster(const Cluster & bCloned) : Cluster()
	{
		for (int pos = 0; pos < bCloned.__size; pos++)
			add(bCloned[pos]);
	}

	Cluster & Cluster::operator=(const Cluster & group)
	{
		if (this == &group)
			return *this;
		else
		{
			if (__points != NULL)
			{
				LNodePtr prev = __points;
				LNodePtr curr = NULL;
				while (prev != NULL)
				{
					curr = prev->next;
					delete  prev;
					prev = curr;
				}
				__size = 0;
				__points = NULL;
			}
			for (int i = 0; i < group.__size; i++)
				add(group[i]);
		}
		return *this;
	}

	Cluster::~Cluster()
	{
		if (__points != NULL) 
		{
			LNodePtr prev = __points;
			LNodePtr curr = NULL;
			while (prev != NULL) 
			{
				curr = prev->next;
				delete  prev;
				prev = curr;
			}
		}
	}

	int Cluster::getSize() const
	{
		return __size;
	}

	void Cluster::add(const Point& coord)
	{
		Point temp(coord);
		LNodePtr newP = new LNode(temp, NULL);
		LNodePtr curr = __points;
		LNodePtr next = __points;
		if (__points == NULL) {
			__points = newP;
			__size++;
		}
		else if (__points->next == NULL) 
		{
			if (coord < __points->point) 
			{
				__points = newP;
				newP->next = curr;
				__size++;
			}
			else 
			{
				__points->next = newP;
				__size++;
			}
		}
		else
		{
			next = next->next;
			if (coord < curr->point) 
			{
				__points = newP;
				newP->next = curr;
				__size++;
				return;
			}
			while (next != NULL) 
			{
				if (coord < next->point) 
				{
					curr->next = newP;
					newP->next = next;
					__size++;
					return;
				}
				next = next->next;
				curr = curr->next;
			}
			curr->next = newP;
			__size++;
		}
	}

	const Point & Cluster::remove(const Point & remov)
	{
		LNodePtr prev = __points;

		if (prev->next == NULL)
		{
			if (prev->point == remov)
			{
				__points = NULL;
				__size = 0;
				delete prev;
			}
		}
		else
		{
			bool found = false;
			prev = __points;
			LNodePtr curr = __points->next;

			if (__points->point == remov)
			{
				found = true;
				__points = curr;
				--__size;
				delete prev;
			}
			for (curr; !found && curr != NULL; curr = curr->next)
			{
				if (curr->point == remov)
				{
					found = true;
					prev->next = curr->next;
					--__size;
					delete curr;
				}
				else
					prev = curr;
			}
		}
		return remov;
	}


	bool Cluster::contains(const Point& tarPoint)
	{
		bool target = false;

		LNodePtr curr = __points;

		for (curr; !target && curr != NULL; curr = curr->next)
		{
			if (curr->point == tarPoint)
				target = true;
		}
		return target;
	}

	const Point & Cluster::operator[](unsigned int index) const
	{
		if (__points != NULL && index < __size && index >= 0)
		{
			LNodePtr curr = __points;

			for (int pos = 0; pos < index; ++pos)
				curr = curr->next;
			return curr->point;
		}
		else
			return NULL;
	}

	Cluster & Cluster::operator+=(const Point & point)
	{
		add(point);
		return *this;
	}

	Cluster & Cluster::operator-=(const Point & point)
	{
		remove(point);
		return *this;
	}

	Cluster & Cluster::operator+=(const Cluster & cluster)
	{
		LNodePtr curr = cluster.__points;
		for (curr; curr != NULL; curr = curr->next)
			if (!(contains(curr->point)))
				add(curr->point);
		return *this;
	}

	Cluster & Cluster::operator-=(const Cluster & cluster)
	{
		LNodePtr curr = cluster.__points;
		for (curr; curr != NULL; curr = curr->next)
			if((contains(curr->point)))
				remove(curr->point);
		return *this;
	}

	std::ostream & operator<<(std::ostream & out, const Cluster & cluster)
	{
		LNodePtr curr = cluster.__points;
		
		if (&curr != NULL)
		{
			for (curr; &curr->point != NULL; curr = curr->next)
			{
				out << &curr->point;
				if (&curr->next != NULL)
					out << "\n";
			}
		}
		return out;
	}

	std::istream & operator>>(std::istream & in, Cluster & cluster)
	{
		std::string line;
		while (getline(in, line))
		{
			int tempInt = static_cast<int>(std::count(line.begin(), line.end(), ','));
			Point *temp = new Point(tempInt + 1);
			std::stringstream lineStream(line);

			lineStream >> *temp;

			cluster.add(*temp);
		}
		return in;
	}

	bool operator==(const Cluster & cluster1, const Cluster & cluster2)
	{
		if (cluster1.__size != cluster2.__size)
			return false;
		LNodePtr current1 = cluster1.__points;
		LNodePtr current2 = cluster2.__points;
		bool equal = true;
		while (current1 != NULL && current2 != NULL)
		{
			if (current1->point != current2->point)
				equal = false;
			current1 = current1->next;
			current2 = current2->next;
		}
		return equal;
	}

	bool operator!=(const Cluster & cluster1, const Cluster & cluster2)
	{
		return !(cluster1 == cluster2);
	}

	const Cluster operator+(const Cluster & cluster1, const Point & cluster2)
	{
		Cluster newCluster(cluster1);
		return newCluster += cluster2;
	}

	const Cluster operator-(const Cluster & cluster1, const Point & cluster2)
	{
		Cluster newCluster(cluster1);
		return newCluster -= cluster2;
	}

	const Cluster operator+(const Cluster & cluster, const Cluster & point)
	{
		Cluster newCluster(cluster);
		return newCluster += point;
	}

	const Cluster operator-(const Cluster & cluster, const Cluster & point)
	{
		Cluster newCluster(cluster);
		return newCluster -= point;
	}
}