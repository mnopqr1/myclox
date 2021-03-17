#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"

int main(int argc, const char* argb[]) {
  initVM();
  
  Chunk chunk;
  initChunk(&chunk);

  /* Chapter 14 test 
     int constant = addConstant(&chunk, 1.2);
     writeChunk(&chunk, OP_CONSTANT, 123);
     writeChunk(&chunk, constant, 123);
     writeChunk(&chunk, OP_RETURN, 123);
  */

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

  /* My test for 15.2 
  int constant1 = addConstant(&chunk, 1000);
  int constant2 = addConstant(&chunk, 2000);

  writeChunk(&chunk, OP_CONSTANT, 1);
  writeChunk(&chunk, constant1, 1);
  writeChunk(&chunk, OP_CONSTANT, 2);
  writeChunk(&chunk, constant2, 2);
  writeChunk(&chunk, OP_NEGATE, 2);
  writeChunk(&chunk, OP_RETURN, 3); */

  /* Test for 15.3 */
  /* return -((1.2 + 3.4) / 5.6) */
  /* int constant = addConstant(&chunk, 1.2);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);
  
  constant = addConstant(&chunk, 3.4);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);

  writeChunk(&chunk, OP_ADD, 123);

  constant = addConstant(&chunk, 5.6);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);

  writeChunk(&chunk, OP_DIVIDE, 123);
  writeChunk(&chunk, OP_NEGATE, 123);

  writeChunk(&chunk, OP_RETURN, 123); */

  /* Challenge 15.1 */
  // 1 * 2 + 3
  int constant = addConstant(&chunk, 1);
  writeChunk(&chunk, OP_CONSTANT, 100);
  writeChunk(&chunk, constant, 100);

  int constant2 = addConstant(&chunk, 2);
  writeChunk(&chunk, OP_CONSTANT, 100);
  writeChunk(&chunk, constant2, 100);

  writeChunk(&chunk, OP_MULTIPLY, 100);

  int constant3 = addConstant(&chunk, 3);
  writeChunk(&chunk, OP_CONSTANT, 100);
  writeChunk(&chunk, constant3, 100);

  writeChunk(&chunk, OP_ADD, 100);

  // writeChunk(&chunk, OP_RETURN, 100);
  
  // 1 + 2 * 3
  constant = addConstant(&chunk, 1);
  writeChunk(&chunk, OP_CONSTANT, 200);
  writeChunk(&chunk, constant, 200);

  constant = addConstant(&chunk, 2);
  writeChunk(&chunk, OP_CONSTANT, 200);
  writeChunk(&chunk, constant, 200);
  
  constant = addConstant(&chunk, 3);
  writeChunk(&chunk, OP_CONSTANT, 200);
  writeChunk(&chunk, constant, 200);
  writeChunk(&chunk, OP_MULTIPLY, 200);

  writeChunk(&chunk, OP_ADD, 200);
  writeChunk(&chunk, OP_RETURN, 200);
  
  interpret(&chunk); 
  
  freeVM();
  freeChunk(&chunk);
  return 0;
}
