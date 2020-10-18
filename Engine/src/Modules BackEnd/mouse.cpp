#include "mouse.h"

#include "window.h"

glm::vec2 Mouse::position;
glm::vec2 Mouse::positionOffset;
glm::vec2 Mouse::positionDirection;

double Mouse::scrollValue;
double Mouse::scrollOffset;

int Mouse::scrollDirection;

int Mouse::buttonPressStatus[3];

Mouse::Mouse(Window* window) {

	position = glm::vec2(-1.0f);
	positionOffset = glm::vec2(0.0f);
	positionDirection = glm::vec2(0.0f);

	scrollValue = 0.0;
	scrollOffset = 0.0;

	scrollDirection = 0;

	for (int i = 0; i < 3; ++i) { buttonPressStatus[i] = (int)ButtonState::CLEAR; }

	glfwSetCursorPosCallback(window->getWindow(), onMouseMove);
	glfwSetScrollCallback(window->getWindow(), onMouseWheelScroll);
	glfwSetMouseButtonCallback(window->getWindow(), mouse_button_callback);

	glfwSetInputMode(window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);

}

Mouse::~Mouse() { }

void Mouse::switchWindowCapture(Window* window) {

	glfwSetCursorPosCallback(window->getWindow(), onMouseMove);
	glfwSetScrollCallback(window->getWindow(), onMouseWheelScroll);
	glfwSetMouseButtonCallback(window->getWindow(), mouse_button_callback);

	glfwSetInputMode(window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);

}

void Mouse::onMouseMove(GLFWwindow *window, double x, double y) {

	if (position.x == -1.0 && position.y == -1.0) {

		position.x = x;
		position.y = y;

		return;

	}

	if (x > position.x) { positionDirection.x = 1.0f; }
	else if (x < position.x) { positionDirection.x = -1.0f; }
	else { positionDirection.x = 0.0f; }

	if (y > position.y) { positionDirection.y = 1.0f; }
	else if (y < position.y) { positionDirection.y = -1.0f; }
	else { positionDirection.y = 0.0f; }

	positionOffset.x = x - position.x;
	positionOffset.y = y - position.y;

	position.x = x;
	position.y = y;

}

void Mouse::onMouseWheelScroll(GLFWwindow *window, double x, double y) {

	if (y > 0.0) { scrollDirection = 1; }
	else { scrollDirection = -1; }

	scrollOffset = y - scrollValue;
	scrollValue = y;

}

void Mouse::mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {

	if (button == GLFW_KEY_UNKNOWN) { return; }

	buttonPressStatus[button] = action;

}

bool Mouse::isPressed(const int &button) {

	//return glfwGetMouseButton(window->getWindow(), button);
	return false;

}

bool Mouse::isPressedOnce(const int &button) {

	return buttonPressStatus[button] == (int)ButtonState::PRESS;

}

bool Mouse::isReleased(const int &button) {

	return buttonPressStatus[button] == (int)ButtonState::RELEASE;

}

bool Mouse::isHold(const int &button) {

	return buttonPressStatus[button] == (int)ButtonState::HOLD;

}

void Mouse::postUpdate() {

	for (int i = 0; i < 3; ++i) {

		if (buttonPressStatus[i] == (int)ButtonState::PRESS || buttonPressStatus[i] == (int)ButtonState::RELEASE) { buttonPressStatus[i] = (int)ButtonState::CLEAR; }

	}

}

void Mouse::preUpdate() {

	positionDirection = glm::vec2(0.0f);
	positionOffset = glm::vec2(0.0f);

	scrollDirection = 0;

}

glm::vec2& const Mouse::getPosition() { return position; }

glm::vec2& const Mouse::getPositionOffset() { return positionOffset; }

glm::vec2& const Mouse::getPositionDirection() { return positionDirection; }

double& const Mouse::getScrollValue() { return scrollValue; }

double& const Mouse::getOffsetScrol() { return scrollOffset; }

int& const Mouse::getScrollDirection() { return scrollDirection; }