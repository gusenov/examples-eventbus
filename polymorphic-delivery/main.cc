#include <iostream>
#include <cstdlib>

#include "mpm/eventbus.h"
using eventbus = mpm::basic_eventbus<std::allocator<    std::pair<const std::type_index, mpm::detail::subscription>    >>;




// Определение событий:

struct my_base_event : mpm::enable_polymorphic_dispatch<my_base_event>
{
    int x = 12;
};

// События этого типа будут доставляться как оба Derived и Base.
struct my_derived_event : mpm::enable_polymorphic_dispatch<my_derived_event, my_base_event>
{
    int y = 5;
};




int main(int argc, char* argv[]) {
    
    eventbus ebus;

    // two subscriptions - 1 for my_base_event and 1 for my_derived_event

    auto base_subscription = mpm::scoped_subscription<my_base_event> {
        ebus, [](const auto/*my_base_event*/& mbe) noexcept {
            std::cout << "handling a base event" << mbe.x << std::endl;
        }
    };

    auto derived_subscription = mpm::scoped_subscription<my_derived_event> {
        ebus, [](const auto/*my_derived_event*/& mde) noexcept {
            std::cout << "handling a derived event" << mde.y << std::endl;
        }
    };
    
    // Подписки на события учитывают полиморфизм событий.
    // Подписка на события типа Base будет активизирована при публикации
    // события типа Derived.
    // Derived должен расширять Base через mpm::enable_polymorphic_dispatch,
    // а не напрямую.
    // Необязательно использовать mpm::enable_polymorphic_dispatch.
    // Любой экземпляр С++ объекта может быть опубликован, но если нужна
    // полиморфная доставка то надо использовать mpm::enable_polymorphic_dispatch.

    // publish
    ebus.publish(my_derived_event{});
    // Оба обработчика событий сработают!

    // subscriptions terminate at scope exit
    
    return EXIT_SUCCESS;
}