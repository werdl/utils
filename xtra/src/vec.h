


#ifndef _VEC_H
#define _VEC_H
#define VEC_H
#define _XTRA_VEC
#define datalength 127
#define defaultmax 16

#ifndef _STDLIB_H
#include <stdlib.h>
#endif

#ifndef _STDIO_H
#include <stdio.h>
#endif

#ifndef _STRING_H
#include <string.h>
#endif
typedef enum VectorReturn {
    VEC_SUCCESS,
    VEC_FAILURE
} XtraVectorReturn;

typedef struct {
    int length;
    int max;
    void * data[datalength];
} XtraVector;

XtraVector * NewXtraVector(int maxsize) {
    if (!maxsize) maxsize=defaultmax;
    XtraVector * TempVec=(XtraVector *)malloc(sizeof(XtraVector)+sizeof(void *)*maxsize);
    if (TempVec) {
        TempVec->max=maxsize;
        TempVec->length=0;
    }
    return TempVec;
}
XtraVectorReturn XtraVectorPush(XtraVector ** vec, void * data) {
    if ((*vec)->length+1 > (*vec)->max) {
        XtraVector * TempVec=(XtraVector *)realloc((*vec),sizeof(XtraVector)+sizeof(void *)*(*vec)->max*2);
        if (!vec) return VEC_FAILURE;
        (*vec)=TempVec;
        (*vec)->max*=2;
    }
    (*vec)->data[(*vec)->length]=data;
    ++(*vec)->length;
    return VEC_SUCCESS;
}
void * XtraVectorPop(XtraVector ** vec) {
    if ((*vec)->length==0) return NULL;
    --(*vec)->length;
    return (*vec)->data[(*vec)->length];
}
void * XtraVectorIndex(XtraVector ** vec,int index) {
    if ((*vec)->length==0 || index>=(*vec)->length) return NULL;
    return (*vec)->data[index];
} 
void XtraVectorDelete(XtraVector ** vec) {
    for (int i=(*vec)->length;i;i--) {
        (void)XtraVectorPop(vec);
    }
    free(vec);
}
XtraVector * XtraVectorDelEl(XtraVector ** vec, int el) {
    XtraVector * TempVec=NewXtraVector((*vec)->max);
    for (int i=0;i<(*vec)->length;i++) {
        if (i==el) continue;
        (void)XtraVectorPush(&TempVec,XtraVectorIndex(vec,i));
    }
    return TempVec;
}

XtraVector * XtraVectorChangeEl(XtraVector ** vec, int el, void * data) {
    XtraVector * TempVec=NewXtraVector((*vec)->max);
    for (int i=0;i<(*vec)->length;i++) {
        if (i==el) (void)XtraVectorPush(&TempVec,data);
        (void)XtraVectorPush(&TempVec,XtraVectorIndex(vec,i));
    }
    return TempVec;
}
XtraVector * XtraVectorBubbleSort(XtraVector ** vec) {
    XtraVector * oldvec;
    memcpy(oldvec,(*vec),(*vec)->length);

    for (int i=0;i<oldvec->length;i++) {
        for (int j=0;j<(oldvec->length-1);j++) {
            if (XtraVectorIndex(vec,j)>XtraVectorIndex(vec,j+1)) {
                void * temp=XtraVectorIndex(vec,j);
                XtraVectorChangeEl(vec,j,XtraVectorIndex(vec,j+1));
                XtraVectorChangeEl(vec,j+1,temp);
            }
        }
    }
    return (*vec);


}
#define _VEC_2D
typedef struct {
    int CurrWidth;
    int CurrLength;

    int MaxWidth;
    int MaxLength;
    void * data[datalength]; // void ***
} XtraVector2D;

XtraVector2D * NewXtraVector2D(int max_width, int max_length) {
    if (!max_width) max_width=defaultmax;
    if (!max_length) max_length=defaultmax;

    XtraVector2D * TempVec=(XtraVector2D *)malloc(sizeof(XtraVector2D)+sizeof(void *)*max_width*max_length);
    if (TempVec) {
        TempVec->MaxWidth=max_width;
        TempVec->MaxLength=max_width;

        TempVec->CurrWidth=0;
        TempVec->CurrLength=0;
    } else return NULL;
    return TempVec;
}
XtraVectorReturn XtraVector2DPush(XtraVector2D ** vec, void * data, int row) {
    if ((*vec)->CurrLength+1 > (*vec)->MaxLength) {
        XtraVector2D * TempVec=(XtraVector2D *)realloc((*vec),sizeof(XtraVector)+sizeof(void *)*(*vec)->MaxLength*2*(*vec)->MaxWidth);
        if (!vec) return VEC_FAILURE;
        (*vec)=TempVec;
        (*vec)->MaxLength*=2;
    }  
    if ((*vec)->CurrWidth+1 > (*vec)->MaxWidth) {
        XtraVector2D * TempVec=(XtraVector2D *)realloc((*vec),sizeof(XtraVector)+sizeof(void *)*(*vec)->MaxLength*(*vec)->MaxWidth*2);
        if (!vec) return VEC_FAILURE;
        (*vec)=TempVec;
        (*vec)->MaxLength*=2;
    }
    XtraVector * TempVec=(XtraVector *)(*vec)->data[row];
    XtraVectorPush(&TempVec, data);
    (*vec)->data[row]=TempVec;
    return VEC_SUCCESS;
}
XtraVectorReturn XtraVector2DNewRow(XtraVector2D ** vec) {
    if ((*vec)->CurrLength+1 > (*vec)->MaxLength) {
        XtraVector2D * TempVec=(XtraVector2D *)realloc((*vec),sizeof(XtraVector)+sizeof(void *)*(*vec)->MaxLength*2*(*vec)->MaxWidth);
        if (!vec) return (VEC_FAILURE);
        (*vec)=TempVec;
        (*vec)->MaxLength*=2;
    }  
    XtraVector * row=NewXtraVector((*vec)->MaxWidth);
    (*vec)->data[(*vec)->CurrLength]=row;
    ++(*vec)->CurrLength;
    return VEC_SUCCESS;
}
// void * XtraVector2DGrab(XtraVector2D ** vec, int row, int column,XtraVector2D * vecsingle) {
//     if ((*vec)->MaxLength==0 || row>=(*vec)->CurrLength) return NULL;
//     if ((*vec)->MaxWidth==0 || column>=(*vec)->CurrWidth) return NULL;
//     return XtraVectorIndex((XtraVector **)(vecsingle->data[row]),column);
// }
void * XtraVector2DGrab(XtraVector2D ** vec, int row, int col) {
    XtraVector2D * SinglePointer=*vec;
    return XtraVectorIndex((XtraVector **)&((SinglePointer)->data[row]),col);
}
XtraVectorReturn XtraVector2DSet(XtraVector2D ** vec, void * data, int row, int col) {
    XtraVector2D * SinglePointer=*vec;
    XtraVector * RowData=(XtraVector *)((SinglePointer)->data[row]);
    RowData=XtraVectorChangeEl(&RowData,col,data);
    (*vec)->data[row]=RowData;
    return VEC_SUCCESS;
}
#endif
#ifndef _MATRIX
#define _MATRIX
typedef struct {
    int rows;
    int columns;

    void * data[32][32];
} XtraMatrix;
XtraMatrix * NewXtraMatrix(int width, int length) {
    if (!width) width=defaultmax;
    if (!length) length=defaultmax;
    XtraMatrix * TempVec=(XtraMatrix *)malloc(sizeof(XtraMatrix)+sizeof(void *)*32*32);
    if (TempVec) {
        TempVec->rows=width;
        TempVec->columns=length;
    }
    return TempVec;
}
XtraVectorReturn XtraMatrixSet(XtraMatrix ** matrix,int row, int column, void * data) {
    if (row>=(*matrix)->rows || column>=(*matrix)->columns) return VEC_FAILURE;
    (*matrix)->data[row][column]=data;
    return VEC_SUCCESS;
}
void * XtraMatrixGrab(XtraMatrix ** matrix,int row, int column) {
    if (row>=(*matrix)->rows || column>=(*matrix)->columns) return NULL;
    return (*matrix)->data[row][column];
}
XtraVectorReturn XtraMatrixRemove(XtraMatrix ** matrix,int row, int column) {
    if (row>=(*matrix)->rows || column>=(*matrix)->columns) return VEC_FAILURE;
    (*matrix)->data[row][column]=NULL;
    return VEC_SUCCESS;
}
#endif