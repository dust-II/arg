#ifndef GEO_IMAGE_ARG_H
#define GEO_IMAGE_ARG_H

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

class Arg
{
public:
    Arg(const std::string key, size_t value_arg_size, const std::vector<std::string>& args)
        :m_key_arg(key),
         m_value_arg_size(value_arg_size),
         m_args(args)
    {}
    virtual ~Arg() = default;
    virtual bool parse() = 0;

protected:
    bool extract_value_args(std::vector<std::string>& val_args)
    {
       if (m_key_arg.empty() || (0 == m_value_arg_size) || m_args.empty())
       {
           std::cout << "cmd Arg objiec invalid " << std::endl;
           return false;
       }

       std::vector<std::string>::iterator it = std::find(m_args.begin(), m_args.end(), m_key_arg);
       if (it == m_args.end())
       {
           std::cout << "cmd args miss " << m_key_arg.c_str() << std::endl;
           return false;
       }

       for (size_t i = 0; i < m_value_arg_size; ++i)
       {
           if (++it == m_args.end())
           {
               std::cout << "cmd arg size of " << m_key_arg.c_str() << "less than"
                          << std::to_string(m_value_arg_size).c_str() << std::endl;
               return false;
           }

           val_args.push_back(*it);
       }

       return true;
    }

private:
    std::string m_key_arg;
    size_t      m_value_arg_size;
    std::vector<std::string> m_args;
};

#endif //GEO_IMAGE_ARG_H
