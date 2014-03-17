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

/**
 * @brief  angoloS
 * @author Andrea Grimaldi <andrea.grimaldi.1@studenti.unipd.it>
 * @version 0.1
 *
 */

#include "angoloS.h"
#include <cmath>
#include <iostream>
angoloS::angoloS(int Xgradi, int Xprimi, double Xsecondi)
{
  secondi=Xsecondi+60*( Xprimi + 60 * Xgradi );
  
}
angoloS::~angoloS()
{

}


//resittuisce il valore in radianti

double angoloS::GetRad()
{
return (secondi/648000)*M_PI;
}




//Operazioni algebriche generali 
angoloS& angoloS::operator*( double sx)
{
  double secondiTmp=secondi*sx;
  return *( new  angoloS(0,0,secondiTmp) );
  
}

angoloS& angoloS::operator*( int sx)
{
  double secondiTmp=secondi*sx;
  return *( new angoloS(0,0,secondiTmp) );
  
}


angoloS& angoloS::operator/( int sx )
{
 ;
  return *( new angoloS(0,0, secondi/sx) );
  
}

angoloS& angoloS::operator/( double sx )
{
  int secondiTmp=secondi/sx;
  return *( new angoloS(0,0,secondiTmp) );
  
}


angoloS& angoloS::operator+(angoloS& sx)
{
 int secondiTmp=secondi+sx.secondi;
  return *(new angoloS(0,0,secondiTmp));
}


angoloS& angoloS::operator-(angoloS& sx)
{
 int secondiTmp=secondi-sx.secondi;
  return *(new angoloS(0,0,secondiTmp));
}


std::ostream& operator<<(std::ostream& os, angoloS& other)
{
  
  int secondiTmp = other.secondi;
    os << secondiTmp/3600 << "°" << ( secondiTmp/60 )%60 << '\''<< secondiTmp%60 + (other.secondi - secondiTmp ) << "\'\'";
    return os;
}

std::ostream& operator<<(std::ostream& os, angoloS* other)
{
  
  int secondiTmp = other->secondi;
    os << secondiTmp/3600 << "°" << ( secondiTmp/60 )%60 << '\''<< secondiTmp%60 + (other->secondi - secondiTmp ) << "\'\'";
    return os;
}





angoloS::angoloS(const angoloS& other)
{

}


angoloS* ReadP(std::istream& is)
{
  if ( !( is.good() ) ) return 0;
  
  int gradi=0;
  int primi=0;
  
  if (! ( is >> gradi ) ) return 0;
  is >> primi;
  
  return new angoloS(gradi,primi);
  
}



