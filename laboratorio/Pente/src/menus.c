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

GtkWidget *create_toolbar() {
    GtkWidget *toolbar;

    tool_item_dt toolbar_options[7] = {
        {"gtk-new", gen_callback, NULL},
        {"gtk-open", gen_callback, NULL},
        {"gtk-save", gen_callback, NULL},
        {"gtk-save-as", gen_callback, NULL},
        {"gtk-undo", gen_callback, NULL},
        {"gtk-redo", gen_callback, NULL},
        {"gtk-info", gen_callback, NULL},
    };

    toolbar = gtk_toolbar_new();

    for (int i = 0; i < 7; i++)
        create_toolbar_item(toolbar, toolbar_options[i]);

    return toolbar;
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

GtkToolItem *create_toolbar_item(GtkWidget *parent, tool_item_dt info) {
    GtkToolItem *tool_item;

    tool_item = gtk_tool_button_new_from_stock(info.stock_id);
    g_signal_connect(tool_item, "clicked", G_CALLBACK(info.callback), info.data);

    gtk_toolbar_insert(GTK_TOOLBAR(parent), tool_item, -1);

    return tool_item;
}

void create_menu_from_array(GtkWidget *parent_item, menu_item_dt *items, int size) {
    GtkWidget *menu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(parent_item), menu);

    for (int i = 0; i < size; i++)
        create_menu_item(menu, items[i]);
}
