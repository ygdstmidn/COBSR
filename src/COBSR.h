#ifndef INCLUDE_COBSR_H_
#define INCLUDE_COBSR_H_

#include "mbed.h"
#include "COBSR_config.h"

namespace mbed
{
namespace lib_ygdstmidn
{

#define MaxBrockSize    0xFF
#define delimiter       0x00

#if(encodeCOBSR_ENABLE)

/**
 * char型の文字列をCOBS/Rを使ってエンコードします
 * @param buf エンコードした文字列を入れる配列
 * @param buf_size bufのサイズ(バイト数)
 * @param data エンコードしたいデータの入った配列
 * @param data_size dataのサイズ(バイト数)
 * @return エンコードした後のデータのサイズ
 * @note エラーの場合，返り値は0
 * @note データをエンコードした結果、バッファに入りきらなかった場合、エラー
*/
size_t encodeCOBSR(void *buf,size_t buf_size,const void *data,size_t data_size);

#endif// encodeCOBSR_ENABLE

#if(decodeCOBSR_ENABLE)

/**
 * COBS/Rを使ってエンコードされたchar型の文字列をデコードします
 * @param buf デコードした後の文字列を入れる配列
 * @param buf_size bufのサイズ(バイト数)
 * @param data デコードしたいデータの入った配列
 * @param data_size dataのサイズ(バイト数)
 * @return デコードした後のデータのサイズ
 * @note エラーの場合，返り値は0
 * @note データをデコードした結果、バッファに入りきらなかった場合、エラー
 * @note 文字列にdelimiterが入っていない場合、エラー
 * @note delimiterが見つかった時点でプログラム終了
*/
size_t decodeCOBSR(void *buf,size_t buf_size,const void *data,size_t data_size);

#endif// decodeCOBSR_ENABLE

}//namespace lib_ygdstmidn
}//namespace mbed

using namespace mbed::lib_ygdstmidn;

#endif// INCLUDE_COBSR_H_