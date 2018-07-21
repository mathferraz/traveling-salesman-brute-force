#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*set the size of the array*/
#define size 4

int ary[size][size],completed[size],cost=0;
long int numItera = 0;

/*set the size of the array*/
void takeInput()
{
    int i,j;
    for(i=0; i < size; i++)
    {
        for( j=0; j < size; j++)
        {
            if(i == j)
            {
                ary[i][j] = 0;
            }
            else
            {
                if(ary[j][i] != 0)
                {
                    ary[i][j] = ary[j][i];
                }
                else
                {
                    ary[i][j] = i+i*8;
                }
            }
        }
    }
    for(i=0; i<size; i++)
    {
        completed[i] = i;
    }
}

/*make the change in recursion*/
void swap(int *x, int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

/*find the current cost*/
void findCost(int *a)
{
    int i;
    int costAux = 0;
    for(i=0; i < size; i++)
    {
        if(i == size-1)
        {
            costAux = costAux + ary[a[i]][a[0]];
        }
        else
        {
            costAux = costAux + ary[a[i]][a[i+1]];
        }
    }

    /*print the current cost*/
    printf("\n");
    for(i=0; i<size; i++)
    {
        printf("%d ", a[i]);
    }
    printf("- %d", costAux);

    /*verify which cost is better*/
    if(costAux < cost)
    {
        cost = costAux;
        for(i=0;i<size;i++)
        {
            completed[i] = a[i];
        }

    }

    /*iterates the iteration counter*/
    numItera ++;
}

/*starts recursion*/
void permute(int *a, int l, int r)
{
    int i;
    if (l == r)
    {
        findCost(a);
    }
    else
    {
        for (i = l; i <= r; i++)
        {
            swap((a+l), (a+i));
            permute(a, l+1, r);
            swap((a+l), (a+i));
        }
    }
}

/*starts some variables and calls recursion*/
int vectorFind()
{
    int arr[size];
    int n = sizeof(arr)/sizeof(arr[0]);
    int i = 0;
    for(i=0;i<size; i++)
    {
        arr[i] = completed[i];
    }
    permute(arr, 0, n-1);
    return 0;
}

int main()
{
    int i = 0;

    takeInput();
    for(i=0; i<size; i++)
    {
        if(i == size-1)
        {
            cost = cost + ary[completed[i]][completed[0]];
        }
        else
        {
            cost = cost + ary[completed[i]][completed[i+1]];
        }
    }

    /*getTime*/
    clock_t begin = clock();

    /*starts the master function*/
    vectorFind();

    printf("\n\nBest: ");
    for(i=0; i<size; i++)
    {
        printf("%d -> ", completed[i]);
    }
    printf("%d", completed[0]);
    printf("\nMinimum cost: %d ",cost);
    printf("\nNumber of iterations: %ld",numItera);

    /*printTime*/
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\n\nRuntime: %f\n", time_spent);
    return 0;
}
