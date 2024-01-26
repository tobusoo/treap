#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bstree.h"

static void replace_node(Bstree* parent, Bstree* node, Bstree* child);

Bstree* bstree_create(int key, char* value)
{
    Bstree* node = malloc(sizeof(Bstree));
    if (!node) {
        return NULL;
    }

    node->key = key;
    node->value = strdup(value);

    node->parent = NULL;
    node->right = NULL;
    node->left = NULL;

    return node;
}

Bstree* bstree_max(Bstree* tree)
{
    if (tree == NULL)
        return NULL;

    while (tree->right != NULL)
        tree = tree->right;
    return tree;
}

Bstree* bstree_min(Bstree* tree)
{
    if (tree == NULL)
        return NULL;

    while (tree->left != NULL)
        tree = tree->left;
    return tree;
}

void bstree_add(Bstree* tree, int key, char* value)
{
    if (tree == NULL)
        return;

    Bstree *parent, *node;

    while (tree != NULL) {
        parent = tree;
        if (key < tree->key)
            tree = tree->left;
        else if (key > tree->key)
            tree = tree->right;
        else
            return;
    }

    node = bstree_create(key, value);
    node->parent = parent;
    if (key < parent->key)
        parent->left = node;
    else
        parent->right = node;
}

Bstree* bstree_lookup(Bstree* tree, int key)
{
    while (tree != NULL) {
        if (key == tree->key)
            return tree;
        else if (key < tree->key)
            tree = tree->left;
        else
            tree = tree->right;
    }

    return tree;
}

static void replace_node(Bstree* parent, Bstree* node, Bstree* child)
{
    if (parent != NULL) {
        if (node->key < parent->key)
            parent->left = child;
        else
            parent->right = child;
    }
}

Bstree* bstree_delete(Bstree* tree, int key)
{
    Bstree* node = bstree_lookup(tree, key);
    if (!node)
        return NULL;

    Bstree* parent = node->parent;
    if (node->left == NULL) {
        replace_node(parent, node, node->right);
        if (parent == NULL)
            tree = node->right;
    } else if (node->right == NULL) {
        replace_node(parent, node, node->left);
        if (parent == NULL)
            tree = node->left;
    } else {
        Bstree* min = node->right;
        while (min->left != NULL)
            min = min->left;
        replace_node(parent, node, min);
        if (parent == NULL)
            tree = min;
        if (node->right != min) {
            min->parent->left = min->right;
            min->left = node->left;
            min->right = node->right;
        } else {
            min->left = node->left;
        }
    }

    free(node);
    return tree;
}

void traverse_in_order(Bstree* tree, void (*pfun)(Bstree* tree))
{
    if (tree != NULL) {
        traverse_in_order(tree->left, pfun);
        pfun(tree);
        traverse_in_order(tree->right, pfun);
    }
}

void traverse_preorder(Bstree* tree, void (*pfun)(Bstree* tree))
{
    if (tree != NULL) {
        pfun(tree);
        traverse_preorder(tree->left, pfun);
        traverse_preorder(tree->right, pfun);
    }
}

void traverse_postorder(Bstree* tree, void (*pfun)(Bstree* tree))
{
    if (tree != NULL) {
        traverse_postorder(tree->left, pfun);
        traverse_postorder(tree->right, pfun);
        pfun(tree);
    }
}

void bstree_delete_all(Bstree* tree)
{
    if (tree != NULL) {
        bstree_delete_all(tree->left);
        bstree_delete_all(tree->right);
        free(tree);
    }
}