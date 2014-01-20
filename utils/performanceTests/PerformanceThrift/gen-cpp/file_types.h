/**
 * Autogenerated by Thrift Compiler (0.9.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef file_TYPES_H
#define file_TYPES_H

#include <thrift/Thrift.h>
#include <thrift/TApplicationException.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TTransport.h>



namespace thriftTest {

typedef struct _inner__isset {
  _inner__isset() : att1(false), att2(false), att3(false) {}
  bool att1;
  bool att2;
  bool att3;
} _inner__isset;

class inner {
 public:

  static const char* ascii_fingerprint; // = "44156A2FED099BBAFBD39CBA70225370";
  static const uint8_t binary_fingerprint[16]; // = {0x44,0x15,0x6A,0x2F,0xED,0x09,0x9B,0xBA,0xFB,0xD3,0x9C,0xBA,0x70,0x22,0x53,0x70};

  inner() : att1(), att2(0), att3(0) {
  }

  virtual ~inner() throw() {}

  std::string att1;
  int32_t att2;
  double att3;

  _inner__isset __isset;

  void __set_att1(const std::string& val) {
    att1 = val;
  }

  void __set_att2(const int32_t val) {
    att2 = val;
  }

  void __set_att3(const double val) {
    att3 = val;
  }

  bool operator == (const inner & rhs) const
  {
    if (!(att1 == rhs.att1))
      return false;
    if (!(att2 == rhs.att2))
      return false;
    if (!(att3 == rhs.att3))
      return false;
    return true;
  }
  bool operator != (const inner &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const inner & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(inner &a, inner &b);

typedef struct _outer__isset {
  _outer__isset() : att1(false), att2(false), att3(false), att4(false) {}
  bool att1;
  bool att2;
  bool att3;
  bool att4;
} _outer__isset;

class outer {
 public:

  static const char* ascii_fingerprint; // = "DC2293E96701067D7A839FBD473D3070";
  static const uint8_t binary_fingerprint[16]; // = {0xDC,0x22,0x93,0xE9,0x67,0x01,0x06,0x7D,0x7A,0x83,0x9F,0xBD,0x47,0x3D,0x30,0x70};

  outer() : att1(0), att2(), att3(0) {
  }

  virtual ~outer() throw() {}

  double att1;
  std::string att2;
  int32_t att3;
  inner att4;

  _outer__isset __isset;

  void __set_att1(const double val) {
    att1 = val;
  }

  void __set_att2(const std::string& val) {
    att2 = val;
  }

  void __set_att3(const int32_t val) {
    att3 = val;
  }

  void __set_att4(const inner& val) {
    att4 = val;
  }

  bool operator == (const outer & rhs) const
  {
    if (!(att1 == rhs.att1))
      return false;
    if (!(att2 == rhs.att2))
      return false;
    if (!(att3 == rhs.att3))
      return false;
    if (!(att4 == rhs.att4))
      return false;
    return true;
  }
  bool operator != (const outer &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const outer & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(outer &a, outer &b);

} // namespace

#endif
