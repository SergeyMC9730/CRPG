#include "./inc/cworld.hpp"

bool cworld::Protocol::h(int istrue){
    return (istrue == 1 ? true : false);
}
void cworld::Protocol::save(cworld::World::World *world, const char *filename){
    FILE* savedata = fopen(filename, "wb");
    fwrite(&world, sizeof(struct cworld::World::World), 1, savedata);
    fclose(savedata);
}
const char *cworld::Protocol::Exceptions::get_ex(int signum){
    switch(signum) {
        case 11: return "Invalid access to storage";
        case 6:  return "Abnormal termination";
        default: return "Unknown error";
    }
}
void cworld::Protocol::Exceptions::make(int signum){
    printf("-----------------------\n");
    printf("Application operation got failed! Here is some info about that:\n");
    printf("- What caused the error: %s\n", cworld::Protocol::Exceptions::get_ex(11));
    printf("- Signal Number        : %d\n", signum);
    printf("-----------------------\nSavefile will not be saved!\n");
    while(1);
}