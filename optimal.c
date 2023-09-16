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

void print(int m, int f[m])
{
	int i; 
	for(i=0; i<m; i++)
	{
		printf(" %d",f[i]);
	}
}

int checkdemand(int pos, int ele, int n, int s[n], int m, int f[m], int demand[m])
{
	int i, j, max = -1, index = -1;
	for(i=0; i<m; i++)
	{
		demand[i] = 0;
		for(j=0; j<n; j++)
		{
			if(j > pos)
			{
				if(f[i] == s[j])
					break;
				else
					demand[i]++;
			}
		}
        
		if(i == 0)
		{
			max = demand[i];
			index = 0;
		}
		else if(demand[i] > max)
		{
			max = demand[i];
			index = i;
		}
	}
	printf("\t -Page Fault-  demand of (");
	print(m,f);
	printf(" ) is after (");
	print(m,demand);
	printf(" ) requests =>\treplace %d",f[index]);

	return index;
}

void setdefault(int m, int f[m])
{
	int i;
	for(i=0; i<m; i++)
		f[i] = -1;
}

int iterate(int n, int s[n], int m, int f[m])
{
    printf("\n\n\tPage\t       Frames\n\t---------------------------");
	int i, k = -1, index = -1, pf = 0;
	int demand[m];
	for(i=0; i<n; i++)
	{
		if(available(m,f,s[i]) == 0)
		{
			pf++;
			if(hasspace(m,f) == 1)
			{
				k++;
				f[k] = s[i];
			}
			else
			{
				index = checkdemand(i,s[i],n,s,m,f,demand);
				f[index] = s[i];			
			}
		}		
		printf("\n\t[%d]",s[i]);
		printF(m,f);
		if((i+1)%4 == 0 )
	    	printf("\n\n");
	}
	return pf;		
}

void main()
{
	int n, m = 3, i;
	printf("\n\t\t\tOptimal\n");
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




