#ifndef QUADTREE_H
#define QUADTREE_H

#include "bbox.h"

typedef struct s_quadtree_node {
  bbox2d box;
  struct s_quadtree_node *childs[4];
  void *data;
} *quadtree_node;


extern quadtree_node quadtree_create(double tlx, double tly, double brx, double bry, unsigned int level);
/*Do node->data=f(node,data) for each leaf*/
extern void quadtree_foreach_leaf(quadtree_node node, void *data, void (*f)(quadtree_node , void *));
#endif
