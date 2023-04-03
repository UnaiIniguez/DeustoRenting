#ifndef MENU_H_
#define MENU_H_

#include "user.h"
#include "stdout.h"
#include "stdin.h"
#include <stdio.h>
#include <stdlib.h>
#include "vehicle.h"
#include "administrador.h"
#include "service.h"

void showMenu(User* user);
unsigned short getAction();

#endif
