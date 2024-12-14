#ifndef HANDLE_MAP_H
#define HANDLE_MAP_H

struct handlemap;

struct handlemap * handlemap_init();
void handlemap_exit(struct handlemap *);

int handlemap_new(struct handlemap *, void *ud);
void * handlemap_grab(struct handlemap *, int id);
void * handlemap_release(struct handlemap *, int id);
int handlemap_list(struct handlemap *, int n, int * result);

#endif
