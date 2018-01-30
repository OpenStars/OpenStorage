
namespace cpp bskv

typedef binary TItemKey //key - index of an item, with simple set, itemkey is equivalent to item

struct TItem{
    1: required binary key,
    2: required binary value
}

typedef i64 TContainerKey

typedef TContainerKey TSmallSetIDKey


struct TItemSet{
    1: list<TItem> items
}

typedef TContainerKey TMetaKey


enum TErrorCode{
    EGood = 0,
    ENoRootMeta = 1,
    ECouldNotConnectMetadata = 2,
    ECouldNotConnectIDGen = 3,
    ECouldNotConnectSmallSet = 4,
    ECouldNotConnectRootMetaMapping = 5,
    EItemNotExisted = 100,
    EUnknownException = 10,

    EBigSetNotExisted = 101, // not existed bigset with specific name
    EBigSetCreated, // created new bigset ID
    EBigSetAlreadyExisted,
    EBigSetAssigned, //assigned a bigset name to a specific IDs.
}

struct TItemResult{
    1: TErrorCode error, // 0: ok, -1 : error
    2: optional TItem item
}

struct TItemSetResult{
    1: TErrorCode error,
    2: optional TItemSet items,
}

struct TPutItemResult{
    1: TErrorCode error, // 0: ok, -1 : error
    2: bool ok,
    3: optional TItem oldItem,
}

struct TExistedResult{
    1: TErrorCode error, // 0: ok, -1 : error
    2: bool existed
}

struct TMultiPutItemResult{
    1: TErrorCode error,
    2: optional list<TItemKey> added,
    3: optional list<TItem> replaced, // old items were replaced by operation
}



service RawBigSetKVService{

    TPutItemResult bsgPutItem(1:TContainerKey rootID, 2:TItem item),

    /*return true if item is existed in the list otherwise return false*/
    bool bsgRemoveItem(1:TMetaKey key, 2:TItemKey itemKey),

    TExistedResult bsgExisted(1:TContainerKey rootID, 2: TItemKey itemKey),

    TItemResult bsgGetItem(1:TContainerKey rootID, 2: TItemKey itemKey),

    TItemSetResult bsgGetSlice(1:TContainerKey rootID, 2: i32 fromIdx, 3: i32 count)

    TItemSetResult bsgGetSliceFromItem(1:TContainerKey rootID, 2: TItemKey fromKey, 3: i32 count)

    TItemSetResult bsgGetSliceR(1:TContainerKey rootID, 2: i32 fromIdx, 3: i32 count)

    TItemSetResult bsgGetSliceFromItemR(1:TContainerKey rootID, 2: TItemKey fromKey, 3: i32 count)

    TItemSetResult bsgRangeQuery(1:TContainerKey rootID, 2: TItemKey startKey, 3: TItemKey endKey),

    TMultiPutItemResult bsgMultiPut(1: TContainerKey rootID, 2: TItemSet setData, 3: bool getAddedItems, 4: bool getReplacedItems ),

    i64 getTotalCount(1:TContainerKey rootID),

    i64 removeAll(1:TContainerKey rootID)

}

typedef string TStringKey
typedef i64 TKey

service TStringBigSetKVService{

    TPutItemResult bsPutItem(1:TStringKey bsName, 2:TItem item),

    /*return true if item is existed in the list otherwise return false*/
    bool bsRemoveItem(1:TStringKey bsName, 2:TItemKey itemKey),

    TExistedResult bsExisted(1:TStringKey bsName, 2: TItemKey itemKey),

    TItemResult bsGetItem(1:TStringKey bsName, 2: TItemKey itemKey),

    TItemSetResult bsGetSlice(1:TStringKey bsName, 2: i32 fromPos, 3: i32 count)

    TItemSetResult bsGetSliceFromItem(1:TStringKey bsName, 2: TItemKey fromKey, 3: i32 count)

    TItemSetResult bsGetSliceR(1:TStringKey bsName, 2: i32 fromPos, 3: i32 count)

    TItemSetResult bsGetSliceFromItemR(1:TStringKey bsName, 2: TItemKey fromKey, 3: i32 count)

    TItemSetResult bsRangeQuery(1:TStringKey bsName, 2: TItemKey startKey, 3: TItemKey endKey),


    TMultiPutItemResult bsMultiPut(1: TStringKey bsName, 2: TItemSet setData, 3: bool getAddedItems, 4: bool getReplacedItems ),

    i64 getTotalCount(1:TStringKey bsName),

    i64 removeAll(1:TStringKey bsName)

}


/* 
* BigSet with Int BigSetID key-value items
* This is a interface of a safer big set (a bit slower)
* Non-ProProfessional should use it instead of TBSGenericDataService directly
*/
service TIBSDataService{

    TPutItemResult putItem(1:TKey bigsetID, 2:TItem item),

    /*return true if item is existed in the list otherwise return false*/
    bool removeItem(1:TKey bigsetID, 2:TItemKey itemKey),

    TExistedResult existed(1:TKey bigsetID, 2: TItemKey itemKey),

    TItemResult getItem(1:TKey bigsetID, 2: TItemKey itemKey),

    TItemSetResult getSlice(1:TKey bigsetID, 2: i32 fromPos, 3: i32 count)

    TItemSetResult getSliceFromItem(1:TKey bigsetID, 2: TItemKey fromKey, 3: i32 count)

    TItemSetResult getSliceR(1:TKey bigsetID, 2: i32 fromPos, 3: i32 count)

    TItemSetResult getSliceFromItemR(1:TKey bigsetID, 2: TItemKey fromKey, 3: i32 count)

    TItemSetResult rangeQuery(1:TKey bigsetID, 2: TItemKey startKey, 3: TItemKey endKey),

    TMultiPutItemResult multiPut(1: TKey bigsetID, 2: TItemSet setData, 3: bool getAddedItems, 4: bool getReplacedItems ),
    
    i64 getTotalCount(1:TKey bigsetID),

    i64 removeAll(1:TKey bigsetID)


}