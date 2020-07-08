/* Program Gauss_Jacobi
   Solution of a system of linear equations by Gauss-Jacobi's iteration
   method. Testing of diagonal dominance is also incorporated */

#include<math.h>
#include<stdlib.h>
#include<QVector>
#include<iostream>
#include <QMessageBox>

using namespace std;

class Jacobi{

public:
    Jacobi(){}

private:
    void init(int val){

        this->n = val;
        a = QVector<QVector<double>>(n, QVector<double>(n, 0.0));
        b = QVector<double>(n, 0.0);
        x = QVector<double>(n, 0.0);
        xn = QVector<double> (n, 0.0);
        epp = 0.00005;
    }

    void set(int n, QVector<QVector<double>> a,  QVector<double> b, QVector<double> x){

        this->n = n;
        this->a = a;
        this->b = b;
        this->x = x;
    }

    double sum(QVector<double> x){

        double sum = 0;
        for(int i=0; i<x.size(); i++){

            sum += x[i];
        }
        return sum;
    }

    bool willConverge(QVector<double> x, int j){

        return fabs(sum(x)-x[j]) <= fabs(x[j]);
    }

    bool willConverge(){

        for(int i=0; i<a.size(); i++){

            QVector<double> row = a[i];
            if(!willConverge(row, i)) {
                return false;
            }
        }

        return true;
    }

    void addNewIteration(QVector<double> x){

        iteraTable.push_back(x);
    }

    bool isTolerable(QVector<double> x, QVector<double> xn,double epp){

        //indicates |x[i]-xn[i]|<epp for all i
        for(int i=0;i<n;i++) {
            if(fabs(x[i]-xn[i]) > epp) return false;
        }

        return true;
    }

    QVector<double> product(int n, QVector<double> ai, QVector<double> x){

        QVector<double> res(n, 0.0);
        for(int j=0; j<n; j++){
            res[j] = ai[j] * x[j];
        }
        return res;
    }

public:
    QVector<double> solve(int arg_n,  QVector<QVector<double>> arg_a,  QVector<double> arg_b, QVector<double> arg_x){

        init(arg_n);
        set(arg_n,arg_a,arg_b,arg_x);

        if(!willConverge()) {
            cerr << "the equation won't converge!";
            return {};
        }


        addNewIteration(x);

        for(;;){

            //    xn.clear();
            //    xn = QVector<double>(n,0.0);

            // one iteration of jacobi
            for(int i=0;i<n;i++)
            {

                QVector<double> aix = product(n, a[i], x);
                double aii = a[i][i];
                double aiixi = aii*x[i];
                xn[i] = (b[i] - (sum(aix)-aiixi))/aii;
            }

            // print the results
            addNewIteration(xn);

            if(isTolerable(x,xn,epp)) break;

            x = xn;
        }

        addNewIteration(xn);

        return xn;
    }

    QVector<QVector<double>> iterationTable(){
        return iteraTable;
    }

    QString iterationTableStr(){

        QString str = "";

        for(int i=0; i<iterationTable().size(); i++){

            QVector<double> row = iterationTable()[i];

            str += QString("\n") + "iteration " + QString::number(i+1) + "\n";

            for(int j=0; j<row.size(); j++){

               str += QString::number(row[j]) + "\t\t";
            }

            str += "\n";
        }

        return str;
    }
private:
    int n;
    QVector<QVector<double>> a;
    QVector<QVector<double>> iteraTable;
    QVector<double> b;
    QVector<double> x;
    QVector<double> xn;
    double epp;
};
