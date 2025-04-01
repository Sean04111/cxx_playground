//
// Created by Sean on 4/1/25.
//

#pragma once
#ifndef LOCK_FREE_STACK_WITH_HAZARD_POINTER_HPP
#define LOCK_FREE_STACK_WITH_HAZARD_POINTER_HPP
#include <atomic>

#include "lock_free_stack_with_delete_list.hpp"

template <typename T>
class lock_free_stack_with_hazard_pointer : public lock_free_stack_with_delete_list<T> {
private:
    std::atomic<void*>& get_hazard_pointer_for_current_thread();
public:
    std::shared_ptr<T> pop() {
        std::atomic<void*> & hp = get_hazard_pointer_for_current_thread();
        node* old_head = head.load();
        node* temp;

        do {
            temp = old_head;
            hp.store(old_head);
            old_head = head.load();
        }while (old_head != temp);

        // ....
    }
};

#endif //LOCK_FREE_STACK_WITH_HAZARD_POINTER_HPP
