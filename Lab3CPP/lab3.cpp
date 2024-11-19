#include "lab3.h"
#include "queue.h"

std::vector<std::string> TaskData::toResult()
{
    std::vector<std::string> result;
    result.push_back(std::to_string(answer));

    return result;
}

std::optional<char> TaskData::getPointValue(FieldPoint const &p)
{
    std::optional<char> ans;
    if (p.lineNum < field.size() && p.charNum < field.at(p.lineNum).size())
    {
        return field.at(p.lineNum).at(p.charNum);
    }
    return ans;
}
void TaskData::appendLine(std::string const &line)
{
    for (size_t i = 0; i < line.size(); i++)
    {
        if (line[i] == 'X')
        {
            startPointId = this->registerPoint({field.size(), i});
        }
    }
    field.push_back(line);
}

Data TaskData::registerPoint(FieldPoint p)
{
    lastUsedId++;
    idToFieldPoint[lastUsedId] = p;
    return lastUsedId;
}

bool TaskData::checkIsPointAccessible(FieldPoint const &p)
{
    return this->getPointValue(p) != '#';
}
void TaskData::findAndRegisterAllChildren(FieldPoint const &p, std::function<void(Data)> insertToQueue)
{
    if (p.lineNum > 0)
    {
        FieldPoint newPoint = {p.lineNum - 1, p.charNum};
        if (checkIsPointAccessible(newPoint))
        {
            insertToQueue(registerPoint(newPoint));
        }
    }
    if (p.charNum > 0)
    {
        FieldPoint newPoint = {p.lineNum, p.charNum - 1};
        if (checkIsPointAccessible(newPoint))
        {
            insertToQueue(registerPoint(newPoint));
        }
    }
    if (p.lineNum < field.size())
    {
        FieldPoint newPoint = {p.lineNum + 1, p.charNum};
        if (checkIsPointAccessible(newPoint))
        {
            insertToQueue(registerPoint(newPoint));
        }
    }
    if (p.charNum < field.at(p.lineNum).size())
    {
        FieldPoint newPoint = {p.lineNum, p.charNum + 1};
        if (checkIsPointAccessible(newPoint))
        {
            insertToQueue(registerPoint(newPoint));
        }
    }
}

void TaskData::process()
{
    Queue q;
    q.insert(startPointId);
    while (!q.empty())
    {
        auto pointId = q.get();
        q.remove();
        auto pointCoordinates = idToFieldPoint.at(pointId);
        auto pointVal = getPointValue(pointCoordinates);
        if (pointVal.has_value() && pointVal.value() >= '0' && pointVal.value() <= '9')
        {
            answer = pointVal.value() - '0';
            return;
        }
        findAndRegisterAllChildren(pointCoordinates, [&q](Data id) { 
            q.insert(id);
        });
    }
    answer = -1;
}
std::vector<std::string> Task(std::ifstream &input)
{
    std::string line;
    TaskData data;

    while (!input.eof())
    {
        std::getline(input, line);
        data.appendLine(line);
    }

    data.process();

    return data.toResult();
}
