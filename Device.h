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
  Device(const Device& orig);
  virtual ~Device();
  
  std::string GetMAC() const
  {
    return MAC;
  }

  void SetMAC(std::string MAC)
  {
    this->MAC = MAC;
  }

  std::string GetName() const
  {
    return name;
  }

  void SetName(std::string name)
  {
    this->name = name;
  }

private:
  std::string MAC;
  std::string name;
};

#endif	/* DEVICE_H */

