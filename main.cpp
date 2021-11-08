#include "./inc/cworld.hpp"

int cworld::Main::main(){
    return main();
}

int main(){
    printf("Loading...\n");

    signal(SIGSEGV, cworld::Protocol::Exceptions::make);

    //test
    cworld::World::World worldtest;
    cworld::World::genc(0, &worldtest);
    cworld::World::placeobj(&worldtest, 0, 255, 1, 1);
    cworld::Protocol::save(&worldtest, "test.dat");

    cworld::Render::render(&worldtest);
}