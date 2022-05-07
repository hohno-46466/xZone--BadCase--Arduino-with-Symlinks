
# ------------------------------------------------------------------------------
# (1) git clone したての状態で ls -l を実行．file1.h と file2.h はシンボリックリンクになっている
# ------------------------------------------------------------------------------

$ ls -l

lrwxrwxrwx 1 hohno hohno  22 May  8 02:03 file1.h -> ../common/dir1/file1.h
lrwxrwxrwx 1 hohno hohno  22 May  8 02:03 file2.h -> ../common/dir2/file2.h
-rw-r--r-- 1 hohno hohno 124 May  8 02:03 re-link.bat
-rw-r--r-- 1 hohno hohno 219 May  8 02:03 sketch_BadSketch_20220507.ino


# ------------------------------------------------------------------------------
# (2) cmd.exe で dir すると SYMLINK ではなく JUNCTION になっている
# ------------------------------------------------------------------------------

$ cmd.exe /c dir

 Volume in drive C has no label.
 Volume Serial Number is D89C-CEB2

 Directory of C:\Users\hohno\Desktop\GitHub4winFS\xZone--BadCase--Arduino-with-Symlinks\sketch_BadSketch_20220507

2022/05/08  02:03    <DIR>          .
2022/05/08  02:03    <DIR>          ..
2022/05/08  02:03    <JUNCTION>     file1.h [...]
2022/05/08  02:03    <JUNCTION>     file2.h [...]
2022/05/08  02:03               124 re-link.bat
2022/05/08  02:03               219 sketch_BadSketch_20220507.ino
               4 File(s)            343 bytes
               2 Dir(s)  103,790,694,400 bytes free
total 0

# ------------------------------------------------------------------------------
# (4) この時，WSL 上の arduino-cli を使えば sketch_BadSketch_20220507.ino を問題なくビルド可能
# ------------------------------------------------------------------------------

$ arduino-cli compile -b arduino:avr:uno
`
Sketch uses 1708 bytes (5%) of program storage space. Maximum is 32256 bytes.
Global variables use 190 bytes (9%) of dynamic memory, leaving 1858 bytes for local variables. Maximum is 2048 bytes.

# ------------------------------------------------------------------------------
# (4) しかし， Windows の Arduino IDE で ビルドすると以下のように失敗
# ------------------------------------------------------------------------------

Error during sketch processing: CreateFile C:\Users\hohno\Desktop\GitHub4winFS\xZone--BadCase--Arduino-with-Symlinks\sketch_BadSketch_20220507\file1.h: The file cannot be accessed by the system.

Error compiling for board Arduino Uno.

# ------------------------------------------------------------------------------
# (5) re-link.bat の内容を確認
# ------------------------------------------------------------------------------

$ cat re-link.bat

del file1.h
cmd.exe /c mklink  file1.h ..\common\dir1\file1.h
del file2.h
cmd.exe /c mklink  file2.h ..\common\dir2\file2.h

# ------------------------------------------------------------------------------
# (6) 管理者モードのコマンドプロンプトで re-linik.bat を実行
# ------------------------------------------------------------------------------

C:> re-link.bat

C:> del file1.h
C:> cmd.exe /c mklink  file1.h ..\common\dir1\file1.h
file1.h <<===>> ..\common\dir1\file1.h のシンボリック リンクが作成されました

C:> del file2.h
C:> cmd.exe /c mklink  file2.h ..\common\dir2\file2.h
file2.h <<===>> ..\common\dir2\file2.h のシンボリック リンクが作成されました

# ------------------------------------------------------------------------------
# (7) 再び ls -l を実行．タイムスタンプは変更になっているがシンボリックリンクは健在
# ------------------------------------------------------------------------------

$ ls -l

lrwxrwxrwx 1 hohno hohno  22 May  8 02:05 file1.h -> ../common/dir1/file1.h
lrwxrwxrwx 1 hohno hohno  22 May  8 02:05 file2.h -> ../common/dir2/file2.h
-rw-r--r-- 1 hohno hohno 124 May  8 02:03 re-link.bat
-rw-r--r-- 1 hohno hohno 219 May  8 02:03 sketch_BadSketch_20220507.ino
 Volume in drive C has no label.
 Volume Serial Number is D89C-CEB2

 Directory of C:\Users\hohno\Desktop\GitHub4winFS\xZone--BadCase--Arduino-with-Symlinks\sketch_BadSketch_20220507

# ------------------------------------------------------------------------------
# (8) cmd.exe /c dir してみると file1.h と file2.h は JUNCTION ではなく SYMLINK になっている
# ------------------------------------------------------------------------------

$ cmd.exe /c dir

2022/05/08  02:05    <DIR>          .
2022/05/08  02:05    <DIR>          ..
2022/05/08  02:05    <SYMLINK>      file1.h [..\common\dir1\file1.h]
2022/05/08  02:05    <SYMLINK>      file2.h [..\common\dir2\file2.h]
2022/05/08  02:03               124 re-link.bat
2022/05/08  02:03               219 sketch_BadSketch_20220507.ino
               4 File(s)            343 bytes
               2 Dir(s)  103,793,381,376 bytes free

 Volume in drive C has no label.
 Volume Serial Number is D89C-CEB2

# ------------------------------------------------------------------------------
# (9) Windows の Arduino IDE で ビルドすると正常にビルドできる
# ------------------------------------------------------------------------------

Sketch uses 1708 bytes (5%) of program storage space. Maximum is 32256 bytes.
Global variables use 190 bytes (9%) of dynamic memory, leaving 1858 bytes for local variables. Maximum is 2048 bytes.

# ------------------------------------------------------------------------------

