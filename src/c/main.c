/**
 * Pebble Hello World アプリケーション
 *
 * このアプリは、Pebbleスマートウォッチの画面に"Hello World!"という
 * テキストを表示するシンプルなアプリケーションです。
 *
 * Pebble C APIの基本的な使い方を示しています：
 * - Windowの作成と管理
 * - TextLayerを使ったテキスト表示
 * - リソースの適切な初期化とクリーンアップ
 */

#include <pebble.h>

// グローバル変数
// windowとtext_layerはアプリケーション全体で使用するため、
// staticグローバル変数として宣言します
static Window *window;        // メインウィンドウへのポインタ
static TextLayer *text_layer; // テキストレイヤーへのポインタ

/**
 * window_load - ウィンドウがロードされた時に呼ばれるコールバック関数
 *
 * この関数は、ウィンドウが画面に表示される直前に実行されます。
 * ここでUI要素（TextLayerなど）を作成し、ウィンドウに追加します。
 *
 * @param window ロードされるウィンドウへのポインタ
 */
static void window_load(Window *window) {
  // ウィンドウのルートレイヤー（最上位のレイヤー）を取得
  // すべてのUI要素はこのレイヤーの子として追加されます
  Layer *window_layer = window_get_root_layer(window);

  // ウィンドウレイヤーの境界（サイズと位置）を取得
  // これによりウィンドウの幅と高さがわかります
  GRect bounds = layer_get_bounds(window_layer);

  // TextLayerを作成します
  // GRect(x, y, width, height)で位置とサイズを指定
  // - x=0: 左端から開始
  // - y=55: 上から55ピクセルの位置（画面中央付近）
  // - width=bounds.size.w: ウィンドウの幅全体
  // - height=50: テキストレイヤーの高さ50ピクセル
  text_layer = text_layer_create(GRect(0, 55, bounds.size.w, 50));

  // TextLayerに表示するテキストを設定
  // このテキストはメモリに保持する必要があります（文字列リテラルなので自動的に保持されます）
  text_layer_set_text(text_layer, "Hello World!");

  // テキストのフォントを設定
  // FONT_KEY_GOTHIC_28_BOLD: Pebbleの組み込みフォント（28ポイント、ボールド）
  text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));

  // テキストの配置を中央揃えに設定
  // GTextAlignmentCenter: 水平方向に中央揃え
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);

  // TextLayerをウィンドウのレイヤー階層に追加
  // text_layer_get_layer()でTextLayerの基礎となるLayerを取得し、
  // それをwindow_layerの子として追加します
  layer_add_child(window_layer, text_layer_get_layer(text_layer));
}

/**
 * window_unload - ウィンドウがアンロードされる時に呼ばれるコールバック関数
 *
 * この関数は、ウィンドウが画面から削除される前に実行されます。
 * ここでwindow_loadで作成したすべてのリソースを解放する必要があります。
 * メモリリークを防ぐため、作成したリソースは必ず破棄します。
 *
 * @param window アンロードされるウィンドウへのポインタ
 */
static void window_unload(Window *window) {
  // TextLayerを破棄してメモリを解放
  // window_loadで作成したtext_layerを必ずここで破棄します
  text_layer_destroy(text_layer);
}

/**
 * init - アプリケーションの初期化関数
 *
 * アプリケーションが起動した時に一度だけ呼ばれます。
 * ここでウィンドウを作成し、イベントハンドラを設定し、
 * ウィンドウを画面に表示します。
 */
static void init(void) {
  // メインウィンドウを作成
  // window_create()は新しいWindowオブジェクトを動的に割り当てて返します
  window = window_create();

  // ウィンドウのイベントハンドラを設定
  // WindowHandlers構造体を使って、ウィンドウのライフサイクルイベントに
  // 対応するコールバック関数を登録します
  // .load: ウィンドウがロードされる時に呼ばれる関数
  // .unload: ウィンドウがアンロードされる時に呼ばれる関数
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });

  // ウィンドウをウィンドウスタックにプッシュして画面に表示
  // 第2引数のtrueはアニメーション付きで表示することを意味します
  // Pebbleはウィンドウをスタック構造で管理しており、
  // 最上位のウィンドウが画面に表示されます
  window_stack_push(window, true);
}

/**
 * deinit - アプリケーションの終了処理関数
 *
 * アプリケーションが終了する時に一度だけ呼ばれます。
 * ここでinit()で作成したすべてのリソースを解放します。
 */
static void deinit(void) {
  // ウィンドウを破棄してメモリを解放
  // これによりwindow_unloadも自動的に呼ばれ、
  // 関連するすべてのリソースがクリーンアップされます
  window_destroy(window);
}

/**
 * main - アプリケーションのエントリーポイント
 *
 * すべてのCプログラムと同様、実行はここから始まります。
 * Pebbleアプリケーションの標準的な構造は：
 * 1. init()でリソースを初期化
 * 2. app_event_loop()でイベントループを実行（ボタン押下などのイベントを処理）
 * 3. deinit()でリソースをクリーンアップ
 *
 * @return int プログラムの終了コード（通常は使用されません）
 */
int main(void) {
  // アプリケーションを初期化
  init();

  // イベントループを開始
  // この関数はアプリケーションが終了するまでブロックします
  // ユーザーのボタン操作やシステムイベントがここで処理されます
  app_event_loop();

  // アプリケーションを終了し、リソースをクリーンアップ
  deinit();

  return 0;
}
