//
// Created by Howell Young on 2022/5/13.
//

#include "setting/homepage.h"
#include <QDebug>
#include <iostream>

using namespace std;
int main(){
    QUrl url1("https://github.com/");
    QUrl url2("https://bilibili.com/");
    int set1 = setHomePage(url1);
    int set2 = setHomePage(url2);
    QString output = getHomePage().toString();
    printf("%s\n",output.toStdString().data());
    return !(set1 && set2);

    
}