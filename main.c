#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"

int main(int argc, const char* argb[]) {
  initVM();
  
  Chunk chunk;
  initChunk(&chunk);

  /* Chapter 14 test */
     int constant = addConstant(&chunk, 1.2);
     writeChunk(&chunk, OP_CONSTANT, 123);
     writeChunk(&chunk, constant, 123);
     writeChunk(&chunk, OP_RETURN, 123);
  //  */

  /* test for challenge 14.1
     int constant = addConstant(&chunk, 1.2);
     writeChunk(&chunk, OP_CONSTANT, 1);
     writeChunk(&chunk, constant, 1);
     writeChunk(&chunk, OP_RETURN, 1);
     writeChunk(&chunk, OP_RETURN, 4);
     writeChunk(&chunk, OP_RETURN, 4);
     writeChunk(&chunk, OP_RETURN, 5);
     writeChunk(&chunk, OP_RETURN, 9);
     writeChunk(&chunk, OP_RETURN, 9); */
    
  // disassembleChunk(&chunk, "test chunk");
  interpret(&chunk);
  
  freeVM();
  freeChunk(&chunk);
  return 0;
}
