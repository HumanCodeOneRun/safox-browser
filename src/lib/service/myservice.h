//
// Created by Howell Young on 2022/5/17.
//

#ifndef _SERVICE_H
#define _SERVICE_H

#include <map>
#include <QString>
#include <QObject>

/**
 * @class MyServiceLocator
 * @brief Handles the registration and lookup of unique services.
 *        This class does not own any of the services stored in its registry.
 *        For QObject-derived types, this would be instantiated with
 *        QString = QString, QObject = QObject
 */

class MyServiceLocator {
private:
    /// Non-copyable，this project only needs Pass By Reference
    MyServiceLocator(const MyServiceLocator &) = delete;

    /// Non-copyable
    MyServiceLocator &operator=(const MyServiceLocator &) = delete;

public:
    /// Default constructor
    MyServiceLocator() = default;

    /// Default destructor
    ~MyServiceLocator() = default;


    bool addService(const QString &key, std::shared_ptr<QObject> service) {
        auto it = m_serviceMap.find(key);
        if (it != m_serviceMap.end())
            return false;

        m_serviceMap[key] = service;
        return true;
    }

    std::shared_ptr<QObject> getService(const QString &key) const {
        const auto it = m_serviceMap.find(key);
        if (it == m_serviceMap.end())
            return nullptr;

        return it->second;
    }

    /**
     * @brief getServiceAs Looks for and attempts to return a service with the key
     * @param key
     * @return a Derived type pointer to the service if found, or a nullptr if not found
     */
    template<class Derived>
    std::shared_ptr<Derived> getServiceAs(const QString &key) const {
        static_assert(std::is_base_of<QObject, Derived>::value, "Object should inherit from QObject");

        if (std::shared_ptr<QObject> service = getService(key))
            return std::static_pointer_cast<Derived>(service);
        return nullptr;
    }

private:
    std::map<QString, std::shared_ptr<QObject>> m_serviceMap;
};

//using MyServiceLocator = MyServiceLocator<QString , QObject>;
#endif //FOLKTELL_SERVICE_H
