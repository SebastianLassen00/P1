# Main Program
## Basic functions
### Input af datasæt
Funktionen skal finde en liste af alle forskellige interesser, der kommer fra datasæt (separat fil).
Funktionen skal finde en liste over alle uddannelser, fra filen
Funktionen skal gemme vægtningerne for alle uddannelser og interesser
Gemme via outputparametre

### Brugerinput
Læser data fra terminalen, som brugeren indtaster
Holder dialogen med brugeren i gang
Får interesser fra "Input af datasæt", som den stiller spørgsmål om

### Output brugervektor
Funktionen gemmer brugerens interrese-vektor til en fil seperat fra data-filen

### Vektorregning
Vektorer skal gemmes som arrays af doubles funktioner returnere gemmen outputvektorer
Skal kunne udføre følgende udregninger: 
* Add
	* Addition af to vektorer
	* Skal også kunne bruges til substraktion
* Scale
	* Skal kunne skalere en vektor
* Length
	* Skal kunne beregne længden af en vektor ved brug af Pythagoras
* Normalize
	* Skal kunne omdanne en vektor til den tilsvarende enhedsvektor (længde = 1)
* Dot Product
	* Skal kunne bestemme prikprodukt hvis vektorne er enhedsvektorer
	* Udregnes som: x_1x_2 + y_1y_2 + z_1z_2

### Beregning af output
Funktionen skal kunne sammenligne brugerens vektor med uddannelsernes vektorerne og bestemme den, der passer bedst
Bruger prikprodukt og en adjustment vektor (som er den, der justerer brugerens vektor efter tidligere evalueringer)

### Formatering af output
Funktionen skal skrive navnet samt information fra datasættet.

### Input evaluering
Funktion skal beregne adjustment vektoren ud fra brugerens evaluering af den viste uddannelse.

0.1 < k < 0.5
adjust_vector = adjust_vector + normalize(study_vector - user_vector) * k * eval

### Command handling
Funktionen skal finde ud af hvilken command brugeren har indtastet samt om der hører argumenter med, hvilket også gemmes. Følgende commands skal håndteres:
	* Find uddannelse
	* Save uddannelse
	* Recommend uddannelse
	* Load saved
	* Evaluate uddannelse

### Interactions
Funktionen skal fungere som kerne-funktionen der kalder på de andre funktioner og holder på de variabler som programmet gemmer undervejs. 







