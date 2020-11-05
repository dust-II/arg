#ifndef GEO_IMAGE_INT_ARG_H
#define GEO_IMAGE_INT_ARG_H

#include "arg/arg.h"
#include "arg/factory.h"

class Int32Arg : public Arg
{
public:
    Int32Arg(const std::string& key,
             const std::vector<std::string>& args,
             int32_t& value):
        Arg(key, 1, args),
        m_value(value)
    {}

public:
    virtual bool parse() final
    {
        std::vector<std::string> val_args;
        if (!extract_value_args(val_args))
            return false;
        if (val_args.empty())
            return false;

        m_value = std::stoi(val_args[0]);
        return true;
    }

private:
    int32_t& m_value;
};


template<typename Factory = ArgFactory>
inline std::shared_ptr<Arg> int_arg_create(
        const std::string& key,
        const std::vector<std::string>& args,
        int32_t& value)
{
    return Factory::template create<Int32Arg>(key, args, value);
}




#endif //GEO_IMAGE_INT_ARG_H
