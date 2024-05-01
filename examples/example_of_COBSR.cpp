/**
 * 使用例です。
 * 自由に使ってね。
 * 
 * プログラムの内容
 * -->pcから受け取ったデータを保存
 * -->一定時間(1秒)ごとにデータをエンコード、デコードしてpcに出力
 * -->この時，LED1が光ります
 * 
 * f303k8で動作しましたが、ほかのマイコンでも大丈夫だと思います。
*/

#if(0)

#include "mbed.h"
#include "COBSR.h"

#define PC_READ_BUF_SIZE            100
#define ENCODE_BUF_SIZE             PC_READ_BUF_SIZE+2      //最初のohb+末尾のdeimter
#define PC_WRITE_1KETA_BUF_SIZE     10                      //理論上4でいいけど怖いので10
#define OUTPUT_INTERVAL             1000
#define PC_SERIAL_BAUDRATE          115200

DigitalOut led(LED1);
UnbufferedSerial pc(USBTX,USBRX,PC_SERIAL_BAUDRATE);
Ticker tick;

void flip();
void pc_read();

char pc_read_buf[PC_READ_BUF_SIZE];
unsigned int pc_reading_i = 0;

int main()
{
    chrono::milliseconds output_interval(OUTPUT_INTERVAL);
    tick.attach(&flip,output_interval);
    pc.attach(&pc_read,SerialBase::RxIrq);
    while(1)
    {
    }
}

void flip()
{
    led=!led;

    if(pc_reading_i != 0)
    {
        pc.write("\r\ndata  :",9);
        for(unsigned int i=0;i<pc_reading_i;i++)
        {
            char write_buf[PC_WRITE_1KETA_BUF_SIZE];
            unsigned char size = snprintf(write_buf,PC_WRITE_1KETA_BUF_SIZE,"%02X,",pc_read_buf[i]);
            pc.write(write_buf,size);
        }

        pc.write("\r\nencode:",9);
        char encode[ENCODE_BUF_SIZE];
        unsigned int size_encode = encodeCOBSR(encode,ENCODE_BUF_SIZE,pc_read_buf,pc_reading_i);
        for(unsigned int i=0;i<size_encode;i++)
        {
            char write_buf[PC_WRITE_1KETA_BUF_SIZE];
            unsigned char size = snprintf(write_buf,PC_WRITE_1KETA_BUF_SIZE,"%02X,",encode[i]);
            pc.write(write_buf,size);
        }

        pc.write("\r\ndecode:",9);
        char decode[PC_READ_BUF_SIZE];
        unsigned int size_decode = decodeCOBSR(decode,PC_READ_BUF_SIZE,encode,size_encode);
        for(unsigned int i=0;i<size_decode;i++)
        {
            char write_buf[PC_WRITE_1KETA_BUF_SIZE];
            unsigned char size = snprintf(write_buf,PC_WRITE_1KETA_BUF_SIZE,"%02X,",decode[i]);
            pc.write(write_buf,size);
        }

        pc_reading_i = 0;
    }
}

void pc_read()
{
    if((pc_reading_i!=PC_READ_BUF_SIZE))
    {
        pc_reading_i++;
    }
    pc.read(&pc_read_buf[pc_reading_i-1],1);
}

#endif

/**
 * 以下，このプログラムで通信してみた出力結果の例です．
*/

#if(0)

---- utf8 でエンコードされたメッセージを送信しました: "Hello World" ----

data  :48,65,6C,6C,6F,20,57,6F,72,6C,64,
encode:64,48,65,6C,6C,6F,20,57,6F,72,6C,00,
decode:48,65,6C,6C,6F,20,57,6F,72,6C,64,
---- 16 進数でエンコードされたメッセージを送信しました: "00a10023" ----

data  :00,A1,00,23,
encode:01,02,A1,23,00,
decode:00,A1,00,23,

#endif