#include "btreenode.h"
#include <stdio.h>

extern BTREE_NODE *btreenode_new(void *data)
{
    // create new node, set data
    BTREE_NODE *new_node = (BTREE_NODE *) malloc(sizeof(BTREE_NODE));
    new_node->value = data;
    new_node->right_node = NULL;
    new_node->left_node = NULL;
    return new_node;
}

extern BTREE_NODE *btreenode_clone(BTREE_NODE *node)
{
    if (node != NULL)
    {
        BTREE_NODE *new_node = btreenode_new(node->value);
        
        if (node->left_node != NULL)
        {
            new_node->left_node = btreenode_clone(node->left_node);
        }
        
        if (node->right_node != NULL)
        {
            new_node->right_node = btreenode_clone(node->right_node);
        }
        
        return new_node;
    }
    else
    {
        return NULL;
    }
}

extern bool btreenode_equals(BTREE_NODE *node1, BTREE_NODE *node2)
{
    bool is_equal = false;

    if (node1 == NULL || node2 == NULL)
    {
        return is_equal;
    }

    // compare node values
    is_equal = node1->value == node2->value;

    // compare child nodes if not NULL for both nodes
    if (node1->left_node != NULL && node2->left_node != NULL)
    {
        is_equal = is_equal && btreenode_equals(node1->left_node, node2->left_node);
    }
    else if (node1->left_node != NULL || node2->left_node != NULL)
    {
        is_equal = false;
    }

    if (node1->right_node != NULL && node2->right_node != NULL)
    {
        is_equal = is_equal && btreenode_equals(node1->right_node, node2->right_node);
    }
    else if (node1->right_node != NULL || node2->right_node != NULL)
    {
        is_equal = false;
    }

    return is_equal;
}

extern void btreenode_destroy(BTREE_NODE **node,
                              DESTROY_DATA_FCT destroy_data)
{
    if (node != NULL && *node != NULL)
    {
        // destroy node data if function given
        if (destroy_data != NULL)
        {
            destroy_data(&(**node).value);
        }

        // destroy child nodes if not NULL
        if ((**node).right_node != NULL)
        {
            btreenode_destroy(&(**node).right_node, destroy_data);
        }
    
        if ((**node).left_node != NULL)
        {
            btreenode_destroy(&(**node).left_node, destroy_data);
        }
        
        free(*node);
        *node = NULL;
    }
}

extern void *btreenode_get_data(BTREE_NODE *node)
{
    return node == NULL
        ? NULL
        : node->value;
}

extern BTREE_NODE *btreenode_get_left(BTREE_NODE *node)
{
    return node == NULL
        ? NULL
        : node->left_node;
}

extern BTREE_NODE *btreenode_get_right(BTREE_NODE *node)
{
    return node == NULL
           ? NULL
           : node->right_node;
}

extern bool btreenode_is_leaf(BTREE_NODE *node)
{
    return btreenode_get_left(node) == NULL && btreenode_get_right(node) == NULL;
}

extern bool btreenode_set_left(BTREE_NODE *parent_node, BTREE_NODE *node)
{
    bool already_has_left_child_node = parent_node->left_node != NULL;

    if (!already_has_left_child_node)
    {
        parent_node->left_node = node;
    }

    return !already_has_left_child_node;
}

extern bool btreenode_set_right(BTREE_NODE *parent_node, BTREE_NODE *node)
{
    bool already_has_right_child_node = parent_node->right_node != NULL;

    if (!already_has_right_child_node)
    {
        parent_node->right_node = node;
    }

    return !already_has_right_child_node;
}

extern void btreenode_print(BTREE_NODE *node, PRINT_DATA_FCT print_data)
{
    if (print_data != NULL && node != NULL)
    {
        // print address and data
        printf("(%p", node);
        print_data(node->value);
        printf(")");
    }
}
