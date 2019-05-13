#include "combiSchema.h"

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

CombiSchema
CombiSchema::operator-(const CombiSchema& _combiSchema)
{
    int rstSchema[6];
    for (size_t i = 0; i < 6; i++) {
        rstSchema[i] = schema[i] - _combiSchema.getSchema()[i];
        if (rstSchema[i] < 0) {
            throw std::logic_error("Unable to perform subtraction, there was "
                                   "an unexpected negative value.");
        }
    }

    return CombiSchema(rstSchema);
}

bool
CombiSchema::operator==(const CombiSchema& _combiSchema)
{
    bool flag = true;
    for (size_t i = 0; i < 6; i++) {
        if (schema[i] != _combiSchema.getSchema()[i]) {
            flag = false;
        }
	}
    return flag;
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
