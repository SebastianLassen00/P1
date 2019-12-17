# P1

Automatiser dit studievalg af gruppe A302, Datalogi 1.semester,  17-12-2019

Programmet P1 omhandler et program, som kan automatisere studievalg i det danske uddannelsessystem. Programmet er programmeret i ANSI C og er multiplatform. Programmet er succesfuldt blevet kompileret med følgende options `-Wall`, `-ansi` og `-pedantic` på Windows, MacOS og Ubuntu Linux.  

## Projektets struktur  

Projektet er inddelt i tre hovedemapper: **src**, **include** og **bin**. Derudover findes der to hjælpemapper kaldet **docs** og **test**. 

Hovedemapperne holder på alle essentielle filer til programmet. Dette inkluderer alle binærfiler, samt alle .c filer, .h filer og datafiler.  

### Hovedmappernes indhold

* [src](./src/)
  * indeholder alle .c filer. Dette inkluderer main.c.
* [include](./include/)
  * indeholder alle .h filer.
* [bin](./bin/)
  * indeholder programmets .exe/.out fil, samt en [data](./bin/data/) mappe, som indeholder [database.txt](./bin/data/database.txt) og testprofiler.  

I folderen `src` findes `main.c`, hvilket er programmets entry-point. Størstedelen af .c filerne i `src` er reflekteret i `include` i form af en .h fil. Dette kan ses ved [`parser.c`](src/parser.c) og [`parser.h`](include/parser.h). I den tilhørende .h fil, findes alle prototyper til funktioner, som skal være offentligt tilgængelige for resten af programmet.

I mappen [bin](./bin/) kan programmet findes, når det er blevet kompileret. Derudover kan den rå databasefil også findes i [/bin/data](./bin/data/) Det anbefales, at databasefilen åbnes med et program, som kan åbne tabulatorsepareret filer (for eksempel Microsoft Excel).

### Hjælpemappernes indhold

* [test](./test/)
  * indeholder test kode, som f.eks. [CuTest](test/AllTest.c).
* [docs](./docs/)
  * indeholder dokumentation af kode. Denne dokumentation er autogenereret vha. doxygen og en tilhørende doxygen fil.

test indeholder, som nævnt tidligere, testværktøjer. Mappen inkluderer en [fil](./test/AllTest.c), hvor CuTest bliver udført. 

docs indeholder en html mappe, hvor [index.html](./docs/html/index.html) kan åbnes i en valgfri browser. På denne hjemmeside-lignende html fil, kan programmet udforskes mere interaktivt vha. diverse menu'er. Dette er en mere overskuelig måde at udforske kildekoden. Denne html side er skabt vha. Doxygen. 

## Kompilering  

Til kompilering af programmet er der lavet en [makefile](./makefile). Denne makefile kaldes med terminalskommandoen `make`, hvorefter programmet kan findes i mappen [bin](./bin/) med navnet `prog`.  

Som tidligere nævnt, bruges kompiler options *-Wall*, *-ansi* og *-pedantic* til kompileringen. Derudover bruges `lm`, så `math.h` bliver linked korrekt. Det fulde kompiler udtryk kan ses [her](./makefile) i makefilen. 

Nedenfor ses en step-by-step guide til kompilering og kørsel af programmet:
```shell
make
cd bin
./prog.exe
```

## Kør programmet
For at køre programmet skal der højreklikkes på programmet i folderen `bin` og trykkes åben. Derefter åbner et terminalvindue, hvor programmet kan integreres med. Hvis programmet køres gennem en terminal *skal* current directory være i `bin`.
