#include<stddef.h>
#include<stdlib.h>

typedef char byte;

typedef short int16;

typedef int int32;

typedef long long int64;

typedef struct _native_row
{
    /** 数组指针 */
    byte* base;

    /** 数组长度 */
    int32 sizeInBytes;

    int32 numFields;

    int32 bitSetWidthInBytes;

} NativeRow;

int32 getFieldOffset(NativeRow* row, int32 ordinal);

int32 calculateBitSetWidthInBytes(int32 numFields);

int64 roundNumberOfBytesToNearestWord(int64 numBytes);

void initRowWithoutBuff(NativeRow* rowPtr, int32 numFields);

void initRowWithBuff(NativeRow* rowPtr, int32 numFields);

void freeRow(NativeRow* row);

void freeRows(NativeRow* rows, int32 len);

typedef void (*ReadRowFieldFunc)(NativeRow*,int32,void*);

void readRowField(NativeRow* row, int32 ordinal, ReadRowFieldFunc func, void* result);

void readShortFromRow(NativeRow* row, int32 ordinal, void* result);

typedef void (*WriteRowFieldFunc)(NativeRow*,int32,void*);

void writeRowField(NativeRow* row, int32 ordinal, WriteRowFieldFunc func, void* input);

void writeShortToRow(NativeRow* row, int32 ordinal, void* input);

typedef struct _native_row_batch
{
    
    NativeRow* rows;

    int32 len;

} NativeRowBatch;


void initNativeRowBatch(NativeRowBatch* batch, int32 len);

void freeNativeRowBatch(NativeRowBatch batch);





