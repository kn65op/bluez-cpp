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
  my_socket = 0;
}

Device::Device(const Device& c)
{
  //kopiowanie tylko danych urządzenia
  MAC = c.MAC;
  name = c.name;
  port = c.port;
  my_socket = 0;
}

Device::~Device()
{
  stopConnection();
}

void Device::sendInt(int to_send) throw (Device::ConnectionError)
{
  //createSockAddrSend();
  //int socket = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM); //alokacja socket
  //int status = connect(my_socket, (struct sockaddr *) &sock_addr_send, sizeof (sock_addr_send)); //nawiązanie połączenie 
  /*if (status < 0)
  {
    std::cout << "Status: " << status << "\n";
    close(my_socket);
    throw Device::ConnectionError(name, MAC, "connecting");
  }*/
  int status = write(my_socket, &to_send, sizeof (int));
  if (status < 0)
  {
    //  std::cout << "Status: " << status << "\n";
    throw Device::ConnectionError(name, MAC, "sending");
  }
}

void Device::sendChar(char to_send) throw (Device::ConnectionError)
{
  int status = write(my_socket, &to_send, sizeof (char));
  //close(socket);
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

char Device::receiveUChar() throw (Device::ConnectionError)
{
  u_char buff;
  int read_len = read(my_socket, &buff, sizeof (buff)); //czytanie
  if (read_len < 0) //bład
  {
    throw (Device::ConnectionError(name, MAC, "Error while reading from socket"));
  }
  else if (!read_len) //jeśli nie odebrano danych
  {
    return receiveUChar(); //próbujemy jeszcze raz odebrać
  }
  return buff;
}

//TODO: sprawdzić wydajnosć

uint32_t Device::receiveUInt4() throw (Device::ConnectionError)
{
  unsigned int buff; //bufor
  //pobranie pierwszego bajtu
  buff = receiveUChar(); //domyślna konwersja char do uint
  for (int i=0; i<3; i++) //trzykrotnie przesunięcie bitowe i pobranie po kolejnym
  {
    buff << 8; //zrobienie miejsca na kolejne bajty
    buff += receiveUChar();  //pobranie kolejnego bajtu
  }
  return buff;

  //stare
  /*int read_len = read(my_socket, &buff, sizeof (buff)); //czytanie
  if (read_len < 0)
  {
    throw (Device::ConnectionError(name, MAC, ""));
  }
  while (read_len != sizeof (buff))
  {

  }
  return buff;**/

  //bardzo stare
  /*
  struct sockaddr remote_addr;
  createSockAddrRec();
  //int socket = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM); //alokacja socket
  //bind(socket, (struct sockaddr *) &sock_addr_rec, sizeof (sock_addr_rec));
  //listen(socket, 1); // nasłuchiwanie (chyba dozwolone jedno połączenie)
  socklen_t remote_addr_len = sizeof (remote_addr);
  std::cout << "Czytanie1\n";
  int client = accept(my_socket, (struct sockaddr*) &remote_addr, &remote_addr_len); //akceptacja połączenia

  int buff; //bufor
  std::cout << "Czytanie2\n";
  int read_len = read(client, &buff, sizeof (buff)); //czytanie
  std::cout << "Przeczytane\n";
  close(client);
  close(my_socket);
  if (read_len < 0)
  {
    throw (Device::ConnectionError(name, MAC, "no_data_received"));
  }
  return buff;*/
}

void Device::stopConnection()
{
  if (my_socket)
  {
    close(my_socket);
  }
  my_socket = 0;
}

void Device::startConnection()
{
  createSockAddrSend();
  this->my_socket = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM); //alokacja socket
  int status = connect(my_socket, (struct sockaddr *) &sock_addr_send, sizeof (sock_addr_send)); //nawiązanie połączenie 
  if (status < 0)
  {
    //std::cout << "Status: " << status << "\n";
    close(my_socket);
    throw Device::ConnectionError(name, MAC, "Error while connecting");
  }
}