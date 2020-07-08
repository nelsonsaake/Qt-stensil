#include "mainwindow.h"

#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

//  HELLO WORLD; LET'S GET STARTED

//  DIRECT METHODS
//  Guassian's elimination - done
//  Gauss Jordan elimination - done
//  LU decomposition - done

//  ITERATIVE METHODS
//  Jacobi - done something
//  Gauss Seidal - done
//  Successive Over Relaxation - done something
