#pragma once
#include "stdafx.h"

#include <array>

class CombiSchema
{
  private:
    std::array<int, 6> schema;
    int quantity;

  public:
    CombiSchema();
    CombiSchema(int* combination);
    CombiSchema(const char* combination);
    ~CombiSchema();

    bool contain(const CombiSchema& _combiSchema);

    // CombiSchema operator-(const CombiSchema& _combiSchema);
    bool operator<(const CombiSchema& _combiSchema) const;

    std::array<int, 6> getSchema() const;
    int printSchema();
};
