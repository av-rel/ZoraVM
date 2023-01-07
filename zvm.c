#include <stdio.h>
#include <stdlib.h>

#include "./include/zvm.h"

void vm_exec(Zvm *vm, Inst *inst){
    int i;
    switch(inst->op){
        case OP_Push:
            stack_push(vm, inst->val);
            break;
        case OP_Pop:
            stack_pop(vm);
            break;
        case OP_Move:
            vm->stack_size = inst->val;
            break;
        case OP_Add:
            vm->stack[vm->stack_size - 2] += vm->stack[vm->stack_size - 1];
            vm->stack_size--;
            break;
        case OP_Sub:
            vm->stack[vm->stack_size - 2] -= vm->stack[vm->stack_size - 1];
            vm->stack_size--;
            break;
        case OP_Mul:
            vm->stack[vm->stack_size - 2] *= vm->stack[vm->stack_size - 1];
            vm->stack_size--;
            break;
        case OP_Div:
            vm->stack[vm->stack_size - 2] /= vm->stack[vm->stack_size - 1];
            vm->stack_size--;
            break;
        case OP_Mod:
            vm->stack[vm->stack_size - 2] %= vm->stack[vm->stack_size - 1];
            vm->stack_size--;
            break;
        case OP_Log:
            printf("\n[Stack]:\n");
            for (i = 0; i < vm->stack_size; i++){
                printf("\t");
                printf("%d", vm->stack[i]);
                printf("\n");
            }
            break;
        default:
            printf("\nUnknown instruction\n");
            break;
    }
}

Zvm* zvm_new(){
    Zvm* _zvm = (Zvm*) calloc(1, sizeof(Zvm) * sizeof(i32) * STACK_SIZE);
    _zvm->stack_size = 0;
    return _zvm;
}

Inst *inst_new(){
    Inst *inst = (Inst*) calloc(1, sizeof(Inst)* sizeof(st));
    inst->op = OP_Log;
    inst->val = 0;
    return inst;
}

void zvm_free(Zvm* vm, Inst* inst){
    free(vm);
    free(inst);
}
