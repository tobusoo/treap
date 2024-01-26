#pragma once

typedef struct Treap {
    struct Treap* left;
    struct Treap* right;

    int x;
    int y;

    char* value;
} Treap;

Treap* treap_create(int key, const char* value);
Treap* treap_add(Treap* root, int key, const char* value);
Treap* treap_lookup(Treap* root, int key);
Treap* treap_remove(Treap* root, int key);
void treap_split(Treap* treap, int key, Treap** left, Treap** right);
void treap_merge(Treap* treap1, Treap* treap2, Treap** treap);
void treap_free(Treap* root);