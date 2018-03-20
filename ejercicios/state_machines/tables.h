/************************************************************************
 *                                                                      *
 * Archivo: tables.h                                                    *
 * Descripcion: Tablas para la maquina de estados y funciones externas  *
 *      Aqui se definen todos las tablas que se utilizan                *
 *      en el programa                                                  *
 *                                                                      *
 ************************************************************************/

/*************** ARCHIVOS DE INCLUSION ***************/ 
#include "local.h"
#include <stdio.h>


/*************** FUNCIONES EXTERNAS *********************
 * En esta seccion se declaran los encabezados de   *
 * todas las funciones que se utilizan en las       *
 * tablas del programa. Todas las funciones deben   *
 * ser de tipo entero y no deben recibir parametros *
 ********************************************************/ 
extern int nul(void);

extern int msg_A(void);
extern int msg_B(void);
extern int msg_C(void);

extern int msg_sal_A(void);
extern int msg_sal_B(void);
extern int msg_sal_C(void);

/******************** TABLAS ********************
 * En esta seccion se declaran las tablas   *
 * que se van a usar en el programa     *
 ************************************************/ 
 
/*************** TABLA DE ACCION ***************/  
ACTION_TAB action_table[] = {
        /*etype     accion    bandera   sigEdo. */    
    { ENTRADA_A,   msg_A,         -1, ESTADO_A},
    { ENTRADA_B,   msg_B,         -1, ESTADO_B},
    { ENTRADA_C,   msg_C,         -1, ESTADO_C},
    { ENTRADA_W,   NULL,          -1, ESTADO_ESPERA},

    { ENTRADA_a,   msg_sal_A,     -1, ESTADO_ESPERA},
    { -1,  NULL,          -1, ESTADO_A},

    { ENTRADA_b,   msg_sal_B,     -1, ESTADO_ESPERA},
    { -1,  NULL,          -1, ESTADO_B},

    { ENTRADA_c,   msg_sal_C,     -1, ESTADO_ESPERA},
    { -1,  NULL,          -1, ESTADO_C},
};

/*************** TABLA AUXILIAR ***************/  
AUX_TAB aux_table[] = {        
/*    accion       bandera           sigEdo */
    { NULL,        -1,          -1},
};

/*************** TABLA DE ESTADOS ***************/  
STATE_TAB state_table[] = {
   /*estado      inicio   fin */
    {ESTADO_ESPERA, 0, 3},
    {ESTADO_A, 4, 5},
    {ESTADO_B, 6, 7},
    {ESTADO_C, 8, 9},
};
