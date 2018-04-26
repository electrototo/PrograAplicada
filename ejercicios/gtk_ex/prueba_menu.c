/*
 * autor: cristobal liendo i
 * fecha: Tue 24 Apr 2018 04:08:03 PM CDT
 * descripcion: 
*/

#include <gtk/gtk.h>

static void destroy(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}

static gboolean delete_event(GtkWidget *widget, GdkEvent *event, gpointer data) {
    destroy(widget, data);

    return FALSE;
}

int main(int argc, char **argv) {
    GtkWidget *window, *toolbar, *dialog, *menu_bar, *button;
    GtkToolItem *tool_item;

    GtkWidget *hbox, *vbox;

    GtkWidget *token, *white;


    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "delete-event", G_CALLBACK(delete_event), NULL);
    // gtk_container_set_border_width(GTK_CONTAINER(window), 0);

    vbox = gtk_vbox_new(FALSE, 0);
    hbox = gtk_hbox_new(TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, TRUE, TRUE, 0);

    toolbar = gtk_toolbar_new();

    tool_item = gtk_tool_button_new_from_stock(GTK_STOCK_SAVE);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), tool_item, -1);

    tool_item = gtk_tool_button_new_from_stock(GTK_STOCK_UNDO);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), tool_item, -1);

    tool_item = gtk_tool_button_new_from_stock(GTK_STOCK_REDO);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), tool_item, -1);

    tool_item = gtk_tool_button_new_from_stock(GTK_STOCK_INFO);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), tool_item, -1);


    gtk_container_add(GTK_CONTAINER(hbox), toolbar);
    gtk_widget_show(toolbar);
    
    for (int y = 0; y < 20; y++) {
        hbox = gtk_hbox_new(TRUE, 0);
        gtk_box_pack_start(GTK_BOX(vbox), hbox, TRUE, TRUE, 0);

        for (int x = 0; x < 20; x++) {
            // button = gtk_button_new_with_label("O");
            if (x % 2 == 0)
                token = gtk_image_new_from_file("imagenes/red_token.jpg");
            else
                token = gtk_image_new_from_file("imagenes/blue_token.jpg");

            gtk_container_add(GTK_CONTAINER(hbox), token);
            gtk_widget_show(token);
        }
    }

    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}

