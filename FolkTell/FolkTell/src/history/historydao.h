
#ifndef HISTORYDAO_H
#define HISTORYDAO_H

#include "../dao/basedao.h"

#define HISTORYDAO_TABLE_NAME "history"



class HistoryDao:BaseDao {

    public:
    HistoryDao();

    bool insert_history_entry();


    public://just for test and it should be changed to private
    unsigned int userid;
};

#endif