#include <stdlib.h>

#include "starlist.h"

SSList *
s_slist_append(SSList *slist, void *data)
{
  SSList *tmp = slist;
  SSList *elem = malloc(sizeof(struct SSList));

  elem->data = data;
  elem->next = NULL;

  if(!slist)
    return elem;

  while(tmp->next)
    tmp = tmp->next;
  tmp->next = elem;
  
  return slist;
}

void
s_slist_free(SSList *slist)
{
  SSList *tmp;

  while(slist) {
    tmp = slist->next;
    free(slist);
    slist = tmp;
  }
}
