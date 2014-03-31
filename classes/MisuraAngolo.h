/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2014  <copyright holder> <email>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef MISURAANGOLO_H
#define MISURAANGOLO_H
#include <angoloS.h>
#include<iostream>

class MisuraAngolo
{

public:
  MisuraAngolo( angoloS * InNonio1, angoloS* InNonio2){
    nonio1=InNonio1;
    nonio2=InNonio2;
  }
  
  
  ~MisuraAngolo() { delete nonio1; delete nonio2; }
  
  
  
  angoloS& operator-( MisuraAngolo& sx){
    
    return ( *this->nonio1 - *sx.nonio1  + *this->nonio2 - *sx.nonio2 ) /2;
    
  }
  
  
private:
  
  angoloS*  nonio1;
  angoloS*  nonio2;
  
  
};

MisuraAngolo* ReadMisuraP(std::istream& is){
  angoloS * angoloTmp1=ReadP(is);
  if (!angoloTmp1) return 0;
  angoloS * angoloTmp2=ReadP(is);
  if (!angoloTmp2) return 0;
  
 return new MisuraAngolo( angoloTmp1, angoloTmp2 ); 
}

#endif // MISURAANGOLO_H
