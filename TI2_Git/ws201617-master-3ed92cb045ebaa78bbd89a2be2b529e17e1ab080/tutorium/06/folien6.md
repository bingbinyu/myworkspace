# Organisatorisches

\LARGE{}

Bitte wählt beim Upload eine geeignete Lizenzierungsoption aus:

# Der Default ist ungeeignet:

![](pic/lizenz01.pdf)\ 

# Selbstverfasste, nicht publizierte Werke

![](pic/lizenz02.pdf)\ 

# Nachträgliche Änderung

Bitte sendet eine formlose Nachricht per Stud.IP an `obergman` oder
mit formloser E-Mail an `bergmann@tzi.org`, um die Lizenzoption
nachträglich zu ändern.

# Musterlösung Übungsblatt 3, Aufgabe 1

* Interrupts nach Tastendrücken ($\rightarrow$ Pufferspeicher fast voll)
* Interrupts nach Zugriffen auf Festplatte
* Blockierende Operationen: Prozesszustand *asleep* $\rightarrow$ *ready-to-run* $\rightarrow$ *running*
* Systemaufrufe zum Öffnen, Lesen, Schreiben von Dateien ($\rightarrow$ Traps)
* `fork()`, `exec(ls)`: Systemaufrufe, später Signale an Vaterprozess
* Kindprozess nach Ende im Zustand `SZOMB`

# Musterlösung Übungsblatt 3, Aufgabe 2

* `struct sigaction` anlegen und initialisieren:  
  `sa_mask`, `sa_flags`, `sa_sigaction`
* Setzen des Signalhandlers mit `sigaction()`
* Aufruf von `pause()` in Endlosschleife
* Signalhandler

# Musterlösung Übungsblatt 3, Aufgabe 3

a. monotones Anwachsen des Kontostands, jüngere Prozesse werden bevorzugt, möglicher Integer-Overflow
b. Prozess A kommt doppelt so häufig an die Reihe wie B, das sich wiederholende Muster ist BBA (siehe Tabelle).

# Musterlösung Übungsblatt 3, Aufgabe 3 b)

\scriptsize{}

| t    |  0 |   1 |  2 |   3 |  4 |   5 |  6 |   7 |  8 |   9 | 10 |  11 | 12 |
|------+---:+----:+---:+----:+---:+----:+---:+----:+---:+----:+---:+----:+---:|
| K_A  |  0 |   0 |  0 |  50 | 25 |  12 | 56 |  28 | 14 |  57 | 28 |  14 | 57 |
| N_A  |  0 |   0 |100 |   0 |  0 | 100 |  0 |   0 |100 |   0 |  0 | 100 |  0 |
| K'_A |  0 |   0 | 50 |  25 | 12 |  56 | 28 |  14 | 57 |  28 | 14 |  57 | 28 |
| P_A  | 56 |  56 |106 |  81 | 68 | 112 | 84 |  84 |113 |  84 | 70 | 113 | 84 |
| K_B  |  0 |   0 | 50 |  25 | 62 |  81 | 40 |  70 | 85 |  42 | 71 |  85 | 42 |
| N_B  |  0 | 100 |  0 | 100 |100 |   0 |100 | 100 |  0 | 100 |100 |   0 |100 |
| K'_B |  0 |  50 | 25 |  62 | 81 |  48 | 70 |  85 | 42 |  71 | 85 |  42 | 71 |
| P_B  | 10 |  60 | 35 |  72 | 91 |  50 | 80 |  95 | 52 |  81 | 95 |  52 | 81 |


# Musterlösung Übungsblatt 3, Aufgabe 3 c)

c. Arithmetische Reihe $\frac{100}{2} + \frac{100}{4} + \frac{100}{8} + \dots$:  
   $\sum_{n=1}^{\infty} \frac{100}{2^n} = 100 \cdot \sum_{n=1}^{\infty} \frac{1}{2^n} = 100$  
   (Kontostand von A kann nie größer werden als trunc((99+100)/2) == 99
   $\rightarrow$ B kommt bei Basispriorität > 99 nie an die Reihe.)

# Musterlösung Übungsblatt 3, Aufgabe 3 d)

\scriptsize{}

| t    |  0 |   1 |  2 |   3 |  4 |   5 |  6 |   7 |  8 |   9 | 10 |  11 | 12 |
|------+---:+----:+---:+----:+---:+----:+---:+----:+---:+----:+---:+----:+---:|
| K_A  |  0 |   0 | 50 |  61 | 80 |  76 | 88 |  80 | 90 |  81 | 90 |  81 | 90 |
| N_A  |  0 | 100 | 72 | 100 | 72 | 100 | 72 | 100 | 72 | 100 | 72 | 100 | 72 |
| K'_A |  0 |  50 | 61 |  80 | 76 |  88 | 80 |  90 | 81 |  90 | 81 |  90 | 81 |
| P_A  |  0 |  50 | 61 |  80 | 76 |  88 | 80 |  90 | 81 |  90 | 81 |  90 | 81 |
| K_B  |  0 |   0 |  0 |  13 |  6 |  16 |  8 |  17 |  8 |  17 |  8 |  17 |  8 |
| N_B  |  0 |   0 | 27 |   0 | 27 |   0 | 27 |   0 | 27 |   0 | 27 |   0 | 27 |
| K'_B |  0 |   0 | 13 |   6 | 16 |   8 | 17 |   8 | 17 |   8 | 17 |   8 | 17 |
| P_B  | 15 |  15 | 28 |  21 | 31 |  23 | 32 |  23 | 32 |  23 | 32 |  23 | 32 |

# Übungsblatt 5 (Abgabe: 5.12.2016) {.shrink}

## Aufgabe 1 (5 Punkte)

`/home/ti2/ueb/05/factorial`

a) Wo befinden sich die Funktionen `factorial` und `main` im
   Textsegment? (Ausdehnung beachten!)
   
b) Stack*zugriffe* in `factorial`?  
   Ausgangswert von `%rsp` ist `0x7fffffffdf60`

c) Von `printf` in `main` gelesener Format-String? (Ausdehnung
   beachten!)

d) Virtuelle Adressen ergeben Page-Nummer und Offset. Ermittelt dazu
   die physischen Adressen.

**Achtung: Diese Aufgabe muss zwingend auf der Referenzplattform
durchgeführt werden.**

# Aufgabe 1

## Beispielrechnung

\small{}

Virtuelle Adresse ist `0x100b`  
Page-Größe ist 2 KiB = 2048 B = 0x0800 B  
Offset von Page-Frame 0 ist `0x20000000`
\vspace{1em}

Page(0x100b) = floor(0x100b/0x800) = 2  
Offset(0x100b) = 0x100b mod 0x800 = 0x0b
\vspace{1em}

Nachschauen in der Page-Tabelle (z. B. Page 2 $\rightarrow$ PF 9293 = 0x244d)
\vspace{1em}

Phys. Adresse: 0x244d $\cdot$ 0x800 + 0x0b + 0x20000000 = 0x2122680B 
\vspace{1em}

**Page-Fault**, wenn Eintrag nicht vorhanden  
$\rightarrow$ wählt einen freien Page-Frame (bitte eindeutig kennzeichnen).

# Aufgabe 2 (2 Punkte)

Wieviele Blöcke werden mindestens benötigt, um eine Datei der Größe 33696325 B auf der Platte zu speichern?  

* Unix-V7-Dateisystem
* Inode-Größe 128 B ($\rightarrow$ ein eigener Block)
* Logische Blockgröße auf Platte hier 512 B (= Sektorgröße)
* jede Dateiblocknummer umfasst vier Bytes
* Indirekt-Blöcke fassen wie Datenblöcke 512 B
* Wieviele Indirekt-Einträge passen in einen Indirekt-Block?
* Wieviele Datenblöcke werden benötigt?
* Wieviele Indirekt-Blöcke werden benötigt?

**Rechnung mit angeben!**

# Aufgabe 3 (3 Punkte)

* Unix-V7-Dateisystem
* Kein Befehl schlägt fehl
* Welcher Block (gehört zu, „Nummer“, Art)?
* Wo liegt er, sofern möglich (Inodes)?
* Warum wird er geladen?

<!--  LocalWords:  
 -->

<!-- Local Variables: -->
<!-- coding: utf-8 -->
<!-- ispell-local-dictionary: "german-new8" -->
<!-- End: -->
