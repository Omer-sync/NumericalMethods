#include<stdio.h>
#include<math.h>

void gauss_elimination(int m, int n, float A[50][50], float x[30]);
void printMatrix(int m, int n, float matrix[50][50]);
void parabola_fit(float functionValue,int size,float x[10],float y[10]);
void printVector(int m, float A[50]);
void saturation_growth(float functionValue,int size,float x[10],float y[10]);



int main()
{
    int i;
    float x[] = {5,10,15,20,25,30,35,40,45,50};
    float y[] = {17,24,31,33,37,37,40,40,42,41};
    
    int size = sizeof(x)/sizeof(x[0]);
    parabola_fit(17,size,x,y);
    //saturation_growth(17,size,x,y);
    //printf("\n\nSince Saturation Growth function's r^2 coefficient value is \ncloser to 1 than Parabola function,\nSaturation Growth Function is superior\n\n");

    return 0;
}

void saturation_growth(float functionValue,int size,float x[10],float y[10])
{
    printf("\n\n******Saturation Growth******\n");
    int i;
    float A[50][50];
    float solution[50];
    float f[50],f_reel[50], f_user;
    float S_t = 0, S_r = 0, S_y_x, S_y, r_two, r;
    float sumX = 0, sumY = 0, sumX_two = 0, sumX_Y = 0;
    float sumX_avrg, sumY_avrg;
    float a_0, a_1, a_2, A_3, B_3;
    
    A[0][0] = size;

    for ( i = 0; i < size; i++)
    {
        sumX += 1/x[i];
        A[0][1] = sumX;
        A[1][0] = sumX;

        sumY += 1/y[i];
        A[0][2] = sumY;

        sumX_two += (1/x[i])*(1/x[i]);
        A[1][1] = sumX_two;    

        sumX_Y += (1/x[i])*(1/y[i]);
        A[1][2] = sumX_Y;

    }
    sumX_avrg = sumX / size;
    sumY_avrg = sumY / size;

    gauss_elimination(2,3,A,solution);

    a_0 = solution[0];
    a_1 = solution[1];
    A_3 = 1/solution[0];
    B_3 = a_1/a_0;
    for ( i = 0; i < size; i++)
    {
        f[i] = a_0 + a_1*(1/x[i])  ;
        S_r += ((1/y[i]) - f[i]) * ((1/y[i]) - f[i]);
        S_t += ((1/y[i]) - sumY_avrg) * ((1/y[i]) - sumY_avrg);
    }
    printf("\n(1/x & 1/y)Function Results Vector\n");
    printVector(size,f);
    for ( i = 0; i < size; i++)
    {
        f_reel[i] = (A_3 * x[i]/ (B_3 + x[i])) ;
    }
    f_user =  (A_3 * functionValue/ (B_3 + functionValue));
    printf("\n(Original)Function Results Vector\n");
    printVector(size,f_reel);
    printf("\nf(%f) = %f\n",functionValue,f_user);


    S_y_x = sqrt(S_r / (size - 3) );
    S_y = sqrt(S_t/ (size - 1));
    r_two = (S_t -S_r)/S_t;
    r = sqrt(r_two);
    printf("\na0: %f a1: %f ", solution[0],solution[1]);
    printf("\n1/f(x) = %f + %fx ", solution[0],solution[1]);
    printf("\nf(x) = A_3 * x / (B_3 +x) = %f * x / (%f + x)",A_3,B_3);
    printf("\nS_r: %f\nS_y: %f\nS_t: %f\nS_y/x: %f\nr_2: %f\nr: %f",S_r,S_y,S_t,S_y_x,r_two,r);
    printf("\n%f",(1/a_0)*2/((a_1/a_0)+2));
}




void parabola_fit(float functionValue,int size,float x[10],float y[10])
{
    printf("\n******Parabola fit******\n");
    int i;
    float A[50][50];
    float solution[50];
    float f[50],f_user;
    float S_t = 0, S_r = 0, S_y_x, S_y, r_two, r;
    float sumX = 0, sumY = 0, sumX_two = 0, sumX_three = 0, sumX_four = 0, sumX_Y = 0, sumX_two_Y = 0;
    float sumX_avrg = 0, sumY_avrg = 0;
    float a_0 = 0, a_1 = 0, a_2 = 0;
    
    A[0][0] = size;

    for ( i = 0; i < size; i++)
    {
        sumX += x[i];
        A[0][1] = sumX;
        A[1][0] = sumX;

        sumY += y[i];
        A[0][3] = sumY;

        sumX_two += x[i]*x[i];
        A[0][2] = sumX_two;
        A[1][1] = sumX_two;
        A[2][0] = sumX_two;

        sumX_three += x[i]*x[i]*x[i];
        A[1][2] = sumX_three;
        A[2][1] = sumX_three;

        sumX_four += x[i]*x[i]*x[i]*x[i];
        A[2][2] = sumX_four;


        sumX_Y += x[i]*y[i];
        A[1][3] = sumX_Y;

        sumX_two_Y += x[i]*x[i]*y[i];
        A[2][3] = sumX_two_Y;
    }
    sumX_avrg = sumX / size;
    sumY_avrg = sumY / size;
    gauss_elimination(3,4,A,solution);


    a_0 = solution[0];
    a_1 = solution[1];
    a_2 = solution[2];
    for ( i = 0; i < size; i++)
    {
        f[i] = a_0 + a_1*x[i] + a_2*x[i]*x[i] ;
        S_r += (y[i] - f[i]) * (y[i] - f[i]);
        S_t += (y[i] - sumY_avrg) * (y[i] - sumY_avrg);
    }
    f_user = a_0 + a_1*functionValue + a_2*functionValue*functionValue;
    
    printf("\nFunction Results Vector\n");
    printVector(size,f);
    printf("\nf(%f) = %f\n",functionValue,f_user);
    S_y_x = sqrt(S_r / (size - 3) );
    S_y = sqrt(S_t/ (size - 1));
    r_two = (S_t -S_r)/S_t;
    r = sqrt(r_two);
    printf("\na0: %f a1: %f a2: %f ", solution[0],solution[1],solution[2]);
    printf("\nf(x) = %f + %fx + %fx^2 ", solution[0],solution[1],solution[2]);
    printf("\nS_r: %f\nS_y: %f\nS_t: %f\nS_y/x: %f\nr_2: %f\nr: %f",S_r,S_y,S_t,S_y_x,r_two,r);
    
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
void printMatrix(int m, int n, float A[50][50])
{
    int i,j;
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            printf("%lf\t",A[i][j]);
        }
        printf("\n");
    } 
}
void printVector(int m, float A[50])
{
    int i;
    for(i=0;i<m;i++)
    {
        printf("%lf\t",A[i]);
        printf("\n");
    } 
}