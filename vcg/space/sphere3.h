/****************************************************************************
* VCGLib                                                            o o     *
* Visual and Computer Graphics Library                            o     o   *
*                                                                _   O  _   *
* Copyright(C) 2004                                                \/)\/    *
* Visual Computing Lab                                            /\/|      *
* ISTI - Italian National Research Council                           |      *
*                                                                    \      *
* All rights reserved.                                                      *
*                                                                           *
* This program is free software; you can redistribute it and/or modify      *   
* it under the terms of the GNU General Public License as published by      *
* the Free Software Foundation; either version 2 of the License, or         *
* (at your option) any later version.                                       *
*                                                                           *
* This program is distributed in the hope that it will be useful,           *
* but WITHOUT ANY WARRANTY; without even the implied warranty of            *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
* GNU General Public License (http://www.gnu.org/licenses/gpl.txt)          *
* for more details.                                                         *
*                                                                           *
****************************************************************************/
/****************************************************************************
  History

$Log: not supported by cvs2svn $

****************************************************************************/

#ifndef VCG_SPHERE_H
#define VCG_SPHERE_H

#include <vcg/point3.h>

namespace vcg {

/** \addtogroup space */
/*@{*/
/** 
Templated class for 3D sphere.
  This is the class for definition of a sphere in 3D space. It is stored just as a Point3 and a radius
	@param T (template parameter) Specifies the type of scalar used to represent coords.
  Various policy could be added to improve efficience (keeping square of radius for instance).
*/

template <class T> class Sphere {
protected:
  Point3<T> _center;
	T _radius;
public:
	Sphere(): radius(-1) {}
  Sphere(const Point3<T> &center, T radius): _center(center), _radius(radius) {}

  T &Radius() { return _radius; }
  const T &Radius() const { return _radius; }
  Point3<T> &Center() { return _center; }
  const Point3<T> &Center() const { return _center; }

	bool IsEmpty() const { return _radius < 0; }
  ///return true if @param p - Center() <= Radius() 
  bool IsIn(const Point3<T> &p) const;

  void Add(Point3<T> &p);
	void Add(const Sphere &sphere);
  	
};

template <class T> void Sphere<T>::Add(const Sphere<T> &sphere) {
  if(IsEmpty()) {
			*this = sphere;
			return;
		}
		Point3<T> dist = sphere.center - _center;
    float distance = dist.Norm();
		float fartest = distance + sphere.Radius();

		if(fartest <= _radius) 
      return;
    if(distance == 0) 
      _radius = sphere.Radius();
    else {
	    _center += dist * ((fartest - _radius) / (dist.Norm() * 2));
		  _radius = (_radius + fartest)/2;
    }
}

template <class T> void Sphere<T>::Add(Point3<T> &p) {
	if(IsEmpty()) {
		_center = p;
		_radius = 0;
	}
	Point3<T> dist = p - _center;
	float fartest = dist.Norm();
	if(fartest <= _radius) return;
	_center += dist * ((fartest - _radius) / (fartest*2));
	_radius = (_radius + fartest)/2;
}  

template <class T> bool Sphere<T>::IsIn(const Point3<T> &p) const {
	Point3<T> dist = p - _center;
	return dist.Norm() <= _radius;
}

} //namespace


#endif