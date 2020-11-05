#ifndef GEO_IMAGE_GPS_BBOX_ARG_H
#define GEO_IMAGE_GPS_BBOX_ARG_H

#include "arg/arg.h"
#include "arg/factory.h"

struct GpsBbox
{
    double top, left, bottom, right;
    GpsBbox(): top(0.0),left(0.0),bottom(0.0),right(0.0)
    {}
};

class GpsBboxArg : public Arg
{
public:
    GpsBboxArg(const std::string& key,
             const std::vector<std::string>& args,
             GpsBbox& value):
        Arg(key, 4, args),
        m_value(value)
    {}

public:
    virtual bool parse() final
    {
        std::vector<std::string> val_args;
        if (!extract_value_args(val_args))
            return false;
        if (val_args.size() != 4)
            return false;

        for (const std::string& val_arg: val_args)
        {
            std::vector<std::string> gps = split_string(val_arg, "=");
            std::string key = gps[0];
            double      val = std::stod(gps[1]);;
            if (key == "top")
                m_value.top = val;

            if (key == "left")
                m_value.left = val;

            if (key == "bottom")
                m_value.bottom = val;

            if (key == "right")
                m_value.right = val;
        }

        return true;
    }

private:
    /**
    * Split string on delim.
    *
    * @param The string to be split.
    * @param The separator characters.
    * @returns Vector with the parts of the string split up. Empty strings will not remove from result.
    */
    static std::vector<std::string> split_string(const std::string& src_str, const char* delim)
    {
        std::vector<std::string> tokens;
        if (src_str.empty() || nullptr == delim)
            return tokens;

        size_t delim_len = strlen(delim);
        std::string::size_type pos = 0;
        while(pos < src_str.size())
        {
            std::string::size_type next_pos = src_str.find(delim, pos);
            if(std::string::npos == next_pos)
                next_pos = src_str.size();

            if(pos < next_pos)
                tokens.push_back(src_str.substr(pos, next_pos - pos));

            if(pos == next_pos)
                tokens.push_back("");

            pos = next_pos + delim_len;
        }

        return tokens;
    }


private:
    GpsBbox& m_value;
};


template<typename Factory = ArgFactory>
inline std::shared_ptr<Arg> gpsbbox_arg_create(
        const std::string& key,
        const std::vector<std::string>& args,
        GpsBbox& value)
{
    return Factory::template create<GpsBboxArg>(key, args, value);
}




#endif //GEO_IMAGE_GPS_BBOX_ARG_H
