#ifndef ALTHACK_VISUALS_ACCOUNT_NODE_HPP_
#define ALTHACK_VISUALS_ACCOUNT_NODE_HPP_

// AltHack
#include <althack/visuals/node.hpp>

namespace althack {
namespace visuals {

//! \brief Funds holding account node class.
class AccountNode : public Node {
 public:
  //! \brief Initializes this instance.
  /*!
    \param identifier The internal string identifier, passed to the Node superclass.
    \param provider The provider identifier for the provider that holds this account.
    \param account The account identifier at the provider.
    \param amount The initial funds amount held by this account.
    \param currency The currency identifier for this account.
   */
  AccountNode(
      const std::string& identifier, const std::string& provider,
      const std::string& account, double amount, const std::string& currency);

  void draw(const ImVec2 position, bool hovered, bool dragged) override;

  ImVec2 size() const override;

  //! \brief Sets the amount this visual node displays.
  /*!
    \param amount The currency amount to display for this account node.
   */
  void setAmount(double amount);

  //! \brief Returns the provider identifier string.
  /*!
    \returns The string value denoting which provider this account associates to.
   */
  const std::string& getProvider() const;

  //! \brief Returns the account identifier string.
  /*!
    \returns The string value denoting the account at the specified provider.
   */
  const std::string& getAccount() const;

  const std::string& getCurrency() const;

  double getAmount() const;

 private:
  //! \brief The provider identifier for the provider that holds this account.
  const std::string provider_;

  //! \brief The account identifier at the provider.
  const std::string account_;

  //! \brief The initial funds amount held by this account.
  const std::string currency_;

  //! \brief The currency identifier for this account.
  double amount_;
};

}  // namespace visuals
}  // namespace althack

#endif  // ALTHACK_VISUALS_ACCOUNT_NODE_HPP_
