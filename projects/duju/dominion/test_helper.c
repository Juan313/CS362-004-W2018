#include "test_helper.h"
#include <stdbool.h>
#include <stdio.h>

void asserttrue(bool statement){

  if (statement)
    printf("TEST SUCCESSFULLY COMPLETED!\n");
  else 
    printf("TEST FAILED!!!!\n");

}
