#ifndef LUDECOMPOSITION_H
#define LUDECOMPOSITION_H

#include<iostream>
#include<cstdio>
#include<QVector>

using namespace std;

class LUDecomposition
{
public:

    LUDecomposition()
    {
    }

private:

    void set(int n, QVector<QVector<double>> a){

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                this->a[i][j] = a[i][j];
            }
        }

        this->n = n;
    }

    void lu(double a[][10], double l[][10], double u[][10], int n)
    {
        int i = 0, j = 0, k = 0;
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                if (j < i)
                    l[j][i] = 0;
                else
                {
                    l[j][i] = a[j][i];
                    for (k = 0; k < i; k++)
                    {
                        l[j][i] = l[j][i] - l[j][k] * u[k][i];
                    }
                }
            }
            for (j = 0; j < n; j++)
            {
                if (j < i)
                    u[i][j] = 0;
                else if (j == i)
                    u[i][j] = 1;
                else
                {
                    u[i][j] = a[i][j] / l[i][i];
                    for (k = 0; k < i; k++)
                    {
                        u[i][j] = u[i][j] - ((l[i][k] * u[k][j]) / l[i][i]);
                    }
                }
            }
        }
    }

    QVector<QVector<double>> output(double x[][10], int n)
    {
        QVector<QVector<double>> mat;

        int i = 0, j = 0;
        for (i = 0; i < n; i++)
        {
            QVector<double> rowi;
            for (j = 0; j < n; j++)
            {
                rowi.push_back(x[i][j]);
            }

            mat.push_back(rowi);
        }

        return mat;
    }

public:
    QString solve(int n, QVector<QVector<double>> a)
    {
        set(n, a);
        lu(this->a, l, u, this->n);
        return res();
    }

    QVector<QVector<double>> lDecomposition(){
        return output(l, n);
    }

    QVector<QVector<double>> uDecomposition(){
        return output(u, n);
    }

    QString toString(QVector<QVector<double>> vvf){

        QString str = "{\n";
        for(int i=0; i<n; i++){

            str += "\t\t";
            for(int j=0; j<n; j++){

                str += QString::number(vvf[i][j]) + "\t";
            }
            str+="\n";
        }
        str += "\n}";

        return str;
    }

    QString res(){

        // convert the l to string
        // convert the u to string
        QString str;
        str = "l = ";
        str += toString(lDecomposition());
        str += "\n\n";
        str += "u = ";
        str += toString(uDecomposition());

        return str;
    }

private:
    int n;
    double a[10][10], l[10][10], u[10][10];
};

struct LU2{

    void lu_3x3(QVector<QVector<double>> a){

           double u11 = a[0][0];
           double u12 = a[0][1];
           double u13 = a[0][2];

           double l21 = a[1][0] / u11;
           double u22 = a[1][1] - (l21)*(u12);
           double u23 = a[1][2] - (l21)*(u13);

           double l31 = a[2][0] / u11;
           double l32 = (a[2][1] - l31*u12)/(u22);
           double u33 = (a[2][2] - (l31*u13 + l32*u23));

           vl = {{1,0,0},{l21,1,0},{l31,l32,1}};
           vu = {{u11,u12,u13},{0,u22,u23},{0,0,u33}};
    }

    QVector<QVector<double>> vl, vu;
};

// just use the vec and remove the inner implementation of array

#endif // LUDECOMPOSITION_H
