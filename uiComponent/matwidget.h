#ifndef MATWIDGET_H
#define MATWIDGET_H

#include <QLineEdit>
#include <QWidget>
#include "ui_matwidget.h"

namespace Ui {
class MatWidget;
}

class MatWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MatWidget(int n, int m = -1, QVector<QVector<double>> vvf = {}, QString name = "", bool isInputEnabled = false, QWidget *parent = nullptr) :
        QWidget(parent),
        ui(new Ui::MatWidget)
    {
        ui->setupUi(this);

        if(n < 0){
            this->n = 0;
        }else {
            this->n = n;
        }

        if(m < 0){
            this->m = n;
        }else {
            this->m = m;
        }

        if(vvf.isEmpty()){
            this->init_vvf = QVector<QVector<double>>(n, QVector<double>(m, 0.0));
        }else {
            this->init_vvf = vvf;
        }

        this->name = name;
        this->isInput = isInputEnabled;

        setup();
    }
    ~MatWidget()
    {
        delete ui;
    }


    void createInputs(){

        for(int i=0; i<n; i++){

            QVector<QLineEdit*> row;
            for(int j=0; j<m; j++){

                QLineEdit *lineEdit = new QLineEdit(this);
                row.push_back(lineEdit);

                lineEdit->setText(QString::number(init_vvf[i][j]));
                lineEdit->setEnabled(isInput);
            }
            matInput.push_back(row);
        }
    }

    void addInputsToView(){

        QGridLayout *layout = ui->gridLayout;

        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){

                layout->addWidget(matInput[i][j],i,j,Qt::AlignLeft);
            }
        }
    }

    void setLable(){

        QLabel *label = ui->label;
        QString labelStr = "";

        name = name.trimmed();
        if(!name.isEmpty()){
            labelStr = name + " = ";
        }

        label->setText(labelStr);
    }

    void setup(){

        setLable();
        createInputs();
        addInputsToView();
    }


public:
    QVector<QVector<double>> val(){

        QVector<QVector<double>> mat;

        for(int i=0; i<n; i++){

            QVector<double> row;
            for(int j=0; j<m; j++){

                QString text = matInput[i][j]->text();
                double f = text.toDouble();
                row.push_back(f);
            }
            mat.push_back(row);
        }

        return mat;
    }

    QVector<double> vecVal(){

        return val()[0];
    }

private:
    Ui::MatWidget *ui;

    int n;
    int m;
    QVector<QVector<double>> init_vvf;
    QString name;
    bool isInput;

    QVector<QVector<QLineEdit*>> matInput;
};

struct MatDisplay : MatWidget {

    MatDisplay(int n, QVector<QVector<double>> vvf, QString name = "", QWidget *parent = nullptr) :
        MatWidget(n, n, vvf, name, false, parent){

    }
};

struct MatInput : MatWidget {

    MatInput(int n, QString name = "", QWidget *parent = nullptr) :
        MatWidget(n, n, {}, name, true, parent){

    }
};

struct VecDisplay : MatWidget {
    VecDisplay(QVector<double> vf, QString name = "", QWidget *parent = nullptr) :
        MatWidget(1, vf.size(), {vf}, name, false, parent){

    }
};

struct VecInput : MatWidget {

    VecInput(int n, QString name = "", QWidget *parent = nullptr) :
        MatWidget(1, n, {}, name, true, parent) {

    }
};

#endif // MATWIDGET_H
