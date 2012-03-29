/* 
 * File:   Device.h
 * Author: tomko
 *
 * Created on 26 marzec 2012, 23:24
 */

#ifndef DEVICE_H
#define	DEVICE_H

#include <string>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

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
  
  uint8_t getPort() const
  {
    return port;
  }

  void setPort(uint8_t port)
  {
    this->port = port;
  }


  void sendInt(int to_send);
private:
  std::string MAC;
  std::string name;
  uint8_t port;
  struct sockaddr_rc sock_addr;
  
  void createSockAddr();
};

#endif	/* DEVICE_H */

