/*
** AnsParser.cpp for cpp_zia in /home/dupil_l/cpp_zia/AnsParser.cpp
**
** Made by Loic DUPIL
** Login   <loic.dupil@epitech.eu>
**
** Started on  Wed Jan 24 10:44:10 2018 Loic DUPIL
** Last update Wed Jan 24 10:44:10 2018 Loic DUPIL
*/

#include "Parser/AnsParser.hpp"

AnsParser::AnsParser()
{
}

AnsParser::~AnsParser()
{

}

void AnsParser::parseHttpFormat(std::string httpAnswer)
{
    std::stringstream   line(httpAnswer);
    std::string         segment;

    while (std::getline(line, segment, '\n'))
        this->dividedResponseLines.push_back(segment);

    for (const auto &request : dividedResponseLines)
    {
        std::stringstream   line(request);
        while (std::getline(line, segment, ' ')) {
            std::cout << segment << "   ";
            this->dividedResponseWords.push_back(segment);
        }
        std::cout << std::endl;
    }
    for (const auto &word : dividedResponseWords)
    {
        if (word.find("HTTP/1.1") != std::string::npos)
        {
            this->treatHttp1_1();
            break;
        }
    }

    //TODO : Faire un if qui convertit le dividedResponseWords[1] en int et qui le compare a la valeur de tous les valeurs possibles de l'enum
    //TODO : Parser le code retour et la raison dans dividedReponseWords et les mettre dans l'objet HttpResponse reponse;
}

void AnsParser::treatHttp1_1()
{
    this->response.version = zia::api::http::Version::http_1_1;
    this->response.status = std::stoi(this->dividedResponseWords[1]);
    this->response.reason = this->dividedResponseWords[2];
    for (const auto &method : this->dividedResponseWords)
    {
        if (method.at(method.size() - 1) == ':')
            fillHeaders(method);
    }
}

void AnsParser::fillHeaders(std::string toFind) {

    for (const auto &headers : this->dividedResponseLines)
    {
        if (headers.find(toFind) != std::string::npos)
            this->response.headers.insert({toFind, headers.substr(toFind.size() + 1)});
    }
}

void AnsParser::getBody() {

}
