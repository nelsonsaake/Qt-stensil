#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <algo/gaussianselimination.h>
#include <algo/gaussjordan.h>
#include <algo/ludecomposition.h>
#include <algo/jacobi.h>
#include <algo/gaussseidel.h>
#include <algo/sor.hpp>
#include "ui_mainwindow.h"
#include "uiComponent/matwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    enum class Method{GaussiansElimination_M, GaussJordan_M, LU_M, Jacobi_M, GaussSeidel_M, SOR_M};

public:
    MainWindow(QWidget *parent = nullptr)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
    {
        ui->setupUi(this);
        setup();
    }
    ~MainWindow()
    {
        delete ui;
    }

private:
    void setup(){

        // we provide the n input
        // after we recieve the results of the n input

        n = 0;
        A = new MatInput(n, "", this);
        B = new VecInput(n, "", this);
        X = new VecInput(n, "", this);
        m = Method::Jacobi_M;
    }

    void addInputWidget(QWidget *w){

        ui->input_verticalLayout->addWidget(w);
    }

    void clearInputWidget(){

        A->deleteLater();
        B->deleteLater();
        X->deleteLater();
    }

    void setN(int n){

        clearInputWidget();
        this->n = n;

        if(n < 1) n = 0;

        A = new MatInput(n, "A", this);
        addInputWidget(A);

        B = new VecInput(n, "b", this);
        addInputWidget(B);

        X = new VecInput(n, "x", this);
        addInputWidget(X);
    }

    void clearSolnWidgets(){

        for(QWidget *w: solnWidgets){
            w->deleteLater();
        }
        solnWidgets.clear();
    }

    void addOutputWidget(QWidget *w){

        ui->output_verticalLayout->addWidget(w);
        solnWidgets.push_back(w);
    }

    void displayRes(QVector<double> x){

        clearSolnWidgets();

        VecDisplay *res_display = new VecDisplay(x, "X", this);
        addOutputWidget(res_display);
    }

    void gaussianElimination(){

        QVector<QVector<double>> a = A->val();
        QVector<double> b = B->vecVal();
        QVector<double> x = X->vecVal();

        for(int i=0; i<n; i++){
            a[i].push_back(b[i]);
        }

        GaussianElimination solver;
        QVector<double> res = solver.solve(n, a);
        displayRes(res);
    }

    void gaussJordan(){

        QVector<QVector<double>> a = A->val();
        QVector<double> b = B->vecVal();
        QVector<double> x = X->vecVal();

        for(int i=0; i<n; i++){
            a[i].push_back(b[i]);
        }

        class GaussJordan solver;
        QVector<double> res = solver.solve(n, a);
        displayRes(res);
    }

    void lu(){

        QVector<QVector<double>> a = A->val();
        QVector<double> b = B->vecVal();
        QVector<double> x = X->vecVal();

        LUDecomposition solver;
        solver.solve(n, a);

        addOutputWidget(new MatDisplay(n, solver.lDecomposition(), "L", this));
        addOutputWidget(new MatDisplay(n, solver.uDecomposition(), "U", this));
    }

    void lu2_3x3_err(){
        QMessageBox::warning(this, "Error", "LU accepts only 3x3 matrix!");
    }

    void lu2(){
        QVector<QVector<double>> a = A->val();

        if(a.size() != 3){
            lu2_3x3_err();
            return;
        }

        for(QVector<double> vd: a){
            if(vd.size() != 3){
                lu2_3x3_err();
                return;
            }
        }

        LU2 solver;
        solver.lu_3x3(a);

        clearSolnWidgets();
        addOutputWidget(new MatDisplay(n, solver.vl, "L", this));
        addOutputWidget(new MatDisplay(n, solver.vu, "U", this));
    }

    void jacobi(){

        QVector<QVector<double>> a = A->val();
        QVector<double> b = B->vecVal();
        QVector<double> x = X->vecVal();

        Jacobi solver;
        QVector<double> res = solver.solve(n, a, b, x);
        if(res.isEmpty()) {
            QMessageBox::warning(this, "Error", "The equations won't converge!");
            return;
        }
        displayRes(res);

        QVector<QVector<double>> iterationTable = solver.iterationTable();
        MatWidget *it = new MatWidget(n, iterationTable.size(), iterationTable, "Iterations", false, this);
        addOutputWidget(it);
    }

    void gaussSeidel(){

        QVector<QVector<double>> a = A->val();
        QVector<double> b = B->vecVal();
        QVector<double> x = X->vecVal();

        GaussSeidel solver;
        QVector<double> res = solver.solve(n, a, b, x);
        if(res.isEmpty()) {
            QMessageBox::warning(this, "Error", "The equations won't converge!");
            return;
        }
        displayRes(res);

        QLabel *label = new QLabel(solver.iterationTableStr(), this);
        addOutputWidget(label);

        QVector<QVector<double>> iterationTable = solver.iterationTable();
        MatWidget *it = new MatWidget(n, iterationTable.size(), iterationTable, "Iterations", false, this);
        addOutputWidget(it);
    }

    void sor(){

        QVector<QVector<double>> a = A->val();
        QVector<double> b = B->vecVal();
        QVector<double> x = X->vecVal();

        for(int i=0; i<n; i++){
            a[i].push_back(b[i]);
        }

        SOR solver;
        QVector<double> res = solver.solve(n, a);
        displayRes(res);
    }

    void solve(){

        switch(m){

        case Method::GaussiansElimination_M:
            gaussianElimination();
            break;

        case Method::GaussJordan_M:
            gaussJordan();
            break;

        case Method::LU_M:
            lu2();
            break;

        case Method::Jacobi_M:
            jacobi();
            break;

        case Method::GaussSeidel_M:
            gaussSeidel();
            break;

        case Method::SOR_M:
            sor();
            break;
        }
    }

    void setAppLabel(QString t){

        QString html = "<html><head/><body><p align='center'>" + t + " </p></body></html>";
        ui->app_label->setText(html);

        QString title = "Stensil - " + t;
        setWindowTitle(title);
    }

    void gotoMainPage(){

        ui->stackedWidget->setCurrentIndex(1);

        QString label;

        switch(m){

        case Method::GaussiansElimination_M:
           label = "Guassian's Elimination";
            break;

        case Method::GaussJordan_M:
            label = "Gauss Jordan Elimination";
            break;

        case Method::LU_M:
            label = "LU Decomposition";
            break;

        case Method::Jacobi_M:
            label = "Jacobi";
            break;

        case Method::GaussSeidel_M:
            label = "Gauss Seidal";
            break;

        case Method::SOR_M:
            label = "Successive Over Relaxation";
            break;
        }

        setAppLabel(label);

        setN(0);
    }

    void gotoHomePage(){

        ui->stackedWidget->setCurrentIndex(0);
    }

private slots:
    void on_n_lineEdit_editingFinished()
    {
        int n = ui->n_lineEdit->text().toInt();
        setN(n);
        clearSolnWidgets();
    }

    void on_solve_pushButton_clicked()
    {
        solve();
    }

    void on_gaussJordan_pushButton_clicked()
    {
        m = Method::GaussJordan_M;
        gotoMainPage();
    }

    void on_guassianElimination_pushButton_clicked()
    {
        m = Method::GaussiansElimination_M;
        gotoMainPage();
    }

    void on_lu_pushButton_clicked()
    {
        m = Method::LU_M;
        gotoMainPage();
    }

    void on_jacobi_pushButton_clicked()
    {
        m = Method::Jacobi_M;
        gotoMainPage();
    }

    void on_gaussSeidal_pushButton_clicked()
    {
        m = Method::GaussSeidel_M;
        gotoMainPage();
    }

    void on_sor_pushButton_clicked()
    {
        m = Method::SOR_M;
        gotoMainPage();
    }

    void on_pushButton_clicked()
    {
        gotoHomePage();
    }

private:
    Ui::MainWindow *ui;

    int n;

    MatInput *A;
    VecInput *B;
    VecInput *X;

    QVector<QWidget *> solnWidgets;

    Method m;
};
#endif // MAINWINDOW_H
