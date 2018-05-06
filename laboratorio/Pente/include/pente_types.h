/*
 * Pente types
 * Escrito por Cristobal Liendo <cristobal@liendo.net>
*/


#ifndef PTYPESH
#define PTYPESH

typedef struct image_data_t{
    GtkWidget *image;
    int x, y;

    struct game_info_t *game_info;
} image_data_t;

typedef struct game_info_t {
    int turn;
    int player1_p, player2_p;
    int ccount_1, ccount_2;
} game_info_t;

typedef struct menu_item_dt {
    char label[15];
    void (*callback)(GtkMenuItem *, gpointer);
    gpointer data;
} menu_item_dt;

#endif
