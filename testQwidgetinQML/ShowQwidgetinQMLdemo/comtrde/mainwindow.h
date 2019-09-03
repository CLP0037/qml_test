#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileInfo>
#include <QFileDialog>
#include <QDir>

#include "./include/comtradeview.h"

using namespace std;
#define g_C2Q(str) QString::fromLocal8Bit(str)
#define g_Q2C(qs)  (const char*)(qs).toLocal8Bit()

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_btn_show_clicked();

    bool isDirExist(QString fullPath);
    bool isFileExist(QString fileFullName);

    void on_btn_pathselect_clicked();

    void on_btn_save_clicked();

    void on_Btn_T0_clicked();

    void on_Btn_vscale0_clicked();

    void on_Btn_vscale1_clicked();

    void on_Btn_hscale0_clicked();

    void on_Btn_hscale_clicked();

    void on_Btn_recover_clicked();

    void on_Btn_showall_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_Btn_max_clicked();

    void on_Btn_min_clicked();

    void on_comboBox_2_currentIndexChanged(const QString &arg1);

    void on_btn_back_clicked();

private:
    Ui::MainWindow *ui;

    QList<Comtradeview *> mComtradeList;
    int mCrtIndex;
};

#endif // MAINWINDOW_H
