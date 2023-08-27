#include "native_row_writer.h"
#include<stddef.h>
#include<stdlib.h>


void initNativeRowWriter(NativeRowWriter* writer, int32 numFields) {
    NativeRow row;
    initRowWithoutBuff(&row, numFields);
    writer->fixSize = row.bitSetWidthInBytes + 8*numFields;
    int32 roundedSize = roundNumberOfBytesToNearestWord(writer->fixSize);
    writer->buff = (byte*)malloc(sizeof(byte)*roundedSize);
    writer->buffSize = roundedSize;
    writer->cursor = roundedSize;
    /** point buff to base in row */
    row.base = writer->buff;
    row.sizeInBytes = writer->buffSize;
    writer->row = row;
}

void freeNativeRowWriter(NativeRowWriter* writer) {
    freeRow(&writer->row);
    writer->buff = NULL;
    writer->buffSize = 0;
    writer->cursor = 0;
    writer->fixSize = 0;
}

void writeShortWithWriter(NativeRowWriter* writer, int32 ordinal, int16 value) {
    writeRowField(&writer->row, ordinal, writeShortToRow, &value);
}