#include "turtle.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <cairo/cairo.h>
#include <gtk-3.0/gtk/gtk.h>
#include <assert.h>
#include <argp.h>
#include <float.h>
#include <math.h>
#include <stdbool.h>

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif



static char doc[] = "Turtle geometry";

static char args_doc[] = "";


static struct argp_option options[] = {
    {"out",      'o', "FILE",      0,  "output png file path" },
    {"width",    'w', "WIDTH",     0,  "window/image width" },
    {"height",   'h', "HEIGHT",    0,  "window/image height" },
    {"speed",    's', "factor",    0,  "make turle slower/faster" },
    { 0 }
};

typedef struct {
    int width, height;
    char *outfile;
	float speed;
} arguments;


static error_t parse_opt(int key, char *arg, struct argp_state *state) {
	errno = 0;
    arguments *args = state->input;
    
    switch (key) {
        case 'w': 
            args->width = atoi(arg);
            break;
        case 'h':
            args->height = atoi(arg);
            break;
        case 'o':
            args->outfile = arg;
            break;
        case 's':
            args->speed = atof(arg);
            break;
        default:
            return ARGP_ERR_UNKNOWN;
        }
    return 0;
}

static struct argp argp = { options, parse_opt, args_doc, doc };


static arguments args;


// - - - - - - 
// vec2.h
typedef struct {
    float x, y;
} vec2;
// - - - - - - 




// - - - - - - 
// path.h
typedef struct {
    vec2 from;
    vec2 to;
	int draw;
} line; 


typedef struct {
    line *lines;
    unsigned int num_lines;
    unsigned int line_capacity;
} path;


path* path_new(unsigned int initial_line_capacity);
void path_destroy(path *p);

line* path_append(path *p);
// - - - - - - 




// - - - - - - 
// path.c

path* path_new(unsigned int initial_line_capacity) {
    path *p = malloc(sizeof(path));
    p->line_capacity = initial_line_capacity;
    p->lines = malloc(sizeof(line) * initial_line_capacity);
    p->num_lines = 0;
    return p;
};

void path_destroy(path *p) {
    free(p->lines);
    free(p);
}

static int path_get_increment_line_capacity(path *p) {
    return p->line_capacity * 2 + 2;
}

line* path_append(path *p) {
    if (p->num_lines + 1 > p->line_capacity) {
        line *tmp = p->lines;
        p->line_capacity =  path_get_increment_line_capacity(p);
        p->lines = malloc(sizeof(line) * p->line_capacity);
        memcpy(p->lines, tmp, sizeof(line) * p->num_lines);
        free(tmp);
    }
	p->lines[p->num_lines].draw = 1;
    return &p->lines[p->num_lines++];
}
// - - - - - - 




// - - - - - - 
// turtle.h
typedef struct {
    vec2 position;
	float orientation;
    vec2 size;
    cairo_surface_t *sprite;
    float speed;
	bool pen_down;
} turtle;


turtle* turtle_new(const vec2 *position, const char *image_file_path);
void turtle_destroy(turtle *t);
vec2 turtle_center(const turtle *t);
void turtle_move(turtle *t, float length);
// - - - - - - 




// - - - - - - 
// turtle.c
vec2 turtle_center(const turtle *t) {
    vec2 center;
    center.x = t->position.x + t->size.x * 0.5f;
    center.y = t->position.y + t->size.y * 0.5f;
    return center;  
}

turtle* turtle_new(const vec2 *position, const char *image_file_path) {
    turtle *t = malloc(sizeof(turtle));
    
    t->speed = 30.f * args.speed;
    t->sprite = cairo_image_surface_create_from_png(image_file_path);
    t->size.x = cairo_image_surface_get_width(t->sprite);
    t->size.y = cairo_image_surface_get_height(t->sprite);

    t->position.x = position->x - t->size.x * 0.5f; 
    t->position.y = position->y - t->size.y * 0.5f;
    
	t->orientation = 0;
	t->pen_down = true;
    return t;
}

void turtle_destroy(turtle *t) {
    cairo_surface_destroy(t->sprite);
    free(t);
}


void turtle_move(turtle *t, float length) {
    vec2 new_position;
    new_position.x = t->position.x + length * cosf(t->orientation);
    new_position.y = t->position.y + length * sinf(t->orientation);
    t->position = new_position;
}
// - - - - - - 



// - - - - - - 
// turtle-command.h
typedef struct {
    void (*callback)(turtle*,float,float);
    float length_after;
	float arg1, arg2;
} turtle_command;

typedef struct turtle_command_item turtle_command_item;
struct turtle_command_item {
    turtle_command command;
    turtle_command_item *next;
};

typedef struct {
    turtle_command_item *head;
} turtle_command_queue;

turtle_command_queue* turtle_command_queue_new();
void turtle_command_queue_destroy(turtle_command_queue *queue);
turtle_command* turtle_command_queue_append(turtle_command_queue *queue);
turtle_command* turtle_command_queue_front(const turtle_command_queue *queue);
void turtle_command_queue_pop_front(turtle_command_queue *queue);
// - - - - - - 


static turtle_command_queue *command_queue = NULL;


// - - - - - - 
// turtle-command.c
turtle_command_queue* turtle_command_queue_new() {
    turtle_command_queue *queue = malloc(sizeof(turtle_command_queue));
    queue->head = NULL;
    return queue;
}

void turtle_command_queue_destroy(turtle_command_queue *queue) {
    turtle_command_item *current = queue->head;
    while(current != NULL) {
        turtle_command_item *tmp = current->next;
        free(current);
        current = tmp;
    }
    free(queue);
}

turtle_command* turtle_command_queue_append(turtle_command_queue *queue) {
    turtle_command_item *command_item = malloc(sizeof(turtle_command_item));
    command_item->next = NULL;
	command_item->command.length_after = 0;

    if (queue->head == NULL)
        queue->head = command_item;
    else {
        turtle_command_item *current = queue->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = command_item;
    }
    return &command_item->command;
}

turtle_command* turtle_command_queue_front(const turtle_command_queue *queue) {
    if (queue->head == NULL) {
        return NULL;
    }
    return &queue->head->command;
}

void turtle_command_queue_pop_front(turtle_command_queue *queue) {
    assert(queue->head != NULL);
    turtle_command_item *tmp = queue->head;
    queue->head = tmp->next;
    free(tmp);
} 
// - - - - - - 




// - - - - - - 
// turtle-gtk.c
static void draw_turtle_path(cairo_t *cr, turtle *t, turtle_command_queue *commands) {
    cairo_save(cr);
    cairo_set_source_rgb(cr, 255, 255, 255);
    cairo_paint(cr);
    cairo_restore(cr); 

    cairo_set_source_rgb(cr, 0, 0, 0);
    
    turtle_command *command = turtle_command_queue_front(commands);
    while(command != NULL) {
        vec2 turtle_c = turtle_center(t);
        cairo_move_to(cr, turtle_c.x, turtle_c.y);

        command->callback(t, command->arg1, command->arg2);
        turtle_move(t, command->length_after);
        if (command->length_after > 0 && t->pen_down) {
            turtle_c = turtle_center(t);
            cairo_line_to(cr, turtle_c.x, turtle_c.y);
            cairo_stroke(cr);
            
        }
        turtle_command_queue_pop_front(commands);
        command = turtle_command_queue_front(commands);
    }
}

static void turtle_rot(turtle *t, float degree, float) {
	static const float pi = M_PI;
	static const float twopi = 2.0f*M_PI;
	float rad = degree/180.f*pi;
	t->orientation += rad;
	if (t->orientation < 0)
		t->orientation += twopi;
	if (t->orientation >= twopi)
		t->orientation -= twopi;
}

static void turtle_pos_x(turtle *t,float, float) {
	t->orientation = 0;
}


static void turtle_pos_y(turtle *t,float, float) {
	t->orientation = 0;
	turtle_rot(t, 90, 0);
}

static void turtle_init(turtle *t,float, float) {
	t->orientation = 0;
	t->position.x = 0;
	t->position.y = 0;
}

static void turtle_neg_x(turtle *t,float, float) {
	t->orientation = 0;
	turtle_rot(t, 180, 0);

}

static void turtle_neg_y(turtle *t,float, float) {
	t->orientation = 0;
	turtle_rot(t, -90, 0);
}

static void turtle_pen_up(turtle *t, float, float) {
	t->pen_down = false;
}

static void turtle_pen_down(turtle *t, float, float) {
	t->pen_down = true;
}


void face_up() {
	turtle_command *command = turtle_command_queue_append(command_queue);
	command->callback = turtle_neg_y;
	command->length_after = 0;
}

void turn_left() {
	turtle_command *command = turtle_command_queue_append(command_queue);
	command->callback = turtle_rot;
	command->length_after = 0;
	command->arg1 = -90;
}

void rotate(float degrees) {
	turtle_command *command = turtle_command_queue_append(command_queue);
	command->callback = turtle_rot;
	command->length_after = 0;
	command->arg1 = degrees;
}

void forward(float time) {
	turtle_command *command = turtle_command_queue_append(command_queue);
	command->callback = turtle_rot;
	command->arg1 = 0;
	command->length_after = time;
}

void pen_up() {
	turtle_command *command = turtle_command_queue_append(command_queue);
	command->callback = turtle_pen_up;
	command->length_after = 0;
}

void pen_down() {
	turtle_command *command = turtle_command_queue_append(command_queue);
	command->callback = turtle_pen_down;
	command->length_after = 0;
}

extern void run(void);

// void init_turtle_path(turtle_command_queue *queue) {
// 
//     // INSERT COMMANDS HERE
//     turtle_command *command;
//     
//     command = turtle_command_queue_append(queue);
//     command->callback = turtle_init;
//     command->length_after = 0;
// 
//     for (int i = 0; i < 5; ++i) {
//         command = turtle_command_queue_append(queue);
//         command->callback = turtle_pos_y;
//         command->length_after = 10;
// 
//         command = turtle_command_queue_append(queue);
//         command->callback = turtle_pos_x;
//         command->length_after = 10;
//     }
// 
// 	for (int i = 0; i < 40; ++i) {
// 		command = turtle_command_queue_append(queue);
// 		command->callback = turtle_rot;
// 		command->length_after = 10;
// 		command->arg1 = 9;
// 	}
// }


typedef struct {
    turtle *t;
    const arguments *args;
    turtle_command_queue *command_queue;
    path *turtle_path;
} application_user_data;



gint64 prev_time = 0;
turtle_command *current_command = NULL;
line *current_line_segment = NULL;

gboolean update(GtkWidget *widget, GdkFrameClock *clock, gpointer user_data) {
    const application_user_data *app_data = (application_user_data*) user_data;
    
    gint64 current_time = g_get_monotonic_time();
    if (prev_time == 0) {
        prev_time = current_time;
        return G_SOURCE_CONTINUE;
    }
    
    const gint64 dt = current_time - prev_time;
    prev_time = current_time;

    const float dt_seconds = dt / 1000000.f;

    if (!current_command) {
        current_command = turtle_command_queue_front(app_data->command_queue);
        if (current_command != NULL) {
            //printf("%f %f \n", app_data->t->position.x, app_data->t->position.y);
            current_command->callback(app_data->t, current_command->arg1, current_command->arg2);
            current_line_segment = path_append(app_data->turtle_path);
            current_line_segment->from = turtle_center(app_data->t);
			current_line_segment->draw = app_data->t->pen_down;
        }
    }
    else if (current_command->length_after <= 0) {
        turtle_command_queue_pop_front(app_data->command_queue);
        current_command = turtle_command_queue_front(app_data->command_queue);
        current_line_segment->to = turtle_center(app_data->t);
        current_line_segment = NULL;
        if (current_command != NULL) {
            //printf("%f %f \n", app_data->t->position.x, app_data->t->position.y);
            current_command->callback(app_data->t, current_command->arg1, current_command->arg2);
            current_line_segment = path_append(app_data->turtle_path);
            current_line_segment->from = turtle_center(app_data->t);
			current_line_segment->draw = app_data->t->pen_down;
        }
    } 

    if (current_command != NULL) {
        const float effective_length = fmin(dt_seconds * app_data->t->speed, current_command->length_after);

        assert(effective_length <= current_command->length_after);
        current_command->length_after -= effective_length;    
        turtle_move(app_data->t, effective_length);
        current_line_segment->to = turtle_center(app_data->t);
    }
    gtk_widget_queue_draw(widget);
    return G_SOURCE_CONTINUE;
}

static void draw(GtkWidget *drawing_area, cairo_t *cr, gpointer user_data) {
    const application_user_data *app_data = (application_user_data*) user_data;
    
    const vec2 turtle_c = turtle_center(app_data->t);


    // Draw turtle
    cairo_matrix_t transformation_matrix;
    cairo_matrix_init_identity(&transformation_matrix);
        
	vec2 turtle_dir;
	turtle_dir.x = cosf(app_data->t->orientation);
	turtle_dir.y = sinf(app_data->t->orientation);
    if (turtle_dir.x > 0) {
        cairo_matrix_translate(&transformation_matrix, app_data->t->position.x * 2 + app_data->t->size.x, 0); 
        transformation_matrix.xx = -1;
        double x = app_data->t->position.x;
        double y =  app_data->t->position.y;
        cairo_matrix_transform_point(&transformation_matrix, &x, &y);
    }


    cairo_set_matrix(cr, &transformation_matrix);
    
    cairo_set_source_surface(cr, app_data->t->sprite, app_data->t->position.x, app_data->t->position.y);
    cairo_paint(cr);

    cairo_matrix_init_identity(&transformation_matrix);
    cairo_set_matrix(cr, &transformation_matrix);
    cairo_set_source_rgb(cr, 0, 0, 0);
    for (int line_index = 0; line_index < app_data->turtle_path->num_lines; ++line_index) {
        const line *current_line = app_data->turtle_path->lines + line_index;
        cairo_move_to(cr, current_line->from.x, current_line->from.y);
        if (current_line == current_line_segment) { 
			if (app_data->t->pen_down) {
				cairo_line_to(cr, turtle_c.x, turtle_c.y);
				cairo_stroke(cr);
			}
        }
        else 
			if (current_line->draw) {
				cairo_line_to(cr, current_line->to.x, current_line->to.y);
				cairo_stroke(cr);
			}
    }
}

static gboolean keyhandler(GtkWidget *widget, GdkEventKey *key, gpointer user_data) {
	if (key->keyval == GDK_KEY_Escape) {
		gtk_window_close(GTK_WINDOW(user_data));
		return TRUE;
	}
	return FALSE;
}

static void activate(GtkWidget *widget, gpointer user_data) {
    application_user_data *app_data = (application_user_data*) user_data;
    GtkWidget *window = gtk_application_window_new(GTK_APPLICATION(widget));
    
    gtk_window_set_title(GTK_WINDOW(window), "Turtle runner");
    gtk_window_set_default_size(GTK_WINDOW(window), app_data->args->width, app_data->args->height);
	g_signal_connect(window, "key_press_event", G_CALLBACK(keyhandler), window);
    
    GtkWidget *drawing_area = gtk_drawing_area_new();
    gtk_widget_set_name(drawing_area, "drawing-area");
    gtk_widget_add_events(window, GDK_KEY_PRESS_MASK);
    g_signal_connect(drawing_area, "draw", G_CALLBACK(draw), app_data); 
    gtk_widget_add_tick_callback(drawing_area, update,  app_data, NULL);

    gtk_container_add(GTK_CONTAINER(window), drawing_area);
    gtk_widget_show_all(window);
}

int main(int argc, char **argv) {
    args.width = 800;
    args.height = 600;
    args.outfile = NULL;
	args.speed = 1;

    argp_parse(&argp, argc, argv, 0, 0, &args);
    
    vec2 turtle_start;
    turtle_start.x = args.width * 0.5f;
    turtle_start.y = args.height * 0.5f;
    
    turtle *t = turtle_new(&turtle_start, "turtle.png");
    command_queue = turtle_command_queue_new();
    path *turtle_path = path_new(100);

    run();

    if (args.outfile != NULL) {
        cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, args.width, args.height);
        cairo_t *cr = cairo_create(surface);
        draw_turtle_path(cr, t, command_queue);
        cairo_surface_write_to_png(surface, args.outfile);
    }
    else {
        application_user_data user_data = {.t = t, .args = &args, .command_queue = command_queue, .turtle_path = turtle_path};
        GtkApplication *app = gtk_application_new("org.gtk.example", 0); // 0 should be G_APPLICATION_DEFAULT_FLAGS...
        g_signal_connect(app, "activate", G_CALLBACK(activate), &user_data);
		int gtk_argc = 1;
		char *gtk_argv[] = { argv[0], NULL };
        int status = g_application_run(G_APPLICATION(app), gtk_argc, gtk_argv);
        g_object_unref(app);
    }
    turtle_destroy(t);
    turtle_command_queue_destroy(command_queue);
    path_destroy(turtle_path);
    return 0;
}
// - - - - - - 
