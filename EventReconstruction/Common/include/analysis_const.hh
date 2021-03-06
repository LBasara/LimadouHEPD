#ifndef LIMADOU_ANALYSIS_CONST
#define LIMADOU_ANALYSIS_CONST 1

const int NCALIBEVENTS = 1000;
const double SIGMA_CUT_CN=5.; //at first 3
const double SIGMA_CUT_SIGMA=3.;
const double SIGMA_SEL=1.5;
const double GE_THRESHOLD=6.5; //good events threshold
const int BIN_SIGMA=500;
const double MAX_SIGMA=100.;
const double SIGMA_STEP=MAX_SIGMA/(double)BIN_SIGMA;

const double MIN_NCHANSPERBIN_4CN=5.;
const double MIN_SIGMA_CHANNEL_OFF=6.;
const double MAX_SIGMA_CHANNEL_OFF=30.;
const double MAX_SIGMA_NOISE_LEVEL=4.;

const double NSIGMABOOL=3.;
const double GAUSSTHRESHOLD=0.0027;
const double GAUSINDEX_CUT=3.;


//LTrackerSignal
const double HOTSIGMA=25.;
const double COLDSIGMA=1.;
const double NGILOW=-999.;
const double NGIHIGH=3.;
const double HOLDCORRCONST=0.018;//0.018;


//eta manage

const int ETASTEP=400;
const double ETAMIN=-0.2;
const double ETAMAX=1.2;
const double ETARANGE=ETAMAX-ETAMIN;

#endif
