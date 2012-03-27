/* 
 * File:   BluezBluetooth.h
 * Author: tomko
 *
 * Created on 26 marzec 2012, 23:21
 */

#ifndef BLUEZBLUETOOTH_H
#define	BLUEZBLUETOOTH_H

#include <list>
#include "Device.h"


class BluezBluetooth
{
public:
  /**
   * Klasa wyjątku w przypadku błędu.
   */
  class NoDeviceException
  {
  public:
    NoDeviceException(std::string e) : error(e)
    {
      
    }
    
    std::string GetError() const
    {
      return error;
    }

  private:
    std::string error;
  };
  
  BluezBluetooth();
  BluezBluetooth(const BluezBluetooth& orig);
  virtual ~BluezBluetooth();
  
  /**
   * Funkcja zwracająca listę wykrytych urządzeń.
   * @return Lista wykrytych urządzeń.
   */
  std::list<Device> scanDevices() throw(NoDeviceException);
  
  
private:
  std::list<Device> devices;
  void scan() throw(NoDeviceException);
};

#endif	/* BLUEZBLUETOOTH_H */

