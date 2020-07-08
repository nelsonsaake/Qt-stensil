#ifndef TOMPUSHBUTTON_H
#define TOMPUSHBUTTON_H

#include <QWidget>

namespace Ui {
class TomPushButton;
}

class TomPushButton : public QWidget
{
    Q_OBJECT

public:
    explicit TomPushButton(QWidget *parent = nullptr);
    ~TomPushButton();

private:
    Ui::TomPushButton *ui;
};

#endif // TOMPUSHBUTTON_H
