#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "form.h"
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDebug>
#include <QApplication>

int main(int argc, char *argv[])
{
//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

//    QGuiApplication app(argc, argv);

//    QQmlApplicationEngine engine;


//    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


////    Form fm;
////        fm.setAttribute(Qt::WA_NativeWindow);
////        fm.windowHandle()->setParent(mainWindow);
////        fm.show();
////        fm.move(0,25);


//    if (engine.rootObjects().isEmpty())
//        return -1;

//    return app.exec();


    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

        QApplication app(argc, argv);//因为要创建widget，只能使用QApplication

        QQmlApplicationEngine engine;
        engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
        if (engine.rootObjects().isEmpty())
            return -1;
        QObject *QmlObj=engine.rootObjects().first();//获取QMl的源对象
        QWindow *QmlWindow=qobject_cast<QWindow *>(QmlObj);//获取qml在的源窗口
        QmlWindow->setTitle("test widget in qml");//设置一个窗口标签，确认自己拿到的窗口句柄就是自己想要的
        WId parent_HWND = QmlWindow->winId();  //Qml窗口的句柄
        QWidget Widget; //新建一个Widget
        Widget.setGeometry(0,0,180,180);//设置widget的大小
        Widget.setStyleSheet("background-color: lightgray; color: naviy;");//设置风格，方便辨识
        Widget.setProperty("_q_embedded_native_parent_handle",QVariant(parent_HWND));//给widget父对象句柄赋值
        QLabel Label("this is Widget",&Widget); //在widget中添加一个标签
        Label.setGeometry(0,0,140,40);   //标签属性设置
        QLineEdit Edit("",&Widget);      //添加输入框
        Edit.setGeometry(0,50,100,20);
        QPushButton Btn("send",&Widget);    //添加按钮
        Btn.setGeometry(100,100,60,20);
        Widget.winId();//必须调用，才能为widget创建句柄，否则将会失败
        Widget.windowHandle()->setParent(QmlWindow);//同样是设置父窗口
        Widget.show();
        if(Widget.isModal())//判断是否是模态对话框
        {
            qDebug()<<"model"<<endl;
        }else{
             qDebug()<<"not model"<<endl;

        }
        return app.exec();






}
