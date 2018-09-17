/**
 *  Core graph data structure
 *   Aaron S. Crandall, 2017 <acrandal@gmail.com>
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <queue>
#include <string>
#include <fstream>
#include <vector>
#include <regex>
#include <algorithm>
#include <list>
#include <stack>
#include <unordered_map>
#include <cmath>
#include <cfloat>

#include "Vertex.h"

using namespace std;

class Graph
{
	vector<Vertex*> _vertices;		// All vertices in the graph (vertex id == index)
	int _last_startingID = -1;

public:
	// Remove all vertices
	void clear() {
		_vertices.clear();
	}

	// Number of vertices in our graph
	int size() {
		return _vertices.size();
	}

	/**
	 *  Parses a single in from a dot file
	 */
	void parseDotfileLine( string line ) {
		smatch matched;
		regex newSubGraph ("\\s*(\\S+)\\s*->\\s*(\\S+)\\s*\\[.*?weight=\"*(\\S+?)\"*\\s*\\]\\;");

		if( regex_match( line, matched, newSubGraph ) ) {
			string strconv = matched[1];
			int srcid = ::atof(strconv.c_str());
			strconv = matched[2];
			int destid = ::atof(strconv.c_str());
			strconv = matched[3];
			double weight = ::atof(strconv.c_str());
			//cout << "SrcID: " << srcid << " | DestID: " << destid << " | Edge Weight: " << weight << endl;

			// Grow set of vertices if new high id is inserted or connected to
			int growVerts = max(srcid, destid);
			for( int i = _vertices.size(); i <= growVerts; i++ ) {
				Vertex* newVert = new Vertex(i);		// Allocate the new vertex
				_vertices.push_back( newVert );		// Add vertex to the end of the list 
			}
			_vertices[srcid]->addEdge(_vertices[destid], weight);
		}
	}

	/**
	 *  Loads a single Graphviz-(limited) formatted dot file with a graph
	 */
	void loadDotFile( string filename ) {
		cout << " [d] Loading dot file: " << filename;
		ifstream ifs( filename );
		string instr;
		while (getline(ifs, instr)) {
			parseDotfileLine( instr );
		}
		cout << " - Done." << endl;
	}

	/**
	 *  Returns stringified version of graph for viewing
	 */
	string to_string( bool with_edges = false ) {
		string ret = "";
		for( auto vert : _vertices ) {
			ret += vert->to_string( with_edges ) + "\n";
		}
		return ret;
	}


    ////////////////////////////////////////////////////////////
    
    list<Vertex*> getTopoSort()
    {
        queue<Vertex*> q;
        int count = 0;
        vector <int> topo_order; //using to print out final order
        list<Vertex*> finalOrder;
        vector<int> in_degrees(_vertices.size()); //keeps track of the in-degrees

        for(int i = 0; i < _vertices.size(); i++) //set up in-degrees //////////////////////////////////////WORKING
        {
            //cout << "BREAKPOINT -3" << endl;
            for(auto it = _vertices[i]->getEdges().begin(); it!= _vertices[i]->getEdges().end(); ++it) //iterate
            {
               //cout << "BREAKPOINT -2" << endl;
               in_degrees[(*it).first->getId()]++; 
            }
        }

        //cout << "BREAKPOINT -1" << endl;
        for(int i = 0; i < _vertices.size(); i++) //find the nodes with no in-degrees //////////////////////WORKING
        {
            //cout << "BREAKPOINT 0" << endl;
            //cout << in_degrees[i] << endl;
            if(in_degrees[i] == 0)
            {
                q.push(_vertices[i]);
            }
        }



        while (!q.empty())
        {
            Vertex* x = q.front();
            q.pop();

            topo_order.push_back(x->getId());
            finalOrder.push_back(x);

            _vertices[x->getId()]->set_known();
            count++;

            //cout << "BREAKPOINT 1" << endl;
            for(auto i = x->getEdges().begin(); i!= x->getEdges().end(); ++i) //iterate through adjaecent edges
            {
                //cout << "BREAKPOINT 2" << endl;
                //cout << _vertices[(*i).first->getId()] << " ";
                if(--in_degrees[(*i).first->getId()] == 0 && !((*i).first->is_known())) //if it becomes 0 and is not known
                {
                   
                    q.push((*i).first); //gets sent to the queue
                }
            }
            //delete current x in _vertices once it's edges have been added to the queue
            //_vertices.erase(_vertices.begin() + x->getId());//deletes by iterator position
            delete _vertices[x->getId()];
        }

        if(count != _vertices.size())
        {
            cout << "CYCLE EXISTS IN GRAPH." << endl;
            cout << "COUNT: " << count << endl;
            cout << "VERTICE SIZE: " << _vertices.size() << endl;
        }
        else
        {
            _vertices.clear(); //all vertices have been visited
        }
        ///////////////////print out in topological order
        cout << "  {";
        for(int i = 0; i < topo_order.size(); i++)
        {
            if(i != topo_order.size()-1)
            {
                cout << topo_order[i] << ", ";
            }
            else //OCD formatting
            {
                cout << topo_order[i];
            }
        }
        cout << "}" << endl;
        cout << "NEW GRAPH SIZE (EMPTY):" << _vertices.size() << endl;
        return finalOrder;
        
    }
    
};

#endif
