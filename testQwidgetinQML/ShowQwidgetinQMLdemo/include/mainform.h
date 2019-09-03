#ifndef MAINFORM_H
#define MAINFORM_H

#include <QWidget>
//#include "../ieee37.111-comtrade-parser/comtrade_format.h"
#include "./include/comtrade_format.h"
#include "./include/xcustomplot.h"
#include "./include/harmonicform.h"
#include "./include/angleform.h"

using namespace std;
#define g_C2Q(str) QString::fromLocal8Bit(str)
#define g_Q2C(qs)  (const char*)(qs).toLocal8Bit()

#define XRANGE 1000   //默认x轴显示的长度
#define YRANGE 50   //默认x轴显示的长度
#define MINHEIGHT 150   //默认customplot的窗体高度

namespace Ui {
class MainForm;
}

class MainForm : public QWidget
{
    Q_OBJECT

public:
    explicit MainForm(QWidget *parent = 0);
    ~MainForm();

    void setCFGPath(QString filepath);

    /**
     * @brief OpenComtradeFile
     * @param path
     */
    void OpenComtradeFile(QString path);

    bool savePicturetoFile(QString picturefilepath);

    void rescalePicture();


    string& replace_all_distinct(string&  str, const string& old_value, const  string&  new_value);
    void ShowDatNodes(QString path);
    int CountT0Point();
    double ToSeconds(char * time);


    /**********波形操作的一些接口**********/
    /**
     * @brief HorizontalScale 水平方向缩放
     * @param factor 缩放因子,大于1为放大，小于1为缩小，等于1不变，不可小于0
     * @return 成功为true，失败为false
     */
    void HorizontalScale(double factor);
    /**
     * @brief VerticalScale 垂直方向缩放
     * @param factor 缩放因子,大于1为放大，小于1为缩小，等于1不变，不可小于0
     * @return  成功为true，失败为false
     */
    void VerticalScale(double factor);
    /**
     * @brief showAll 波形所有内容显示到当前界面
     */
    void showAll();
    /**
     * @brief showT0 显示故障点，已显示则隐藏
     */
    void showT0();
    /**
     * @brief Recover 恢复到默认比例
     */
    void Recover();
    /**
     * @brief showMaxPoint 最大点定位
     */
    void showMaxPoint();
    /**
     * @brief showMinPoint 最小点定位
     */
    void showMinPoint();

    /**
     * @brief setbackground 设置所有customplot的背景色
     * @param color 设置的颜色，默认黑色背景，坐标轴白色;其他背景，坐标轴黑色。设置失败颜色不动
     * @return
     */
    bool setbackground(QColor color);

    /*****ui->scrollArea_2窗体的操作*****/
    /**
     * @brief showHrmWidget显示谐波分析界面
     */
    void showHrmWidget();
    /**
     * @brief showAnglWidget显示相角分析界面
     */
    void showAnglWidget();
private:
    Ui::MainForm *ui;

    //int mCrtXPos;
    QList<QCPGraph*> graphList;
    QList<QCustomPlot*> controlList;
    QList<QPixmap> pixmapList;
    QGridLayout *gridLayoutMain;
    QVBoxLayout *verticalLayoutCentral;
    QVBoxLayout *verlayout;//ui->scrollArea_2的布局

    int controlList_index;

    QList<QCPItemStraightLine *> mT0LineList;//故障点


    HarmonicForm *mHrmForm;//谐波分析的窗体
    AngleForm *mAngleForm;//相角分析的窗体

    QList<XCustomPlot *> mCstmpltList;      //存储每个通道的QCusomPlot
    QList<int > mMaxList;
    QList<int > mMinList;       //记录每个通道的极值index
    int pointcount;     //点数（显示到显示屏上的，大于1920为1920，小于为实际值）
    int mXRange;    //当前x轴宽度
    QList<QVector<double>> xlist,ylist,x_t0list;    //每个通道的数据
    bool mT0Flag;   //TO点显示/隐藏标志，true/false
    bool mAngleFlag;    //相角分析标志位
    bool mHrmFlag;  //谐波分析标志位
    /**
     * @brief getXRange 获取当前x轴宽度
     */
    void getXRange();
    /*****谐波分析相关*****/

    void initHrmTable();
    void UpHrmTable();

    /*****相角分析相关*****/
    void UpAngleTable();
    /**
     * @brief initAngleTable 将通道号初始化
     *strlist
     */
    void initAngleTable(QStringList strlist);


public:
    QString file_type;
    cmtr_cfg_info *cfgInfo;
    cmtr_cfg_info *cfgInfoWrite;
    QString path;
    cmtr_dat_smpdot *datInfo;
    cmtr_dat_smpdot *datInfoWrite;
    QList<cmtr_dat_smpdot> datList;
    QString cfgfilepath;


private slots:
    void contextMenuRequest(QPoint pos);
    void contextMenuRequest_0(QPoint pos,unsigned char index);
    void contextMenuRequest_1(QPoint pos);
    void contextMenuRequest_2(QPoint pos);
    void contextMenuRequest_3(QPoint pos);
    void rescaleShow();
    void on_horizontalScrollBar_valueChanged(int value);
    void sendPosition(int x, int y, int num);
    void on_pushButton_clicked();
    void updtChannel();
};

#endif // MAINFORM_H
