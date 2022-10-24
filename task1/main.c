#include<stdio.h>
#include<math.h> 
void Euler(double a)
{
	double n = 0.001;
	double h = 0.001; 
	while (1)
	{
	    double b = 0.999 * a;
		printf("%lf      %lf\n", n, b);
		if(a-b<0.001*h)
		{
			break;
		}
		a = b; 
		n += 0.001;
	}

}
int main()
{
	double a;
	scanf("%lf", &a);
	//a=exp(1)*a;
	//a=acos(-1.0)*a;
	printf("%lf\n",a);
	printf("       x       y\n");
	Euler(a);
	return 0;
}
