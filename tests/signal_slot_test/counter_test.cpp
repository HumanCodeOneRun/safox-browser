#include "browserwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

//test core used by cuddly
#include "Core/historymodel.h"
#include <iostream>
#include <QObject>
#include "test/counter.h"


int main(int argc, char *argv[])
{
    //HistoryModel historyModel;
    Counter a, b;
    QObject::connect(&a, &Counter::value_change, &b, &Counter::setvalue);
    a.setvalue(1, 2);
    std::cout<<b.value1<<" "<<b.value2<<std::endl;
    
}
