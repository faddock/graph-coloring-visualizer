#pragma once

#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include <node.h>
#include <vector>
#include <unordered_map>


using std::vector;
using glm::vec2;
namespace graph_color {

class GraphContainer {
    //map of nodes_
    std::unordered_map<int, graph_color::Node*> nodes_;
    int chromatic_number_ = 0;
    const float kRadius = 10.0;

    vector<int> selected_node_ids_;

    //colors_ list (8). after which, colours will be automatically generated
    vector<ci::Color8u> colors_ = {ci::Color8u(255, 255, 255), ci::Color8u(204, 150, 255), ci::Color8u(100, 149, 237), ci::Color8u(223, 255, 0), ci::Color8u(255, 191, 0), ci::Color8u(64, 224, 208), ci::Color8u(255, 127, 80), ci::Color8u(222, 49, 99), ci::Color8u(159, 226, 191)};
    //hex codes: "#6495ED","#CCCCFF","#DFFF00","#FFBF00","#40E0D0","#FF7F50","#DE3163","#9FE2BF"

    //data
    int graph_data_[7][7] = {{0, 1, 1, 0, 1, 1, 0},
                             {1, 0, 0, 1, 1, 0, 1},
                             {1, 0, 0, 1, 1, 1, 0},
                             {0, 1, 1, 0, 1, 0, 1},
                             {1, 1, 1, 1, 0, 0, 0},
                             {1, 0, 1, 0, 0, 0, 1},
                             {0, 1, 0, 1, 0, 1, 0}};

public:
    vec2 boundary_top_left_ = vec2(100, 100);
    vec2 boundary_bottom_right_ = vec2(500,500);
    int graph_dimension_;

    //constructors
    GraphContainer();
    GraphContainer(vec2 setBoundaryTopLeft, vec2 setBoundaryBottomRight);

    //destructor
    ~GraphContainer();

    //getters
    int getChromaticNumber() const;

    const float getRadius() const;

    const std::unordered_map<int, graph_color::Node *> &getNodes() const;

    const vector<int> &getSelectedNodeIds() const;

    //setters
    void setChromaticNumber(int chromaticNumber);

    //custom
    /**
     * Algorithm to color the graph_color and return its chromatic number.
     * @return chromatic number
     */
    int ColorGraph();

    /**
     * Loads adjacent matrix values from a file into the nodes_ map.
     */
    void LoadAdjMatrix();

    /**
     * Generates random number for the coordinates when loading a graph_color.
     * @param lower lower bound of random number
     * @param upper upper bound of random number
     * @return
     */
    float GenerateRandomNumber(float lower, float upper);

    /**
     * puts together two random coordinates to return a vec2.
     * @return position vector
     */
    vec2 GenerateRandomCoordinate();

    /**
     * Adds a node to the node Id when mouse clicked and manages node selection for movement.
     * @param vec position vector of the node to be added
     */
    void AddAndSelectNode(const glm::ivec2 &vec);

    /**
     * Adds an edge from two position vectors of nodes_, after being called twice.
     * @param vec position vector of a node
     */
    void AddEdge(const glm::ivec2 &vec);

    /**
     * returns a vectors of color ids of the adjacent nodes_ to a given node.
     * @param node give node
     * @return vector of color Ids
     */
    vector<int>* FindAdjacentNodesColorIds(Node *node);

    /**
     * returns shortest distance between any two positions.
     * @param p1 position 1
     * @param p2 position 2
     * @return distance
     */
    float ComputeDistance(vec2 p1, vec2 p2);

    /**
     * Displays the container walls and the positions and colors_ of nodes_.
     */
    void Display();

    /**
     * Clears the nodes_ vector, chromatic number, and selected Nodes vector.
     */
    void Reset();

    /**
     * Adds a randomly generated color to the colors_ vector.
     */
    void AddRandomColor();

    /**
     * Modifies the nodes_ map to make each and every node connect to each other.
     */
    void ConnectAllNodes();

    /**
     * Removes a node by setting its hidden parameter to true.
     * @param vec
     */
    void RemoveNode(vec2 vec);

    /**
     * Empties the selected Nodes vector.
     */
    void ClearSelectedNodes();

    /**
     * Updates Node position while it is being moved.
     * @param vec position vector
     */
    void UpdateNodePosition(const glm::ivec2 &vec);

    /**
     * Selects a node by adding its id to a selected nodes_ list.
     * @param vec position vector to select the node at
     * @return whether the node is selected or node
     */
    bool SelectNode(vec2 vec);

    friend std::ostream &operator<<( std::ostream &output, const GraphContainer &D );
    friend std::istream &operator>>(std::istream &is, GraphContainer &container_);

    };
} // namespace graph_color
