#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>

#include "CPPML/logging/logging.hpp"

/* This doesn't work */
bool LoadOBJFile(const char *address, std::unique_ptr<float[]> &ret_data, std::unique_ptr<uint[]> &ret_indices, uint &ret_vertexCount, uint &ret_dataBytes, uint &ret_indicesBytes)
{
    /* std::stof converts std::string to float, contained in <string>, doesn't care about spaces before and after num */
    std::ifstream file(address);

    if (file.is_open() == false)
    {
        CPPML_ERROR("Could not open model at \"{}\"", address);
        return false;
    }

    std::string line;

    std::vector<std::array<float, 3>> vertexDict = std::vector<std::array<float, 3>>();
    std::vector<std::array<float, 2>> texcoordDict = std::vector<std::array<float, 2>>();
    std::vector<std::array<float, 3>> normalDict = std::vector<std::array<float, 3>>();
    std::vector<std::array<uint, 3>> vtnComboDict = std::vector<std::array<uint, 3>>();
    std::vector<uint> comboIndices;
    uint comboIndex = 0;

    while (std::getline(file, line))
    {
        if (line[0] == 'v') // per-vertex data
        {
            if (line[1] == 't') // texcoord
            {
                uint numsFound = 0;
                std::string numStr = "";
                std::array<float, 2> grp = std::array<float, 2>();
                uint grpi = 0;
                for (size_t i = 3; i < line.size(); i++)
                {
                    if (i == line.size() - 1)
                    {
                        numStr += line[i];
                    }
                    if (line[i] == ' ' || i == line.size() - 1)
                    {
                        grp[grpi] = std::stof(numStr);
                        grpi++;
                        numsFound++;
                        numStr = "";

                        if (numsFound == 2)
                        {
                            break;
                        }
                        continue;
                    }

                    if (i != line.size() - 1)
                    {
                        numStr += line[i];
                    }
                }
                texcoordDict.push_back(grp);
            }
            else if (line[1] == 'n') // normal
            {
                uint numsFound = 0;
                std::string numStr = "";
                std::array<float, 3> grp = std::array<float, 3>();
                uint grpi = 0;
                for (size_t i = 3; i < line.size(); i++)
                {
                    if (i == line.size() - 1)
                    {
                        numStr += line[i];
                    }
                    if (line[i] == ' ' || i == line.size() - 1)
                    {
                        grp[grpi] = std::stof(numStr);
                        grpi++;
                        numsFound++;
                        numStr = "";
                        if (numsFound == 3)
                        {
                            break;
                        }
                        continue;
                    }
                    if (i != line.size() - 1)
                    {
                        numStr += line[i];
                    }
                }
                normalDict.push_back(grp);
            }
            else // vertex
            {
                uint numsFound = 0;
                std::string numStr = "";
                std::array<float, 3> grp = std::array<float, 3>();
                uint grpi = 0;
                for (size_t i = 2; i < line.size(); i++)
                {
                    if (i == line.size() - 1)
                    {
                        numStr += line[i];
                    }
                    if (line[i] == ' ' || i == line.size() - 1)
                    {
                        grp[grpi] = std::stof(numStr);
                        grpi++;
                        numsFound++;
                        numStr = "";
                        if (numsFound == 3)
                        {
                            break;
                        }
                        continue;
                    }
                    if (i != line.size() - 1)
                    {
                        numStr += line[i];
                    }
                }
                vertexDict.push_back(grp);
            }
        }
        else if (line[0] == 'f') // face specification
        {

            uint numsFound = 0;
            std::string numStr = "";
            std::array<uint, 3> vtnCombo = std::array<uint, 3>();
            uint vtnComboi = 0;
            for (size_t i = 2; i < line.size(); i++)
            {
                if (line[i] == '/')
                {
                    uint try_stoi;
                    try
                    {
                        try_stoi = std::stoi(numStr);
                    }
                    catch (std::invalid_argument &e)
                    {
                        CPPML_ERROR("Expected an integer, instead got \"{}\"", numStr);
                        return false;
                    }

                    vtnCombo[vtnComboi] = try_stoi;
                    vtnComboi++;
                    numsFound++;
                    numStr = "";
                    continue;
                }

                if (numsFound == 2 && line[i] == ' ')
                {
                    uint try_stoi;
                    try
                    {
                        try_stoi = std::stoi(numStr);
                    }
                    catch (std::invalid_argument &e)
                    {
                        CPPML_ERROR("Expected an integer, instead got: \"{}\"", numStr);
                        return false;
                    }

                    vtnCombo[vtnComboi] = try_stoi;
                    vtnComboi = 0;
                    numsFound = 0;
                    numStr = "";

                    // handle vtn combo

                    int foundIndex = -1;
                    // check if vtn combo is in dict already
                    for (size_t vi = 0; vi < vtnComboDict.size(); vi++)
                    {
                        std::array<uint, 3> vtnComboVI = vtnComboDict.at(vi);
                        // compare
                        if (vtnComboVI[0] == vtnCombo[0] && vtnComboVI[1] == vtnCombo[1] && vtnComboVI[2] == vtnCombo[2])
                        {
                            // found
                            foundIndex = vi;
                            break;
                        }
                    }

                    if (foundIndex == -1)
                    {
                        foundIndex = comboIndex;
                        vtnComboDict.push_back(vtnCombo);
                        comboIndex++;
                    }

                    comboIndices.push_back(foundIndex);
                    continue;
                }

                numStr += line[i];
            }
        }
        else // comment or other line that isn't used
        {
            continue;
        }
    }

    file.close();

    ret_data = std::make_unique<float[]>(vtnComboDict.size() * 8);
    ret_indices = std::make_unique<uint[]>(comboIndices.size());
    ret_dataBytes = vtnComboDict.size() * 8 * sizeof(float);
    ret_indicesBytes = comboIndices.size() * sizeof(uint);
    ret_vertexCount = comboIndices.size();

    for (size_t i = 0; i < vtnComboDict.size(); i++)
    {
        ret_data[i * 8] = vertexDict.at(vtnComboDict[i][0] - 1)[0];
        ret_data[(i * 8) + 1] = vertexDict.at(vtnComboDict[i][0] - 1)[1];
        ret_data[(i * 8) + 2] = vertexDict.at(vtnComboDict[i][0] - 1)[2];
        ret_data[(i * 8) + 3] = texcoordDict.at(vtnComboDict[i][1] - 1)[0];
        ret_data[(i * 8) + 4] = texcoordDict.at(vtnComboDict[i][1] - 1)[1];
        ret_data[(i * 8) + 5] = normalDict.at(vtnComboDict[i][2] - 1)[0];
        ret_data[(i * 8) + 6] = normalDict.at(vtnComboDict[i][2] - 1)[1];
        ret_data[(i * 8) + 7] = normalDict.at(vtnComboDict[i][2] - 1)[2];
    }

    for (size_t i = 0; i < comboIndices.size(); i++)
    {
        ret_indices.get()[i] = comboIndices[i];
    }

    return true;
}