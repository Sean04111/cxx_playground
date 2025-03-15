//
// Created by Sean on 3/15/25.
//

#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include <memory>

/*info:
 * impl a dynamically allocate memory manager for integar
 * use std::unique_ptr
 * no copy allowed
 */

class ResourceManager {
private:
    std::unique_ptr<int> ptr;
public:
    explicit ResourceManager(int value = 0);
    ~ResourceManager();

    ResourceManager(const ResourceManager& other) = delete;
    ResourceManager& operator=(const ResourceManager& other) = delete;

    ResourceManager(ResourceManager&& other) noexcept;
    ResourceManager& operator=(ResourceManager&& other) noexcept;

    int* operator->() const;
    int& operator*() const;

    int getValue() const;

    void setValue(int newValue);
};

#endif //RESOURCEMANAGER_H
