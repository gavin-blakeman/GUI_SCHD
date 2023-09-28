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

#ifndef PAGESECURITIES_H
#define PAGESECURITIES_H

  // Standard C++ library header files

#include <memory>

  // msmERP header files.

#include "include/database/models/core/modelCurrency.h"
#include "include/database/models/modelExchanges.h"
#include "include/database/tables/core/tbl_objectTypes.h"
#include "include/pages/pageTransactionView.h"
#include "include/widgets/widgetSecurities.h"

namespace transactionPages
{
  class CPageSecurities final: public CPageTransactionView
  {
  public:
    CPageSecurities(CApplication &, std::unique_ptr<parameters_t>);

    static std::unique_ptr<CPageTransaction> createClass(CApplication &parent, std::unique_ptr<parameters_t> p)
    {
      return std::make_unique<CPageSecurities>(parent, std::move(p));
    }
  protected:
  private:
    CPageSecurities() = delete;
    CPageSecurities(CPageSecurities const &) = delete;
    CPageSecurities operator=(CPageSecurities const &) = delete;

    std::shared_ptr<models::CModelCurrency> modelCurrency;
    std::shared_ptr<models::CModelExchanges> modelExchanges;

    widgets::CWidgetSecurities *widgetSecurities;

    Wt::WLineEdit *lineEditShortText = nullptr;
    Wt::WComboBox *comboBoxExchange = nullptr;
    Wt::WLineEdit *lineEditCode = nullptr;
    Wt::WComboBox *comboBoxCurrency = nullptr;
    Wt::WLineEdit *lineEditLongText = nullptr;
    Wt::WComboBox *comboBoxSecurityType = nullptr;

    index_t exchangeID_ = 0;
    index_t recordChangeID = 0;

    virtual void createUI() override;
    virtual constexpr objectType_t objectTypeID() const override { return OT_IMM_SECURITIES; }

    virtual void enableEdit(bool) override;
    virtual void clearFields() override;
    virtual void populateFields() override;
    virtual void processFind() override {};
    virtual void processModeFind() override {};
    virtual void processModeSearch() override {};
    virtual void processModeRecordChange() override;
    virtual void saveComplete() override;
  };

} // namespace transactions

#endif // PAGESECURITIES_H
