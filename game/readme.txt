これはDXライブラリを利用したゲーム開発用のテンプレートです。

キーボードやマウスからの入力情報の取得は、
keyInput.関数名(引数);
mouseInput.関数名(引数);
で実行できます。

後に移植してAndroidに対応させる場合は、以下のサイトで対応しているかを確認しましょう。
http://dxlib.o.oo7.jp/dxfunc.html

executeClickEventのboost::any版は、boostライブラリが必要です。
利用したい場合は、boostライブラリを導入してプロジェクトの設定をboostを利用できるように変更した後、Buttonヘッダ内のインクルード部分とexecuteClickEventのコメントを外すと利用可能になります。
