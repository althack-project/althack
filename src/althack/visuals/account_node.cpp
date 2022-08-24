#include <althack/visuals/account_node.hpp>

#include <iostream>
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui_internal.h>

namespace althack {
namespace visuals {

AccountNode::AccountNode(const std::string& identifier)
  : Node(identifier) {
}

void AccountNode::draw(const ImVec2 position, bool hovered, bool dragged) {
  const float opacity = dragged ? 0.5 : 1.0;
  const ImVec2 nd_size = size();
  const ImU32 col_bg =
    hovered ? ImGui::ColorConvertFloat4ToU32(ImVec4(0.9, 0.9, 0.9, opacity))
            : ImGui::ColorConvertFloat4ToU32(ImVec4(1.0, 1.0, 1.0, opacity));
  const ImU32 col_border =
    hovered ? ImGui::ColorConvertFloat4ToU32(ImVec4(0.1, 0.1, 0.1, opacity))
            : ImGui::ColorConvertFloat4ToU32(ImVec4(0.3, 0.3, 0.3, opacity));
  const ImU32 col_shadow = ImGui::ColorConvertFloat4ToU32(ImVec4(0.3, 0.3, 0.3, 0.5 * opacity));
  const ImVec2 shadow_offset{2.0f, 2.0f};

  ImDrawList* draw_list = ImGui::GetWindowDrawList();
  draw_list->AddRectFilled(position - nd_size / 2.0 + shadow_offset, position + nd_size / 2.0 + shadow_offset, col_shadow, 5.0f);
  draw_list->AddRectFilled(position - nd_size / 2.0, position + nd_size / 2.0, col_bg, 5.0f);
  draw_list->AddRect(position - nd_size / 2.0, position + nd_size / 2.0, col_border, 5.0f);
}

ImVec2 AccountNode::size() const {
  return ImVec2(200, 100);
}

bool AccountNode::hit(const ImVec2 node_position, const ImVec2 hit_position) const {
  const ImVec2 node_size = size();
  const ImRect node_rect{node_position - node_size / 2.0, node_position + node_size / 2.0};
  return node_rect.Contains(hit_position);
}

}  // namespace visuals
}  // namespace althack
