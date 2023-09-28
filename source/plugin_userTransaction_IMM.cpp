#include "include/pluginInterface/interfaceUserTransaction.h"

  // msmERP header files

#include "include/database/tables/core/tbl_businessTransactions.h"
#include "include/database/tables/core/tbl_menuItems.h"
#include "include/database/tables/core/tbl_objectTypes.h"
#include "include/menuIndexes.h"
#include "include/pages/pageConfiguration.h"
#include "include/pages/pageCostTypes.h"
#include "include/pages/pageExchanges.h"
#include "include/pages/pagePortfolio.h"
#include "include/pages/pageSecurities.h"
#include "include/pages/pageSecurityPrices.h"
#include "include/pages/page_IMM_transaction.h"
#include "include/pages/page_IMM_customerTransaction.h"

namespace pluginInterface
{
  /// @brief      Code to initialise the plugin. Called by the OS when the plugin is loaded. (No parameters)
  /// @version    2023-07-23/GGB - Function created.

  void initialisePlugin()
  {
    using namespace database::tbl_core_menuItems;

    menuItemVector.emplace_back(MENU_IMM, MENU_PARENT, MODULE_IMM_ORDER,
                                "Investment Management", "", OT_NONE, BT_ALL,
                                nullptr);
    menuItemVector.emplace_back(MENU_IMM_CLIENTTRANSACTION, MENU_IMM, 0,
                                "Transaction Entry", "", OT_IMM_CUSTOMERTRANSACTION, BT_ALL,
                                &transactionPages::CPageIMMClientTransaction::createClass);
    menuItemVector.emplace_back(MENU_IMM_TRANSACTION, MENU_IMM, 1,
                                "Transaction Entry", "", OT_IMM_TRANSACTION, BT_ALL,
                                &transactionPages::CPageIMMTransaction::createClass);
    menuItemVector.emplace_back(MENU_IMM_PRICES, MENU_IMM, 2,
                                "Price entry", "", OT_IMM_SECURITYPRICES, BT_ALL,
                                &transactionPages::CPageSecurityPrices::createClass);

    menuItemVector.emplace_back(MENU_IMM_MD, MENU_IMM, 9,
                                "Master Data", "", OT_NONE, BT_ALL,
                                nullptr);
    menuItemVector.emplace_back(MENU_IMM_MD_EXCHANGES, MENU_IMM_MD, 0,
                                "Security Exchanges", "", OT_IMM_EXCHANGES, BT_ALL,
                                &transactionPages::CPageExchanges::createClass);
    menuItemVector.emplace_back(MENU_IMM_MD_SECURITIES, MENU_IMM_MD, 1,
                                "Securities", "", OT_IMM_SECURITIES, BT_ALL,
                                &transactionPages::CPageSecurities::createClass);
    menuItemVector.emplace_back(MENU_IMM_PORTFOLIO, MENU_IMM_MD, 2,
                                "Portfolio Management", "Manage Customer Portfolios", OT_IMM_PORTFOLIO, BT_ALL,
                                &transactionPages::CPagePortfolio::createClass);
    menuItemVector.emplace_back(MENU_IMM_MD_COSTTYPES, MENU_IMM_MD, 3,
                                "Cost Types", "Manage Cost Types", OT_IMM_COSTTYPES, BT_ALL,
                                &transactionPages::CPageCostTypes::createClass);

    menuItemVector.emplace_back(MENU_IMM_CD, MENU_IMM, 10,
                                "Configuration Data", "", OT_IMM_CONFIGURATION, BT_ALL,
                                &transactionPages::CPageConfiguration::createClass);

  }

  void destroyPlugin()
  {
  }

} // namespace
