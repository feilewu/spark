typedef char byte;

typedef int int32;


typedef struct _native_row
{
    /** 数组指针 */
    byte* base;

    /** 数组长度 */
    int32 sizeInBytes;

    int32 numFields;

    int32 bitSetWidthInBytes;

} NativeRow;


typedef struct _native_row_batch
{
    
    NativeRow* rows;

    int32 len;

} NativeRowBatch;




