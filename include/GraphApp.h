#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "graph_container.h"

namespace graph_color {
    class GraphApp : public ci::app::App {

    public:
        GraphApp();

        void draw() override;

        void update() override;

        void keyDown(ci::app::KeyEvent event) override;

        void mouseDown(ci::app::MouseEvent event) override;

        void mouseDrag(ci::app::MouseEvent event) override;

        void setup() override;

        void keyUp(ci::app::KeyEvent event) override;

        void mouseUp(cinder::app::MouseEvent event) override;


    private:
        const float kWindowWidth = 1000;
        const float kWindowHeight = 600;
        std::string file_path_ = "D:\\Cinder\\my-projects\\final-project-faddock\\data\\graph_data_output.txt";
        GraphContainer container_;
        bool is_del_pressed_;
        bool is_a_pressed_;
        bool is_enter_pressed_;
        bool is_save_pressed_;
        bool is_load_pressed_;
        int is_chromatic_num_outdated_;
        int chromatic_num_;

        struct Mode {
            bool vertex_;
            bool edge_;
            bool remove_;
        };

        Mode mode;
        };
}
