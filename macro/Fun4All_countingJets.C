#include <fun4all/Fun4AllDstInputManager.h>
#include <fun4all/Fun4AllInputManager.h>
#include <fun4all/Fun4AllServer.h>
#include <fun4all/SubsysReco.h>

#include <fun4all/Fun4AllUtils.h>
#include <fun4all/Fun4AllOutputManager.h>
#include <fun4all/Fun4AllRunNodeInputManager.h>
#include <fun4all/Fun4AllDstInputManager.h>
#include <fun4all/Fun4AllInputManager.h>
#include <fun4all/Fun4AllServer.h>
#include <fun4all/SubsysReco.h>
#include <fun4all/Fun4AllDstOutputManager.h>
#include <fun4all/Fun4AllOutputManager.h>

#include <mbd/MbdReco.h>
#include <globalvertex/GlobalVertex.h> //set global vertex
#include <globalvertex/GlobalVertexReco.h>
#include <phool/recoConsts.h> //to get reco constants
#include <Calo_Calib.C> //for calibrations
#include <HIJetReco.C>
#include <ffamodules/CDBInterface.h>
#include <fun4all/Fun4AllNoSyncDstInputManager.h> //to hopefully stop it from breaking?

#include <string>
#include <fstream>
#include <iostream>

#include <TSystem.h>

// My two modules
#include <countingjets/countingJets.h>
R__LOAD_LIBRARY(libcountingJets.so)

R__LOAD_LIBRARY(libfun4all.so)
R__LOAD_LIBRARY(libcalo_reco.so)
R__LOAD_LIBRARY(libg4dst.so)


void Fun4All_countingJets() {

  int verbosity = 0;

  Fun4AllServer *se = Fun4AllServer::instance();
  se->Verbosity(verbosity);

  const string caloFile = "dst_real.list";
  //const string globalFile = "dst_global.list"; 
  //const string truthjetFile = "dst_truth_jet.list";
  //const string tracksFile = "dst_tracks.list";
  //const string truthFile = "dst_truth.list";


  // Register input managers
  Fun4AllInputManager *in1 = new Fun4AllDstInputManager("in1");
  in1->AddListFile(caloFile);
  se->registerInputManager(in1);

/*
  Fun4AllInputManager *in2 = new Fun4AllDstInputManager("in2");
  in2->AddListFile(globalFile);
  se->registerInputManager(in2);

  Fun4AllInputManager *in3 = new Fun4AllDstInputManager("DSTtruthjet");
  in3->AddListFile(truthjetFile);
  se->registerInputManager(in3);

  Fun4AllInputManager *in4 = new Fun4AllDstInputManager("DSTtracks");
  in4->AddListFile(tracksFile);
  se->registerInputManager(in4);

  Fun4AllInputManager *in5 = new Fun4AllDstInputManager("DSTtruth");
  in5->AddListFile(truthFile);
  se->registerInputManager(in5);
*/
  




  //get runnumber of first file
  ifstream file(caloFile);
  string first_file;
  getline(file, first_file);

  pair<int, int> runseg = Fun4AllUtils::GetRunSegment(first_file);
  int runnumber = runseg.first;
  cout << "run number = " << runnumber << endl;



  GlobalVertex::VTXTYPE vertex_type = GlobalVertex::MBD;
  
  recoConsts *rc = recoConsts::instance();
  Enable::CDB = true;
  rc->set_StringFlag("CDB_GLOBALTAG", "newcdbtag");
  rc->set_uint64Flag("TIMESTAMP", runnumber);
  CDBInterface::instance()->Verbosity(0);

  std::cout << "=======Starting Calibration=======" << std::endl;  
  Process_Calo_Calib(); 
  

  std::cout << "=======Starting Vertex Reco=======" << std::endl;
  //vertex block 
  MbdReco *mbdreco = new MbdReco();
  se->registerSubsystem(mbdreco);
  GlobalVertexReco *gvertex = new GlobalVertexReco();
  se->registerSubsystem(gvertex);

  std::cout << "=======Starting HI Jet Reco=======" << std::endl; 
  HIJetReco();

  std::cout << "=======Registering Ana File=======" << std::endl;
  countingJets *myJets = new countingJets("countingJets.root");
  se->registerSubsystem(myJets);

  std::cout << "=======Starting Run=======" << std::endl;
  se->run(1);
  std::cout << "=======End Run=======" << std::endl;
  se->End();
  //gSystem->Exit(0);
}
