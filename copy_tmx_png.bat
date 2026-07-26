@echo off
setlocal enabledelayedexpansion

:: --- 設定エリア ---
set "SOURCE_ROOT=C:\Project\GitHub\Toposun\toposun\authoring\map"
set "DEST_PATH=C:\Project\GitHub\Toposun\toposun\Resources\map"

echo マップ関連ファイルのコピー処理を開始します...
echo.

:: 1. 出力先フォルダの存在チェック
if not exist "%DEST_PATH%" (
    echo 【エラー】出力先フォルダが見つかりません。
    echo 対象パス: "%DEST_PATH%"
    echo 処理を中断します。
    pause
    exit /b
)

:: 2. .tmx ファイルと .tsx ファイルと .png ファイルのコピー実行（上書き許可）
echo .tmx ファイルをコピー中...
copy /Y "%SOURCE_ROOT%\*.tmx" "%DEST_PATH%\"

echo .tsx ファイルをコピー中...
copy /Y "%SOURCE_ROOT%\*.tsx" "%DEST_PATH%\"

echo .png ファイルをコピー中...
copy /Y "%SOURCE_ROOT%\*.png" "%DEST_PATH%\"

echo.
echo すべてのコピー処理が完了しました。
pause