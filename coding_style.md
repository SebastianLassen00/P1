# Coding Style

## Generalt
* indrykning: 4 gange whitespace

### Functions
´´´c 
void func(param1, param2){
    function();
}´´´

### Structures 

´´´c
int i;
for(i = 0; i < 9; i++){
    function();
}

if(this && that){
    function();
} else if(just this){
    function7();
} else{
    function1();
}

while(this is true){
    function();
}

do{
    function();
} while(that);

switch(expression){
    case 1:
        function1();    
        break;
    case 2:
        function2();    
        break;
    default:
        return shit;
}´´´

### Operators  
´´´c
i = 3 + 4 * (7 / 5 + 5 % 2);
i += 2;
i -= 2;´´´

### Structures
´´´c
char array[SYMBOLIC_CONSTANT] = "Some text";
char *array = "Some other text";
char array[] = "Some text again";´´´

variablenames are written with underscores: 
´´´c
int this_integer = 2;
char some_character = 'a';´´´

### Calls  
Functionnames are written in camelcase:
´´´c
callFunction(a, 2, 3, a, bdw, w);
parseSomething(a, b);´´´
