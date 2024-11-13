#include <stdio.h>

float area_circle(float radius, float x_pos)
{
	if (radius > x_pos) {
		fprintf(stderr, "circle not fully over x-axis\n");
		return 0.0;
	}
	float area = 0.0;
	area = 22.0/7.0 * radius*radius;
	return area;
}

float area_under_circle(float radius, float x_pos)
{
	float c_area = area_circle(radius, x_pos);
	if (!c_area) {
		return 0.0;
	}
	float area_under_circle = 0;
	area_under_circle = (radius * 2.0 * x_pos) - area_circle(radius, x_pos)/2.0;
	return area_under_circle;
}

float area_under_and_circle(float radius, float x_pos)
{
	float cu_area = area_under_circle(radius, x_pos);
	if (!cu_area) {
		return 0.0;
	}
	float area_under_and_circle = 0;
	area_under_and_circle = cu_area + area_circle(radius, x_pos);
	return area_under_and_circle;
}
int main()
{
	float radius = 4.0;
	float x_position = 15.0;
	printf("c_area: %f\n", area_circle(radius, x_position));
	printf("uc_area: %f\n", area_under_circle(radius, x_position));
	printf("uc_and_area: %f\n", area_under_and_circle(radius, x_position));
	printf("uc - uc_and: %f\n", (area_under_and_circle(radius, x_position) - area_under_circle(radius, x_position)));
	return 0;
}
