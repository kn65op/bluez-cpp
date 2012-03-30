/* 
 * File:   Device.cpp
 * Author: tomko
 * 
 * Created on 26 marzec 2012, 23:24
 */

#include "Device.h"

#include <iostream>

//Temporary
#undef BDADDR_ALL
#undef BDADDR_ANY
#undef BDADDR_LOCAL

#define BDADDR_ANY_INITIALIZER   {{0, 0, 0, 0, 0, 0}}
#define BDADDR_ALL_INITIALIZER  {{0xff, 0xff, 0xff, 0xff, 0xff, 0xff}}
#define BDADDR_LOCAL_INITIALIZER {{0, 0, 0, 0xff, 0xff, 0xff}}

#define BDADDR_ANY   (&(bdaddr_t) BDADDR_ANY_INITIALIZER)
#define BDADDR_ALL   (&(bdaddr_t) BDADDR_ALL_INITIALIZER)
#define BDADDR_LOCAL   (&(bdaddr_t) BDADDR_LOCAL_INITIALIZER)
//Temporary

#include <unistd.h>
#include <sys/socket.h>

Device::Device()
{
}

Device::~Device()
{
}

void Device::sendInt(int to_send) throw (Device::ConnectionError)
{
  createSockAddrSend();
  int s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM); //alokacja socket
  int status = connect(s, (struct sockaddr *) &sock_addr_send, sizeof (sock_addr_send)); //nawiązanie połączenie 
  if (status < 0)
  {
    std::cout << "Status: " << status << "\n";
    close(s);
    throw Device::ConnectionError(name, MAC, "connecting");
  }
  status = write(s, &to_send, sizeof (int));
  close(s);
  if (status < 0)
  {
    std::cout << "Status: " << status << "\n";
    throw Device::ConnectionError(name, MAC, "sending");
  }
}

void Device::createSockAddrSend()
{
  createSockAddrSend(port);
}

void Device::createSockAddrSend(uint8_t port)
{
  sock_addr_send.rc_family = AF_BLUETOOTH; // ustawienie na bluetooth
  sock_addr_send.rc_channel = port; //TODO: ustalić port
  str2ba(MAC.c_str(), &sock_addr_send.rc_bdaddr); //ustawienie adresu MAC urządzenia docelowego
}

void Device::createSockAddrRec()
{
  sock_addr_rec.rc_family = AF_BLUETOOTH; // ustawienie na bluetooth
  bdaddr_t bt_any = BDADDR_ANY_INITIALIZER;
  sock_addr_rec.rc_bdaddr = bt_any; //dowolne źródło
  sock_addr_rec.rc_channel = (uint8_t) 1; // port nasłuchiwania
}

int Device::receiveInt() throw (Device::ConnectionError)
{
  struct sockaddr remote_addr;
  createSockAddrRec();
  int s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM); //alokacja socket
  bind(s, (struct sockaddr *) &sock_addr_rec, sizeof (sock_addr_rec));
  listen(s, 1); // nasłuchiwanie (chyba dozwolone jedno połączenie)
  socklen_t remote_addr_len = sizeof (remote_addr);
  int client = accept(s, (struct sockaddr*) &remote_addr, &remote_addr_len); //akceptacja połączenia

  int buff; //bufor
  int read_len = read(client, &buff, sizeof (buff)); //czytanie
  close(client);
  close(s);
  if (read_len < 0)
  {
    throw (Device::ConnectionError(name, MAC, "no_data_received"));
  }
  return buff;
}