#include "native_row.h"


int32 getFieldOffset(NativeRow* row, int32 ordinal) {
  return row->bitSetWidthInBytes + ordinal * 8;
}

int32 calculateBitSetWidthInBytes(int32 numFields) {
    return (int32)((((int64)numFields + 63)/ 64) * 8);
}

int64 roundNumberOfBytesToNearestWord(int64 numBytes) {
    int64 remainder = numBytes & 0x07;  // This is equivalent to `numBytes % 8`
    if (remainder == 0) {
      return numBytes;
    } else {
      return numBytes + (8 - remainder);
    }
}

void initRowWithoutBuff(NativeRow* rowPtr, int32 numFields) {
    rowPtr->base=NULL;
    rowPtr->bitSetWidthInBytes = calculateBitSetWidthInBytes(numFields);
    rowPtr->numFields = numFields;
    rowPtr->sizeInBytes = 0;
}

void initRowWithBuff(NativeRow* rowPtr, int32 numFields) {
  initRowWithoutBuff(rowPtr, numFields);
  int32 roundedSize = rowPtr->bitSetWidthInBytes + roundNumberOfBytesToNearestWord(numFields);
  rowPtr->base = (byte*)malloc(sizeof(byte)*roundedSize);
  rowPtr->sizeInBytes = roundedSize;
}

void freeRow(NativeRow* row) {
  if (row == NULL) {
    return;
  } 
  if (row->base != NULL) {
    free(row->base);
    row->base = NULL;
  }
  row->bitSetWidthInBytes = 0;
  row->numFields = 0;
  row->sizeInBytes = 0;
}

void freeRows(NativeRow* rows, int32 len) {
  if (rows == NULL) {
    return;
  }
  for(int i= 0;i<len;i++) {
    freeRow(rows+i);
  }
}


void readShortFromRow(NativeRow* row, int32 ordinal, void* result) {
    byte* base = row->base;
    int32 offset = getFieldOffset(row, ordinal);
    short low = *(base+offset) & 0xff;
    short high = *(base+offset+1);
    *((short*)result) = high << 8 | low;
}

void readRowField(NativeRow* row, int32 ordinal, ReadRowFieldFunc func, void* result) {
    func(row, ordinal, result);
}

void writeRowField(NativeRow* row, int32 ordinal, WriteRowFieldFunc func, void* input) {
    func(row, ordinal, input);
}

void writeShortToRow(NativeRow* row, int32 ordinal, void* input) {
  short value = *((short*)input);
  byte* base = row->base;
  int32 offset = getFieldOffset(row, ordinal);
  *(base+offset) = (value << 8) >> 8;
  *(base+offset+1) = value >> 8;
}


void initNativeRowBatch(NativeRowBatch* batch, int32 len) {
  batch->len = len;
  if (len == 0){
    batch->rows = NULL;
  } else {
    batch->rows = malloc(sizeof(NativeRow)*len);
  } 
}

void freeNativeRowBatch(NativeRowBatch batch) {
  if (batch.rows == NULL) {
    return;
  }
  int32 len = batch.len;
  for(int i=0;i<len;i++){
    NativeRow row = *(batch.rows+i);
    freeRow(&row);
  }
  free(batch.rows);
  batch.rows = NULL;
  batch.len = 0;
}