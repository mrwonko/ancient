#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <algorithm>
#include <boost/regex.hpp>
#include "Configfile.h"
#include "Helpers.h"
#include "CLArguments.h"

std::string GetFileContent(const std::string& filename)
{
    std::string content;
    std::ifstream in(filename.c_str());
    if(in.fail())
    {
        std::cout<<"Could not open "<<filename<<"!"<<std::endl;
        return "";
    }
    while(!in.eof())
    {
        content += in.get();
    }
    in.close();
    return content;
}

std::string GetFileExtension(const std::string& filename)
{
    std::string::size_type lastDotPos = filename.find_last_of('.');

    if(lastDotPos == std::string::npos) return "";

    return filename.substr(lastDotPos+1);
}

enum ResourceType
{
    RT_NULL,
    RT_TEXTURE,
    RT_MODEL,
    RT_MODEL2,
    RT_MODEL3,
    RT_SOUND,
    RT_SCRIPT,
    RT_EFFECT,
    RT_MUSIC,
    RT_PATCHTEX,
    RT_SHADER,
    RT_ALPHAMAP
};

void AddNextToSetAndTrimInput(std::string& input, std::string::size_type start, std::set<std::string>& set, ResourceType rt)
{
    if(start == std::string::npos)
    {
        std::cout<<"AddNextToSetAndTrimInput called with npos start!"<<std::endl;
        return;
    }
    if(input == "")
    {
        std::cout<<"AddNextToSetAndTrimInput called with empty input!"<<std::endl;
    }

    input.erase(0, start);
    std::string::size_type end = std::string::npos;
    if(rt == RT_SCRIPT)
    {
        input.erase(0, 9);
        end = input.find('"');
    }
    else if (rt == RT_EFFECT)
    {
        input.erase(0, 10);
        end = input.find('"');
    }
    else if (rt == RT_PATCHTEX)
    {
        input.erase(0, 12);
        end = input.find('\n');
    }
    else if (rt == RT_SHADER)
    {
        input.erase(0, 10);
        end = input.find('"');
    }
    else if (rt == RT_ALPHAMAP)
    {
        input.erase(0, 12);
        end = input.find('"');
    }
    else if (rt == RT_MODEL2)
    {
        input.erase(0, 10);
        end = input.find('"');
    }
    else if (rt == RT_MODEL3)
    {
        input.erase(0, 9);
        end = input.find('"');
    }
    else
    {
        end = input.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890_-./\\()&+");
        //std::cout<<"ELSE!"<<((end==std::string::npos) ? "npos" : Helpers::IntToString(end))<<std::endl;
    }

    if(end == std::string::npos)
    {
        std::cout<<"Error: sudden end of file! Type: "<< rt << ". Last 50 characters: \""<<input.substr(0, 50)<<"\"";
        //ensure we don't get stuck here
        if(!input.empty()) input.erase(0, 1);
        std::cout<<" dammit."<<std::endl;
        return;
    }
    std::string insme = input.substr(0, end);
    insme = Helpers::ToLower(Helpers::Replace(insme, "\\", "/"));
    if(rt == RT_SCRIPT) insme = "scripts/" + insme;
    else if(rt == RT_PATCHTEX && insme.substr(0, 9) != "textures/") insme = "textures/" + insme;
    else if(rt == RT_SHADER && insme.substr(0, 9) != "textures/") insme = "textures/" + insme;
    else if(rt == RT_EFFECT && insme.substr(0, 8) != "effects/") insme = "effects/" + insme;
    set.insert(insme);
    input.erase(0, end);
}

void SearchForResources(std::string& content, std::set<std::string>& output)
{

    while(true)
    {
        std::string::size_type nextTexturePos = content.find("textures/");
        if(nextTexturePos == std::string::npos) nextTexturePos = content.find("textures\\");
        std::string::size_type nextModel2Pos = content.find("\"model2\" \"");
        std::string::size_type nextModel3Pos = content.find("\"model\" \"");
        std::string::size_type nextModelPos = content.find("models/");
        if(nextModelPos == std::string::npos) nextModelPos = content.find("models\\");
        std::string::size_type nextSoundPos = content.find("sound/");
        if(nextSoundPos == std::string::npos) nextSoundPos = content.find("sound\\");
        std::string::size_type nextScriptPos = content.find("script\" \"");
        std::string::size_type nextEffectPos = content.find("\"fxfile\" \"");
        std::string::size_type nextPatchTexPos = content.find("patchdef2\n{\n");
        std::string::size_type nextAlphamapPos = content.find("\"alphamap\" \"");
        std::string::size_type nextShaderPos = content.find("\"shader\" \"");
        std::string::size_type nextMusicPos = content.find("music/");
        if(nextMusicPos == std::string::npos) nextMusicPos = content.find("music\\");

        std::string::size_type nextPos = std::string::npos;
        std::vector<std::string::size_type> positions;
        positions.push_back(nextEffectPos);
        positions.push_back(nextModelPos);
        positions.push_back(nextModel2Pos);
        positions.push_back(nextModel3Pos);
        positions.push_back(nextMusicPos);
        positions.push_back(nextScriptPos);
        positions.push_back(nextSoundPos);
        positions.push_back(nextTexturePos);
        positions.push_back(nextPatchTexPos);
        for(std::vector<std::string::size_type>::iterator it = positions.begin();it != positions.end(); ++it)
        {
            nextPos = std::min(nextPos, *it);
        }
        std::cout<<"nextPos = "<<nextPos<<std::endl;
        if(nextPos == std::string::npos) break;

        ResourceType nextResource = RT_NULL;
        if     (nextPos == nextEffectPos  ) nextResource = RT_EFFECT;
        else if(nextPos == nextModelPos   ) nextResource = RT_MODEL;
        else if(nextPos == nextModel2Pos  ) nextResource = RT_MODEL2;
        else if(nextPos == nextModel3Pos  ) nextResource = RT_MODEL3;
        else if(nextPos == nextMusicPos   ) nextResource = RT_MUSIC;
        else if(nextPos == nextScriptPos  ) nextResource = RT_SCRIPT;
        else if(nextPos == nextSoundPos   ) nextResource = RT_SOUND;
        else if(nextPos == nextPatchTexPos) nextResource = RT_PATCHTEX;
        else if(nextPos == nextShaderPos  ) nextResource = RT_SHADER;
        else if(nextPos == nextAlphamapPos) nextResource = RT_ALPHAMAP;
        else if(nextPos == nextTexturePos ) nextResource = RT_TEXTURE;

        std::cout<<"nextPos = "<<nextPos<<std::endl;
        std::cout<<"nextTexturePos: "<<nextTexturePos<<" nextPos: "<<nextPos << " nextResource: "<<nextResource<<std::endl;
        AddNextToSetAndTrimInput(content, nextPos, output, nextResource);
    }
}

int main(int argc, char** argv)
{
    cppag::CLArguments arg(argc, argv);
    std::cout   << "This program parses a given .map file and creates a list containing all the textures and models used in it, plus the textures those models use." << std::endl
                << "Usage: ResourceLister.exe mapname.map" << std::endl
                << "Note: Can only parse textures in md3 and ase files" << std::endl;

    if(argc <= 1)
    {
        std::cout <<"Error: No map given!" << std::endl;
        //Exit
        std::cout<<"Press Enter to exit";
        std::fflush(stdin);
        std::getchar();
        return EXIT_FAILURE;
    }

    WGF::Configfile config;
    if(!config.LoadFromFile(arg.GetWorkingDirectory()+"ResourceLister.cfg"))
    {
        std::cout<<"Error: Couldn't load config file ResourceLister.cfg"<<std::endl;
        //Exit
        std::cout<<"Press Enter to exit";
        std::fflush(stdin);
        std::getchar();
        return EXIT_FAILURE;

    }
    std::string basepath = config.GetString("basepath");
    std::string listpath = config.GetString("listpath");
    std::string modpath = config.GetString("modpath");
    std::cout<<"Using basepath \""<<basepath<<"\"."<<std::endl;
    std::cout<<"Using modpath \""<<modpath<<"\"."<<std::endl;
    std::cout<<"Outputting list to \""<<listpath<<"\"."<<std::endl;

    std::string content = Helpers::ToLower(GetFileContent(argv[1]));

    if(content == "")
    {
        std::cout<<"Error: Couldn't open map \""<<argv[1]<<"\"!"<<std::endl;
        //Exit
        std::cout<<"Press Enter to exit";
        std::fflush(stdin);
        std::getchar();
        return EXIT_FAILURE;
    }
    std::cout<<"Successfully loaded the file."<<std::endl;

    std::set<std::string> resources;

    std::cout<<"Parsing brush faces..."<<std::endl;
    //parse for brush face textures
    {
        std::string contentCopy = content;
        const boost::regex regex_brushface("(\\(( -?[0-9]+(\\.[0-9]+)?){3} \\) ){3}([^ ()]+)( -?[0-9]+(\\.[0-9]+)?){8}");
        boost::match_results<std::string::iterator> result;
        while(boost::regex_search(contentCopy.begin(), contentCopy.end(), result, regex_brushface))
        {
            std::string str = result[4].str();
            if(str.substr(0, 7) != "models/")
            {
                str = "textures/" + str;
            }
            resources.insert(str);
            contentCopy.erase(contentCopy.begin(), result[0].second);
        }
    }

    //parse for textures and models
    std::cout<<"Parsing keys & values..."<<std::endl;
    SearchForResources(content, resources);

    std::cout<<"Map parsed. Parsing found models..."<<std::endl;

    std::set<std::string> oldResources = resources;
    for(std::set<std::string>::iterator it = oldResources.begin(); it != oldResources.end(); ++it)
    {
        std::string fileExt = Helpers::ToLower(GetFileExtension(*it));
        if(fileExt == "md3" || fileExt == "ase")
        {
            std::cout<<"Parsing "<<*it<<"..."<<std::endl;
            std::string modelContent = "";
            if(basepath != "") modelContent = GetFileContent(basepath + (*it));
            if(modelContent == "")
            {
                modelContent = GetFileContent(modpath + (*it));
            }
            if(modelContent == "") continue;
            SearchForResources(modelContent, resources);
        }
    }
    std::cout<<"Models parsed."<<std::endl;

    std::string outName = argv[1];
    outName.erase(0, outName.find_last_of("/\\")+1);
    outName += ".Resources.txt";
    outName = listpath + outName;
    std::ofstream out(outName.c_str());
    if(out.fail())
    {
        std::cout<<"Error: Couldn't create output file "<<outName<<"!"<<std::endl<<"Resources in this map: "<<std::endl;
        for(std::set<std::string>::iterator it = resources.begin(); it != resources.end(); ++it)
        {
            std::cout<<(*it)<<std::endl;
        }
    }
    else
    {
        for(std::set<std::string>::iterator it = resources.begin(); it != resources.end(); ++it)
        {
            out<<*it<<std::endl;
        }
        out.close();
        std::cout<<"List written to "<<outName<<std::endl;
    }

    //Exit
    std::cout<<"Press Enter to exit";
    std::fflush(stdin);
    std::getchar();
    return EXIT_SUCCESS;
}
