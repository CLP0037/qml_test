#include "qmlplot.h"
//#include "qcustomplot.h"
#include <QDebug>

CustomPlotItem::CustomPlotItem( QQuickItem* parent ) : QQuickPaintedItem( parent )
    , m_CustomPlot( nullptr ), m_timerId( 0 )  //, m_CustomBar( nullptr )
{
    setFlag( QQuickItem::ItemHasContents, true );
    setAcceptedMouseButtons( Qt::AllButtons );

    connect( this, &QQuickPaintedItem::widthChanged, this, &CustomPlotItem::updateCustomPlotSize );
    connect( this, &QQuickPaintedItem::heightChanged, this, &CustomPlotItem::updateCustomPlotSize );

    m_WaveDatavalueList.clear();
    plot_start_flag = false;
    m_BarDataList_multi.clear();
    bar_start_flag = false;
}

CustomPlotItem::~CustomPlotItem()
{
    delete m_CustomPlot;
    m_CustomPlot = nullptr;

    //delete m_CustomBar;
    //m_CustomBar = nullptr;

    if(m_timerId != 0) {
        killTimer(m_timerId);
    }
}


Q_INVOKABLE void CustomPlotItem::initCustomPlot_Lines(int index)
{
    channel_index = index;

    m_CustomPlot = new QCustomPlot();

    updateCustomPlotSize();
    m_CustomPlot->addGraph();
    m_CustomPlot->graph( 0 )->setPen( QPen( Qt::red ) );
    switch(index%4)
    {
        case 0:
            m_CustomPlot->graph(0)->setPen(QPen(Qt::yellow));
        break;
        case 1:
            m_CustomPlot->graph(0)->setPen(QPen(Qt::green));
        break;
        case 2:
            m_CustomPlot->graph(0)->setPen(QPen(Qt::red));
        break;
        case 3:
            m_CustomPlot->graph(0)->setPen(QPen(Qt::blue));
            m_CustomPlot->axisRect(0)->axis(QCPAxis::atLeft)->setRange(0, 2);
        break;
    }

    m_CustomPlot->xAxis->setLabel( "t" );

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    m_CustomPlot->xAxis->setTicker(timeTicker);

    m_CustomPlot->yAxis->setLabel( "S" );
    //m_CustomPlot->xAxis->setRange( 0, 10 );
    m_CustomPlot->yAxis->setRange( 0, 5 );
    m_CustomPlot ->setInteractions( QCP::iRangeDrag | QCP::iRangeZoom );

    //startTimer(200);

    connect( m_CustomPlot, &QCustomPlot::afterReplot, this, &CustomPlotItem::onCustomReplot );

    m_CustomPlot->replot();

    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    dataTimer.start(1000);
    //dataTimer_plot
    connect(&dataTimer_plot, SIGNAL(timeout()), this, SLOT(realtimePlotSlot()));

}

Q_INVOKABLE void CustomPlotItem::initCustomPlot_CPBars(int index)
{
    channel_index = index;

    m_CustomPlot = new QCustomPlot();
    //QCPBars *bar_plot = new QCPBars(m_CustomPlot->xAxis, m_CustomPlot->yAxis);
    m_Barplot = new QCPBars(m_CustomPlot->xAxis, m_CustomPlot->yAxis);
    m_Barplot->setAntialiased(false);
    m_Barplot->setStackingGap(1);
    m_Barplot->setWidth(0.5);
    m_Barplot->setWidthType(QCPBars::wtPlotCoords);
    switch(index%4)
    {
        case 0:
            m_Barplot->setPen(QPen((QColor(218 ,165 ,32,127))));//Qt::yellow
            m_Barplot->setBrush(QBrush(QColor(218 ,165 ,32,127)));//Qt::yellow
        break;
        case 1:
            m_Barplot->setPen(QPen(QColor(95 ,158 ,160 ,127)));//Qt::green
            m_Barplot->setBrush(QBrush(QColor(95 ,158 ,160 ,127)));//Qt::green
        break;
        case 2:
            m_Barplot->setPen(QPen(QColor(219 ,112 ,147,127)));//Qt::red
            m_Barplot->setBrush(QBrush(QColor(219 ,112 ,147,127)));//Qt::red
        break;
        case 3:
            m_Barplot->setPen(QPen(QColor(70 ,130 ,180,127)));//Qt::blue
            m_Barplot->setBrush(QBrush(QColor(70 ,130 ,180,127)));//Qt::blue

        break;
    }
    //customPlot->setBackground(Qt::lightGray);//Qt::black
    m_CustomPlot->axisRect()->setupFullAxesBox();//上右坐标显示
    m_CustomPlot->xAxis->grid()->setVisible(true);
    m_CustomPlot->yAxis->setRange(0, 1.2);
    m_CustomPlot->yAxis->setPadding(3);
    m_CustomPlot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(m_BarticksList, m_BarlabelsList);

    m_CustomPlot->xAxis->setTickLabelRotation(45);//20
    //m_CustomPlotBarList.at(index)->xAxis->setTickLength(0, 4);
    m_CustomPlot->xAxis->setRange(0, 33);
    m_CustomPlot->xAxis->setTicker(textTicker);

//    // Add data:
//    QVector<double> barData;
//    barData  << 0.0030 << 0.8465 << 0.15*0.5 << 0.15*0.3 << 0.15*0.2 << 0.0001 << 0.0001 << 0.0001 << 0.0001 << 0.0001 ;
//    m_Barplot->setData(m_BarticksList, barData);
    m_BarDataList.clear();
    for(int i=0;i<32;i++)
    {
        m_BarDataList.append(((double)rand() / RAND_MAX));
    }
    m_Barplot->setData(m_BarticksList, m_BarDataList);



    connect( m_CustomPlot, &QCustomPlot::afterReplot, this, &CustomPlotItem::onCustomReplot );
    m_CustomPlot->replot(QCustomPlot::rpQueuedReplot);

    connect(&barTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot_bar()));
    barTimer.start(1000);
    //dataTimer_plot
    connect(&barTimer_plot, SIGNAL(timeout()), this, SLOT(realtimePlotSlot_bar()));
}



void CustomPlotItem::initCustomPlot()
{
    m_CustomPlot = new QCustomPlot();

    updateCustomPlotSize();
    m_CustomPlot->addGraph();
    m_CustomPlot->graph( 0 )->setPen( QPen( Qt::red ) );
    m_CustomPlot->xAxis->setLabel( "t" );

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    m_CustomPlot->xAxis->setTicker(timeTicker);

    m_CustomPlot->yAxis->setLabel( "S" );
    //m_CustomPlot->xAxis->setRange( 0, 10 );
    m_CustomPlot->yAxis->setRange( 0, 5 );
    m_CustomPlot ->setInteractions( QCP::iRangeDrag | QCP::iRangeZoom );

    //startTimer(200);

    connect( m_CustomPlot, &QCustomPlot::afterReplot, this, &CustomPlotItem::onCustomReplot );

    m_CustomPlot->replot();

    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    dataTimer.start(1000);
    //dataTimer_plot
    connect(&dataTimer_plot, SIGNAL(timeout()), this, SLOT(realtimePlotSlot()));
}

void CustomPlotItem::realtimeDataSlot()//每秒刷新通道数据
{
    //m_WaveDatavalueList
    //每1s（后期改为接收下位机主动上传数据的槽函数中实现）添加采样数据
    for(int i=0;i<500;i++)
    {
//        if(i==0)qDebug() << Q_FUNC_INFO <<QString("m_WaveDatavalueList.count() = %1, plot_start_flag  = %2")
//                         .arg(QString::number(m_WaveDatavalueList.count()))
//                         .arg((plot_start_flag == false)?"false":"true");

        m_WaveDatavalueList.append(((double)rand() / RAND_MAX) * 5);//
    }


    if(m_WaveDatavalueList.count() >= 500*2 && plot_start_flag == false)
    {
        qDebug() << "prepare to start dataTimer_plot";
        plot_start_flag = true;
        dataTimer_plot.start(200);

        QDateTime time_base = QDateTime::currentDateTime();   //获取当前时间
        m_timebaseT = time_base.toTime_t();
        m_timeCount = 0;
    }
}

void CustomPlotItem::realtimePlotSlot()
{
    static double t, U;
    static QTime time(QTime::currentTime());
//    static QDateTime time_base = QDateTime::currentDateTime();   //获取当前时间
//    static unsigned int timebaseT = time_base.toTime_t();
//    static unsigned int count = 0;

    // calculate two new data points:
    //double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds

//    float time_elapse = (float)time.elapsed();
//    //QString str_times = QString::asprintf("%.0f", (time_elapse/200.0f)) ;
//    int int_times = int((time_elapse/200.0f)+0.5);//四舍五入
//    double key = int_times * 200.0f;
    double key = m_timeCount * 200.0f;//count
    qDebug() << Q_FUNC_INFO << QString("key = %1, timebaseT = %2,(time.elapsed())= %3").arg(key).arg(m_timebaseT).arg(time.elapsed());

    for(int i=0;i<100;i++)//一次新增多个点
    {
        key +=2;
        if(!m_WaveDatavalueList.isEmpty())
        {

            U = m_WaveDatavalueList.at(0);
            m_CustomPlot->graph(0)->addData(key, U);//key+2*i
            m_WaveDatavalueList.takeFirst();
            //qDebug() << Q_FUNC_INFO << QString("Adding dot key = %1, S = %2").arg(key).arg(U);
        }
        else
        {
            qDebug() << Q_FUNC_INFO << "m_WaveDatavalueList is empty,no dot to plot,key="<<key;
        }

    }
    m_timeCount++;//count++;
    m_CustomPlot->xAxis->setRange(key, 500, Qt::AlignRight);

    m_CustomPlot->replot();
}

void CustomPlotItem::realtimeDataSlot_bar()
{
    //刷新数据
    QVector<double> tempBarData;
    for(int i=0;i<5;i++)//00
    {
        tempBarData.clear();
        for(int j=0;j<32;j++)
        {
            tempBarData.append(((double)rand() / RAND_MAX));
        }
        m_BarDataList_multi.append(tempBarData);
    }
    if(m_BarDataList_multi.count() >= 5*2 && bar_start_flag == false)//00
    {
        qDebug() << "prepare to start barTimer_plot";
        bar_start_flag = true;
        barTimer_plot.start(200);
    }
    //m_Barplot->setData(m_BarticksList, m_BarDataList);
}

void CustomPlotItem::realtimePlotSlot_bar()
{
    if(!m_BarDataList_multi.isEmpty())
    {
        m_Barplot->setData(m_BarticksList, m_BarDataList_multi.at(0));

        m_CustomPlot->replot(QCustomPlot::rpQueuedReplot);

        m_BarDataList_multi.takeFirst();

    }
    else
    {
        qDebug() << Q_FUNC_INFO << "m_BarDataList_multi is empty,no dot to plot";
    }
}

void CustomPlotItem::paint( QPainter* painter )
{
    if (m_CustomPlot)
    {
        QPixmap    picture( boundingRect().size().toSize() );
        QCPPainter qcpPainter( &picture );

        m_CustomPlot->toPainter( &qcpPainter );

        painter->drawPixmap( QPoint(), picture );
    }
}

void CustomPlotItem::mousePressEvent( QMouseEvent* event )
{
    qDebug() << Q_FUNC_INFO;
    routeMouseEvents( event );
}

void CustomPlotItem::mouseReleaseEvent( QMouseEvent* event )
{
    qDebug() << Q_FUNC_INFO;
    routeMouseEvents( event );
}

void CustomPlotItem::mouseMoveEvent( QMouseEvent* event )
{
    routeMouseEvents( event );
}

void CustomPlotItem::mouseDoubleClickEvent( QMouseEvent* event )
{
    qDebug() << Q_FUNC_INFO;
    routeMouseEvents( event );
}

void CustomPlotItem::wheelEvent( QWheelEvent *event )
{
    routeWheelEvents( event );
}

/**
 *
 * 起始时标（公元秒6字节）、
 * 周波数（无符号短整型）、
 * 数据点数N（无符号整型）、
 * 点时间间隔（单位微妙，浮点型）、
 * N个数据值（无符号短整型）
 *
 * 收到1s数据
 * 取前500ms数据，后每100ms向后移动100ms数据至下一个1s数据到达？？？
 *
 */
void CustomPlotItem::timerEvent(QTimerEvent *event)
{
    static double t, U;
    static QTime time(QTime::currentTime());
    // calculate two new data points:
    //double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
    double key = time.elapsed();

//    U = ((double)rand() / RAND_MAX) * 5;
//    m_CustomPlot->graph(0)->addData(t, U);
//    qDebug() << Q_FUNC_INFO << QString("Adding dot t = %1, S = %2").arg(t).arg(U);
//    t++;
    for(int i=0;i<100;i++)//一次新增多个点
    {
//        U = ((double)rand() / RAND_MAX) * 5;
//        //m_CustomPlot->graph(0)->addData(t, U);
//        m_CustomPlot->graph(0)->addData(key+2*i, U);//每200ms增加100个点
//        qDebug() << Q_FUNC_INFO << QString("Adding dot t = %1, S = %2").arg(t).arg(U);
//        t++;


        if(!m_WaveDatavalueList.isEmpty())
        {
            U = m_WaveDatavalueList.at(0);
            m_CustomPlot->graph(0)->addData(key+2*i, U);
            m_WaveDatavalueList.takeFirst();
            qDebug() << Q_FUNC_INFO << QString("Adding dot key = %1, S = %2").arg(key).arg(U);
        }

    }

    //m_CustomPlot->xAxis->setRange(t, 80, Qt::AlignRight);
    m_CustomPlot->xAxis->setRange(key, 500, Qt::AlignRight);
//    if(t>30)//200*
//    {

//    }
    m_CustomPlot->replot();
}

void CustomPlotItem::graphClicked( QCPAbstractPlottable* plottable )
{
    qDebug() << Q_FUNC_INFO << QString( "Clicked on graph '%1 " ).arg( plottable->name() );
}

void CustomPlotItem::routeMouseEvents( QMouseEvent* event )
{
    if (m_CustomPlot)
    {
        QMouseEvent* newEvent = new QMouseEvent( event->type(), event->localPos(), event->button(), event->buttons(), event->modifiers() );
        QCoreApplication::postEvent( m_CustomPlot, newEvent );
    }
}

void CustomPlotItem::routeWheelEvents( QWheelEvent* event )
{
    if (m_CustomPlot)
    {
        QWheelEvent* newEvent = new QWheelEvent( event->pos(), event->delta(), event->buttons(), event->modifiers(), event->orientation() );
        QCoreApplication::postEvent( m_CustomPlot, newEvent );
    }
}

void CustomPlotItem::updateCustomPlotSize()
{
    if (m_CustomPlot)
    {
        m_CustomPlot->setGeometry(0, 0, (int)width(), (int)height());
        m_CustomPlot->setViewport(QRect(0, 0, (int)width(), (int)height()));
    }
}

void CustomPlotItem::onCustomReplot()
{
    qDebug() << Q_FUNC_INFO;
    update();
}
