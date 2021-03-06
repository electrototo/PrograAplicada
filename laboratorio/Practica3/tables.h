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

extern int c_nip(void);
extern int mensaje_init(void);
extern int mensaje_I(void);
extern int mensaje_R(void);
extern int imp_saldo(void);
extern int mensaje_mov(void);
extern int mensaje_C(void);
extern int mensaje_prin(void);
extern int mul_100_I(void);
extern int mensaje_I(void);
extern int mul_100_R(void);
extern int mensaje_R(void);
extern int m_filt(void);
extern int m_todo(void);
extern int check_P(void);
extern int mensaje_prin(void);
extern int error_nip(void);
extern int error_mul_100_I(void);
extern int agr_I(void);
extern int error_mul_100_R(void);
extern int agr_R(void);
extern int error_C(void);
extern int agr_C(void);
extern int mensaje_desp(void);


/******************** TABLAS ********************
 * En esta seccion se declaran las tablas       *
 * que se van a usar en el programa             *
 ************************************************/

/*************** TABLA DE ACCION ***************/
// { ENTRADA_0,  Pide_Passw,   -1, Pass_Word_1},
/*etype     accion     bandera   sigEdo. */

ACTION_TAB action_table[] = {
    {0, c_nip, 0, -1},
    {-1, mensaje_init, -1, 0},
    {2, mensaje_I, -1, 2},
    {3, mensaje_R, -1, 3},
    {4, imp_saldo, -1, 1},
    {5, mensaje_mov, -1, 4},
    {6, mensaje_C, -1, 5},
    {7, mensaje_desp, -1, 0},
    {-1, mensaje_prin, -1, 1},
    {9, mul_100_I, 0, -1},
    {-1, mensaje_I, -1, 2},
    {11, mul_100_R, 0, -1},
    {12, mul_100_R, 0, -1},
    {13, mul_100_R, 0, -1},
    {14, mul_100_R, 0, -1},
    {15, mul_100_R, 0, -1},
    {16, mul_100_R, 0, -1},
    {-1, mensaje_R, -1, 3},
    {18, m_filt, -1, 1},
    {19, m_todo, -1, 1},
    {-1, mensaje_mov, -1, 4},
    {21, check_P, 0, -1},
    {-1, mensaje_C, -1, 5},
};

/*************** TABLA AUXILIAR ***************/
/*    accion       bandera           sigEdo */
// { funcion1,        -1,          ESTADO_0},
AUX_TAB aux_table[] = {
    {mensaje_prin, -1, 1},
    {error_nip, -1, 0},
    {error_mul_100_I, -1, 2},
    {agr_I, -1, 0},
    {error_mul_100_R, -1, 3},
    {agr_R, -1, 0},
    {error_C, -1, 5},
    {agr_C, -1, 0},
    
};

/*************** TABLA DE ESTADOS ***************/
/*estado      inicio   fin */
// {ESTADO_0,     0,      1},
STATE_TAB state_table[] = {
    {INIT, 0, 1},
    {MAIN, 2, 8},
    {DEPOSIT, 9, 10},
    {WITHDRAWAL, 11, 17},
    {MOV, 18, 20},
    {CHANGE, 21, 22},
};
