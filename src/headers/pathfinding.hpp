struct CellIndex
{
    int x;
    int y;

    bool operator<(const CellIndex &other) const
    {
        return x == other.x ? y < other.y : x < other.x;
    }
};

void do_bfs(CellIndex start);