#pragma once

class RecvTable;
class RecvProp;

class RecvProp
{
public:
    char* varName;
    char pad0[4];
    int flags;
    int stringBufferSize;
    int bInsideArray;
    const void* extraData;
    RecvProp* pArrayProp;
    char pad1[12];
    RecvTable* pDataTable;
    int offset;
    int elementStride;
    int nElements;
    const char* pParentArrayPropName;
};

class RecvTable
{
public:
    RecvProp* pProps;
    int nProps;
    void* pDecoder;
    char* netTableName;
};