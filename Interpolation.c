#include <stdio.h>
#include<math.h>


// Obtaining divided differences with this recursive function
float difference(int start, int size, float x[50],float y[50])
{    
    if (size == 1)
        return y[start];

    size--;
    
    return (((difference(start,size,x,y)-difference(start-1,size,x,y))/(x[start]-x[start-size])));
}
void newton_interpolate(float functionValue,int size, float x[50],float y[50],float diffs[50])
{
    printf("\nNewton Interpolation\n");

    int i,j;
    int length = size;
    float sum_1 = 0,sum_2 = 0;
    float multiplier = 1.0;
    
    // Obtaining divided differences and saving to an array
    for ( i = size-1; i >= 0; i--)
    {
        float deneme =  difference(size-1,size,x,y);
        diffs[i] = difference(size-1,size,x,y);
        size--; 
    }
    // Calculating function result 
    for ( i = 0; i < length; i++)
    {
        for ( j= 0; j < i; j++)
            multiplier *= functionValue - x[j];
        
        sum_1 += diffs[i]*multiplier;
        multiplier = 1.0;
    }
    // Calculating previus result to evaluate R_i
    for ( i = 0; i < length-1; i++)
    {
        for ( j= 0; j < i; j++)
            multiplier *= functionValue - x[j];
        
        sum_2 += diffs[i]*multiplier;
        multiplier = 1.0;
    }

    for ( j = 1; j < length; j++)
        printf("\n%d.div. difference: %f",j,diffs[j]);

    printf("\n\nf_%d(%f) = %f\n",length-1,functionValue,sum_1);
    printf("\nR_%d: %f\n",length-2,sum_1 - sum_2);
}

void lagrange_interpolate(float functionValue, int size, float x[50], float y[50],float x_new[50], float y_new[50],int size_new)
{
    printf("\nLagrange Interpolation\n");
    int i,j;
    float sum_1 = 0,sum_2 = 0, multiplier ;
    for ( i = 0; i < size; i++)
    {
        multiplier = 1.0;
        for ( j= 0; j < size ; j++)
        {
            if (j != i)
                multiplier *= ( functionValue - x[j] )/( x[i] - x[j] );
            
        }
        sum_1 += multiplier * y[i];
        
    }
    for ( i = 0; i < size_new; i++)
    {
        multiplier = 1.0;
        for ( j= 0; j < size_new ; j++)
        {
            if (j != i)
                multiplier *= ( functionValue - x_new[j] )/( x_new[i] - x_new[j] );
            
        }
        sum_2 += multiplier * y_new[i];
        
    }
    
    printf("\nf_%d(%f): %f\n", size-1,functionValue,sum_1);

    printf("\nf_%d(%f): %f\n", size_new-1,functionValue,sum_2);

    printf("\nR_%d: %f\n", size-1,sum_2-sum_1);
}


int main()
{
    //float x[] = {0,0.1,0.3,0.6,1.0};
    //float y[] = {-6.0000,-5.8948,-5.6501,-5.1779,-4.2817};
    float x_new[] = {0,0.1,0.3,0.6,1.0,1.1};
    float y_new[] = {-6.0000,-5.8948,-5.6501,-5.1779,-4.2817,-3.9958};
    
    float diffs[50];
    
    int size_new = sizeof(x_new)/sizeof(x_new[0]);
    float functionValue = 16;


    //lagrange_interpolate(functionValue,size,x,y,x_new,y_new,size_new);
    float x[] = {10,15,20,22.5};
    float y[] = {227.04,362.78,517.35,602.97};
    int size = sizeof(x)/sizeof(x[0]);
    newton_interpolate(functionValue,size,x,y,diffs);
    
    newton_interpolate(functionValue,size_new,x_new,y_new,diffs);

    return 0;
}