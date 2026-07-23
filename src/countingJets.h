// Tell emacs that this is a C++ source
//  -*- C++ -*-.
#ifndef COUNTINGJETS_H
#define COUNTINGJETS_H

#include <fun4all/SubsysReco.h>

#include <string>

class PHCompositeNode;

class countingJets : public SubsysReco
{
 public:

  countingJets(const std::string &name = "countingJets");

  ~countingJets() override;

  /** Called during initialization.
      Typically this is where you can book histograms, and e.g.
      register them to Fun4AllServer (so they can be output to file
      using Fun4AllServer::dumpHistos() method).
   */
  int Init(PHCompositeNode *topNode) override;

  /** Called for each event.
      This is where you do the real work.
   */
  int process_event(PHCompositeNode *topNode) override;

  /// Clean up internals after each event.
  int ResetEvent(PHCompositeNode *topNode) override;

  /// Called at the end of all processing.
  int End(PHCompositeNode *topNode) override;

 private:
 std::string m_outfile = "outputfile.root";
};

#endif // COUNTINGJETS_H
