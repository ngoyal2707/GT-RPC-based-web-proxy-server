/**
 * Autogenerated by Thrift Compiler (0.9.3)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include "server_types.h"

#include <algorithm>
#include <ostream>

#include <thrift/TToString.h>

namespace RPC {


dataFormat::~dataFormat() throw() {
}


void dataFormat::__set_isSucceeded(const bool val) {
  this->isSucceeded = val;
}

void dataFormat::__set_data(const std::string& val) {
  this->data = val;
}

uint32_t dataFormat::read(::apache::thrift::protocol::TProtocol* iprot) {

  apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_BOOL) {
          xfer += iprot->readBool(this->isSucceeded);
          this->__isset.isSucceeded = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->data);
          this->__isset.data = true;
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

  return xfer;
}

uint32_t dataFormat::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("dataFormat");

  xfer += oprot->writeFieldBegin("isSucceeded", ::apache::thrift::protocol::T_BOOL, 1);
  xfer += oprot->writeBool(this->isSucceeded);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("data", ::apache::thrift::protocol::T_STRING, 2);
  xfer += oprot->writeString(this->data);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(dataFormat &a, dataFormat &b) {
  using ::std::swap;
  swap(a.isSucceeded, b.isSucceeded);
  swap(a.data, b.data);
  swap(a.__isset, b.__isset);
}

dataFormat::dataFormat(const dataFormat& other0) {
  isSucceeded = other0.isSucceeded;
  data = other0.data;
  __isset = other0.__isset;
}
dataFormat& dataFormat::operator=(const dataFormat& other1) {
  isSucceeded = other1.isSucceeded;
  data = other1.data;
  __isset = other1.__isset;
  return *this;
}
void dataFormat::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "dataFormat(";
  out << "isSucceeded=" << to_string(isSucceeded);
  out << ", " << "data=" << to_string(data);
  out << ")";
}

} // namespace
