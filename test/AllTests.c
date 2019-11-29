#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <profile.h>
#include <education.h>
#include <subjects.h>
#include <vector.h> 
#include "CuTest.h"

CuSuite* CuGetSuite();
CuSuite* CuStringGetSuite();
CuSuite* test4000();

void RunAllTests(void){
    CuString *output = CuStringNew();
    CuSuite* suite = CuSuiteNew();
    
    /*
    CuSuiteAddSuite(suite, CuGetSuite());
    CuSuiteAddSuite(suite, CuStringGetSuite());
    */

    CuSuiteAddSuite(suite, test4000());

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer); 
}

int main(void)
{
    RunAllTests();
    return 0;
}

