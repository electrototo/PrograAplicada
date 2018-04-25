#include <gtk/gtk.h>

static void destroy(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}

static gboolean delete_event(GtkWidget *widget, GdkEvent *event, gpointer data) {
    g_print("delete\n");

    destroy(widget, data);

    return FALSE;
}

int main(int argc, char **argv) {
    GtkWidget *window, *image;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "delete-event", G_CALLBACK(delete_event), NULL);

    image = gtk_image_new_from_file("/home/ic17eli/Downloads/isabel.jpg");

    gtk_container_set_border_width(GTK_CONTAINER(window), 100);
    gtk_container_add(GTK_CONTAINER(window), image);

    gtk_widget_show(image);
    gtk_widget_show(window);

    gtk_main();

    return 0;
}
