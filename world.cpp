#include "inc/crpg.hpp"

unsigned char crpg::World::genc(unsigned char chunky, crpg::World::World *world){
    world->chunks[world->chunkp].is_used = true;
    world->chunks[world->chunkp].y = chunky;

    unsigned char i = 0;
    while(i < 64) world->chunks[world->chunkp].blocks[i++] = 0;

    return ++world->chunkp;
}

void crpg::World::placeobj(World *world, unsigned char chunkid, unsigned char blockid, unsigned char x, unsigned char y){
    unsigned char xy = x * 8 + y;

    world->chunks[chunkid].blocks[xy] = blockid;
}