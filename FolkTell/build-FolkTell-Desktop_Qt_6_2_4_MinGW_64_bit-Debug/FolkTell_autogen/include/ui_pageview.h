/********************************************************************************
** Form generated from reading UI file 'pageview.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAGEVIEW_H
#define UI_PAGEVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PageView
{
public:

    void setupUi(QWidget *PageView)
    {
        if (PageView->objectName().isEmpty())
            PageView->setObjectName(QString::fromUtf8("PageView"));
        PageView->resize(400, 300);

        retranslateUi(PageView);

        QMetaObject::connectSlotsByName(PageView);
    } // setupUi

    void retranslateUi(QWidget *PageView)
    {
        PageView->setWindowTitle(QCoreApplication::translate("PageView", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PageView: public Ui_PageView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAGEVIEW_H
