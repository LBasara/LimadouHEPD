#include "LTrackerCalibration.hh"
#include <iostream>
#include <algorithm>
#include <math.h>

void LTrackerCalibration::Add(const LTrackerCalibrationSlot *lcal) {
  calarray.push_back(*lcal);
  ++nSlots;
  std::cout << __LTRACKERCALIBRATION__ << "Current slot number " << nSlots << std::endl;;
  return;
}

LTrackerCalibration::LTrackerCalibration() {
  Reset();
}


void LTrackerCalibration::Reset(void) {
  RunId=-99999;
  nSlots=0;
  InitialTargetRun=-99999;
  FinalTargetRun=-99999;
  calarray.resize(0);
  return;
}

LTrackerCalibration::LTrackerCalibration(const int RunIdINP,  const int InitialTargetRunINP, const int FinalTargetRunINP) {
  RunId=RunIdINP;
  nSlots=0;
  InitialTargetRun=InitialTargetRunINP;
  FinalTargetRun=FinalTargetRunINP;
}

void LTrackerCalibration::Write(std::ofstream *output) const {
  *output << RunId << std::endl;
  *output << InitialTargetRun << " " << FinalTargetRun << std::endl;
  *output << nSlots << std::endl;

  for(auto cslotit : calarray) cslotit.Write(output);
  
  *output << std::endl;
    
  return;
}


void LTrackerCalibration::Write(const char *fileOut) const {
  std::ofstream output(fileOut, std::ofstream::out); 
  Write(&output);
  output.close();
  return;
}


LTrackerCalibration* LTrackerCalibration::Read(std::ifstream *input) {
  
  int RunIdST, InitialTargetRunST, FinalTargetRunST, nSlotsST;

  *input >> RunIdST;
  *input >> InitialTargetRunST >> FinalTargetRunST;

  LTrackerCalibration *result = new LTrackerCalibration(RunIdST, InitialTargetRunST, FinalTargetRunST);

  *input >> nSlotsST;
  for(int is=0; is<nSlotsST; ++is) result->Add(LTrackerCalibrationSlot::Read(input));

  return result;
}
 
LTrackerCalibration* LTrackerCalibration::Read(const char *fileIn) {
  
  std::ifstream input(fileIn, std::ifstream::in); 
  LTrackerCalibration *result = Read(&input);
  input.close();

  return result;
}
 


LTrackerCalibration& LTrackerCalibration::operator=(const LTrackerCalibration& other) {
  calarray.resize(0);
  
  // slots
  for(int is=0; is<other.GetNSlots(); ++is) {
    calarray.push_back(other.GetTrackerCalibrationSlot(is));
  }
  // In/out run info
  RunId = other.GetRunId();
  InitialTargetRun = other.GetInitialTargetRun();
  FinalTargetRun = other.GetFinalTargetRun();

  return *this;
}

LTrackerCalibration& LTrackerCalibration::operator+=(const LTrackerCalibration& rhs) // compound assignment (does not need to be a member,
{                           // but often is, to modify the private members)
  calarray.resize(0);
  
  // slots
  // Firstly, sum up all slots of this
  LTrackerCalibrationSlot tmpSlot;
  int cntSlot=0;
  for(int is=0; is<nSlots; ++is) {
    tmpSlot+=(GetTrackerCalibrationSlot(is));
    ++cntSlot;
  }
  tmpSlot/=(static_cast<double>(cntSlot));
  // Secondly, sum up all the rest
  LTrackerCalibrationSlot tmpSlot2;
  int cntSlot2=0;
  for(int is=0; is<rhs.GetNSlots(); ++is) {
    tmpSlot2+=(rhs.GetTrackerCalibrationSlot(is));
    ++cntSlot2;
  }
  tmpSlot2/=(static_cast<double>(cntSlot2));

  LTrackerCalibrationSlot *toAdd = new LTrackerCalibrationSlot();
  *toAdd = tmpSlot+tmpSlot2;
  Add(toAdd);
  nSlots=1;

  // In/out run info
  RunId = rhs.GetRunId();
  InitialTargetRun = rhs.GetInitialTargetRun();
  FinalTargetRun = rhs.GetFinalTargetRun();

  
  return *this; // return the result by reference
}
 
LTrackerCalibration operator+(LTrackerCalibration lhs,        // passing lhs by value helps optimize chained a+b+c
		   const LTrackerCalibration& rhs) // otherwise, both parameters may be const references
{
  lhs += rhs; // reuse compound assignment
  return lhs; // return the result by value (uses move constructor)
}


LTrackerCalibration& LTrackerCalibration::operator/=(const double& rhs) 
{
  for(auto pslot : calarray) pslot/=rhs;
  return *this; // return the result by reference
}
 
