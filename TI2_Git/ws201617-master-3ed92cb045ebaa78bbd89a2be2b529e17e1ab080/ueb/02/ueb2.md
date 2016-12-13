# Aufgabe 1 (4 Punkte)

Unter `/home/ti2/ueb/02/aufgabe1` findet ihr einige Dateien mit einem
128 Byte langen ID3v1-Tag[^1]. Schreibt ein Shellscript mit dem Namen
`mp3-rename.sh`, das (im Rahmen der Möglichkeiten von `bash`) eine
beliebige Anzahl an Dateinamen als Argument entgegennimmt und jede
dieser Dateien nach folgenden Regeln umbenennt:

* Sind Künstler, Album, Titel und Tracknummer verfügbar, so wird die
  Datei entsprechend des Musters *Kuenstler-Album-Titel-NN.mp3*
  benannt. Alle Leerzeichen und Minuszeichen in *Kuenstler*, *Album*
  und *Titel* werden durch Unterstriche ersetzt. Der Tracknummer *NN*
  wird eine Null vorangestellt, wenn sie kleiner ist als 10.

* Fehlen entweder Kuenstler, Album oder Titel, so wird das betreffende
  Feld durch einen Unterstrich ersetzt.

* Fehlt die Tracknummer, so wird der Anteil im Dateinamen *-NN* weggelassen.

Hinweis: Für diese Aufgabe werden Hilfsprogramme wie `tail`, `tr`,
`cut`, `echo` und bash-Funktionen wie `read`, `basename`, `while`
benötigt. Der „Advanced Bash-Scripting Guide“[^2] bietet einen
hervorragenden Einstieg in die Programmierung mit bash.

[^1]: Siehe \url{https://en.wikipedia.org/wiki/ID3\#Layout} für eine Beschreibung
      des Formats.
[^2]: Siehe  \url{http://www.tldp.org/LDP/abs/html/}.
      
# Aufgabe 2 (5 Punkte)

Unter `/home/ti2/ueb/02/aufgabe2` findet ihr ein einfaches Programm zur
Berechnung der Fibonacci-Folge. Die Dateien `main.s`, `fib.s` und
`show.s` enthalten eine stark vereinfachte Version des Assemblercodes,
den der C++-Compiler auf einem LP64-System erzeugt hat. Die
verwendeten Symbole für den Linker orientieren sich an der Notation
aus der Vorlesung. Der Suffix `m` steht hier für `unsigned long`.

a. Gebt zu jeder der drei Assemblerdateien die
   Text/Data-Relocation-Table, Symboltabelle und Stringtabelle für das
   `a.out`-Format an wie in der Vorlesung gezeigt. Geht dazu von der
   Annahme aus, dass jede Instruktion vier Bytes benötigt, Adressen
   sind acht Bytes lang. Einträge in der Text/Data-Relocation-Table
   und der Symboltabelle sind vier Bytes lang.

b. Nehmt an, ein Linker würde die drei Objektdateien in der
   Reihenfolge `main.o`, `fib.o` und `show.o` als a.out-Datei
   zusammenbinden. Welche Symbole könnten mit pc-relativen Sprüngen
   ausgedrückt werden? Gebt die berechneten Offsets für diese Sprünge
   an!

c. Warum wäre die so erzeugte a.out-Datei so noch nicht ausführbar?
   Welche Informationen müsste der Linker neben den in Teilaufgabe b
   berechneten pc-relativen Sprüngen noch hinzufügen?

# Aufgabe 3 (1 Punkt)

Unter `/home/ti2/ueb/02/aufgabe3` findet ihr ein Programm `geheim`,
das euch nach einem Passwort fragt. Findet mit Hilfe des Programms
*gdb* heraus, wie das Passwort lautet. Dokumentiert eure
Vorgehensweise. Warum „weiß“ *gdb* soviel über das Programm, obwohl
nur der Maschinencode vorliegt?

<!--  LocalWords:  
 -->

<!-- Local Variables: -->
<!-- coding: utf-8 -->
<!-- ispell-local-dictionary: "german-new8" -->
<!-- End: -->
