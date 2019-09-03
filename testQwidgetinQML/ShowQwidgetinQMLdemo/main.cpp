#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QQmlContext>
#include <QQmlEngine>
#include <QtQml>

#include "form.h"
#include "form01.h"
#include "./comtrde/mainwindow.h"
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDebug>
#include <QApplication>

//Form01 Widget;

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

//        //qmlRegisterType<Form01>("Form01", 1, 0, "Form01");
//        QObject *QmlObj_01=engine.rootObjects().at(1);
//        QWindow *QmlWindow_01=qobject_cast<QWindow *>(QmlObj_01);
//        QmlWindow_01->setTitle("01 01 test widget in qml 01 01");
        qDebug()<<"engine.rootObjects().count():"<<engine.rootObjects().count();

//        QWidget Widget; //新建一个Widget
//        Widget.setGeometry(0,0,180,180);//设置widget的大小
//        Widget.setStyleSheet("background-color: lightgray; color: naviy;");//设置风格，方便辨识
//        Widget.setProperty("_q_embedded_native_parent_handle",QVariant(parent_HWND));//给widget父对象句柄赋值
//        QLabel Label("this is Widget",&Widget); //在widget中添加一个标签
//        Label.setGeometry(0,0,140,40);   //标签属性设置
//        QLineEdit Edit("",&Widget);      //添加输入框
//        Edit.setGeometry(0,50,100,20);
//        QPushButton Btn("send",&Widget);    //添加按钮
//        Btn.setGeometry(100,100,60,20);

        Form01 Widget;
        //Widget.setGeometry(0,100,180,500);//设置widget的大小
        Widget.setGeometry(0,100,1200,500);
        Widget.setStyleSheet("background-color: lightgray; color: naviy;");//设置风格，方便辨识
        Widget.setProperty("_q_embedded_native_parent_handle",QVariant(parent_HWND));//给widget父对象句柄赋值

        engine.rootContext()->setContextProperty("Widget", &Widget);

        Widget.winId();//必须调用，才能为widget创建句柄，否则将会失败
        Widget.windowHandle()->setParent(QmlWindow);//同样是设置父窗口
        //Widget.show();
        if(Widget.isModal())//判断是否是模态对话框
        {
            qDebug()<<"model"<<endl;
        }else{
             qDebug()<<"not model"<<endl;

        }


        MainWindow Mainwindow01;
        Mainwindow01.setStyleSheet("background-color: lightblue; color: naviy;");//设置风格，方便辨识
        Mainwindow01.setProperty("_q_embedded_native_parent_handle",QVariant(parent_HWND));//给widget父对象句柄赋值
        Mainwindow01.winId();
        Mainwindow01.windowHandle()->setParent(QmlWindow);//同样是设置父窗口
        engine.rootContext()->setContextProperty("Mainwindow", &Mainwindow01);

        return app.exec();






}
