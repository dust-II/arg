#include "arg/int_arg.h"
#include "arg/string_arg.h"
#include "arg/gpsbbox_arg.h"


struct Args
{
    std::string region;
    std::string read_json_file;
    std::string write_dir;
    GpsBbox     bounding_bbox;
    int32_t     min_zoom;
    int32_t     max_zoom;
};

/*************************************************
 * --region       na eu sa global
 * --read-json    input json file
 * --write-dir    output directory  XXX/   image + log
 * --bounding-box top=39.972750 left=124.273873 bottom=39.9530776 right=124.3126108
 * --minzoom      min zoom
 * --maxzoom      max zoom
*************************************************/
bool parse_args(int argc, char *argv[], Args& args)
{
    std::vector<std::string> arguments;
    for (int i = 0; i < argc; ++i)
    {
        arguments.push_back(argv[i]);
    }

    bool extract_region  = string_arg_create("--region", arguments, args.region)->parse();
    bool extract_json    = string_arg_create("--read-json", arguments, args.read_json_file)->parse();
    bool extract_dir     = string_arg_create("--write-dir", arguments, args.write_dir)->parse();
    bool extract_bouding = gpsbbox_arg_create("--bounding-box", arguments, args.bounding_bbox)->parse();
    bool extract_minzoom = int_arg_create("--minzoom", arguments, args.min_zoom)->parse();
    bool extract_maxzoom = int_arg_create("--maxzoom", arguments, args.max_zoom)->parse();

    if (extract_region &&
        extract_json &&
        extract_dir &&
        extract_bouding &&
        extract_minzoom &&
        extract_maxzoom)
        return true;

    std::cout<< "For example:--region na --minzoom 12 --maxzoom 16 --bounding-box top=81.72750 left=124.273873 bottom=39.9530776 right=163.3126108 --write-dir /Users/test --read-json /Users/test/19Q1_WorldMapAdminLink.json" << std::endl;
    return false;
}
