/*
 *  autor: cirstobal liendo <cristobal@liendo.net> 
 *  fecha: Sun 06 May 2018 10:18:36 AM CDT
 *  descripcion: archivo que contiene los menus
*/

#include <gtk/gtk.h>

#include "callbacks.h"
#include "menus.h"
#include "pente_types.h"

GtkWidget *create_menubar() {
    GtkWidget *menu_bar;

    GtkWidget *file_item, *edit_item, *help_item;

    menu_item_dt file_options[7] = {
        {"Open File", gen_callback, NULL},
        {"New Game", gen_callback, NULL},
        {"~~~", NULL, NULL},
        {"Save", gen_callback, NULL},
        {"Save as...", gen_callback, NULL},
        {"~~~", NULL, NULL},
        {"Quit", gen_callback, NULL}
    };

    menu_item_dt edit_options[2] = {
        {"Undo", gen_callback, NULL},
        {"Redo", gen_callback, NULL}
    };

    menu_item_dt help_options[2] = {
        {"Pente Tutorial", gen_callback, NULL},
        {"About Us", gen_callback, NULL},
    };

    menu_bar = gtk_menu_bar_new();

    file_item = gtk_menu_item_new_with_label("File");
    edit_item = gtk_menu_item_new_with_label("Edit");
    help_item = gtk_menu_item_new_with_label("Help");

    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), file_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), edit_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), help_item);

    create_menu_from_array(file_item, file_options, 7);
    create_menu_from_array(edit_item, edit_options, 2);
    create_menu_from_array(help_item, help_options, 2);

    return menu_bar;
}

GtkWidget *create_menu_item(GtkWidget *parent, menu_item_dt info) {
    GtkWidget *item;
    
    if (info.callback != NULL) {
        item = gtk_menu_item_new_with_label(info.label);
        g_signal_connect(item, "activate", G_CALLBACK(info.callback), info.data);
    }
    else
        item = gtk_separator_menu_item_new();

    gtk_menu_shell_append(GTK_MENU_SHELL(parent), item);

    return item;
}

void create_menu_from_array(GtkWidget *parent_item, menu_item_dt *items, int size) {
    GtkWidget *menu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(parent_item), menu);

    for (int i = 0; i < size; i++)
        create_menu_item(menu, items[i]);
}
