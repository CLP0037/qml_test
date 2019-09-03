#include "form01.h"
#include "ui_form01.h"

Form01::Form01(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form01)
{
    ui->setupUi(this);
}

Form01::~Form01()
{
    delete ui;
}

void Form01::frm_show()
{
    this->show();
}
void Form01::frm_close()
{
   this->close();
}

void Form01::on_btn_test_w_clicked()
{
    this->close();
}
