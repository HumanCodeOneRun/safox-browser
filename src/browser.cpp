#include "browser.h"

Browser::Browser(int userid)
{
    this->userid = userid;
    this->baseHistory = new History(userid);
}
