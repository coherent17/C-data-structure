#ifndef _RBT_H_
#define _RBT_H_

#include <stdlib.h>

typedef enum _rb_color{
    RED = 0,
    BLACK = 1
}rb_color;

typedef struct _rb_node{
    int key;
    rb_color color;
    struct _rb_node *left;
    struct _rb_node *right;
    struct _rb_node *parent;
}rb_node;


#endif