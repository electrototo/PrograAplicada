/*
 *  autor: cristobal liendo i
 *  fecha: Fri 06 Apr 2018 09:39:41 AM CDT
 *  descripcion: calculadora basica hecha con gtk
*/

#include <gtk/gtk.h>
#include <string.h>

GtkWidget *entry;
GtkEntryBuffer *entry_buffer;
int loc;

gchar input[100];

static gboolean delete_event(GtkWidget *widget, GdkEvent *event, gpointer *data) {
    return FALSE;
}

static void destroy(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}

void parse_command(char *input) {
    float num1, num2, total;
    char operator;

    int parsed;

    parsed = sscanf(input, "%f%c%f", &num1, &operator, &num2);

    if (parsed != 3)
        gtk_entry_buffer_set_text(entry_buffer, "Bad operation", 13);

    else {
        switch(operator) {
            case '-':
                total = num1 - num2;
                break;

            case '+':
                total = num1 + num2;
                break;

            case '*':
                total = num1 * num2;
                break;

            case '/':
                total = num1 / num2;
                break;

            default:
                break;
        }

        sprintf(input, "%.2f", total);
        g_object_set(G_OBJECT(entry), "text", input, NULL);
    }
}

void callback(GtkWidget *widget, gpointer callback_data) {
    gchar *label;

    g_object_get(G_OBJECT(widget), "label", &label, NULL);

    if (*label == '=') {
        strcpy(input, gtk_entry_buffer_get_text(entry_buffer));
        parse_command(input);

        loc = 0;
        input[loc] = 0;
    }
    else if (loc < 99) {
        input[loc++] = *label;
        input[loc] = 0;

        gtk_entry_buffer_set_text(entry_buffer, input, loc);
    }

    g_free(label);
}

GtkWidget *create_numpad() {
    char *options[16] = {
        "7", "8", "9", "/",
        "4", "5", "6", "*",
        "1", "2", "3", "-",
        "0", ".", "=", "+"
    };

    GtkWidget *container;
    GtkWidget *row, *button;

    container = gtk_vbox_new(FALSE, 3);

    for (int i = 0; i < 16; i++) {
        if (i % 4 == 0) {
            row = gtk_hbox_new(TRUE, 0);
            gtk_box_pack_start(GTK_BOX(container), row, TRUE, TRUE, 0);
        }

        button = gtk_button_new_with_label(options[i]);
        gtk_widget_set_size_request(button, 60, 33);
        g_signal_connect(button, "clicked", G_CALLBACK(callback), NULL);

        gtk_box_pack_start(GTK_BOX(row), button, TRUE, TRUE, 2);
        gtk_widget_show(button);
    }

    return container;
}

void entry_callback(GtkWidget *widget, gpointer *data) {
    strcpy(input, gtk_entry_buffer_get_text(entry_buffer));
    parse_command(input);
}

int main(int argc, char **argv) {
    GtkWidget *window;
    GtkWidget *row, *button, *box1, *entrybox;

    loc = 0;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    // entry set up
    entry_buffer = gtk_entry_buffer_new(NULL, -1);
    entry = gtk_entry_new_with_buffer(entry_buffer);
    gtk_entry_set_alignment(GTK_ENTRY(entry), 1);
    g_signal_connect(entry, "activate", G_CALLBACK(entry_callback), NULL);

    box1 = gtk_vbox_new(FALSE, 0);

    entrybox = gtk_hbox_new(TRUE, 5);
    row = gtk_hbox_new(TRUE, 5);

    gtk_box_pack_start(GTK_BOX(box1), entrybox, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(entrybox), entry, TRUE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(box1), create_numpad(), TRUE, TRUE, 0);

    g_signal_connect(window, "delete-event", G_CALLBACK(delete_event), NULL);
    g_signal_connect(window, "destroy", G_CALLBACK(destroy), NULL);

    gtk_container_add(GTK_CONTAINER(window), box1);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
