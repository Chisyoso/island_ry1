#include "raylib.h"
#include <iostream>
#include <string>
#include <vector>
#include <random>
using namespace std;
int hand = -1;

int mision = 0;
string pedido = "madera" ;

random_device g;
int frame[4];
mt19937 gen(g());

    int rx = 0;
    int ry = 0; 
    void hitbos(int x, int y, int dx, int dy);
int aleatorio(int a, int b){
    uniform_int_distribution<int> total (a, b);
    return total(gen);
}

struct obj{
  int id;  
  int x;
  int y;
  int t;
  int v, vx;  
};
vector<obj> arb;

Color colo();

// TAMAÑO DISPLAY
const int tamay = 20;
const int tamax = 20; 
Color colores_matriz[tamax][tamay];


unsigned char con(int a){
    if(a != 0){
return a * 255 / 100;
}
    return 0;
}

void manos(){
    switch(hand){
        case 100: DrawRectangle(rx, ry + 25, 20, 20, BROWN); 
        break; // madera
        case 102: DrawRectangle(rx, ry + 25, 20, 20, GRAY);
        break; // piedra
        case 103: DrawRectangle(rx, ry + 25, 20, 20, RED);
        break; // vallas salvajes
    }
}

void bote(int x, int y){
    Color cafe1 = {con(80), con(80), con(30), 255};
    Color cafe2 = {con(70), con(70), con(20), 255};
    for(int i = 0; i < 6; i++){
    DrawRectangle(-850 + x, -30 + (10 * i) + y, 100, 20, cafe1);
}
    DrawRectangle(-840 + x, -30+ y, 10, 60, cafe2);
    DrawRectangle(-760 + x , -30 + y, 10, 60, cafe2);
    
    
    if(rx  < (-800 + x)+ 100 && rx >  (-800 + x)  && ry > (-50 + y)   && ry <  (-30 + y) + 100 ){
    DrawText(TextFormat("consigue: %s    materiales: %d / 10", pedido.c_str(), mision ), rx- 200 , ry  - 50 , 20, BLACK);
}
}

void lifeline(int min,  int max){
    for(int i = 0; i < max; i++){
        DrawRectangle(rx, ry + 30, 10 * i, 10, GRAY);
    }
    for(int i = 0; i < min; i++){
        DrawRectangle(rx, ry + 30, 10 * i, 10, RED);
    }
    
}

void iniciar(){
    int ctd_arb = aleatorio(5, 10);
    for(int i = 0; i < ctd_arb; i++){
        arb.push_back({});
        arb[i].x = aleatorio(-650, 650);
        arb[i].y = aleatorio(-500, 500);
        arb[i].t = aleatorio(80, 170);
        arb[i].id = i;
        arb[i].v = arb[i].t / 25;
        arb[i].vx = arb[i].v; 
    }
    
    for(int a = 0; a < tamax; a++){
        for(int b = 0; b < tamay; b++){
            colores_matriz[a][b] = colo();
        }
    }
}

void hitbos(int x, int y, int dx, int dy){
    DrawLine(x, y, x, dy, RED);
    DrawLine(x, y, dx ,  y, RED);
    DrawLine(dx, dy, x, dy , RED);
    DrawLine(dx, dy,dx , y , RED);
}

void arbol(int x, int y, int t, int id){
    DrawRectangle(x - t/2, y + t , t - t/2, t, BROWN);
    DrawRectangle(x- t/1.5, y , (t / 2.5) * 2, (t / 1.5) * 2, GREEN);
    DrawRectangle(x  -  t/1.1 , y + t/9 , (t / 1.5) * 2, (t / 2) * 2, GREEN);
    
    if(rx  < x + 100 && rx > x - 150  && ry < y + 200 + t && ry > y + 100 && (hand == id || hand == -1)){
        hand = id;
        lifeline(arb[id].v ,arb[id].vx);
        frame[0] = 0;
        if (IsKeyDown(KEY_Q) && frame[1] > 40 && hand < 99){ arb[id].v -= 1; frame[1] = 0;}  
        DrawText(TextFormat("un arbol? toca (q) " ) , rx,  ry + 20, 20, BLACK);
    }
    else if(frame[0] > 40 && hand < 99){
        hand  = -1;
    }
    if(arb[id].v <= 0){
        arb.erase(arb.begin() + id);
        for(int i = 0; i < arb.size(); i++){
         arb[i].id = i;
         hand = 100;   
        }
    }
    
}

void map(int ax, int ay){
    int x = ax;
    int y = ay;
    for(int a = 0; a < tamax; a++){
        for(int b = 0; b < tamay; b++){
            DrawRectangle(x, y, 20, 20, colores_matriz[a][b]);
            y+=20;
        }
        y = ay;
        x += 20;
    }
}
void per(int x, int y){
    DrawRectangle(x ,y ,50,50,BLUE);
    DrawRectangle(x + 2, y + 10,20 ,25, WHITE);
    DrawRectangle(x + 27, y + 10 ,20 ,25, WHITE);
    DrawRectangle(x + 2, y + 20,10 ,15, BLACK);
    DrawRectangle(x + 27, y + 20,10 ,15, BLACK);
    
}

Color colo(){

    Color c1 = {con(20), con(80), con(20), 255};
    Color c2 = {con(20), con(80), con(30), 255};
    Color c3 = {con(30), con(80), con(30), 255};

    int a = aleatorio(1, 3);
    
    switch(a){
        case 1: return c1; 
        break;
        case 2: return c2;
        break;
        case 3: return c3;
        break;
        default: return c2;
    }
}

void arbolrend(){
    for(int i = 0; i < arb.size(); i++){
        arb[i].id = i;
        arbol(arb[i].x,arb[i].y, arb[i].t, arb[i].id);
    }
}

int main() {
   // #960
   int jx = 0;
    int jy = 0;
    int speed = 5;
    iniciar();
    int life = 8;
    
    
    InitWindow(800, 450, "Raylib - Movimiento");
    Color ocean = {con(40), con(40), con(80), 255};
    Vector2 jugador = {0, 0};
    Camera2D camera = {0};
    camera.target = jugador;
        camera.offset = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
        camera.rotation = 0.0f;
        camera.zoom = 1.0f;
    SetTargetFPS(60);

    while (!WindowShouldClose()){
    if(frame[0] < 60){
        frame[0]++;
    }
    if(frame[1] < 60){
        frame[1]++;
    }
        if (IsKeyDown(KEY_RIGHT)){ jugador.x += speed; jx +=speed; rx += speed;}
        if (IsKeyDown(KEY_LEFT)){  jugador.x -= speed; jx -=speed; rx -= speed;}
        if (IsKeyDown(KEY_UP)){    jugador.y -= speed; jy +=speed; ry -= speed;}
        if (IsKeyDown(KEY_DOWN)){  jugador.y += speed; jy -=speed; ry += speed;}
        // funciones 
        if(rx > 800 ){
            jugador.x -= 4; jx -= 4; rx -= 4;
        }
        if(rx < -800){
            jugador.x += 4; jx += 4; rx += 4;
        }
        if(ry < -800){
            jugador.y += 4; jy -=4; ry += 4;
            
        }
        if(ry > 800){
            jugador.y -= 4; jy +=4; ry -= 4;
        }
        
        BeginDrawing();
       camera.target = jugador;
              BeginMode2D(camera);
        ClearBackground(ocean);
        int x = -800;
        for(int i = 0; i < 4; i++){
            int y = -800;
            for(int j = 0; j < 4; j++){
                
                map(0 + x, 0 + y);
                y += 400;
        }
        x += 400;
    }
        bote(0,0);
        per(jugador.x - 25,jugador.y - 25);
        manos();
        arbolrend();
        EndMode2D();
        DrawText("coordenadas : ", 10, 10, 20, BLACK);
        DrawText(TextFormat("x: %d y: %d", jx , jy) , 10, 30, 20, BLACK);
        DrawText(TextFormat("x: %d y: %d", rx , ry) , 10, 50, 20, BLACK);
         x = 0;
        for(int i = 0; i < life; i++){
            DrawRectangle(340 + x, 350, 10, 10, RED);
            x += 15;
        }
        EndDrawing();
        
    }
    
    CloseWindow();

    return 0;
}
