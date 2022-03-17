#include "inc/cworld.hpp"

void cworld::Render::render(cworld::World::World *world){
    system("stty cooked");
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
                printf("Player X: %d", world->player.y);
                break;
            case 2:
                printf("Player Y: %d", world->player.x);
                break;
            case 3:
                printf("Current Chunk: %d", world->player.c);
                break;
            case 4:
                printf("Chunk Y: %d", world->chunks[i].y);
                break;
            case 5:
                printf("TPS: %lld", cworld::World::Tick::get_tps());
                break;
            case 6:
                printf("Test: %d", cworld::Protocol::Keyboard::get_key_pressed());
                break;
            case 9:
                i3 = 0;
                break;
            }
            i3++;

            printf("\n");
            i2 = 0;
        }
        char rc;
        char col[16];

        switch(world->chunks[world->player.c].blocks[i++]){
            case 0: {
                rc = '#'; 
                strcpy(col, "\033[0;34m");
                break;
            }
            case 1: {
                rc = '='; 
                strcpy(col, "\033[0;32m");
                break;
            }
            case 2: {
                rc = '%';
                strcpy(col, "\033[0;31m");
                break;
            }
            case 3: {
                rc = '0';
                strcpy(col, "\033[0;30m");
                break;
            }
            case 4: {
                rc = 'j';
                strcpy(col, "\033[0;37m");
                break;
            }
            case 255: {
                rc = '*';
                strcpy(col, "\033[1;31m");
                break;
            }
            default: {
                rc = '?'; 
                strcpy(col, "\033[1;31m");
                break;
            }
        }

        if((i - 1) == playerxy) {
            rc = '@';
            strcpy(col, "\033[0;33m");
        }

        #ifdef DEBUG
            printf("%x ", world->chunks[world->player.c].blocks[i - 1]);
        #endif
        #ifndef DEBUG
            printf("%s%c\033[0m ", col, rc);
        #endif

        i2++;
    }

    printf("\n");

    #ifdef DEBUG
        printf("DEBUG MODE\n");
    #endif
    system("stty raw");
}
