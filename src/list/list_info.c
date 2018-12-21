#include <type.h>
#include <list/list.h>

unsigned long long len(List *p_list) {
    return p_list->length;
}

int isListEmpty(List *p_list) {
    if (p_list->head == NULL || p_list->tail == NULL)// If its head or tail is NULL,it would be thought as empty.
        return 1;                // But we should ensure that both of them are NULL when we
    return 0;                    // want to make a list empty.
}
