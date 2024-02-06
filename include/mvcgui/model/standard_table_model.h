#pragma once
#include <mvcgui/model/base/abstract_table_model.h>

namespace mvcgui {
class StandardTableModel : public AbstractTableModel
{
public:
	InsertedItems InsertRows(size_t row, size_t count) override;
	void RemoveRows(size_t row, size_t count) override;
	void set_row_count(size_t count) override;
	size_t row_count() const override;

	InsertedItems InsertColumns(size_t col, size_t count) override;
	void RemoveColumns(size_t col, size_t count) override;
	void set_column_count(size_t count) override;
	size_t column_count() const override;

	void Clear() override;

	void set_item_data(const ModelIndex& idx, ModelItemData&& data) override;
	const ModelItemData& item_data(const ModelIndex& idx) const override;

	const TableHorizontalHeaderData& hori_header_data(size_t column) override;
	void set_hori_header_data(TableHorizontalHeaderData&& data) override;

private:
	std::vector<TableHorizontalHeaderData> hori_header_datas_;
	std::list<std::vector<ModelItemData>> item_datas_;
};
}