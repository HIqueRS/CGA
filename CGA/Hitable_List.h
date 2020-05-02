#pragma once
#include "Hitable.h"
class Hitable_List : public Hitable
{
public:
	Hitable_List(){}
	Hitable_List(Hitable** l, int n) { list = l; list_size = n; }
	virtual bool Hit(const Ray& r, float t_min, float t_max, Hit_Record& rec) const;
	Hitable** list;
	int list_size;

};



