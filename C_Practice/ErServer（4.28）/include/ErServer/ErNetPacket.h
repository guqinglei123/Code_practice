#ifndef ERNETPACKET_H
#define ERNETPACKET_H
#include <string>
//定义了一个类型类
class ErTypes
{
public:
  /// A single signed byte
  typedef char Byte;
  /// Two signed bytes
  typedef short Byte2;
  /// Four signed bytes
  typedef int Byte4;
  /// Eight signed bytes
  typedef long long Byte8;

  /// A single unsigned byte
  typedef unsigned char UByte;
  /// Two unsigned bytes
  typedef unsigned short UByte2;
  /// Four unsigned bytes
  typedef unsigned int UByte4;
  /// Eight unsigned bytes
  typedef unsigned long long UByte8;
};


//定义一个发送网络数据包的类
class ErNetPacket
{
public:
   //构造函数
   ErNetPacket(ErTypes::UByte2 bufferSize=MAX_LENGTH + 5,
               ErTypes::UByte2 headerLength = HEADER_LENGTH,
               char * buf = NULL,
               ErTypes::UByte2 footerLength = FOOTER_LENGTH);

   ErNetPacket(const ErNetPacket &other);

  /// Assignment operator
   ErNetPacket &operator=(const ErNetPacket &other);

   ~ErNetPacket();

   //设置网络包各个部分中的最大值
  enum {
    SIZE_OF_LENGTH = 2,  ///< Number of bytes needed to store packet length value
    MAX_LENGTH = 32000,  ///< Suggested maximum total size of a packet (bytes)
    HEADER_LENGTH = 6,   ///< Bytes of packet data used for header
    FOOTER_LENGTH = 2,   ///< Byset of packet data used for footer

    /** Suggested maximum size for data payload (this is the total suggested
        packet size minus headers and footers)
    */
    MAX_DATA_LENGTH = MAX_LENGTH - HEADER_LENGTH - FOOTER_LENGTH - SIZE_OF_LENGTH
  };

  // 包的来源
  enum PacketSource
  {
    TCP, ///< Came in over tcp
    UDP ///< Came in over udp
  };

   /*将不同类型的数据放入buff中进行缓冲*/

    void doubleToBuf(double val);

  /// Puts ErTypes::Byte into packets buffer
    void byteToBuf(ErTypes::Byte val);
  /// Puts ErTypes::Byte2 into packets buffer
    void byte2ToBuf(ErTypes::Byte2 val);
  /// Puts ErTypes::Byte4 into packets buffer
    void byte4ToBuf(ErTypes::Byte4 val);
  /// Puts ErTypes::Byte8 into packets buffer
    void byte8ToBuf(ErTypes::Byte8 val);

  /// Puts ErTypes::UByte into packets buffer
    void uByteToBuf(ErTypes::UByte val);
  /// Puts ErTypes::UByte2 into packet buffer
    void uByte2ToBuf(ErTypes::UByte2 val);
  /// Puts ErTypes::UByte4 into packet buffer
    void uByte4ToBuf(ErTypes::UByte4 val);
  /// Puts ErTypes::UByte8 into packet buffer
    void uByte8ToBuf(ErTypes::UByte8 val);

  /// Puts a NULL-terminated string into packet buffer
    void strToBuf(const char *str);

  /**
   * @brief Copies the given number of bytes from str into packet buffer
   * @deprecated use strToBufPadded(), strToBuf(), or dataToBuf() instead
  **/
    void strNToBuf(const char *str, int length);
  /// Copies length bytes from str, if str ends before length, pads data with 0s
    void strToBufPadded(const char *str, int length);
  /// Copies length bytes from data into packet buffer
    void dataToBuf(const char *data, int length);
  /// Copies length bytes from data into packet buffer
    void dataToBuf(const unsigned char *data, int length);

   /*将buff提取相应的数据进行缓冲*/
  /// Gets a double from the packet buffer
    double bufToDouble(void);
  // Utility functions to read differet data types from a bufer. Each read
  // will increment the myReadLength.
  /// Gets a ErTypes::Byte from the buffer
    ErTypes::Byte bufToByte(void);
  /// Gets a ErTypes::Byte2 from the buffer
    ErTypes::Byte2 bufToByte2(void);
  /// Gets a ErTypes::Byte4 from the buffer
    ErTypes::Byte4 bufToByte4(void);
  /// Gets a ErTypes::Byte8 from the buffer
    ErTypes::Byte8 bufToByte8(void);

  /// Gets a ErTypes::UByte from the buffer
    ErTypes::UByte bufToUByte(void);
  /// Gets a ErTypes::UByte2 from the buffer
    ErTypes::UByte2 bufToUByte2(void);
  /// Gets a ErTypes::UByte4 from the buffer
    ErTypes::UByte4 bufToUByte4(void);
  /// Gets a ErTypes::UByte8 from the buffer
    ErTypes::UByte8 bufToUByte8(void);

 /// Gets a null-terminated string from the buffer
    void bufToStr(char *buf, int maxlen);
  /// Gets a null-terminated string from the buffer
   std::string bufToString();
  /// Gets length bytes from buffer and puts them into data
    void bufToData(char * data, int length);
  /// Gets length bytes from buffer and puts them into data
    void bufToData(unsigned char * data, int length);

/****/
  /// Sets the command this packet is
   void setCommand(ErTypes::UByte2 command);
  /// Gets the command this packet is
   ErTypes::UByte2 getCommand(void);


 /*得到包中各个部分的长度*/
  /// 包的长度
   ErTypes::UByte2 getLength(void) const { return myLength; }
  /// 包中数据部分的长度
    ErTypes::UByte2 getDataLength(void) const;
  /// 已经阅读了的包的长度
   ErTypes::UByte2 getReadLength(void) const { return myReadLength; }
  /// 已经阅读了的包中数据的长度
   ErTypes::UByte2 getDataReadLength(void) const { return myReadLength - myHeaderLength; }
  /// 包中头的长度
   ErTypes::UByte2 getHeaderLength(void) const
  { return myHeaderLength; }
  ///包中尾的长度
   ErTypes::UByte2 getFooterLength(void) const
  { return myFooterLength; }
  ///包中最大长度
   ErTypes::UByte2 getMaxLength(void) const { return myMaxLength; }

  /*得到包中的数据*/
  /// Gets a const pointer to the buffer the packet uses
    const char * getBuf(void) const;

  /// Gets a pointer to the buffer the packet uses
    char * getBuf(void);

 /*确定包中数据的来源*/
  PacketSource getPacketSource(void) { return myPacketSource; }
  void setPacketSource(PacketSource source) { myPacketSource = source; }

   /*设置包中的数据*/
  /// Sets the buffer the packet is using
    void setBuf(char *buf, ErTypes::UByte2 bufferSize);
  /// Sets the maximum buffer size (if new size is <= current does nothing)
    void setMaxLength(ErTypes::UByte2 bufferSize);
  /// Sets the length of the packet
    bool setLength(ErTypes::UByte2 length);
  /// Sets the read length
    void setReadLength(ErTypes::UByte2 readLength);
  /// Sets the length of the header
    bool setHeaderLength(ErTypes::UByte2 length);

  /*实现一个包*/
  /// returns true if the checksum matches what it should be
   bool verifyCheckSum(void);
  /// returns the checksum, probably used only internally
   ErTypes::Byte2 calcCheckSum(void);
  /// MakeFinals the packet in preparation for sending, must be done
    void finalizePacket(void) ;
   /*复制一个包*/
   void duplicatePacket(ErNetPacket *packet);

  /// Iternal function that sets if we already added the footer(for forwarding)
  bool getAddedFooter(void) { return myAddedFooter; }
  /// Iternal function that sets if we already added the footer(for forwarding)
  void setAddedFooter(bool addedFooter) { myAddedFooter = addedFooter; }


   void empty(void);

  /// ArLogs the hex and decimal values of each byte of the packet, and possibly extra metadata as well
    void log(void);
  /// ArLogs the hex value of each byte in the packet
    void printHex(void);

  /// Returns whether the packet is valid, i.e. no error has occurred when reading/writing.
    bool isValid(void);

  /// Resets the valid state of the packet.
    void resetValid();

    void resetRead(void);



  void setArbitraryString(const char *string) { myArbitraryString = string; }
  const char *getArbitraryString(void) { return myArbitraryString.c_str(); }

private:

  /// Inserts the header information (command, length, etc.) into the buffer.
  void insertHeader();


protected:
  PacketSource myPacketSource;
  bool myAddedFooter;
  std::string myArbitraryString;
  ErTypes::UByte2 myCommand;

  // internal function to make sure we have enough length left to read in the packet
   bool isNextGood(int bytes);

  /// Returns true if there is enough room in the packet to add the specified number of bytes
   bool hasWriteCapacity(int bytes);

  // internal data
  ErTypes::UByte2 myHeaderLength;
  ErTypes::UByte2 myFooterLength;
  ErTypes::UByte2 myMaxLength;

  ErTypes::UByte2 myReadLength;
  bool myOwnMyBuf;

  // Actual packet data
  char *myBuf;
  ErTypes::UByte2 myLength;

  // Whether no error has occurred in reading/writing the packet.
  bool myIsValid;

};


#endif // ERNETPACKET_H
