#ifndef STARLIST_H
#define STARLIST_H

typedef struct SSList {
  void *data;
  struct SSList *next;
} SSList;

/*Add data to the end of the list*/
SSList *s_slist_append(SSList *slist, void *data);
/*Free the list(not data)*/
void s_slist_free(SSList *slist);

/*From GLib*/
#define s_slist_next(slist) ((slist) ? (((SSList *)(slist))->next) : NULL)

#endif
