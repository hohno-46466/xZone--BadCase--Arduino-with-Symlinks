# xZone--BadCase--Arduino-with-Symlinks

Bad case of Arduino sketche with symbolic links

### ディレクトリ構成

    ./xZone--BadCase--Arduino-with-Symlinks
     ├── README.md
     ├── common
     │   ├── dir1
     │   │   └── file1.h
     │   └── dir2
     │       └── file2.h
     └── sketch_BadSketch_20220507
         ├── README-01.txt
         ├── README.md
         ├── file1.h -> ../common/dir1/file1.h
         ├── file2.h -> ../common/dir2/file2.h
         ├── re-link.bat
         └── sketch_BadSketch_20220507.ino
     
     4 directories, 9 files (Sun May  8 02:32:28 JST 2022)


See also ./sketch_BadSketch_20220507/README-01.txt


### これは何？

上記のような構成のディレクトリを git clone（など）で作り，sketch_BadSketch_20220507 にある sketch_BadSketch_20220507.ino を Arduino IDE でビルドすることを考える．なお，sketch_BadSketch_20220507.ino 内では file1.h と file2.h を #include している．
このとき Linux やmac OS では問題なくビルドできるが Windows ではエラーになる．

これは，git で上記のディレクトリ構成を clone や pull すると sketch_BadSketch_20220507 内の file1.h と file2.h が SYMLINK ではなく JUNCTION　として作られるからだと思われる．

上記のディレクトリにあるバッチファイル re-link.bat は，ディレクトリ内の JUNCTION を消去してシンボリックリンクを作り直す働きをする（これは WSL で動く別のシェルスクリプトで生成しているが詳細はここでは省略）

このようにして JUNCTION を SYMLINK　に作り直せば Windows 上の Arduino IDE でも問題なくビルドできる

こうしてシンボリックリンクを作り直した状態で git push するとリポジトリ上のファイルも更新されるが，これを Linux や macOS で pull した場合，特に問題なく POSIXシンボリックリンクとして生成される。

