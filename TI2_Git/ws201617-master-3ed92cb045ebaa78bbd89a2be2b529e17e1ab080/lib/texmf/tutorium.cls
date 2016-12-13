% -----------------------------------------------------------------------
% pi1.cls
% Based on pi1-muster.tex and defs.tex used before 2003 for
% PI 1 in Bremen.
% Adapted by Thomas R�fer

\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{tutorium}
\LoadClass[11pt,a4paper,twoside]{article}
\usepackage{ngerman}
\usepackage[utf8]{inputenc}
\usepackage{graphicx}
\usepackage{moreverb}
\usepackage{fancyhdr}

% -----------------------------------------------------------------------
% Page layout

% enlarge page
\setlength{\textwidth}{16cm}
\setlength{\topmargin}{-1cm}
\setlength{\evensidemargin}{0cm}
\setlength{\oddsidemargin}{0cm}
\setlength{\textheight}{24cm}

% skip between paragraphs
\setlength{\parskip}{1ex}
% ... and no indentation at start of a new paragraph
\setlength{\parindent}{0ex}

\pagestyle{fancy}
\thispagestyle{empty}

% -----------------------------------------------------------------------
% Main macros

\renewcommand{\maketitle}[1]
          {\@maketitle{#1}}
%\renewcommand\thesection{Aufgabe \arabic{section}}
%\newcommand\skipsection{\stepcounter{section}}

% -----------------------------------------------------------------------
% Misc macros

%\newcommand{\grenzop}[3]{\mathop{#1}\limits^{#2}_{#3}}
%\newcommand{\langrechtspfeil}[2]{\grenzop{\longrightarrow}{#1}{#2}}
%\newcommand{\bob}[0]{\hspace*{\fill}$\Box$}

% -----------------------------------------------------------------------

\renewcommand{\@maketitle}[7]
{
    \begin{tabular*}{20cm}[t]{lr}
      \begin{tabular*}{10cm}[t]{l}
        {\Huge\sf Tutoriumsvorbereitung}\\[1.5ex]
        \vspace{5mm}{\Large\sf {#1}}
      \end{tabular*}
      &
      \begin{tabular}[t]{rlrl}
          {#2}&{}&{#3}&{}\\
          {#4}&{}&{#5}&{}\\
          {#6}&{}&{#7}&{}\\
      \end{tabular} \\[2ex]
    \end{tabular*}\\
    \rule{\linewidth}{1pt}

% -----------------------------------------------------------------------
% Create headings (Thanks to Elmar Loos)

    %\fancyhead{} %clear all fields
    %\fancyhead[LO,RE]{PI 1, \thissemester}
    %\fancyhead[RO,LE]{Tutor: {#3}, Gruppe: {#4}, {#5} et. al.}
    %\fancyfoot{} %clear all fields
    %\fancyfoot[RO,LE]{\thepage}
}
\newcommand{\waitem}[2]{\item \textbf{{#1}}\\{#2}}%Weitere Aufgaben Item
\endinput
