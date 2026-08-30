#include "raylib.h" // raylib se vende por separado
#include <iostream>
#include <string>
#include <vector>
#include <random>
using namespace std;
random_device g;
mt19937 gen(g());

int aleatorio(int a, int b){
    uniform_int_distribution<int> total (a, b);
    return total(gen);
}

struct obj{
  int id;  
  int x;
  int y;
  int t;  
};
vector<obj> arb;

Color colo();
const int tamay = 20;
const int tamax = 20; 
Color colores_matriz[tamax][tamay];


unsigned char con(int a){
    if(a != 0){
return a * 255 / 100;
}
    return 0;
}

void iniciar(){
    int ctd_arb = aleatorio(10, 20);
    for(int i = 0; i < ctd_arb; i++){
        arb.push_back({});
        arb[i].x = aleatorio(-650, 650);
        arb[i].y = aleatorio(-650, 650);
        arb[i].t = aleatorio(80, 170);
        arb[i].id = i;
    }
    
    for(int a = 0; a < tamax; a++){
        for(int b = 0; b < tamay; b++){
            colores_matriz[a][b] = colo();
        }
    }
}

void arbol(int x, int y, int t, int id){
    DrawRectangle(x - t/2, y + t , t - t/2, t, BROWN);
    DrawRectangle(x- t/1.5, y , (t / 2.5) * 2, (t / 1.5) * 2, GREEN);
    DrawRectangle(x  -  t/1.1 , y + t/9 , (t / 1.5) * 2, (t / 2) * 2, GREEN);
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
        arbol(arb[i].x,arb[i].y, arb[i].t, arb[i].id);
    }    
}

int main() {
   // #960
    int speed = 5;
    int jx = 0;
    int jy = 0;
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

        if (IsKeyDown(KEY_RIGHT)){ jugador.x += speed; jx +=speed;}
        if (IsKeyDown(KEY_LEFT)){  jugador.x -= speed; jx -=speed;}
        if (IsKeyDown(KEY_UP)){    jugador.y -= speed; jy +=speed;}
        if (IsKeyDown(KEY_DOWN)){  jugador.y += speed; jy -=speed;}
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
        per(jugador.x - 25,jugador.y - 25);
        arbolrend();
        EndMode2D();
        DrawText("coordenadas : ", 10, 10, 20, BLACK);
        DrawText(TextFormat("x: %d y: %d", jx , jy) , 10, 30, 20, BLACK);
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
