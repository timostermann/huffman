#include "binary_heap.h"
#include "huffman_common.h"
#include <stdlib.h>
#include <stdio.h>

 /**
  * Vertauscht zwei Heap-Elemente an den angegebenen Indizes.
  * @param index_elem1 - Index eines zu tauschenden Heap-Elements
  * @param index_elem2 - Index eines zu tauschenden Heap-Elements
  */
static void swap_elements(int index_elem1, int index_elem2);

/**
 * Gibt die Unter-Baumstruktur ab einem bestimmten Element aus.
 * @param index - Index des Elements im Heap
 * @param depth - Tiefe des Elements in Baumstruktur
 */
static void print_subtree(int index, int depth);

/**
 * Gibt ein Element aus dem Heap aus.
 * @param index - Index des Elements im Heap
 * @param depth - Tiefe des Elements in Baumstruktur
 */
static void print_element(int index, int depth);

/**
 * Ermittelt Index des übergeordneten Elements. Eingabe von 0 liefert 0.
 * @param element_index - Index des Elements
 * @return Index des übergeordneten Elements.
 */
static int get_parent_index(int element_index);

/**
 * Ermittelt Indizes der Kinder eines Elementes in der Heap-Baumstruktur.
 * Schreibt Kinder-Indizes in entsprechende Parameter. Falls ein Element kein
 * linkes oder rechtes Kindelement hat, wird -1 in den entsprechenden Parameter geschrieben.
 * @param element_index - Index des Elements
 * @param left_child_index - Zeiger auf Index des linken Kindelements
 * @param right_child_index - Zeiger auf Index des rechten Kindelements
 * @return true, Element falls Kindelemente hat; sonst false
 */
static bool get_child_indices(int element_index, int *left_child_index, int *right_child_index);

/**
 * Gibt an, ob ein Element ein kleineres Kindelement hat.
 * @param element_index - Index des Elements
 * @param left_child_index - Index des linken Kindelements
 * @param right_child_index - Index des rechten Kindelements
 * @return true, falls mindestens ein Kindelement kleiner als das Element ist;
 *         sonst false
 */
static bool has_smaller_child(int element_index, int left_child_index, int right_child_index);

/**
 * Ermittelt Index des kleineren Kindelements.
 * @param left_child_index - Index des linken Kindelements
 * @param right_child_index - Index des rechten Kindelements
 * @return Index des kleineren Kindelements
 */
static int get_index_of_smaller_child(int left_child_index, int right_child_index);

/**
 * Heap-Speicher
 */
static void **heap;

/**
 * Funktion zum Vergleich zweier Heap-Elemente
 */
static HEAP_ELEM_COMP comp_elem_func;

/**
 * Funktion zur Ausgabe eines Heap-Elements
 */
static HEAP_ELEM_PRINT print_elem_func;

/**
 * Heap-Größe
 */
static int size;

/**
 * Heap-Füllstand
 */
static int filling_level;

extern void heap_init(HEAP_ELEM_COMP comp, HEAP_ELEM_PRINT print)
{
    if (heap != NULL)
    {
        heap_destroy();
    }

    // set comp and print function, init heap, set size and filling_level to initial values
    comp_elem_func = comp;
    print_elem_func = print;
    heap = malloc(sizeof(void*) * NUM_OF_ELEMENTS);

    if (heap == NULL)
    {
        printf("Fehler bei der Speicherreservierung.");
        exit(1);
    }

    size = NUM_OF_ELEMENTS;
    filling_level = 0;
}

extern void heap_destroy(void)
{
    // free heap, set size and filling_level to initial values
    free(heap);
    heap = NULL;
    size = 0;
    filling_level = 0;
}

extern void heap_insert(void *element)
{
    int parent_index;
    int element_index;
    bool has_smaller_parent = false;

    if (filling_level == size)
    {
        // increase heap size
        heap = realloc(heap, (size + NUM_OF_ELEMENTS) * sizeof(void*));
        if (heap == NULL)
        {
            printf("Fehler bei der Speicherreservierung.");
            exit(1);
        }
        size += NUM_OF_ELEMENTS;
    }

    // add element to heap
    heap[filling_level] = element;
    element_index = filling_level;
    parent_index = get_parent_index(element_index);
    filling_level++;

    // move new element to right position
    while (element_index > 0 && !has_smaller_parent)
    {
        if (comp_elem_func(heap[element_index], heap[parent_index]) == -1)
        {
            swap_elements(element_index, parent_index);
            element_index = parent_index;
            parent_index = get_parent_index(element_index);
        }
        else
        {
            has_smaller_parent = true;
        }
    }
}

extern bool heap_extract_min(void **min_element)
{
    int element_index = 0;
    int left_child_index = -1;
    int right_child_index = -1;
    int smaller_child_index;

    if (filling_level == 0)
    {
        return false;
    }
    else
    {
        // extract first element, remove from heap
        *min_element = heap[0];
        swap_elements(filling_level - 1, 0);
        filling_level--;

        if (filling_level < size - NUM_OF_ELEMENTS)
        {
            heap = realloc(heap, (size - NUM_OF_ELEMENTS) * sizeof(void*));
            if (heap == NULL)
            {
                printf("Fehler bei der Speicherreservierung.");
                exit(1);
            }
            size -= NUM_OF_ELEMENTS;
        }

        while (get_child_indices(element_index, &left_child_index, &right_child_index)
               && has_smaller_child(element_index, left_child_index, right_child_index))
        {
            // swap element with smaller child
            smaller_child_index = get_index_of_smaller_child(left_child_index, right_child_index);
            swap_elements(smaller_child_index, element_index);
            element_index = smaller_child_index;
        }
    }

    return true;
}

extern void heap_print(void)
{
    if (filling_level > 0)
    {
        print_subtree(0, 0);
        printf("\n");
    }
}

static void print_subtree(int index, int depth)
{
    int left_child_index = -1;
    int right_child_index = -1;

    print_element(index, depth);

    if (get_child_indices(index, &right_child_index, &left_child_index))
    {
        if (left_child_index != -1)
        {
            print_subtree(left_child_index, depth + 1);
        }

        if (right_child_index != -1)
        {
            print_subtree(right_child_index, depth + 1);
        }
    }
}

static void swap_elements(int index_elem1, int index_elem2)
{
    void *temp_elem = heap[index_elem1];
    heap[index_elem1] = heap[index_elem2];
    heap[index_elem2] = temp_elem;
}

static void print_element(int index, int depth)
{
    for (int i = 0; i < depth; i++)
    {
        printf("\t");
    }
    printf("|--");
    print_elem_func(heap[index]);
    printf("\n");
}

static int get_parent_index(int element_index)
{
    return (element_index - 1) / 2;
}

static bool get_child_indices(int element_index, int *left_child_index, int *right_child_index)
{
    bool has_children = false;

    if (((2 * element_index) + 1) < filling_level)
    {
        *left_child_index = (2 * element_index) + 1;
        has_children = true;
    }
    else
    {
        *left_child_index = -1;
    }

    if (((2 * element_index) + 2) < filling_level)
    {
        *right_child_index = (2 * element_index) + 2;
        has_children = true;
    }
    else
    {
        *right_child_index = -1;
    }

    return has_children;
}

static bool has_smaller_child(int element_index, int left_child_index, int right_child_index)
{
    bool has_smaller_child = false;

    if (left_child_index != -1 && right_child_index != -1)
    {
        has_smaller_child = comp_elem_func(heap[left_child_index], heap[element_index]) == -1
                ||  comp_elem_func(heap[right_child_index], heap[element_index]) == -1;
    }
    else if (left_child_index != -1)
    {
        has_smaller_child = comp_elem_func(heap[left_child_index], heap[element_index]) == -1;
    }
    else if (right_child_index != -1)
    {
        has_smaller_child = comp_elem_func(heap[right_child_index], heap[element_index]) == -1;
    }

    return has_smaller_child;
}

static int get_index_of_smaller_child(int left_child_index, int right_child_index)
{
    int index_of_smaller_child;

    if (left_child_index != -1 && right_child_index != -1)
    {
        if (comp_elem_func(heap[left_child_index], heap[right_child_index]) == -1)
        {
            index_of_smaller_child = left_child_index;
        }
        else
        {
            index_of_smaller_child = right_child_index;
        }
    }
    else
    {
        index_of_smaller_child = left_child_index == -1 ? right_child_index : left_child_index;
    }

    return index_of_smaller_child;
}