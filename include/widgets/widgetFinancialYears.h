#ifndef WIDGETFINANCIALYEARS_H
#define WIDGETFINANCIALYEARS_H

  // Standard C++ library header files

#include <memory>

  // Wt++ framework header files

#include <Wt/WContainerWidget.h>

  // Miscellaneous library header files.


  // msmERP header files

#include "include/application.h"
#include "include/core/typeDefinitions.h"
#include "include/database/models/modelFinancialYears.h"

namespace widgets
{
  class CWidgetFinancialYears : public Wt::WContainerWidget
  {
  private:
    CWidgetFinancialYears() = delete;
    CWidgetFinancialYears(CWidgetFinancialYears const &) = delete;
    CWidgetFinancialYears operator=(CWidgetFinancialYears const &) = delete;

    CApplication &application_;

    Wt::WTableView *tableViewFinancialYears;

    std::shared_ptr<models::CModelFinancialYears> modelFinancialYears;

    Wt::Signal<index_t> selectionChanged_;

    void setupUI();

  public:
    CWidgetFinancialYears(CApplication &);

    // Signals

    Wt::Signal<index_t> &selectionChanged() { return selectionChanged_; }

  };

} // namespace

#endif // WIDGETFINANCIALYEARS_H
