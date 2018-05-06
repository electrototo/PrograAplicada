#ifndef MENUH
#define MENUH

#include <gtk/gtk.h>
#include "pente_types.h"

GtkWidget *create_menubar();
GtkWidget *create_menu_item();
void create_menu_from_array(GtkWidget *parent_item, menu_item_dt *items, int size);

#endif
