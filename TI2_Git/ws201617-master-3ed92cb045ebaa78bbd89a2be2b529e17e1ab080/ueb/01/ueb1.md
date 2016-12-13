# Aufgabe 0 (0 Punkte, einzeln zu bearbeiten)

Die Referenzplattform für den Übungsbetrieb zu Technische Informatik 2
sind die x-Rechner im Pool des Fachbereichs 3. Ihr müsst Eure
Programme daher auf diesen entwickeln oder zumindest anschließend dort
testen. Hierfür müsst Ihr Euch auf den x-Rechnern einloggen und auf
Shell-Ebene auf ihnen arbeiten können.

Loggt Euch von einem anderen Rechner (z.B. Eurem eigenen Notebook)
aus auf einem der x-Rechner (`x01` bis `x24`) ein. Hierfür müsst
Ihr ggf. einen SSH-Client installieren und ein entsprechendes
Schlüsselpaar generieren. Eine Anleitung dazu findet ihr im Wiki in
Stud.IP.

Schaut Euch anschließend in eurem Home-Verzeichnis um und lernt, auf
Shell-Ebene im Dateibaum zu navigieren. Kopiert testweise Dateien von
eurem Rechner in euer Heimverzeichnis.[^1] Legt Euch dort ggf. ein
Arbeitsverzeichnis für diese Veranstaltung an.

[^1]: Eine sehr komfortable Möglichkeit dafür bietet SSHFS.

Hinweis: Im Rahmen dieser Veranstaltung sollte jeder aus eurer Gruppe
in der Lage sein, sich unter seinem eigenen Account mittels SSH auf
einem der x-Rechner einzuloggen und Befehle auf der Kommandozeile
auszuführen.

# Aufgabe 1 (4 Punkte)

In Unix-artigen Betriebssystemen werden alle Geräte wie Dateien
behandelt. Dies betrifft auch den Standardeingabekanal `STDIN` und die
Ausgabekanäle `STDOUT` (Standardausgabe) und `STDERR` (Fehler) eines
Programms. Ein Benutzer kann beim Aufruf eines Programms zum Beispiel
entscheiden, ob die Eingabe aus einer Datei gelesen oder die Ausgabe
in eine Datei geschrieben werden soll. Erläutert anhand der folgenden
Kommandofolge für jede Zeile, was genau dort passiert. (Wird eine
Anweisungsfolge in Klammern gesetzt, so erzeugt der Shellprozess dafür
einen eigenen Kindprozess, für den Eingabe- und Ausgabeumlenkung
verwendet werden kann und der weitere Kindprozesse erzeugen kann.

~~~~
echo "Hallo Wurzel" >wurzel
echo "Wurzelverzeichnis: " >wurzel
ls -l / >>wurzel
(tail -n +3 |cut -b2-4,43-) <wurzel |sort -k2
~~~~

Hinweis: Es wird vorausgesetzt, dass die aufgerufenen Kommandos
verfügbar sind und sich im aktuell gesetzten Ausführungspfad
befinden. Der Nutzer besitzt Schreibrechte im aktuellen Verzeichnis,
die `umask` hat den Wert `022`. Das aktuelle Verzeichnis enthält vor
Ausführung der gezeigten Sequenz keine regulären Dateien.

Eine bloße Beschreibung der sichtbaren Auswirkungen auf Shell-Ebene
reicht nicht aus. Was passiert mit Eingaben und Ausgaben? Wo werden
neue Prozesse erzeugt? Welches Programm wird jeweils ausgeführt?

# Aufgabe 2 (6 Punkte)

Entwickelt eine einfaches Werkzeug `myfind` zum Auffinden von Dateien
und Verzeichnissen in einem Verzeichnisbaum. Das erste Argument von
`myfind` ist ein Pfad, ab dem gesucht wird. Danach können null oder
mehr Argumente in beliebiger Reihenfolge folgen, mit denen die Ausgabe
eingegrenzt wird:

* Das Argument `-type T` dient zur Eingrenzung des Dateityps. *T* ist
  ein Buchstabe aus der Menge $\{s,l,f,b,d,c,p\}$ entsprechend der
  Dateitypen `S_IFSOCK`, `S_IFLNK`, `S_IFREG`, `S_IFBLK`.  `S_IFDIR`,
  `S_IFCHR`, `S_IFIFO`, die vom Aufruf `lstat()` im Ergebnisfeld
  `st_mode` zurückgeliefert werden. (Die Auswertung der Rechte erfolgt
  über Bitfelder, vgl. `man lstat`.)

* Das Argument `-name N` dient zur Eingrenzung der gefundenen Einträge
  auf den angegebenen Namen *N* (ohne Unterstützung von Wildcards).

* Das Argument `-suffix S` grenzt die gefundenen Einträge auf alle
  Einträge mit der Endung *.S* ein (d.h. der Punkt wird beim Aufruf nicht
  mit angegeben.

* Das Argument `-newer F` grenzt die gefundenen Einträge auf alle
  Einträge ein, deren letzte Änderung neuer ist als die letzte Änderung
  der Datei mit dem Namen *F*.
  
`myfind` soll rekursiv durch alle Unterverzeichnisse gehen, die bei
der Suche gefunden werden. Symbolische Links werden aber *nicht*
aufgelöst (um euch auf einfache Weise Endlosschleifen zu
ersparen). Das Argument `-newer` bezieht sich aber immer auf das Ziel
eines Symbolic Link, nicht auf den Link selbst (hier müsst ihr
aufpassen mit Endlosschleifen, aber der Systemaufruf `stat` fängt dies
normalerweise ab). Werden mehrere Argumente angegeben, so bedeutet
dies implizit eine logische Und-Verknüpfung. Der Aufruf `myfind
. -type p -name myfifo` würde alle *named pipes* mit dem Namen „myfifo“
liefern, die sich im aktuellen Verzeichnis oder einem Unterverzeichnis
des aktuellen Verzeichnisses befinden.

Wir haben Euch hierzu unter `/home/ti2/ueb/01` ein Gerüst für eine
Implementierung vorgegeben[^2], das jedoch nicht vollständig ist und
insbesondere noch keinen Code für die relevanten Systemaufrufe
enthält.  Der Sinn dieser Aufgabe ist es, sich mit den relevanten
Bibliotheksfunktionen und Datenstrukturen vertraut zu machen.

[^2]: Siehe auch Aufgabe 0.

Kopiert euch die Dateien und ergänzt die Dateien `myfind.cc` und
`filter.cc` um die fehlende Funktionalität in den Funktionen
`process()` und `matches()` an den jeweils angegebenen Stellen. Die
anderen Dateien dürfen nicht verändert werden. Ihr benötigt für das
Auslesen eines Verzeichnisses die Funktionen `opendir()`, `readdir()`
und `closedir()`, ferner `stat()` und `lstat()` für das Auslesen von
Dateiattributen. Die Manual Pages zu diesen Systemfunktionen enthalten
auch Code-Beispiele!  Eine Implementierung mittels `scandir()`,
`ftw()` o.ä. ist hier nicht zulässig.

Bedenkt, dass Operationen scheitern können; Ihr müsst also mögliche
Fehler bzw.  entsprechende Rückgabewerte von Systemaufrufen
(insbesondere `NULL`) behandeln. Treten bei einem Systemaufruf Fehler
auf, so soll eine entsprechende Fehlermeldung mittels
`strerror(errno)` auf dem Ausgabestrom `std::cerr` ausgeben werden.

Die von euch entwickelte Lösung soll nachvollziehbar dokumentiert und
lauffähig sein. Aus der Dokumentation soll hervorgehen, wie das
Programm funktioniert und wo eventuelle Einschränkungen
liegen. Kommentierte Tests dienen als Nachweis dieser
Funktionalität. Daher muss aus der Kommentierung der Tests auch
deutlich werden, warum ihr glaubt, dass diese Tests den behaupteten
Funktionsumfang abdecken. Die Kommandos `mkdir`, `mkfifo`, `ln` und
`touch` können euch beim Erzeugen von Testfällen helfen.

<!--  LocalWords:  
 -->

<!-- Local Variables: -->
<!-- coding: utf-8 -->
<!-- ispell-local-dictionary: "german-new8" -->
<!-- End: -->
