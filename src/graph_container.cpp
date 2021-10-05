#include "../include/graph_container.h"

using namespace std;
using glm::vec2;

namespace graph_color {


    GraphContainer::GraphContainer() {}

    GraphContainer::GraphContainer(vec2 setBoundaryTopLeft, vec2 setBoundaryBottomRight) {
        this->boundary_top_left_ = setBoundaryTopLeft;
        this->boundary_bottom_right_ = setBoundaryBottomRight;
    }

    float GraphContainer::GenerateRandomNumber(float lower, float upper) {
        float random_number_ =
                lower + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (upper - lower)));
        std::cout << "Random Number: " << random_number_ << std::endl;
        return random_number_;
    }

    void GraphContainer::AddAndSelectNode(const glm::ivec2 &vec) {
        bool add = true;
        for (auto pair : nodes_) {
            if (2 * kRadius > ComputeDistance(vec, pair.second->getPosition()) && !pair.second->isHidden()) {
                add = false;
            }
            if (kRadius >= ComputeDistance(vec, pair.second->getPosition()) && !pair.second->isHidden() &&
                selected_node_ids_.empty())
                if (SelectNode(vec)) {
                    continue;
                }
        }
        if (add == true) {
            Node *node = new Node(vec, nodes_.size(), 0, false);
            nodes_.insert({nodes_.size(), node});
        }
    }

    void GraphContainer::UpdateNodePosition(const glm::ivec2 &vec) {
        nodes_[selected_node_ids_[0]]->setPosition(vec);
    }

    vec2 GraphContainer::GenerateRandomCoordinate() {
        double x_coordinate = GenerateRandomNumber(boundary_top_left_.x + kRadius,
                                                   boundary_bottom_right_.x - kRadius);
        double y_coordinate = GenerateRandomNumber(boundary_top_left_.y + kRadius,
                                                   boundary_bottom_right_.y - kRadius);
        return vec2{x_coordinate, y_coordinate};
    }

    void GraphContainer::LoadAdjMatrix() {
        int id_count = -1;
        for (int i = 0; i < graph_dimension_; i++) {
            id_count++;

            Node *node = new Node(GenerateRandomCoordinate(),id_count, 0, false); //creates a new node with a different id
            for (int j = 0; j < graph_dimension_; j++) {
                if (graph_data_[i][j] == 1) {
                    node->AddAdjacentNodeId(j);
                }
            }
            nodes_[nodes_.size()] = node;
        }
    }

    int GraphContainer::ColorGraph() {
        chromatic_number_ = 0;
        for (auto pair : nodes_) {
            Node *node = pair.second;
            vector<int> *AdjColorIds = FindAdjacentNodesColorIds(node);

            if (!node->isHidden()) {
                if (!node->isColored()) {
                    AddRandomColor();
                }
                for (int colorId = 1; colorId < static_cast<int>(colors_.size()); colorId++) {
                    if (std::count(AdjColorIds->begin(), AdjColorIds->end(), colorId) == 0) {
                        node->setColorId(colorId);
                        chromatic_number_ = max(chromatic_number_, colorId);
                        node->setColored(true);
                        break;
                    }
                }
            }
        }
        return chromatic_number_;
    }

    void GraphContainer::AddRandomColor() {
        int rgb[3];
        for (int i = 0; i < 3; i++) {
            rgb[i] = rand() % 256;
        }
        colors_.push_back(ci::Color8u(rgb[0], rgb[1], rgb[2]));
    }


    vector<int> *GraphContainer::FindAdjacentNodesColorIds(Node *node) {
        vector<int> *adj_nodes_color_ids = new vector<int>();
        for (int id : node->getAdjacentNodeIds()) {
            if (!nodes_[id]->isHidden()) {
                adj_nodes_color_ids->push_back(nodes_[id]->getColorId());
            }
        }
        return adj_nodes_color_ids;
    }

    GraphContainer::~GraphContainer() {
        for (auto pair : nodes_) {
            delete pair.second;
        }
    }

    void GraphContainer::Display() {
        for (auto pair : nodes_) {
            //color and draw nodes
            if (pair.second->isSelected()) {
                ci::gl::color(ci::Color("red"));
                ci::gl::drawSolidCircle(pair.second->getPosition(), kRadius);
            } else if (!pair.second->isHidden()) {
                ci::gl::color(colors_[pair.second->getColorId()]);
                ci::gl::drawSolidCircle(pair.second->getPosition(), kRadius);
            }
            //draw edges
            for (int id : pair.second->getAdjacentNodeIds()) {
                if (!nodes_[id]->isHidden() && !pair.second->isHidden()) {
                    ci::gl::color(ci::Color("White"));
                    ci::gl::drawLine(nodes_[id]->getPosition(), pair.second->getPosition());
                    // Hello this is Suyash from the future
                    // You will get herpes in exactly one year.
                    //colors_[pair.second->getColorId()]
                }
            }
        }
        //Draw Boundary
        ci::gl::color(ci::Color("white"));
        ci::gl::drawStrokedRect(ci::Rectf(boundary_top_left_, boundary_bottom_right_));
    }

    void GraphContainer::Reset() {
        nodes_.clear();
        setChromaticNumber(0);
        selected_node_ids_.clear();
    }

    bool GraphContainer::SelectNode(vec2 vec) {
        bool selected = false;
        for (auto pair : nodes_) {
            if (kRadius >= ComputeDistance(vec, pair.second->getPosition()) && !pair.second->isHidden()) {
                pair.second->setSelected(true);
                selected = true;
                selected_node_ids_.push_back(pair.first);
            }
        }
        return selected;
    }

    void GraphContainer::AddEdge(const glm::ivec2 &vec) {
        bool selected = SelectNode(vec);
        if (selected_node_ids_.size() == 2) {
            nodes_[selected_node_ids_[1]]->AddAdjacentNodeId(selected_node_ids_[0]);
            nodes_[selected_node_ids_[0]]->AddAdjacentNodeId(selected_node_ids_[1]);
            nodes_[selected_node_ids_[1]]->setSelected(false);
            nodes_[selected_node_ids_[0]]->setSelected(false);
            selected_node_ids_.clear();
        }
    }

    void GraphContainer::RemoveNode(vec2 vec) {
        for (auto pair : nodes_) {
            if (kRadius >= ComputeDistance(vec, pair.second->getPosition())) {
                pair.second->setHidden(true);
                if (pair.second->isColored()) {
                    colors_.pop_back();
                }
                break;
            }
        }
    }

    float GraphContainer::ComputeDistance(vec2 p1, vec2 p2) {
        return sqrtf(pow(p1.x - p2.x, 2) +
                     pow(p2.y - p1.y, 2));
    }

    void GraphContainer::ConnectAllNodes() {
        for (auto pair : nodes_) {
            Node *node = pair.second;
            vector<int> a = node->getAdjacentNodeIds();
            for (int id = 0; id < static_cast<int>(nodes_.size()); id++) {
                if (id != pair.first && std::count(a.begin(), a.end(), id) != 1) {
                    node->AddAdjacentNodeId(id);
                }
            }
        }
    }

    void GraphContainer::ClearSelectedNodes() {
        for (int i : selected_node_ids_) {
            nodes_[i]->setSelected(false);
        }
        selected_node_ids_.clear();
    }

    //getters
    const unordered_map<int, graph_color::Node *> &GraphContainer::getNodes() const {
        return nodes_;
    }

    int GraphContainer::getChromaticNumber() const {
        return chromatic_number_;
    }

    const float GraphContainer::getRadius() const {
        return kRadius;
    }

    const vector<int> &GraphContainer::getSelectedNodeIds() const {
        return selected_node_ids_;
    }

    //setters
    void GraphContainer::setChromaticNumber(int chromaticNumber) {
        chromatic_number_ = chromaticNumber;
    }

} // namespace graph_color