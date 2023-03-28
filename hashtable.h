/* Open addressing and linear probing hash table implementation. */
#ifndef HASHTABLE_H
#define HASHTABLE_H

struct slot {
    char key[256];
    char val[256];
};
typedef struct slot slot;

struct hashtable {
    unsigned k, n;
    slot *arr;
};
typedef struct hashtable hashtable;

unsigned hash(const char *);
unsigned find_slot(const hashtable *, const char *);
char *find_value(const hashtable *, const char *);
float load_factor(const hashtable *);
hashtable *add_record(hashtable *, const char *, const char *);
hashtable *read_records(hashtable *, unsigned, const char *);
hashtable *initialize(hashtable *);
hashtable *rebuild(hashtable *);
hashtable *delete_table(hashtable *);
void print_table(const hashtable *);

#endif
