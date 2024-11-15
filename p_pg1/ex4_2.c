#include <stdio.h>

float area_circle(float radius, float x_pos)
{
	if (radius > x_pos) {
		// wenn hier nicht geprinted werden soll und es mehr
		// als eine Art fehler moeglich waere muessen die return
		// werte gegen verschiedene error faelle gecheckt werden
		// ausserdem muesste ich hier auch checken wenn radius 0.0
		// ist und dafuer entweder keine oder ne andere error variable
		// definieren, muesste ich hier aber auch abchecken
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

float area_any_circle(float radius, float x_pos)
{
	// hier muesste ich doch erstmal die schnittpunkte mit der
	// x-achse ausrechnen um die aufgabe zu machen???
	return 0.0;
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
