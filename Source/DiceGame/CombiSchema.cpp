#include "CombiSchema.h"

CombiSchema::CombiSchema()
  : quantity(0)
{
    schema = new int[6];
    for (size_t i = 0; i < 6; i++) {
        schema[i] = 0;
    }
}

CombiSchema::CombiSchema(int* combination)
{
    int _quantity = 0;

    schema = new int[6];
    for (size_t i = 0; i < 6; i++) {
        schema[i] = combination[i];
        _quantity += schema[i];
    }

    quantity = _quantity;
}

CombiSchema::CombiSchema(const char* combination)
{
    int _quantity = 0;

    schema = new int[6];
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

CombiSchema
CombiSchema::operator-(const CombiSchema& _combiSchema)
{
    int rstCombination[6];
    for (size_t i = 0; i < 6; i++) {
        rstCombination[i] = schema[i] - _combiSchema.getSchema()[i];
        if (rstCombination[i] < 0) {
            throw std::logic_error("Unable to perform subtraction, there was "
                                   "an unexpected negative value.");
        }
    }

    return CombiSchema(rstCombination);
}

bool
CombiSchema::operator<(const CombiSchema& _combiSchema) const
{
    return schema[0] < _combiSchema.schema[0] &&
           schema[1] < _combiSchema.schema[1] &&
           schema[2] < _combiSchema.schema[2] &&
           schema[3] < _combiSchema.schema[3] &&
           schema[4] < _combiSchema.schema[4] &&
           schema[5] < _combiSchema.schema[5];
}

int*
CombiSchema::getSchema() const
{
    return schema;
}

std::string
CombiSchema::printSchema()
{
    int _schema = 0;
    for (size_t i = 0, d = 100000; i < 6; i++) {
        _schema += d * schema[i];
        d /= 10;
    }

    return std::to_string(_schema);
}