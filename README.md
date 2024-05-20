# このライブラリについて

データをCOBS/Rを用いてエンコード、デコードする関数を入れています。

COBSR_config.hで要らない機能の項目を0にすることにより、メモリ領域の削減、コンパイルする時間の短縮につながります。

名前空間は`mbed::lib_ygdstmidn`です。ヘッダファイル内でusingしています。

# 各関数の説明

## encodeCOBSR

```c++
size_t encodeCOBSR(unsigned char *buf,size_t buf_size,const unsigned char *data,size_t data_size);
```
char型の文字列をCOBS/Rを使ってエンコードします

パラメーター:<br>
buf – エンコードした文字列を入れる配列<br>
buf_size – bufのサイズ(バイト数)<br>
data – エンコードしたいデータの入った配列<br>
data_size – dataのサイズ(バイト数)

戻り値:<br>
エンコードした後のデータのサイズ

注:<br>
エラーの場合，返り値は0<br>
データをエンコードした結果、バッファに入りきらなかった場合、エラー

## decodeCOBSR

```c++
size_t decodeCOBSR(unsigned char *buf,size_t buf_size,const unsigned char *data,size_t data_size)
```
COBS/Rを使ってエンコードされたchar型の文字列をデコードします

パラメーター:<br>
buf – デコードした後の文字列を入れる配列<br>
buf_size – bufのサイズ(バイト数)<br>
data – デコードしたいデータの入った配列<br>
data_size – dataのサイズ(バイト数)

戻り値:<br>
デコードした後のデータのサイズ

注:<br>
エラーの場合，返り値は0<br>
データをデコードした結果、バッファに入りきらなかった場合、エラー<br>
文字列にdelimiterが入っていない場合、エラー<br>
delimiterが見つかった時点でプログラム終了<br>
※この関数で作られた文字列には，末尾にNULL文字が追加されません．%sに注意


# 参考文献
- [Arduinoでバイナリ送受信のシリアル通信をするときのパケットの構造(Qiita)](https://qiita.com/hideakitai/items/347985528656be03b620)
- [参考にしたコード(GitHub)](https://github.com/bakercp/PacketSerial/blob/master/src/Encoding/COBS.h)
- [COBS/Rについて](https://pythonhosted.org/cobs/cobsr-intro.html)
- [COBSについて(Wikipedia)](https://en.wikipedia.org/wiki/Consistent_Overhead_Byte_Stuffing)
- [【COBS】：感動のデータエンコーディング革命！奇跡の効率アップ＆サイズ削減で心揺さぶられる未来への扉を開く(Qiita)](https://qiita.com/keek123/items/8eba70953f3dfc9dc395)
