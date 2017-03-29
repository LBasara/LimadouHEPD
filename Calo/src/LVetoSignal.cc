#include "LVetoSignal.hh"

#include <iostream>

LVetoSignal::LVetoSignal() {
    nunits=VETOPLANES;
    npmts=2;
    CreateContainers();
}

LVetoSignal::~LVetoSignal() {

}

void LVetoSignal::Dump() {
  std::cout << "############# Veto signal dumping." << std::endl;
  DumpAll();
  return;
}