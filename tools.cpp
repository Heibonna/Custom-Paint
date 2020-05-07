#include "tools.h"

tools::tools(mainWindow* w){
    this -> w = w;

    x0 = &(w->x0);
    x1 = &(w->x1);
    y0 = &(w->y0);
    y1 = &(w->y1);

    mode = &(w->mode);
}
