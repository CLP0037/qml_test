#ifndef FORM01_H
#define FORM01_H

#include <QWidget>

namespace Ui {
class Form01;
}

class Form01 : public QWidget
{
    Q_OBJECT

public:
    explicit Form01(QWidget *parent = nullptr);
    ~Form01();

    void frm_show();
    void frm_close();

private slots:
    void on_btn_test_w_clicked();

private:
    Ui::Form01 *ui;
};

#endif // FORM01_H
