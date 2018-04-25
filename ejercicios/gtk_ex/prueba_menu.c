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

    GtkWidget *h_box, *v_box;

    GtkWidget *token, *white;


    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "delete-event", G_CALLBACK(delete_event), NULL);
    gtk_container_set_border_width(GTK_CONTAINER(window), 100);

    // dialog = gtk_file_chooser_dialog_new("Open file", NULL, GTK_FILE_CHOOSER_ACTION_OPEN, NULL, GTK_RESPONSE_ACCEPT, NULL);
    
    //menu_bar = gtk_menu_bar_new();
    //gtk_container_add(GTK_CONTAINER(window), menu_bar);

    //toolbar = gtk_toolbar_new();
    //tool_item = gtk_tool_button_new_from_stock(GTK_STOCK_SAVE);
    // gtk_toolbar_insert(GTK_TOOLBAR(toolbar), tool_item, 0);
    //
    v_box = gtk_vbox_new(FALSE, 0);
    
    for (int y = 0; y < 20; y++) {
        h_box = gtk_hbox_new(TRUE, 0);
        gtk_box_pack_start(GTK_BOX(v_box), h_box, TRUE, TRUE, 0);

        for (int x = 0; x < 20; x++) {
            // button = gtk_button_new_with_label("O");
            if (x % 2 == 0)
                token = gtk_image_new_from_file("imagenes/red_token.jpg");
            else
                token = gtk_image_new_from_file("imagenes/blue_token.jpg");

            gtk_container_add(GTK_CONTAINER(h_box), token);
            gtk_widget_show(token);
        }
    }

    gtk_container_add(GTK_CONTAINER(window), v_box);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}

