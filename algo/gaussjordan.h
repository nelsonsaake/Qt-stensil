#ifndef GAUSSJORDAN_H
#define GAUSSJORDAN_H

#include <QVector>
#include<iostream>
using namespace std;


class GaussJordan {

public:

    GaussJordan(){
    }

    QVector<double> solve(int n, QVector<QVector<double>> a){

        this->a = a;
        this->n = n;

        return solve();
    }

private:
    QVector<double> solve() {

        for(int j=0; j<n; j++) {
           for(int i=0; i<n; i++) {
              if(i!=j) {
                 double b=a[i][j]/a[j][j];
                 for(int k=0; k<=n; k++) {
                    a[i][k]=a[i][k]-b*a[j][k];
                 }
              }
           }
        }

        QVector<double> x;
        for(int i=0; i<n; i++) {
           double xi=a[i][n]/a[i][i];
           x.push_back(xi);
        }

        return x;
    }

private:
    QVector<QVector<double>> a;
    int n;
};


#endif // GAUSSIANSELIMINATION_H
