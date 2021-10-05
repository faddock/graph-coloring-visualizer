

# Graph Coloring Visualizer
<!-- ![Image of Title Screen](https://github.com/uiuc-sp21-cs126/final-project-faddock/blob/main/assets/graphApp_title.png) -->
<p align="center">

<img src="https://github.com/uiuc-sp21-cs126/final-project-faddock/blob/main/assets/graphApp_title.png" alt="graph title img" width="300" height="300">
 </p>
<p align="center">
<img src="https://github.com/uiuc-sp21-cs126/final-project-faddock/blob/main/assets/graphApp_screenshot.png" alt="graph App screen" width="800">
</p>

## *ABOUT THIS PROJECT*
The Graph coloring Visualizer allows a user to create a graph and calculate its chromatic number while also providing a visualization of it. This will help students taking Discrete Structures(CS 173) to find the chromatic number of any given graph. 

The coloring algorithm is called backtracking and was written from scratch, based on pen-and-paper methods of sovling graph coloring. The graph visualizer has touch screen support, and allows resizing of the nodes, along with deleting and drawing individual edges. For quick graph construction, it has a 'connect all nodes' feature.




## *DEPENDENCIES*
### Windows or Mac
* [Cinder (v0.9.2)](https://libcinder.org/download)
* [CMake](https://cmake.org/)
###### * for Windows users, download [Visual Studio Code](https://code.visualstudio.com/download) as well


## *GETTING STARTED*
- Download Cinder v0.9.2 for your platform
- Open the ~/Cinder folder in your C++ IDE and click the green build button to build libcinder.
- Download [this](https://github.com/uiuc-sp21-cs126/final-project-faddock) repository into a new folder in the ~/Cinder folder
- Open this folder in your C++ IDE and click run to play the game!

## *CONTROLS*
Key | Action
------------ | -------------
DELETE | Clear graph board
SPACE / ENTER | Calculate Chromatic Number
V | Vertex Mode
E | Edge Mode
R | Remove Mode
S | Save graph
L | Load graph
