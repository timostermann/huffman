#include "btree.h"
#include <stdio.h>

/**
 * Implementierung der Datenstruktur für Binärbäume.
 */
typedef struct _BTREE
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

/**
 * Gibt Unterbaum des Binärbaumes aus.
 * @param node          Wurzel des Unterbaumes
 * @param depth         Tiefe des Unterbaumes im Binärbaum
 * @param print_func    Funktion zur Ausgabe der Daten eines Binärbaumknotens
 */
static void print_subtree(BTREE_NODE *node, int depth, PRINT_DATA_FCT print_func);

extern BTREE *btree_new(void *data,
                        DESTROY_DATA_FCT destroy_data,
                        PRINT_DATA_FCT print_data)
{
    // create new tree, set data
    BTREE *new_tree = (BTREE *) malloc(sizeof(BTREE));
    new_tree->root = btreenode_new(data);

    if (destroy_data != NULL)
    {
        new_tree->destroy_data_func = destroy_data;
    }

    if (print_data != NULL)
    {
        new_tree->print_data_func = print_data;
    }

    return new_tree;
}

extern BTREE *btree_clone(BTREE *tree)
{
    if (tree != NULL)
    {
        // create new tree with data and functions of old tree, clone and set left and right node
        BTREE *new_tree = btree_new(btreenode_get_data(tree->root), tree->destroy_data_func, tree->print_data_func);
        btreenode_set_left(new_tree->root, btreenode_clone(btreenode_get_left(tree->root)));
        btreenode_set_right(new_tree->root, btreenode_clone(btreenode_get_right(tree->root)));
        return new_tree;
    }
    else
    {
        return NULL;
    }
}

extern void btree_destroy(BTREE **tree, bool destroy_data)
{
    if (tree != NULL && *tree != NULL)
    {
        // destroy root, free tree
        btreenode_destroy(&(**tree).root, destroy_data ? (**tree).destroy_data_func : NULL);
        free(*tree);
        *tree = NULL;
    }
}

extern bool btree_equals(BTREE *tree1, BTREE *tree2)
{
    return tree1 != NULL && tree2 != NULL
        ? btreenode_equals(tree1->root, tree2->root)
        : false;
}

extern BTREE_NODE *btree_get_root(BTREE *tree)
{
    if (tree == NULL || tree->root == NULL)
    {
        return NULL;
    }
    else
    {
        return tree->root;
    }
}

extern BTREE *btree_merge(BTREE *left, BTREE *right, void *data)
{
    // create new tree with left trees' functions
    BTREE *new_tree = btree_new(data, left->destroy_data_func, left->print_data_func);

    // set rood node of left and right tree as left and right child nodes
    btreenode_set_left(new_tree->root, left->root);
    btreenode_set_right(new_tree->root, right->root);

    // free left and right tree
    free(left);
    left = NULL;
    free(right);
    right = NULL;

    return new_tree;
}

extern void btree_print(BTREE *tree)
{
    if (tree != NULL)
    {
        print_subtree(tree->root, 0, tree->print_data_func);
    }
}

static void print_subtree(BTREE_NODE *node, int depth, PRINT_DATA_FCT print_func)
{
    for (int i = 0; i < depth; i++)
    {
        printf("\t");
    }
    printf("|-- ");
    btreenode_print(node, print_func);
    printf("\n");

    if (btreenode_get_left(node) != NULL)
    {
        print_subtree(btreenode_get_left(node), depth + 1, print_func);
    }

    if (btreenode_get_right(node) != NULL)
    {
        print_subtree(btreenode_get_right(node), depth + 1, print_func);
    }
}