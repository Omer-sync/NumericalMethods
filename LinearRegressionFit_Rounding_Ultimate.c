#include<stdio.h>
#include<math.h>
#include<stdlib.h>

void gauss_elimination(int m, int n, double A[50][50], double x[30]);
void printMatrix(int m, int n, double matrix[50][50]);
void polynomial_fit(int plug_Equation,int significantDigit_equation,int choice_equation,int plug,int choice,int significantDigit,int degree,double functionValue,int size,double x[10],double y[10]);
void printVector(int m, double A[50]);
void nonLinear_fit(int plug_Equation,int significantDigit_equation,int choice_equation,int plug,int choice,int significantDigit,int type,double functionValue,int size,double x[10],double y[10]);
// Function to round - off(1) / Chop off(0)   the number
double Round_off(int plug,double N, double n, int choice);
double polynomial_equation(int plug_Equation,int significantDigit_equation,int choice_equation,int degree,double solution[50], double x[50],int index);




int main()
{
    int i;
    //double x[] = {5,10,15,20,25,30,35,40,45,50};
    //double y[] = {17,24,31,33,37,37,40,40,42,41};
    //double x[] = {1,2,3,4,5,6,7};
    //double y[] = {0.5,2.5,2,4,3.5,6,5.5};
    //double x[] = {1,2,3,4,5,6,7,8,9,10};
    //double y[] = {45000,50000,60000,80000,110000,150000,200000,300000,500000,1000000};
    //double x[] = {1,2,3,5,6,7,8,9,10,12,13,14,15,16,18,19,21,22};
    //double y[] = {100,90,80,60,60,55,60,65,70,70,75,76,78,79,90,99,99,100};
    //double x[] = {0,1,2,3,4,5};
    //double y[] = {2.1,7.7,13.6,27.2,40.9,61.1};
    //double x[] = {1,2,3,4,5};
    //double y[] = {0.5,1.7,3.4,5.7,8.4};
    //double x[50] = {0.25,0.5,0.75,1,1.25};
    //double y[50] = {0.09,1,0.64,1.21,1.69};
    double x[50] = {70,75,77,80,82,84,87,90};
    double y[50] = {2.10,2.12,2.15,2.20,2.22,2.23,2.26,2.30};
    int plug_Equation = 0;
    int significantDigit_equation = 4;
    int choice_equation = 1;
    int plug = 0;
    int choice = 1;
    int significantDigit = 4;
    int degree = 2;
    double functionValue = 95;
    int type = 6;
    int size = 8;
    //int s = sizeof(x);
    //int a = sizeof(x[0]);

    //polynomial_fit(plug_Equation,significantDigit_equation,choice_equation,plug,choice,significantDigit,degree,functionValue,size,x,y);
    
    nonLinear_fit(plug_Equation,significantDigit_equation,choice_equation,plug,choice,significantDigit, type, functionValue, size, x, y);


   // nonLinear_fit(17,size,x,y);

    return 0;
}

void nonLinear_fit(int plug_Equation,int significantDigit_equation,int choice_equation,int plug,int choice,int significantDigit,int type,double functionValue,int size,double x[10],double y[10])
{
    
    int i,j,k;
    double A[50][50]= {0};
    double solution[50]= {0};
    double f[50]= {0},f_reel[50]= {0}, f_user;
    double S_t = 0, S_r = 0, S_y_x, S_y, r_two, r;
    double sumX = 0, sumY = 0, sumX_two = 0, sumX_Y = 0;
    double sumX_avrg, sumY_avrg;
    double a_0, a_1, a_2, A_3, B_3;
    double tableContent[50][50] = {0};
    A[0][0] = size;

    for ( i = 0; i < size; i++)
    {   
        //Saturation Growth
        if (type == 1)
        {
            sumX += Round_off(plug,1/x[i],significantDigit,choice);
            sumY += Round_off(plug,1/y[i],significantDigit,choice);
            sumX_two += Round_off(plug,pow(1/x[i],2),significantDigit,choice);
            sumX_Y += Round_off(plug,((1/x[i])*(1/y[i])),significantDigit,choice);
  
        }
        //Exponential
        else if (type == 2)
        {
            
            sumX += x[i];
            sumY += Round_off(plug,log(y[i]),significantDigit,choice);
            sumX_two += pow(x[i],2);
            sumX_Y += Round_off(plug,((x[i])*(log(y[i]))),significantDigit,choice);
            
        }
        //Power Equation
        else if (type == 3)
        {
            
            sumX += Round_off(plug,log10(x[i]),significantDigit,choice);
            sumY += Round_off(plug,log10(y[i]),significantDigit,choice);
            sumX_two += Round_off(plug,pow(log10(x[i]),2),significantDigit,choice);
            sumX_Y += Round_off(plug,((log10(x[i]))*(log10(y[i]))),significantDigit,choice);
        }
        //Rational 
        else if (type == 4)
        {
            
            sumX += x[i];
            sumY += Round_off(plug,1/y[i],significantDigit,choice);
            sumX_two += Round_off(plug,pow(x[i],2),significantDigit,choice);
            sumX_Y += Round_off(plug,((x[i])*(1/y[i])),significantDigit,choice);
        }
        //Saturation Growth root
        else if (type == 5)
        {
            
            sumX += Round_off(plug,1/x[i],significantDigit,choice);
            sumY += Round_off(plug,1/sqrt(y[i]),significantDigit,choice);
            sumX_two += Round_off(plug,pow(1/x[i],2),significantDigit,choice);
            sumX_Y += Round_off(plug,((1/x[i])*(1/sqrt(y[i]))),significantDigit,choice);
  
        }
        //Power Equation natural version
        else if (type == 6)
        {
            
            sumX += Round_off(plug,log(x[i]),significantDigit,choice);
            sumY += Round_off(plug,log(y[i]),significantDigit,choice);
            sumX_two += Round_off(plug,pow(log(x[i]),2),significantDigit,choice);
            sumX_Y += Round_off(plug,((log(x[i]))*(log(y[i]))),significantDigit,choice);
        }
    }

    A[0][1] = sumX;
    A[1][0] = sumX;        
    A[0][2] = sumY;        
    A[1][1] = sumX_two;            
    A[1][2] = sumX_Y;

    printf("\n Main Matrix from sums\n");
    printMatrix(2,3,A);
    sumX_avrg = Round_off(plug,(sumX / size),significantDigit,choice);
    sumY_avrg = Round_off(plug,(sumY / size),significantDigit,choice);

    gauss_elimination(2,3,A,solution);

    //Saturation Growth
    if (type == 1)
    {
        printf("\n\n******Saturation Growth******\n");
        a_0 = Round_off(plug,solution[0],significantDigit,choice);
        a_1 = Round_off(plug,solution[1],significantDigit,choice);
        A_3 = Round_off(plug,1/solution[0],significantDigit,choice);
        B_3 = Round_off(plug,a_1/a_0,significantDigit,choice);
        for ( i = 0; i < size; i++)
        {
            f[i] = a_0 + a_1*Round_off(plug,1/x[i],significantDigit,choice)  ;
            S_r += Round_off(0,(pow(((Round_off(plug,1/y[i],significantDigit,choice)) - f[i]),2)),significantDigit,choice);
            S_t += Round_off(plug,(pow(((Round_off(plug,1/y[i],significantDigit,choice)) - sumY_avrg),2)),significantDigit,choice);
            f_reel[i] = Round_off(plug,((A_3 * x[i]/ (B_3 + x[i]))),significantDigit,choice) ;
            
        }
        f_user = Round_off(plug,((A_3 * functionValue/ (B_3 + functionValue))),significantDigit,choice) ;
        for ( i = 1; i <= 2; i++)
        {
            for ( j = 0; j < size; j++)
                tableContent[j][i-1] = Round_off(plug,pow(Round_off(plug,1/x[j],significantDigit,choice),i),significantDigit,choice);
        }
        for ( k = 0; k < 2; k++,i++)
        {
            for ( j = 0; j < size; j++)
                tableContent[j][i-1] = Round_off(plug,(pow(Round_off(plug,1/x[j],significantDigit,choice), k) * Round_off(plug,1/y[j],significantDigit,choice)),significantDigit,choice);
        }  
        printf("\nf(x) = A_3 * x / (B_3 +x) = %lf * x / (%lf + x)",A_3,B_3);
    }
    //Exponential
    else if (type == 2)
    {
        printf("\n\n******EXponential******\n");
        a_0 = Round_off(plug,solution[0],significantDigit,choice);
        a_1 = Round_off(plug,solution[1],significantDigit,choice);
        A_3 = Round_off(plug,exp(solution[0]),significantDigit,choice);
        B_3 = a_1;
        for ( i = 0; i < size; i++)
        {
            f[i] = a_0 + a_1*x[i];  
            S_r += Round_off(0,(pow(((Round_off(plug,log(y[i]),significantDigit,choice)) - f[i]),2)),significantDigit,choice);
            S_t += Round_off(plug,(pow(((Round_off(plug,log(y[i]),significantDigit,choice)) - sumY_avrg),2)),significantDigit,choice);
            f_reel[i] = Round_off(plug,(A_3*exp(B_3*x[i])),significantDigit,choice);
           
        }
        f_user = Round_off(plug,(A_3*exp(B_3*functionValue)),significantDigit,choice);
        for ( i = 1; i <= 2; i++)
        {
            for ( j = 0; j < size; j++)
                tableContent[j][i-1] = Round_off(plug,pow(x[j],i),significantDigit,choice);
        }
        for ( k = 0; k < 2; k++,i++)
        {
            for ( j = 0; j < size; j++)
                tableContent[j][i-1] = Round_off(plug,(pow(x[j], k) * Round_off(plug,log(y[j]),significantDigit,choice)),significantDigit,choice);
        }  
        printf("\nf(x) = A_3 * e^(B_3 * x) = %lf * e^(%lf * x) ",A_3,B_3);
    }
    //Power Equation
    else if (type == 3)
    {
        printf("\n\n******Power******\n");
        a_0 = Round_off(plug,solution[0],significantDigit,choice);
        a_1 = Round_off(plug,solution[1],significantDigit,choice);
        A_3 = Round_off(plug,pow(10,solution[0]),significantDigit,choice);
        B_3 = a_1;
        for ( i = 0; i < size; i++)
        {
            f[i] = a_0 + a_1*Round_off(plug,log10(x[i]),significantDigit,choice);  
            S_r += Round_off(0,(pow(((Round_off(plug,log10(y[i]),significantDigit,choice)) - f[i]),2)),significantDigit,choice);
            S_t += Round_off(plug,(pow(((Round_off(plug,log10(y[i]),significantDigit,choice)) - sumY_avrg),2)),significantDigit,choice);
            f_reel[i] = Round_off(plug,(A_3*pow(x[i],B_3)),significantDigit,choice);
            
        }
        f_user =  Round_off(plug,(A_3*pow(functionValue,B_3)),significantDigit,choice);
        for ( i = 1; i <= 2; i++)
        {
            for ( j = 0; j < size; j++)
                tableContent[j][i-1] = Round_off(plug,pow(Round_off(plug,log10(x[j]),significantDigit,choice),i),significantDigit,choice);
        }
        for ( k = 0; k < 2; k++,i++)
        {
            for ( j = 0; j < size; j++)
                tableContent[j][i-1] = Round_off(plug,(pow(Round_off(plug,log10(x[j]),significantDigit,choice), k) * Round_off(plug,log10(y[j]),significantDigit,choice)),significantDigit,choice);
        }  
        printf("\nf(x) = A_3 * x^B_3 = %lf * x^%lf ",A_3,B_3);
    }
    //Rational 
    else if (type == 4)
    {
        printf("\n\n******Rational******\n");
        a_0 = Round_off(plug,solution[0],significantDigit,choice);
        a_1 = Round_off(plug,solution[1],significantDigit,choice);
        A_3 = a_1;
        B_3 = a_0;
        for ( i = 0; i < size; i++)
        {
            f[i] = a_0 + a_1*x[i]  ;
            S_r += Round_off(0,(pow(((Round_off(plug,1/y[i],significantDigit,choice)) - f[i]),2)),significantDigit,choice);
            S_t += Round_off(plug,(pow(((Round_off(plug,1/y[i],significantDigit,choice)) - sumY_avrg),2)),significantDigit,choice);
            f_reel[i] = Round_off(plug,(1/(B_3 + (A_3*x[i]))),significantDigit,choice);
            
        }
        f_user =  Round_off(plug,(1/(B_3 + (A_3*functionValue))),significantDigit,choice);
        for ( i = 1; i <= 2; i++)
        {
            for ( j = 0; j < size; j++)
                tableContent[j][i-1] = Round_off(plug,pow(x[j],i),significantDigit,choice);
        }
        for ( k = 0; k < 2; k++,i++)
        {
            for ( j = 0; j < size; j++)
                tableContent[j][i-1] = Round_off(plug,(pow(x[j], k) * Round_off(plug,1/y[j],significantDigit,choice)),significantDigit,choice);
        }  
        printf("\nf(x) = 1/( A_3*x + B_3 ) = 1/( %lf*x + %lf ) ",A_3,B_3);
    }
        //Saturation Growth root
    else if (type == 5)
    {
        printf("\n\n******Saturation Growth root******\n");
        a_0 = Round_off(plug,solution[0],significantDigit,choice);
        a_1 = Round_off(plug,solution[1],significantDigit,choice);
        A_3 = Round_off(plug,1/solution[0],significantDigit,choice);
        B_3 = Round_off(plug,a_1/a_0,significantDigit,choice);
        for ( i = 0; i < size; i++)
        {
            f[i] = a_0 + a_1*Round_off(plug,1/x[i],significantDigit,choice)  ;
            S_r += Round_off(0,(pow(((Round_off(plug,1/sqrt(y[i]),significantDigit,choice)) - f[i]),2)),significantDigit,choice);
            S_t += Round_off(plug,(pow(((Round_off(plug,1/sqrt(y[i]),significantDigit,choice)) - sumY_avrg),2)),significantDigit,choice);
            f_reel[i] = Round_off(plug,(pow((A_3 * x[i]/ (B_3 + x[i])),2)),significantDigit,choice) ;
            
        }
        f_user = Round_off(plug,(pow((A_3 * functionValue/ (B_3 + functionValue)),2)),significantDigit,choice) ;
        for ( i = 1; i <= 2; i++)
        {
            for ( j = 0; j < size; j++)
                tableContent[j][i-1] = Round_off(plug,pow(Round_off(plug,1/x[j],significantDigit,choice),i),significantDigit,choice);
        }
        for ( k = 0; k < 2; k++,i++)
        {
            for ( j = 0; j < size; j++)
                tableContent[j][i-1] = Round_off(plug,(pow(Round_off(plug,1/x[j],significantDigit,choice), k) * Round_off(plug,1/sqrt(y[j]),significantDigit,choice)),significantDigit,choice);
        }  
        printf("\nf(x) = A_3 * x / (B_3 +x) = %lf * x / (%lf + x)",A_3,B_3);
    }
    //Power Equation natural version
    else if (type == 6)
    {
        printf("\n\n******Power******\n");
        a_0 = Round_off(plug,solution[0],significantDigit,choice);
        a_1 = Round_off(plug,solution[1],significantDigit,choice);
        A_3 = Round_off(plug,exp(solution[0]),significantDigit,choice);
        B_3 = a_1;
        for ( i = 0; i < size; i++)
        {
            f[i] = a_0 + a_1*Round_off(plug,log(x[i]),significantDigit,choice);  
            S_r += Round_off(0,(pow(((Round_off(plug,log(y[i]),significantDigit,choice)) - f[i]),2)),significantDigit,choice);
            S_t += Round_off(plug,(pow(((Round_off(plug,log(y[i]),significantDigit,choice)) - sumY_avrg),2)),significantDigit,choice);
            f_reel[i] = Round_off(plug,(A_3*pow(x[i],B_3)),significantDigit,choice);
            
        }
        f_user =  Round_off(plug,(A_3*pow(functionValue,B_3)),significantDigit,choice);
        for ( i = 1; i <= 2; i++)
        {
            for ( j = 0; j < size; j++)
                tableContent[j][i-1] = Round_off(plug,pow(Round_off(plug,log(x[j]),significantDigit,choice),i),significantDigit,choice);
        }
        for ( k = 0; k < 2; k++,i++)
        {
            for ( j = 0; j < size; j++)
                tableContent[j][i-1] = Round_off(plug,(pow(Round_off(plug,log(x[j]),significantDigit,choice), k) * Round_off(plug,log(y[j]),significantDigit,choice)),significantDigit,choice);
        }  
        printf("\nf(x) = A_3 * x^B_3 = %lf * x^%lf ",A_3,B_3);
    }


    printf("\n(1/x & 1/y)Function Results Vector\n");
    printVector(size,f);

   
    printf("\n(Original)Function Results Vector\n");
    printVector(size,f_reel);
    printf("\nf(%lf) = %lf\n",functionValue,f_user);


    S_y_x = Round_off(plug,sqrt(S_r / (size - 2) ),significantDigit,choice);
    S_y = Round_off(plug,sqrt(S_t/ (size - 1)),significantDigit,choice);
    r_two = Round_off(0,((S_t -S_r)/S_t),significantDigit,choice);
    r = Round_off(0,sqrt(r_two),6,choice);
    printf("\na0: %lf a1: %lf ", a_0,a_1);
    printf("\n1/f(x) = %lf + %lfx ", a_0,a_1);
    
    printf("\nS_r: %lf\nS_y: %lf\nS_t: %lf\nS_y/x: %lf\nr_2: %lf\nr: %lf",S_r,S_y,S_t,S_y_x,r_two,r);
        printf("\nSum Results\n");
    printMatrix(size,(4),tableContent);
}




void polynomial_fit(int plug_Equation,int significantDigit_equation,int choice_equation,int plug,int choice,int significantDigit,int degree,double functionValue,int size,double x[10],double y[10])
{
    printf("\n******Polynomial fit******\n");
    int i,j,k;
    double A[50][50] = {0};
    double solution[50] = {0};
    double f[50] = {0},f_user;
    double functionvalue_user[] = {functionValue};
    double S_t = 0, S_r = 0, S_y_x, S_y, r_two, r;
    double sumX = 0, sumY = 0, sumX_two = 0, sumX_three = 0, sumX_four = 0, sumX_Y = 0, sumX_two_Y = 0;
    double sumX_avrg = 0, sumY_avrg = 0;
    double a_0 = 0, a_1 = 0, a_2 = 0;
    /* This arrays for quizes or exams */

    double tableContent[50][50] = {0};

    /* This arrays for quizes or exams */
    
    A[0][0] = size;
    

    for ( j = 0; j < degree+1 ; j++)
    {
        for ( k = 0; k < degree+1; k++)
        {
            if (!(j == 0 && k == 0) )
            {
                for ( i = 0; i < size; i++)
                     A[j][k] += Round_off(plug,pow(x[i],j+k),significantDigit,choice);
            }
        }
        for ( i = 0; i < size; i++)
            A[j][degree+1] += Round_off(plug,(pow(x[i], j) * y[i]),significantDigit,choice);
    }

    for ( i = 1; i <= degree*2; i++)
    {
        for ( j = 0; j < size; j++)
        {
            tableContent[j][i-1] = Round_off(plug,pow(x[j],i),significantDigit,choice);
        }
        
    }
    
    for ( k = 0; k < degree + 1; k++,i++)
    {
        for ( j = 0; j < size; j++)
        {
            tableContent[j][i-1] = Round_off(plug,(pow(x[j], k) * y[j]),significantDigit,choice);
        }
    }
        
    
    
    sumX = A[0][1];
    sumY = A[0][degree+1] ;   
    printf("\n Main Matrix from sums\n");
    printMatrix(degree+1,degree+2,A);
    sumX_avrg = Round_off(plug,(sumX / size),significantDigit,choice);
    sumY_avrg = Round_off(plug,(sumY / size),significantDigit,choice);
    gauss_elimination(degree+1,degree+2,A,solution);


    for ( i = 0; i < size; i++)
    {
        f[i] = Round_off(plug,polynomial_equation(plug_Equation,significantDigit_equation,choice_equation,degree,solution,x,i),significantDigit,choice);
        S_r += Round_off(0,(pow((y[i] - f[i]),2)),significantDigit,choice);
        S_t += Round_off(plug,(pow((y[i] - sumY_avrg),2)),significantDigit,choice);
    }
    f_user = Round_off(plug,polynomial_equation(plug_Equation,significantDigit_equation,choice_equation,degree,solution,functionvalue_user,0),significantDigit,choice);
    
    
    S_r = Round_off(plug,S_r,significantDigit,choice);

    S_y_x = Round_off(plug,sqrt(S_r / (size - (degree + 1)) ),significantDigit,choice);
    S_y = Round_off(plug,sqrt(S_t/ (size - 1)),significantDigit,choice);
    r_two = Round_off(plug,((S_t -S_r)/S_t),significantDigit,choice);
    r = Round_off(plug,sqrt(r_two),significantDigit,choice);
    printf("\nf(x) = %lf + %lfx",Round_off(plug_Equation,solution[0],significantDigit_equation,choice_equation), Round_off(plug_Equation,solution[1],significantDigit_equation,choice_equation));
    for ( i = 2; i < degree+1; i++)
        printf("+ %lfx^%d ", Round_off(plug_Equation,solution[i],significantDigit_equation,choice_equation),i);
    printf("\nf(%lf) = %lf",functionValue,f_user);
    printf("\n\nS_r: %lf\n\nS_y: %lf\n\nS_t: %lf\n\nS_y/x: %lf\n\nr_2: %lf\n\nr: %lf\n\n",S_r,S_y,S_t,S_y_x,r_two,r);
    printf("\nSum Results\n");
    printMatrix(size,(degree*2 + degree+1),tableContent);
    printf("\nFunction Results Vector\n");
    printVector(size,f);
    printf("\n\n");
}

void gauss_elimination(int m, int n, double A[50][50], double x[50])
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
                    double temp;
                    temp=A[i][j];
                    A[i][j]=A[k][j];
                    A[k][j]=temp;
                }
            }
        }
        for(k=i+1;k<m;k++)
        {
            double  term=A[k][i]/ A[i][i];
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
void printMatrix(int m, int n, double A[50][50])
{
    int i,j;
    
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            printf("%-20lf\t",A[i][j]);
        }
        printf("\n");
    }
    /*
    FILE *fp;
    char output[] = "output.txt";
    fp = fopen(output,"w");
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            fprintf(fp,"%-20lf ",A[i][j]);
        }
        fprintf(fp,"\n");
    }
    fclose(fp);
    */

}
void printVector(int m, double A[50])
{
    int i;
    for(i=0;i<m;i++)
    {
        printf("%lf\t",A[i]);
        printf("\n");
    } 
}
// Function to round - off(1) / Chop off(0)   the number
double Round_off(int plug,double N, double n, int choice)
{
    if (plug == 1)
    {
        int h;
        double l, a, b, c, d, e, i, j, m, f, g, x;
        b = N;
        c = floor(N);
 
        // Counting the no. of digits to the left of decimal point
        // in the given no.
        for (i = 0; b >= 1; ++i)
            b = b / 10;
    
        d = n - i;
        b = N;
        b = b * pow(10, d);
        if (choice == 1)
        {
            e = b + 0.5;
            g = floor(b);
            x = floor(e);
            if ((int)g % 2 == 0 && e-x < 0.1f)
            {
                j = floor(g);
                m = pow(10, d);
                j = j / m;
                return j;
            }

            if ((double)e == (double)ceil(b)) 
            {
                f = (ceil(b));
                h = f - 2;
                if (h % 2 != 0)
                    e = e - 1;
            }
            j = floor(e);
            m = pow(10, d);
            j = j / m;
            return j;
        }
        else
        {
            j = floor(b);
            m = pow(10, d);
            j = j / m;
            return j;
        }
    }
    return N;
    
}
double polynomial_equation(int plug_Equation,int significantDigit_equation,int choice_equation,int degree,double solution[50], double x[50],int index)
{
    double result = 0;
    int i;
    for ( i = 0; i < degree + 1; i++)
        result +=  Round_off(plug_Equation,solution[i],significantDigit_equation,choice_equation) * pow(x[index],i);
    
    
    return result;
}