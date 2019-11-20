## Navngivning

En uddannelse kalder vi `bachelor`
En vektor af interesser kalder vi `interst[]`

```c
struct bachelor{   
  double interest[];
}
```

## Filstrukturen af databasen

```
Interesse:            .... \t  .... \t  .... \t  .... \t 
Fag:                  mat  \t  dan  \t  .... \t  
           Biologi    0.3  \t       \t       \t
           Datalogi   1.0  \t  0.0  \t       \t        \t beskrivelse \t  region  \t  'z'  \t  'A' (krav)
           Dansk      0.0  \t  1.0
           ...
           ..
           ...

```
Til at beskrive fagenes niveau bruge ASCII code points for bogstaverne 'A', 'B' og 'C'. 
Bogstavet 'Z' .. 
