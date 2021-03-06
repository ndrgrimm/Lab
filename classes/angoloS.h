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

#ifndef ANGOLOS_H
#define ANGOLOS_H

#include <iostream>
class angoloS
{
  
friend
  std::ostream& operator<<( std::ostream& os, angoloS& other);
friend
  std::ostream& operator<<( std::ostream& os, angoloS* other);
  
public:
  angoloS(int Xgradi, int Xprimi = 0, double Xsecondi = 0.);
  virtual ~angoloS();
  

  //ritorna il converte l'angolo i radianti
  double GetRad();

  
  //Operatori generici
  angoloS& operator*( double sx);
  angoloS& operator/( double sx);
  angoloS& operator*( int sx);
  angoloS& operator/( int sx );
  angoloS& operator+( angoloS& sx);
  angoloS& operator-( angoloS& sx);
  angoloS& operator=(const angoloS& other){ this->secondi=other.secondi; return *this;};


private:
  

  double secondi;
  
  //copie private
  angoloS(const angoloS& other);
};

  // Altre funzioni da sistemare da qualche parte
  angoloS* ReadP(std::istream& is);


#endif // ANGOLOS_H
