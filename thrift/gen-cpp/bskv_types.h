/**
 * Autogenerated by Thrift Compiler (0.11.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef bskv_TYPES_H
#define bskv_TYPES_H

#include <iosfwd>

#include <thrift/Thrift.h>
#include <thrift/TApplicationException.h>
#include <thrift/TBase.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TTransport.h>

#include <thrift/stdcxx.h>


namespace bskv {

struct TErrorCode {
  enum type {
    EGood = 0,
    ENoRootMeta = 1,
    ECouldNotConnectMetadata = 2,
    ECouldNotConnectIDGen = 3,
    ECouldNotConnectSmallSet = 4,
    ECouldNotConnectRootMetaMapping = 5,
    EItemNotExisted = 100,
    EUnknownException = 10,
    EBigSetNotExisted = 101,
    EBigSetCreated = 102,
    EBigSetAlreadyExisted = 103,
    EBigSetAssigned = 104
  };
};

extern const std::map<int, const char*> _TErrorCode_VALUES_TO_NAMES;

std::ostream& operator<<(std::ostream& out, const TErrorCode::type& val);

typedef std::string TItemKey;

typedef int64_t TContainerKey;

typedef TContainerKey TSmallSetIDKey;

typedef TContainerKey TMetaKey;

typedef std::string TStringKey;

typedef int64_t TKey;

class TItem;

class TItemSet;

class TItemResult;

class TItemSetResult;

class TPutItemResult;

class TExistedResult;

class TMultiPutItemResult;


class TItem : public virtual ::apache::thrift::TBase {
 public:

  TItem(const TItem&);
  TItem& operator=(const TItem&);
  TItem() : key(), value() {
  }

  virtual ~TItem() throw();
  std::string key;
  std::string value;

  void __set_key(const std::string& val);

  void __set_value(const std::string& val);

  bool operator == (const TItem & rhs) const
  {
    if (!(key == rhs.key))
      return false;
    if (!(value == rhs.value))
      return false;
    return true;
  }
  bool operator != (const TItem &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TItem & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(TItem &a, TItem &b);

std::ostream& operator<<(std::ostream& out, const TItem& obj);

typedef struct _TItemSet__isset {
  _TItemSet__isset() : items(false) {}
  bool items :1;
} _TItemSet__isset;

class TItemSet : public virtual ::apache::thrift::TBase {
 public:

  TItemSet(const TItemSet&);
  TItemSet& operator=(const TItemSet&);
  TItemSet() {
  }

  virtual ~TItemSet() throw();
  std::vector<TItem>  items;

  _TItemSet__isset __isset;

  void __set_items(const std::vector<TItem> & val);

  bool operator == (const TItemSet & rhs) const
  {
    if (!(items == rhs.items))
      return false;
    return true;
  }
  bool operator != (const TItemSet &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TItemSet & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(TItemSet &a, TItemSet &b);

std::ostream& operator<<(std::ostream& out, const TItemSet& obj);

typedef struct _TItemResult__isset {
  _TItemResult__isset() : error(false), item(false) {}
  bool error :1;
  bool item :1;
} _TItemResult__isset;

class TItemResult : public virtual ::apache::thrift::TBase {
 public:

  TItemResult(const TItemResult&);
  TItemResult& operator=(const TItemResult&);
  TItemResult() : error((TErrorCode::type)0) {
  }

  virtual ~TItemResult() throw();
  TErrorCode::type error;
  TItem item;

  _TItemResult__isset __isset;

  void __set_error(const TErrorCode::type val);

  void __set_item(const TItem& val);

  bool operator == (const TItemResult & rhs) const
  {
    if (!(error == rhs.error))
      return false;
    if (__isset.item != rhs.__isset.item)
      return false;
    else if (__isset.item && !(item == rhs.item))
      return false;
    return true;
  }
  bool operator != (const TItemResult &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TItemResult & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(TItemResult &a, TItemResult &b);

std::ostream& operator<<(std::ostream& out, const TItemResult& obj);

typedef struct _TItemSetResult__isset {
  _TItemSetResult__isset() : error(false), items(false) {}
  bool error :1;
  bool items :1;
} _TItemSetResult__isset;

class TItemSetResult : public virtual ::apache::thrift::TBase {
 public:

  TItemSetResult(const TItemSetResult&);
  TItemSetResult& operator=(const TItemSetResult&);
  TItemSetResult() : error((TErrorCode::type)0) {
  }

  virtual ~TItemSetResult() throw();
  TErrorCode::type error;
  TItemSet items;

  _TItemSetResult__isset __isset;

  void __set_error(const TErrorCode::type val);

  void __set_items(const TItemSet& val);

  bool operator == (const TItemSetResult & rhs) const
  {
    if (!(error == rhs.error))
      return false;
    if (__isset.items != rhs.__isset.items)
      return false;
    else if (__isset.items && !(items == rhs.items))
      return false;
    return true;
  }
  bool operator != (const TItemSetResult &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TItemSetResult & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(TItemSetResult &a, TItemSetResult &b);

std::ostream& operator<<(std::ostream& out, const TItemSetResult& obj);

typedef struct _TPutItemResult__isset {
  _TPutItemResult__isset() : error(false), ok(false), oldItem(false) {}
  bool error :1;
  bool ok :1;
  bool oldItem :1;
} _TPutItemResult__isset;

class TPutItemResult : public virtual ::apache::thrift::TBase {
 public:

  TPutItemResult(const TPutItemResult&);
  TPutItemResult& operator=(const TPutItemResult&);
  TPutItemResult() : error((TErrorCode::type)0), ok(0) {
  }

  virtual ~TPutItemResult() throw();
  TErrorCode::type error;
  bool ok;
  TItem oldItem;

  _TPutItemResult__isset __isset;

  void __set_error(const TErrorCode::type val);

  void __set_ok(const bool val);

  void __set_oldItem(const TItem& val);

  bool operator == (const TPutItemResult & rhs) const
  {
    if (!(error == rhs.error))
      return false;
    if (!(ok == rhs.ok))
      return false;
    if (__isset.oldItem != rhs.__isset.oldItem)
      return false;
    else if (__isset.oldItem && !(oldItem == rhs.oldItem))
      return false;
    return true;
  }
  bool operator != (const TPutItemResult &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TPutItemResult & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(TPutItemResult &a, TPutItemResult &b);

std::ostream& operator<<(std::ostream& out, const TPutItemResult& obj);

typedef struct _TExistedResult__isset {
  _TExistedResult__isset() : error(false), existed(false) {}
  bool error :1;
  bool existed :1;
} _TExistedResult__isset;

class TExistedResult : public virtual ::apache::thrift::TBase {
 public:

  TExistedResult(const TExistedResult&);
  TExistedResult& operator=(const TExistedResult&);
  TExistedResult() : error((TErrorCode::type)0), existed(0) {
  }

  virtual ~TExistedResult() throw();
  TErrorCode::type error;
  bool existed;

  _TExistedResult__isset __isset;

  void __set_error(const TErrorCode::type val);

  void __set_existed(const bool val);

  bool operator == (const TExistedResult & rhs) const
  {
    if (!(error == rhs.error))
      return false;
    if (!(existed == rhs.existed))
      return false;
    return true;
  }
  bool operator != (const TExistedResult &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TExistedResult & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(TExistedResult &a, TExistedResult &b);

std::ostream& operator<<(std::ostream& out, const TExistedResult& obj);

typedef struct _TMultiPutItemResult__isset {
  _TMultiPutItemResult__isset() : error(false), added(false), replaced(false) {}
  bool error :1;
  bool added :1;
  bool replaced :1;
} _TMultiPutItemResult__isset;

class TMultiPutItemResult : public virtual ::apache::thrift::TBase {
 public:

  TMultiPutItemResult(const TMultiPutItemResult&);
  TMultiPutItemResult& operator=(const TMultiPutItemResult&);
  TMultiPutItemResult() : error((TErrorCode::type)0) {
  }

  virtual ~TMultiPutItemResult() throw();
  TErrorCode::type error;
  std::vector<TItemKey>  added;
  std::vector<TItem>  replaced;

  _TMultiPutItemResult__isset __isset;

  void __set_error(const TErrorCode::type val);

  void __set_added(const std::vector<TItemKey> & val);

  void __set_replaced(const std::vector<TItem> & val);

  bool operator == (const TMultiPutItemResult & rhs) const
  {
    if (!(error == rhs.error))
      return false;
    if (__isset.added != rhs.__isset.added)
      return false;
    else if (__isset.added && !(added == rhs.added))
      return false;
    if (__isset.replaced != rhs.__isset.replaced)
      return false;
    else if (__isset.replaced && !(replaced == rhs.replaced))
      return false;
    return true;
  }
  bool operator != (const TMultiPutItemResult &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TMultiPutItemResult & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(TMultiPutItemResult &a, TMultiPutItemResult &b);

std::ostream& operator<<(std::ostream& out, const TMultiPutItemResult& obj);

} // namespace

#endif
