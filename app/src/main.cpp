#include "./Controllers/AppSupervisor.h"

int main () {
    AppSupervisor *app = new AppSupervisor(); 
    delete app; 
    return 0; 
}