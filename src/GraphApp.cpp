#include "../include/GraphApp.h"

namespace graph_color {
    GraphApp::GraphApp() {
        ci::app::setWindowSize((int) kWindowWidth, (int) kWindowHeight);
    }

    void GraphApp::setup() {

        //container_.LoadAdjMatrix();
        mode.vertex_ = false;
        mode.edge_ = false;
        mode.remove_ = false;
        is_enter_pressed_ = false;
        is_a_pressed_ = false;
        is_del_pressed_ = false;
        is_chromatic_num_outdated_ = false;
        is_save_pressed_ = false;
        is_load_pressed_ = false;
    }

    void GraphApp::draw() {
        ci::Color background_color("black");
        ci::gl::clear(background_color);
        if (mode.vertex_) {
            ci::gl::drawString("vertex mode: enabled", vec2{550, 100}, ci::Color("green"), ci::Font("arial", 25));
        } else {
            ci::gl::drawString("vertex mode: disabled [V]", vec2{550, 100}, ci::Color("white"), ci::Font("arial", 25));
        }
        if (mode.edge_) {
            ci::gl::drawString("edge mode: enabled", vec2{550, 150}, ci::Color("green"), ci::Font("arial", 25));
        } else {
            ci::gl::drawString("edge mode: disabled [E]", vec2{550, 150}, ci::Color("white"), ci::Font("arial", 25));
        }
        if (mode.remove_) {
            ci::gl::drawString("remove mode: enabled", vec2{550, 200}, ci::Color("green"), ci::Font("arial", 25));
        } else {
            ci::gl::drawString("remove mode: disabled [R]", vec2{550, 200}, ci::Color("white"), ci::Font("arial", 25));
        }
        if (is_a_pressed_) {
            ci::gl::drawString("connect all nodes: [A]", vec2{550, 280}, ci::Color("red"), ci::Font("arial", 25));
        } else {
            ci::gl::drawString("connect all nodes: [A]", vec2{550, 280}, ci::Color("white"), ci::Font("arial", 25));
        }
        if (is_save_pressed_) {
            ci::gl::drawString("Save [S]", vec2{550, 485}, ci::Color("red"), ci::Font("arial", 25));
        } else {
            ci::gl::drawString("Save [S]", vec2{550, 485}, ci::Color("darkorange"), ci::Font("arial", 25));
        }
        if (is_load_pressed_) {
            ci::gl::drawString("Load [L]", vec2{700, 485}, ci::Color("red"), ci::Font("arial", 25));
        } else {
            ci::gl::drawString("Load [L]", vec2{700, 485}, ci::Color("darkorange"), ci::Font("arial", 25));
        }
        if (is_del_pressed_) {
            ci::gl::drawString("Clear [delete]", vec2{405, 80}, ci::Color("red"), ci::Font("arial", 20));
        } else {
            ci::gl::drawString("Clear [delete]", vec2{405, 80}, ci::Color("white"), ci::Font("arial", 20));
        }
        if (is_enter_pressed_) {
            ci::gl::drawString("[SpaceBar] Chromatic number: " + std::to_string(container_.getChromaticNumber()),
                               vec2{100, 510}, ci::Color("red"), ci::Font("arial", 25));
        } else if (is_chromatic_num_outdated_) {
            ci::gl::drawString("[SpaceBar] Chromatic number: " + std::to_string(container_.getChromaticNumber()) + "*",
                               vec2{100, 510}, ci::Color("slateblue"), ci::Font("arial", 25));
        } else {
            ci::gl::drawString("[SpaceBar] Chromatic number: " + std::to_string(container_.getChromaticNumber()),
                               vec2{100, 510}, ci::Color("slateblue"), ci::Font("arial", 25));
        }
        container_.Display();
    }

    void GraphApp::update() {
        AppBase::update();
        //container_.Display();

    }

    void GraphApp::keyUp(ci::app::KeyEvent event) {
        switch (event.getCode()) {
            case ci::app::KeyEvent::KEY_DELETE:
                is_del_pressed_ = false;
                break;
            case ci::app::KeyEvent::KEY_RETURN:
            case ci::app::KeyEvent::KEY_SPACE:
                is_enter_pressed_ = false;
                break;
            case ci::app::KeyEvent::KEY_a:
                is_a_pressed_ = false;
                break;
            case ci::app::KeyEvent::KEY_s:
                is_save_pressed_ = false;
                break;
            case ci::app::KeyEvent::KEY_l:
                is_load_pressed_ = false;
                break;
        }
    }

    void GraphApp::keyDown(ci::app::KeyEvent event) {
        switch (event.getCode()) {
            case ci::app::KeyEvent::KEY_DELETE:
                is_del_pressed_ = true;
                container_.Reset();
                break;
            case ci::app::KeyEvent::KEY_RETURN:
            case ci::app::KeyEvent::KEY_SPACE:
                is_enter_pressed_ = true;
                chromatic_num_ = container_.ColorGraph();
                is_chromatic_num_outdated_ = false;
                container_.ClearSelectedNodes();
                break;
            case ci::app::KeyEvent::KEY_v:
                mode.vertex_ = true;
                mode.edge_ = false;
                mode.remove_ = false;
                container_.ClearSelectedNodes();
                break;
            case ci::app::KeyEvent::KEY_e:
                mode.edge_ = true;
                mode.vertex_ = false;
                mode.remove_ = false;
                break;
            case ci::app::KeyEvent::KEY_a:
                is_a_pressed_ = true;
                is_chromatic_num_outdated_ = true;
                container_.ClearSelectedNodes();
                container_.ConnectAllNodes();
                break;
            case ci::app::KeyEvent::KEY_r:
                mode.remove_ = true;
                mode.edge_ = false;
                mode.vertex_ = false;
                container_.ClearSelectedNodes();
                break;
            case ci::app::KeyEvent::KEY_s: {
                is_save_pressed_ = true;
                std::ofstream output_file = std::ofstream(file_path_);
                output_file << container_;
                break;
            }
            case ci::app::KeyEvent::KEY_l: {
                is_load_pressed_ = true;
                auto input_file = std::ifstream(file_path_);
                input_file >> container_;
                container_.LoadAdjMatrix();
                break;
            }
        }
    }

    void GraphApp::mouseDown(ci::app::MouseEvent event) {
        auto xCoord = static_cast<float>(event.getX());
        auto yCoord = static_cast<float>(event.getY());
        float radius = container_.getRadius();
        if (xCoord < container_.boundary_bottom_right_.x - radius &&
            xCoord > container_.boundary_top_left_.x + radius &&
            yCoord < container_.boundary_bottom_right_.y - radius &&
            yCoord > container_.boundary_top_left_.y + radius) {
            if (mode.vertex_) {
                container_.AddAndSelectNode(vec2{event.getX(), event.getY()});
                is_chromatic_num_outdated_ = true;
            }
            if (mode.edge_) {
                container_.AddEdge(vec2{event.getX(), event.getY()});
                is_chromatic_num_outdated_ = true;
            }
            if (mode.remove_) {
                container_.RemoveNode(vec2{event.getX(), event.getY()});
                is_chromatic_num_outdated_ = true;
            }
        }
    }

    void GraphApp::mouseDrag(cinder::app::MouseEvent event) {
        if (mode.vertex_) {
            auto xCoord = static_cast<float>(event.getX());
            auto yCoord = static_cast<float>(event.getY());
            float radius = container_.getRadius();
            if (container_.SelectNode(vec2{xCoord, yCoord}) &&
                xCoord < container_.boundary_bottom_right_.x - radius &&
                xCoord > container_.boundary_top_left_.x + radius &&
                yCoord < container_.boundary_bottom_right_.y - radius &&
                yCoord > container_.boundary_top_left_.y + radius) {
                container_.UpdateNodePosition(vec2{xCoord, yCoord});
            }
        }
    }

    void GraphApp::mouseUp(cinder::app::MouseEvent event) {
        if (mode.vertex_) {
            container_.ClearSelectedNodes();
        }
    };
    std::istream &operator>>(std::istream &is, GraphContainer &container_) {

        std::string line;
        getline(is, line);
        std::stringstream ss(line);
        size_t dimension;
        ss >> dimension;
        container_.graph_dimension_ = dimension;
        container_.graph_data_[dimension][dimension];
        size_t row_idx = 0;
        while (getline(is, line)) { // reading each row
            ss = std::stringstream (line);
            for (size_t i = 0; i < dimension; i++) { // Reading each column
                ss >> container_.graph_data_[row_idx][i];
            }
            row_idx++;
        }
        return is;
    }

    std::ostream &operator<<(std::ostream &os, const GraphContainer &container_) {

        int length = container_.getNodes().size();
        os << length << "\n";

        for (auto &pair: container_.getNodes()) {
            vector<int> AdjNodeIds = pair.second->getAdjacentNodeIds();
            for (int id = 0; id < length; id++) {
                if (std::count(AdjNodeIds.begin(), AdjNodeIds.end(), id) == 1) {
                    os << "1" << " ";
                } else {
                    os << "0" << " ";
                }
            };
            os << "\n";
        }
        return os;
    }

} // namespace graph_color