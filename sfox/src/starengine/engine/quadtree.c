#include <stdlib.h>

#include "quadtree.h"

quadtree_node
quadtree_create(double tlx, double tly, double brx, double bry, unsigned int level)
{
  quadtree_node root;
  double midx = (brx+tlx)/2.0f;
  double midy = (bry+tly)/2.0f;

  if(level == 0)
    return NULL;

  root = calloc(1, sizeof(struct s_quadtree_node));
  bbox2d_set(&root->box, tlx, tly, brx, bry);

  root->childs[0] = quadtree_create(tlx, tly, midx, midy, level-1);
  root->childs[1] = quadtree_create(midx, tly, brx, midy, level-1);
  root->childs[2] = quadtree_create(tlx, midy, midx, bry, level-1);
  root->childs[3] = quadtree_create(midx, midy, brx, bry, level-1);

  return root;
}

void
quadtree_foreach_leaf(quadtree_node node, void *data, void(*f)(quadtree_node , void *))
{
  if(node->childs[0] == NULL || node->childs[1] == NULL ||
     node->childs[2] == NULL || node->childs[3] == NULL) {
    f(node, data);
    return;
  }

  quadtree_foreach_leaf(node->childs[0], data, f);
  quadtree_foreach_leaf(node->childs[1], data, f);
  quadtree_foreach_leaf(node->childs[2], data, f);
  quadtree_foreach_leaf(node->childs[3], data, f);
}
