#include "../base/include/libbase.h"
#include "objects.h"
#include "video.h"
#include <stdint.h>

enum Gui_Element_Type {
	BUTTON,
	SLIDER,
	FIELD
};

struct Gui_Element {
	int w;
	int h;
};

struct Button {
	struct Gui_Element;
	uint8_t highlighted;
	uint8_t active;
};

struct Gui_Element *new_gui_element()
{
	return NULL;
}

