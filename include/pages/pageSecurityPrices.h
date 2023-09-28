//**********************************************************************************************************************************
//
// PROJECT:             msmERP
// SUBSYSTEM:           GUI: Investment Management
// FILE:                pageSecurityPrices.h
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
// HISTORY:             2023-07-27/GGB - File Created
//
//**********************************************************************************************************************************

#ifndef PAGE_SECURITYPRICES_H
#define PAGE_SECURITYPRICES_H

  // Standard C++ library header files

#include <memory>

  // Wt framework header files.

#include <Wt/WComboBox.h>
#include <Wt/WFileDropWidget.h>
#include <Wt/WFileUpload.h>
#include <Wt/WLineEdit.h>

  // Miscellaneous library header files

  // msmERP header files.

#include "include/core/typeDefinitions.h"
#include "include/pages/pageTransaction.h"
#include "include/database/models/modelExchanges.h"
#include "include/database/models/modelSecurities.h"
#include "include/extendedComboBox.h"
#include "include/extendedPushButton.h"

namespace transactionPages
{

  class CPageSecurityPrices: public CPageTransaction
  {
  public:
    CPageSecurityPrices(CApplication &, std::unique_ptr<parameters_t>);

    static std::unique_ptr<CPageSecurityPrices> createClass(CApplication &parent, std::unique_ptr<parameters_t> p)
    {
      return std::make_unique<CPageSecurityPrices>(parent, std::move(p));
    }
  protected:
    void accountChanged(index_t);

  private:
    struct tableRow_t
    {
      index_t exchangeID_ = 0;
      std::size_t transactionLineIndex;
      extendedPushButton *pushButtonDelete = nullptr;
      Wt::WLineEdit *lineEditFilename = nullptr;
      Wt::WLineEdit *lineEditFileType = nullptr;
      extendedComboBox *comboBoxExchange = nullptr;
      extendedComboBox *comboBoxSecurity = nullptr;
      extendedPushButton *pushButtonUpload = nullptr;
      std::shared_ptr<models::CModelExchanges> modelExchanges;
      std::shared_ptr<models::CModelSecurities> modelSecurities;
      Wt::WFileDropWidget::File *file = nullptr;
    };
    using tableStore_t = std::vector<tableRow_t>;

    tableStore_t tableStore;

    Wt::WFileUpload *fileUpload = nullptr;
    Wt::WFileDropWidget *fileDropWidget = nullptr;
    Wt::WTable *tableLines = nullptr;

    std::shared_ptr<models::CModelExchanges> modelExchanges;
    std::shared_ptr<models::CModelSecurities> modelSecurities;

    CPageSecurityPrices() = delete;
    CPageSecurityPrices(CPageSecurityPrices const &) = delete;
    CPageSecurityPrices operator=(CPageSecurityPrices const &) = delete;

    virtual void createUI() override;
    virtual constexpr objectType_t objectTypeID() const { return 20; }
    virtual bool allowEdit() const override {};
    virtual void enableEdit(bool) override {};
    virtual void processSaveData() override {};
    virtual void clearFields() override {};
    virtual void populateFields() override {};
    virtual void processFind() override {}
    virtual void processModeFind() override {};
    virtual void processModeEdit() override {};
    virtual void processModeCreate() override {};
    virtual void processModeSearch() override {};
    virtual void processModeRecordChange() override {};

    void createLine(Wt::WFileDropWidget::File *);
    void deleteLine(std::size_t);
    void enableUploadButton(std::size_t);

    void pushButtonUploadClicked(std::size_t);
    //void comboBoxTypeChanged(std::size_t);
  };

} // namespace transactions

#endif // PAGE_SECURITYPRICES_H
