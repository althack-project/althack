#include <althack/visuals/account_node.hpp>

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui_internal.h>

namespace althack {
namespace visuals {

AccountNode::AccountNode(
    const std::string& identifier, const std::string& provider,
    const std::string& account, double amount, const std::string& currency)
  : Node(identifier)
  , provider_{provider}
  , account_{account}
  , amount_{amount}
  , currency_{currency} {
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
  const ImVec2 top_left = position - nd_size / 2.0;
  const ImVec2 bottom_right = position + nd_size / 2.0;
  // Shadow
  draw_list->AddRectFilled(top_left + shadow_offset, bottom_right + shadow_offset, col_shadow, 5.0f);
  // Background
  draw_list->AddRectFilled(top_left, bottom_right, col_bg, 5.0f);
  // Border
  draw_list->AddRect(top_left, bottom_right, col_border, 5.0f);

  const ImU32 col_text = ImGui::ColorConvertFloat4ToU32(ImVec4(0.1, 0.1, 0.1, 1.0 * opacity));
  ImVec2 text_offset{5.0f, 5.0f};
  // Provider text
  draw_list->AddText(top_left + text_offset, col_text, provider_.c_str());
  text_offset += ImVec2{0.0f, 15.0f};
  draw_list->AddText(top_left + text_offset, col_text, account_.c_str());
  text_offset += ImVec2{0.0f, 15.0f};
  draw_list->AddText(top_left + text_offset, col_text, (std::to_string(amount_) + " " + currency_).c_str());
}

ImVec2 AccountNode::size() const {
  return ImVec2(150, 52);
}

}  // namespace visuals
}  // namespace althack
