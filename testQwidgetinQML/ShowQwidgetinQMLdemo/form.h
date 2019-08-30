#ifndef FORM_H
#define FORM_H

//#include <QWidget>
#include <QWindow>

namespace Ui {
class Form;
}

class Form : public QWindow
{
    Q_OBJECT

public:
    explicit Form(QWindow *parent = nullptr);//
    ~Form();

private slots:
    void on_btn_test_clicked();

private:
    Ui::Form *ui;
};

#endif // FORM_H
