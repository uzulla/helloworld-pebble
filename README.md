# helloworld-pebble

Pebbleスマートウォッチ用のシンプルなHello Worldアプリケーションです。

## 概要

このアプリは、Pebbleの画面中央に「Hello World!」というテキストを表示する基本的なアプリケーションです。

## プロジェクト構成

```text
helloworld-pebble/
├── appinfo.json          # アプリケーションのメタデータ
├── package.json          # プロジェクト設定
├── wscript              # ビルドスクリプト
└── src/
    └── c/
        └── main.c       # メインのCコード
```

## 必要な環境

- Pebble SDK 3.x
- Python 2.7 (Pebble SDKのビルドシステムで使用)

## ビルド方法

Pebble SDKがインストールされている場合:

```bash
pebble build
```

## インストール方法

### シミュレータで実行

```bash
pebble install --emulator basalt
```

### 実機にインストール

1. Pebbleアプリ（スマートフォン）を起動
2. 開発者接続を有効化
3. 以下のコマンドを実行:

```bash
pebble install --phone [IPアドレス]
```

または、ビルドされた `.pbw` ファイルをPebbleアプリ経由でインストールできます。

## コードの説明

### main.c

- `init()`: ウィンドウを作成し、初期化します
- `window_load()`: TextLayerを作成し、"Hello World!"テキストを設定します
- `window_unload()`: リソースをクリーンアップします
- `deinit()`: ウィンドウを破棄します
- `main()`: アプリケーションのエントリーポイント

## 参考リンク

- [Rebble](https://rebble.io/) - Pebbleコミュニティサービス
- [Pebble SDK Documentation](https://developer.rebble.io/developer.pebble.com/index.html)

## ライセンス

MIT
