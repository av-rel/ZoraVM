#define ZORAVM_LOG 1

#include "./zoravm.c"

int usage(char** argv) {
  return -1;
}

int main(int argc, char** argv) {

  ZoraVM_Program program[] = {
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

  return ZoraVME(program, sizeof(program)/sizeof(program[0]));
}

