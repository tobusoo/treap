#pragma once

typedef struct Treap {
    struct Treap* left;
    struct Treap* right;

    int x;
    int y;
} Treap;

Treap* treap_create(int x, int y);
Treap* treap_add(Treap* treap, int x, int y);
Treap* treap_lookup(Treap* treap, int x);
Treap* treap_remove(Treap* treap, int x);
void treap_split(Treap* treap, int x, Treap** left, Treap** right);
void treap_merge(Treap* treap1, Treap* treap2, Treap** treap);
void treap_free(Treap* root);
