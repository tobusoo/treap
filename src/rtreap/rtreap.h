#pragma once

typedef struct RTreap {
    struct RTreap* left;
    struct RTreap* right;

    int x;
    int y;
} RTreap;

RTreap* rtreap_create(int x);
RTreap* rtreap_add(RTreap* root, int x);
RTreap* rtreap_lookup(RTreap* root, int x);
RTreap* rtreap_remove(RTreap* root, int x);
void rtreap_split(RTreap* treap, int x, RTreap** left, RTreap** right);
void rtreap_merge(RTreap* treap1, RTreap* treap2, RTreap** treap);
void rtreap_free(RTreap* root);