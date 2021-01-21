
#ifndef HEAP_BINARY_HEAP_H
#define HEAP_BINARY_HEAP_H

#include <stdbool.h>

/**
 * Typdefiniton Elementsvergleichsfunktion
 */
typedef int (*HEAP_ELEM_COMP) (void *elem1, void *elem2);

/**
 * Typdefiniton Elementsausgabefunktion
 */
typedef void (*HEAP_ELEM_PRINT) (void *elem);

/**
 * Initialisiert den Heap.
 * @param comp - Elementsvergleichsfunktion
 * @param print - Elementsausgabefunktion
 */
extern void heap_init(HEAP_ELEM_COMP comp, HEAP_ELEM_PRINT print);

/**
 * Gibt Speicher des Heaps frei.
 */
extern void heap_destroy(void);

/**
 * Fügt ein neues Element in den Heap ein und stellt Heap-Eigenschaft wieder her.
 * @param element - einzufügendes Element
 */
extern void heap_insert(void *element);

/**
 * Entfernt kleinstes Element des Heaps und stellt Heap-Eigenschaft wieder her.
 * @param min_element - Übergabeparameter für extrahiertes Element
 * @return false, falls heap leer ist, sonst true
 */
extern bool heap_extract_min(void **min_element);

/**
 * Gibt Heap auf dem Bildschirm aus.
 */
extern void heap_print(void);

#endif //HEAP_BINARY_HEAP_H
