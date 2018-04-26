/*
 * autor: cristobal liendo i, estibaliz cano l, isabel leon, s.
 * fecha: Tue 24 Apr 2018 04:08:03 PM CDT
 * descripcion: 
*/

#include <gtk/gtk.h>

GtkWidget *create_label(char *str);

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

    // menubar
    GtkWidget *file_item, *edit_item, *help_item;
    // end menubar

    // tablero principal
    GtkWidget *main_container, *sidebar_menu, *pente_container;
    GtkWidget *players, *turn, *comidas;
    GtkWidget *label, *frame;
    // final tablero principal

    GtkWidget *token, *white;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "delete-event", G_CALLBACK(delete_event), NULL);

    vbox = gtk_vbox_new(FALSE, 0);
    hbox = gtk_hbox_new(TRUE, 0);
    // menubar
    menu_bar = gtk_menu_bar_new();

    file_item = gtk_menu_item_new_with_label("File");
    edit_item = gtk_menu_item_new_with_label("Edit");
    help_item = gtk_menu_item_new_with_label("Help");

    gtk_menu_append(GTK_MENU(menu_bar), file_item);
    gtk_menu_append(GTK_MENU(menu_bar), edit_item);
    gtk_menu_append(GTK_MENU(menu_bar), help_item);

    gtk_container_add(GTK_CONTAINER(vbox), menu_bar);
    //end menubar

    gtk_box_pack_start(GTK_BOX(vbox), hbox, TRUE, TRUE, 0);

    main_container = gtk_hbox_new(TRUE, 0);
    sidebar_menu = gtk_vbox_new(TRUE, 0);
    pente_container = gtk_vbox_new(TRUE, 0);

    players = gtk_vbox_new(TRUE, 0);
    turn = gtk_vbox_new(TRUE, 0);
    comidas = gtk_vbox_new(TRUE, 0);


    // Toolbar
    toolbar = gtk_toolbar_new();

    tool_item = gtk_tool_button_new_from_stock(GTK_STOCK_NEW);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), tool_item, -1);

    tool_item = gtk_tool_button_new_from_stock(GTK_STOCK_OPEN);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), tool_item, -1);

    tool_item = gtk_tool_button_new_from_stock(GTK_STOCK_SAVE);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), tool_item, -1);

    tool_item = gtk_tool_button_new_from_stock(GTK_STOCK_SAVE_AS);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), tool_item, -1);

    tool_item = gtk_tool_button_new_from_stock(GTK_STOCK_UNDO);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), tool_item, -1);

    tool_item = gtk_tool_button_new_from_stock(GTK_STOCK_REDO);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), tool_item, -1);

    tool_item = gtk_tool_button_new_from_stock(GTK_STOCK_INFO);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), tool_item, -1);

    gtk_container_add(GTK_CONTAINER(hbox), toolbar);
    gtk_widget_show(toolbar);
    // end toolbar
    
    // start pente board
    for (int y = 0; y < 20; y++) {
        hbox = gtk_hbox_new(TRUE, 0);
        gtk_box_pack_start(GTK_BOX(pente_container), hbox, TRUE, TRUE, 0);

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
    // end pente board

    gtk_box_pack_start(GTK_BOX(vbox), main_container, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(main_container), sidebar_menu, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(main_container), pente_container, TRUE, TRUE, 0);

    // informacion general
    frame = gtk_frame_new("Jugadores");
    gtk_container_add(GTK_CONTAINER(sidebar_menu), frame);
    gtk_container_add(GTK_CONTAINER(frame), players);
    gtk_container_add(GTK_CONTAINER(players), create_label("Jugador 1"));
    gtk_container_add(GTK_CONTAINER(players), create_label("Jugador 2"));

    frame = gtk_frame_new("Turno");
    gtk_container_add(GTK_CONTAINER(sidebar_menu), frame);
    gtk_container_add(GTK_CONTAINER(frame), turn);
    gtk_container_add(GTK_CONTAINER(turn), create_label("Jugador 1"));

    // gtk_container_add(GTK_CONTAINER(turn), create_label("Turno"));

    frame = gtk_frame_new("Comidas");
    gtk_container_add(GTK_CONTAINER(sidebar_menu), frame);
    gtk_container_add(GTK_CONTAINER(frame), comidas);
    gtk_container_add(GTK_CONTAINER(comidas), create_label("Jugador 1: "));
    gtk_container_add(GTK_CONTAINER(comidas), create_label("Jugador 2: "));

    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}

GtkWidget *create_label(char *str) {
    GtkWidget *label;

    label = gtk_label_new(str);
    gtk_misc_set_alignment(GTK_MISC(label), 0, 0);
    gtk_misc_set_padding(GTK_MISC(label), 50, 5);

    return label;
}
