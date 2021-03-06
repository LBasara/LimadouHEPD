#include "LEvRec0File.hh"
#include "LCaloCalibrationManager.hh"          	
#include <iostream>



using namespace std;

int main(int argc,char *argv[]){
  if(argc!=3) {
    std::cerr << "Error! Usage:    ./CalibrateCalo <calRunFile> <calOutFile>" << std::endl;
    std::cerr << "Aborted." << std::endl;
    return -999;
  }
  
  
  LCaloCalibrationManager::GetInstance().LoadRun(argv[1]);
  LCaloCalibration *cal =   LCaloCalibrationManager::GetInstance().CalibrateHG();
  cal->Write(argv[2]);
  
  
  // Test read-write and sum
  LCaloCalibration *calr=LCaloCalibration::Read(argv[2]);
  LCaloCalibration cal2 = (*calr) + (*calr);
  cal2.Write("ciccio.cal");
  
  return 0;
}
