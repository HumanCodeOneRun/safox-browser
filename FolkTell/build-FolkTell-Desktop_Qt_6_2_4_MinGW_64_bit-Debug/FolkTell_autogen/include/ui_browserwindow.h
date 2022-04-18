/********************************************************************************
** Form generated from reading UI file 'browserwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BROWSERWINDOW_H
#define UI_BROWSERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BrowserWindow
{
public:
    QWidget *centralwidget;
    QToolButton *closeBtn;
    QToolButton *minBtn;
    QToolButton *switchBtn;

    void setupUi(QMainWindow *BrowserWindow)
    {
        if (BrowserWindow->objectName().isEmpty())
            BrowserWindow->setObjectName(QString::fromUtf8("BrowserWindow"));
        BrowserWindow->resize(3327, 1793);
        BrowserWindow->setStyleSheet(QString::fromUtf8("border-radius: 0px 0px 8px 8px;\n"
"background-color: rgba(46, 50, 53, 100);"));
        centralwidget = new QWidget(BrowserWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        closeBtn = new QToolButton(centralwidget);
        closeBtn->setObjectName(QString::fromUtf8("closeBtn"));
        closeBtn->setGeometry(QRect(20, 10, 24, 22));
        closeBtn->setStyleSheet(QString::fromUtf8("background-color: rgba(235, 106, 99, 100);\n"
"width:20px;\n"
"height:20px;\n"
"border-radius:10px;"));
        closeBtn->setIconSize(QSize(20, 20));
        minBtn = new QToolButton(centralwidget);
        minBtn->setObjectName(QString::fromUtf8("minBtn"));
        minBtn->setGeometry(QRect(60, 10, 24, 22));
        minBtn->setStyleSheet(QString::fromUtf8("background-color: rgba(241, 195, 78, 100);\n"
"width:20px;\n"
"height:20px;\n"
"border-radius:10px;"));
        minBtn->setIconSize(QSize(20, 20));
        switchBtn = new QToolButton(centralwidget);
        switchBtn->setObjectName(QString::fromUtf8("switchBtn"));
        switchBtn->setGeometry(QRect(100, 10, 24, 22));
        switchBtn->setStyleSheet(QString::fromUtf8("background-color: rgba(57, 194, 77, 100);\n"
"width:20px;\n"
"height:20px;\n"
"border-radius:10px;"));
        switchBtn->setIconSize(QSize(20, 20));
        BrowserWindow->setCentralWidget(centralwidget);

        retranslateUi(BrowserWindow);

        QMetaObject::connectSlotsByName(BrowserWindow);
    } // setupUi

    void retranslateUi(QMainWindow *BrowserWindow)
    {
        BrowserWindow->setWindowTitle(QCoreApplication::translate("BrowserWindow", "BrowserWindow", nullptr));
        closeBtn->setText(QString());
        minBtn->setText(QString());
        switchBtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class BrowserWindow: public Ui_BrowserWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BROWSERWINDOW_H
