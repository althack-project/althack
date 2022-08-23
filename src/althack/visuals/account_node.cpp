#include <althack/visuals/account_node.hpp>

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui_internal.h>

namespace althack {
namespace visuals {

AccountNode::AccountNode(const std::string& identifier)
  : Node(identifier) {
}

void AccountNode::draw(const ImVec2 position) {
  const ImVec2 nd_size = size();
  const ImU32 col_fill = ImGui::ColorConvertFloat4ToU32(ImVec4(0.3, 0.1, 0.5, 1.0));

  ImDrawList* draw_list = ImGui::GetWindowDrawList();
  draw_list->AddRectFilled(position - nd_size / 2.0, position + nd_size / 2.0, col_fill, 0.3f);
}

ImVec2 AccountNode::size() const {
  return ImVec2(200, 50);
}

}  // namespace visuals
}  // namespace althack
