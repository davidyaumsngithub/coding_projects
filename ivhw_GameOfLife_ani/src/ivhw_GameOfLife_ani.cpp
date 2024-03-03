// [AM, Mar 02, 2024] Taiwei Yau
// Implement the algorithm of 'Game of Life' with Python matlibplot plot animation

#include <vector>
#include <iostream>
#include <fstream>
#include <string.h>
#include "matplotlibcpp.h"

namespace std {

typedef struct cell_loc_s{
    struct {int x; int y;};
} cell_loc_t;

class live_cell {
    public:
        live_cell(int x_, int y_) : cell_loc({x_, y_}) {};
        cell_loc_t _cell_loc(void) {return cell_loc;}
        unsigned int is_neighbor(cell_loc_t exist_cell);
    private:
        cell_loc_t cell_loc;
};

unsigned int live_cell::is_neighbor(cell_loc_t exist_cell) {
    int xe = exist_cell.x, ye = exist_cell.y;
    int xl = cell_loc.x, yl = cell_loc.y;
    return (((xe == (xl + 1)) && (ye == yl)) || ((xe == (xl - 1)) && (ye == yl)) || ((xe == xl)) && (ye == (yl + 1)) || ((xe == xl) && (ye == (yl - 1))) || ((xe == (xl + 1)) && (ye == (yl + 1))) || ((xe == (xl + 1)) && (ye == (yl - 1))) || ((xe == (xl - 1)) && (ye == (yl + 1))) || ((xe == (xl - 1)) && (ye == (yl - 1)))) ? 1 : 0;
}


class Universe {
    public:
        ~Universe() {cells.clear();}
        void update_universe(void);
        std::vector<class live_cell> cells;
    private:
        std::vector<int> icell_dying;
        std::vector<struct cell_loc_s> cells_to_bore;
};


void Universe::update_universe(void) {
    unsigned int neighbor_counter;
    unsigned int birth_neighbors[8];
    cell_loc_t cell_birth[8];
    volatile unsigned int number_cell;
    for (int iextcell = 0; iextcell < cells.size(); iextcell++) {
        neighbor_counter = 0;
        memset(birth_neighbors, 0, 8 * sizeof(unsigned int));
        cell_birth[0].x = cells[iextcell]._cell_loc().x; cell_birth[0].y = cells[iextcell]._cell_loc().y + 1; 
        cell_birth[1].x = cells[iextcell]._cell_loc().x; cell_birth[1].y = cells[iextcell]._cell_loc().y - 1;
        cell_birth[2].x = cells[iextcell]._cell_loc().x + 1; cell_birth[2].y = cells[iextcell]._cell_loc().y;
        cell_birth[3].x = cells[iextcell]._cell_loc().x - 1; cell_birth[3].y = cells[iextcell]._cell_loc().y;
        cell_birth[4].x = cells[iextcell]._cell_loc().x + 1; cell_birth[4].y = cells[iextcell]._cell_loc().y + 1; 
        cell_birth[5].x = cells[iextcell]._cell_loc().x + 1; cell_birth[5].y = cells[iextcell]._cell_loc().y - 1;
        cell_birth[6].x = cells[iextcell]._cell_loc().x - 1; cell_birth[6].y = cells[iextcell]._cell_loc().y + 1;
        cell_birth[7].x = cells[iextcell]._cell_loc().x - 1; cell_birth[7].y = cells[iextcell]._cell_loc().y - 1;
        for (vector<class live_cell>::iterator livecell = cells.begin(); livecell != cells.end(); livecell++) {
            neighbor_counter += livecell->is_neighbor((cell_loc_t)cells[iextcell]._cell_loc());
            birth_neighbors[0] += livecell->is_neighbor((cell_loc_t)cell_birth[0]);
            birth_neighbors[1] += livecell->is_neighbor((cell_loc_t)cell_birth[1]);
            birth_neighbors[2] += livecell->is_neighbor((cell_loc_t)cell_birth[2]);
            birth_neighbors[3] += livecell->is_neighbor((cell_loc_t)cell_birth[3]);
            birth_neighbors[4] += livecell->is_neighbor((cell_loc_t)cell_birth[4]);
            birth_neighbors[5] += livecell->is_neighbor((cell_loc_t)cell_birth[5]);
            birth_neighbors[6] += livecell->is_neighbor((cell_loc_t)cell_birth[6]);
            birth_neighbors[7] += livecell->is_neighbor((cell_loc_t)cell_birth[7]);
        }
        if ((neighbor_counter < 2) || (neighbor_counter > 3)) icell_dying.push_back(iextcell); 
        if (birth_neighbors[0] == 3) cells_to_bore.push_back(cell_birth[0]);
        if (birth_neighbors[1] == 3) cells_to_bore.push_back(cell_birth[1]);
        if (birth_neighbors[2] == 3) cells_to_bore.push_back(cell_birth[2]);
        if (birth_neighbors[3] == 3) cells_to_bore.push_back(cell_birth[3]);
        if (birth_neighbors[4] == 3) cells_to_bore.push_back(cell_birth[4]);
        if (birth_neighbors[5] == 3) cells_to_bore.push_back(cell_birth[5]);
        if (birth_neighbors[6] == 3) cells_to_bore.push_back(cell_birth[6]);
        if (birth_neighbors[7] == 3) cells_to_bore.push_back(cell_birth[7]);
    }

    for (vector<struct cell_loc_s>::iterator toboredcell = cells_to_bore.begin(); toboredcell != cells_to_bore.end(); toboredcell++) {
        neighbor_counter = 0;
        number_cell = cells.size(); 
        for (unsigned int icell = 0; icell < number_cell; icell++) {
            if ((toboredcell->x == cells[icell]._cell_loc().x) && (toboredcell->y == cells[icell]._cell_loc().y)) {
                neighbor_counter = 1;
                break;
            }
        }
        if (!neighbor_counter) cells.push_back((live_cell){toboredcell->x,toboredcell->y});
    }
    cells_to_bore.clear();

    for (auto icell = icell_dying.rbegin(); icell != icell_dying.rend(); icell++) cells.erase(cells.begin() + (*icell));
    icell_dying.clear();

}
}

namespace plt = matplotlibcpp;
using namespace std;

int main(int argc, char* argv[]) {
    FILE *inFile, *outFile = NULL;
    char keyin[_MAX_PATH];
    unsigned int numEvolution;

    switch (argc) {
        case 1:
            printf("initial cell location file (.txt)? "); scanf("%s", keyin);
            inFile = fopen(keyin, "rt");
            if (inFile == NULL) {printf("file isn't availabe! Abort\n"); return 1;}
            printf("number of iteration? "); scanf("%u", &numEvolution);
            break;
        case 2:
            inFile = fopen(argv[1], "rt");
            if (inFile == NULL) {printf("file is not available! Abort\n"); return 1;}
            printf("number of iteration? "); scanf("%u", &numEvolution);
            break;
        case 3:
            inFile = fopen(argv[1], "rt");
            if (inFile == NULL) {printf("file is not available! Abort\n"); return 1;}
            sscanf(argv[2], "%u", &numEvolution);
            break;
        case 4:
            inFile = fopen(argv[1], "rt");
            if (inFile == NULL) {printf("file is not available! Abort\n"); return 1;}
            sscanf(argv[2], "%u", &numEvolution);
            outFile = fopen(argv[3], "wt");
            break;
        default:
            std::cout << "Number of input argument error. Abort" << std::endl;
            return 1;
    }

    Universe* universe = new Universe;

    while (1) {
        int _x, _y;
        if (fscanf(inFile, "%d, %d", &_x, &_y) != 2) break;
        universe->cells.push_back((live_cell){_x, _y});
    }
    fclose(inFile);

   	std::vector<double> xp, yp;
    std::cout << universe->cells.size() << " cells initialized in universe" << std::endl;
    for (vector<class live_cell>::iterator livecell = universe->cells.begin(); livecell != universe->cells.end(); livecell++) {
        std::cout << "cell location (" << livecell->_cell_loc().x << ", " << livecell->_cell_loc().y << ")" << std::endl;
        xp.push_back((double)livecell->_cell_loc().x); yp.push_back((double)livecell->_cell_loc().y);
    }
    cout << endl;

    if (outFile) {
        fprintf(outFile, "UNIVERSE\n");
        fprintf(outFile, "- initial -\n");
        fprintf(outFile, "%d cells:\n", universe->cells.size());
        for (vector<class live_cell>::iterator livecell = universe->cells.begin(); livecell != universe->cells.end(); livecell++) {
            fprintf(outFile, "(%d, %d) ", livecell->_cell_loc().x, livecell->_cell_loc().y); 
        }
        fprintf(outFile, "\n\n");
    }
    
    plt::clf(); plt::margins(1.1, 1.1);
   	plt::plot(xp, yp, {{"linestyle", ""}, {"marker", "s"}, {"markersize", "36.0"}}); plt::axis("square"); plt::grid(true); plt::pause(1.0);

    for (unsigned int lp = 0; lp < numEvolution; lp++){
        cout << "evol #" << (lp + 1) << ":" << endl;
        if (universe->cells.empty()) {cout << "-- end of world --" << endl; break;}
        universe->update_universe();
        std::cout << universe->cells.size() << " cells in universe" << std::endl;
        xp.clear(); yp.clear();
        for (vector<class live_cell>::iterator livecell = universe->cells.begin(); livecell != universe->cells.end(); livecell++) {
            std::cout << "cell location (" << livecell->_cell_loc().x << ", " << livecell->_cell_loc().y << ")" << std::endl;
            xp.push_back((double)livecell->_cell_loc().x); yp.push_back((double)livecell->_cell_loc().y);
        }
        cout << endl;

        if (outFile) {
            fprintf(outFile, "- evol #%u -\n", lp + 1);
            fprintf(outFile, "%d cells:\n", universe->cells.size());
            for (vector<class live_cell>::iterator livecell = universe->cells.begin(); livecell != universe->cells.end(); livecell++) {
                fprintf(outFile, "(%d, %d) ", livecell->_cell_loc().x, livecell->_cell_loc().y); 
            }
            fprintf(outFile, "\n\n");
        }
        
        plt::clf(); plt::margins(1.1, 1.1); 
        plt::plot(xp, yp, {{"linestyle", ""}, {"marker", "s"}, {"markersize", "36.0"}}); plt::axis("square"); plt::grid(true); plt::pause(1.0);
    }

    if (outFile) fclose(outFile);
   	printf("- End -\n");
	plt::show(true);
    delete universe;
    return 0;
}