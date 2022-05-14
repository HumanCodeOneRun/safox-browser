#include "browser.h"

Browser::Browser(QObject *parent,int userid)
    : QObject{parent}
{
    this->userid = userid;
}
