/**
 * Autogenerated by Thrift Compiler (0.9.1)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include "fileSimple_types.h"

#include <algorithm>

namespace thriftTest {

const char* structure::ascii_fingerprint = "18BB90904A19379815A9A295B251B2BB";
const uint8_t structure::binary_fingerprint[16] = {0x18,0xBB,0x90,0x90,0x4A,0x19,0x37,0x98,0x15,0xA9,0xA2,0x95,0xB2,0x51,0xB2,0xBB};

uint32_t structure::read(::apache::thrift::protocol::TProtocol* iprot) {

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
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->att1);
          this->__isset.att1 = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->att2);
          this->__isset.att2 = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_DOUBLE) {
          xfer += iprot->readDouble(this->att3);
          this->__isset.att3 = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 4:
        if (ftype == ::apache::thrift::protocol::T_DOUBLE) {
          xfer += iprot->readDouble(this->att4);
          this->__isset.att4 = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 5:
        if (ftype == ::apache::thrift::protocol::T_BOOL) {
          xfer += iprot->readBool(this->att5);
          this->__isset.att5 = true;
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

uint32_t structure::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  xfer += oprot->writeStructBegin("structure");

  xfer += oprot->writeFieldBegin("att1", ::apache::thrift::protocol::T_I32, 1);
  xfer += oprot->writeI32(this->att1);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("att2", ::apache::thrift::protocol::T_STRING, 2);
  xfer += oprot->writeString(this->att2);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("att3", ::apache::thrift::protocol::T_DOUBLE, 3);
  xfer += oprot->writeDouble(this->att3);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("att4", ::apache::thrift::protocol::T_DOUBLE, 4);
  xfer += oprot->writeDouble(this->att4);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("att5", ::apache::thrift::protocol::T_BOOL, 5);
  xfer += oprot->writeBool(this->att5);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(structure &a, structure &b) {
  using ::std::swap;
  swap(a.att1, b.att1);
  swap(a.att2, b.att2);
  swap(a.att3, b.att3);
  swap(a.att4, b.att4);
  swap(a.att5, b.att5);
  swap(a.__isset, b.__isset);
}

} // namespace
