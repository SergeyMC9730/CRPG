#include "inc/cworld.hpp"

void cworld::Render::render(cworld::World::World *world){
    printf("\033[2J\033[1;1H");

    unsigned char playerxy = world->player.x * 8 + world->player.y;

    unsigned char i  = 0;
    unsigned char i2 = 0;
    unsigned char i3 = 0;
    while(i < 64){
        if(i2 == 8){
            switch(i3){
            case 0:
                printf("HP: %d", world->player.hp);
                break;
            case 1:
                printf("Player X: %d", world->player.x);
                break;
            case 2:
                printf("Player Y: %d", world->player.y);
                break;
            case 3:
                printf("Current Chunk: %d", world->player.c);
                break;
            case 4:
                printf("Chunk Y: %d", world->chunks[i].y);
                break;
            case 8:
                i3 = 0;
                break;
            }
            i3++;

            printf("\n");
            i2 = 0;
        }
        char rc;

        switch(world->chunks[world->player.c].blocks[i++]){
            case 0:   rc = '#'; break;
            case 255: rc = '*'; break;
            default: rc = '?'; break;
        }

        if((i - 1) == playerxy) rc = '@';

        #ifdef DEBUG
            printf("%x ", world->chunks[world->player.c].blocks[i - 1]);
        #endif
        #ifndef DEBUG
            printf("%c ", rc);
        #endif

        i2++;
    }

    printf("\n");

    #ifdef DEBUG
        printf("DEBUG MODE\n");
    #endif
}
