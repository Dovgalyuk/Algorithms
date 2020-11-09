#include "map.h"

int main()
{
   Map* mp = map_create();

   map_insert(mp, "Test50", "Test1");
   map_insert(mp, "Test30", "Test2");
   map_insert(mp, "Test70", "Test3");

   if (map_getData(mp, "Test1") != "Test50")
      std::cout << "map getData error: Test1" << std::endl;
   if (map_getData(mp, "Test2") != "Test30")
      std::cout << "map getData error: Test2" << std::endl;
   if (map_getData(mp, "Test3") != "Test70")
      std::cout << "map getData error: Test3" << std::endl;

   map_delete(mp);
   return 0;
}
