/* buttonsentry.c
   Este ejercicio muestra el uso de contenedores, botones y
   espacios de entrada con sus funciones de callback y seniales

*/

#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>

#include <time.h>

typedef struct _node{
    GtkWidget *label[3];
    int flag;
} NODO;

GtkWidget *AddButton(GtkWidget *theBox, const gchar *buttonText, gpointer CallBackFunction, GtkWidget *EntryBox);
void ButtonClicked(GtkButton *button, gpointer data);
void StopTheApp(GtkWidget *window, gpointer data);
void HelloAction(GtkButton *button, gpointer data);
void CambiaLabel(GtkButton *button, gpointer data);


gint main ( gint argc, gchar *argv[]) {
  GtkWidget *window;
  GtkWidget *button;
  GtkWidget *box;
  GtkWidget *verticalbox;
  GtkWidget *entrybox;
  NODO lista;
  int i;
  char texto[2];

  srand(time(NULL));

  gtk_init(&argc, &argv);

  lista.flag = 0;

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window),320,200);
  gtk_container_border_width(GTK_CONTAINER(window),5);

  
  verticalbox = gtk_vbox_new(TRUE,5);

  entrybox = gtk_entry_new();

  box = gtk_hbox_new(TRUE,5); 
  button = AddButton(box,"pon texto",ButtonClicked,entrybox);
  button = AddButton(box,"captura texto",HelloAction,entrybox);
  
  button = gtk_button_new_with_label("camb col");
  gtk_box_pack_start(GTK_BOX(box),button,FALSE,TRUE,0);
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(CambiaLabel),&lista);
  gtk_widget_show(button);

  for (i=0; i<3; i++)
    {
      sprintf(texto,"%d",i+1);
      lista.label[i] = gtk_label_new(texto);
      gtk_box_pack_start(GTK_BOX(verticalbox),lista.label[i],TRUE,TRUE,0);
    }

  gtk_box_pack_start(GTK_BOX(verticalbox),entrybox,TRUE,TRUE,5);
  gtk_box_pack_start(GTK_BOX(verticalbox),box,TRUE,TRUE,5);
  
  
  gtk_signal_connect(GTK_OBJECT(window),"destroy",GTK_SIGNAL_FUNC(StopTheApp),NULL);
  

  gtk_container_add(GTK_CONTAINER(window),verticalbox);
  
  gtk_widget_show_all(window);
  
  gtk_main();

  return 0;

}

GtkWidget *AddButton(GtkWidget *theBox, const gchar *buttonText, gpointer CallBackFunction, GtkWidget *EntryBox) {
    GtkWidget *button;
    button = gtk_button_new_with_label(buttonText);
    gtk_box_pack_start(GTK_BOX(theBox),button,FALSE,TRUE,0);
    gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(CallBackFunction),EntryBox);
    gtk_widget_show(button);

    return button;
}

void ButtonClicked(GtkButton *button, gpointer data) {
    g_print("Button got clicked \n");
    gtk_entry_set_text(GTK_ENTRY(data),"Hola Mundo");
}

void HelloAction(GtkButton *button, gpointer data) {
    const gchar *text;
    
    text = gtk_entry_get_text(GTK_ENTRY(data));
    g_print("%s",text);
}

void StopTheApp(GtkWidget *window, gpointer data) {
    gtk_main_quit();
}

void CambiaLabel(GtkButton *button, gpointer data) {
  GdkColor color;
  int i;
  NODO *datos=(NODO *)data;
  
  //gdk_color_parse("#368f1f", &color);

  if (!datos->flag) {
    color.red= random() % 0xFFFF;
    color.green= random() % 0xFFFF;
    color.blue= random() % 0xFFFF;

    datos->flag = 1;
  }
  else {
    color.red= 0;
    color.green= 0;
    color.blue= 0;

    datos->flag = 0;
  }
  
  for (i=0; i<3; i++)
    gtk_widget_modify_fg(GTK_WIDGET(datos->label[i]), GTK_STATE_NORMAL, &color);
 
}
