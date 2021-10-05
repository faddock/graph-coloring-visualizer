#include "../include/node.h"

namespace graph_color {
    //constructors
    Node::Node(int nId, int cId) {
        colored = false;
        nodeId = nId;
        colorId = cId;
    }

    Node::Node(vec2 pos, int nId, int cId, bool slct) {
        colored = false;
        nodeId = nId;
        colorId = cId;
        position = pos;
        selected = slct;
        hidden = false;
    }

    //getters
    vector<int> &Node::getAdjacentNodeIds() {
        return adjacent_node_ids;
    }

    bool Node::isColored() const {
        return colored;
    }

    int Node::getColorId() const {
        return colorId;
    }

    int Node::getNodeId() const {
        return nodeId;
    }

    bool Node::isSelected() const {
        return selected;
    }

    const vec2 &Node::getPosition() const {
        return position;
    }

    bool Node::isHidden() const {
        return hidden;
    }


    //setters
    void Node::setAdjacentNodeIds(const vector<int> &adjacentNodeIds) {
        adjacent_node_ids = adjacentNodeIds;
    }

    void Node::setColored(bool colored) {
        Node::colored = colored;
    }

    void Node::setColorId(int colorId) {
        Node::colorId = colorId;
    }

    void Node::setNodeId(int nodeId) {
        Node::nodeId = nodeId;
    }

    void Node::setSelected(bool selected) {
        Node::selected = selected;
    }

    void Node::setPosition(const vec2 &position) {
        Node::position = position;
    }

    void Node::setHidden(bool hidden) {
        Node::hidden = hidden;
    }

    //custom
    void Node::AddAdjacentNodeId(int id) {
        adjacent_node_ids.push_back(id);
    }

} // namespace graph_color