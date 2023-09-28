//**********************************************************************************************************************************
//
// PROJECT:             msmERP
// FILE:                pageIMM_customerTransaction
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
// HISTORY:             2023-08-17/GGB - File Created
//
//**********************************************************************************************************************************

#ifndef PAGE_IMM_CUSTOMERTRANSACTION_H
#define PAGE_IMM_CUSTOMERTRANSACTION_H

  // Standard C++ library header files

#include <memory>
#include <vector>

  // msmERP header files.

#include "include/database/tables/core/tbl_objectTypes.h"
#include "include/database/models/modelComboBox.h"
#include "include/database/models/modelCostElements.h"
#include "include/database/models/modelCostTypes.h"
#include "include/database/models/modelExchanges.h"
#include "include/database/models/modelPortfolio.h"
#include "include/database/models/modelSecurities.h"
#include "include/pages/pageTransactionView.h"
#include "include/widgets/containerChartOfAccounts.h"
#include "include/extendedComboBox.h"
#include "include/extendedPushButton.h"
#include "include/extendedLineEdit.h"
#include "include/extendedDoubleSpinBox.h"
#include "include/database/views/viewTransactionLines.h"

namespace transactionPages
{
  class CPageIMMClientTransaction : public CPageTransactionView
  {
  public:
    CPageIMMClientTransaction(CApplication &, std::unique_ptr<parameters_t>);

    void refreshTableView();

    static std::unique_ptr<CPageIMMClientTransaction> createClass(CApplication &parent, std::unique_ptr<parameters_t> p)
    {
      return std::make_unique<CPageIMMClientTransaction>(parent, std::move(p));
    }

  protected:
    virtual void createUI() override;
    virtual constexpr objectType_t objectTypeID() const override { return OT_IMM_CUSTOMERTRANSACTION; }
    virtual bool allowEdit() const override { return true; }
    virtual void enableEdit(bool) override;
    virtual void processSaveData() override;
    virtual void saveComplete() override;
    virtual void clearFields() override;
    virtual void populateFields() override;
    virtual void processFind() override {}
    virtual void processModeFind() override {};
    virtual void processModeEdit() override {};
    virtual void processModeCreate() override {};
    virtual void processModeSearch() override {};
    virtual void processModeRecordChange() override {};

  private:
    CPageIMMClientTransaction() = delete;
    CPageIMMClientTransaction(CPageIMMClientTransaction const &) = delete;
    CPageIMMClientTransaction &operator=(CPageIMMClientTransaction const &) = delete;

    struct tableRow_t
    {
      views::CViewTransactionLines *transactionLine;
      extendedPushButton *pushButtonDelete;
      extendedComboBox *comboBoxType;
      extendedDoubleSpinBox *spinBoxCost;
      std::shared_ptr<models::CModelCostTypes> modelTypes;
      std::size_t transactionLineIndex;
    };
    using tableStore_t = std::vector<tableRow_t>;

    tableStore_t tableStore;

    Wt::WLineEdit *lineEditTransaction = nullptr;
    Wt::WComboBox *comboBoxPortfolio = nullptr;
    Wt::WComboBox *comboBoxExchange = nullptr;
    Wt::WComboBox *comboBoxSecurity = nullptr;
    Wt::WComboBox *comboBoxTransactionType = nullptr;
    Wt::WDoubleSpinBox *spinBoxQuantity = nullptr;
    Wt::WDoubleSpinBox *spinBoxPrice = nullptr;
    Wt::WLineEdit *lineEditCosts = nullptr;
    Wt::WLineEdit *lineEditTotal = nullptr;
    Wt::WDateEdit *dateEditPosting = nullptr;
    Wt::WLineEdit *lineEditBasePrice = nullptr;

    Wt::WTable *tableCostLine = nullptr;
    Wt::WPushButton *pushButtonRowAdd = nullptr;

    std::shared_ptr<models::CModelComboBox<tindex_t>> modelTransactionType;
    std::shared_ptr<models::CModelPortfolio> modelPortfolio;
    std::shared_ptr<models::CModelExchanges> modelExchanges;
    std::shared_ptr<models::CModelSecurities> modelSecurities;

    index_t exchangeID_ = 0;

    void createLine(bool = false);
    void deleteCostLine(std::size_t);
    void updateCosts();

    void comboBoxTypeChanged(std::size_t);
    void spinBoxValueChanged(std::size_t);

    void updateActions();
  };

} // namespace transactions

#endif // PAGE_IMM_CUSTOMERTRANSACTION_H
