#include "./inc/crpg.hpp"

int crpg::Main::main(){
    return main();
}

int main(){
    printf("Loading...\n");

    signal(SIGSEGV, crpg::Protocol::Exceptions::make);

    //test
    crpg::World::World worldtest;
    crpg::World::genc(0, &worldtest);
    crpg::World::placeobj(&worldtest, 0, 255, 1, 1);
    crpg::Protocol::save(&worldtest, "test.dat");

    crpg::Render::render(&worldtest);
}