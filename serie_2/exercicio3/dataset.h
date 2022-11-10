#ifndef DATASET_H
#define DATASET_H

typedef struct { char label[7]; short value; } Data;

#define A

#ifdef A
typedef struct { const int *id; unsigned length; Data **data; } Dataset;
#else
typedef struct { const int *id; unsigned length; Data *data[7]; } Dataset;
#endif

#endif
