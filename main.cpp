#include "./inc/cworld.hpp"
uint64_t tps1 = 0;
int cworld::Main::main(){
    return main();
}
// namespace Threads {
//     std::thread *keyboard_thread;
//     std::thread *tick_thread;
//     std::thread *physics_thread;
// }
std::thread *cworld::Main::Threads::keyboard_thread = nullptr;
std::thread *cworld::Main::Threads::tick_thread = nullptr;
std::thread *cworld::Main::Threads::physics_thread = nullptr;
int main(){
    printf("Loading...\n");

    signal(SIGSEGV, cworld::Protocol::Exceptions::make);
    signal(SIGABRT, cworld::Protocol::Exceptions::make);
    signal(6, cworld::Protocol::Exceptions::make);

    ao_initialize();

    //test
    cworld::World::World worldtest;

    strcpy(worldtest.filename, "test.dat");
    
    std::thread tick_thread(cworld::World::Tick::run, &worldtest);
    tick_thread.detach();
    std::thread keyboard_thread(cworld::Protocol::Keyboard::run, &worldtest);
    keyboard_thread.detach();
    std::thread physics_thread(cworld::World::Physics::run, &worldtest);
    physics_thread.detach();
    cworld::Main::Threads::keyboard_thread = &keyboard_thread;
    cworld::Main::Threads::physics_thread = &physics_thread;
    cworld::Main::Threads::tick_thread = &tick_thread;

    cworld::World::init(&worldtest);

    cworld::World::genc(0, &worldtest);
    cworld::World::placeobj(&worldtest, 0, 255, 1, 1);

    // while(1){
    //     if(cworld::World::Tick::is_tick_done()){
    //         return 0;
    //     }
    // }
    while(1) {
        tps1 = cworld::World::Tick::get();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        tps1 = cworld::World::Tick::get() - tps1;
        cworld::World::Tick::set_tps(tps1);
    }
}