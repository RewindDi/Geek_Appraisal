#include<stdio.h>
void Euler(double a)
{
	double n = 0.001;
	while (1)
	{
	    double b = 0.999 * a;
		printf("%lf      %lf\n", n, b);
		if(a-b<0.000001)
		{
			break;
		}
		a = b; 
		n += 0.001;
	}

}
int main()
{
	int a;
	scanf("%d", &a);
	printf("       x       y\n");
	Euler(a);
	return 0;
}
