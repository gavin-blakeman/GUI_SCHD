//**********************************************************************************************************************************
//
// PROJECT:             msmERP
// FILE:
// SUBSYSTEM:
// LANGUAGE:						C++
// TARGET OS:           LINUX
// LIBRARY DEPENDANCE:	None.
// NAMESPACE:           N/A
// AUTHOR:							Gavin Blakeman.
// LICENSE:             GPLv2
//
//                      Copyright 2022 Gavin Blakeman.
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
// HISTORY:             2022-07-31/GGB - File Created
//
//**********************************************************************************************************************************


#include "include/widgets/containerChartOfAccounts.h"

  // Standard C++ library header files.

#include <any>
#include <cstdint>

  // Wt++ framework header files.

#include <Wt/WLabel.h>
#include <Wt/WTreeView.h>

namespace  widgets
{
  /// @brief      Constructor for the class.
  /// @param[in]  parent: The Application that owns this object. (Needed for session)
  /// @throws
  /// @version    2022-05-24/GGB - Function created.

  CContainerChartOfAccounts::CContainerChartOfAccounts(CApplication &parent)
    : Wt::WContainerWidget(), parent_(parent), selectionChanged_()
  {
    modelEditChartOfAccounts = std::make_shared<models::CModelEditChartOfAccounts>(parent_);
    modelEditChartOfAccounts->reload();

    setupUI();
  }

  /// @brief      Function called by the tree view when an account is selected.
  /// @throws
  /// @version    2022-05-24/GGB - Function created.

  void CContainerChartOfAccounts::accountChanged()
  {
    std::any accountID = (*treeViewCOA->selectedIndexes().begin()).data(Wt::ItemDataRole::User);
    if (accountID.has_value())
    {
      try
      {
        selectionChanged_.emit(std::any_cast<index_t>(accountID));
      }
      catch(std::exception &e)
      {
        ERRORMESSAGE(e.what());
      };
    };
  }

  /// @brief      Sets up the user interface.
  /// @throws
  /// @version    2022-05-24/GGB - Function created.

  void CContainerChartOfAccounts::setupUI()
  {
    setLayoutSizeAware(true);
    setOverflow(Wt::Overflow::Scroll);

      // Create the query model for the business combobox and assign the model to the business unit combobox.

    treeViewCOA = addWidget(std::make_unique<Wt::WTreeView>());
    treeViewCOA->setModel(modelEditChartOfAccounts);
    treeViewCOA->setSortingEnabled(false);
    treeViewCOA->addStyleClass("col-sm-12 h-100");
    treeViewCOA->setSelectionMode(Wt::SelectionMode::Single);
    treeViewCOA->setSelectionBehavior(Wt::SelectionBehavior::Rows);
    treeViewCOA->expandToDepth(4);
    treeViewCOA->setSelectable(true);

    treeViewCOA->selectionChanged().connect(this, &widgets::CContainerChartOfAccounts::accountChanged);
  }

  void CContainerChartOfAccounts::updateData()
  {
    DEBUGMESSAGE("Update Data");

//    modelEditChartOfAccounts->loadData();
    treeViewCOA->refresh();
  }
}
