#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include <cstddef>
#include <node.h>
#include <vector>

using std::vector;
using glm::vec2;

namespace graph_color {
class Node {
    vector<int> adjacent_node_ids;
    bool colored;
    bool selected;
    bool hidden;
    int colorId; //index of color
    int nodeId;
    vec2 position;


public:
    Node(int nodeId, int colorId);

    Node(vec2 position, int nodeId, int colorId, bool selected);

    //getters
    vector<int> &getAdjacentNodeIds();

    bool isColored() const;

    int getColorId() const;

    int getNodeId() const;

    const vec2 &getPosition() const;

    bool isSelected() const;

    bool isHidden() const;

    //setters
    void setAdjacentNodeIds(const vector<int> &adjacentNodeIds);

    void setColored(bool colored);

    void setColorId(int colorId);

    void setNodeId(int nodeId);

    void setPosition(const vec2 &position);

    void setSelected(bool selected);

    void setHidden(bool hidden);

    //custom
    void AddAdjacentNodeId(int id);

    //void RemoveAdjacentNodeId(int id);

    vector<ci::Color> FindAdjacentNodesColors();




    //look at linkedlist


    // A node class which stores the color and the edges
    // connected to the node





};

} // namespace graph_color
