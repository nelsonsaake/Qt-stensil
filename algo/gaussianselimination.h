#ifndef GAUSSIANSELIMINATION_H
#define GAUSSIANSELIMINATION_H

// Gauss Elimination

/* math.h header file is included for abs() function */
#include<bits/stdc++.h>
#include<iostream>
#include<iomanip>
#include <QVector>
#include<math.h>

using namespace std;


class GaussiansElimination {

public:
    GaussiansElimination(){}

private:
    // C++ program to demostrate working of Guassian Elimination
    // method

    // function to get matrix content
    void gaussianElimination(QVector<QVector<double>> mat)
    {
        // reduction into r.e.f.
        int singular_flag = forwardElim(mat);

        // if matrix is singular
        if (singular_flag != -1)
        {
            printf("Singular Matrix.\n");

            //  if the RHS of equation corresponding to
            //  zero row is 0, * system has infinitely
            //  many solutions, else inconsistent

            //?
            if (mat[singular_flag][N])
                printf("Inconsistent System.");
            else
                printf("May have infinitely many solutions.");

            return;
        }

        //  get solution to system and print it using
        //  backward substitution
        backSub(mat);
    }

    // function for elementary operation of swapping two rows
    void swap_row(QVector<QVector<double>> mat, int i, int j)
    {
        //printf("Swapped rows %d and %d\n", i, j);

        for (int k=0; k<=N; k++)
        {
            double temp = mat[i][k];
            mat[i][k] = mat[j][k];
            mat[j][k] = temp;
        }
    }

    // function to print matrix content at any stage
    void print(QVector<QVector<double>> mat)
    {
        for (int i=0; i<N; i++, printf("\n"))
            for (int j=0; j<=N; j++)
                printf("%lf ", mat[i][j]);

        printf("\n");
    }

    // function to reduce matrix to r.e.f.
    // indicate whether matrix is singular or not
    int forwardElim(QVector<QVector<double>> mat)
    {
        for (int k=0; k<N; k++)
        {
            // Initialize maximum value and index for pivot
            int i_max = k;
            int v_max = mat[i_max][k];

            // find greater amplitude for pivot if any
            for (int i = k+1; i < N; i++)
                if (abs(mat[i][k]) > v_max)
                    v_max = mat[i][k], i_max = i;

            // if a prinicipal diagonal element is zero,
            // it denotes that matrix is singular, and
            // will lead to a division-by-zero later.
            if (!mat[k][i_max])
                return k; // Matrix is singular

            // Swap the greatest value row with current row
            if (i_max != k)
                swap_row(mat, k, i_max);


            for (int i=k+1; i<N; i++)
            {
                // factor f to set current row kth element to 0,
                // and subsequently remaining kth column to 0
                double f = mat[i][k]/mat[k][k];

                // subtract fth multiple of corresponding kth
                // row element
                for (int j=k+1; j<=N; j++)
                    mat[i][j] -= mat[k][j]*f;

                // filling lower triangular matrix with zeros
                mat[i][k] = 0;
            }

            //print(mat);	 //for matrix state
        }
        //print(mat);		 //for matrix state
        return -1;
    }

    // function to calculate the values of the unknowns
    void backSub(QVector<QVector<double>> mat)
    {
        double x[N]; // An array to store solution

        /* Start calculating from last equation up to the
        first */
        for (int i = N-1; i >= 0; i--)
        {
            /* start with the RHS of the equation */
            x[i] = mat[i][N];

            /* Initialize j to i+1 since matrix is upper
            triangular*/
            for (int j=i+1; j<N; j++)
            {
                /* subtract all the lhs values
                * except the coefficient of the variable
                * whose value is being calculated */
                x[i] -= mat[i][j]*x[j];
            }

            /* divide the RHS by the coefficient of the
            unknown being calculated */
            x[i] = x[i]/mat[i][i];
        }

        //? printf("\nSolution for the system:\n");
        res.clear();
        for (int i=0; i<N; i++)
            //? printf("%lf\n", x[i]);
            res.push_back(x[i]);
    }

public:
    QVector<double> solve(int n, QVector<QVector<double>> a){

        N = n;
        gaussianElimination(a);

        return res;
    }

private:
    int N;
    QVector<double> res;
};

class GaussianElimination {

public:
    GaussianElimination(){}

private:

    void setup(int n, QVector<QVector<double>> mat){

        this->n = n;
        this->mat = mat;
        res = QVector<double>(this->n, 0.0);
    }

    void consoleInput(){

        cout<<"\nEnter the no. of equations: ";
        cin>>n;

        mat.clear();
        mat = QVector<QVector<double>>(n, QVector<double>(n+1, 0.0));
        res = QVector<double>(n, 0.0);

        cout<<"\nEnter the elements of the augmented matrix: ";
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n+1;j++)
            {
                cin>>mat[i][j];
            }
        }
    }

    void swaping(){

        for(int i=0;i<n;i++)
        {
            for(int j=i+1;j<n;j++)
            {
                if(abs(mat[i][i]) < abs(mat[j][i]))
                {
                    for(int k=0;k<n+1;k++)
                    {
                        /* swapping mat[i][k] and mat[j][k] */
                        mat[i][k]=mat[i][k]+mat[j][k];
                        mat[j][k]=mat[i][k]-mat[j][k];
                        mat[i][k]=mat[i][k]-mat[j][k];
                    }
                }
            }
        }

    }

    void gaussianElimination(){

        /* performing Gaussian elimination */
        for(int i=0;i<n-1;i++)
        {
            for(int j=i+1;j<n;j++)
            {
                double f=mat[j][i]/mat[i][i];
                for(int k=0;k<n+1;k++)
                {
                    mat[j][k]=mat[j][k]-f*mat[i][k];
                }
            }
        }

    }

    void backwardSubstitution(){

        /* Backward substitution for discovering values of unknowns */
        for(int i=n-1;i>=0;i--)
        {
            res[i]=mat[i][n];

            for(int j=i+1;j<n;j++)
            {
                if(i!=j)
                {
                    res[i]=res[i]-mat[i][j]*res[j];
                }
            }
            res[i]=res[i]/mat[i][i];
        }

    }

    void printResults(){

        cout<<"\nThe values of unknowns for the above equations=>\n";
        for(int i=0;i<n;i++)
        {
            cout<<res[i]<<"\n";
        }
    }

    void main()
    {

        swaping();

        gaussianElimination();

        backwardSubstitution();
    }

public:
    QVector<double> solve(int n, QVector<QVector<double>> mat){

        setup(n, mat);
        main();
        return res;
    }

private:
    int n;

    /* for n equations there will be n unknowns which will be stored in array 'res' */
    QVector<double> res;

    /* if no of equations are n then size of augmented matrix will be n*n+1. So here we are declaring 2d array 'mat' of size n+n+1 */
    // double mat[n][n+1];
    QVector<QVector<double>> mat;
};

// just use the vec and remove the inner implementation of array

#endif // GAUSSIANSELIMINATION_H
