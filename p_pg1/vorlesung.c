#include <stdio.h>
#include <stdlib.h>

// scanf nimmt einfach den input stream buffer,
// deswegen recht easy wenn man zu scanf hinpiped
// printf trunkiert nicht, sondern rounded
// also konvertierung trunkiert, ausgabe runded
int main()
{
	int *a = malloc(sizeof(int));
	int b = 0;

	scanf("%d", a);
	scanf("%d", &b);
	printf("value: %d", *a * b);
	return 0;
}
