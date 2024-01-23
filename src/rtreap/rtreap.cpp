#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <random>

#include "rtreap.h"

std::random_device rd;
std::default_random_engine re(rd());
std::uniform_int_distribution<int> uniform_dist(0, INT32_MAX);

static RTreap* rtreap_alloc(int x)
{
    RTreap* node = (RTreap*)malloc(sizeof(RTreap));
    if (!node) {
        return NULL;
    }

    node->x = x;
    node->y = uniform_dist(re);
    node->left = NULL;
    node->right = NULL;

    return node;
}

RTreap* rtreap_create(int x)
{
    RTreap* treap = rtreap_alloc(x);
    if (!treap) {
        fprintf(stderr, "Could not alloc memory for RTreap\n");
        return NULL;
    }

    return treap;
}

RTreap* rtreap_lookup(RTreap* treap, int x)
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

void rtreap_split(RTreap* treap, int x, RTreap** treap1, RTreap** treap2)
{
    assert(treap1 && treap2);
    if (treap == NULL) {
        *treap1 = NULL;
        *treap2 = NULL;
    } else if (x > treap->x) {
        rtreap_split(treap->right, x, &treap->right, treap2);
        *treap1 = treap;
    } else {
        rtreap_split(treap->left, x, treap1, &treap->left);
        *treap2 = treap;
    }
}

void rtreap_merge(RTreap* treap1, RTreap* treap2, RTreap** treap)
{
    assert(treap);
    if (treap1 == NULL || treap2 == NULL) {
        *treap = treap1;
        if (treap1 == NULL) {
            *treap = treap2;
        }
    } else if (treap1->y > treap2->y) {
        rtreap_merge(treap1->right, treap2, &treap1->right);
        *treap = treap1;
    } else {
        rtreap_merge(treap2->left, treap1, &treap2->left);
        *treap = treap2;
    }
}

RTreap* rtreap_add(RTreap* treap, int x)
{
    assert(treap);
    RTreap *t1, *t2;
    RTreap* node = rtreap_alloc(x);
    assert(node);

    rtreap_split(treap, node->x, &t1, &t2);
    rtreap_merge(t1, node, &t1);
    rtreap_merge(t1, t2, &t1);

    return t1;
}

RTreap* rtreap_remove(RTreap* treap, int x)
{
    RTreap* t1;
    RTreap *node = treap, *parent = NULL;

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

    rtreap_merge(node->left, node->right, &t1);

    if (parent == NULL) {
        return t1;
    }

    if (parent->left == node) {
        parent->left = t1;
    } else {
        parent->right = t1;
    }

    return treap;
}

void rtreap_free(RTreap* root)
{
    if (root) {
        rtreap_free(root->left);
        rtreap_free(root->right);
        free(root);
    }
}