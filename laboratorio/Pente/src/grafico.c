/*
 * autor: cristobal liendo i, estibaliz cano l, isabel leon, s.
 * fecha: Tue 24 Apr 2018 04:08:03 PM CDT
 * descripcion: 
*/

#include <gtk/gtk.h>

#include "callbacks.h" 
#include "pente_types.h" 

GtkWidget *create_label(char *str);

int main(int argc, char **argv) {
    GtkWidget *window, *toolbar, *dialog, *menu_bar, *button;
    GtkToolItem *tool_item;

    GtkWidget *hbox, *vbox;

    // para las imagenes
    GtkWidget *event_box;
    image_data_t *img_data;

    // menubar
    GtkWidget *file_item, *edit_item, *help_item;
    GtkWidget *file_menu, *edit_menu, *help_menu;
    GtkWidget *open_item, *new_game_item, *save_item, *save_as_item, *quit_item;
    // end menubar

    // tablero principal
    GtkWidget *main_container, *sidebar_menu, *pente_container;
    GtkWidget *players, *turn, *comidas;
    GtkWidget *label, *frame;
    // final tablero principal

    GtkWidget *token, *white;

    // informacion general
    game_info_t game_data;
    game_data.turn = 1;
    game_data.player1_p = 0;
    game_data.player2_p = 0;
    game_data.ccount_1 = 0;
    game_data.ccount_2 = 0;


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

    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), file_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), edit_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), help_item);

    gtk_container_add(GTK_CONTAINER(vbox), menu_bar);
    //end menubar

    // file menu
    file_menu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_item), file_menu);

    open_item = gtk_menu_item_new_with_label("Open file");
    new_game_item = gtk_menu_item_new_with_label("New game");
    save_item = gtk_menu_item_new_with_label("Save");
    save_as_item = gtk_menu_item_new_with_label("Save as...");
    quit_item = gtk_menu_item_new_with_label("Quit");

    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), open_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), new_game_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), save_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), save_as_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), quit_item);

    // end file menu 

    // edit menu
    edit_menu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(edit_item), edit_menu);
    // end edit menu

    // help menu
    help_menu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(help_item), help_menu);
    // end help menu

    gtk_box_pack_start(GTK_BOX(vbox), hbox, TRUE, TRUE, 0);

    main_container = gtk_hbox_new(TRUE, 0);
    sidebar_menu = gtk_vbox_new(TRUE, 0);
    pente_container = gtk_vbox_new(TRUE, 0);

    players = gtk_vbox_new(TRUE, 0);
    turn = gtk_hbox_new(TRUE, 0);
    comidas = gtk_vbox_new(TRUE, 0);


    // Toolbar se puede hacer en un ciclo
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
            token = gtk_image_new_from_file("imagenes/white_token.jpg");

            img_data = (image_data_t *) g_malloc(sizeof(image_data_t));

            img_data->x = x;
            img_data->y = y;
            img_data->image = token;
            img_data->game_info = &game_data;

            event_box = gtk_event_box_new();
            gtk_container_add(GTK_CONTAINER(event_box), token);

            g_signal_connect(G_OBJECT(event_box), "button_press_event", G_CALLBACK(image_press_callback), img_data);

            gtk_container_add(GTK_CONTAINER(hbox), event_box);
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

    // imagen del jugador
    gtk_container_add(GTK_CONTAINER(turn), gtk_image_new_from_file("imagenes/white_token.jpg"));

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
    //gtk_misc_set_alignment(GTK_MISC(label), 0, 0);
    //gtk_misc_set_padding(GTK_MISC(label), 50, 5);

    return label;
}
