#include "maze.h"

 maze::maze(){
    this->list.add(START);
  }

maze::maze(ruletype r = LEFT)
{

  this->rule = r;
  this->list.add(START);
}

void maze::addM(desition d)
{

  if (this->rule == LEFT)
  {

    addMLHR(d);
  }
  else if (this->rule == RIGHT)
  {

    addMRHR(d);
  }
}

void maze::addMLHR(desition d) {

  desition saved = d;

  if (this->list.get(this->list.size() - 1) == BW)
  {

    if (this->list.get(this->list.size() - 2) == LT)
    {
      if (d == LT)
      {

        saved = FW; // LT BW LT = FW
      }
      else if (d == FW)
      {

        saved = RT; // LT BW FW = RT
      }
    }

    else if (this->list.get(this->list.size() - 2) == FW)
    {
      if (d == FW)
      {

        saved = BW; // FW BW FW = BW
      }
      else if (d == LT)
      {

        saved = RT; // FW BW LT = RT
      }
    }

    else if (this->list.get(this->list.size() - 2) == RT)
    {

      if (d == LT)
      {

        saved = BW; // RT BW LT =BW
      }
    }

    this->list.pop();
    this->list.pop();
  }

  this->list.add(saved);
}

void maze::addMRHR(desition d) {

  desition saved = d;
  if (this->list.get(this->list.size() - 1) == BW)
  {

    if (this->list.get(this->list.size() - 2) == RT)
    {
      if (d == RT)
      {

        saved = FW; // RT BW RT = FW
      }
      else if (d == FW)
      {

        saved = LT; // RT BW FW = LT
      }
    }

    else if (this->list.get(this->list.size() - 2) == FW)
    {
      if (d == FW)
      {

        saved = BW; // FW BW FW = BW
      }
      else if (d == RT)
      {

        saved = LT; // FW BW RT = LT
      }
    }

    else if (this->list.get(this->list.size() - 2) == LT)
    {

      if (d == RT)
      {

        saved = BW; // LT BW RT =BW
      }
    }

    this->list.pop();
    this->list.pop();
  }

  this->list.add(saved);
}

desition maze::takeDesition(junction j)
{

  if (this->rule == LEFT)
  {
    return takeDesitionLHR(j);
  }
  else if (this->rule == RIGHT)
  {
    return takeDesitionRHR(j);
  }
}

desition maze::takeDesitionLHR(junction j)
{

  switch (j)
  {
    case LS:
      addM(LT);
      return LT;
      break;
    case SR:
      addM(FW);
      return FW;
      break;
    case LR:
      addM(LT);
      return LT;
      break;
    case LSR:
      addM(LT);
      return LT;
      break;
    case E:
      addM(BW);
      return BW;
      break;
    case STOP:
      addM(END);
      return END;
      break;
  }
}

desition maze::takeDesitionRHR(junction j)
{

  switch (j)
  {
    case LS:
      addM(FW);
      return FW;
      break;
    case SR:
      addM(RT);
      return RT;
      break;
    case LR:
      addM(RT);
      return RT;
      break;
    case LSR:
      addM(RT);
      return RT;
      break;
    case E:
      addM(BW);
      return BW;
      break;
    case STOP:
      addM(END);
      return END;
      break;
  }
}

LinkedList<desition> maze::readForword()
{
  writeData();
  return this->list;
}

LinkedList<desition> maze::readBackword()
{

  return changelist(readForword());

}

LinkedList<desition> maze::changelist(LinkedList<desition> l) {

  LinkedList<desition> tempList;
  
  for (int i = l.size()-1; i >-1 ; i--)
  {
    desition d = l.get(i);
    switch (d)
    {
      case LT:
        d = RT;
        break;
      case RT:
        d = LT;
        break;
      case START:
        d = END;
        break;
      case END:
        d = START;
        break;
    }
    
    tempList.add(d);
  }

  return tempList;
}

void maze::writeData() {

  for (int i = minAddress ; i < minAddress + 50 ; i++) {
    EEPROM.write(i, 0);
  }


  int desitionInt;
  for (int i = 0; i < this->list.size(); i++) {
    switch (list.get(i)) {

      case LT:
        desitionInt = 4;
        break;
      case RT:
        desitionInt = 6;
        break;
      case FW:
        desitionInt = 8;
        break;
      case BW:
        desitionInt = 2;
        break;
      case END:
        desitionInt = 9;
        break;
      case START:
        desitionInt = 1;
        break;
    }
    EEPROM.write(i + minAddress, desitionInt);

  }


}


LinkedList<desition> maze::readForwordEEPROM() {

  for(int i=0;i<eplist.size();i++){
    eplist.pop();
    }

  

  for (int i = minAddress; i < EEPROM.length(); i++) {
    desition des;
    switch (EEPROM.read(i)) {
      case 4:
        des = LT;
        break;
      case 6:
        des = RT;
        break;
      case 8:
        des = FW;
        break;
      case 2:
        des = BW;
        break;
      case 9:
        des = END;
        eplist.add(des);
        return eplist;
        break;
      case 1:
        des = START;
        break;
      default:
        break;
    }
    eplist.add(des);
 

  }


}


LinkedList<desition> maze::readBackwordEEPROM(){
  
  return changelist(eplist);
  
  }


void maze::printDesition(desition d)
{
  switch (d)
  {
    case LT:
      Serial.print("LT");
      break;
    case RT:
      Serial.print("RT");
      break;
    case FW:
      Serial.print ("FW");
      break;
    case BW:
      Serial.print ("BW");
      break;
    case END:
      Serial.print ("END");
      break;
    case START:
      Serial.print ("START");
      break;
  }
}






