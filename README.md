# xZone--BadCase--Arduino-with-Symlinks

Bad case of Arduino sketche with symbolic links

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

