//**********************************************************************************************************************************
//
// PROJECT:             msmERP
// FILE:                pageExchanges
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
// HISTORY:             2023-07-25/GGB - File Created
//
//**********************************************************************************************************************************

#include "include/pages/pageExchanges.h"

  // Wt framework header files.

#include <Wt/WComboBox.h>
#include <Wt/WGridLayout.h>
#include <Wt/WLineEdit.h>
#include <Wt/WMessageBox.h>
#include <Wt/WTemplate.h>
#include <Wt/WTableView.h>

  // msmERP header files

#include "include/pages/GUI_Templates.h"
#include "include/database/tables/tbl_imm_exchanges.h"
#include "include/database/views/viewExchange.h"

namespace transactionPages
{

  /// @brief      Class constructor.
  /// @param[in]  a: The application that owns this instance.
  /// @param[in]  p: The Parametrs passed to the function on creation.
  /// @throws
  /// @version    2023-07-23/GGB - Function created.

  CPageExchanges::CPageExchanges(CApplication &a, std::unique_ptr<parameters_t> p) : CPageTransactionView(a, std::move(p))
  {
    record_ = std::make_unique<views::CViewExchange>(a);

    modelCountry= std::make_shared<models::CModelCountry>(a, models::CModelCountry::MU_COMBO);
    modelCountry->reload();
  }

  /// @brief      Clears all the fields.
  /// @throws     None.
  /// @version    2023-07-23/GGB - Function created.

  void CPageExchanges::clearFields() noexcept
  {
    lineEditShortText->setText("");
    lineEditLongText->setText("");
    lineEditSuffix->setText("");
    comboBoxCountry->setCurrentIndex(0);
  }

  /// @brief    Creates the UI for account creation/managment
  /// @throws
  /// @version  2023-03-27/GGB - Function created.

  void CPageExchanges::createUI()
  {
    auto result = container()->addWidget(std::make_unique<Wt::WTemplate>(templateExchanges));
    result->addFunction("id", &Wt::WTemplate::Functions::id);

    lineEditShortText= result->bindWidget("lineEditShortText", std::make_unique<Wt::WLineEdit>());
    lineEditShortText->changed().connect([this]
    {
      switch(internalMode)
      {
        case BT_UPDATE:
        {
          dirty();
          dynamic_cast<views::CViewExchange *>(record_.get())->shortText(lineEditShortText->text().toUTF8());
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

    auto btn = result->bindWidget("buttonAction", std::make_unique<Wt::WPushButton>("Action"));
    {
      auto popup = std::make_unique<Wt::WPopupMenu>();
      popup->addItem("Find");
      popup->addItem("Search");
      auto pp = popup.get();
      btn->setMenu(std::move(popup));
      btn->setStyleClass("btn-outline-primary");
      btn->setAttributeValue("type", "button");
      pp->itemSelected().connect([this](Wt::WMenuItem *item)
      {
        previousMode = internalMode;
        if (item->text() == "Find")
        {
          internalMode = BT_FIND;
          enableEdit(false);
          clearFields();
          lineEditShortText->setEnabled(true);
          lineEditShortText->setFocus(true);
          dirty(false);
        }
        else if (item->text() == "Search")
        {
          internalMode = BT_SEARCH;
        }
        else
        {
          CODE_ERROR();
        };
        checkSave();
      });
    }

    lineEditStatus = result->bindWidget("lineEditStatus", std::make_unique<Wt::WLineEdit>());
    btn = result->bindWidget("buttonStatus", std::make_unique<Wt::WPushButton>("Action"));
    createStatusButton(btn);
    lineEditStatus->setEnabled(false);

    lineEditLongText = result->bindWidget("lineEditLongText", std::make_unique<Wt::WLineEdit>());
    lineEditLongText->changed().connect([this]
    {
      dynamic_cast<views::CViewExchange *>(record_.get())->longText(lineEditLongText->text().toUTF8());
      dirty();
    });


    comboBoxCountry = result->bindWidget("comboBoxCountry", std::make_unique<Wt::WComboBox>());
    comboBoxCountry->setModel(modelCountry);
    comboBoxCountry->activated().connect([this](int currentIndex)
    {
      dynamic_cast<views::CViewExchange *>(record_.get())->country(modelCountry->index2ID(currentIndex));
      dirty();
    });

    lineEditSuffix = result->bindWidget("lineEditSuffix", std::make_unique<Wt::WLineEdit>());
    lineEditSuffix->changed().connect([this]
    {
      dynamic_cast<views::CViewExchange *>(record_.get())->suffix(lineEditSuffix->text().toUTF8());
      dirty();
    });

    updateTransactions();
    enableEdit(false);
  }

  /// @brief Enables/Disables the controls as required.
  /// @param[in] enable: The required state of the controls.
  /// @throws
  /// @version 2023-03-28/GGB - Function created.

  void CPageExchanges::enableEdit(bool enable)
  {
    lineEditShortText->setEnabled(enable);
    lineEditLongText->setEnabled(enable);
    lineEditSuffix->setEnabled(enable);
    comboBoxCountry->setEnabled(enable);
  }

  /// @brief populate the fields as required.
  /// @throws
  /// @version 2023-03-29/GGB - Function created.

  void CPageExchanges::populateFields()
  {
    lineEditShortText->setText(dynamic_cast<views::CViewExchange *>(record_.get())->shortText());
    lineEditLongText->setText(dynamic_cast<views::CViewExchange *>(record_.get())->longText());
    lineEditSuffix->setText(dynamic_cast<views::CViewExchange *>(record_.get())->suffix());

    lineEditStatus->setText(record_->statusText());

    try
    {
      comboBoxCountry->setCurrentIndex(modelCountry->ID2Index(dynamic_cast<views::CViewExchange *>(record_.get())->country()));
    }
    catch(...)
    {
        // Auto fix errors.

      comboBoxCountry->setCurrentIndex(0);
      dynamic_cast<views::CViewExchange *>(record_.get())->country(0);
      dirty();
    }
    updateTransactions();
  }

  /// @brief      Processes the record identified in the FIND command.
  /// @throws
  /// @version    2023-07-23/GGB - Function created.

  void CPageExchanges::processFind()
  {
    using namespace database;

    std::string tempST = lineEditShortText->text().toUTF8();
    bool recordExists =  tbl_imm_exchanges::recordExists(application(), tempST);

    if (recordExists)
    {
      record_->ID(tbl_imm_exchanges::recordID(application(), tempST));
      record_->loadData();

      populateFields();
      lineEditShortText->setEnabled(false);
      dirty(false);
      internalMode = BT_NONE;
    }
    else if (!recordExists)
    {
      Wt::WMessageBox::show("Exchange does not exist!",
                            "The specified record does not exist.",
                            Wt::StandardButton::Ok);

    }
  }

}
