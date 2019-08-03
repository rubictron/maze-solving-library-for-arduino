#ifndef MAZE_H
#define MAZE_H

#include "enum.h"
#include <LinkedList.h>
#include <EEPROM.h>
#include <Arduino.h>
#include <stdlib.h>


class maze
{
  private:
    void addM(desition d);
    void addMLHR(desition d);
    void addMRHR(desition d);
    LinkedList<desition> list;
    LinkedList<desition> eplist;
    ruletype rule = LEFT;
    int minAddress = 0;
    desition takeDesitionLHR(junction j);
    desition takeDesitionRHR(junction j);
    LinkedList<desition> changelist(LinkedList<desition> l);


  public:
    maze();
    maze(ruletype r);
    desition takeDesition(junction j);
    LinkedList<desition> readForword();
    LinkedList<desition> readBackword();
    void writeData();
    LinkedList<desition> readForwordEEPROM();
    LinkedList<desition> readBackwordEEPROM();
    void printDesition(desition d);
};

#endif
