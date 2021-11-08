#pragma once

//#define DEBUG

#include <cstdio>
#include <csignal>
#include <cstdlib>
#include <cstring>
#include <exception>

#pragma pack(push, 1)
namespace cworld {
    namespace World {
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
        };
        struct World {
            unsigned char chunkp = 0;
            Chunk chunks[256];
            Player player;
        };
        unsigned char genc(unsigned char chunky, World *world);
        void placeobj(World *world, unsigned char chunkid, unsigned char blockid, unsigned char x, unsigned char y);
    };
    namespace Main {
        int main();
    };
    namespace Protocol {
        bool h(int istrue);
        void save(cworld::World::World *world, const char *filename);
        cworld::World::World *load(const char *filename);

        namespace Exceptions {
            const char *get_ex(int signum);
            void make(int signum);
        }
    }
    namespace Render {
        void render(cworld::World::World *world);
    }
};
#pragma pack(pop)