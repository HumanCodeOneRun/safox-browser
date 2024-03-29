#include "userdao.h"

UserDao::UserDao(std::shared_ptr<DatabaseTaskScheduler> _scheduler, const QString &_table_name)
        : BaseDao(_scheduler, _table_name) {
    createTable();

}


bool UserDao::createTable() {
    check_thread_connection();
    QString cmd = "CREATE TABLE IF NOT EXISTS " + this->getTableName() +
                  " (ID INTEGER PRIMARY KEY AUTOINCREMENT, NAME TEXT UNIQUE NOT NULL, PASSWORD TEXT);";
    QSqlQuery query(BaseDao::db_connection.localData()->get_db_connection());
    bool ok = query.exec(cmd);

    if (!ok) {
        qDebug() << "[error] fail to create User table " << query.lastError().text();
        return false;
    }

    return true;
}


QVector<QVariant> UserDao::QueryById(const int &id) {
    check_thread_connection();
    auto db = BaseDao::db_connection.localData()->get_db_connection();
    QString cmd = "SELECT * from " + this->getTableName() + " WHERE ID=" + QString::number(id);
    QVector<QVariant> ret;

    if (db.transaction()) {
        QSqlQuery query(db);
        query.prepare(cmd);

        if (!query.exec()) {
            qDebug() << "[error] fail to query by id,  " << query.lastError().text();
            db.rollback();
            return ret;
        }

        if (!db.commit()) {
            qDebug() << "[error] fail to commit " << db.lastError().text();
            db.rollback();
            return ret;
        }

        while (query.next()) {
            ret.append({query.value(0), query.value(1), query.value(2)});
        }
    } else {
        qDebug() << "[error] fail to start transaction " << db.lastError().text();
        return ret;
    }
    return ret;
}

QVector<QVariant> UserDao::QueryByIdPassword(const int &id, const QString &password) {
    check_thread_connection();
    auto db = BaseDao::db_connection.localData()->get_db_connection();
    QString cmd = "SELECT * from " + this->getTableName() + " WHERE ID=" + QString::number(id) + " AND PASSWORD=\"" +
                  password + "\"";
    QVector<QVariant> ret;

    if (db.transaction()) {
        QSqlQuery query(db);
        query.prepare(cmd);

        if (!query.exec()) {
            qDebug() << "[error] fail to query by id and password,  " << query.lastError().text();
            db.rollback();
            return ret;
        }

        if (!db.commit()) {
            qDebug() << "[error] fail to commit " << db.lastError().text();
            db.rollback();
            return ret;
        }

        while (query.next()) {
            ret.append({query.value(0), query.value(1), query.value(2)});
        }
    } else {
        qDebug() << "[error] fail to strt transaction " << db.lastError().text();
        return ret;
    }

    return ret;
}

QVector<QVariant> UserDao::QueryByNamePassword(const QString &name, const QString &password) {
    check_thread_connection();
    auto db = BaseDao::db_connection.localData()->get_db_connection();
    QString cmd =
            "SELECT * from " + this->getTableName() + " WHERE NAME=\"" + name + "\" AND PASSWORD=\"" + password + "\"";
    QVector<QVariant> ret;

    if (db.transaction()) {
        QSqlQuery query(db);
        query.prepare(cmd);

        if (!query.exec()) {
            qDebug() << "[error] fail to query by id and password,  " << query.lastError().text();
            db.rollback();
            return ret;
        }

        if (!db.commit()) {
            qDebug() << "[error] fail to commit " << db.lastError().text();
            db.rollback();
            return ret;
        }

        while (query.next()) {
            ret.append({query.value(0), query.value(1), query.value(2)});
        }
    } else {
        qDebug() << "[error] fail to start transaction " << db.lastError().text();
        return ret;
    }

    return ret;
}

QVector<QVariant> UserDao::QueryByName(const QString &name) {
    check_thread_connection();
    auto db = BaseDao::db_connection.localData()->get_db_connection();
    QString cmd = "SELECT * from " + this->getTableName() + " WHERE NAME=\"" + name + "\"";
    QVector<QVariant> ret;

    if (db.transaction()) {
        QSqlQuery query(db);
        query.prepare(cmd);

        if (!query.exec()) {
            qDebug() << "[error] fail to query by name,  " << query.lastError().text();
            db.rollback();
            return ret;
        }

        if (!db.commit()) {
            qDebug() << "[error] fail to commit " << db.lastError().text();
            db.rollback();
            return ret;
        }

        while (query.next()) {
            ret.append({query.value(0), query.value(1), query.value(2)});
        }
    } else {
        qDebug() << "[error] fail to start transaction " << db.lastError().text();
        return ret;
    }

    return ret;
}


bool UserDao::setName(const int &id, const QString &name) {
    check_thread_connection();
    auto db = BaseDao::db_connection.localData()->get_db_connection();
//    QString cmd = "UPDATE " + this->table_name + "SET NAME =\"" + name + "\" WHERE ID"+QString::number(id);
    QString cmd = "UPDATE " + this->getTableName() + " SET NAME= \"" + name + "\" WHERE ID= " + QString::number(id);

    if (db.transaction()) {
        QSqlQuery query(BaseDao::db_connection.localData()->get_db_connection());

        query.bindValue(":name", name);
        query.bindValue(":id", id);
        if (!query.prepare(cmd)) {
            qDebug() << "[error] fail to prepare cmd in setname: " << query.lastError().text();
            db.rollback();
            return false;
        }


        if (!query.exec()) {
            qDebug() << "[error] fail to exec cmd in setname: " << query.lastError().text();
            db.rollback();
            return false;
        }

        if (!db.commit()) {
            qDebug() << "[error] fail to commit " << db.lastError().text();
            db.rollback();
            return false;
        }
    } else {
        qDebug() << "[error] fail to strt transaction " << db.lastError().text();
        return false;
    }

    return true;
}

bool UserDao::setPassword(const int &id, const QString &password) {
    check_thread_connection();
    auto db = BaseDao::db_connection.localData()->get_db_connection();
    QString cmd =
            "UPDATE " + this->getTableName() + " SET PASSWORD= \"" + password + "\" WHERE ID= " + QString::number(id);

    if (db.transaction()) {
        QSqlQuery query(db);

        if (!query.prepare(cmd)) {
            qDebug() << "[error] fail to prepare cmd in setpassword: " << query.lastError().text();
            db.rollback();
            return false;
        }


        if (!query.exec()) {
            qDebug() << "[error] fail to exec cmd in setpassword: " << query.lastError().text();
            db.rollback();
            return false;
        }

        if (!db.commit()) {
            qDebug() << "[error] fail to commit " << db.lastError().text();
            db.rollback();
            return false;
        }
    } else {
        qDebug() << "[error] fail to strt transaction " << db.lastError().text();
        return false;
    }
    return true;
}


bool UserDao::insert(const QString &name, const QString &password) {
    check_thread_connection();
    auto db = BaseDao::db_connection.localData()->get_db_connection();
    QString cmd = "INSERT INTO " + this->getTableName() + "( NAME, PASSWORD)" + " VALUES( :name, :password)";

    if (db.transaction()) {
        QSqlQuery query(db);
        query.prepare(cmd);
        // query.bindValue(":id", id);
        query.bindValue(":name", name);
        query.bindValue(":password", password);

        if (!query.exec()) {
            qDebug() << "[error] fail to insert,  " << query.lastError().text();
            db.rollback();
            return false;
        }

        if (!db.commit()) {
            qDebug() << "[error] fail to commmit " << db.lastError().text();
            db.rollback();
            return false;
        }
        query.finish();
    } else {
        qDebug() << "[error] fail to strt transaction " << db.lastError().text();
        return false;
    }

    return true;
}

bool UserDao::remove(const int &id) {
    check_thread_connection();
    auto db = BaseDao::db_connection.localData()->get_db_connection();
    QString cmd = "DELETE FROM " + this->table_name + " WHERE ID=:id";

    if (db.transaction()) {
        QSqlQuery query(db);
        query.prepare(cmd);
        query.bindValue(":id", id);

        if (!query.exec()) {
            qDebug() << "[error] fail to delete,  " << query.lastError().text();
            return false;
        }

        if (!db.commit()) {
            qDebug() << "[error] fail to commit " << db.lastError().text();
            return false;
        }
    } else {
        qDebug() << "[error] fail to strt transaction " << db.lastError().text();
        return false;
    }

    return true;
}

QVector<QVariant> UserDao::getcolumns() {
    check_thread_connection();
    auto db = BaseDao::db_connection.localData()->get_db_connection();
    QString cmd = "PRAGMA  table_info(" + this->table_name + ")";
    QVector<QVariant> ret;

    if (db.transaction()) {
        QSqlQuery query(db);
        query.prepare(cmd);

        if (!query.exec()) {
            qDebug() << "[error] fail to query all columns,  " << query.lastError().text();
            return ret;
        }

        if (!db.commit()) {
            qDebug() << "[error] fail to commit " << db.lastError().text();
            return ret;
        }
        while (query.next()) {
            ret.append({query.value(0), query.value(1), query.value(2)});
        }
    } else {
        qDebug() << "[error] fail to strt transaction " << db.lastError().text();
        return ret;
    }

    return ret;
}

void UserDao::showAll() {
    check_thread_connection();
    QString cmd = "SELECT * FROM " + this->table_name;
    QSqlQuery query(BaseDao::db_connection.localData()->get_db_connection());
    query.prepare(cmd);

    if (!query.exec()) {
        qDebug() << "[error] fail to query all  " << query.lastError().text();
    }

    while (query.next()) {

        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        QString pwd = query.value(2).toString();
        qDebug() << id << name << pwd;
    }

}

bool UserDao::deleteTable() {
    check_thread_connection();
    QString cmd = "DROP TABLE " + this->table_name;

    QSqlQuery query(BaseDao::db_connection.localData()->get_db_connection());
    query.prepare(cmd);

    if (!query.exec()) {
        qDebug() << "[error] fail to delete table,  " << query.lastError().text();
        return false;
    }

    return true;
}


UserDao::~UserDao() {
}
