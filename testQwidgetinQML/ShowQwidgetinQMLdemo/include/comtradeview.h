#ifndef COMTRADEVIEW_H
#define COMTRADEVIEW_H

#include "comtradeview_global.h"
#include "../comtrde/mainwindow.h"
#include "./include/channeldialog.h"
#include "./include/mainform.h"

class COMTRADEVIEWSHARED_EXPORT Comtradeview
{

public:
    Comtradeview();
     ~Comtradeview();
    MainForm *w;//窗体
    /**
     * @brief Show  显示录波文件波形
     * @param showpicture_flag 是否显示图形,1-显示图形;0-不显示图形
     * @param filepath  cfg文件全路径
     * @param savepicture_flag 是否存储图形文件标志位：1-保存，0-不保存
     * @param picturepath 图片存储全路径
     * @return 返回图形显示及图形保存的状态:0-画图显示报错;1-选择不保存文件;2-保存文件成功;3-保存文件失败
     */

    unsigned char Show(unsigned char showpicture_flag,QString filepath,unsigned char savepicture_flag,QString picturepath);


    /**
     * @brief Show  显示录波文件波形
     * @param showpicture_flag 是否显示图形,1-显示图形;0-不显示图形
     * @param filepath  cfg文件全路径
     * @param savepicture_flag 是否存储图形文件标志位：1-保存，0-不保存
     * @param picturepath 图片存储全路径
     * @param channelType 0-所有通道；1-通道名称；2-通道序号（序号从1开始）
     * @param channelNames 用户输入的备选通道名list
     * @return 返回图形显示及图形保存的状态:0-画图显示报错;1-选择不保存文件;2-保存文件成功;3-保存文件失败
     */
    unsigned char ShowSpecifiedChannels(unsigned char showpicture_flag,QString filepath,unsigned char savepicture_flag,QString picturepath,char channelType,QStringList channelNames);

    /**
     * @brief Show_withChannelSelect   显示录波文件对应的通道选择
     * @param filepath  cfg文件全路径
     * @param type 0-备选显示所有配置文件的通道；1-备选只显示用户输入的配置文件中有的通道
     * @param channelNames 用户输入的备选通道名list
     * @return 0-界面展示失败;1-界面展示成功
     */
    unsigned char Show_withChannelSelect(QString filepath,int type,QStringList channelNames);



    /**********波形操作的一些接口**********/
    /**
     * @brief HorizontalScale 水平方向缩放
     * @param factor 缩放因子,大于1为放大，小于1为缩小，等于1不变，不可小于0，推荐1.1和0.9
     * @return 成功为true，失败为false
     */
    bool HorizontalScale(double factor);
    /**
     * @brief VerticalScale 垂直方向缩放
     * @param factor 缩放因子,大于1为放大，小于1为缩小，等于1不变，不可小于0,推荐1.1和0.9
     * @return  成功为true，失败为false
     */
    bool VerticalScale(double factor);
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
     * @param color 设置的颜色，默认黑色背景，坐标轴白色;其他背景，坐标轴黑色。
     */
    void setbackground(QColor color);
    /**
     * @brief showHrmWidget显示谐波分析界面
     */
    void showHrmWidget();
    /**
     * @brief showAnglWidget显示相角分析界面
     */
    void showAnglWidget();






//    bool savePicture(QString picturefilepath);

private:

     ChannelDialog *channel_frm;

};

#endif // COMTRADEVIEW_H
