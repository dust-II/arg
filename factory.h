#ifndef GEO_IMAGE_ARG_FACTORY_H
#define GEO_IMAGE_ARG_FACTORY_H

#include <memory>
#include <arg/arg.h>

struct ArgFactory
{
    template<typename Arg_T, typename... ArgArgs>
    static std::shared_ptr<Arg> create(ArgArgs &&... args)
    {
        auto arg = std::make_shared<Arg_T>(std::forward<ArgArgs>(args)...);
        return arg;
    }
};


#endif //GEO_IMAGE_ARG_FACTORY_H
