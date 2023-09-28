//**********************************************************************************************************************************
//
// PROJECT:             msmERP
// FILE:                widgetSecurities
// SUBSYSTEM:           Investment Management GUI Plugin
// LANGUAGE:						C++
// TARGET OS:           LINUX
// LIBRARY DEPENDANCE:	None.
// NAMESPACE:           N/A
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
// HISTORY:             2023-07-23/GGB - File Created
//
//**********************************************************************************************************************************

#include "include/widgets/widgetSecurities.h"

  // Standard C++ library header files.

#include <any>
#include <cstdint>

  // Wt++ framework header files.

#include <Wt/WLabel.h>
#include <Wt/WTableView.h>
#include <Wt/WTemplate.h>

  // msmERP header files

#include "include/pages/GUI_Templates.h"

namespace  widgets
{
  /// @brief      Constructor for the class.
  /// @param[in]  a: The Application that owns this object. (Needed for session)
  /// @throws
  /// @version    2023-07-23/GGB - Function created.

  CWidgetSecurities::CWidgetSecurities(CApplication &a, index_t &eid)
    : Wt::WContainerWidget(), application_(a), exchangeID_(eid)
  {
    modelExchanges= std::make_shared<models::CModelExchanges>(a, models::CModelExchanges::MU_COMBO_NO_NULL);
    modelExchanges->reload();

    modelSecurities = std::make_shared<models::CModelSecurities>(a, models::CModelSecurities::MU_TABLE, exchangeID_);
    modelSecurities->reload();

    setupUI();
    exchangeID_ = modelExchanges->index2ID(comboBoxExchange->currentIndex());
    modelSecurities->reload();
  }

  /// @brief    Sets up the user interface.
  /// @throws
  /// @version  2019-11-18/GGB - Function created.

  void CWidgetSecurities::setupUI()
  {
    setMaximumSize(Wt::WLength::Auto, Wt::WLength::Auto);

    auto result = addWidget(std::make_unique<Wt::WTemplate>(templateWidgetSecurities));

    comboBoxExchange = result->bindWidget("comboBoxExchange", std::make_unique<Wt::WComboBox>());
    comboBoxExchange->setModel(modelExchanges);
    comboBoxExchange->activated().connect([this](int currentIndex)
    {
      exchangeID_ = modelExchanges->index2ID(currentIndex);
      modelSecurities->reload();
    });

    tableViewSecurities = result->bindWidget("tableViewSecurity", std::make_unique<Wt::WTableView>());
    tableViewSecurities->setModel(modelSecurities);
    tableViewSecurities->setAlternatingRowColors(true);
    tableViewSecurities->setSelectable(true);
    tableViewSecurities->setSelectionBehavior(Wt::SelectionBehavior::Rows);
    tableViewSecurities->setSelectionMode(Wt::SelectionMode::Single);
    tableViewSecurities->selectionChanged().connect([this]
    {
      index_t ID = modelSecurities->index2ID(tableViewSecurities->selectedIndexes().begin()->row());
      selectionChanged_.emit(ID);
    });
  }
}
