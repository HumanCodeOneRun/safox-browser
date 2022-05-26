//
// Created by Howell Young on 2022/5/17.
//

#ifndef safox_SERVICE_H
#define safox_SERVICE_H

#include <string>
//#include <QString>
#include <unordered_map>
#include <memory>
#include <map>

class QObject;


template<class KeyType, class BaseServiceType>
class ServiceLocator {
private:
   
    ServiceLocator(const ServiceLocator &) = delete;
    ServiceLocator &operator=(const ServiceLocator &) = delete;

public:
   
    ServiceLocator() = default;

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
#endif //safox_SERVICE_H
