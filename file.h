#ifndef FILE_H 
#define FILE_H

#include <stdio.h>
#include "stack.h"

void loadFromFile(struct Table *head);
void saveToFile(struct Table *head);

#endif
