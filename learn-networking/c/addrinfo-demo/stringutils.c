#include "stringutils.h"
#include <stdio.h>
#include <stdlib.h>
//
// Created by avilay on 11/14/24.
//
void append_str_to_str(char** buf, char* text) {
  char* tmp = *buf;
  asprintf(buf, "%s%s", *buf, text);
  free(tmp);
}

void append_int_to_str(char** buf, const int i) {
  char* tmp = *buf;
  asprintf(buf, "%s%d", *buf, i);
  free(tmp);
}

void append_uint_to_str(char** buf, const unsigned int u) {
  char *tmp = *buf;
  asprintf(buf, "%s%u", *buf, u);
  free(tmp);
}
