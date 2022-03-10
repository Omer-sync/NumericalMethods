#include<stdio.h>
#include<math.h>


void function(float functionValue,int interval_size,float solution[50],float x[50], float y[50])
{
    int i, j = 0;
    float seconds[50];
    float interval_values[50];

    // Second Derivative values assignment to array 
    seconds[0] = 0;
    seconds[1] = solution[0];
    seconds[2] = solution[1];
    seconds[3] = 0;

    // Calculating function result in each interval with given value
    for ( i = 0; i < interval_size; i++)
    {
        interval_values[i] = ( seconds[i] * pow(x[i+1] - functionValue,3) / ( 6 * (x[i+1] - x[i]))) +  
                             ( seconds[i+1] * pow(functionValue - x[i],3) / ( 6 * (x[i+1] - x[i]))) +
                             ( (( y[i] / (x[i+1] - x[i])) - ( seconds[i] * (x[i+1] - x[i]) / 6)) * (x[i+1] - functionValue)) +
                             ( (( y[i+1] / (x[i+1] - x[i])) - ( seconds[i+1] * (x[i+1] - x[i]) / 6)) * (functionValue - x[i]));
    }

    // Finding the right interval to calculate more precise result
    while (x[j+1] < functionValue && j != interval_size-1)
        j++;
    
    printf("\nf(%f)",functionValue);

    if (x[j+1] < functionValue || x[j] > functionValue)
        printf("\nThis value is not in range of cubic spline interpolation!!\n");
    
    else
        printf("\nAccording to %d. interval result is : %f\n",j+1,interval_values[j]);
    
}


void cubic_spline(int size,float functionValue,float x[50],float y[50])
{

    float A[50][50] ;
    float solution[50];

    // Filling A array to find unknown second derivatives according to equation
    A[0][0] = 2 * (x[2] - x[0]);
    A[0][1] = (x[2] - x[1]);
    A[0][2] = (6/(x[1] - x[0]) * (y[0] - y[1])) +  (6/(x[2] - x[1]) * (y[2] - y[1]));

    A[1][0] = (x[2] - x[1]);
    A[1][1] = 2 * (x[3] - x[1]);    
    A[1][2] = (6/(x[2] - x[1]) * (y[1] - y[2])) +  (6/(x[3] - x[2]) * (y[3] - y[2]));

    // Obtaining unknown second derivatives
    gauss_elimination(2,3,A,solution);

    // Calculating function result with taken value
    function(functionValue,size -1,solution,x,y);
}


void gauss_elimination(int m, int n, float A[50][50], float x[50])
{
    int i,j,k;
    for(i=0;i<m-1;i++)
    {
        for(k=i+1;k<m;k++)
        {
            if(fabs(A[i][i])<fabs(A[k][i]))
            {
                for(j=0;j<n;j++)
                {                
                    float temp;
                    temp=A[i][j];
                    A[i][j]=A[k][j];
                    A[k][j]=temp;
                }
            }
        }
        for(k=i+1;k<m;k++)
        {
            float  term=A[k][i]/ A[i][i];
            for(j=0;j<n;j++)
                A[k][j]=A[k][j]-term*A[i][j];
        }
         
    }
    for(i=m-1;i>=0;i--)
    {
        x[i]=A[i][n-1];
        for(j=i+1;j<n-1;j++)
            x[i]=x[i]-A[i][j]*x[j];
        
        x[i]=x[i]/A[i][i];
    }
}


int main()
{
    float x[] = {1,2,3,4};
    float y[] = {1.0,0.5,(float)1/3,0.25};

    int size = sizeof(x)/ sizeof(x[0]);

    cubic_spline(size,1.2,x,y);
    cubic_spline(size,2.5,x,y);
    cubic_spline(size,3.4,x,y);
    cubic_spline(size,5,x,y);
    cubic_spline(size,4,x,y);
    cubic_spline(size,3,x,y);
    cubic_spline(size,2,x,y);
    cubic_spline(size,1,x,y);
    cubic_spline(size,0,x,y);

    printf("\n");
    return 0;
}