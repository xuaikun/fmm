#ifndef MM_STMATCH_ALGORITHM_HPP
#define MM_STMATCH_ALGORITHM_HPP

#include "network/network.hpp"
#include "network/network_graph.hpp"
#include "mm/stmatch/stmatch_config.hpp"
#include "mm/composite_graph.hpp"
#include "mm/transition_graph.hpp"

namespace MM {

class STMATCH {
 public:
  STMATCH(const Network &network, const NetworkGraph &graph) :
      network_(network), graph_(graph) {

  };
  // Procedure of HMM based map matching algorithm.
  MatchResult match_traj(const Trajectory &traj,
                         const STMATCHConfig &config);
 protected:
  void update_tg(TransitionGraph *tg,
                 const CompositeGraph &cg,
                 const Trajectory &traj,
                 const STMATCHConfig &config);

  void update_layer(int level, TGLayer *la_ptr, TGLayer *lb_ptr,
                    const CompositeGraph &cg,
                    double eu_dist,
                    double delta);

  /**
   * Return distances from source to all targets and with an upper bound of
   * delta to stop the search
   * @param  source  source node index
   * @param  targets a vector of N target node indices
   * @param  delta   upperbound of search
   * @return         a vector of N indices
   */
  std::vector<double> shortest_path_upperbound(
      int level,
      const CompositeGraph &cg, NodeIndex source,
      const std::vector<NodeIndex> &targets, double delta);

  C_Path build_cpath(const TGOpath &opath);
 private:
  const Network &network_;
  const NetworkGraph &graph_;
};// STMATCH

} // MM

#endif
