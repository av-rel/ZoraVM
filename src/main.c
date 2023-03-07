#include "inst.h"
#define ZORAVM_LOG 1
#define ZORASM_LOG 1

#include "./zoravm.c"
#include "./inst.c"

int usage(char** argv) {
  return -1;
}

#define MEMORY 1024

int main(int argc, char** argv) {

  ZoraVM_Program loop[] = {
    ZoraVM_PushInt(33),
    ZoraVM_Store(0),
    ZoraVM_Load(0),
    ZoraVM_Dec(),
    ZoraVM_Store(0),
    ZoraVM_Load(0),
    ZoraVM_Print(),
    ZoraVM_PushStr("\n"),
    ZoraVM_Print(),
    ZoraVM_Load(0),
    ZoraVM_PushInt(10),
    ZoraVM_CmpGt(),
    ZoraVM_JmpIf(2),
    ZoraVM_PushStr("Loop end!\n"),
    ZoraVM_Print(),
    ZoraVM_Halt(0),					
  };

  ZoraVM_Program scan[] = {
    ZoraVM_Scan(),
    ZoraVM_Print(),
    ZoraVM_Halt(0)
  };

#define program loop

  return ZoraVME(program, sizeof(program)/sizeof(program[0]), MEMORY);
}

