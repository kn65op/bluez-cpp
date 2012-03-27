/* 
 * File:   NeuronTest.cpp
 * Author: tomko
 *
 * Created on 2012-03-15, 16:31:46
 */

#include <stdlib.h>
#include <iostream>
#include <gtest/gtest.h>

#include <list>

#include "BluezBluetooth.h"
#include "Device.h"

TEST(ScanDevices, TwiceScanDevices)
{
  BluezBluetooth b;
  b.scanDevices();
  std::list<Device> devs = b.getDevices();
  std::list<Device>::iterator it, end;
  for (it = devs.begin(), end = devs.end(); it != end; it++)
  {
    std::cout << it->getMAC() << " " << it->getName() << "\n";
  }
  b.scanDevices();
  devs = b.getDevices();
  for (it = devs.begin(), end = devs.end(); it != end; it++)
  {
    std::cout << it->getMAC() << " " << it->getName() << "\n";
  }
}

TEST(FindByMAC, Tel)
{
  BluezBluetooth b;
  Device tel;
  b.scanDevices();
  ASSERT_THROW(tel = b.findByMAC("1"), BluezBluetooth::NotFound);
  ASSERT_NO_THROW(tel = b.findByMAC("")); //wpisz swój
  ASSERT_EQ(tel.getName(), ""); //wpisz swoj
  
}

TEST(FindByName, Tel)
{
  BluezBluetooth b;
  Device tel;
  b.scanDevices();
  ASSERT_THROW(tel = b.findByName("a1"), BluezBluetooth::NotFound);
  ASSERT_NO_THROW(tel = b.findByName("")); //wpisz swoj
  ASSERT_EQ(tel.getMAC(), ""); //wpisz swoj
  
}

int main(int argc, char **argv)
{

  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();

}

