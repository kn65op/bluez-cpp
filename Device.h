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

  class ConnectionError
  {
  public:

    ConnectionError(std::string n, std::string m, std::string a) : name(n), MAC(m), action(a)
    {
    };
    std::string GetMAC() const
    {
      return MAC;
    }

    std::string GetName() const
    {
      return name;
    }

    std::string GetAction() const
    {
      return action;
    }


  private:
    std::string MAC;
    std::string name;
    std::string action;
  };
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

  /**
   * Funkcja wysyłająca int na dane urządzenie.
   * @param to_send int do wysłania.
   */
  void sendInt(int to_send) throw(Device::ConnectionError);
  int receiveInt() throw(Device::ConnectionError);
private:
  std::string MAC;
  std::string name;
  uint8_t port;
  struct sockaddr_rc sock_addr_send;
  struct sockaddr_rc sock_addr_rec;

  void createSockAddrSend();
  void createSockAddrSend(uint8_t port);
  void createSockAddrRec();
  void clearSockRec();
};

#endif	/* DEVICE_H */

