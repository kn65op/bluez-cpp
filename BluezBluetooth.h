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
  BluezBluetooth();
  BluezBluetooth(const BluezBluetooth& orig);
  virtual ~BluezBluetooth();
  
  /**
   * Funkcja skanująca urządzenia.
   */
  std::list<Device> scanDevices();
private:

};

#endif	/* BLUEZBLUETOOTH_H */

