#include "./inc/cworld.hpp"

int key_pressed;

void cworld::Protocol::save(cworld::World::World *world, const char *filename){
    FILE* savedata = fopen(filename, "wb");
    while(fwrite(world, sizeof(struct cworld::World::World), 1, savedata) != 1);
    //fwrite(&world, sizeof(struct cworld::World::World), 1, savedata);
    fclose(savedata);
}
cworld::World::World cworld::Protocol::load(const char *filename){
    cworld::World::World w;
    FILE* savedata = fopen(filename, "r");
    if(savedata == NULL) cworld::Protocol::Exceptions::make(11);
    while(fread(&w, sizeof(struct cworld::World::World), 1, savedata));
    fclose(savedata);
    return w;
}
const char *cworld::Protocol::Exceptions::get_ex(int signum){
    switch(signum) {
        case 22: return "Aborted";
        case 11: return "Invalid access to storage";
        case 6:  return "Abnormal termination";
        default: return "Unknown error";
    }
}
void cworld::Protocol::Exceptions::make(int signum){
    printf("-----------------------\n");
    printf("Application operation got failed! Here is some info about that:\n");
    printf("- What caused this error: %s\n", cworld::Protocol::Exceptions::get_ex(signum));
    printf("- Signal Number         : %d\n", signum);
    printf("-----------------------\nSavefile will not be saved!\n");
    exit(1);
}
void cworld::Protocol::Keyboard::run(cworld::World::World *w){
    system("stty raw");
    while(1){
        key_pressed = getchar();
        if(key_pressed == 3) {
            system("stty cooked");
            ao_shutdown();
            exit(0);
        }
        switch(key_pressed){
            case 119: {
                if(w->player.x == 7) {
                    w->player.c++;
                    w->player.x = 0;
                    cworld::World::genc(w->player.cy, w);
                } else {
                    w->player.x++;
                }
                break;
            }
            case 97: {
                if(w->player.x == 0) {
                    w->player.c++;
                    w->player.cy--;
                    w->player.y = 7;
                    cworld::World::genc(w->player.cy, w);
                } else {
                    w->player.y--;
                }
                break;
            }
            case 115: {
                if(w->player.x == 0) {
                    w->player.c++;
                    w->player.x = 7;
                    cworld::World::genc(w->player.cy, w);
                } else {
                    w->player.x--;
                }
                break;
            }
            case 100: {
                if(w->player.y == 7) {
                    w->player.c++;
                    w->player.cy++;
                    w->player.y = 0;
                    cworld::World::genc(w->player.cy, w);
                } else {
                    w->player.y++;
                }
                break;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
int cworld::Protocol::Keyboard::get_key_pressed(){
    return key_pressed;
}
ao_device *cworld::Protocol::play(sound_t sound) {
    
}