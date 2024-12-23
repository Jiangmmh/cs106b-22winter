#include "Plotter.h"
#include "strlib.h"
using namespace std;


struct position {
    double x;
    double y;
};

void runPlotterScript(istream& input) {
    // Some variables to save current pen style, position and pen status
    struct PenStyle ps = { 1, "black" };
    struct position pos = { 0.0, 0.0};
    bool penDown = false;

    // get one line each loop
    string cmd;
    while (getline(input, cmd)) {

        // open down
        if (startsWith(toLowerCase(cmd), "pendown")) {
            penDown = true;
            continue;
        }

        // open up
        if (startsWith(toLowerCase(cmd), "penup")) {
            penDown = false;
            continue;
        }

        // split the line to string vector
        Vector<string> vec = stringSplit(cmd, " ");

        // change pen color
        if (startsWith(toLowerCase(vec[0]), "pencolor")) {
            ps.color = vec[1];
            continue;
        }

        // change pen width
        if (startsWith(toLowerCase(vec[0]), "penwidth")) {
            ps.width = stringToDouble(vec[1]);
            continue;
        }

        // move the open absolutely
        if (startsWith(toLowerCase(vec[0]), "moveabs")) {
            double x = stringToReal(vec[1]);
            double y = stringToReal(vec[2]);
            if (penDown) {
                drawLine(pos.x, pos.y, x, y, ps);
            }
            pos.x = x;
            pos.y = y;
            continue;
        }

        // move the open relatively
        if (startsWith(toLowerCase(vec[0]), "moverel")) {
            double dx = stringToReal(vec[1]);
            double dy = stringToReal(vec[2]);
            if (penDown) {
                drawLine(pos.x, pos.y, pos.x + dx, pos.y + dy, ps);
            }
            pos.x += dx;
            pos.y += dy;
            continue;
        }
    }
}

