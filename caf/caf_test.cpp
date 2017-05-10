#include <iostream>
#include "caf/actor_system.hpp"
#include "caf/actor_system_config.hpp"
#include "caf/event_based_actor.hpp"
#include "caf/blocking_actor.hpp"
#include "caf/exit_reason.hpp"

using namespace std::literals::chrono_literals;

class Blocking : public caf::blocking_actor {
public:
    std::atomic_bool running{true};
    caf::actor actor;

    Blocking(caf::actor_config &cfg) : caf::blocking_actor(cfg) {
        actor = spawn([&](caf::event_based_actor *self) {
            self->set_exit_handler([=](const caf::exit_msg &em) {
                std::cout << "exiting" << std::endl;
                self->quit();
            });
            return caf::behavior{
                [&](const std::string &s, caf::actor sender) {
                    std::cout << "got " << s << std::endl;
                    self->send_exit(sender, caf::exit_reason::kill);
                }
            };
        });
        link_to(actor);
    }

    void act() override {
        receive_while([&]{return running.load();})(
            [&](const std::string &s) {
                send(actor, s, caf::actor_cast<caf::actor>(this));
            },
            [=](const caf::exit_msg &em) {
                running = false;
            }
        );
        std::cout << "act ending" << std::endl;
    }
};

int main(int argc, const char **argv) {
    caf::actor_system_config cfg;
    caf::actor_system system{cfg};

    auto blocky = system.spawn<Blocking>();

    caf::anon_send(blocky, std::string("fart"));

    system.await_all_actors_done();
}
