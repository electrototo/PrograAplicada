/*
 *  autores: cristobal liendo, estibaliz cano, isabel leon
 *  fecha: Sat 05 May 2018 09:15:54 PM CDT
 *  descripcion: callbacks para la interfaz grafica de pente
*/

#include <gtk/gtk.h>

#include "callbacks.h" 
#include "pente_types.h" 

gboolean image_press_callback(GtkWidget *event_box, GdkEventButton *event, gpointer data) {
    image_data_t *img_data = (image_data_t *) data;
    game_info_t *game_data = (game_info_t *) img_data->game_info;

    GdkPixbuf *new_image;

    printf("Click at: %d, %d\n", img_data->x, img_data->y);

    printf("Player 1 points: %d, Player 2 points: %d\n",
        game_data->player1_p, game_data->player2_p);

    if (game_data->turn == 1) {
        new_image = gdk_pixbuf_new_from_file("imagenes/blue_token.jpg", NULL);
        game_data->turn = 2;
    }
    else {
        new_image = gdk_pixbuf_new_from_file("imagenes/red_token.jpg", NULL);
        game_data->turn = 1;
    }

    gtk_image_set_from_pixbuf(GTK_IMAGE(img_data->image), new_image);
}

void destroy(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}

gboolean delete_event(GtkWidget *widget, GdkEvent *event, gpointer data) {
    destroy(widget, data);

    return FALSE;
}

void gen_callback(GtkWidget *menuitem, gpointer data) {
    g_print("gen_callback\n");
}
