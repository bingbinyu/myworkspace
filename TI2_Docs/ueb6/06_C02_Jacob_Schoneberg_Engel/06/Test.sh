echo "-------------------------------------------------"
echo "Test der korrekten Funktion:"
echo "--------------------------------------"
echo "  kleine Datei (3 Zeichen):"
echo "    Ausführung: solution/mycp solution/littleFile.txt solution/littleFileOut.txt"
sudo solution/mycp solution/littleFile.txt solution/littleFileOut.txt
echo "    Inhalt von littleFileOut.txt:"
sudo cat solution/littleFileOut.txt
echo "\n"
echo "Vergleiche Dateien:"
sudo diff solution/littleFile.txt solution/littleFileOut.txt
echo -e "\n--------------------------------------"
echo "  große Datei (1877443 Zeichen):"
echo "    Ausführung: solution/mycp solution/bigFile.txt solution/bigFileOut.txt"
sudo solution/mycp solution/bigFile.txt solution/bigFileOut.txt
echo "    Inhalt (Erste 2 Zeilen) von bigFileOut.txt:"
sudo head -2 solution/bigFileOut.txt
echo "Vergleiche Dateien:"
sudo diff solution/bigFile.txt solution/bigFileOut.txt
sudo rm solution/littleFileOut.txt
sudo rm solution/bigFileOut.txt
echo "-------------------------------------------------"
echo "Leistungstest (2 Durchläufe):"
echo "--------------------------------------"
echo "  1. Durchlauf"
echo "-----------------------------"
echo "     Referenzimplementierung:"
echo "       Caches leeren und Ausführung: time uni/mycp uni/bigFile.txt uni/bigFileOut.txt"
sudo sh -c "sync; echo 3 > /proc/sys/vm/drop_caches"
sudo time uni/mycp uni/bigFile.txt uni/bigFileOut.txt
echo "       Inhalt (Erste 2 Zeilen) von bigFileOut.txt:"
sudo head -2 uni/bigFileOut.txt
sudo rm uni/bigFileOut.txt
echo "-----------------------------"
echo "     Lösung:"
echo "       Caches leeren und Ausführung: time solution/mycp solution/bigFile.txt solution/bigFileOut.txt"
sudo sh -c "sync; echo 3 > /proc/sys/vm/drop_caches"
sudo time solution/mycp solution/bigFile.txt solution/bigFileOut.txt
echo "       Inhalt (Erste 2 Zeilen) von bigFileOut.txt:"
sudo head -2 solution/bigFileOut.txt
echo "Vergleiche Dateien:"
sudo diff solution/bigFile.txt solution/bigFileOut.txt
sudo rm solution/bigFileOut.txt
echo "--------------------------------------"
echo "  2. Durchlauf"
echo "-----------------------------"
echo "     Referenzimplementierung:"
echo "       Caches leeren und Ausführung: time uni/mycp uni/bigFile.txt uni/bigFileOut.txt"
sudo sh -c "sync; echo 3 > /proc/sys/vm/drop_caches"
sudo time uni/mycp uni/bigFile.txt uni/bigFileOut.txt
echo "       Inhalt (Erste 2 Zeilen) von bigFileOut.txt:"
sudo head -2 uni/bigFileOut.txt
sudo rm uni/bigFileOut.txt
echo "-----------------------------"
echo "     Lösung:"
echo "       Caches leeren und Ausführung: time solution/mycp solution/bigFile.txt solution/bigFileOut.txt"
sudo sh -c "sync; echo 3 > /proc/sys/vm/drop_caches"
sudo time solution/mycp solution/bigFile.txt solution/bigFileOut.txt
echo "       Inhalt (Erste 2 Zeilen) von bigFileOut.txt:"
sudo head -2 solution/bigFileOut.txt
echo "Vergleiche Dateien:"
sudo diff solution/bigFile.txt solution/bigFileOut.txt
sudo rm solution/bigFileOut.txt
echo "-------------------------------------------------"
echo "Test: Leere Eingabedatei"
echo "--------------------------------------"
echo "  Ausführung: solution/mycp solution/emptyIn.txt solution/emptyOut.txt"
sudo solution/mycp solution/emptyIn.txt solution/emptyOut.txt
echo "Vergleiche Dateien:"
sudo diff solution/emptyIn.txt solution/emptyOut.txt
sudo rm solution/emptyOut.txt
echo "-------------------------------------------------"
echo "Test: Leere Eingabe"
echo "--------------------------------------"
echo "  Ausführung: solution/mycp"
sudo solution/mycp
echo "-------------------------------------------------"
echo "Test: Quelldatei = Zieldatei"
echo "  Ausführung: solution/mycp solution/littleFile.txt solution/littleFile.txt"
sudo solution/mycp solution/littleFile.txt solution/littleFile.txt
echo "-------------------------------------------------"
echo "Test: Nur Leserechte"
echo "  Wechsel zum Verzeichnis 'solution'"
cd solution
echo "  Ausführung: chmod 100 solution/littleFile.txt"
sudo chmod 000 littleFile.txt
echo "  Ausführung: mycp littleFile.txt littleFileOut.txt"
sudo ./mycp littleFile.txt littleFileOut.txt
sudo chmod 777 littleFile.txt
sudo rm littleFileOut.txt
echo "-------------------------------------------------"