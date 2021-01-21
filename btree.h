/**
 * @file
 * Dieses Modul stellt eine Struktur zur Repräsentation von Binärbäumen
 * und Funktionen darauf zur Verfügung.
 *
 * @author  Ulrike Griefahn
 * @date    2019-09-09
 */ 

#ifndef _BTREE_H
#define _BTREE_H
/* ------------------------------------------------------------------------ */


/* ===========================================================================
 * Header-Dateien 
 * ======================================================================== */

#include "btreenode.h"
#include <stdbool.h>

/* ===========================================================================
 * Typdefinitionen
 * ======================================================================== */

/**
 * Repräsentation eines Binärbaumes.
 */
typedef struct
{
    /**
     * Wurzelknoten des Binärbaumes.
     */
    BTREE_NODE *root;

    /**
     * Funktion zum Löschen des Inhalts eines Binärbaumknotens.
     */
    DESTROY_DATA_FCT destroy_data_func;

    /**
     * Funktion zur Ausgabe des Inhalts eines Binärbaumknotens.
     */
    PRINT_DATA_FCT print_data_func;
} BTREE;

/* ===========================================================================
 * Funktionsprototypen
 * ======================================================================== */


/**
 * Erzeugt einen neuen Binärbaum, dessen Wurzel die übergebenen Daten 
 * beinhaltet. Im zweiten Parameter wird die Funktion übergeben, mit der die
 * enthaltenen Daten gelöscht werden können, im dritten Parameter wird die
 * Funktion übergeben, mit der die Daten am Bildschirm ausgegeben werden können.
 * In beiden Parametern kann NULL übergeben werden, so dass keine Funktionen
 * zum Ausgeben und Löschen der Knotendaten gesetzt sind.
 * 
 * @param data          Daten für die Wurzel des neuen Baums
 * @param destroy_data  Funktion, mit der die in den Knoten
 *                      enthaltenen Daten gelöscht werden können oder NULL
 * @param print_data    Funktion, mit der die in den Knoten
 *                      enthaltenen Daten am Bildschirm ausgegeben werden
 *                      können oder NULL
 * @return              der neu erzeugte Binärbaum
 */
extern BTREE *btree_new(void *data,
                        DESTROY_DATA_FCT destroy_data, 
                        PRINT_DATA_FCT print_data);

/**
 * Erzeugt eine Kopie (deep copy) des übergebenen Binärbaums. Es werden die
 * Struktur des Baums und die Knoten kopiert. Die in den Knoten enthaltenen
 * Daten werden nicht kopiert, sondern nur die Referenz auf sie übernommen.
 * Im Anschluss an die Funktion verweisen beide Bäume auf dieselben Daten.
 * 
 * Es wird davon ausgegangen, dass tree != NULL ist.
 * 
 * @param tree  Binärbaum, der kopiert werden soll
 * @return      die neu erzeugte Kopie
 */
extern BTREE *btree_clone(BTREE *tree);

/**
 * Löscht den übergebenen Baum, d.h. alle Knoten ausgehend von der Wurzel und
 * die Struktur für den Baum. Wird im zweiten Argument true übergeben, werden
 * die in den Knoten enthaltenen Daten ebenfalls gelöscht.
 * 
 * @param tree          Baum, der gelöscht werden soll
 * @param destroy_data  true, wenn die Daten gelöscht werden sollen;
 *                      false, sonst
 */
extern void btree_destroy(BTREE **tree, bool destroy_data);

/**
 * Vergleicht die beiden übergebenen Binärbäume miteinander. Zwei Binärbäume
 * sind gleich, wenn  beide Baeume ab dem Wurzelknoten dieselbe Struktur
 * besitzen und in allen Knoten auf dieselben Daten verweisen. Sie können sich
 * in den gespeicherten Funktionen unterscheiden.
 *
 * @param tree1     der erste zu vergleichende Binärbaum
 * @param tree2     der zweite zu vergleichende Binärbaum
 * @return          true, wenn beide Bäume gleich sind, false sonst
 */
extern bool btree_equals(BTREE *tree1, BTREE *tree2);

/**
 * Liefert die Wurzel des übergebenen Binärbaums.
 * 
 * @param tree  Binärbaum, dessen Wurzel geliefert werden soll
 * @return      Wurzel des Baums oder NULL, wenn der Baum keinen Wurzelknoten
 *              hat oder kein Baum übergeben wurde
 */
extern BTREE_NODE *btree_get_root(BTREE *tree);

/**
 * Erzeugt einen neuen Binärbaum, dessen Wurzel die übergebenen Daten 
 * erhält. Die neue Wurzel bekommt die Wurzel des Binärbaums left als
 * linken Nachfolger und die Wurzel des Binärbaums right als rechten 
 * Nachfolger. Der neue Baum erhält die Funktionen aus dem Baum, der als 
 * linker Nachfolger angefügt wird.
 * 
 * Der Speicherbereich der Bäume left und right, jedoch nicht ihrer Knoten 
 * wird freigegeben.
 * 
 * @param left      die erste zu verbindenden Bäume
 * @param right     der zweite der beiden zu verbindenden Bäume
 * @param data      die Daten für die Wurzel im neuen Baum
 * @return          der neu erzeugte Baum
 */
extern BTREE *btree_merge(BTREE *left, BTREE *right, void *data);

/**
 * Gibt den Binärbaum mit seinen Daten in Preorder-Reihenfolge auf dem 
 * Bildschirm aus.
 *
 * @param tree      Binärbaum, der ausgegeben werden soll
 */
extern void btree_print(BTREE *tree);

/* ------------------------------------------------------------------------ */
#endif
