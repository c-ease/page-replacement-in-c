#include <stdio.h>

int hasspace(int m, int f[m])
{
	int i;
	for(i=0; i<m; i++)
	{
		if(f[i] == -1)
			return 1;
	}
	return 0;
}

int available(int m, int f[m], int x)
{
	int i;
	for(i=0; i<m; i++)
		if(f[i] == x)
			return 1;
	return 0;
}

void printF(int m, int f[m])
{
	int i;
	for(i=0; i<m; i++)
		printf("\t%d",f[i]);
}

int iterate(int n, int s[n], int m, int f[m])
{
    printf("\n\n\t\tPage\t     Frames\n\t\t---------------------------\n\n");
	int i, k = -1, pf = 0;
	for(i=0; i<n; i++)
	{
		printf("\t");
		if(available(m,f,s[i]) != 1)
		{
			pf++;
			k++;
			if(k >= m)
				k = 0;
			f[k] = s[i];

			if(hasspace(m,f) != 1)
			{
				printf("!--");
			}
		}
		printf("\t[%d]",s[i]);
		printF(m,f);
		printf("\n");
		if((i+1)%4 == 0 )
			printf("\n\n");
	}
	return pf;		
}

void setdefault(int m, int f[m])
{
	int i;
	for(i=0; i<m; i++)
		f[i] = -1;
}

void main()
{
	int n, m = 3, i;
	printf("\n\t\t\tFIFO\n");
	printf("\n Enter the length of the reference string: ");
	scanf("%d",&n);
	
	int s[n];
	printf("\n Enter the reference string: "); 
	//7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1
	for(i=0; i<n; i++)
	{
		scanf("%d",&s[i]);
		if(s[i] < 0)
		{
			printf("\n Reference string cannot have negative entries.\n");
			return;
		}
	}
	printf("\n Enter the no. of frames: ");
	scanf("%d",&m);
	int f[m];
	setdefault(m,f);
	int pf = iterate(n,s,m,f);
	printf("\n\tThe Total number of page faults: %d\n\n",pf);
}




