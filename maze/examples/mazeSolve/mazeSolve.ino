#include "maze.h"

junction jun[] = {LS, LR, E, SR, LR, LS, LS, E, LR, E, SR, LR, LR, E, SR, STOP};

maze memory(LEFT);

void setup()
{

  Serial.begin(9600);
}
void loop()
{ desition d;
  junction j;

  /************************************************************************/

  //  get desition list forwording direction from eeprom
  LinkedList<desition> ememo = memory.readForwordEEPROM();

  Serial.println("EEPROM Forword");

  for (int i = 0; i < ememo.size(); i++)
  {
    Serial.print("ed=");
    memory.printDesition(ememo.get(i));
    Serial.println("");
  }


  //  get desition list backwording direction from eeprom
  LinkedList<desition> ememo2 = memory.readBackwordEEPROM();

  Serial.println("EEPROM backword");

  for (int i = 0; i < ememo2.size(); i++)
  {
    Serial.print("ed=");
    memory.printDesition(ememo2.get(i));
    Serial.println("");
  }
  /**************************************************************************************/


  //test for the pre define junction array*********************************************
  int x = 0;

  for (int x = 0; x < (sizeof(jun) / sizeof(jun[0])); x++) {
    d = memory.takeDesition(jun[x]);
  }
  //************************************************************************************
  /**************************************************************************************/

  // get desition list forwording direction
  LinkedList<desition> memo = memory.readForword();

  Serial.println("Forword");

  for (int i = 0; i < memo.size(); i++)
  {
    Serial.print("d=");
    memory.printDesition(memo.get(i));
    Serial.println("");
  }


  // get desition list backwording direction
  Serial.println("Backword");
  // get desition list backword direction
  LinkedList<desition> memo2 = memory.readBackword();

  for (int i = 0; i < memo2.size(); i++)
  {
    Serial.print("db=");
    memory.printDesition(memo2.get(i));
    Serial.println("");
  }


  /********************************************************************************/



  Serial.println("END*********");

  delay(1000000000);
}


