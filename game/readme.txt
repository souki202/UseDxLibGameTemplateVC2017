これはDXライブラリを利用したゲーム開発用のテンプレートです。

キーボードやマウスからの入力情報の取得は、
keyInput.getPressFrame(int key);
とすればキーの押下フレーム数を、
keyInput.getPressTime(int key);
とすればZキーの押下時間(ms)を取得できます。

マウスはそれぞれ
mouseInput.getLeftPressFrame();
mouseInput.getLeftPressTime();
で左クリックの押下フレーム数と押下時間(ms)を取得できます。
Right, Middleも同様に可能です。
mouseInput.getWheelRotateValue();
で前回のUpdate後からのホイールの回転量を取得できます。

Timerクラスは、時間を管理するクラスです。
void update()関数で時間を更新
void reset()関数で最初の時間を初期化(インスタンス生成時にも実行される)
int getDeltaTime()関数で前回の更新からの時間差を取得し、
int getElapsedTime()関数で前回のreset()実行からの時間差を取得します。
なお、getDeltaTime()を加算することで経過時間を測る場合、実際の時間とずれる場合があるため、getElapsedTime()を使用してください。

後に移植してAndroidに対応させる場合は、以下のサイトで対応しているかを確認しましょう。
http://dxlib.o.oo7.jp/dxfunc.html

executeClickEventのboost::any&版は、boostライブラリが必要です。
利用したい場合は、boostライブラリを導入してプロジェクトの設定をboostを利用できるように変更した後、Buttonヘッダ内のインクルード部分とexecuteClickEventのコメントを外すと利用可能になります。
