#include "queue.h"
#include <fstream>
#include <map>
#include <optional>
#include <vector>


struct FieldPoint
{
    size_t lineNum;
    size_t charNum;
};

struct TaskData
{
  public:
    std::vector<std::string> toResult();
    void appendLine(std::string const &line);
    void process();

  private:
    std::vector<std::string> field;
    std::map<Data, FieldPoint> idToFieldPoint;//сделано чтобы не менять тип, используемый в queue и не ломать тесты
    Data lastUsedId = 0;
    int answer;
    Data startPointId;
    Data registerPoint(FieldPoint p);
    bool checkIsPointAccessible(FieldPoint const &p);
    std::optional<char> getPointValue(FieldPoint const &p);
    std::vector<int> findAndRegisterAllChildren(FieldPoint const &p);
};

std::vector<std::string> Task(std::ifstream &input);