//**********************************************************************************************************************************
//
// PROJECT:             msmERP
// FILE:                financialMonth.h
// SUBSYSTEM:           Financial Year transaction page
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
// OVERVIEW:						Implement the transaction page for financial year management.
//
// HISTORY:             2023-07-20/GGB - File created.
//
//**********************************************************************************************************************************

#include "include/pages/pageSecurities.h"

  // Standard C++ library header files

#include <utility>

  // Wt framework header files.

#include <Wt/WContainerWidget.h>
#include <Wt/WLengthValidator.h>
#include <Wt/WTemplate.h>

  // msmERP header files

#include "include/application.h"
#include "include/database/views/viewSecurity.h"
#include "include/pages/GUI_Templates.h"

namespace transactionPages
{

  /// @brief      Constructor for the class.
  /// @param[in]  a: The application object.
  /// @param[in]  p: The parameters being passed in.
  /// @version    2019-11-08/GGB - Function created.

  CPageSecurities::CPageSecurities(CApplication &a, std::unique_ptr<parameters_t> p)
    : CPageTransactionView(a, std::move(p))
  {
    record_ = std::make_unique<views::CViewSecurity>(a);

    modelExchanges = std::make_shared<models::CModelExchanges>(a, models::CModelExchanges::MU_COMBO_NULL);
    modelExchanges->reload();

    modelCurrency = std::make_shared<models::CModelCurrency>(a, models::CModelCurrency::MU_COMBO);
    modelCurrency->reload();
  }

  /// @brief Creates the UI for the business unit view transaction.
  /// @version 2019-11-08/GGB - Function created.

  void CPageSecurities::createUI()
  {
    try
    {
      auto result = container()->addWidget(std::make_unique<Wt::WTemplate>(templateSecurities));
      result->addFunction("id", &Wt::WTemplate::Functions::id);

      widgetSecurities = result->bindWidget("widgetSecurities", std::make_unique<widgets::CWidgetSecurities>(application(),
                                                                                                            exchangeID_));
      widgetSecurities->selectionChanged().connect([this](index_t sid)
      {
        recordChangeID = sid;
        internalMode = BT_RECORDCHANGE;
        checkSave();
      });

      lineEditStatus = result->bindWidget("lineEditStatus", std::make_unique<Wt::WLineEdit>());
      auto btn = result->bindWidget("buttonStatus", std::make_unique<Wt::WPushButton>("Action"));
      createStatusButton(btn);
      lineEditStatus->setEnabled(false);

      {
        lineEditShortText= result->bindWidget("lineEditShortText", std::make_unique<Wt::WLineEdit>());
        lineEditShortText->changed().connect([this]
        {
          switch(internalMode)
          {
            case BT_CREATE:
            case BT_UPDATE:
            {
              dirty();
              dynamic_cast<views::CViewSecurity*>(record_.get())->shortText(lineEditShortText->text().toUTF8());
              break;
            }
            default:
            {
              CODE_ERROR();
              break;
            }
          };
        });
        auto validator = std::make_shared<Wt::WLengthValidator>(3, 100);
        lineEditShortText->setValidator(validator);
      }

      comboBoxExchange = result->bindWidget("comboBoxExchange", std::make_unique<Wt::WComboBox>());
      comboBoxExchange->setModel(modelExchanges);
      comboBoxExchange->activated().connect([this](int currentIndex)
      {
        dynamic_cast<views::CViewSecurity *>(record_.get())->exchangeID(modelExchanges->index2ID(currentIndex));
        dirty();
      });

      comboBoxCurrency = result->bindWidget("comboBoxCurrency", std::make_unique<Wt::WComboBox>());
      comboBoxCurrency->setModel(modelCurrency);
      comboBoxCurrency->activated().connect([this](int currentIndex)
      {
        dynamic_cast<views::CViewSecurity *>(record_.get())->currencyID(modelCurrency->index2ID(currentIndex));
        dirty();
      });

      {
        lineEditCode = result->bindWidget("lineEditCode", std::make_unique<Wt::WLineEdit>());
        lineEditCode->changed().connect([this]
        {
          dynamic_cast<views::CViewSecurity *>(record_.get())->code(lineEditCode->text().toUTF8());
          dirty();
        });
        auto validator = std::make_shared<Wt::WLengthValidator>(3, 6);
        lineEditCode->setValidator(validator);
      };

      lineEditLongText = result->bindWidget("lineEditLongText", std::make_unique<Wt::WLineEdit>());
      lineEditLongText->changed().connect([this]
      {
        dynamic_cast<views::CViewSecurity *>(record_.get())->longText(lineEditLongText->text().toUTF8());
        dirty();
      });

      comboBoxSecurityType = result->bindWidget("comboBoxSecurityType", std::make_unique<Wt::WComboBox>());

    }
    catch (std::exception &e)
    {
      std::cerr << "exception: " << e.what() << std::endl;
    }

    enableEdit(false);
  }

  /// @brief      Sets the enables state of the widgets.
  /// @throws
  /// @version    2023-07-22/GGB - Function created.

  void CPageSecurities::enableEdit(bool enable)
  {
    comboBoxExchange->setEnabled(enable);
    lineEditShortText->setEnabled(enable);
    lineEditCode->setEnabled(enable);
    comboBoxCurrency->setEnabled(enable);
    lineEditLongText->setEnabled(enable);
    comboBoxSecurityType->setEnabled(enable);
  }


  /// @brief      Clear all the fields.
  /// @throws
  /// @version    2023-07-22/GGB - Function created.

  void CPageSecurities::clearFields()
  {
    record_->clearData();
    comboBoxExchange->setCurrentIndex(0);
    lineEditShortText->setText("");
    lineEditCode->setText("");
    comboBoxCurrency->setCurrentIndex(0);
    lineEditLongText->setText("");

    updateStatus();
  }

  void CPageSecurities::processModeRecordChange()
  {
    record_->ID(recordChangeID);
    record_->loadData();
  }

  void CPageSecurities::populateFields()
  {
    lineEditShortText->setText(dynamic_cast<views::CViewSecurity *>(record_.get())->shortText());
    lineEditCode->setText(dynamic_cast<views::CViewSecurity  *>(record_.get())->code());
    lineEditLongText->setText(dynamic_cast<views::CViewSecurity  *>(record_.get())->longText());
    comboBoxExchange->setCurrentIndex(modelExchanges->ID2Index(dynamic_cast<views::CViewSecurity  *>(record_.get())->exchangeID()));
    comboBoxCurrency->setCurrentIndex(modelCurrency->ID2Index(dynamic_cast<views::CViewSecurity  *>(record_.get())->currencyID()));

    updateStatus();
  }

  void CPageSecurities::saveComplete()
  {
    widgetSecurities->refresh();
    CPageTransactionView::saveComplete();
  }

} // namespace transactions
