#include <SFML/Graphics.hpp>
#include<bits/stdc++.h>
#define pb push_back
#define Log(x) cout<<x<<endl;

using namespace std;
using namespace sf;

class curve{

vector<Vertex> path;
Color c;
public:
float x,y;
Color c1;
Color c2;

void addpoint()
{
    c.r=(c1.r+c2.r)/2;
    c.b=(c1.b+c2.b)/2;
    c.g=(c1.g+c2.g)/2;
    c.a = 255;
    path.pb(Vertex(Vector2f(x,y),c));

}

void draw(RenderWindow* app)
{
    (*app).draw(&path[0],path.size(),LinesStrip);
}

};

Color colr(int i)
{
    switch(i%8)
    {
    case 0:
        return  Color::White;
        break;
    case 1:
        return Color::Red;
        cout<<"HIHI"<<endl;
        break;
    case 2:
        return Color::Yellow;
        break;
    case 6:
        return Color::Blue;
        break;
    case 7:
        return Color::Green;
        break;
    case 5:
        return Color::Cyan;
        break;
    case 4:
        return Color::Magenta;
        break;
    case 3:
        return Color(255,140,0,255);
        break;

    }
}

curve desene[10][10];

int c;
int s = 70;
int offset = 15,offsety = 10,offsetx = 25;
CircleShape circles[11];
CircleShape point[21];
float angle;
bool start;
Vertex vertices[50];

void drawL(int i)
{
    circles[i].setRadius(s/2);
    circles[i].setOrigin(s/2,s/2);
    circles[i].setPointCount(300);
    Color col = colr(i);
    circles[i].setOutlineColor(col);
    int x,y;
    x=i*s + offset * i + offsetx + s/2;
    y=offsety + s/2;
    circles[i].setFillColor(Color::Black);
    circles[i].setOutlineThickness(2);
    circles[i].setPosition(x,y);
    float xx,yy;
    xx=s/2 * cos(angle * (i+1) - M_PI_2);
    yy=s/2 * sin(angle * (i+1) - M_PI_2);
    int rad = 5;
    point[i].setRadius(rad);
    point[i].setOrigin(rad,rad);
    point[i].setPointCount(30);
    point[i].setFillColor(Color::White);
    point[i].setPosition(xx + x,yy + y);
    vertices[(i+c)*2].position = Vector2f(xx+x,yy+y);
    vertices[(i+c)*2+1].position = Vector2f(xx+x,700);
    //Log(i);
    for(int j = 1;j<c;j++)
    {desene[j][i].x = xx+x;
    desene[j][i].c1=colr(i);}

}

void drawC(int i)
{
    circles[i].setRadius(s/2);
    circles[i].setOrigin(s/2,s/2);
    circles[i].setPointCount(300);
    circles[i].setOutlineColor(colr(i));
    int x,y;
    x=offsetx + s/2;
    y=i*s + offset * i + offsety + s/2;
    circles[i].setFillColor(Color::Black);
    circles[i].setOutlineThickness(2);
    circles[i].setPosition(x,y);
    float xx,yy;
    xx=s/2 * cos(angle * (i+1) - M_PI_2);
    yy=s/2 * sin(angle * (i+1) - M_PI_2);
    int rad = 5;
    point[i+c].setRadius(rad);
    point[i+c].setOrigin(rad,rad);
    point[i+c].setPointCount(30);
    point[i+c].setFillColor(Color::White);
    point[i+c].setPosition(xx + x,yy + y);
    vertices[i*2].position = Vector2f(xx+x,yy+y);
    vertices[i*2+1].position = Vector2f(700,yy+y);
    for(int j = 1;j<c;j++)
    {desene[i][j].y = yy+y;
    desene[i][j].c2=colr(i);}
}

int main()
{
    RenderWindow app(VideoMode(700, 700), "SFML window",Style::Close|Style::Titlebar);
    c = 700/(s+offset);
    c=8;
    app.setFramerateLimit(60);
    while (app.isOpen())
    {
        Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == Event::Closed)
                app.close();
            if(event.type == Event::KeyPressed)
                if(event.key.code == Keyboard::Space)
                start = true;
        }
        app.clear();
if(start==true){
        for(int i = 1; i< c;i++)
        {
            drawL(i);
            app.draw(circles[i]);
            app.draw(point[i]);
            drawC(i);
            app.draw(circles[i]);
            app.draw(point[i+c]);
            app.draw(vertices+(i*2),2,Lines);
            app.draw(vertices+((i+c)*2),2,Lines);
        }

            for(int q=1;q<c;q++)
                for(int k=1;k<c;k++)
            {
                desene[q][k].addpoint();
                desene[q][k].draw(&app);
            }

        angle+=0.1;


        app.display();}
    }

    return EXIT_SUCCESS;
}
