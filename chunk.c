#include <stdlib.h>
/* #include <stdio.h> // (debugging only) */ 

#include "chunk.h"
#include "memory.h"

void initChunk(Chunk* chunk) {
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;

    // run-length encoding of line numbers (Challenge 14.1)
    // example: after passing to addLine as line values 1, 1, 1, 4, 4, 5, 9, 9, 9, 9, 9
    // we get lines = [1, 4, 5, 9] and instructioncount = [3, 5, 6, 11] 
    chunk->linecapacity = 0;         // capacity of lines and instructioncount arrays
    chunk->linerun = -1;             // what run are we at
    chunk->lines = NULL;             // stores linenumber
    chunk->instructioncount = NULL;  // instructioncount[i] is the number of instructions up to linenumber lines[i], inclusive

    
    initValueArray(&chunk->constants);
}

void freeChunk(Chunk* chunk) {
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);

    FREE_ARRAY(int, chunk->lines, chunk->linecapacity);
    FREE_ARRAY(int, chunk->instructioncount, chunk->linecapacity);

    freeValueArray(&chunk->constants);
    initChunk(chunk);
}

int getLine(Chunk* chunk, int instruction) {
    int idx = 0;
    while (idx <= chunk->linerun && chunk->instructioncount[idx] <= instruction) idx++;
    if (idx > chunk->linerun) {
        return -1;               // the value of instruction was higher than the last instruction we read
    }
    else {
        return chunk->lines[idx];
    }
}
void addLine(Chunk* chunk, int line) {
    if (chunk->linerun >= 0 && chunk->lines[chunk->linerun] == line) {
        chunk->instructioncount[chunk->linerun]++;
    }
    else
    {
        chunk->linerun++;
        if (chunk->linecapacity < chunk->linerun + 1) {
            int oldLinecapacity = chunk->linecapacity;
            chunk->linecapacity = GROW_CAPACITY(oldLinecapacity);
            chunk->lines = GROW_ARRAY(int, chunk->lines, oldLinecapacity, chunk->linecapacity);
            chunk->instructioncount = GROW_ARRAY(int, chunk->instructioncount, oldLinecapacity, chunk->linecapacity);
        }
        chunk->lines[chunk->linerun] = line;
        chunk->instructioncount[chunk->linerun] = chunk->linerun > 0 ?
                                                  chunk->instructioncount[chunk->linerun - 1] + 1 :
                                                  1;
    }
    /* printf("Added one instruction at line %d. Now linerun = %d, lines[linerun] = %d, and lines[instructioncount] = %d.\n", 
       line, chunk->linerun, chunk->lines[chunk->linerun], chunk->instructioncount[chunk->linerun]); */
}

void writeChunk(Chunk* chunk, uint8_t byte, int line) {
    if (chunk->capacity < chunk->count + 1) {
        int oldCapacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(oldCapacity);
        chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);
    }

    chunk->code[chunk->count] = byte;
    // chunk->lines[chunk->count] = line;
    addLine(chunk, line);
    chunk->count++;
}

int addConstant(Chunk* chunk, Value value)
{
    writeValueArray(&chunk->constants, value);
    return chunk->constants.count - 1;
}
