#ifndef HARMONICFORM_H
#define HARMONICFORM_H

#include <QWidget>
#include "xcustomplot.h"

#define g_C2Q(str) QString::fromLocal8Bit(str)
#define g_Q2C(qs)  (const char*)(qs).toLocal8Bit()

namespace Ui {
class HarmonicForm;
}

class HarmonicForm : public QWidget
{
    Q_OBJECT

public:
    explicit HarmonicForm(QWidget *parent = nullptr);
    ~HarmonicForm();

    void setTableRowHead(QStringList strlist);
    void setTableColHead(QStringList strlist);
    void initItem();
    void setHrmCount(int count);
    void upData(QList<QStringList> datalist);
    void setFileName(QString fname);

private slots:
    void on_Btn_save_clicked();

    void on_spinBox_valueChanged(int arg1);

private:
    Ui::HarmonicForm *ui;
    QString mFileName;
    int mPower;//保存几次谐波
};

#endif // HARMONICFORM_H
