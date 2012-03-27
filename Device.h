/* 
 * File:   Device.h
 * Author: tomko
 *
 * Created on 26 marzec 2012, 23:24
 */

#ifndef DEVICE_H
#define	DEVICE_H

#include <string>

/**
 * Klasa Device odpowiada urządzeniu bluetooth.
 */
class Device
{
public:
  Device();
  Device(std::string M, std::string n) : MAC(M), name(n)
  {
    
  }
  virtual ~Device();
  
  std::string getMAC() const
  {
    return MAC;
  }

  void setMAC(std::string MAC)
  {
    this->MAC = MAC;
  }

  std::string getName() const
  {
    return name;
  }

  void setName(std::string name)
  {
    this->name = name;
  }

private:
  std::string MAC;
  std::string name;
};

#endif	/* DEVICE_H */

