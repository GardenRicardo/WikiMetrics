#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include "JsonReader.h"
#include "Human.h"
#include "CalculateMetrics.h"
#include "GenerateGraphics.h"
#include <filesystem>

namespace fs = std::filesystem;

int main()
{
    std::string folderPath = "../jsonFiles";
    int countHumans = 0;

    std::map<std::string, int> genders;
    std::unordered_map<std::string, int> religions;
    std::unordered_map<std::string, int> professions;
    std::unordered_map<std::string, int> educations;
    std::map<std::string, int> futebolistasPorDecada;
    std::map<std::string, int> politicosPorDecada;

    try
    {
        for (const auto &entry : fs::directory_iterator(folderPath))
        {
            if (entry.is_regular_file() && entry.path().extension() == ".json")
            {
                std::string filePath = entry.path().string();
                std::cout << "Processando arquivo: " << filePath << std::endl;

                std::vector<Human> humans = JsonReader::parseHumans(filePath);
                countHumans += humans.size();

                CalculateMetrics calc;

                auto fileGenders = CalculateMetrics::simpleItemRatio(humans);
                auto fileReligions = CalculateMetrics::compositeItemRatio(humans, "religion");
                auto fileProfessions = CalculateMetrics::compositeItemRatio(humans, "profession");
                auto fileEducations = CalculateMetrics::compositeItemRatio(humans, "education");
                calc.countByProfessionAndDecade(humans, "futebolista", futebolistasPorDecada);
                calc.countByProfessionAndDecade(humans, "político", politicosPorDecada);

                for (const auto &[key, value] : fileGenders)
                {
                    genders[key] += value;
                }

                for (const auto &[key, value] : fileReligions)
                {
                    religions[key] += value;
                }

                for (const auto &[key, value] : fileProfessions)
                {
                    professions[key] += value;
                }

                for (const auto &[key, value] : fileEducations)
                {
                    educations[key] += value;
                }
            }
        }

        std::cout << "Total de humanos processados: " << countHumans << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Erro: " << e.what() << std::endl;
    }

    GenerateGraphics::generateBarChart(genders, "barchart.txt");
    GenerateGraphics::generatePieChart(religions, "piechartReligions.txt");
    GenerateGraphics::generatePieChart(professions, "piechartProfessions.txt");
    GenerateGraphics::generatePieChart(educations, "piechartEducations.txt");

    std::map<std::string, int> futebolistasBar(futebolistasPorDecada.begin(), futebolistasPorDecada.end());
    GenerateGraphics::generateBarChart(futebolistasBar, "barchartFutebolistasPorDecada.txt");

    std::map<std::string, int> politicosBar(politicosPorDecada.begin(), politicosPorDecada.end());
    GenerateGraphics::generateBarChart(politicosBar, "barchartPoliticosPorDecada.txt");

    return 0;
}
