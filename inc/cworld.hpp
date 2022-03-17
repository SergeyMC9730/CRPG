#pragma once

//#define DEBUG

#include <iostream>
#include <csignal>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <chrono>
#include <time.h>

#define _XOPEN_SOURCE 700

#ifndef _WIN32
#include <termios.h>
#include <thread>
#else
#include "../mingw-std-threads/mingw.thread.h"
#endif

#include <ao/ao.h>

#pragma pack(push, 1)
namespace cworld {
    namespace World {
        namespace Blocks {
            constexpr unsigned char player = '@';
            constexpr unsigned char air = '#';
        }
        struct Enitity {
            unsigned char id = 0;
            unsigned char x = 0;
            unsigned char y = 0;
            bool iscreated = false;
        };
        struct LinkedChunk {
            unsigned char chunkid = 0;
            unsigned char chunky = 0;
            bool iscreated = false;
        };
        struct Chunk {
            unsigned char blocks[64];
            Enitity mobs[64];
            unsigned char y = 0;
            bool is_used = false;
            LinkedChunk linked[64];
        };
        struct Player {
            unsigned char x  = 0;
            unsigned char y  = 0;
            unsigned char c  = 0;
            unsigned char hp = 10;
            char cy = 0;
        };
        struct Seed {
            uintptr_t seed;
        };
        struct World {
            Seed seed;
            unsigned char chunkp = 0;
            Chunk chunks[256];
            Player player;
            char filename[64];
        };

        namespace Tick {
            void set_tps(uint64_t tps);
            uint64_t get_tps();
            uint64_t get();
            bool is_tick_done();
            void run(cworld::World::World *world);
        };
        namespace PlayerObject {
            void move(cworld::World::World *world, uint8_t x, uint8_t y);
            void jump(cworld::World::World *world);

            bool isMoving();
            bool isJumping();
            bool isFalling();
        };
        namespace EntityObject {
            void move(cworld::World::Enitity *entity, uint8_t x, uint8_t y);
            void create(cworld::World::World *world, uint8_t x, uint8_t y, uint8_t id, uint8_t chunkid);

            bool isMoving();
            bool isFalling();
        };
        namespace Physics {
            void run(World *world);
            void update(Chunk *chunk, bool early, World *world);
        };

        void init(World *world);
        unsigned char genc(char chunky, World *world);
        void placeobj(World *world, unsigned char chunkid, unsigned char blockid, unsigned char x, unsigned char y);
    };
    namespace Main {
        namespace Threads {
            extern std::thread *keyboard_thread;
            extern std::thread *tick_thread;
            extern std::thread *physics_thread;
        }
        int main();
    };
    namespace Protocol {
        //bits, rate and channels are 32, 44100 and 2 by default
        typedef struct {
            const char *filename;
            char *buffer;
            uint32_t size;

            uint8_t bits = 32;
            uint16_t rate = 44100;
            uint8_t channels = 2;

            ao_device *device;
        } sound_t;

        ao_device *play(sound_t sound);

        void save(cworld::World::World *world, const char *filename);
        cworld::World::World load(const char *filename);
        //cworld::World::World *load(const char *filename);

        namespace Exceptions {
            const char *get_ex(int signum);
            void make(int signum);
        }

        namespace Keyboard {
            namespace Keys {
                constexpr int up = 72;
                constexpr int down = 80;
                constexpr int left = 75;
                constexpr int right = 77;
            }
            int get_key_pressed();
            void run(cworld::World::World *w);
        }
    }
    namespace Render {
        void render(cworld::World::World *world);
    }
};
#pragma pack(pop)