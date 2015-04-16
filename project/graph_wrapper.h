#ifndef SRC_GRAPH_WRAPPER_H_
#define SRC_GRAPH_WRAPPER_H_

#include <memory>
#include <boost/graph/dijkstra_shortest_paths.hpp> 
#include <boost/graph/adjacency_list.hpp>

namespace alfa_test {

using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS, 
	           property<vertex_distance_t, double>, 
	               property<edge_weight_t, double>> graph_t; 

class graph_wrapper
{
  public:
	graph_wrapper();
	virtual ~graph_wrapper();

	bool get_shortest_path(size_t end, size_t bgn, 
	    std::vector<std::wstring>& dict);

  private:
    void add_link(size_t src, size_t dst);  

  void make_dict(std::vector<std::wstring>& dict); 

  private:
    property_map<graph_t, edge_weight_t>::type weightmap_;
    graph_t::edge_descriptor descr_; 
    graph_t::vertex_descriptor vd_; 
    graph_t graph_; 

};

}  //  namespace alfa_test
#endif  //  SRC_GRAPH_WRAPPER_H_