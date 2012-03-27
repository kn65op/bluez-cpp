/* 
 * File:   equalMAC.h
 * Author: tomko
 *
 * Created on 27 marzec 2012, 11:49
 */

#ifndef EQUALNAME_H
#define	EQUALNAME_H

#include <string>

#include "Device.h"

class EqalName
{
public:

  EqalName(std::string n) : name(n)
  {
  };
  bool operator()(Device & d)
  {
    return d.getName() == name;
  }
private:
  std::string name;
};

#endif	/* EQUALNAME_H */

