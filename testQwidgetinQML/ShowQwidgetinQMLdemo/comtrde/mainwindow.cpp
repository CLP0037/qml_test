#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    mComtradeList.clear();


}

MainWindow::~MainWindow()
{

    delete ui;
}


void MainWindow::on_btn_show_clicked()
{
    QString cfg_path = ui->lineEdit_cfgpath->text();
    //frm_comtrade = new Comtradeview();
    Comtradeview *comtrade = new Comtradeview();
    if(isFileExist(cfg_path))
    {
        unsigned char save_flag;
        if(ui->checkBox->isChecked())
            save_flag=1;
        else
            save_flag=0;
        QString picturepath;
        picturepath = ui->lineEdit_picturepath->text();
        comtrade->Show(1,cfg_path,save_flag,picturepath);
        ui->tabWidget->addTab(comtrade->w,cfg_path.mid(cfg_path.lastIndexOf("/")+1));
    }
    else
    {
        //录波文件不存在
    }
    mComtradeList.append(comtrade);
}

bool MainWindow::isDirExist(QString fullPath)
{
    QDir dir(fullPath);
    if(dir.exists())
    {
      return true;
    }
    return false;
}

bool MainWindow::isFileExist(QString fileFullName)
{
    QFileInfo fileInfo(fileFullName);
    if(fileInfo.isFile())
    {
        return true;
    }
    return false;
}

void MainWindow::on_btn_pathselect_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("Open cfg File"),
                                                qApp->applicationDirPath(),QString::fromLocal8Bit("cfg Files(*.cfg)"));
    ui->lineEdit_cfgpath->setText(path);
}

void MainWindow::on_btn_save_clicked()//保存最后一次显示的图形
{
    //QString picture_path = ui->lineEdit_picturepath->text().trimmed();
    ////bool MainForm::savePicturetoFile(QString picturefilepath)
    //frm_comtrade->savePicture(picture_path);
}

void MainWindow::on_Btn_T0_clicked()
{
    mComtradeList.value(mCrtIndex)->showT0();
}

void MainWindow::on_Btn_vscale0_clicked()
{
    mComtradeList.value(mCrtIndex)->VerticalScale(0.9);
}

void MainWindow::on_Btn_vscale1_clicked()
{
    mComtradeList.value(mCrtIndex)->VerticalScale(1.1);
}

void MainWindow::on_Btn_hscale0_clicked()
{
    mComtradeList.value(mCrtIndex)->HorizontalScale(0.9);
}

void MainWindow::on_Btn_hscale_clicked()
{
    mComtradeList.value(mCrtIndex)->HorizontalScale(1.1);
}

void MainWindow::on_Btn_recover_clicked()
{
    mComtradeList.value(mCrtIndex)->Recover();
}

void MainWindow::on_Btn_showall_clicked()
{
    mComtradeList.value(mCrtIndex)->showAll();
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    mCrtIndex = index;
}

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    QColor color;
    if(arg1 == g_C2Q("白色")){
        color.setNamedColor("white");
    }
    else if(arg1 == g_C2Q("黄色")){
        color.setNamedColor("yellow");
    }
    else if(arg1 == g_C2Q("黑色")){
        color.setNamedColor("black");
    }
    else if(arg1 == g_C2Q("红色")){
        color.setNamedColor("red");
    }
    else if(arg1 == g_C2Q("绿色")){
        color.setNamedColor("green");
    }
    else
        color.setNamedColor("black");

    mComtradeList.value(ui->tabWidget->currentIndex())->setbackground(color);
}

void MainWindow::on_Btn_max_clicked()
{
    mComtradeList.value(ui->tabWidget->currentIndex())->showMaxPoint();
}

void MainWindow::on_Btn_min_clicked()
{
    mComtradeList.value(ui->tabWidget->currentIndex())->showMinPoint();
}

void MainWindow::on_comboBox_2_currentIndexChanged(const QString &arg1)
{
    if(arg1 == g_C2Q("谐波分析"))
        mComtradeList.value(ui->tabWidget->currentIndex())->showHrmWidget();
    else if(arg1 == g_C2Q("相角分析"))
        mComtradeList.value(ui->tabWidget->currentIndex())->showAnglWidget();//mComtradeList.value(ui->tabWidget->currentIndex())->showHrmWidget();
}

void MainWindow::on_btn_back_clicked()
{
    this->close();
}
