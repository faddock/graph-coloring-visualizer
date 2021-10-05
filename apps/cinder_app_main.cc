#include "graph_container.h"
#include "GraphApp.h"

using graph_color::GraphApp;

void prepareSettings(GraphApp::Settings* settings) {
  settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(GraphApp, ci::app::RendererGl, prepareSettings);
