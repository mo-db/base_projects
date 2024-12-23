#ifndef GUI_H
#define GUI_H

#include "../base/include/libbase.h"
#include "objects.h"
#include "video.h"
#include <stdint.h>

struct Gui_Element *new_gui_element();

void imgui_begin();
void imgui_end();
int imgui_button(int x, int y, int id, struct scaled_surface *s_surf);
void print_ginf();


#endif
