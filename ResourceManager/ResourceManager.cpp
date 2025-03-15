//
// Created by Sean on 3/15/25.
//

#include "ResourceManager.hpp"

#include <iostream>

ResourceManager::ResourceManager(int value) {
    ptr = std::make_unique<int>(value);
}

ResourceManager::~ResourceManager() {
    std::cout << "final here" << std::endl;
    ptr.release();
}

ResourceManager::ResourceManager(ResourceManager &&other) noexcept {
    ptr.release();
    ptr = std::move(other.ptr);
}

ResourceManager &ResourceManager::operator=(ResourceManager &&other) noexcept {
    if (this != &other) {
        ptr.release();
        ptr = std::move(other.ptr);
    }
    return *this;
}

int *ResourceManager::operator->() const {
    return ptr.get();
}

int &ResourceManager::operator*() const {
    return *ptr;
}

int ResourceManager::getValue()const{
    return *ptr;
}

void ResourceManager::setValue(int newValue) {
    *ptr = newValue;
}
