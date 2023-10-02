//**********************************************************************************************************************************
//
// PROJECT:             msmERP
// FILE:                pageConfiguration
// SUBSYSTEM:           Module: Investement Management
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
// HISTORY:             2023-08-29/GGB - File Created
//
//**********************************************************************************************************************************

#include "include/pages/pageJobDetails.h"

  // Wt framework header files.

#include <Wt/WComboBox.h>
#include <Wt/WGridLayout.h>
#include <Wt/WLineEdit.h>
#include <Wt/WMessageBox.h>
#include <Wt/WTemplate.h>
#include <Wt/WTableView.h>

  // msmERP header files

#include "include/pages/GUI_Templates.h"
//#include "include/database/tables/tbl_imm_costTypes.h"
//#include "include/database/views/viewCostType.h"

namespace transactionPages
{

  /// @brief      Class constructor.
  /// @param[in]  a: The application that owns this instance.
  /// @param[in]  p: The Parametrs passed to the function on creation.
  /// @throws
  /// @version    2023-08-08/GGB - Function created.

  CPageConfiguration::CPageConfiguration(CApplication &a, std::unique_ptr<parameters_t> p) : CPageTransactionBase(a, std::move(p))
  {
  }

  /// @brief      Clears all the fields.
  /// @throws     None.
  /// @version    2023-08-08/GGB - Function created.

  void CPageConfiguration::clearFields() noexcept
  {
    lineEditShortText->setText("");
    comboBoxCostElement->setCurrentIndex(0);
  }

  /// @brief    Creates the UI for account creation/managment
  /// @throws
  /// @version  2023-08-08/GGB - Function created.

  void CPageConfiguration::createUI()
  {
    auto result = container()->addWidget(std::make_unique<Wt::WTemplate>(templateCostTypes));
    result->addFunction("id", &Wt::WTemplate::Functions::id);

    lineEditShortText= result->bindWidget("lineEditShortText", std::make_unique<Wt::WLineEdit>());
    lineEditShortText->changed().connect([this]
    {
      switch(internalMode)
      {
        case BT_CREATE:
        case BT_UPDATE:
        {
          break;
        }
        case BT_FIND:
        {
          processFind();
          break;
        }
        default:
        {
          CODE_ERROR();
          break;
        }
      };
    });

//    auto btn = result->bindWidget("buttonAction", std::make_unique<Wt::WPushButton>("Action"));
//    {
////      auto popup = std::make_unique<Wt::WPopupMenu>();
////      popup->addItem("Find");
////      popup->addItem("Search");
////      auto pp = popup.get();
////      btn->setMenu(std::move(popup));
////      btn->setStyleClass("btn-outline-primary");
////      btn->setAttributeValue("type", "button");
////      pp->itemSelected().connect([this](Wt::WMenuItem *item)
////      {
////        previousMode = internalMode;
////        if (item->text() == "Find")
////        {
////          internalMode = BT_FIND;
////          enableEdit(false);
////          clearFields();
////          lineEditShortText->setEnabled(true);
////          lineEditShortText->setFocus(true);
////          dirty(false);
////        }
////        else if (item->text() == "Search")
////        {
////          internalMode = BT_SEARCH;
////        }
////        else
////        {
////          CODE_ERROR();
////        };
////        checkSave();
////      });
//    }

    lineEditStatus = result->bindWidget("lineEditStatus", std::make_unique<Wt::WLineEdit>());
    //btn = result->bindWidget("buttonStatus", std::make_unique<Wt::WPushButton>("Action"));
//    createStatusButton(btn);
    lineEditStatus->setEnabled(false);

    comboBoxCostElement = result->bindWidget("comboBoxCostElement", std::make_unique<Wt::WComboBox>());
    //comboBoxCostElement->setModel(modelCostElements);
    comboBoxCostElement->activated().connect([this](int currentIndex)
    {
//      dynamic_cast<views::CViewCostType *>(record_.get())->costElement(modelCostElements->index2ID(currentIndex));
//      dirty();
    });

//    updateTransactions();
    enableEdit(false);
  }

  /// @brief      Enables/Disables the controls as required.
  /// @param[in]  enable: The required state of the controls.
  /// @throws
  /// @version    2023-08-08/GGB - Function created.

  void CPageConfiguration::enableEdit(bool enable)
  {
    lineEditShortText->setEnabled(enable);
    comboBoxCostElement->setEnabled(enable);
  }

  /// @brief populate the fields as required.
  /// @throws
  /// @version 2023-03-29/GGB - Function created.

  void CPageConfiguration::populateFields()
  {
  }

}
