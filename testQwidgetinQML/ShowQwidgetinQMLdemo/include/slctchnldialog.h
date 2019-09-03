#ifndef SLCTCHNLDIALOG_H
#define SLCTCHNLDIALOG_H

#include <QDialog>
#define g_C2Q(str) QString::fromLocal8Bit(str)
#define g_Q2C(qs)  (const char*)(qs).toLocal8Bit()
namespace Ui {
class SlctChnlDialog;
}

class SlctChnlDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SlctChnlDialog(QWidget *parent = nullptr);
    ~SlctChnlDialog();

    void setTableItem();

    QStringList ChnlList;
    QList<int > SlctIndexList;

private slots:
    void on_tBtn_up_clicked();

    void on_tBtn_OK_clicked();

    void on_tBtn_recover_clicked();

    void on_tableWidget_doubleClicked(const QModelIndex &index);

    void on_tableWidget_2_doubleClicked(const QModelIndex &index);

private:
    Ui::SlctChnlDialog *ui;
};

#endif // SLCTCHNLDIALOG_H
