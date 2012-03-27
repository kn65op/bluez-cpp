/* 
 * File:   equalMAC.h
 * Author: tomko
 *
 * Created on 27 marzec 2012, 11:49
 */

#ifndef EQUALMAC_H
#define	EQUALMAC_H

#include <string>

#include "Device.h"

class EqalMAC
{
public:

  EqalMAC(std::string mac) : MAC(mac)
  {
  };
  bool operator()(Device & d)
  {
    return d.getMAC() == MAC;
  }
private:
  std::string MAC;
};

#endif	/* EQUALMAC_H */

