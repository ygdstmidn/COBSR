# このライブラリについて

データをCOBS/Rを用いてエンコード、デコードする関数を入れています。

COBSR_config.hで要らない機能の項目を0にすることにより、メモリ領域の削減、コンパイルする時間の短縮につながります。

名前空間は`mbed::lib_ygdstmidn`です。ヘッダファイル内でusingしています。

# 各関数の説明

## encodeCOBSR

`size_t encodeCOBSR(unsigned char *buf,size_t buf_size,const unsigned char *data,size_t data_size);`<br>
char型の文字列をCOBS/Rを使ってエンコードします

パラメーター:<br>
buf – エンコードした文字列を入れる配列<br>
buf_size – bufのサイズ(バイト数)<br>
data – エンコードしたいデータの入った配列<br>
data_size – dataのサイズ(バイト数)

戻り値:<br>
エンコードした後のデータのサイズ

注:<br>
データをエンコードした結果、バッファに入りきらなかった場合、エラー

## decodeCOBSR

`size_t decodeCOBSR(unsigned char *buf,size_t buf_size,const unsigned char *data,size_t data_size)`<br>
COBS/Rを使ってエンコードされたchar型の文字列をデコードします

パラメーター:<br>
buf – デコードした後の文字列を入れる配列<br>
buf_size – bufのサイズ(バイト数)<br>
data – デコードしたいデータの入った配列<br>
data_size – dataのサイズ(バイト数)

戻り値:<br>
デコードした後のデータのサイズ

注:<br>
データをデコードした結果、バッファに入りきらなかった場合、エラー<br>
文字列にdelimiterが入っていない場合、エラー<br>
delimiterが見つかった時点でプログラム終了<br>