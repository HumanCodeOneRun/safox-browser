//
// Created by Howell Young on 2022/5/17.
//

#ifndef FOLKTELL_SERVICE_H
#define FOLKTELL_SERVICE_H

#include <string>
//#include <QString>
#include <unordered_map>
#include <memory>
#include <map>

class QObject;

/**
 * @class ServiceLocator
 * @brief Handles the registration and lookup of unique services.
 *        This class does not own any of the services stored in its registry.
 *        For QObject-derived types, this would be instantiated with
 *        KeyType = QString, BaseServiceType = QObject
 */
template<class KeyType, class BaseServiceType>
class ServiceLocator {
private:
    /// Non-copyable，this project only needs Pass By Reference
    ServiceLocator(const ServiceLocator &) = delete;

    /// Non-copyable
    ServiceLocator &operator=(const ServiceLocator &) = delete;

public:
    /// Default constructor
    ServiceLocator() = default;

    /// Default destructor
    ~ServiceLocator() = default;


    bool addService(const KeyType &key, std::shared_ptr<BaseServiceType> service) {
        auto it = m_serviceMap.find(key);
        if (it != m_serviceMap.end())
            return false;

        m_serviceMap[key] = service;
        return true;
    }

    std::shared_ptr<BaseServiceType> getService(const KeyType &key) const {
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
    std::shared_ptr<Derived> getServiceAs(const KeyType &key) const {
        static_assert(std::is_base_of<BaseServiceType, Derived>::value, "Object should inherit from BaseServiceType");

        if (std::shared_ptr<BaseServiceType> service = getService(key))
            return std::static_pointer_cast<Derived>(service);
        return nullptr;
    }

private:
    std::map<KeyType, std::shared_ptr<BaseServiceType>> m_serviceMap;
};

using MyServiceLocator = ServiceLocator<std::string , QObject>;
#endif //FOLKTELL_SERVICE_H
