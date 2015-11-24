/**
 * Autogenerated by Thrift Compiler (0.9.3)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef server_TYPES_H
#define server_TYPES_H

#include <iosfwd>

#include <thrift/Thrift.h>
#include <thrift/TApplicationException.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TTransport.h>

#include <thrift/cxxfunctional.h>


namespace RPC {

class dataFormat;

typedef struct _dataFormat__isset {
  _dataFormat__isset() : isSucceeded(false), data(false) {}
  bool isSucceeded :1;
  bool data :1;
} _dataFormat__isset;

class dataFormat {
 public:

  dataFormat(const dataFormat&);
  dataFormat& operator=(const dataFormat&);
  dataFormat() : isSucceeded(0), data() {
  }

  virtual ~dataFormat() throw();
  bool isSucceeded;
  std::string data;

  _dataFormat__isset __isset;

  void __set_isSucceeded(const bool val);

  void __set_data(const std::string& val);

  bool operator == (const dataFormat & rhs) const
  {
    if (!(isSucceeded == rhs.isSucceeded))
      return false;
    if (!(data == rhs.data))
      return false;
    return true;
  }
  bool operator != (const dataFormat &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const dataFormat & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(dataFormat &a, dataFormat &b);

inline std::ostream& operator<<(std::ostream& out, const dataFormat& obj)
{
  obj.printTo(out);
  return out;
}

} // namespace

#endif