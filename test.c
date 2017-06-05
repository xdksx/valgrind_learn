#include<stdio.h>
#include<stdlib.h>
int main()
{
	int len=5;
	int i;
	int *pt=(int*)malloc(len*sizeof(int));
	int *p=pt;
	for(i=0;i<len;i++)
	{
		p++;
	}
	*p=5;
	printf("%d",*p);
	return 0;
}
