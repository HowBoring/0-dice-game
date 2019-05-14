#pragma once
#include "stdafx.h"

class CombiSchema
{
  private:
    int* schema;
    int quantity;

  public:
    CombiSchema();
    CombiSchema(int* combination);
    CombiSchema(const char* combination);
    ~CombiSchema();

	bool contain(const CombiSchema& _combiSchema);

	CombiSchema operator-(const CombiSchema& _combiSchema);
    bool operator<(const CombiSchema& _combiSchema) const;

	int* getSchema() const;

	std::string printSchema();

};
