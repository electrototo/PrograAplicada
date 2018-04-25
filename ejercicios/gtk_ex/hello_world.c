/*
 * autor: cristobal liendo i
 * fecha: Tue 20 Mar 2018 07:21:13 PM CST
 * descripcion: 
*/

#include <gtk/gtk.h>

static void hello(GtkWidget *widget, gpointer data) {
    g_print("Hello world\n");
}

static void destroy(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}

static gboolean delete_event(GtkWidget *widget, GdkEvent *event, gpointer data) {
    g_print("delete event\n");

    destroy(widget, data);

    return FALSE;
}

int main(int argc, char **argv) {
    GtkWidget *window;
    GtkWidget *button;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "delete-event", G_CALLBACK(delete_event), NULL);

    gtk_container_set_border_width(GTK_CONTAINER(window), 100);
    button = gtk_button_new_with_label("Hello world\n");

    g_signal_connect(button, "clicked", G_CALLBACK(hello), NULL);
    gtk_container_add(GTK_CONTAINER(window), button);

    gtk_widget_show(button);
    gtk_widget_show(window);

    gtk_main();

    return 0;
}

