#include <stdio.h>
#include "hashtable.h"

int main()
{
    char key[256];
    hashtable table = *initialize(&table);

    table = *read_records(&table, 48, "states.dat");
    print_table(&table);
    printf("Key: ");
    scanf(" %[^\n]", key);
    printf("Value: %s\n", find_value(&table, key));
    table = *delete_table(&table);
    return(0);
}
