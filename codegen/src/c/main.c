#include<stdio.h>
#include<assert.h>
#include "native_row_writer.h"


void testRowBaseWriteAndRead() {

    printf("begin to testRowBaseWriteAndRead() \n");

    NativeRow row;
    initRowWithBuff(&row, 2);
    short shortInput = (short)-123;
    writeRowField(&row,0,writeShortToRow,&shortInput);

    short ShortOutput = 0;
    readRowField(&row,0,readShortFromRow,&ShortOutput);
    printf("read short from row: %d\n", ShortOutput);

    assert(shortInput == ShortOutput);

    freeRow(&row);
    printf("testRowBaseWriteAndRead() end! \n");
}

void testRowWriter() {

    printf("begin to testRowWriter() \n");

    NativeRowWriter writer;
    initNativeRowWriter(&writer,2);

    short shortInput = 20;
    writeShortWithWriter(&writer,0,shortInput);

    short shortOutput = 0;
    readRowField(&writer.row, 0, readShortFromRow, &shortOutput);

    assert(shortInput == shortOutput);
    freeNativeRowWriter(&writer);

    printf("testRowWriter() end! \n");
}


int main(){
   printf("hello world!\n");
   testRowBaseWriteAndRead();
   testRowWriter();
   return 0;
}