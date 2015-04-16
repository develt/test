#include <iostream>
#include <string>
#include <set>
#include "graph_wrapper.h"

namespace alfa_test {

using namespace std;

bool is_sim(const wstring& s1, const wstring& s2)
{
  if (s1.size() != s2.size() || s1 == s2 || s1.empty())
      return false;
        
  size_t cnt = 0;

  for(size_t i = 0; i < s1.size() && cnt < 2; ++i)
  {
      if (s1.at(i) != s2.at(i))
        ++cnt;
  }
        
  return cnt == 1;
}

graph_wrapper::graph_wrapper()
{
}

graph_wrapper::~graph_wrapper()
{
}

void graph_wrapper::add_link(size_t src, size_t dst) 
{
  bool ins = false;
        
  tie(descr_, ins) = add_edge(src, dst, graph_); 
  weightmap_[descr_] = 1;
}


void graph_wrapper::make_dict(vector<wstring>& dict) 
{
  wcout << "\n";
    
  for(size_t i = 0; i < dict.size(); ++i)
  {
      for(size_t j = i + 1; j < dict.size() - 1; ++j)
      {
          if (!is_sim(dict[i], dict[j]))
			  continue;

          add_link(i + 1, j + 1); 
      }
  }
}


bool graph_wrapper::get_shortest_path(size_t end, size_t bgn,
	vector<wstring>& dict)
{
  graph_.clear();

  make_dict(dict); 

  vd_ = vertex(bgn, graph_);

  vector<graph_t::vertex_descriptor> pp(num_vertices(graph_));

  vector<double> dd(num_vertices(graph_));

  dijkstra_shortest_paths(graph_, vd_, 
	    predecessor_map(&pp[0]).distance_map(&dd[0])); 
        
  wcout << endl << dd[end] << " step from \"" << 
	  dict[end - 1] << "\" to \"" << dict[bgn - 1] <<"\":" << endl;  

  if (dd[end] > dict.size())
  {
      wcout << L"no transformation path found" << endl;

      return false;
  }

  size_t i = end; 
	
  wcout << dict[i - 1] << endl; 

  while(i != bgn)
  {
      i = pp[i]; 

      wcout << dict[i - 1] << endl;
  }

  return true;
}

}  //  namespace alfa_test
