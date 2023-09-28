//**********************************************************************************************************************************
//
// PROJECT:             msmERP
// FILE:                pageIMM_securityPriceReview
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
// HISTORY:             2023-09-26/GGB - File Created
//
//**********************************************************************************************************************************

#ifndef PAGE_IMM_SECURITYPRICEREVIEW_H
#define PAGE_IMM_SECURITYPRICEREVIEW_H

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
  class CPageSecurityPriceReview final: public CPageTransactionView
  {
  public:
    CPageSecurityPriceReview(CApplication &, std::unique_ptr<parameters_t>);

    static std::unique_ptr<CPageTransaction> createClass(CApplication &parent, std::unique_ptr<parameters_t> p)
    {
      return std::make_unique<CPageSecurityPriceReview>(parent, std::move(p));
    }
  private:
    CPageSecurityPriceReview() = delete;
    CPageSecurityPriceReview(CPageSecurityPriceReview const &) = delete;
    CPageSecurityPriceReview operator=(CPageSecurityPriceReview const &) = delete;

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
    virtual constexpr objectType_t objectTypeID() const override { return OT_IMM_SECURITYPRICES; }

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

#endif // PAGE_IMM_SECURITYPRICEREVIEW_H
