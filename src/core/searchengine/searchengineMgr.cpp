//
// Created by Howell Young on 2022/5/27.
//
#include "searchengineMgr.h"
#include "Config.h"

void SearchEngineManager::addSearchEngine(QString name, QString value) {
    Config con;
    con.Set(name, value);
}

void SearchEngineManager::deleteSearchEngine(QString name) {
    Config con;
    con.Delete(name);
}

void SearchEngineManager::changeDefaultSearchEngine(QString name) {
    Config con;
    m_defaultSearchEngineUrl = con.Get(name).toString();
    m_defaultSearchEngineName = name;
    con.Set("defaultSearchEngine", m_defaultSearchEngineUrl);
    con.Set("defaultSearchEngineName", m_defaultSearchEngineName);
}

SearchEngineManager::SearchEngineManager() {
    Config con;
    if (!con.Contains("defaultSearchEngine")) {
        addSearchEngine("defaultSearchEngineName", "bing");
        addSearchEngine("defaultSearchEngine", "https://cn.bing.com/search?form=MOZLBR&pc=MOZI&q=");
    }
    m_defaultSearchEngineUrl = con.Get("defaultSearchEngine").toString();
    m_defaultSearchEngineName = con.Get("defaultSearchEngineName").toString();
    addSearchEngine("bing", "https://cn.bing.com/search?form=MOZLBR&pc=MOZI&q=");
    addSearchEngine("google", "https://www.google.com/search?q=");
    addSearchEngine("baidu", "https://www.baidu.com/s?wd=");
}
