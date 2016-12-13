#!/usr/bin/env bash

echo "--- Starte Test:"
echo ""
echo "--- Verzeichnisse:"
ls
echo "--- Unterverzeichnis:"
cd the\ programmer
ls
cd ..
echo ""
echo "--- umbenennen:"
./mp3-rename.sh track1.mp3 track2.mp3 track3.mp3 track4.mp3 track5.mp3 track6.mp3 track7.mp3 unknown
echo ""
echo "--- umbenennen2:"
cd the\ programmer
./../mp3-rename.sh bugs.mp3 mt.unsafe.mp3 recursion.mp3
cd ..
echo ""
echo "--- Verzeichnisse danach:"
ls
echo "--- Unterverzeichnis:"
cd the\ programmer
ls
cd ..
echo ""
echo "--- fertig"

