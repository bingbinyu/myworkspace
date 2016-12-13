# Musterlösung Übungsblatt 2, Aufgabe 1

`mp3-rename.sh`

* Über Argumentliste iterieren
* Heraussschneiden der letzten 128 Byte (z. B. `tail`)
* Prüfen auf Zeichenkette "TAG" in den ersten drei Bytes.
* Auslesen der Felder title, artist, album
* Auslesen der Tracknummer, mit Prüfung, ob drittletztes Byte den Wert 0 hat
* Leere Felder title, artist, album behandeln
* Leerzeichen und Minuszeichen in title, artist, album ersetzen
* Tracknummer auf zwei Ziffern padden, wenn kleiner als 100
* Dateinamen zusammensetzen

Und wie immer: **Testen**

# Musterlösung Übungsblatt 2, Aufgabe 2

\includegraphics[height=.8\textheight]{symtbl_03}

# Musterlösung Übungsblatt 2, Aufgabe 2

\includegraphics[height=.8\textheight]{symtbl_02}

# Musterlösung Übungsblatt 2, Aufgabe 2

\includegraphics[height=.8\textheight]{symtbl_01}

# Musterlösung Übungsblatt 2, Aufgabe 2

Ausführbare Datei erfordert mindestens Laufzeitumgebung und
ggf. weitere Bibliotheken (z. B. für `cout` und `strtol()`).

# Musterlösung Übungsblatt 2, Aufgabe 3 # {.shrink} 

Beispielsession:

\scriptsize{}

         x03-> gdb ./geheim
         ...
         (gdb) info functions
         All defined functions:

         File geheim.cc:
         bool check_password(char const*);
         int main();
         bool set_echo(bool);
         ...
         (gdb) disass main
         ...
         (gdb) disass check_password

#

Beobachtungen:

1. In dem Programm passiert soweit erstmal nichts Böses
2. In `check_password` gibt es zwei Vergleiche. Nach dem zweiten wird 0x64 mal an Funktionsbeginn+88 gesprungen. `%rdx` scheint eine Laufvariable zu sein.
3. Der Vergleich in +93 könnte demnach interessant sein.
4. Ansonsten gibt es wenig Hinweise auf statische Zeichenketten.

#

Setzen eines Breakpoints auf +93 und Programm laufenlassen:
\scriptsize{}

         (gdb) b *0x0000000000400f6d
         Breakpoint 1 at 0x400f6d: file geheim.cc, line 35.
         (gdb) r
         Starting program: /home/ti2/ueb/02/aufgabe3/geheim 
         Bitte das Passwort eingeben: 

         Breakpoint 1, 0x0000000000400f6d in check_password (
             input=input@entry=0x601880 "foo") at geheim.cc:35
         35	geheim.cc: No such file or directory.

#

Unsere Eingabe sehen wir als Argument der Funktion. Was gibt es sonst noch?
\scriptsize{}

      (gdb) where full
         #0  0x0000000000400f6d in check_password (input=input@entry=
             0x601880 "foo")
             at geheim.cc:35
                 i = <optimized out>
                 pass = "TeI2-ist_einfach", '\000' <repeats 83 times>
                 ok = <optimized out>
         #1  0x0000000000400c28 in main () at geheim.cc:59
                 ok = <optimized out>

#

Vielleicht ist `pass` das Passwort:
\scriptsize{}
 
        (gdb) disable 1
        (gdb) c
        Continuing.
        Leider nein :-(
        Bitte das Passwort eingeben: 

        Das war richtig!
        [Inferior 1 (process 3398) exited normally]

# Zusatzfrage

## Warum „weiß“ *gdb* soviel über das Programm, obwohl nur der Maschinencode vorliegt?

$\rightarrow$ Debuginformationen (Compileroption `-g`)

# Übungsblatt 4 (Abgabe: 28.11.2016)

## Aufgabe 1 (5 Punkte)

* Prozesse starten (ggf. im Hintergrund)
* Aufruf auf Kommandozeile, mehrere Argumente möglich
* Vorgabe in `/home/ti2/ueb/04`: (ggf. `flex` installieren)


* Systemaufrufe: `getenv()`, `fork()`, `execv()`, `wait()`
* Signalhandler für `SIGCHLD` $\rightarrow$ `sigaction()`
      * `SA_RESTART` setzen
* Fehlerbehandlung
* Vordergrundprozess

# und viel testen!

Beispielaufruf: **./ti2sh**

~~~~
ti2sh$ ls -l
ti2sh$ sleep 10 &
ti2sh$ echo foo
ti2sh$ bla/fasel
ti2sh$ sleep 100
~~~~

Wie unterscheiden sich die Aufrufe `/bin/ls` und `ls`?

# Aufgabe 2 (2 Punkte)

## Aufgabe 2: Buddy-Algorithmus

Zu Beginn ein Block mit 64 KiB ab Adresse 0.

a) Speicheranforderungen abarbeiten  
   Skizze: Welche Blöcke werden vergeben, welche bleiben frei, *welche Adressen*?
b) Freigabe von drei Blöcken. Wie sieht die Speichersituation nun aus? Kann die nächste Anforderung erfüllt werden?

In dieser Aufgabe:  Blöcke werden nur bis zur Mindestgröße von 4 KiB aufgespalten.

# Beispiel (ohne Mindestgröße)

1-KiB-Block  
Anforderungen: 100 B, 87 B, 512 B, 39 B

\includegraphics[height=.6\textheight]{buddy_01}

# Beispiel (ohne Mindestgröße)

Freigabe von 100 B, 87 B, später 39 B

\includegraphics[height=.6\textheight]{buddy_02}


# Aufgabe 3 (3 Punkte)

## Eine Befehlsfolge

~~~~
$ bash
$ sleep 20 &
$ emacs &
$ bash
$ date
~~~~

#

\includegraphics{proc_example2}

<!--  LocalWords:  
 -->

<!-- Local Variables: -->
<!-- coding: utf-8 -->
<!-- ispell-local-dictionary: "german-new8" -->
<!-- End: -->
