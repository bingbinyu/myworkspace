\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{ti2ueb}[]
\LoadClass[a4paper]{scrartcl}

% -----------------------------------------------------------------------
% Required packages

\RequirePackage[ngerman]{babel}
\RequirePackage{amssymb}
\RequirePackage{epsfig}
\RequirePackage{graphicx}
\RequirePackage{moreverb}
\RequirePackage{parskip}
\RequirePackage{listings}
%\RequirePackage{courier}

\DeclareOption{uebung}{
  \newcommand{\theTitle}[1]{\"Ubungsblatt #1}
}
\DeclareOption{weitereaufgaben}{
  \renewcommand{\theTitle}[1]{\"Ubungsblatt #1: Weitere Aufgaben}
}

\ExecuteOptions{uebung}

\ProcessOptions\relax

\lstset{
         basicstyle=\footnotesize\ttfamily, % Standardschrift
         %numbers=left,               % Ort der Zeilennummern
         numberstyle=\tiny,          % Stil der Zeilennummern
         %stepnumber=2,               % Abstand zwischen den Zeilennummern
         numbersep=5pt,              % Abstand der Nummern zum Text
         tabsize=2,                  % Groesse von Tabs
         extendedchars=true,         %
         breaklines=true,            % Zeilen werden Umgebrochen
%         keywordstyle=\color{red},
    		frame=none,         
 %        keywordstyle=[1]\textbf,    % Stil der Keywords
 %        keywordstyle=[2]\textbf,    %
 %        keywordstyle=[3]\textbf,    %
 %        keywordstyle=[4]\textbf,   \sqrt{\sqrt{}} %
%         stringstyle=\color{white}\ttfamily, % Farbe der String
         showspaces=false,           % Leerzeichen anzeigen ?
         showtabs=false,             % Tabs anzeigen ?
         xleftmargin=17pt,
         framexleftmargin=17pt,
         framexrightmargin=5pt,
         framexbottommargin=4pt,
         %backgroundcolor=\color{lightgray},
         showstringspaces=false      % Leerzeichen in Strings anzeigen ?        
 }

\usepackage[utf8]{inputenc}
\usepackage{url}
\usepackage{xspace}

\usepackage[T1]{fontenc}
\usepackage{palatino}

\usepackage{xspace}
\usepackage{enumitem}

% -----------------------------------------------------------------------
% define page layout using typearea

\KOMAoptions{headinclude=true}
\KOMAoptions{footinclude=true}
\areaset{16cm}{27cm}
% -----------------------------------------------------------------------
% define page style
\pagestyle{plain}
\thispagestyle{plain}

% -----------------------------------------------------------------------
% Macro fÃ¼r das Abgabeblatt
\newcommand{\Abgabeblatt}[8]
          {\Arbblatt{#1}{#2}{#3}{#4}{#5}{#6}{#7}{#8}{\"Ubungsblatt}}

\newcommand{\grenzop}[3]{\mathop{#1}\limits^{#2}_{#3}}

\newcommand{\langrechtspfeil}[2]{\grenzop{\longrightarrow}{#1}{#2}}
\newcommand{\bob}[0]{\hspace*{\fill}$\Box$}

% -----------------------------------------------------------------------

\newcommand{\Arbblatt}[9]
{
\begin{tabular}[t]{lr}
  \begin{tabular}[t]{l}
    Technische Informatik 2\hspace{20ex} WS 2016/17\\ Tutor: {#3}\\ \hspace{70ex} \\
    {\Huge\textsf{{#9} {#1}}} \hspace{10ex} \begin{tabular}{c|c|c|c|c|c}1&2&3&4&5&$\sum$\\\hline &&&&&\end{tabular}\\[1.5ex]
    {\Large Abgabe: {#2}} \\[1ex]
  \end{tabular}
  &
  \begin{tabular}[t]{l}
      {#4}\\\\
      {#5}\\
      {#6}\\
      {#7}\\
      {#8}\\
  \end{tabular} \\[2ex]
\end{tabular}\\
\rule{\linewidth}{1pt}
}

\newcommand{\Uebung}[2]
{
  Technische Informatik 2\hfill WS 2016/17
  \rule{\linewidth}{1pt}
  \vspace{0.2em}\\
  {\Huge\textbf{\centering \theTitle{#1}}}
%  {\Huge\textbf{\centering {\"Ubungsblatt} {#1}}}
  \vspace{0.2em}\\
  \rule{\linewidth}{1pt}
  \ifx&#2&{}\else{Abgabe bis spätestens {#2} in Stud.IP}\fi
}

\newcommand{\Arbeitssitzung}[1]
{
  Technische Informatik 2\hfill WS 2016/17
  \rule{\linewidth}{1pt}
  \vspace{0.2em}\\
  {\Huge\textbf{\centering {#1}. Arbeitssitzung}}
  \vspace{0.2em}\\
  \rule{\linewidth}{1pt}
%  Abgabe bis spätestens {#2}
}

\newcounter{Aufgabe}
\newcommand{\Aufg}[2]
{
  \stepcounter{Aufgabe}
  \section*{Aufgabe \theAufgabe{} \ifnum#1=0{}\else{({#1} \ifnum#1=1{Punkt}\else{Punkte}\fi, {#2})}\fi{}}
  \vspace{-1.2em}
  \ifnum\theAufgabe>1\vspace{-3.6em}\rule{\linewidth}{1pt}\vspace{3.6em}
  \fi
}

\newcommand{\EinzelAufgabe}[1]{\Aufg{#1}{einzeln}}
\newcommand{\Aufgabe}[1]{\Aufg{#1}{Gruppe}}

\newcommand{\Abgabe}[1]
{
  \section*{Abgabe}
  
  Bis 24:00 Uhr am {#1} digital in Stud.IP und -- wenn nicht anders mit
  Eurem Tutor vereinbart -- ausgedruckt in unser Postfach in der
  MZH-Ebene~6 oder im nächsten Tutorium. Es gelten die vereinbarten
  Scheinbedingungen (siehe Stud.IP). Bitte beachtet unsere
  ergänzenden Hinweise ebenda.

  Packt die abgaberelevanten Dateien in eine Archivdatei. Die
  Dateinamen innerhalb des Archivs wie auch der Archivname selbst
  müssen den in den Scheinbedingungen festgelegten Namenskonventionen
  folgen. Abgaben, die diese Konventionen nicht einhalten, gelten als
  nicht erfolgt.

  Eure Ansätze und der gewählte Lösungsweg müssen nachvollziehbar
  sein. Achtet insofern auf eine saubere Dokumentation im
  Quelltext. Benennt alle von euch verwendeten Quellen, auch
  Zusammenarbeit mit anderen Gruppen und verwendete Unterlagen aus
  früheren Jahrgängen.

  Für Programmieraufgaben ist die Korrektheit der Lösung bzw. deren
  Grenzen grundsätzlich nachzuweisen. Dies geschieht neben der
  Dokumentation des Programmcodes durch geeignete Tests, deren Auswahl
  und Eignung begründet werden muss.
}

%Weitere Aufgaben Item
\newcommand{\waitem}[2]{\item {#1}}

%%% Local Variables: 
%%% mode: latex
%%% TeX-master: t
%%% End: 

