#ifndef CHANNELDIALOG_H
#define CHANNELDIALOG_H

#include <QDialog>

#define MAXCHANNELNUM 64*2

namespace Ui {
class ChannelDialog;
}

class ChannelDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChannelDialog(QWidget *parent = 0);
    ~ChannelDialog();

    void load_channelsData(QString filePath, int analogCount, QStringList analogList, int digitCount, QStringList  digitList, QStringList analogList_all, QStringList  digitList_all);

    //_analog     _digit
    unsigned char channelChecked_analog[MAXCHANNELNUM];
    unsigned char channelChecked_digit[MAXCHANNELNUM];
    int channelNums_tatal;
    int channelNums_analog;
    int channelNums_digit;
    int channelNums_analog_sel;
    int channelNums_digit_sel;

private slots:
    void on_btn_sel_OK_clicked();

private:
    Ui::ChannelDialog *ui;

    QString frm_filePath;
    int frm_analogCount;
    QStringList frm_analogList;
    int frm_digitCount;
    QStringList  frm_digitList;
    QStringList frm_analogList_all;
    QStringList  frm_digitList_all;
};

#endif // CHANNELDIALOG_H
