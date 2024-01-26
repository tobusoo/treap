#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "treap.h"

static Treap* treap_alloc(int x, const char* value)
{
    Treap* node = (Treap*)malloc(sizeof(Treap));
    if (!node) {
        return NULL;
    }

    node->x = x;
    node->y = rand();
    node->value = strdup(value);
    node->left = NULL;
    node->right = NULL;

    assert(node->value);
    return node;
}

Treap* treap_create(int x, const char* value)
{
    Treap* treap = treap_alloc(x, value);
    if (!treap) {
        fprintf(stderr, "Could not alloc memory for Treap\n");
        return NULL;
    }

    return treap;
}

Treap* treap_lookup(Treap* treap, int x)
{
    while (treap) {
        if (x == treap->x)
            return treap;
        else if (x < treap->x)
            treap = treap->left;
        else
            treap = treap->right;
    }

    return NULL;
}

void treap_split(Treap* treap, int x, Treap** treap1, Treap** treap2)
{
    assert(treap1 && treap2);
    if (treap == NULL) {
        *treap1 = NULL;
        *treap2 = NULL;
    } else if (x > treap->x) {
        treap_split(treap->right, x, &treap->right, treap2);
        *treap1 = treap;
    } else {
        treap_split(treap->left, x, treap1, &treap->left);
        *treap2 = treap;
    }
}

void treap_merge(Treap* treap1, Treap* treap2, Treap** treap)
{
    assert(treap);
    if (treap1 == NULL || treap2 == NULL) {
        *treap = treap1;
        if (treap1 == NULL) {
            *treap = treap2;
        }
    } else if (treap1->y > treap2->y) {
        treap_merge(treap1->right, treap2, &treap1->right);
        *treap = treap1;
    } else {
        treap_merge(treap2->left, treap1, &treap2->left);
        *treap = treap2;
    }
}

Treap* treap_add(Treap* treap, int x, const char* value)
{
    assert(treap);
    Treap *t1, *t2;
    Treap* node = treap_alloc(x, value);
    assert(node);

    treap_split(treap, node->x, &t1, &t2);
    treap_merge(t1, node, &t1);
    treap_merge(t1, t2, &t1);

    return t1;
}

Treap* treap_remove(Treap* treap, int x)
{
    Treap* t1;
    Treap *node = treap, *parent = NULL;

    while (node) {
        if (x == node->x)
            break;
        else if (x < node->x) {
            parent = node;
            node = node->left;
        } else {
            parent = node;
            node = node->right;
        }
    }
    if (!node)
        return treap;

    treap_merge(node->left, node->right, &t1);

    if (parent == NULL) {
        free(node->value);
        free(node);
        return t1;
    }

    if (parent->left == node) {
        parent->left = t1;
    } else {
        parent->right = t1;
    }

    free(node->value);
    free(node);

    return treap;
}

void treap_free(Treap* root)
{
    if (root) {
        treap_free(root->left);
        treap_free(root->right);
        free(root->value);
        free(root);
    }
}