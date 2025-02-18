#ifndef INPUT_HPP
#define INPUT_HPP

#include <GLFW/glfw3.h>
#include <clue.hpp>

#define NUM_KEYS 350

class KeyListener {
public:
  KeyListener();
  static void keyCallback(GLFWwindow *window, int key, int scancode, int action,
                          int mods) {
    (void)window;
    (void)mods;
    (void)scancode;
    if (action == GLFW_PRESS)
      keyPressed[key] = true;
    else if (action == GLFW_RELEASE)
      keyPressed[key] = false;
  }

  static bool isKeyPressed(int key) {
    if (key < NUM_KEYS)
      return keyPressed[key];
    else
      LOG_ERROR("Key " << key << " is out of bounds from key arrays");
    return false;
  }

private:
  static bool keyPressed[350];
};

class MouseListener {
public:
  MouseListener() {
    this->scrollX = 0;
    this->scrollY = 0;
    this->xPos = 0;
    this->yPos = 0;
    this->lastX = 0;
    this->lastY = 0;
  }

  static void mousePosCallback(GLFWwindow *window, double xPosition,
                               double yPosition) {
    (void)window;
    lastX = xPos;
    lastY = yPos;
    xPos = xPosition;
    yPos = yPosition;
    dragging =
        mouseButtonPresses[0] || mouseButtonPresses[1] || mouseButtonPresses[2];
  }

  static void mouseButtonCallback(GLFWwindow *window, int button, int action,
                                  int mods) {
    (void)window;
    (void)mods;
    if (action == GLFW_PRESS) {
      if (button < 3)
        mouseButtonPresses[button] = true;
    } else if (action == GLFW_RELEASE) {
      if (button < 3) {
        mouseButtonPresses[button] = false;
        dragging = false;
      }
    }
  }

  static void mouseScrollCallback(GLFWwindow *window, double xOffset,
                                  double yOffset) {
    (void)window;
    scrollX = xOffset;
    scrollY = yOffset;
  }

  static void endFrame() {
    scrollX = 0;
    scrollY = 0;
    lastX = xPos;
    lastY = yPos;
  }

  static float getX() { return (float)xPos; }
  static float getY() { return (float)yPos; }
  static float getDx() { return (float)(lastX - xPos); }
  static float getDy() { return (float)(lastY - yPos); }
  static float getScrollX() { return (float)scrollX; }
  static float getScrollY() { return (float)scrollY; }
  static bool isDragging() { return dragging; }
  static bool isMouseButtonDown(int button) {
    if (button < 3)
      return mouseButtonPresses[button];
    return false;
  }

private:
  static double scrollX, scrollY;
  static double xPos, yPos, lastX, lastY;
  static bool mouseButtonPresses[3];
  static bool dragging;
};

#endif // INPUT_HPP
