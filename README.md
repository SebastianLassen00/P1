# P1
Automatiser dit studievalg A302

Programmet P1 omhandler et program, som kan automatiserer studievalg i det danske uddannelses system. Programmet er programmeret i ansi C og er multiplatform. Programmet er succesfuldt blevet kompileret med følgende options *-Wall*, *-ansi* og *-pedantic* på Windows, MacOS og Ubuntu Linux.  


## Projektets struktur  

Projektet er inddelt i tre hovedemapper: src, include og bin. Derudover findes der to hjælpemapper kaldet docs og test. 

Hovedemapperne holder på alle essentielle filer til programmet. Dette inkludere alle binærfiler, samt alle .c, .h filer og datafiler. 

**Hovedmappernes indhold**
* src
  * indeholder alle .c filer. Dette inkludere main.c.
* include
  * indeholder alle .h filer.
* bin
  * indeholder programmets .exe/.out fil, samt en data mappe, som indeholder database.txt og testprofiler. 

## Kompilering  

Til kompilering af programmet er der lavet en *makefile*. Denne makefile kaldes med terminalskommandoen **make**, hvorefter programmet kan findes i mappen *bin*.  

Som tidligere nævnt, bruges kompiler options *-Wall*, *-ansi* og *-pedantic* til kompileringen.
