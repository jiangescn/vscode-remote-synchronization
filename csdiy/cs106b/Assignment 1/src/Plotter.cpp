#include "Plotter.h"
#include "strlib.h"
using namespace std;

void runPlotterScript(istream& input) {
    /* TODO：删除此行及其后一行，然后实现此函数。 */
    double X = 0;
    double Y = 0;
    bool pen_down = false;

    PenStyle style = {1, "black"};
    string s;
    while(getline(input, s))
    {
        Vector<string> parts = stringSplit(s, " ");
        string command = toLowerCase(parts[0]);
        if(command == "penup")
        {
            pen_down = false;
        }
        else if(command == "pendown")
        {
            pen_down = true;
        }
        else if(command == "pencolor")
        {
            style.color = parts[1];
        }
        else if(command == "penwidth")
        {
            style.width = stringToReal(parts[1]);
        }
        else
        {
            double newX = stringToReal(parts[1]);
            double newY = stringToReal(parts[2]);
            if(command == "moverel")
            {
                newX += X;
                newY += Y;
            }
            if (pen_down)
            {
                drawLine(X, Y, newX, newY, style);
            }
            X = newX, Y = newY;
        }
    }
}
