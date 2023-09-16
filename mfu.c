#include <stdio.h>

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

int updatefreq(int s, int n, int freq[n][2])
{
    int i, flag = 0;
    for(i=0; i<n; i++)
    {
        if(freq[i][0] == s)
        {
            freq[i][1]++;
            flag = 1;
            return freq[i][1];
        }
    }
    if(flag == 0)
    {
        for(i=0; i<n; i++)
        {
            if(freq[i][0] == -1)
                break;
        }
        freq[i][0] = s;
        freq[i][1]++;
    }
    return freq[i][1];
}

int available(int s, int m, int f[m][3])
{
    int i; 
    for(i=0; i<m; i++)
    {
        if(f[i][0] == s)
            return i;       // if element s is found in frame, return index
    }
    return -1;
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

void printF(int s,int m, int f[m][3])
{
	int i;
    printf("\t[%d]",s);
	for(i=0; i<m; i++)
	{
        if(i != 0)
            printf("\t");
        if(f[i][0] != -1)
    		printf("\t\t%d\t\t%d\t\t%d\n",f[i][0],f[i][1],f[i][2]);
	}
}

int hasSpace(int m, int f[m][3])
{
    int i; 
    for(i=0; i<m; i++)
    {
        if(f[i][0] == -1)
            return i;
    }
    return -1;
}

int checkFreq(int m, int f[m][3])
{
    int i, max, flag = 0, index, count = 0; 
    for(i=0; i<m; i++)
    {
        if(i == 0)
        {
            max = f[i][2];
            index = i;
        }
        else
        {
            if(f[i][2] != max)
            {
                flag = 1;
                if(f[i][2] > max)
                {
                    max = f[i][2];
                    index = i;
                }
            }
        }
    }

    for(i=0; i<m; i++)
    {
        if(f[i][2] == max)
            count++;
    }

    if(flag == 0)
        return -1;
    if(flag == 1 && count == 1)
        return index;

    int maxtc;
    if(count > 1 && count < m)
    {
        for(i=0; i<m; i++)
        {
            if(f[i][2] == max)
            {
                if(i == 0)
                {
                    maxtc = f[i][1];
                    index = i;
                }
                else if(f[i][1] > maxtc)
                {
                    maxtc = f[i][1];
                    index = i;
                }
            }
        }
    }
    return index;
}

int LRU(int m, int f[m][3])
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

void line()
{
    int i;
    printf("\n\t");
    for(i=0; i<52; i++)
    {
        printf("_");
    }
    printf("\n\n");
}

int iterate(int n, int s[n], int freq[n][2], int m, int f[m][3])
{
    int i, newfreq, index, pf = 0;
    printf("\n\tElement\t      Frames\t   Timecounter\t   Frequency\n\n");
    for(i=0; i<n; i++)
    {
        newfreq = updatefreq(s[i],n,freq);
        
        if(available(s[i],m,f) == -1)
        {
            pf++;
            printf("!--");
            if(hasSpace(m,f) != -1)
            {
                index = hasSpace(m,f);
            }
            else
            {
                if(checkFreq(m,f) == -1)
                {
                    index = LRU(m,f);
                }
                else
                {
                    index = checkFreq(m,f);
                }
            }
            f[index][0] = s[i];
            timecounter(index,m,f,0);
        }
        else
        {
            index = available(s[i],m,f);
            timecounter(index,m,f,1);
        }  
        f[index][2] = newfreq;
        printF(s[i],m,f); 
        line();     
    }
    return pf;
}

void main()
{
    int i, n, m=3, pf;
    printf("\n\n\t\t\tMost Frequently Used\n\n");
    printf("\n Enter the total number of page requests: ");
    scanf("%d",&n);

    int s[n], freq[n][2], f[m][3];
    printf("\n Enter the %d page requests: ",n);
    //7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1
    for(i=0; i<n; i++)
    {
        scanf("%d",&s[i]);
        freq[i][0] = -1;
        freq[i][1] = 0;
        if(s[i] < 0)
        {
            printf("\n\t!-- Page requests cannot be negative --!");
            return;
        }
    }
	printf("\n Enter the no. of frames: ");
	scanf("%d",&m);
    setdefault(m,f);
    pf = iterate(n,s,freq,m,f);
    printf("\n\n\tThe total number of page faults: %d\n\n",pf);
}
