#include "COBSR.h"

namespace mbed
{
namespace lib_ygdstmidn
{

size_t encodeCOBSR(void *buf, size_t buf_size, const void *data, size_t data_size)
{
  if(buf==nullptr||data==nullptr)
  {
    return 0;//ポインタのヌルチェック
  }

  unsigned char *cbuf = static_cast<unsigned char *>(buf);
  const unsigned char *cdata = static_cast<const unsigned char *>(data);

  if(buf_size <= 1)
  {
    return 0;
  }

  unsigned int write_i = 1;//最初は必ずohbになる
  unsigned int ohb_i = 0;

  for(unsigned int read_i = 0;read_i < data_size;read_i++)//COBS
  {
    if(buf_size<=write_i)
    {
      return 0;
    }
    
    if(((unsigned int)(write_i-ohb_i))==MaxBrockSize)
    {
      cbuf[ohb_i] = MaxBrockSize;
      ohb_i=write_i;
      write_i++;
      if(buf_size<=write_i)
      {
        return 0;
      }
    }
    
    if(cdata[read_i]==delimiter)
    {
      cbuf[ohb_i] = (unsigned int)(write_i-ohb_i);
      ohb_i=write_i;
    }else
    {
      cbuf[write_i] = cdata[read_i];
    }

    write_i++;
  }

  if((unsigned int)(write_i-ohb_i)<cdata[data_size-1])//最後のところ(/R)
  {
    cbuf[ohb_i] = cdata[data_size-1];
    cbuf[write_i-1] = delimiter;
    return write_i;
  }else
  {
    if(buf_size<=write_i)
    {
      return 0;
    }
    cbuf[write_i] = delimiter;
    cbuf[ohb_i] = (unsigned int)(write_i-ohb_i);
    return write_i+1;
  }
}

size_t decodeCOBSR(void *buf,size_t buf_size,const void *data,size_t data_size)
{
  if(buf==nullptr||data==nullptr)
  {
    return 0;//ポインタのヌルチェック
  }
  
  unsigned char *cbuf = static_cast<unsigned char *>(buf);//キャスト変換
  const unsigned char *cdata = static_cast<const unsigned char *>(data);//キャスト変換

  if(buf_size == 0||data_size <= 1||cdata[0]==delimiter)
  {
    return 0;
  }

  unsigned char ohb = cdata[0];
  unsigned int read_i = 1;//ohbの次のバイトを表す
  unsigned int write_i = 0;
  while(cdata[read_i]!=delimiter)
  {
    for(unsigned char i=0;i<ohb-1;i++)//データの切り取り
    {
      if(buf_size<=write_i)
      {
        return 0;//バッファが足りない
      }
      if(cdata[i+read_i]==delimiter)//COBS/Rなので途中でdelimiterが見つかる。
      {
        cbuf[write_i] = ohb;
        return write_i+1;
      }
      cbuf[write_i] = cdata[i+read_i];
      write_i++;
    }

    if(cdata[read_i+ohb-1]==delimiter)//delimiterに届いたら終わり(COBS)
    {
      return write_i;
    }
    
    if(ohb != MaxBrockSize)//MBSでないならdelimiter追加
    {
      if(buf_size<=write_i)
      {
        return 0;//バッファが足りない
      }
      cbuf[write_i] = delimiter;
      write_i++;
    }
    
    read_i+=ohb;//ohb切り替え
    ohb = cdata[read_i-1];

    if(data_size<=read_i)
    {
      return 0;//データが少ない(delimiterがみつからない)
    }
  }// while(cdata[read_i]!=delimiter)

  //次がdelimiterだった場合にwhileを抜けてくる
  if(ohb==1)
  {//末尾がdelimiter
    return write_i;
  }else
  {//Rなのでこういうことがある
    cbuf[write_i] = ohb;
    return write_i+1;
  }
}

}//namespace lib_ygdstmidn
}//namespace mbed