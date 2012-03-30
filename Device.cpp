/* 
 * File:   Device.cpp
 * Author: tomko
 * 
 * Created on 26 marzec 2012, 23:24
 */

#include "Device.h"

#include <iostream>

#include <unistd.h>
#include <sys/socket.h>

Device::Device()
{
}

Device::~Device()
{
}


void Device::sendInt(int to_send) throw(Device::ConnectionError)
{
  createSockAddr();
  int s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM); //alokacja socket
  int status = connect(s, (struct sockaddr *) &sock_addr, sizeof(sock_addr)); //nawiązanie połączenie 
  if (status < 0)
  {
    std::cout << "Status: " << status << "\n";
    throw Device::ConnectionError(name, MAC, "connecting");
  }
  status = write(s, &to_send, sizeof(int));
  if (status < 0)
  {
    std::cout << "Status: " << status << "\n";
    throw Device::ConnectionError(name, MAC, "sending");
  }
}

void Device::createSockAddr()
{
  createSockAddr(port);
}

void Device::createSockAddr(uint8_t port)
{
  sock_addr.rc_family = AF_BLUETOOTH; // ustawienie na bluetooth
  sock_addr.rc_channel = port; //TODO: ustalić port
  str2ba(MAC.c_str(), &sock_addr.rc_bdaddr); //ustawienie adresu MAC urządzenia docelowego
}