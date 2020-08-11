#include <iostream>
#include <cstdlib>

#include "mpm/eventbus.h"
using eventbus = mpm::basic_eventbus<std::allocator<    std::pair<const std::type_index, mpm::detail::subscription>    >>;




// Определение событий:

struct my_object {};

struct my_non_polymorphic_event : my_object
{
    int foo = -1;
};




int main(int argc, char* argv[]) {
    
    eventbus ebus;

    // two subscriptions - 1 for my_object, 1 for my_non_polymorphic_event

    auto base_subscription = mpm::scoped_subscription<my_object> {
        ebus, [](const my_object& mo) noexcept {
            std::cout << "handling a my_object";
        }
    };

    auto non_poly_subscription = mpm::scoped_subscription<my_non_polymorphic_event> {
        ebus, [](const my_non_polymorphic_event& mnpe) noexcept {
            std::cout << "handling a my_non_polymorphic_event " << mnpe.foo;
        }
    };
    
    // Для неполиморфической отправки, тип объекта может быть опубликован
    // и он будет обработан только обработчиками точно такого же типа.

    // publish
    ebus.publish(my_non_polymorphic_event{});
    // Сработает только обработчик для my_non_polymorphic_event потому что
    // нет наследования через mpm::enable_polymorphic_dispatch.

    // subscriptions terminate at scope exit
    
    return EXIT_SUCCESS;
}