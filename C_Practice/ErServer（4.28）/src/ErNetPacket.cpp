#include "ErServer/ErLog.h"
#include "ErServer/ErNetPacket.h"
#include <stdio.h>
#include <string.h>
#include <ros/ros.h>

ErNetPacket::ErNetPacket(ErTypes::UByte2 bufferSize,
                            ErTypes::UByte2 headerLength ,
                            char * buf ,
                            ErTypes::UByte2 footerLength )
{

  if (buf == NULL && bufferSize > 0)
   {
     myOwnMyBuf = true;
     myBuf = new char[bufferSize];
     // memset(myBuf, 0, bufferSize);
   }
   else
   {
     myOwnMyBuf = false;
     myBuf = buf;
   }
   myHeaderLength = headerLength;
   myFooterLength = footerLength;
   myReadLength = myHeaderLength;
   myMaxLength = bufferSize;
   myLength = myHeaderLength;
   myIsValid = true;
  insertHeader();
}
ErNetPacket &ErNetPacket::operator=(const ErNetPacket &other)
{
  if (this != &other) {
    ErNetPacket::operator=(other);
    myPacketSource = other.myPacketSource;
    myAddedFooter  = other.myAddedFooter;
    myArbitraryString = other.myArbitraryString;
    myCommand      = other.myCommand;
  }
  return *this;
}

ErNetPacket::~ErNetPacket()
{
}

 bool ErNetPacket::hasWriteCapacity(int bytes)
{
  if (bytes < 0) {
    ErLog::log(ErLog::Normal, "ErNetPacket::hasWriteCapacity(%d) cannot write negative amount",
               bytes);
    return false;
  }

  // Make sure there's enough room in the packet
  if ((myLength + bytes) <= myMaxLength) {
     return true;
  }

  myIsValid = false;

  return false;

} // end method hasWriteCapacity


 void ErNetPacket::byteToBuf(ErTypes::Byte val)
{
  if (!hasWriteCapacity(1)) {
    return;
  }

  memcpy(myBuf+myLength, &val, 1);
  myLength += 1;
}

 void ErNetPacket::byte2ToBuf(ErTypes::Byte2 val)
 {
   if (!hasWriteCapacity(2)) {
     return;
   }

   unsigned char c;
   c = (val >> 8) & 0xff;
   memcpy(myBuf+myLength+1, &c, 1);
   c = val & 0xff;
   memcpy(myBuf+myLength, &c, 1);
   myLength += 2;
 }

 void ErNetPacket::byte4ToBuf(ErTypes::Byte4 val)
 {
   if (!hasWriteCapacity(4)) {
     return;
   }

   unsigned char c;
   c = (val >> 24) & 0xff;
   memcpy(myBuf+myLength+3, &c, 1);
   c = (val >> 16) & 0xff;
   memcpy(myBuf+myLength+2, &c, 1);
   c = (val >> 8) & 0xff;
   memcpy(myBuf+myLength+1, &c, 1);
   c = val & 0xff;
   memcpy(myBuf+myLength, &c, 1);
   myLength += 4;

 }



 void ErNetPacket::uByteToBuf(ErTypes::UByte val)
{
  if (!hasWriteCapacity(1)) {
    return;
  }
  memcpy(myBuf+myLength, &val, 1);
  myLength += 1;
}

 void ErNetPacket::uByte2ToBuf(ErTypes::UByte2 val)
{
  if (!hasWriteCapacity(2)) {
    return;
  }
  // Note that MSB is placed one byte after the LSB in the end of the buffer:
  unsigned char c;
  c = (val >> 8) & 0xff;
  memcpy(myBuf+myLength+1, &c, 1);
  c = val & 0xff;
  memcpy(myBuf+myLength, &c, 1);
  myLength += 2;
}


void ErNetPacket::insertHeader()
{
  int length = myLength;
  myLength = 0;
  myCommand = 0x01;
  uByteToBuf(0xF);         // 1
  uByteToBuf(0xC);         // 2
  ROS_INFO("before insert Header,myAddedFooter is %d",myAddedFooter);
  if (myAddedFooter)
    uByte2ToBuf(length);   // 3 & 4
  else
    uByte2ToBuf(length+2); // 3 & 4

  uByte2ToBuf(myCommand);  // 5 & 6

  if (myAddedFooter)
    myLength = length - 2;
  else
    myLength = length;
} // end method insertHeader
 const char *ErNetPacket::getBuf(void) const
{
  return myBuf;
}

 char *ErNetPacket::getBuf(void)
{
  return myBuf;
}

 void ErNetPacket::setMaxLength(ErTypes::UByte2 bufferSize)
 {
   if (myMaxLength >= bufferSize)
     return;
   if (myOwnMyBuf)
   {
     delete[] myBuf;
     myOwnMyBuf = false;
   }
   myBuf = new char[bufferSize];
   // memset(myBuf, 0, bufferSize);

   myMaxLength = bufferSize;
   myOwnMyBuf = true;
 }



 void ErNetPacket::finalizePacket(void)
{

  insertHeader();

 int chkSum = calcCheckSum();
 ROS_INFO("CHKSUM IS %d",chkSum);
 byteToBuf((chkSum >> 8) & 0xff );
 byteToBuf(chkSum & 0xff );
 myAddedFooter = true;
  //log();
  //printf("%d %d %d\n", myLength ,myCommand, chkSum);
}


 ErTypes::Byte2 ErNetPacket::calcCheckSum(void)
{
  int c = 0;

  //printf("%d\n", myLength);
  //log();
  int i = 3;
  int n = myLength - 2;

  while (n > 3) {

    //printf("n %d i %d c %d c1 %d c2 %d\n", n, i, c, myBuf[i], myBuf[i+1]);
    c += ((unsigned char)myBuf[i]<<8) | (unsigned char)myBuf[i+1];
    c = c & 0xffff;
    n -= 2;
    i += 2;
  }
  //printf("aft n %d i %d c %d\n", n, i, c);
  if (n > 0)
    c = c ^ (int)((unsigned char) myBuf[i]);
  //printf("%d\n", c);
  return c;
}

 bool ErNetPacket::verifyCheckSum(void)
{
  ErTypes::Byte2 chksum;
  ErTypes::Byte2 calcedChksum;
  unsigned char c1, c2;
  int length;

  if (myLength - 2 < myHeaderLength)
    return false;

  c2 = myBuf[myLength-2];
  c1 = myBuf[myLength-1];
  chksum = (c1 & 0xff) | (c2 << 8);
  length = myLength;
  myLength = myLength - 2;
  calcedChksum = calcCheckSum();
  myLength = length;

  //printf("%d %d\n", chksum, calcedChksum);
  if (chksum == calcedChksum) {
    return true;
  } else {
    return false;
  }

}


 void ErNetPacket::duplicatePacket(ErNetPacket *packet)
{
  myLength = packet->myLength;

  // if (myMaxLength < myLength)
  //  setMaxLength(packet->myLength);
  if (myMaxLength < myLength + packet->myFooterLength)
    setMaxLength(packet->myLength + packet->myFooterLength);

  myReadLength = packet->myReadLength;
  myHeaderLength = packet->myHeaderLength;
  myFooterLength = packet->myFooterLength;
  myCommand = packet->myCommand;
  myAddedFooter = packet->myAddedFooter;
  memcpy(myBuf, packet->getBuf(), packet->myLength + packet->myFooterLength);
  myArbitraryString = packet->myArbitraryString;
}
