#include <stdio.h>

int hasspace(int m, int f[m][2])
{
	int i;
	for(i=0; i<m; i++)
	{
		if(f[i][0] == -1)
			return 1;
	}
	return 0;
}

int available(int m, int f[m][2], int x)
{
	int i;
	for(i=0; i<m; i++)
		if(f[i][0] == x)
			return i;
	return -1;
}

void printF(int m, int f[m][2])
{
	int i;
	for(i=0; i<m; i++)
	{
		printf("\t%d (%d)",f[i][0],f[i][1]);
	}
}

void timecounter(int k, int m, int f[m][2])
{
    int i;
	for(i=0; i<m; i++)
	{
	    if(i == k)
	        f[i][1] = 0;
	    else if(f[i][0] != -1)
	        f[i][1] = f[i][1] +1;
	}    
}

int LRU(int m, int f[m][2])
{
    int i, max, index; 
    for(i=0; i<m; i++)
    {
        if(i == 0)
        {
            max = f[i][1];
            index = i;
        }
        else if(f[i][1] > max)
        {
            max = f[i][1];
            index = i;
        }
    }
    return index;
}

int iterate(int n, int s[n], int m, int f[m][2])
{
    printf("\n\n\t\tPage\t Frame (Time-counter)\n\t\t--------------------------------\n\n");
	int i, k = -1, pf = 0, index = -1;
	for(i=0; i<n; i++)
	{
		printf("\t");
		if( available(m,f,s[i]) == -1 )
		{
			if(hasspace(m,f) == 1)
			{
				k++;
				f[k][0] = s[i];
				pf++;
				timecounter(k,m,f);
			}
			else
			{
				pf++;
				index = LRU(m,f);
				f[index][0] = s[i];
				timecounter(index,m,f);
				
				printf("!--");
			}
		}
		else
		{
            timecounter( available(m,f,s[i]), m,f);
		}

		printf("\t[%d]",s[i]);
		printF(m,f);
		printf("\n");
		if((i+1)%4 == 0 )
			printf("\n\n");
	}
	return pf;		
}

void setdefault(int m, int f[m][2])
{
	int i;
	for(i=0; i<m; i++)
	{
		f[i][0] = -1;
		f[i][1] = -1;
	}
}

void main()
{
	int n, m = 3, i;
	printf("\n\t\t\tLRU\n");
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
	printf("\n");
	int f[m][2];
	setdefault(m,f);
	int pf = iterate(n,s,m,f);
	printf("\n\tThe Total number of page faults: %d\n\n",pf);
}




