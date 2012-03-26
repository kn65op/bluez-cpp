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
  b.scanDevices();
}

int main(int argc, char **argv)
{

  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();

}

