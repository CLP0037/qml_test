#ifndef XCUSTOMPLOT_H
#define XCUSTOMPLOT_H

#include "./include/qcustomplot.h"
#include "./include/mytracer.h"
#include "./FFTW3_msvc_2017_64/api/fftw3.h"
#include <QObject>
#include <QList>

class XCustomPlot : public QCustomPlot
{
    Q_OBJECT

    public:
        XCustomPlot(QWidget *parent = 0);
        ~XCustomPlot();
        struct _WaveData{
            int num;//0为直流量，1为基波
            double value;//有效值
            double realval;//实部
            double imagval;//虚部
            double angle;//相角
            double per;
        };
        QList<_WaveData> WaveDataList;

        //最大最小值的索引号
        int MaxIndex;
        int MinIndex;
        double PSRate;
        bool Flag;
        QCPTextElement *textelement;
        struct _EleInfo{
            int num;//通道号
            QString name;//通道名
            QString unit;//单位
        }eleinfo;
    protected:
        virtual void mouseMoveEvent(QMouseEvent *event);
signals:
        /**
         * @brief sendPosition 鼠标移动时发送给x的像素位置
         */
        void sendPosition(int x,int y,int num);

    public:
        ///
        /// \brief 设置是否显示鼠标追踪器
        /// \param show:是否显示
        ///
        void showTracer(bool show)
        {
            m_isShowTracer = show;
//            if(m_xTracer)
//                m_xTracer->setVisible(m_isShowTracer);
            foreach (XxwTracer *tracer, m_dataTracers)
            {
                if(tracer)
                    tracer->setVisible(m_isShowTracer);
            }
            if(m_lineTracer)
                m_lineTracer->setVisible(m_isShowTracer);
        }

        ///
        /// \brief 是否显示鼠标追踪器
        /// \return
        ///
        bool isShowTracer(){return m_isShowTracer;}

        /*****数据相关*****/
        void clearDataList();
        void addData(QVector<double>, QVector<double>);
        /**
         * @brief setDefltRange 设置默认比例
         * @param xrange
         * @param yrange
         */
        void setDefltRange(const QCPRange &xrange, const QCPRange &yrange);
        /**
         * @brief initFFTW 初始化fftw，包括plan、内存、周期内数据量
         * @param count 一个周末的数据
         */
        void initFFTW(int count);

        /**
         * @brief setbackground 设置所有customplot的背景色
         * @param color 设置的颜色，默认黑色背景，坐标轴白色;其他背景，坐标轴黑色。设置失败颜色不动
         * @return
         */
        bool setbackground(QColor color);
        /**
         * @brief setMousePositon 设置鼠标的位置，触发类似于鼠标时间
         * @param x
         * @param y
         */
        void setMousePositon(int x,int y);

public slots:
        void setrange(const QCPRange &);
private slots:
        /*****右键相关*****/
        void ShowMenu(QPoint);
        void initMenu();
        void showPrimary();
        void showValue(QAction *action);
        void showAll();
        void RecoverShow();
        void ShowDeflt();
        //轴范围变化记录
        void UpdateXRange(const QCPRange &, const QCPRange &);
        void UpdateYRange(const QCPRange &, const QCPRange &);
    private:
        bool m_isShowTracer;//是否显示追踪器（鼠标在图中移动，显示对应的值）
        XxwTracer *m_xTracer;//x轴
        XxwTracer *m_yTracer;//y轴
        QList<XxwTracer *> m_dataTracers;//
        XxwTraceLine  *m_lineTracer;//直线

        QList<QVector<double>> xlist, ylist;
        /*****x,y轴的显示范围主要用来进行界面恢复*****/
        QCPRange mXOldRange;
        QCPRange mXNewRange;
        QCPRange mYOldRange;
        QCPRange mYNewRange;
        QCPRange mXDfltRange;
        QCPRange mYDfltRange;

        fftw_complex *out;
        double * in;
        fftw_plan p;
        int maxN;

        /*****右键相关*****/
        bool mPrimaryFlag;//显示一次值，默认显示二次值
        QMenu *mMenu;
        QAction *mPrimaryValue;//一次值，默认显示二次值
        QAction *mInstantValue;//瞬时值
        QAction *mTrueRMS;//真有效值，所有值
        QAction *mFRMS;//基波有效值，仅一次
        QAction *mShowAll;//全显
        QAction *mRecoverShow;//恢复上次显示
        QAction *mShowDeflt;//恢复默认比例显示
        QActionGroup *valuegroup;//动作组
        int mshowValueFlags;//0瞬时值1真有效值2基波有效值
        /**
         * @brief do_fftw 计算有效值等
         * @param index 当前点在数据中的位置索引
         * @param graphindex 当前曲线在当前customplot中的graph索引序号
         * @param angle 角度计算
         * @return
         */
        double do_fftw(int index, int graphindex, double &angle);
        /**
         * @brief trasformPos 将鼠标位置转为widget的坐标位置
         * @param mousex
         * @param mousey
         * @param pointx
         * @param pointy
         */
        void trasformPos(int mousex);

};

#endif // XCUSTOMPLOT_H
