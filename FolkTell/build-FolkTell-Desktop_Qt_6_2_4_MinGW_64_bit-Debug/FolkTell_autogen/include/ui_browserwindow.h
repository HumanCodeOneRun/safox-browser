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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BrowserWindow
{
public:
    QWidget *centralwidget;
    QToolButton *minBtn;
    QToolButton *switchBtn;
    QToolButton *closeBtn;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *tab_2;
    QPushButton *pushButton;

    void setupUi(QMainWindow *BrowserWindow)
    {
        if (BrowserWindow->objectName().isEmpty())
            BrowserWindow->setObjectName(QString::fromUtf8("BrowserWindow"));
        BrowserWindow->resize(3327, 1793);
        BrowserWindow->setStyleSheet(QString::fromUtf8("border-radius: 0px 0px 8px 8px;\n"
"background-color: rgba(46, 50, 53, 100);"));
        centralwidget = new QWidget(BrowserWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        minBtn = new QToolButton(centralwidget);
        minBtn->setObjectName(QString::fromUtf8("minBtn"));
        minBtn->setGeometry(QRect(58, 24, 23, 23));
        minBtn->setStyleSheet(QString::fromUtf8("background-color: rgba(241, 195, 78, 100);\n"
"width:20px;\n"
"height:20px;\n"
"border-radius:10px;"));
        minBtn->setIconSize(QSize(20, 20));
        switchBtn = new QToolButton(centralwidget);
        switchBtn->setObjectName(QString::fromUtf8("switchBtn"));
        switchBtn->setGeometry(QRect(87, 24, 23, 23));
        switchBtn->setStyleSheet(QString::fromUtf8("background-color: rgba(57, 194, 77, 100);\n"
"width:20px;\n"
"height:20px;\n"
"border-radius:10px;"));
        switchBtn->setIconSize(QSize(20, 20));
        closeBtn = new QToolButton(centralwidget);
        closeBtn->setObjectName(QString::fromUtf8("closeBtn"));
        closeBtn->setGeometry(QRect(29, 24, 23, 23));
        closeBtn->setStyleSheet(QString::fromUtf8("background-color: rgba(235, 106, 99, 100);\n"
"width:20px;\n"
"height:20px;\n"
"border-radius:10px;"));
        closeBtn->setIconSize(QSize(20, 20));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(150, 20, 127, 80));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tabWidget->addTab(tab_2, QString());
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(580, 280, 93, 29));
        pushButton->setStyleSheet(QString::fromUtf8("border-radius:10px;"));
        BrowserWindow->setCentralWidget(centralwidget);

        retranslateUi(BrowserWindow);

        QMetaObject::connectSlotsByName(BrowserWindow);
    } // setupUi

    void retranslateUi(QMainWindow *BrowserWindow)
    {
        BrowserWindow->setWindowTitle(QCoreApplication::translate("BrowserWindow", "BrowserWindow", nullptr));
        minBtn->setText(QString());
        switchBtn->setText(QString());
        closeBtn->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("BrowserWindow", "Tab 1", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("BrowserWindow", "Tab 2", nullptr));
        pushButton->setText(QCoreApplication::translate("BrowserWindow", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BrowserWindow: public Ui_BrowserWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BROWSERWINDOW_H
