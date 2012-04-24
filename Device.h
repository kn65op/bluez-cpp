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
#include <ostream>
#include <istream>

/**
 * Klasa Device odpowiada urządzeniu bluetooth. Pozwala na wysyłanie i odbieranie informacji z urządzeniem zdalnym.
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

  /**
   * Kontruktor kopiujący. Kopiuje tylko dane urządzenia, połączenie trzeba tworzyć od nowa.
   * @param c Urządzenie do skopiowania.
   */
  Device(const Device & c);

  Device(std::string M, std::string n) : MAC(M), name(n)
  {
    my_socket = 0;
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

  /**
   * Funkcja ustawiająca port, z którym chcemy się połączyć.
   * @param to_send Numer portu.
   */
  void setPort(uint8_t port)
  {
    this->port = port;
  }

  /**
   * Funkcja wysyłająca int na dane urządzenie.
   * @param to_send int do wysłania.
   */
  void sendInt(int to_send) throw (Device::ConnectionError);
  /**
   * Funkcja wysyłająca jeden znak.
   * @param to_send Znak, który chcemy wysłać
   */
  virtual void sendChar(char to_send) throw (Device::ConnectionError);
  /**
   * Funkcja odbierająca 4 bajty z urządzenia zdalnego traktowane jako 4-bajtowa liczba bez znaku z kolejnością bajtów "little endian"
   * @return Liczba bez znaku.
   */
  virtual u_int32_t receiveUInt4() throw (Device::ConnectionError);
  /**
   * Funkcja odbierająca jeden bajt z urządzenia zdalnego traktowany jako char.
   * @return Odebrany bajt jako char.
   */
  char receiveUChar() throw (Device::ConnectionError);
  /**
   * Funkcja łącząca z urządzeniem.
   */
  virtual void startConnection();
  /**
   * Funkcja zamykająca połączenie, a co z tym idzie i połączenie.
   */
  virtual void stopConnection();
private:
  std::string MAC;
  std::string name;
  uint8_t port;
  struct sockaddr_rc sock_addr_send;
  struct sockaddr_rc sock_addr_rec;
  int my_socket;

  void createSockAddrSend();
  void createSockAddrSend(uint8_t port);
  void createSockAddrRec();
  void clearSockRec();
};

/**
 * Funkcja zapisująca Device (nazwę, MAC i port) do std::ostream.
 * @param o std::ostream do którego jest zapis.
 * @param d Device, który jest zapisywany.
 * @return std::ostrema do którego jest zapis.
 */
std::ostream& operator<<(std::ostream& o, Device &d);

/**
 * Funkcja wczytująca Device (nazwę, MAC i port) z std::istream.
 * @param i std::istream z którego jest odczyt.
 * @param d Device, który jest wczytywany.
 * @return std::istream z którego jest zapis.
 */
std::istream& operator>>(std::istream& i, Device &d);

#endif	/* DEVICE_H */
/*
wyjście
        
        153
0
0
0
0
0
0
0
0
0
0
0
156
0
0
0
0
0
0
0
0
0
0
0
155
0
0
0
0
0
0
0
0
0
0
0
152
0
0
0
 */