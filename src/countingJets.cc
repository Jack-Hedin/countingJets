#include "countingJets.h"

#include <fun4all/Fun4AllReturnCodes.h>

#include <phool/PHCompositeNode.h>

//added
#include <fun4all/PHTFileServer.h>
#include <jetbase/JetContainer.h>
#include <jetbase/Jet.h>
#include <phool/getClass.h>

//____________________________________________________________________________..
countingJets::countingJets(const std::string &name):
 SubsysReco("Counting_Jets")
 , m_outfile(name)
{ 
  std::cout << "countingJets::countingJets(const std::string &name) Calling ctor" << std::endl;
}

//____________________________________________________________________________..
countingJets::~countingJets()
{
  std::cout << "countingJets::~countingJets() Calling dtor" << std::endl;
}

//____________________________________________________________________________..
int countingJets::Init([[maybe_unused]] PHCompositeNode *topNode)
{
  std::cout << "countingJets::Init(PHCompositeNode *topNode) Initializing" << std::endl;

  //PHTFileServer::get().open(m_outfile, "RECREATE");
  

  
  
  return Fun4AllReturnCodes::EVENT_OK;
}

//____________________________________________________________________________..
int countingJets::process_event([[maybe_unused]] PHCompositeNode *topNode)
{   
  std::cout << "=======New Event=======" << std::endl;
 
  JetContainer *JetsC04 = findNode::getClass<JetContainer>(topNode, "AntiKt_Tower_r04_Sub1");
  if (!JetsC04)
  {
    std::cout
      << "MyJetAnalysis::process_event - Error can not find DST Reco JetContainer node" << std::endl;
    exit(-1);
  }
  int total_jets = 0;

  for (Jet *jet : *JetsC04 ) {
    
    if(!jet)
        {
          std::cout << "WARNING!!! Jet not found" << std::endl;
          continue;
        }

    total_jets++;
    std::cout << "Jet # " << total_jets << std::endl;
    std::cout << "T Momentum " << jet->get_pt() << std::endl;
    std::cout << "Eta " << jet->get_eta() << std::endl;
    std::cout << "Phi " << jet->get_phi() << std::endl;
    std::cout << "---" << std::endl;
  }

  
  return Fun4AllReturnCodes::EVENT_OK;
}

//____________________________________________________________________________..
int countingJets::ResetEvent([[maybe_unused]] PHCompositeNode *topNode)
{
  std::cout << "countingJets::ResetEvent(PHCompositeNode *topNode) Resetting internal structures, prepare for next event" << std::endl;
  return Fun4AllReturnCodes::EVENT_OK;
}

//____________________________________________________________________________..
int countingJets::End([[maybe_unused]] PHCompositeNode *topNode)
{
  std::cout << "countingJets::End(PHCompositeNode *topNode) This is the End..." << std::endl;
  return Fun4AllReturnCodes::EVENT_OK;
}

