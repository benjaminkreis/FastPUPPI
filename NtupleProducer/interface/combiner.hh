#ifndef FASTPUPPI_NTUPLERPRODUCER_COMBINER_HH
#define FASTPUPPI_NTUPLERPRODUCER_COMBINER_HH
#include "TGraph.h"
#include <algorithm>  
#include <iostream>

class combiner { 
public:
  struct Particle { 
    Particle(double iEt,double iEta,double iPhi,double iM,int iId,double iSigma,double iDZ,double iCaloEta=0,double iCaloPhi=0, double iCharge = 0, double iQuality = -999) 
    {
      Et=iEt; Eta=iEta; Phi=iPhi; M=iM; id=iId; sigma=iSigma; dZ=iDZ; caloEta=iCaloEta; caloPhi=iCaloPhi; charge = iCharge; quality = iQuality;
    }
    double Et;
    double Eta;
    double Phi;
    double M;
    double dZ;
    double sigma;
    double caloEta;
    double caloPhi;
    double charge;
    double quality;
    int id;
  };

  combiner(const std::string iPionFile,const std::string iElectronFile,const std::string iTrackFile);
  void addCalo(double iCalo,double iEcal,double iCaloEta,double iCaloPhi,double iEcalEta,double iEcalPhi);
  void loadFile(TGraph** &iF1, std::string iFile);
  double correct(double iHcal,double iEcal,int iEta);
  void addTrack(double iPt,double iEta,double iPhi,double idZ,double iCaloEta,double iCaloPhi, double iCharge);
  void addMuon(double iPt, double iEta, double iPhi, double charge, double quality);
  void link();
  void doVertexing();  
  void merge(Particle &iTkParticle,Particle &iParticle1,std::vector<Particle> &iCollection);
  inline void    clear() {fTkParticles.clear(); fParticles.clear(); fMuParticles.clear(); fTkParticlesWVertexing.clear(); }
  inline std::vector<Particle> candidates()   { return fParticles;}
  inline std::vector<Particle> tkcandidates() { return fTkParticles;}
  inline std::vector<Particle> mucandidates() { return fMuParticles;}
private:
  void insert(Particle &iPartcle,std::vector<Particle> &iParticles);
  inline double  getTrkRes (double iPt,double iEta,double iPhi) { return fTrackRes   [translateIEta(iEta)]->Eval(iPt);}
  inline double  getPionRes(double iPt,double iEta,double iPhi) { return fElectronRes[translateIEta(iEta)]->Eval(iPt);}
  inline double  getEleRes (double iPt,double iEta,double iPhi) { return fPionRes    [translateIEta(iEta)]->Eval(iPt);}
  inline int     translateIEta(double iEta) { return int(10*std::max(std::min(iEta,3.0),-3.0))+30;}  
  double deltaR(Particle &iParticle1,Particle &iParticle2);
  double deltaRraw(Particle &iParticle1,Particle &iParticle2);
  TGraph **fTrackRes;
  TGraph **fElectronRes;
  TGraph **fPionRes;
  int   fNEta;
  double fDRMatch;
  std::vector<Particle> fTkParticles;
  std::vector<Particle> fTkParticlesWVertexing;  
  std::vector<Particle> fMuParticles;
  std::vector<Particle> fParticles;
};
#endif