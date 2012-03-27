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

TEST(ScanDevices, ScanDevices)
{
  BluezBluetooth b;
  std::list<Device> devs = b.scanDevices();
  std::list<Device>::iterator it, end;
  for (it = devs.begin(), end = devs.end(); it != end; it++)
  {
    std::cout << it->getMAC() << " " << it->getName() << "\n";
  }
  devs = b.scanDevices();
  for (it = devs.begin(), end = devs.end(); it != end; it++)
  {
    std::cout << it->getMAC() << " " << it->getName() << "\n";
  }
}

int main(int argc, char **argv)
{

  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();

}

