#ifndef QMLPLOT_H
#define QMLPLOT_H

#include <QtQuick>
class QCustomPlot;
class QCPAbstractPlottable;
#include "qcustomplot.h"

using namespace std;
#define g_C2Q(str) QString::fromLocal8Bit(str)
#define g_Q2C(qs)  (const char*)(qs).toLocal8Bit()

class CustomPlotItem : public QQuickPaintedItem
{
    Q_OBJECT

public:
    CustomPlotItem( QQuickItem* parent = 0 );
    virtual ~CustomPlotItem();

    void paint( QPainter* painter );

    Q_INVOKABLE void initCustomPlot();
    Q_INVOKABLE void initCustomPlot_Lines(int index);
    Q_INVOKABLE void initCustomPlot_CPBars(int index);//

protected:
    void routeMouseEvents( QMouseEvent* event );
    void routeWheelEvents( QWheelEvent* event );

    virtual void mousePressEvent( QMouseEvent* event );
    virtual void mouseReleaseEvent( QMouseEvent* event );
    virtual void mouseMoveEvent( QMouseEvent* event );
    virtual void mouseDoubleClickEvent( QMouseEvent* event );
    virtual void wheelEvent( QWheelEvent *event );

    virtual void timerEvent(QTimerEvent *event);

private:
    QCustomPlot*         m_CustomPlot;
    //QCustomPlot*         m_CustomBar;
    QCPBars* m_Barplot;
    int                  m_timerId;

    QTimer dataTimer;
    QTimer dataTimer_plot;
    QTimer barTimer;
    QTimer barTimer_plot;
    bool plot_start_flag;
    bool bar_start_flag;
    int channel_index;

    int m_timebaseT;//启动波形显示的基准时间戳
    int m_timeCount;//计时循环次数

//    * 起始时标（公元秒6字节）、
//    * 周波数（无符号短整型）、
//    * 数据点数N（无符号整型）、
//    * 点时间间隔（单位微妙，浮点型）、
//    * N个数据值（无符号短整型）

    typedef struct
    {
        unsigned int  timestamp_start;  //起始  时间戳
        unsigned int  waveCycle_num;
        unsigned int  waveData_num;
        unsigned int  waveData_interval;
        //ComtradeData      ComtradeData_R[_MAX_DATA_NUM_];
    }_ComtradeInfo_R;//实时录波数据结构体
    QList<float> m_WaveDatavalueList;//

//    QVector<double> ticks;
//    QVector<QString> labels;
    QVector<QString> m_BarlabelsList={g_C2Q("直流分量"),
                                    g_C2Q("基波"),
                                    g_C2Q("2次谐波"),
                                    g_C2Q("3次谐波"),
                                    g_C2Q("4次谐波"),
                                    g_C2Q("5次谐波"),
                                    g_C2Q("6次谐波"),
                                    g_C2Q("7次谐波"),
                                    g_C2Q("8次谐波"),
                                    g_C2Q("9次谐波"),
                                    g_C2Q("10次谐波"),
                                    g_C2Q("11次谐波"),
                                    g_C2Q("12次谐波"),
                                    g_C2Q("13次谐波"),
                                    g_C2Q("14次谐波"),
                                    g_C2Q("15次谐波"),
                                    g_C2Q("16次谐波"),
                                    g_C2Q("17次谐波"),
                                    g_C2Q("18次谐波"),
                                    g_C2Q("19次谐波"),
                                    g_C2Q("20次谐波"),
                                    g_C2Q("21次谐波"),
                                    g_C2Q("22次谐波"),
                                    g_C2Q("23次谐波"),
                                    g_C2Q("24次谐波"),
                                    g_C2Q("25次谐波"),
                                    g_C2Q("26次谐波"),
                                    g_C2Q("27次谐波"),
                                    g_C2Q("28次谐波"),
                                    g_C2Q("29次谐波"),
                                    g_C2Q("30次谐波"),
                                    g_C2Q("31次谐波")
                                   };
    QVector<double> m_BarticksList={1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 , 10 ,
                                  11 , 12 , 13 , 14 , 15 , 16 , 17 , 18 , 19 , 20 ,
                                  21 , 22 , 23 , 24 , 25 , 26 , 27 , 28 , 29 , 30 ,
                                  31 , 32 };
    QVector<double> m_BarDataList;
    QList<QVector<double>> m_BarDataList_multi;

private slots:
    void graphClicked( QCPAbstractPlottable* plottable );
    void onCustomReplot();
    void updateCustomPlotSize();

    void realtimeDataSlot();
    void realtimePlotSlot();
    void realtimeDataSlot_bar();
    void realtimePlotSlot_bar();

};

#endif // QMLPLOT_H
