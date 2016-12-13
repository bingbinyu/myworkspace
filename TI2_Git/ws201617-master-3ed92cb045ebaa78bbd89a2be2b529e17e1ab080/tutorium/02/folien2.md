# Organisatorisches

\Large{}

* Sind euch eure Gruppennummern bekannt?

* Wer ist noch ohne?

* Wo ist ggf. noch Platz?
 
*  Andere Tutorien?

# Übungsblatt 1

Abgabe: 7.11.2016

## Aufgabe 1 (4 Punkte)

* „alles ist eine Datei“
* lesen von STDIN (Eingabe)
* schreiben nach STDOUT (Ausgabe), STDERR
* wo werden (vor allem im vierten Fall) neue Prozesse gestartet?
* welche Dateien werden angelegt, an welche Stelle wird ggf. geschrieben?
   * Punkte gibt's für die Erklärung, nicht für die Dokumentation der Beobachtungen

Hinweis: Die Parameter der aufgerufenen Kommandos sind grundsätzlich
irrelevant, helfen aber beim Verständnis.

# Aufgabe 2 (6 Punkte)

* Vorgabe in `/home/ti2/ueb/01`
* `filter.cc` und `myfind.cc` sind unvollständig
* Funktionen aus Systembibliothek verwenden:
  * `stat()`, `lstat()` (was ist der Unterschied?)  
     Achtung: `man 2 stat` $\ne$ `man stat`
  * `opendir()`, `readdir()`, `closedir()`
  * **Testen!** (mit Testdokumentation)

# man lstat

\scriptsize{}

```
...
int stat(const char *path, struct stat *buf);
int lstat(const char *path, struct stat *buf);
...
struct stat {
      dev_t     st_dev;     /* ID of device containing file */
      ino_t     st_ino;     /* inode number */
      mode_t    st_mode;    /* protection */
...
      off_t     st_size;    /* total size, in bytes */
      blksize_t st_blksize; /* blocksize for filesystem I/O */
      blkcnt_t  st_blocks;  /* number of 512B blocks allocated */
      time_t    st_atime;   /* time of last access */
      time_t    st_mtime;   /* time of last modification */
      time_t    st_ctime;   /* time of last status change */
};
...
RETURN VALUE
  On success, zero is returned.  On error, -1 is returned, and errno
  is set appropriately.
...
```

# Automatische Punktabzüge für schlechtes Programmieren (1/2)

* Programmcode, der nicht kompiliert werden kann, wird als nicht
  abgegeben bewertet (Ausnahme: es wurde Pseudocode oder nur ein
  Programmfragment verlangt)
    
* Programmabsturz zur Laufzeit, sofern es sich nicht um eine
  ausdrücklich dokumentierte Einschränkung handelt (z. B. komplexe
  Corner-Cases).
    
* fehlende oder zu wenig aussagekräftige Dokumentation

* fehlende Tests oder fehlende Kommentierung bei Testfällen, die
  allein nicht aussagekräftig genug sind. **Insbesondere ist auf
  Begründung der Testabdeckung zu achten.**
    
# Automatische Punktabzüge für schlechtes Programmieren (2/2)

* typische Programmierfehler vermeiden
    * richtige Datentypen verwenden!  
      (z. B. `off_t` für `st_size` in `struct stat`)
    * Rückgabewert von Systemaufrufen überprüfen, insbesondere `NULL`
    * dynamischen Speicher freigegeben
    * Dateien schließen
    * Variablen richtig initialisieren
    * sinnvolle Rückgabewerte für Funktionen
    * Arraygrenzen überprüfen

* „Magic Numbers“ statt aussagekräftiger Namen für Konstanten (abhängig von Aufgabenstellung)
* Nebenläufigkeit; kritische Abschnitte nicht geschützt

# Statistische Angaben für Ute

\Large{}

Bitte gebt in eurer Lösung zu Übungsblatt 1 euer Fachsemester und
euren Studiengang an.

<!--  LocalWords:  
 -->

<!-- Local Variables: -->
<!-- coding: utf-8 -->
<!-- ispell-local-dictionary: "german-new8" -->
<!-- End: -->
