# Coding Style

## General
* Indentation: 4 times whitespace per indent
* Language: English (both code and comments)
* Brackets: None if only one argument

### Functions
```c
void func(param1, param2){
    function();
}
```

### Structures 

```c
int i;
for(i = 0; i < 9; i++)
    function();
```

```c
int i;
for(i = 0; i < 9; i++){
    function();
    function1();
}
```

```c
if(this && that)
    function();
else if(just this)
    function7();
else
    function1();
```

```c
if(this && that){
    function();
    function1();
} else if(just this){
    function7();
    function();
} else{
    function1();
    function2();
}
```


```c
while(this is true)
    function();
```

```c
while(this is true){
    function();
    function1();
}
```

```c
do
    function();
while(that);
```

```c
do{
    function();
    function1();
} while(that);
```

```c
switch(expression){
    case 1:
        function1();    
        break;
    case 2:
        function2();    
        break;
    default:
        return shit;
}
```

### Operators  
```c
i = 3 + 4 * (7 / 5 + 5 % 2);
i += 2;
i -= 2;
```

### Structures
```c
char array[SYMBOLIC_CONSTANT] = "Some text";
char *array = "Some other text";
char array[] = "Some text again";
```

variablenames are written with underscores: 
```c
int this_integer = 2;
char some_character = 'a';
```

### Calls  
Functionnames are written in camelcase:
```c
callFunction(a, 2, 3, a, bdw, w);
parseSomething(a, b);
```
