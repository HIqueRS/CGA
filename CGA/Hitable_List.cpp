#include "Hitable_List.h"
bool Hitable_List::Hit(const Ray& r, float  t_min, float t_max, Hit_Record& rec)const
{
	Hit_Record temp_rec;
	bool hit_anything = false;
	double closest_so_far = t_max;
	for (int i = 0; i < list_size; i++)
	{
		if (list[i]->Hit(r, t_min, closest_so_far, temp_rec))
		{
			hit_anything = true;
			closest_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}
	return hit_anything;
}