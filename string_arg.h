#ifndef GEO_IMAGE_STRING_ARG_H
#define GEO_IMAGE_STRING_ARG_H

#include "arg/arg.h"
#include "arg/factory.h"

class StringArg : public Arg
{
public:
    StringArg(const std::string& key,
             const std::vector<std::string>& args,
             std::string& value):
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

        m_value = val_args[0];
        return true;
    }

private:
    std::string& m_value;
};


template<typename Factory = ArgFactory>
inline std::shared_ptr<Arg> string_arg_create(
        const std::string& key,
        const std::vector<std::string>& args,
        std::string& value)
{
    return Factory::template create<StringArg>(key, args, value);
}




#endif //GEO_IMAGE_STRING_ARG_H
