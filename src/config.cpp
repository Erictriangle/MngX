#include "config.h"


Config::Config()
{
    assign_path(default_dir());
    if(!filesystem::is_regular_file(path.full))
        creat();
}


Config::~Config()
{
    if(path.io.is_open())
        path.io.close();
}


bool
Config::set_path()
{
    assign_path(default_dir());
    return filesystem::is_regular_file(path.full);
}


bool
Config::set_path(const std::string& input)
{
    filesystem::path input_path(input);
    manage_input(input_path);
    return filesystem::is_regular_file(path.full);
}


bool
Config::set_path(const filesystem::path& input)
{
    manage_input(input);
    return filesystem::is_regular_file(path.full);
}


bool
Config::creat()
{
    try
    {
        filesystem::create_directory(path.dir);
        
        path.io.exceptions(std::fstream::failbit | std::fstream::badbit);
        try
        {
            path.io.open(path.full, std::ios_base::out | std::ios_base::trunc);
            for(auto sm : sections_map)
                path.io << sm.second << std::endl;
            path.io.close();
        }
        catch(const std::fstream::failure e)
        {
            std::cerr << "-=[ EXCEPTION ]=- Creat config file fail!\n" ;
            std::cerr << e.what() << std::endl;
            return 0;
        }
        
        return 1;
    }
    catch(const filesystem::filesystem_error &e)
    {
        std::cerr << "-=[ EXCEPTION ]=- Creat directory fail!\n";
        std::cerr << e.what() << std::endl;
        return 0;
    }
}


void
Config::add_row(const SECTION section, const std::string& input)
{
    std::string temp;
    string_vec vec;
    auto key = sections_map.find(section);

    if(is_repeat(input, key->second))
        return;
    
    path.io.exceptions( std::fstream::badbit);
    try
    {
        path.io.open(path.full, std::ios::in);
        
        while((path.io >> temp) && (temp != key->second))
            vec.push_back(temp);
           
        if(temp != key->second)
            temp = key->second;
        
        vec.push_back(temp);    
        vec.push_back(input);

        while(path.io >> temp)
            vec.push_back(temp);
   
        path.io.close();


        path.io.open(path.full, std::ios::out | std::ios::trunc);

        for(auto v : vec)
            path.io << v << std::endl;
        
        path.io.close();
    }
    catch(const std::fstream::failure e)
    {
        std::cerr << "-=[ EXECEPTION ]=- Change config file fail!\n";
        std::cerr << e.what() << std::endl;
    }
}


void
Config::remove_row(const SECTION section, const std::string& input)
{
    std::string temp;
    string_vec vec;
    auto key = sections_map.find(section);

    if(!is_repeat(input, key->second))
        return;

    path.io.exceptions(std::fstream::badbit);
    try
    {
        path.io.open(path.full, std::ios::in);

        while((path.io >> temp) && (temp != key->second))
            vec.push_back(temp);

        if(temp != key->second)
            return;
        vec.push_back(temp);

        while((path.io >> temp) && (temp != input))
            vec.push_back(temp);

        while(path.io >> temp)
            vec.push_back(temp);
        
        path.io.close();


        path.io.open(path.full, std::ios::out | std::ios::trunc);

        for(auto v : vec)
            path.io << v << std::endl;

            path.io.close();

        
    }
    catch(const std::fstream::failure e)
    {
        std::cerr << "-=[ EXCEPTION =- Change config file fail!\n";
        std::cerr << e.what() << std::endl;
    }
}


void
Config::take_directories(const SECTION section, path_vec& vec)
{
    std::string temp;
    auto key = sections_map.find(section);

    path.io.exceptions(std::fstream::badbit);
    try
    {
        path.io.open(path.full, std::ios::in);

        while((path.io >> temp) && (temp != key->second));
        
        while((path.io >> temp) && !(reverse_section_map.count(temp)))
            vec.push_back(temp);
            
        path.io.close();
    }
    catch(std::fstream::failure e)
    {
        std::cerr << "-=[ EXCEPTION =- Cannot load directory from config file!\n";
        std::cerr << e.what() << std::endl;
    }
}



//==================
//==PRIVATE SECTION
//================


void
Config::manage_input(const filesystem::path& input)
{
    const std::string str = input.native();

    if((str[0] == '/' && str[str.length()-1] == '/') && filesystem::is_directory(input))
        assign_path(input);
    else       
        assign_path(
                    [&input]()->filesystem::path
                    {
                        std::string dir = input.native();
                        while((*(dir.end()-1)) != '/')
                            dir.erase(dir.end()-1);
                        return dir;
                    }(),
                    
                    [&input]()->filesystem::path
                    {
                        std::string native = input.native();
                        std::string file;
                        for(auto it = native.end()-1; it != native.begin(); it--)
                        {
                            if(*it == '/')
                                break;
                            file += *it;
                        }
                        std::reverse(file.begin(), file.end());
                        return file;
                    }()
                    );
                    
}
            

filesystem::path
Config::default_dir()
{
    std::string user = getenv("USER");
    filesystem::path dir = "/home/" + user + "/.mngx/";
    return dir;
}


bool
Config::is_repeat(const std::string& row, const std::string& section)
{
    std::string temp;
    auto key = reverse_section_map.end();
    
    path.io.exceptions(std::ios::badbit);
    try
    {
        path.io.open(path.full, std::ios::in);
        while((path.io >> temp) && (temp != section));

        while((path.io >> temp) && (temp != row) && (key == reverse_section_map.end()));

        if(temp == row)
        {
            path.io.close();
            return 1;
        }

        path.io.close();
        return 0;
    }
    catch(const std::fstream::failure e)
    {
        std::cerr << "-=[ EXCEPTION ]=- Read config file fail!\n";
        std::cerr << e.what() << std::endl;
        return 0;
    }
}
