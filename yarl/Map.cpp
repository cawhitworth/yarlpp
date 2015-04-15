#include "Map.h"

Map::Map(Size s)
: m_size(s)
{
    MapCell c;
    c.type = Rock;

    m_Cells.resize(s.Area(), c);
}

Map::~Map()
{
}

void AddDungeonHeart(Map& map, Position position)
{
    map[position] = MapCell(Heart);
    Position p;
    for (p.x = position.x - 4; p.x < position.x + 5; p.x++)
    {
        for (p.y = position.y - 4; p.y < position.y + 5; p.y++)
        {
            MapCell c(StoneFloor);

            if (Distance(p, position) > 3 || p == position)
            {
                continue;
            }

            if (Distance(p, position) == 2 && !(p.x == position.x || p.y == position.y))
            {
                c = MapCell(Lava);

            }

            map[p] = c;
        }
    }
}