#ifndef VALUE_H
#define VALUE_H

typedef double Value;

typedef struct {
    unsigned int len;
    unsigned int capacity;
    Value* values;
} ValueArray;

void init_value_array(ValueArray *v_arr);
void add_value(ValueArray *v_arr, Value value);
void free_value_arr(ValueArray *v_arr);

#endif
