#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

/* to be altered */
unsigned hash(const char *key)
{
    unsigned h = 0, i;

    for (i = 0; i < strlen(key); ++i)
        h = (31 * h) + key[i];
    return(h);
}

unsigned find_slot(const hashtable *t, const char *key)
{
    unsigned i = hash(key) % t->n;

    /* Search until we either find the key, or find an empty slot. */
    while (strcmp(t->arr[i].key, "") != 0 && strcmp(t->arr[i].key, key) != 0)
        i = (i + 1) % t->n;
    return(i);
}

char *find_value(const hashtable *t, const char *key)
{
    unsigned i = find_slot(t, key);

    if (strcmp(t->arr[i].key, "") != 0)
        return(t->arr[i].val);
    else
        return("not found");
}

float load_factor(const hashtable *t)
{
    return(t->k / (float) t->n);
}

hashtable *add_record(hashtable *t, const char *key, const char *val)
{
    unsigned i = find_slot(t, key);

    if (strcmp(t->arr[i].key, "") != 0) { /* we found our key */
        strcpy(t->arr[i].val, val);
        return(t);
    }
    if (load_factor(t) >= 0.75) {
        t = rebuild(t);
        i = find_slot(t, key);
    }
    ++(t->k);
    strcpy(t->arr[i].key, key);
    strcpy(t->arr[i].val, val);
    print_table(t);
    return(t);
}

hashtable *read_records(hashtable *t, unsigned n, const char *filename)
{
    unsigned i;
    char key[256], val[256];
    FILE *infile = fopen(filename, "r");

    for (i = 0; i < n; ++i) {
        fscanf(infile, " %[^\t] %[^\n]", key, val);
        if (feof(infile))
            break;
        t = add_record(t, key, val);
    }
    fclose(infile);
    return(t);
}

hashtable *initialize(hashtable *t)
{
    t->k = 0;
    t->n = 4;
    t->arr = (slot *) malloc(t->n * sizeof(slot));
    memset(t->arr, 0, t->n * sizeof(slot));
    return(t);
}

hashtable *rebuild(hashtable *t)
{
    unsigned i;
    hashtable *newtab = (hashtable *) malloc(sizeof(hashtable));

    newtab->k = 0;
    newtab->n = 2 * t->n;
    newtab->arr = (slot *) malloc(newtab->n * sizeof(slot));
    memset(newtab->arr, 0, 2 * t->n * sizeof(slot));
    for (i = 0; i < t->n; ++i)
        if (strcmp(t->arr[i].key, "") != 0)
            newtab = add_record(newtab, t->arr[i].key, t->arr[i].val);
    t = delete_table(t);
    t->k = newtab->k;
    t->n = newtab->n;
    t->arr = newtab->arr;
    free(newtab);
    return(t);
}

hashtable *delete_table(hashtable *t)
{
    t->k = 0;
    t->n = 0;
    free(t->arr);
    t->arr = (slot *) NULL;
    return(t);
}

void print_table(const hashtable *t)
{
    unsigned i;

    for (i = 0; i < t->n; ++i) {
        printf("%d ", i);
        if (strcmp(t->arr[i].key, "") != 0)
            printf("%s: %s", t->arr[i].key, t->arr[i].val);
        putchar('\n');
    }
    printf("k = %d, n = %d, load = %f\n\n", t->k, t->n, load_factor(t));
}
