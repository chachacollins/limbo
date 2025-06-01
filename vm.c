#include <stdio.h>
#include "vm.h"


Vm vm = {0};


void reset_stack(void)
{
    vm.stack_top = vm.stack;
}

void init_vm(void)
{
    reset_stack();
}

void free_vm(void){}

void stack_push(Value value)
{
    *vm.stack_top++ = value;
}

Value stack_pop()
{
    vm.stack_top--;
    return *vm.stack_top;
}

InterpretResult run(void)
{
    #define READ_BYTE() (*vm.ip++)
    #define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
    for(;;)
    {
        uint8_t instruction = READ_BYTE();
        switch(instruction)
        {
            case OP_CONSTANT: 
            {
                Value val = READ_CONSTANT();
                stack_push(val);
                break;
            }
            case OP_ADD: 
            {
                Value b = stack_pop();
                Value a = stack_pop();
                stack_push(a+b);
                break;
            }
            case OP_RETURN: 
            {
                printf("%g\n", stack_pop());
                return INTERPRET_OK;
            }
        }
    }
    #undef READ_BYTE
    #undef READ_CONSTANT
}


InterpretResult interpret(Chunk* chunk)
{
    vm.chunk = chunk;
    vm.ip = vm.chunk->codes;
    return run();
}
