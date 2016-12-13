\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{ti2}[2009/10/27 Ingo Sieverdingbeck]
\LoadClass[a4paper]{scrartcl}
\usepackage{ulem}
\usepackage{titletoc}
\usepackage{stmaryrd}
\usepackage[colorinlistoftodos,textwidth=2cm]{todonotes}
\usepackage[ngerman]{babel}
\usepackage{fancyhdr}
\usepackage{graphicx}
\usepackage[utf8]{inputenc}
\usepackage{listings}
\usepackage{url}
% -----------------------------------------------------------------------
% Required packages

% Format commands

% inline quellcode (mit \ilcode{...}) für Methoden
\newcommand*{\M}[1]{%
    \colorbox{red!10}%
    {%
        \lstinline!#1!%
    }
}

\newcommand{\codeBash}[3]{\lstinputlisting[language=Bash,rangeprefix=\#\#--,rangesuffix=--\#\#,linerange=#1-#1_end, caption=#2.bash]{#3}}
\newcommand{\codeSh}[3]{\lstinputlisting[language=Sh,rangeprefix=\#\#--,rangesuffix=--\#\#,linerange=#1-#1_end, caption=#2.sh]{#3}}
\newcommand{\codeCpp}[3]{\lstinputlisting[language=C++,rangeprefix=//--,rangesuffix=--//,linerange=#1-#1_end, caption=#2.c]{#3}}
\newcommand{\codeC}[3]{\lstinputlisting[language=C,rangeprefix=//--,rangesuffix=--//,linerange=#1-#1_end, caption=#2.cpp]{#3}}

\usepackage{color}

\RequirePackage[ngerman]{babel}
\RequirePackage{amssymb}
\RequirePackage{epsfig}
\RequirePackage{graphicx}
\RequirePackage{moreverb}
\RequirePackage{parskip}

% -----------------------------------------------------------------------

\renewcommand\thesection{\textbf{Aufgabe \arabic{section}}}
\renewcommand\thesubsection{\textbf{Aufgabe \arabic{section}.\alph{subsection}}}
\renewcommand\thesubsubsection{\textbf{Aufgabe \arabic{section}.\alph{subsection}.\arabic{subsubsection}}}


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
% Macro für das Abgabeblatt
\newcommand{\Abgabeblatt}[8]
          {\Arbblatt{#1}{#2}{#3}{#4}{#5}{#6}{#7}{#8}{\"Ubungsblatt}}

\newcommand{\grenzop}[3]{\mathop{#1}\limits^{#2}_{#3}}

\newcommand{\langrechtspfeil}[2]{\grenzop{\longrightarrow}{#1}{#2}}
\newcommand{\bob}[0]{\hspace*{\fill}$\Box$}

% -----------------------------------------------------------------------
% Format commands
\newcommand{\C}[1]{\texttt{\mbox{#1}}} % classes
\newcommand{\m}[1]{\emph{\mbox{#1}}} % methods
\newcommand{\p}[1]{\emph{#1}}
\newcommand{\key}[1]{\textbf{#1}} % keywords
\newcommand{\sg}[1]{\m{#1}} % setter/getter
\newcommand{\setter}{\sg{setter()}-}
\newcommand{\getter}{\sg{getter()}-}
\newcommand{\skipInput}[1]{}
\newcommand{\str}[1]{\texttt{"}#1\texttt{"}}
% inline quellcode (mit \ilcode{...}) für Methoden

%%% Schönerer Code
\definecolor{myBGcolor}{rgb}{0.94,0.94,1}
\definecolor{javadocblue}{rgb}{0.25,0.35,0.80} % javadoc
\definecolor{keywordcolor}{rgb}{0,0,0.8}
\definecolor{stringcolor}{rgb}{0,0.5,0}
\definecolor{inlinecolor}{rgb}{1,0.85,0.85}

\lstset{
    includerangemarker=false,columns=spaceflexible,
    numbers=left,
    numberstyle=\tiny,
    numbersep=5pt,
    literate=%
        {Ö}{{\"O}}1
        {Ä}{{\"A}}1
        {Ü}{{\"U}}1
        {ß}{{\ss}}1
        {ü}{{\"u}}1
        {ä}{{\"a}}1
        {ö}{{\"o}}1
        {~}{{\textasciitilde}}1
        {°}{{$^\circ$}}1,
    basicstyle=\fontfamily{pcr}\selectfont\footnotesize,
    showspaces=false,
    showtabs=true,
    showstringspaces=false,
    keywordstyle=\bfseries,
    tabsize=4,
    frameround=ffff,
    frame=single,
    extendedchars=true,
    commentstyle=\itshape,
    postbreak=\space,
    breakindent=5pt,
    breaklines=true,
    backgroundcolor=\color{myBGcolor},
}

\newcommand{\Arbblatt}[9]
{
\begin{tabular}[t]{lr}
  \begin{tabular}[t]{l}
    Technische Informatik 2\hspace{20ex} WS 2016/17\\ Tutor: {#3}\\ \hspace{70ex} \\
    {\Huge\textsf{{#9} {#1}}} \hspace{10ex} \begin{tabular}{c|c|c|c|c|c}1&2&3&4&5&$\sum$\\\hline &&&&&\end{tabular}\\[1.5ex]
    {\Large L\"osungsvorschlag} \\[1ex]
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

%%% Local Variables: 
%%% mode: latex
%%% TeX-master: t
%%% End: 

