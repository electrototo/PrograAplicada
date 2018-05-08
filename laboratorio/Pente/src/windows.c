/*
 *  autor: cristobal liendo <cristobal@liendo.net>
 *  fecha: Mon 07 May 2018 09:03:04 PM CDT
 *  descripcion: se encuentra el codigo de todas las ventanas
*/

#include <gtk/gtk.h>

#include "callbacks.h"

GtkWidget *create_splash_screen() {
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget *vbox = gtk_vbox_new(TRUE, 0);

    GtkWidget *new_game_button, *resume_button;

    gtk_container_set_border_width(GTK_CONTAINER(window), 50);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_title(GTK_WINDOW(window), "Pente v1.0");

    new_game_button = gtk_button_new_with_label("NEW GAME");
    resume_button = gtk_button_new_with_label("RESUME PLAYING");

    g_signal_connect(new_game_button, "clicked", G_CALLBACK(new_game_callback) ,NULL);
    g_signal_connect(resume_button, "clicked", G_CALLBACK(resume_game_callback), NULL);

    gtk_widget_set_usize(new_game_button, 400, 70);

    g_signal_connect(GTK_WINDOW(window), "delete-event", G_CALLBACK(delete_event), NULL);

    gtk_box_pack_start(GTK_BOX(vbox), new_game_button, TRUE, TRUE, 10);
    gtk_box_pack_start(GTK_BOX(vbox), resume_button, TRUE, TRUE, 10);

    gtk_container_add(GTK_CONTAINER(window), vbox);

    return window;
}
