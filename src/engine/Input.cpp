#include <jade/windowing/Input.hpp>

// Define KeyListener static members
bool KeyListener::keyPressed[NUM_KEYS] = {false};

// Define MouseListener static members
double MouseListener::scrollX = 0;
double MouseListener::scrollY = 0;
double MouseListener::xPos = 0;
double MouseListener::yPos = 0;
double MouseListener::lastX = 0;
double MouseListener::lastY = 0;
bool MouseListener::mouseButtonPresses[3] = {false};
bool MouseListener::dragging = false;
