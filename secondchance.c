#include <stdio.h>

int hasspace(int m, int f[m][3])
{
	int i;
	for(i=0; i<m; i++)
	{
		if(f[i][0] == -1)
			return i;
	}
	return -1;
}

int available(int m, int f[m][3], int x)
{
	int i;
	for(i=0; i<m; i++)
		if(f[i][0] == x)
			return i;
	return -1;
}

void printF(int m, int f[m][3])
{
	int i;
	for(i=0; i<m; i++)
	{
		if(f[i][0] != -1)
		{
			if(i != 0)
				printf("\t");
			printf("\t\t%d\t     %d\t\t  %d\n",f[i][0],f[i][1],f[i][2]);
		}
	}
}

int doweskip(int k, int m, int skip[m])
{
	int i;
	for(i=0; i<m; i++)
		if(k == skip[i])
			return 1;
	return 0;
}

int FIFO(int m, int f[m][3], int skip[m])
{
    int i, index, maxtc, flag = 0; 
    for(i=0; i<m; i++)
    {
		if(doweskip(f[i][0],m,skip) == 0)
		{
			if(flag == 0)
			{
				maxtc = f[i][1];
				index = i;
				flag = 1;
			}
			else if(f[i][1] > maxtc)
			{
				maxtc = f[i][1];
				index = i;
			}
		}
    }

    return index;
}

void updateskip(int k, int m, int skip[m])
{
	int i;
	for(i=0; i<m; i++)
	{
		if(skip[i] == -1)
		{
			skip[i] = k;
			return;
		}
	}
}

int getvictim(int m, int f[m][3])
{
    int i, index, count = 0, maxtc, flag = 0, skip[m];
	
	for(i=0; i<m; i++)
		skip[i] = -1;
    
	for(i=0; i<m; i++)
        if(f[i][2] == 1)
            count++;
    
    if(count == 0 || count == m)
    {
        if(count == m)
           	for(i=0; i<m; i++)					
                f[i][2] = 0;
        index = FIFO(m,f,skip);
    }
    else
    {
        for(i=0; i<m; i++)					
        {
			index = FIFO(m,f,skip);
			if(f[index][2] == 1)
			{
				f[index][2] = 0;
				updateskip(f[index][0],m,skip);
			}
			else
				break;
        }
    }
    return index;	
}

void timecounter(int k, int m, int f[m][3], int flag)
{
    int i;
	for(i=0; i<m; i++)
	{
        if(flag == 1 && f[i][0] != -1)
            f[i][1]++;
        else if(flag == 0 && f[i][0] != -1)
        {
            if(i == k)
                f[i][1] = 0;
            else
                f[i][1]++;
        }
	}    
}

void line()
{
	int i;
	printf("\n\t"); 
	for(i=0; i<55; i++)
		printf("_");
	printf("\n\n");
}

int iterate(int n, int s[n], int m, int f[m][3])
{
    printf("\n\n\tPage\t      Frame\ttime-counter\treference-bit");
	line();
	int i, k = -1, pf = 0, index = -1;
	for(i=0; i<n; i++)
	{
		//printf("\t");
		if( available(m,f,s[i]) == -1 )
		{
			pf++;
			if(hasspace(m,f) != -1)
			{
				index = hasspace(m,f);
				f[index][0] = s[i];
				timecounter(index,m,f,0);
				f[index][2] = 0;
			}
			else
			{
				index = getvictim(m,f);
				f[index][0] = s[i];
				timecounter(index,m,f,0);
				printf(" !--");
			}
		}
		else
		{
			index = available(m,f,s[i]);
            timecounter(index,m,f,1);
            f[index][2] = 1;
		}

		printf("\t[%d]",s[i]);
		printF(m,f);
		line();

	}
	return pf;		
}

void setdefault(int m, int f[m][3])
{
	int i;
	for(i=0; i<m; i++)
	{
		f[i][0] = -1;
		f[i][1] = -1;
		f[i][2] = -1;
	}
}

void main()
{
	int n, m = 3, i;
	printf("\n\n\t\tSecond Chance Algorithm\n");
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
	int f[m][3];
	setdefault(m,f);
	int pf = iterate(n,s,m,f);
	printf("\n\tThe Total number of page faults: %d\n\n",pf);
}




