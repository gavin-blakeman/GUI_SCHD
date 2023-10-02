//**********************************************************************************************************************************
//
// PROJECT:             msmERP
// SUBSYSTEM:           GUI: Scheduler
// FILE:                gui_SCHD.cpp
// LANGUAGE:						C++
// TARGET OS:           LINUX
// LIBRARY DEPENDANCE:	None.
// NAMESPACE:           database
// AUTHOR:							Gavin Blakeman.
// LICENSE:             GPLv2
//
//                      Copyright 2023 Gavin Blakeman.
//                      This file is part of the msmERP Project
//
//                      msmERP is free software: you can redistribute it and/or modify it under the terms of the GNU
//                      General Public License as published by the Free Software Foundation, either version 2 of the License, or (at
//                      your option) any later version.
//
//                      msmERP is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
//                      even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
//                      Public License for more details.
//
//                      You should have received a copy of the GNU General Public License along with msmERP.  If not,
//                      see <http://www.gnu.org/licenses/>.
//
// OVERVIEW:
//
// HISTORY:             2023-07-28/GGB - File created
//
//**********************************************************************************************************************************

#include "include/pluginInterface/interfaceUserTransaction.h"

  // msmERP header files

#include "include/database/tables/core/tbl_businessTransactions.h"
#include "include/database/tables/core/tbl_menuItems.h"
#include "include/database/tables/core/tbl_objectTypes.h"
#include "include/menuIndexes.h"

namespace pluginInterface
{
  /// @brief      Code to initialise the plugin. Called by the OS when the plugin is loaded. (No parameters)
  /// @version    2023-07-23/GGB - Function created.

  void initialisePlugin()
  {
    using namespace database::tbl_core_menuItems;

//    menuItemVector.emplace_back(MENU_IMM, MENU_PARENT, MODULE_IMM_ORDER,
//                                "Investment Management", "", OT_NONE, BT_ALL,
//                                nullptr);
//    menuItemVector.emplace_back(MENU_IMM_CLIENTTRANSACTION, MENU_IMM, 0,
//                                "Transaction Entry", "", OT_IMM_CUSTOMERTRANSACTION, BT_ALL,
//                                &transactionPages::CPageIMMClientTransaction::createClass);
//    menuItemVector.emplace_back(MENU_IMM_TRANSACTION, MENU_IMM, 1,
//                                "Transaction Entry", "", OT_IMM_TRANSACTION, BT_ALL,
//                                &transactionPages::CPageIMMTransaction::createClass);
//    menuItemVector.emplace_back(MENU_IMM_PRICES, MENU_IMM, 2,
//                                "Price entry", "", OT_IMM_SECURITYPRICES, BT_ALL,
//                                &transactionPages::CPageSecurityPrices::createClass);

//    menuItemVector.emplace_back(MENU_IMM_MD, MENU_IMM, 9,
//                                "Master Data", "", OT_NONE, BT_ALL,
//                                nullptr);
//    menuItemVector.emplace_back(MENU_IMM_MD_EXCHANGES, MENU_IMM_MD, 0,
//                                "Security Exchanges", "", OT_IMM_EXCHANGES, BT_ALL,
//                                &transactionPages::CPageExchanges::createClass);
//    menuItemVector.emplace_back(MENU_IMM_MD_SECURITIES, MENU_IMM_MD, 1,
//                                "Securities", "", OT_IMM_SECURITIES, BT_ALL,
//                                &transactionPages::CPageSecurities::createClass);
//    menuItemVector.emplace_back(MENU_IMM_PORTFOLIO, MENU_IMM_MD, 2,
//                                "Portfolio Management", "Manage Customer Portfolios", OT_IMM_PORTFOLIO, BT_ALL,
//                                &transactionPages::CPagePortfolio::createClass);
//    menuItemVector.emplace_back(MENU_IMM_MD_COSTTYPES, MENU_IMM_MD, 3,
//                                "Cost Types", "Manage Cost Types", OT_IMM_COSTTYPES, BT_ALL,
//                                &transactionPages::CPageCostTypes::createClass);

//    menuItemVector.emplace_back(MENU_IMM_CD, MENU_IMM, 10,
//                                "Configuration Data", "", OT_IMM_CONFIGURATION, BT_ALL,
//                                &transactionPages::CPageConfiguration::createClass);

  }

  void destroyPlugin()
  {
  }

} // namespace
