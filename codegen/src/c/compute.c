#include "compute.h"
#include<string.h>
#include<stdio.h>

void appendRow(BatchBuilder* builder, NativeRow* row) {

  NativeRowBatch* batch = &builder->batch;

  if (builder->cursor == batch->len) {
    int32 size = sizeof(NativeRow)*(batch->len)*1.5;
    NativeRow* rows = (NativeRow*)malloc(size);
    memset(rows,0,size);
    memcpy(rows, batch->rows, batch->len*sizeof(NativeRow));
    free(batch->rows);
    batch->rows = rows;
    batch->len = size;
  }

  *(batch->rows+builder->cursor) = *row;
  builder->cursor = builder->cursor + 1;

}

void initBatchBuilder(BatchBuilder* builder) {
  NativeRowBatch batch;
  initNativeRowBatch(&batch,8);
  builder->batch = batch;
  builder->cursor = 0;
}

void freeBatchBuilder(BatchBuilder* builder) {
  if (builder->batch.rows != NULL) {
    freeRows(builder->batch.rows, builder->cursor);
    free(builder->batch.rows);
  }
}

NativeRowBatch getNativeRowBatch(BatchBuilder* batchBuilder) {
  NativeRowBatch batch;
  initNativeRowBatch(&batch, batchBuilder->cursor);
  if (batchBuilder->cursor != 0) {
    memcpy(batch.rows,batchBuilder->batch.rows,batchBuilder->cursor*sizeof(NativeRow)); 
  }
  return batch;
}


NativeRow doCompute(NativeRow* row);

NativeRowBatch compute(NativeRowBatch batch){

  int len = batch.len;
  NativeRow* rows = batch.rows;

  BatchBuilder batchBuilder;
  initBatchBuilder(&batchBuilder);

  for (int i=0;i<len;i++) {
    
    NativeRow row = doCompute(rows+i);
    if (row.sizeInBytes != 0) {
      appendRow(&batchBuilder, &row);
    }
    
  }
  NativeRowBatch result = getNativeRowBatch(&batchBuilder);
  /** must not free row, just free the memory of row array */
  free(batchBuilder.batch.rows);
  return result;
}


NativeRow doCompute(NativeRow* inputRow) {
  NativeRow row;
  initRowWithBuff(&row,1);
  short value = (short)100;
  writeShortToRow(&row, 0, &value);
  return row;
}