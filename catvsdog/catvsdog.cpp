#include <iostream>
#include <list>
#include <queue>
#include <map>
#include <limits>

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

template<int NODES>
class MaxFlow
{

public:

  void run(std::map<int, int>* flow, int source, int sink)
  {
    flow_ = flow;
    source_ = source;
    sink_ = sink;
    maxFlow_ = 0;

    int amount;
    while ((amount = augment()) > 0)
      maxFlow_ += amount;
  }

  int flow()
  {
    return maxFlow_;
  }

private:

  int augment()
  {
    bool visited[NODES];
    int pred[NODES];
    std::queue<int> Q;
    bool stop;

    memset(visited, false, sizeof(bool)*NODES);
    memset(pred, -1, sizeof(int)*NODES);

    // Find augmenting path.
    visited[source_] = true;
    Q.push(source_);
    stop = false;
    while (!Q.empty() && !stop)
    {
      int u = Q.front();
      Q.pop();

      for (std::map<int, int>::const_iterator iter = flow_[u].begin();
           iter != flow_[u].end(); ++iter) {
        int v = (*iter).first;
        int cap = (*iter).second;
        if (!visited[v] && cap > 0) {
          pred[v] = u;
          visited[v] = true;
          Q.push(v);

          // Found augmenting path.
          if (v == sink_) {
            stop = true;
            break;
          }
        }
      }
    }

    if (pred[sink_] == -1)
      return 0;

    // Find out augmenting path capacity.
    int cap = std::numeric_limits<int>::max();
    for (int u = sink_; pred[u] != -1; u = pred[u])
      cap = std::min(cap, flow_[pred[u]][u]);

    // Update residual flow.
    for (int u = sink_; pred[u] != -1; u = pred[u])
    {
      flow_[pred[u]][u] -= cap;
      flow_[u][pred[u]] += cap;
    }

    return cap;
  }

  std::map<int, int>* flow_;
  int source_;
  int sink_;
  int maxFlow_;
};

struct Vote
{
  int keep;
  int out;

  Vote(int k, int o): keep(k), out(o) {}
};

int main(int argc, char* argv[])
{
  int N;
  std::map<int, int> flow[500+2];
  MaxFlow<500+2> maxFlow;

  std::cin >> N;
  for (int n = 0; n < N; n++)
  {
    int C, D, V;
    std::vector<Vote> dogLovers, catLovers;

    std::cin >>  C >> D >> V;

    for (int v = 0; v < V; v++)
    {
      char P1[5], P2[5];

      scanf("%s %s", P1, P2);
      if (P1[0] == 'C')
        catLovers.push_back(Vote(atoi(P1+1), atoi(P2+1)));
      else
        dogLovers.push_back(Vote(atoi(P1+1), atoi(P2+1)));
    }

#define CATLOVER_NODE(i) (1 + i)
#define DOGLOVER_NODE(i) (1 + (int)catLovers.size() + i)

    for (int i = 0; i < V + 2; i++)
      flow[i].clear();

    // Add edges between source and catlover nodes
    for (int ci = 0; ci < (int)catLovers.size(); ++ci)
      flow[0][CATLOVER_NODE(ci)] = 1;

    // Add edges between doglover nodes and sink
    for (int di = 0; di < (int)dogLovers.size(); ++di) {
      flow[DOGLOVER_NODE(di)][V+1] = 1;
    }

    // Add edges between catlover and doglover nodes where the catlover wants
    // to keep the cat that the doglover wants to throw out or vice verca.
    for (int ci = 0; ci < (int)catLovers.size(); ++ci) {
      for (int di = 0; di < (int)dogLovers.size(); ++di) {
        if (catLovers[ci].keep == dogLovers[di].out ||
            dogLovers[di].keep == catLovers[ci].out)
          flow[CATLOVER_NODE(ci)][DOGLOVER_NODE(di)] = 1;
      }
    }

    maxFlow.run(flow, 0, V+1);

    // The maximum matching in a bipartite graph is equal to the size of the
    // minimum vertex cover according to König's theorem.
    // Then we also have that the size of the maximum independent set is equal
    // to |V| - |Size of minimum vertex cover|. In other words
    // |Maximum independent set| = |V| - |Size of maximum matching|.
    std::cout << V - maxFlow.flow() << std::endl;
  }

  return 0;
}
