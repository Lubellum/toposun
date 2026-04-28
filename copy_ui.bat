@echo off
setlocal enabledelayedexpansion

:: --- 設定エリア ---
set SOURCE_ROOT="C:\Project\GitHub\Toposun\toposun\authoring\ui\Export"
set DEST_PATH="C:\Project\GitHub\Toposun\toposun\Resources\json"

echo コピー処理を開始します...
echo.

:: 1. 出力先フォルダの存在チェック
if not exist "%DEST_PATH%" (
    echo 【エラー】出力先フォルダが見つかりません。
    echo 対象パス: "%DEST_PATH%"
    echo 処理を中断します。
    pause
    exit /b
)

:: 2. Export内の各サブフォルダをループで処理
for /d %%F in ("%SOURCE_ROOT%\*") do (
    echo フォルダを処理中: %%~nxF
    
    :: フォルダ直下のファイルをコピー（上書き許可）
    copy /Y "%%F\*" "%DEST_PATH%\"
)

echo.
echo すべてのコピー処理が完了しました。
pause