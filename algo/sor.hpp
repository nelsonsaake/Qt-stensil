# include <cstdlib>
# include <iostream>
# include <iomanip>
# include <cmath>
# include <ctime>


#include<stdio.h>
#include<math.h>
#include <QVector>

using namespace std;

double *sor1 ( int n, double a[], double b[], double x[], double w );

class SOR{

public:
    SOR(){

        n = 4;
    }

private:
    /*
    *   SOR ALGORITHM 7.3
    *
    *   To solve Ax = b given the parameter w and an initial approximation
    *   x(0):
    *   Example 7.4.1
    *
    *   INPUT:   the number of equations and unknowns n; the entries
    *            A(I,J), 1<=I, J<=n, of the matrix A; the entries
    *            B(I), 1<=I<=n, of the inhomogeneous term b; the
    *            entries XO(I), 1<=I<=n, of x(0); tolerance TOL;
    *            maximum number of iterations N; parameter w (omega).
    *
    *    OUTPUT:  the approximate solution X(1),...,X(n) or a message
    *             that the number of iterations was exceeded.
    */


    /* Absolute Value Function */
    double absval(double val)
    {
        if (val >= 0) return val;
        else return -val;
    }

public:
    QVector<double> solve(int n, QVector<QVector<double>> a)
    {

        //    n = 4;
        //    A = {{4.0, 1.11, -1.0, 1.0, 1.12},
        //         {1.2, 4.122, -1.0, -1.0, 3.44},
        //         {0.0, 1.0, 99.9, 1.0, 2.15},
        //         {1.3, -0.11, -1.1, 10.0, 4.16}};

        this->n = n;
        A = a;

        X1 = QVector<double>(n, 0.0);
        r  = QVector<double>(n, 0.0);


        /* STEP 1 */
        K = 1;
        OK = false;
        NN = 200;  // Max. number of iteration
        for(I = 0; I < n; I++)   // initial guess
            X1[I] = 0.0;
        W = 1.02;                // Value of relaxation parameter
        TOL = 1.0e-10;           // Tolerance.

        /* STEP 2 */
        while ((!OK) && (K <= NN)) {
            /* err is used to test accuracy - it measures the
             infinity-norm of residual vector */
            ERR = 0.0;
            /* STEP 3 */
            for (I=1; I<=n; I++) {
                S = 0.0;
                for (J=1; J<=n; J++)
                    S = S - A[I-1][J-1] * X1[J-1];
                S = W * (S + A[I-1][n]) / A[I-1][I-1];
                X1[I-1] = X1[I-1] + S;
            }

            // Compute residual vector
            for(I=1; I<=n; I++)
            {
                S = 0.0;
                for(J =1; J <=n; J++)
                {
                    S = S + A[I-1][J-1]*X1[J-1];
                }
                r[I-1] = A[I-1][n] - S;
                if (absval(r[I-1]) > ERR)
                    ERR = absval(r[I-1]);
            }

            /* STEP 4 */
            if (ERR <= TOL) OK = true;
            /* process is complete */
            else
                /* STEP 5 */
                K++;
            /* STEP 6 - is not used since only one vector is required */
        }
        if (!OK) printf("Maximum Number of Iterations Exceeded.\n");

        /* STEP 7 */
        /* procedure completed unsuccessfully */
        // else OUTPUT(X1, K, TOL, W);
        return X1;
    }

private:
    int n; // number of equations

    double W,S,ERR,TOL;
    int I,J,NN,K,OK;

    QVector<QVector<double>> A;
    QVector<double> X1;
    QVector<double> r;
};


















/*

    void OUTPUT(QVector<double> X1, int K, double TOL, double W)
    {
        int I, FLAG;
        char NAME[30];
        FILE *OUP;

        printf("Choice of output method:\n");
        printf("1. Output to screen\n");
        printf("2. Output to text file\n");
        printf("Please enter 1 or 2.\n");
        scanf("%d", &FLAG);
        if (FLAG == 2) {
            printf("Input the file name in the form - drive:name.ext\n");
            printf("for example:   A:OUTPUT.DTA\n");
            scanf("%s", NAME);
            OUP = fopen(NAME, "w");
        }
        else OUP = stdout;
        fprintf(OUP, "SOR ITERATIVE METHOD FOR LINEAR SYSTEMS\n\n");
        fprintf(OUP, "The solution vector is :\n");
        for (I=1; I<=n; I++) fprintf(OUP, " %11.8f\n", X1[I-1]);
        fprintf(OUP, "\nusing %d iterations with\n", K);
        fprintf(OUP, "Tolerance  %.10e in infinity-norm\n", TOL);
        fprintf(OUP, "with Parameter %.10e\n", W);
        fclose(OUP);
    }

 */
