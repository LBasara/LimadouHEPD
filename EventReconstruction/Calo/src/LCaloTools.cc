#include "LCaloTools.hh"

LTriggerSignal GetTriggerSignal(const LEvRec0 lev0, const LCalibration cal) {
  LTriggerSignal result;
  const int nunits = result.GetNUnits();
  const int npmts = result.GetNPMTs();
  const int OFFSET = 0; // PMT index offset for this kind of calo  

  const double *pedestal = cal.GetCaloHGCalibration()->GetPedestal();
  const double *sigma = cal.GetCaloHGCalibration()->GetSigma();

  for(int iu=0; iu<nunits; ++iu) {
    for(int ipmt=0; ipmt<npmts; ++ipmt) {
     int index = OFFSET+iu*npmts+32*ipmt; // even ipmt is east, odd ipmt is west
      result.cont_hg[iu][ipmt] = static_cast<double>(lev0.pmt_high[index])-pedestal[index];
      result.sn_hg[iu][ipmt] = result.cont_hg[iu][ipmt]/sigma[index];
      result.cont_lg[iu][ipmt] = static_cast<double>(lev0.pmt_low[index])-pedestal[index];
      result.sn_lg[iu][ipmt] = result.cont_lg[iu][ipmt]/sigma[index];
    }
  }

  return result;
}

LScintillatorSignal GetScintillatorSignal(const LEvRec0 lev0, const LCalibration cal) {
  LScintillatorSignal result;
  const int nunits = result.GetNUnits();
  const int npmts = result.GetNPMTs();
  const int OFFSET = NTRIGSCINT; // PMT index offset for this kind of calo  

  

  const double *pedestal = cal.GetCaloHGCalibration()->GetPedestal();
  const double *sigma = cal.GetCaloHGCalibration()->GetSigma();

  for(int iu=0; iu<nunits; ++iu) {
    for(int ipmt=0; ipmt<npmts; ++ipmt) {
      //int index = OFFSET+iu*npmts+32*ipmt;  // (even,even)=SouthEast (even,odd)=NorthWest (odd,even)=SouthWest (odd,odd)=NorthEast
     
      int index = OFFSET + iu + (ipmt*32);
      result.cont_hg[iu][ipmt] = static_cast<double>(lev0.pmt_high[index])-pedestal[index];
      result.sn_hg[iu][ipmt] = result.cont_hg[iu][ipmt]/sigma[index];
      result.cont_lg[iu][ipmt] = static_cast<double>(lev0.pmt_low[index])-pedestal[index];
      result.sn_lg[iu][ipmt] = result.cont_lg[iu][ipmt]/sigma[index];
    }
  }
  
  return result;
}

LVetoSignal GetVetoSignal(const LEvRec0 lev0, const LCalibration cal) {
  LVetoSignal result;
  const int nunits = result.GetNUnits();
  const int npmts = result.GetNPMTs();
  const int OFFSET = NTRIGSCINT+NSCINTPLANES; // PMT index offset for this kind of calo  

  const double *pedestal = cal.GetCaloHGCalibration()->GetPedestal();
  const double *sigma = cal.GetCaloHGCalibration()->GetSigma();

  for(int iu=0; iu<nunits; ++iu) { // iu: north, east, south, west, bottom
    for(int ipmt=0; ipmt<npmts; ++ipmt) { // pmt even: up, odd: down   ---   for bottom(iu=4) even:NorthEast, odd:SouthWest
      int index = OFFSET+iu*npmts+32*ipmt; 
      result.cont_hg[iu][ipmt] = static_cast<double>(lev0.pmt_high[index])-pedestal[index];
      result.sn_hg[iu][ipmt] = result.cont_hg[iu][ipmt]/sigma[index];
      result.cont_lg[iu][ipmt] = static_cast<double>(lev0.pmt_low[index])-pedestal[index];
      result.sn_lg[iu][ipmt] = result.cont_lg[iu][ipmt]/sigma[index];
    }
  }
  
  return result;
}

LLysoSignal GetLysoSignal(const LEvRec0 lev0, const LCalibration cal) {
  LLysoSignal result;
  const int nunits = result.GetNUnits();
  const int npmts = result.GetNPMTs();
  const int OFFSET = NTRIGSCINT+NSCINTPLANES+NVETOSCINT; // PMT index offset for this kind of calo  

  const double *pedestal = cal.GetCaloHGCalibration()->GetPedestal();
  const double *sigma = cal.GetCaloHGCalibration()->GetSigma();

  for(int iu=0; iu<nunits; ++iu) {
    for(int ipmt=0; ipmt<npmts; ++ipmt) {
      int index = (iu<5 ? OFFSET+iu*npmts+32*ipmt : OFFSET+(iu-5)*npmts+32); //9-7-1-8-5   and 3-2-6-4
      result.cont_hg[iu][ipmt] = static_cast<double>(lev0.pmt_high[index])-pedestal[index];
      result.sn_hg[iu][ipmt] = result.cont_hg[iu][ipmt]/sigma[index];
      result.cont_lg[iu][ipmt] = static_cast<double>(lev0.pmt_low[index])-pedestal[index];
      result.sn_lg[iu][ipmt] = result.cont_lg[iu][ipmt]/sigma[index];
    }
  }
  
  return result;
}

