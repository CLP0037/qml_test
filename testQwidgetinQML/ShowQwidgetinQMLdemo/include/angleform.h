#ifndef ANGLEFORM_H
#define ANGLEFORM_H

#include <QWidget>
#include "slctchnldialog.h"


namespace Ui {
class AngleForm;
}

class AngleForm : public QWidget
{
    Q_OBJECT

public:
    explicit AngleForm(QWidget *parent = nullptr);
    ~AngleForm();

    void upData(QList<QList<double >> datalist, QStringList unitlist);

    void setChnlList(QStringList strlist);

    void selectclick();
private:
    void initCol();
    void initRow();

private slots:
    void on_Btn_select_clicked();

    void on_Btn_hide_clicked();

    void on_comboBox_mode_currentIndexChanged(int index);

signals:
    void updtChannel();
public:
    QList<QStringList> mDataList;



private:
    Ui::AngleForm *ui;
    SlctChnlDialog *mSlctDialog;

    int VectType;//0,参考向量（相对）；1旋转向量（绝对），默认0


};

#endif // ANGLEFORM_H
