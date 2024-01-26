#pragma once

typedef struct bstree {
    int key;
    char* value;

    struct bstree* parent;
    struct bstree* right;
    struct bstree* left;
} Bstree;

Bstree* bstree_create(int key, char* value);
void bstree_add(Bstree* tree, int key, char* value);
Bstree* bstree_lookup(Bstree* tree, int key);
Bstree* bstree_delete(Bstree* tree, int key);
Bstree* bstree_min(Bstree* tree);
Bstree* bstree_max(Bstree* tree);
void traverse_in_order(Bstree* tree, void (*pfun)(Bstree* tree));
void traverse_postorder(Bstree* tree, void (*pfun)(Bstree* tree));
void traverse_preorder(Bstree* tree, void (*pfun)(Bstree* tree));
void bstree_delete_all(Bstree* tree);
