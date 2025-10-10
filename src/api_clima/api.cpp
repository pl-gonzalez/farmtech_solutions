#include <Arduino.h>
#include <string.h>
#include <stdlib.h>
#include "api.h"

void formata_dados(const char *input, Dados *out) {
  char temp[50];
  strcpy(temp, input);

  char *token = strtok(temp, ";");
  if (token != NULL) strcpy(out->date, token);

  token = strtok(NULL, ";");
  if (token != NULL) out->tempMin = atof(token);

  token = strtok(NULL, ";");
  if (token != NULL) out->tempMax = atof(token);

  token = strtok(NULL, ";");
  if (token != NULL) out->probChuva = atoi(token);
}