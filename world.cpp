#include "inc/cworld.hpp"

uint64_t ticks = 0;
bool istickdone = false;
uint64_t tps2 = 0;

void cworld::World::placeobj(World *world, unsigned char chunkid, unsigned char blockid, unsigned char x, unsigned char y){
    unsigned char xy = x * 8 + y;
    world->chunks[chunkid].blocks[xy] = blockid;
    cworld::Protocol::save(world, world->filename);

    return;
}
void cworld::World::Physics::update(cworld::World::Chunk *chunk, bool early, cworld::World::World *world){
    // if(chunk->blocks[(world->player.x * 8 + world->player.y)] == 0 && chunk->blocks[(world->player.x * 8 + (world->player.y - 1))] == 0) {
    //     //exit(0);
    //     while(chunk->blocks[(world->player.x * 8 + (world->player.y))] == 0) {
    //         world->player.y--;
    //     }
    // }
}
void cworld::World::Physics::run(cworld::World::World *world){
    update(&world->chunks[world->player.c], false, world);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}
unsigned char cworld::World::genc(char chunky, cworld::World::World *world){
    world->chunks[world->chunkp].is_used = true;
    world->chunks[world->chunkp].y = chunky;

    //unsigned char i = 0;

    switch(chunky){
        case 0: {
            uint8_t i = 0;
            while(i < 8) placeobj(world, world->chunkp, 1, 7, i++);

            i = 0;
            uint8_t tomerge[8];
            uint8_t tomerge2[8];
            while(i < 8) tomerge[i++] = (rand() % 64 % 2) == 1 ? 1 : 0;
            i = 0;
            while(i < 8) tomerge2[i++] = (rand() % 64 % 2) == 1 ? 1 : 0;

            //merge
            i = 0;
            while(i < 8) placeobj(world, world->chunkp, tomerge[i], 6, i++);
            i = 0;
            while(i < 8) placeobj(world, world->chunkp, tomerge2[i], 5, i++);

            placeobj(world, world->chunkp, 1, 7, 1);

            break;
        }
        case 1: {
            uint8_t i = 0;
            while(i < 64) world->chunks[world->chunkp].blocks[i++] = 0;
            break;
        }
        case -2: {
            uint8_t i = 0;
            double coal = 0.3;
            while(i < 64) world->chunks[world->chunkp].blocks[i++] = (rand() <= RAND_MAX * coal) ? 3 : 0;
            break;
        }
        case -1: {
            uint8_t i = 0;
            double coal = 0.05;
            while(i < 64) world->chunks[world->chunkp].blocks[i++] = (rand() <= RAND_MAX * coal) ? 3 : 0;
            break;
        }
        case -3: {
            uint8_t i = 0;
            double coal = 0.05;
            double iron = 0.01;
            while(i < 64) {
                if(rand() <= RAND_MAX * coal) {
                    world->chunks[world->chunkp].blocks[i++] = 3;
                } else if (rand() <= RAND_MAX * iron) {
                    world->chunks[world->chunkp].blocks[i++] = 4;
                } else {
                    world->chunks[world->chunkp].blocks[i++] = 0;
                }
            }
            break;
        }
        default: {
            uint8_t i = 0;
            while(i < 64) world->chunks[world->chunkp].blocks[i++] = 0;
            break;
        }
    }
    world->chunkp++;
    cworld::Protocol::save(world, world->filename);
    return world->chunkp;
}

void cworld::World::Tick::run(cworld::World::World *world){
    while(1){
        istickdone = false;
        cworld::Render::render(world);
        cworld::World::Physics::update(&world->chunks[world->player.c], false, world);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        ticks++;
        istickdone = true;
    }
}
uint64_t cworld::World::Tick::get(){
    return ticks;
}
bool cworld::World::Tick::is_tick_done(){
    return istickdone;
}
void cworld::World::Tick::set_tps(uint64_t tps){
    tps2 = tps;
    ticks = 0;
    return;
}
uint64_t cworld::World::Tick::get_tps(){
    return tps2;
}
void cworld::World::PlayerObject::move(cworld::World::World *world, uint8_t x, uint8_t y){
    world->player.x += x;
    world->player.y += y;
    return;
}
void cworld::World::EntityObject::move(cworld::World::Enitity *entity, uint8_t x, uint8_t y){
    entity->x += x;
    entity->y += y;
    return;
}
void cworld::World::EntityObject::create(cworld::World::World *world, uint8_t x, uint8_t y, uint8_t id, uint8_t chunkid){
    uint8_t i = 0;

    while(world->chunks[chunkid].mobs[i].iscreated){
        i++;
        if(i == 64) return;
    }

    world->chunks[chunkid].mobs[i].id = id;
    world->chunks[chunkid].mobs[i].x = x;
    world->chunks[chunkid].mobs[i].y = y;
    world->chunks[chunkid].mobs[i].iscreated = true;
}
void cworld::World::init(cworld::World::World *world){
    uint16_t i = 0;
    while(i < 256){
        uint8_t i2 = 0;
        while(i2 < 64){
            world->chunks[i].blocks[i2] = 0;
            i2++;
        }
        i++;
    }

    world->seed.seed = (unsigned int)abs(static_cast<int>(reinterpret_cast<uintptr_t>(&world->seed.seed) / 256));
    srand(world->seed.seed);
}