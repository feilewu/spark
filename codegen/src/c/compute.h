#include "native_row_writer.h"

typedef struct _batch_builder
{
    NativeRowBatch batch;

    /** size of rows which have been written into batch */
    int cursor;

} BatchBuilder;


NativeRowBatch compute(NativeRowBatch batch);