# Arbeitssitzung am 17.11.2016

* wie gewohnt um 12 Uhr im kleinen Hörsaal
* nur anwesende Gruppenmitglieder können Punkte erhalten

# Musterlösung Übungsblatt 1, Aufgabe 1

~~~~
echo "Hallo Wurzel" >wurzel
~~~~

Prozess `echo`, Umlenken der Ausgabe in neue Datei `wurzel`.

~~~~
echo "Wurzelverzeichnis: " >wurzel
~~~~

Prozess `echo`, Umlenken der Ausgabe in Datei `wurzel` (alter Inhalt
wird überschrieben).

~~~~
ls -l / >>wurzel
~~~~

Prozess `ls`, Umlenken der Ausgabe in Datei `wurzel` (Inhalt wird
angehängt).

# Musterlösung Übungsblatt 1, Aufgabe 1 (Fortsetzung)

~~~~
(tail -n +3 |cut -b2-4,43-) <wurzel |sort -k2
~~~~

* Neuer Kindprozess, in dem die Kindprozesse `tail` und `cut` gestartet werden.
* Eingabeumlenkung des Inhalts der Datei Wurzel an den Enkelprozess (`tail`).
* Die Ausgabe von `tail` wird auf den Standardeingabekanal von `cut` geschickt.
* Neuer Prozess `sort`. Ausgabe des ersten Kindprozesses wird auf den
  Standardeingabekanal von `sort` geschickt.

# Musterlösung Übungsblatt 1, Aufgabe 2

**in `process()`:**

* Rekursive Verarbeitung von Einträgen
* Unterscheidung reguläre Datei/Verzeichnis
* Aufruf von `opendir()`
* Verzeichniseinträge mit `readdir()` lesen
* Behandlung von d_name, Sonderfälle '.' und '..'
* Aufruf von `closedir()`

# Musterlösung Übungsblatt 1, Aufgabe 2 (Fortsetzung)

**Matcher-Funktionen**

* `TypeMatcher::matches()`:
    * lstat() auf path
    * `st_mode & S_IFMT` mit ifmt vergleichen

* `FilenameMatcher::matches()`:
     * letzte Pfadkomponente von path mit filename vergleichen

* `NewerMatcher::matches()`:
     * `stat()` auf path, mtime mit mit `st.st_mtime` vergleichen
     * ggf. `good` berücksichtigen

**Tests**

# Übungsblatt 3 (Abgabe: 21.11.2016)

## Aufgabe 1 (4 Punkte)

`ls -lR / >ausgabe`

1. Eingabe von **Strg-Z** (Ctrl-Z) während `ls`-Prozess läuft.
2. In den Hintergrund mit `bg`.
3. Warten, bis alles fertig ist.

**Aufgabe:**
Wo gibt es Traps/Interrupts/Signale (sinnvoll zusammenfassen)?
Welche Zustandsänderungen beteiligter Prozesse werden damit jeweils
bewirkt?

Hinweis: Es werden acht aus weit über 20 möglichen sinnvollen
Antworten erwartet.

# Aufgabe 2 (2 Punkte)

* Signalhandler für *SIGUSR1* installieren
  (`man sigaction 7 signal`).
* `sa_flags` auf `SA_SIGINFO` setzen.
* Signalnummer, Prozess-ID und User-ID des Senders auswerten und im Signalhandler ausgeben (uuuuh, scary).
* Testen mit dem Kommando `kill` ($\rightarrow$ `man kill`).

# Aufgabe 3 (4 Punkte)

* feste Zeitscheibenlänge, Scheduling alle 200 ms
* Prozessauswahl richtet sich nach Kontostand und Basispriorität  
  $Konto_{i+1} := trunc(\frac{Konto_i + Nutzung_{i}}{2})$

**Beispiel:**  
Prozess A (Basispriorität 50),  
Prozess B (Basispriorität 0)

# Beispieltabelle

A, B lauffähig, $Prio(A) = 50, Prio(B) = 0$


\scriptsize{}

|            |  0 |       1 |       2 |       3 |       4 |       5 |       6 |       7 |       8 |       9 |      10 |
|------------+----+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
| Konto(A)   |  0 |       0 |       0 |      50 |      25 |      12 |      56 |      28 |      14 |      57 |      28 |
| Nutzung(A) |  0 |       0 | **100** |       0 |       0 | **100** |       0 |       0 | **100** |       0 |       0 |
| Konto'(A)  |  0 |       0 |      50 |      25 |    *12* |      56 |      28 |      14 |      57 |    *28* |      14 |
| Prio(A)    | 50 |      50 |     100 |      75 |      62 |     106 |      78 |      64 |     107 |      78 |      64 |
|            |    |         |         |         |         |         |         |         |         |         |         |
| Konto(B)   |  0 |       0 |      50 |      25 |      62 |      81 |      40 |      70 |      85 |      42 |      71 |
| Nutzung(B) |  0 | **100** |       0 | **100** | **100** |       0 | **100** | **100** |       0 | **100** | **100** |
| Konto'(B)  |  0 |      50 |      25 |    *62* |      81 |    *40* |      70 |      85 |    *42* |      71 |    *85* |
| Prio(B)    |  0 |      50 |      25 |      62 |      81 |      40 |      70 |      85 |      42 |      71 |      85 |

<!--  LocalWords:  
 -->

<!-- Local Variables: -->
<!-- coding: utf-8 -->
<!-- ispell-local-dictionary: "german-new8" -->
<!-- End: -->
