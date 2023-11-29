//220201061 Eyüp Ensar Kara
//220201083 Yunus Hanifi Öztürk

#pragma warning(disable:4996)  //Uyarıyı devre dışı bırakmak için (scanf ve sscanf fonksiyonları için)

//Opengl'i nuget paket yöneticisi kullanarak dahil ediyoruz.(Intsall-Package nupengl.core)
//curl.h kütüphanesini vcpkg paket yöneticisi ile projeye dahil ediyoruz.


#include <stdio.h>
#include <curl/curl.h>  //İnternetten veri çekmek için curl.h kütüphanesini projeye dahil ediyoruz.
#include <string.h>  //string işlemleri
#include <GL/glut.h> //opengl'in glut eklentisini grafik kütüphanesi olarak kullanıyoruz.
#include <stdbool.h>  //Boolen değişken kullanabilmek için stdbool.h kütüphanesini projeye dahil ediyoruz.
#include <math.h>   //Matemiksel işlemler için math.h kütüphanesinin projeye dahil ediyoruz.


#define gridSize 120 //Kareli düzlem için boyut tanımlama

//Global structlar

//Koordinatları tanımladığımız struct
struct Point {
    double x;
    double y;
};


//Şeklin sınırlarını belirleyen struct
struct polygonlimit {
    int minx;
    int maxx;
    int miny;
    int maxy;
};


//Karenin biçimini tanımlama (1x1,2x2,4x4,8x8,16x16)
struct unitSquarre {
    int hasResource = 0;
};


//Boyalı Kareleri matris formatında saklamak için kullanılan struct 
struct ResourceArea {
    struct unitSquarre squares[gridSize][gridSize];
};



//Çokgenin bilgilerini tutan struct
struct polygon {
    int corner_count = 0;
    struct Point points[gridSize];
    struct polygonlimit polygonLimit;
    int area = 0;

    struct ResourceArea areaSpace;
};



//Satırlardaki şekilleri tutan sturct
struct line {
    struct polygon polygon[5];
    int polygon_number = 0;
    int reserve_area = 0;
    int platfrom_numbers = 0;
    int platform_area = 0;
};




//GLOBAL DEĞİŞKENLER

struct line line[gridSize];
int selected_line = -1;
bool isScreen1 = true;
int drill_cost;
int platform_cost;
bool onceStart1 = false;
bool onceStart2 = false;





//KOORDINAT CEKME VE ISLEME
void splitLine(char* input, char output[][100], int* lineCount) {
    char* token;
    char* context = NULL;
    // strtok ile satırları \n 'e göre böldük
    token = strtok(input, "\n");
    while (token != NULL) {
        strcpy(output[*lineCount], token);
        (*lineCount)++;
        //bütün satırları ayırmak için strtok'u tekrar kullanıyoruz
        token = strtok(NULL, "\n");
    }
}



//Koordinatları şekil structlarına atama
void parseCoordinates(char* input, struct line* line)
{
    int len = strlen(input);
    int tempx = NULL, tempy = NULL;
    int k = 0, j = 0;
    int x = 0, y = 0;
    int control = 0;
    for (int i = 0; i < len; i++) {

        if (input[i] == '(') {

            if (sscanf(input + i + 1, "%d,%d", &x, &y) == 2) {

                if ((tempx == NULL && tempy == NULL) || (tempx == x && tempy == y)) {

                    if ((tempx == x && tempy == y)) {
                        j++;
                        line->polygon_number = j;
                        k = 0;

                        control = 1;
                    }
                    tempx = x;
                    tempy = y;
                }
                if (control != 1) {
                    line->polygon[j].corner_count++;
                    line->polygon[j].points[k].x = x;
                    line->polygon[j].points[k].y = y;

                    k++;
                }
                else {
                    control = 0;
                    tempx = NULL;
                    tempy = NULL;
                }
            }
        }
    }
}


//OpenGl ile çokgenin kenarlarını çizmek için kullandığımız fonksiyon
void drawlines(struct polygon polygon) {

    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(5);

    for (int i = 0; i < polygon.corner_count; i++) {
        glBegin(GL_LINE_LOOP); //çizgi çizme döngüsü oluşturur(başlangıçla bitişi birleştirir)

        glVertex2f(polygon.points[i].x, polygon.points[i].y);
        glVertex2f(polygon.points[(i + 1) % polygon.corner_count].x, polygon.points[(i + 1) % polygon.corner_count].y);
        glEnd();

    }

}


//polygon'un max ve min'ini hesaplama
void polygonMaxMinHesapla(struct polygon* polygon)//polygonun max min değerlerini tutar
{
    int top = -1, left = -1, right = INT_MAX, bottom = INT_MAX;
    for (int i = 0; i < polygon->corner_count; i++)
    {

        if (top <= polygon->points[i].y) top = polygon->points[i].y;
        if (bottom >= polygon->points[i].y) bottom = polygon->points[i].y;
        if (left <= polygon->points[i].x) left = polygon->points[i].x;
        if (right >= polygon->points[i].x) right = polygon->points[i].x;
    }
    polygon->polygonLimit.minx = right;
    polygon->polygonLimit.maxx = left;
    polygon->polygonLimit.miny = bottom;
    polygon->polygonLimit.maxy = top;
}

//Şekli çizen fonksiyon
void drawquadline(struct Point point, int squarre_size) {

    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(4);

    glBegin(GL_LINE_LOOP);
    glVertex2f(point.x, point.y);
    glVertex2f(point.x + squarre_size, point.y);
    glVertex2f(point.x + squarre_size, point.y + squarre_size);
    glVertex2f(point.x, point.y + squarre_size);
    glEnd();


}




//Sol üst koordinatı verilen kareyi boyar.
void fillGridCell(int x, int y, int size) {
    switch (size) {
    case 16:
        glColor3f(0.0, 0.65, 1.0);
        break;
    case 8:
        glColor3f(0.0, 1.0, 0.0);
        break;
    case 4:
        glColor3f(1.0, 1.0, 0.0);
        break;
    case 2:
        glColor3f(1.0, 0.75, 0.5);
        break;
    case 1:
        glColor3f(0.588, 1.0, 0.05);
        break;
    }

    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + size, y);
    glVertex2f(x + size, y + size);
    glVertex2f(x, y + size);
    glEnd();
}

// Verilen üç nokta p, q ve r ile çalışan yönelim hesaplama fonksiyonu.
int orientation(struct Point p, struct Point q, struct Point r) {
    // İki vektörün dış çarpımını hesaplar (q-p) ve (r-q).
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    // Eğer dış çarpım 0 ise, noktalar aynı çizgi üzerindedir.
    if (val == 0)
        return 0;

    // Eğer dış çarpım pozitifse nokta r, çizgi p-q'nun sağ tarafında yer alır.
    // Aksi takdirde (val negatifse), nokta r, çizgi p-q'nun sol tarafında yer alır.
    return (val > 0) ? 1 : 2;
}

// Verilen üç nokta p, q ve r nin bir çizgi üzerinde olup olmadığını kontrol eden fonksiyon.
bool onSegment(struct Point p, struct Point q, struct Point r) {
    // Eğer q noktasının x ve y koordinatları, p ve r noktalarının sıralı min-max aralığında ise, q noktası çizgi üzerindedir.

    if (q.x <= fmax(p.x, r.x) && q.x >= fmin(p.x, r.x) &&
        q.y <= fmax(p.y, r.y) && q.y >= fmin(p.y, r.y)) {
        return true;
    }
    // Eğer yukarıdaki koşullar sağlanmazsa, q noktası çizgi üzerinde değildir.
    return false;
}

// Verilen bir noktanın poligonun içinde olup olmadığını kontrol eden fonksiyon.
bool isPointInsidePolygon(struct polygon polygon, struct Point p) {
    bool c = false;

    for (int i = 0; i < polygon.corner_count; i++) {
        struct Point p1 = polygon.points[i];
        struct Point p2 = polygon.points[(i + 1) % polygon.corner_count];

        //Bir noktanın,kenarın üzerinde olup olmadığının kontrol eden if.
        if (((p1.y > p.y) != (p2.y > p.y) &&
            (p.x < (p2.x - p1.x) * (p.y - p1.y) / (p2.y - p1.y) + p1.x)))
            c = !c;  // Eğer çarpma koşulu sağlanıyorsa, çarpma sayacını tersine çevir.

        // Her i için bu işlem tekrarlanır, ve sonunda çarpma sayacı true ise, nokta poligonun içindedir.
    }

    return c;  // Çarpma sayacının son durumu döndürülür.
}

// İki doğru parçasının (p1-q1 ve p2-q2) kesişip kesişmediğini kontrol eden fonksiyon.
bool doIntersect(struct Point p1, struct Point q1, struct Point p2, struct Point q2) {
    // Her iki doğru parçası için dört yönelim değeri hesapla.
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // Eğer iki doğru parçasının uçları farklı yönlere bakıyorsa bunlar kesişiyordur.
    if (o1 != o2 && o3 != o4) {
        return true;
    }

    // Eğer ikinci doğrunun bir ucu birincinin doğrunu üstündeyse doğrular kesişiyordur.

    if (o1 == 0 && onSegment(p1, p2, q1)) {
        return true;
    }

    // Eğer hiçbir kesişme koşulu sağlanmazsa, bu iki doğru parçası kesişmez.
    return false;
}


// Verilen bir poligon ve iki nokta ile çalışan, bu iki noktanın bir poligonun içinden geçen bir kenarla kesişip kesişmediği kontrol eden fonksiyon.
bool isEdgeInsidePolygon(struct polygon polygon, struct Point p1, struct Point p2) {
    for (int i = 0; i < polygon.corner_count; i++) {
        struct Point p3 = polygon.points[i];
        struct Point p4 = polygon.points[(i + 1) % polygon.corner_count];

        // Verilen iki noktanın ve poligonun i. kenarının uçlarının kesişip kesişmediğini kontrol etmek için doIntersect fonksiyonunu kullan.
        if (doIntersect(p1, p2, p3, p4)) {
            return true;  // Eğer kesişme varsa, bu iki nokta bir kenarı temsil ediyor ve bu kenar poligonun içinden geçiyor.
        }
    }

    // Eğer hiçbir kesişme yoksa, bu iki nokta bir kenarı temsil etmiyor ve bu kenar poligonun içinden geçmiyor.
    return false;
}

// Verilen poligonun içindeki dörtgen alanı hesaplayan ve bu alanı çizilen bir ızgara üzerine işleyen fonksiyon.
void paint_polygon_area(struct polygon* polygon) {
    polygon->area = 0;  // Poligonun alanını sıfırla.
    polygonMaxMinHesapla(polygon);  // Poligonun sınırlarını hesapla.

    for (int x = polygon->polygonLimit.minx; x < polygon->polygonLimit.maxx; x++) {
        for (int y = polygon->polygonLimit.miny; y < polygon->polygonLimit.maxy; y++) {
            struct Point p1 = { x, y };
            struct Point p2 = { x + 1, y };
            struct Point p3 = { x, y + 1 };
            struct Point p4 = { x + 1, y + 1 };

            // Dörtgenin bir kenarı poligonun içinden geçiyorsa veya dörtgenin bir noktası poligonun içindeyse,ızgara hücresini doldur ve poligonun alanını artır.

            if (isEdgeInsidePolygon(*polygon, p1, p2) || isEdgeInsidePolygon(*polygon, p2, p3) || isEdgeInsidePolygon(*polygon, p3, p4) || isEdgeInsidePolygon(*polygon, p4, p1)) {
                fillGridCell(x, y, 1);
                polygon->area++;
                polygon->areaSpace.squares[y][x].hasResource = 1;
            }
            else if (isPointInsidePolygon(*polygon, p1) || isPointInsidePolygon(*polygon, p2) || isPointInsidePolygon(*polygon, p3) || isPointInsidePolygon(*polygon, p4)) {
                fillGridCell(x, y, 1);
                polygon->area++;
                polygon->areaSpace.squares[y][x].hasResource = 1;
            }
        }
    }
}





//optimization çözümleri


//birim karenin hangi karesel (16x16,8x8,4x4,2x2,1x1) e dahil olduğunu kontrol eder.
bool has_resource_control(int x, int y, int size, struct polygon* polygon) {

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {

            if (polygon->areaSpace.squares[y + i][x + j].hasResource == 1)return true;
        }
    }
    return false;
}

//birim karenin hangi karesel (16x16,8x8,4x4,2x2,1x1) e dahil olduğunu atar.
void set_has_resource(int x, int y, int size, struct polygon* polygon) {


    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {

            polygon->areaSpace.squares[y + i][x + j].hasResource = size;

        }

    }

}

//sol üst köşesinin koordinatı ve boyutu verilen kareyi boyar ve atar.
void paint_quads(int x, int  y, int size, struct polygon* polygon) {

    set_has_resource(x, y, size, polygon);
    fillGridCell(x, y, size);
    struct Point p = { x,y };
    drawquadline(p, size);

}


//2.AŞAMA 


struct quadratic_regions {

    int x;
    int y;
    double cost;

};

struct quadratic_regions quadratic_region[17][gridSize * gridSize];
int quadratic_region_count[17];

struct ResourceArea setted_quadratic_region;


//karelerin karesel bölgelerini atar.
void set_quads(struct polygon polygon, int size)
{
    int cost = 0;
    int i = 0;
    for (int y = polygon.polygonLimit.miny; y < polygon.polygonLimit.maxy; y += size) {
        for (int x = polygon.polygonLimit.minx; x < polygon.polygonLimit.maxx; x += size)
        {
            if (has_resource_control(x, y, size, &polygon))
            {
                quadratic_region[size][i].x = x;
                quadratic_region[size][i].y = y;



                quadratic_region[size][i].cost = (double)(size * size * drill_cost) + platform_cost;
                cost = (size * size * drill_cost) + platform_cost;

                i++;


            }
        }
    }
    quadratic_region_count[size] = i;
}


//karelerin maliyetini hesaplar.
double calculate_cost(int y, int x, int size) {

    double cost = 0;

    for (int k = 0; k < quadratic_region_count[size / 2]; k++) {
        for (int i = y; i <= y + size - 1; i++)
        {
            for (int j = x; j <= x + size - 1; j++)
            {
                if (quadratic_region[size / 2][k].y == i && quadratic_region[size / 2][k].x == j)
                {
                    cost += (quadratic_region[size / 2][k].cost);
                }
            }
        }
    }
    return cost;
}


//Alan taraması yapar ve maliyeti düşük olan kareleri boyar.
void optimization(struct polygon* polygon)
{


    //2x2 lik karelerin alan taraması
    for (int i = 0; i < quadratic_region_count[2]; i++)
    {
        if (calculate_cost(quadratic_region[2][i].y, quadratic_region[2][i].x, 2) > quadratic_region[2][i].cost) {

            paint_quads(quadratic_region[2][i].x, quadratic_region[2][i].y, 2, polygon);
            setted_quadratic_region.squares[quadratic_region[2][i].y][quadratic_region[2][i].x].hasResource = 2;
        }
        else
        {
            for (int j = 0; j < quadratic_region_count[1]; j++)
            {
                if (quadratic_region[1][j].y == quadratic_region[2][i].y && quadratic_region[1][j].x == quadratic_region[2][i].x) {

                    setted_quadratic_region.squares[quadratic_region[2][i].y][quadratic_region[2][i].x].hasResource = 1;


                }

            }

        }
    }


    //4x4 karelerin alan taraması
    for (int i = 0; i < quadratic_region_count[4]; i++)
    {
        double total = 0;

        for (int j = quadratic_region[4][i].y; j < quadratic_region[4][i].y + 4; j++)
        {
            for (int k = quadratic_region[4][i].x; k < quadratic_region[4][i].x + 4; k++)
            {
                if (setted_quadratic_region.squares[j][k].hasResource == 1)
                    total += quadratic_region[1][j].cost;
            }


        }

        for (int j = quadratic_region[4][i].y; j < quadratic_region[4][i].y + 4; j++)
        {
            for (int k = quadratic_region[4][i].x; k < quadratic_region[4][i].x + 4; k++)
            {
                if (setted_quadratic_region.squares[j][k].hasResource == 2)
                    total += quadratic_region[2][j].cost;
            }


        }

        if (total > quadratic_region[4][i].cost) {


            setted_quadratic_region.squares[quadratic_region[4][i].y][quadratic_region[4][i].x].hasResource = 4;
            paint_quads(quadratic_region[4][i].x, quadratic_region[4][i].y, 4, polygon);



        }
    }

    //8x8 karelerin alan taraması

    for (int i = 0; i < quadratic_region_count[8]; i++)
    {
        double total = 0;
        for (int j = quadratic_region[8][i].y; j < quadratic_region[8][i].y + 8; j++)
        {
            for (int k = quadratic_region[8][i].x; k < quadratic_region[8][i].x + 8; k++)
            {
                if (setted_quadratic_region.squares[j][k].hasResource == 1)
                    total += quadratic_region[1][j].cost;
            }


        }

        for (int j = quadratic_region[8][i].y; j < quadratic_region[8][i].y + 8; j++)
        {
            for (int k = quadratic_region[8][i].x; k < quadratic_region[8][i].x + 8; k++)
            {
                if (setted_quadratic_region.squares[j][k].hasResource == 2)
                    total += quadratic_region[2][j].cost;
            }


        }

        for (int j = quadratic_region[8][i].y; j < quadratic_region[8][i].y + 8; j++)
        {
            for (int k = quadratic_region[8][i].x; k < quadratic_region[8][i].x + 8; k++)
            {
                if (setted_quadratic_region.squares[j][k].hasResource == 4)
                    total += quadratic_region[4][j].cost;
            }


        }
        if (total > quadratic_region[8][i].cost)
        {
            setted_quadratic_region.squares[quadratic_region[8][i].y][quadratic_region[8][i].x].hasResource == 8;
            paint_quads(quadratic_region[8][i].x, quadratic_region[8][i].y, 8, polygon);

        }
    }



    //16x16 karelerin alan taraması
    for (int i = 0; i < quadratic_region_count[16]; i++)
    {
        double total = 0;


        for (int j = quadratic_region[16][i].y; j < quadratic_region[16][i].y + 16; j++)
        {
            for (int k = quadratic_region[16][i].x; k < quadratic_region[16][i].x + 16; k++)
            {
                if (setted_quadratic_region.squares[j][k].hasResource == 1)
                    total += quadratic_region[1][j].cost;
            }


        }

        for (int j = quadratic_region[16][i].y; j < quadratic_region[16][i].y + 16; j++)
        {
            for (int k = quadratic_region[16][i].x; k < quadratic_region[16][i].x + 16; k++)
            {
                if (setted_quadratic_region.squares[j][k].hasResource == 2)
                    total += quadratic_region[2][j].cost;
            }


        }

        for (int j = quadratic_region[16][i].y; j < quadratic_region[16][i].y + 16; j++)
        {
            for (int k = quadratic_region[16][i].x; k < quadratic_region[16][i].x + 16; k++)
            {
                if (setted_quadratic_region.squares[j][k].hasResource == 4)
                    total += quadratic_region[4][j].cost;
            }

        }
        for (int j = quadratic_region[16][i].y; j < quadratic_region[16][i].y + 16; j++)
        {
            for (int k = quadratic_region[16][i].x; k < quadratic_region[16][i].x + 16; k++)
            {
                if (setted_quadratic_region.squares[j][k].hasResource == 8)
                    total += quadratic_region[8][j].cost;
            }


        }

        if (total > quadratic_region[16][i].cost) {

            paint_quads(quadratic_region[16][i].x, quadratic_region[16][i].y, 16, polygon);

        }

    }

}


//optimization ve set_quads fonksiyonlarını birleştirir.
void optimization_and_setquads(struct polygon* polygon)
{
    for (int i = 16; i >= 1; i /= 2) {
        set_quads(*polygon, i);
    }
    optimization(polygon);
    
}



//Çokgenlerin alanlarını ve rezerv değerlerini hesaplar.
void calculate_polygons(struct polygon polygon)
{
    int squarres1x1 = 0;
    int squarres2x2 = 0;
    int squarres4x4 = 0;
    int squarres8x8 = 0;
    int squarres16x16 = 0;
    for (int y = polygon.polygonLimit.miny; y < polygon.polygonLimit.maxy; y++)
    {
        for (int x = polygon.polygonLimit.minx; x < polygon.polygonLimit.maxx; x++)
        {
            if (polygon.areaSpace.squares[y][x].hasResource == 1) squarres1x1++;
            if (polygon.areaSpace.squares[y][x].hasResource == 2) squarres2x2++;
            if (polygon.areaSpace.squares[y][x].hasResource == 4) squarres4x4++;
            if (polygon.areaSpace.squares[y][x].hasResource == 8) squarres8x8++;
            if (polygon.areaSpace.squares[y][x].hasResource == 16) squarres16x16++;
        }
    }
    line[selected_line].platform_area += squarres1x1 + squarres2x2 + squarres4x4 + squarres8x8 + squarres16x16;
    squarres2x2 /= 4;
    squarres4x4 /= 16;
    squarres8x8 /= 64;
    squarres16x16 /= 256;
    int platform_numbers = squarres1x1 + squarres2x2 + squarres4x4 + squarres8x8 + squarres16x16;

    line[selected_line].platfrom_numbers += platform_numbers;

}





//Kareli düzlemi çizen fonksiyon
void drawGrid(int size, int step) {
    glColor4f(0.0, 0.0, 0.0, 0.5);
    glLineWidth(0.5);

    for (int i = -size; i <= size; i += step) {
        glBegin(GL_LINES);
        glVertex2f(i, size);
        glVertex2f(i, -size);
        glVertex2f(-size, i);
        glVertex2f(size, i);
        glEnd();
    }
}
//Ekranı yeniden boyutlandırma fonksiyonu
void setupView(int width, int height) {

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, gridSize, gridSize * (GLfloat)height / (GLfloat)width, 0, -20, 20);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}



//Ana Ekran Fonksiyonu
void display()
{
    //Ekranı ve arkaplanı temizleme
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);

    //Ekranlar arası geçiş (iscreen1)
    if (isScreen1) {
        //Kareleri boyar ve alanı hesaplar
        for (int i = 0; i < line[selected_line].polygon_number; i++) {
            paint_polygon_area(&line[selected_line].polygon[i]);
        }


        //Şeklin kenarlarını çizer

        for (int i = 0; i < line[selected_line].polygon_number; i++) {
            drawlines(line[selected_line].polygon[i]);
        }
        //koordinat düzlemi çizimi
        drawGrid(gridSize, 1);

        //Rezerv değerini hesaplama
        int total_field = 0;
        for (int i = 0; i < line[selected_line].polygon_number; i++) {
            total_field += line[selected_line].polygon[i].area;
        }
        if (!onceStart1)
        {
            printf("Rezerv Degeri : %d\n", total_field * 10);
            line[selected_line].reserve_area = total_field * 10;
            onceStart1 = true;
        }
    }
    else
    {
        for (int i = 0; i < line[selected_line].polygon_number; i++) {
            paint_polygon_area(&line[selected_line].polygon[i]);
            optimization_and_setquads(&line[selected_line].polygon[i]);
        }


        for (int i = 0; i < line[selected_line].polygon_number; i++) {
            drawlines(line[selected_line].polygon[i]);

        }

        if (!onceStart2)
        {
            for (int i = 0; i < line[selected_line].polygon_number; i++)
            {
                calculate_polygons(line[selected_line].polygon[i]);
            }
            printf("\n---------------------------------------------------------------\n");

            printf("platform sayisi: %d\n", line[selected_line].platfrom_numbers);
            printf("platformlarin alani: %d\n", line[selected_line].platform_area);
            int total_drill_cost = line[selected_line].platform_area * drill_cost;
            int total_platform_cost = line[selected_line].platfrom_numbers * platform_cost;
            printf("total sondaj maliyeti : %d\n", total_drill_cost);
            printf("total platform maliyeti : %d\n", total_platform_cost);
            printf("total maliyet : %d\n", (total_drill_cost + total_platform_cost));
            printf("Kar miktari : %d\n", (line[selected_line].reserve_area - (total_drill_cost + total_platform_cost)));

            onceStart2 = true;
        }
        drawGrid(gridSize, 1);
    }
    //Ekranı güncelleme
    glutSwapBuffers();
}


//Klavye dinleme fonksiyonu

void keyTrigger(unsigned char key, int x, int y) {
    
    //Ekranlar arası geçiş
    switch (key)
    {
    case '1':
        isScreen1 = true;
        glutPostRedisplay(); //Ekranı güncelleme
        break;
    case '2':
        isScreen1 = false;
        glutPostRedisplay();
        break;
    }

}



//CURL FONKSIYONLARI
//size_t kullanmamızın sebebi kodun farklı platformlarda doğru çalışmasını ve bellek yönetiminin tutarlı olmasını sağlar.
size_t WriteCallBack(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t realsize = size * nmemb;
    char* data = (char*)userp;

    memcpy(data, contents, realsize);

    data[realsize] = '\0';

    return realsize;
}

char* GetWebData(const char* url)
{
    CURL* curl;
    CURLcode res;
    char* data = NULL;

    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);

        // Veri alımındaki işlevi ayarla
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallBack);

        // Bellek tahsisi yap
        data = (char*)malloc(4096);

        // Alınan veriyi dataya aktar
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, data);

        // Sonucun yapısı
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        curl_easy_cleanup(curl);
    }

    return data;
}





int main(int argc, char** argv)
{
    while (1)
    {
        printf("Satir numarasi giriniz:");
        scanf("%d", &selected_line);
        if (selected_line > 0)break;
        printf("Satir sayisi 0'dan kucuk olamaz\n");
    }

    while (1)
    {
        printf("Sondaj maliyetini giriniz:");
        scanf("%d", &drill_cost);
        if (drill_cost <= 10 && drill_cost >= 0) break;
        if (drill_cost > 10) printf("Sondaj maliyeti 10'dan buyuk olamaz\n");
        if (drill_cost < 0) printf("Sondaj maliyeti 0'dan kucuk olamaz\n");

    }
    while (1)
    {
        printf("Platform Maliyetini giriniz:");
        scanf("%d", &platform_cost);
        if (platform_cost >= 0) break;
        printf("Platform maliyeti sifirdan kucuk olamaz\n");
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1200, 900);
    glutInitWindowPosition(700, 1);
    glutCreateWindow("Prolab 1");
    glClearColor(1.0, 1.0, 1.0, 1.0);

    selected_line--;
    //Web sitesi linki
    const char* url = "https://bilgisayar.kocaeli.edu.tr/prolab1/prolab1.txt";

    char* data = GetWebData(url);

    char lines[99][100];

    int line_number = 0;
    if (data) {
        splitLine(data, lines, &line_number);
    }
    glutReshapeFunc(setupView);
    parseCoordinates(lines[selected_line], &line[selected_line]);

    //klavye dinleme fonksiyonu
    glutKeyboardFunc(keyTrigger);
    glutDisplayFunc(display);


    glutMainLoop();


    return 0;
}