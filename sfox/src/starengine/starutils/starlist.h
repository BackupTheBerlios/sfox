#ifndef STARLIST_H
#define STARLIST_H

typedef struct SSList {
  void *data;
  struct SSList *next;
} SSList;

SSList *s_slist_append(SSList *slist, void *data);
void s_slist_free(SSList *slist);

/*From GLib*/
#define s_slist_next(slist) ((slist) ? (((SSList *)(slist))->next) : NULL)

#endif
