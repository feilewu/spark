#include "native_row.h"

typedef struct _native_row_writer
{
    NativeRow row;

    byte* buff;

    int32 buffSize;

    int32 fixSize;

    /** 变长部分指向当前已写末尾 */
    int32 cursor;

} NativeRowWriter;

void initNativeRowWriter(NativeRowWriter* writer, int32 numFields);

void freeNativeRowWriter(NativeRowWriter* writer);

void writeShortWithWriter(NativeRowWriter* writer, int32 ordinal, int16 value);






