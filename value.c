#include "value.h"
#include "memory.h"

void init_value_array(ValueArray *v_arr)
{
    v_arr->len = 0; 
    v_arr->capacity = 0;
    v_arr->values = NULL;
}

void add_value(ValueArray *v_arr, Value value)
{
    if(v_arr->len + 1 > v_arr->capacity)
    {
        v_arr->capacity = GROW_SIZE(v_arr->capacity);
        v_arr->values = ALLOCATE(Value, v_arr->values, v_arr->capacity);
    }
    v_arr->values[v_arr->len++] = value;
}

void free_value_arr(ValueArray *v_arr)
{
    FREE(v_arr->values);
    init_value_array(v_arr);
}
