/*
 * Callbacks
 * Escrito por Cristobal Liendo <cristobal@liendo.net>
*/

#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <gtk/gtk.h>

gboolean image_press_callback(GtkWidget *event_box, GdkEventButton *event, gpointer data);
void destroy(GtkWidget *widget, gpointer data);
gboolean delete_event(GtkWidget *widget, GdkEvent *event, gpointer data);

void gen_callback(GtkWidget *menuitem, gpointer data);

#endif
