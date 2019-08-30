#include "form.h"
#include "ui_form.h"

Form::Form(QWindow *parent) :
    QWindow(parent),
    ui(new Ui::Form)
{
    //ui->setupUi(this);

}

Form::~Form()
{
    delete ui;
}

void Form::on_btn_test_clicked()
{

}
