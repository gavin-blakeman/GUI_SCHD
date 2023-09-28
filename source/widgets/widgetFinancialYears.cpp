#include "include/widgets/widgetFinancialYears.h"

  // Standard C++ library header files.


  // Wt++ framework header files.

#include <Wt/WTableView.h>

  // msmERP header files


namespace  widgets
{
  /// @brief Constructor for the class.
  /// @param[in] a: The Application that owns this object. (Needed for session)
  /// @throws
  /// @version 2019-11-18/GGB - Function created.

  CWidgetFinancialYears::CWidgetFinancialYears(CApplication &a) : Wt::WContainerWidget(), application_(a)
  {
    modelFinancialYears = std::make_shared<models::CModelFinancialYears>(a, models::CModelFinancialYears::MU_TABLE_NO_EDIT);
    modelFinancialYears->reload();

    setupUI();
  }

  /// @brief Sets up the user interface.
  /// @throws
  /// @version 2023-03-20/GGB - Function created.

  void CWidgetFinancialYears::setupUI()
  {
    setMaximumSize(Wt::WLength::Auto, Wt::WLength::Auto);

    tableViewFinancialYears = addWidget(std::make_unique<Wt::WTableView>());
    tableViewFinancialYears->setModel(modelFinancialYears);
    tableViewFinancialYears->setSelectable(true);
    tableViewFinancialYears->setAlternatingRowColors(true);
    tableViewFinancialYears->setSelectionBehavior(Wt::SelectionBehavior::Rows);
    tableViewFinancialYears->setSelectionMode(Wt::SelectionMode::Single);
    tableViewFinancialYears->selectionChanged().connect([this]
    {
      index_t ID = modelFinancialYears->index2ID(tableViewFinancialYears->selectedIndexes().begin()->row());
      selectionChanged_.emit(ID);
    });
  }
}
