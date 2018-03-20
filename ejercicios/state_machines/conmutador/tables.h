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
 * En esta seccion se declaran los encabezados de       *
 * todas las funciones que se utilizan en las           *
 * tablas del programa. Todas las funciones deben       *
 * ser de tipo entero y no deben recibir parametros     *
 ********************************************************/
extern int nul(void);

extern int msg_dial(void);
extern int msg_config(void);
extern int bloqueado(void);
extern int msg_bloq(void);
extern int msg_ubloq(void);
extern int existe_a(void);
extern int existe_b(void);
extern int msg_num_bloq(void);
extern int ocupado(void);
extern int msg_busy(void);
extern int contesta(void);
extern int msg_save(void);
extern int msg_exist(void);
extern int msg_exist(void);
extern int desbloqueo(void);
extern int msg_no_answer(void);
extern int info(void);


/******************** TABLAS ********************
 * En esta seccion se declaran las tablas       *
 * que se van a usar en el programa             *
 ************************************************/

/*************** TABLA DE ACCION ***************/
// { ENTRADA_0,  Pide_Passw,   -1, Pass_Word_1},
/*etype     accion     bandera   sigEdo. */

ACTION_TAB action_table[] = {
    {0, msg_dial, -1, 1},
    {1, msg_config, -1, 2},
    {-1, nul, -1, 0},
    {3, bloqueado, 0, -1},
    {-1, nul, -1, 0},
    {5, msg_bloq, -1, 3},
    {6, msg_ubloq, -1, 4},
    {7, nul, -1, 0},
    {-1, nul, -1, 2},
    {9, existe_a, 0, -1},
    {-1, nul, -1, 0},
    {11, existe_b, 0, -1},
    {-1, nul, -1, 0},
    
};

/*************** TABLA AUXILIAR ***************/
/*    accion       bandera           sigEdo */
// { funcion1,        -1,          ESTADO_0},
AUX_TAB aux_table[] = {
    {msg_num_bloq, -1, 0},
    {ocupado, 0, -1},
    {msg_busy, -1, 0},
    {contesta, 0, -1},
    {msg_save, -1, 0},
    {msg_exist, -1, 0},
    {msg_exist, -1, 0},
    {desbloqueo, -1, 0},
    {msg_no_answer, -1, 0},
    {info, -1, 0},
    
};

/*************** TABLA DE ESTADOS ***************/
/*estado      inicio   fin */
// {ESTADO_0,     0,      1},
STATE_TAB state_table[] = {
    {IDLE, 0, 2},
    {DIAL, 3, 4},
    {CONFIG, 5, 8},
    {BLOQ, 9, 10},
    {UBLOQ, 11, 12},
    
};