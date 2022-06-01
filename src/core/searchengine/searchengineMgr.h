//
// Created by Howell Young on 2022/5/27.
//

#ifndef SAFOX_SEARCHENGINEMGR_H
#define SAFOX_SEARCHENGINEMGR_H
#include "QString"
#include "QObject"

class SearchEngineManager : public QObject{
public:
    explicit SearchEngineManager();

    void addSearchEngine(QString name, QString value);

    void deleteSearchEngine(QString name);

    void changeDefaultSearchEngine(QString name);

    inline QString getSearchEngineUrl(){
        return m_defaultSearchEngineUrl;
    }

    inline QString getSearchEngineName() {
        return m_defaultSearchEngineName;
    }
    

private:
    QString m_defaultSearchEngineName;
    QString m_defaultSearchEngineUrl;

};
#endif //SAFOX_SEARCHENGINEMGR_H
