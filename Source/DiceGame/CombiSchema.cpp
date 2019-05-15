#include "CombiSchema.h"

CombiSchema::CombiSchema()
  : quantity(0)
{
    schema = { 0, 0, 0, 0, 0, 0 };
}

CombiSchema::CombiSchema(int* combination)
{
    int _quantity = 0;
    schema = { 0, 0, 0, 0, 0, 0 };
    for (size_t i = 0; i < 6; i++) {
        schema[i] = combination[i];
        _quantity += schema[i];
    }

    quantity = _quantity;
}

CombiSchema::CombiSchema(const char* combination)
{
    int _quantity = 0;
    schema = { 0, 0, 0, 0, 0, 0 };
    for (size_t i = 0; i < 6; i++) {
        schema[i] = combination[i] - '0';
        _quantity += schema[i];
    }

    quantity = _quantity;
}

CombiSchema::~CombiSchema() {}

bool
CombiSchema::contain(const CombiSchema& _combiSchema)
{
    bool rst = true;

    for (size_t i = 0; i < 6; i++) {
        if (schema[i] < _combiSchema.getSchema()[i]) {
            rst = false;
        }
    }

    return rst;
}

bool
CombiSchema::operator<(const CombiSchema& _combiSchema) const
{
    int schema_lh = 0, schema_rh = 0;
    for (size_t i = 0, d = 100000; i < 6; i++) {
        schema_lh += d * schema[i];
        schema_rh += d * _combiSchema.schema[i];
        d /= 10;
    }

    return schema_lh < schema_rh;
}

std::array<int, 6>
CombiSchema::getSchema() const
{
    return schema;
}

int
CombiSchema::printSchema()
{
    int _schema = 0;
    for (size_t i = 0, d = 100000; i < 6; i++) {
        _schema += d * schema[i];
        d /= 10;
    }

    return _schema;
}