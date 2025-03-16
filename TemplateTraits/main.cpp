//
// Created by Sean on 3/16/25.
//

#include "idTraits.hpp"

int main() {
    Class_With_Id c1;
    call_has_id<Class_With_Id>(c1);

    auto data = new Data_with_id<Class_With_Id>();
    // auto data2 = new Data_with_id<Class_Without_Id>();

    auto data_a = new Class_has_id("ok");
    auto class_with_id = new Data_has_Id<Class_has_id>(*data_a);

    auto data_with_out = new Class_has_not_id();
    auto class_with_out_id = new Data_has_Id<Class_has_not_id>(*data_with_out);

}
