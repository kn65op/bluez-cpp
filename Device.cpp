/* 
 * File:   Device.cpp
 * Author: tomko
 * 
 * Created on 26 marzec 2012, 23:24
 */

#include "Device.h"

#include <unistd.h>
#include <sys/socket.h>

Device::Device()
{
}

Device::~Device()
{
}


void Device::sendInt(int to_send)
{
  
}

void Device::createSockAddr()
{
  sock_addr.rc_family = AF_BLUETOOTH; // ustawienie na bluetooth
  sock_addr.rc_channel = port; //TODO: ustalić port
  str2ba(MAC.c_str(), &sock_addr.rc_bdaddr); //ustawienie adresu MAC urządzenia docelowego
}