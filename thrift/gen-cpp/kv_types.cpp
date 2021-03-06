/**
 * Autogenerated by Thrift Compiler (0.11.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include "kv_types.h"

#include <algorithm>
#include <ostream>

#include <thrift/TToString.h>

namespace kv {


KVPair::~KVPair() throw() {
}


void KVPair::__set_first(const KType& val) {
  this->first = val;
}

void KVPair::__set_second(const VType& val) {
  this->second = val;
}
std::ostream& operator<<(std::ostream& out, const KVPair& obj)
{
  obj.printTo(out);
  return out;
}


uint32_t KVPair::read(::apache::thrift::protocol::TProtocol* iprot) {

  ::apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;

  bool isset_first = false;
  bool isset_second = false;

  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->first);
          isset_first = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->second);
          isset_second = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  if (!isset_first)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  if (!isset_second)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  return xfer;
}

uint32_t KVPair::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  ::apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("KVPair");

  xfer += oprot->writeFieldBegin("first", ::apache::thrift::protocol::T_STRING, 1);
  xfer += oprot->writeString(this->first);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("second", ::apache::thrift::protocol::T_STRING, 2);
  xfer += oprot->writeString(this->second);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(KVPair &a, KVPair &b) {
  using ::std::swap;
  swap(a.first, b.first);
  swap(a.second, b.second);
}

KVPair::KVPair(const KVPair& other0) {
  first = other0.first;
  second = other0.second;
}
KVPair& KVPair::operator=(const KVPair& other1) {
  first = other1.first;
  second = other1.second;
  return *this;
}
void KVPair::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "KVPair(";
  out << "first=" << to_string(first);
  out << ", " << "second=" << to_string(second);
  out << ")";
}

} // namespace
