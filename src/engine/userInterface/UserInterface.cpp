#include "UserInterface.hpp"

UserInterface::UserInterface() {}

void UserInterface::init(GLFWwindow *w) {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

  ImGui::StyleColorsDark();

  ImGui_ImplGlfw_InitForOpenGL(w, true);
  ImGui_ImplOpenGL3_Init("#version 330");
}

void UserInterface::shutdown() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

void UserInterface::render() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  ImGui::ShowDemoWindow();

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
