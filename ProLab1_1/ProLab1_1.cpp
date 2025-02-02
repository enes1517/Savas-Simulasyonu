#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 256
#define MAX_UNITS 20
#include<curl/curl.h>
#include <GL/glut.h>

#define GRID_SIZE 20
#define MAX_UNITS_PER_CELL 100

#define MAX_URL_LENGTH 256
#define MAX_URLS 10






//     230202068 HÜSEYİN ENES İPEK               230202075 MERVAN ELBAHADIR




//global degiskenler
int g1 = 0;
int g2 = 0;
int g3 = 0;
int g4 = 0;
int g5 = 0;
int g6 = 0;
int g7 = 0;
int g8 = 0;


int g1Son = 0;
int g2Son = 0;
int g3Son = 0;
int g4Son = 0;
int g5Son = 0;
int g6Son = 0;
int g7Son = 0;
int g8Son = 0;


double g1SonSaglik = 0;
double g2SonSaglik = 0;
double g3SonSaglik = 0;
double g4SonSaglik = 0;
double g5SonSaglik = 0;
double g6SonSaglik = 0;
double g7SonSaglik = 0;
double g8SonSaglik = 0;

double g1ilkSaglik1 = 0;
double g2ilkSaglik2 = 0.0;
double g3ilkSaglik3 = 0.0;
double g4ilkSaglik4 = 0.0;
double g5ilkSaglik5 = 0.0;
double g6ilkSaglik6 = 0.0;
double g7ilkSaglik7 = 0.0;
double g8ilkSaglik8 = 0.0;

double saglikOrta1 = 0;

double saglikOrta2 = 0;
double saglikOrta3 = 0;

double saglikOrta4 = 0;

double saglikOrta5 = 0;
double saglikOrta6 = 0;
double saglikOrta7 =0;
double saglikOrta8 = 0;

//yapılan degişiklik saglıklarada / kişi sayısını eklemeek








const char* secilenURL(int secim) {
    switch (secim) {
    case 1: return "https://yapbenzet.org.tr/1.json";
    case 2: return "https://yapbenzet.org.tr/2.json";
    case 3: return "https://yapbenzet.org.tr/3.json";
    case 4: return "https://yapbenzet.org.tr/4.json";
    case 5: return "https://yapbenzet.org.tr/5.json";
    case 6: return "https://bilgisayar.kocaeli.edu.tr/1.json";
    case 7: return "https://bilgisayar.kocaeli.edu.tr/2.json";
    case 8: return "https://bilgisayar.kocaeli.edu.tr/3.json";
    case 9: return "https://bilgisayar.kocaeli.edu.tr/4.json";
    case 10: return "https://bilgisayar.kocaeli.edu.tr/5.json";
    default: return NULL; // Geçersiz seçim için NULL döndür
    }
}

// Dosyaya veri yazma fonksiyonu
size_t write_data(void* ptr, size_t size, size_t nmemb, FILE* stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

// Verilen URL'den dosya indiren fonksiyon
void dosyaIndir(const char* url, const char* dosyaAdi) {
    CURL* curl;
    FILE* fp;
    CURLcode res;

    curl = curl_easy_init(); // CURL oturumu başlat
    if (curl) {
        fp = fopen(dosyaAdi, "wb"); // Dosyayı yazma modunda aç
        curl_easy_setopt(curl, CURLOPT_URL, url); // URL'yi ayarla
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data); // Yazma fonksiyonunu ayarla
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp); // Dosya işaretçisini ayarla
        res = curl_easy_perform(curl); // İsteği gerçekleştir
        if (res != CURLE_OK) {
            fprintf(stderr, "curl hata: %s\n", curl_easy_strerror(res));
        }
        fclose(fp); // Dosyayı kapat
        curl_easy_cleanup(curl); // CURL oturumunu kapat
    }
    else {
        fprintf(stderr, "CURL başlatılamadı.\n");
    }
}











// Birim yapısı
typedef struct {
    char name[MAX_LEN];
    int attack;
    int defense;
    int health;
    int critical_chance;
} birim;






typedef struct
{
    birim birim;

}birimPiyade;
typedef struct
{
    birim birim;

}birimokcu;
typedef struct
{
    birim birim;

}birimSuvari;
typedef struct
{
    birim birim;

}birimKusatma;
typedef struct
{
    birim birim;

}birimorkdovucsu;
typedef struct
{
    birim birim;

}birimMizrakci;
typedef struct
{
    birim birim;

}birimVargBinici;
typedef struct
{
    birim birim;

}birimTrol;





typedef struct
{
    char CanavarAd[MAX_LEN];
    int etki_degeri;
    char etki_turu[MAX_LEN];
    char etki_alani[MAX_LEN];


}Canavar;

void ParseEtkiledigi_Birim(char* aciklama, char* etki_alani)
{
    if (strstr(aciklama, "piyadelerin") != NULL)
    {
        strcpy(etki_alani, "piyadeler");
    }
    else if (strstr(aciklama, "suvarilere") != NULL)
    {
        strcpy(etki_alani, "suvariler");
    }
    else if (strstr(aciklama, "okculara") != NULL)
    {
        strcpy(etki_alani, "okcular");
    }
    else if (strstr(aciklama, "trollerin") != NULL)
    {
        strcpy(etki_alani, "troller");
    }
    else if (strstr(aciklama, "varg_binicilerine") != NULL)
    {
        strcpy(etki_alani, "varg_binicileri");
    }
    else if (strstr(aciklama, "ork_dovusculerine") != NULL)
    {
        strcpy(etki_alani, "ork_dovusculeri");
    }
    else if (strstr(aciklama, "suvarilerinin") != NULL)
    {
        strcpy(etki_alani, "suvariler");
    }
    else if (strstr(aciklama, "Trollerin") != NULL)
    {
        strcpy(etki_alani, "Troller");
    }
    else if (strstr(aciklama, "mizrakcilarin") != NULL)
    {
        strcpy(etki_alani, "mizrakcilar");
    }
    else if (strstr(aciklama, "varg_binicilerin") != NULL)
    {
        strcpy(etki_alani, "varg_binicileri");
    }

}

//canavar verileri

void ParseJason(FILE* file, Canavar Canavarlar[], int* CanavarSayisi)
{
    char line[MAX_LEN];
    char current_key[MAX_LEN];
    while (fgets(line, sizeof(line), file))
    {

        if (strstr(line, "\"etki_degeri\":") != NULL)
        {
            sscanf(line, " \"etki_degeri\": \"%d\",", &Canavarlar[*CanavarSayisi].etki_degeri);
        }
        else  if (strstr(line, "\"etki_turu\":") != NULL)
        {
            sscanf(line, " \"etki_turu\": \"%[^\"]\",", Canavarlar[*CanavarSayisi].etki_turu);
        }

        else if (strstr(line, "\"aciklama\":") != NULL)
        {
            // Açıklama kısmından etkilediği birimi çek
            char aciklama[MAX_LEN];
            sscanf(line, " \"aciklama\": \"%[^\"]\"", aciklama);
            ParseEtkiledigi_Birim(aciklama, Canavarlar[*CanavarSayisi].etki_alani);


        }

        else if (strstr(line, ": {") != NULL)
        {
            // Birim adını yakala
            sscanf(line, " \"%[^\"]\": {", current_key);
            strcpy(Canavarlar[*CanavarSayisi].CanavarAd, current_key);

        }

        if (Canavarlar[*CanavarSayisi].etki_degeri == 0)
            continue;


        if (strstr(line, "}"))
            (*CanavarSayisi)++;




    }

}

// unit type verileri

// Dosya açma ve satır satır okuma
void parse_json(FILE* file, birim birimler[], int* birimSayisi) {
    char line[MAX_LEN];
    char current_key[MAX_LEN]; // Geçerli anahtarı saklamak için

    while (fgets(line, sizeof(line), file)) {
        // Anahtar değeri içeriyorsa

        if (strstr(line, "\"saldiri\":") != NULL) {
            sscanf(line, " \"saldiri\": %d,", &birimler[*birimSayisi].attack);
        }
        else if (strstr(line, "\"savunma\":") != NULL) {
            sscanf(line, " \"savunma\": %d,", &birimler[*birimSayisi].defense);
        }
        else if (strstr(line, "\"saglik\":") != NULL) {
            sscanf(line, " \"saglik\": %d,", &birimler[*birimSayisi].health);
        }
        else if (strstr(line, "\"kritik_sans\":") != NULL) {
            sscanf(line, " \"kritik_sans\": %d,", &birimler[*birimSayisi].critical_chance);
        }
        else if (strstr(line, ": {") != NULL) {
            // Birim adını yakala
            sscanf(line, " \"%[^\"]\": {", current_key);
            strcpy(birimler[*birimSayisi].name, current_key);
        }
        if (birimler[*birimSayisi].defense == 0 && birimler[*birimSayisi].critical_chance == 0) {
            continue;
        }

        // Birim bitiminde birim sayacını artır
        if (strstr(line, "}") != NULL && *birimSayisi < MAX_UNITS) {
            (*birimSayisi)++;
        }

    }

}




typedef struct {
    char yetenekAdi[MAX_LEN];   // Yetenek adını saklamak için yeni alan
    int seviye;                 // Seviye alanını int türüne çevirdik
    int deger;
    char etkiledigi_birim[MAX_LEN];
} Yetenek;






void parse_etkiledigi_birim(const char* aciklama, char* etkiledigi_birim) {
    if (strstr(aciklama, "tum_birimlerin") != NULL) {
        strcpy(etkiledigi_birim, "tum_birimler");
    }
    else if (strstr(aciklama, "kusatma_makinelerinin") != NULL)
    {
        strcpy(etkiledigi_birim, "kusatma_makineleri");
    }


}

//arastirma verileri

void ParseJson(FILE* file, Yetenek Yetenekler[], int* YetenekSayisi) {
    char line[MAX_LEN];
    char current_key[MAX_LEN];
    char current_yetenekAdi[MAX_LEN] = "";

    while (fgets(line, sizeof(line), file)) {

        if (strstr(line, ": {") != NULL && !strstr(line, "seviye_")) {
            sscanf(line, " \"%[^\"]\": {", current_yetenekAdi);
        }

        if (strstr(line, "\"deger\":") != NULL) {
            sscanf(line, " \"deger\": \"%d\",", &Yetenekler[*YetenekSayisi].deger);
        }
        else if (strstr(line, "\"aciklama\":") != NULL) {
            char aciklama[MAX_LEN];
            sscanf(line, " \"aciklama\": \"%[^\"]\"", aciklama);
            parse_etkiledigi_birim(aciklama, Yetenekler[*YetenekSayisi].etkiledigi_birim);
        }
        else if (strstr(line, "seviye_") != NULL) {
            int seviye;
            sscanf(line, " \"%[^\"]\": {", current_key);
            sscanf(current_key, "seviye_%d", &seviye);  
            Yetenekler[*YetenekSayisi].seviye = seviye;
            strcpy(Yetenekler[*YetenekSayisi].yetenekAdi, current_yetenekAdi);  
        }

        if (Yetenekler[*YetenekSayisi].deger == 0) {
            continue;
        }

        if (strstr(line, "}") != NULL && *YetenekSayisi < MAX_UNITS) {
            (*YetenekSayisi)++;
        }
    }

}



typedef struct
{
    char kahramanAd[MAX_LEN];
    char bonus_turu[MAX_LEN];
    int bonus_degeri;
    char etki_alani[MAX_LEN];


}Kahraman;

void Parse_etkiledigi_birim(const char* aciklama, char* etki_alani) {
    if (strstr(aciklama, "piyadelere") != NULL) {
        strcpy(etki_alani, "piyadeler");
    }
    else if (strstr(aciklama, "okcularin") != NULL) {
        strcpy(etki_alani, "okcular");
    }
    else if (strstr(aciklama, "suvarilere") != NULL) {
        strcpy(etki_alani, "suvariler");
    }
    else if (strstr(aciklama, "kusatma_makinelerinin") != NULL) {
        strcpy(etki_alani, "kusatma_makineleri");
    }
    else if (strstr(aciklama, "trollerin") != NULL)
    {
        strcpy(etki_alani, "troller");
    }
    else if (strstr(aciklama, "varg_binicilerine") != NULL)
    {
        strcpy(etki_alani, "varg_binicileri");
    }
    else if (strstr(aciklama, "tum_birimlere") != NULL)
    {
        strcpy(etki_alani, "tum_birimler");
    }
    else if (strstr(aciklama, "ork_dovusculerine") != NULL)
    {
        strcpy(etki_alani, "ork_dovusculeri");
    }
    else if (strstr(aciklama, "varg_binicilerin") != NULL)
    {
        strcpy(etki_alani, "varg_binicileri");
    }

}


// kahraman verileri

void parseJason(FILE* file, Kahraman Kahramanlar[], int* KahramanSayisi) {
    char line[MAX_LEN];
    char current_key[MAX_LEN];

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "\"bonus_turu\":") != NULL) {
            sscanf(line, " \"bonus_turu\": \"%[^\"]\",", Kahramanlar[*KahramanSayisi].bonus_turu);
        }
        else if (strstr(line, "\"bonus_degeri\":") != NULL) {
            sscanf(line, " \"bonus_degeri\": \"%d\",", &Kahramanlar[*KahramanSayisi].bonus_degeri);
        }
        else if (strstr(line, "\"aciklama\":") != NULL) {
            // Açıklama kısmından etkilediği birimi çek
            char aciklama[MAX_LEN];
            sscanf(line, " \"aciklama\": \"%[^\"]\"", aciklama);
            Parse_etkiledigi_birim(aciklama, Kahramanlar[*KahramanSayisi].etki_alani);
        }
        else if (strstr(line, ": {") != NULL) {
            // Birim adını yakala
            sscanf(line, " \"%[^\"]\": {", current_key);
            strcpy(Kahramanlar[*KahramanSayisi].kahramanAd, current_key);
        }
        if (Kahramanlar[*KahramanSayisi].bonus_degeri == 0) {
            continue;
        }

        // Birim bitiminde birim sayacını artır
        if (strstr(line, "}") != NULL && *KahramanSayisi < MAX_UNITS) {
            (*KahramanSayisi)++;
        }
    }

}



typedef struct
{
    int piyadeler;
    int okcular;
    int kusatma_makineleri;
    int troller;
    int varg_binicileri;
    int ork_dovusculeri;
    int suvariler;
    int mizrakcilar;

}SeneryoBirim;




void parse_jsonBirim(FILE* file, SeneryoBirim SeneryoBirim[], int* SeneryoSayisi) {

    // Geçerli anahtarı saklamak için
    char line[MAX_LEN];
    while (fgets(line, sizeof(line), file)) {
        // Anahtar değeri içeriyorsa

        if (strstr(line, "\"piyadeler\":") != NULL) {
            sscanf(line, " \"piyadeler\": %d,", &SeneryoBirim[*SeneryoSayisi].piyadeler);
        }
        if (strstr(line, "\"okcular\":") != NULL) {
            sscanf(line, " \"okcular\": %d,", &SeneryoBirim[*SeneryoSayisi].okcular);
        }  if (strstr(line, "\"kusatma_makineleri\":") != NULL) {
            sscanf(line, " \"kusatma_makineleri\": %d,", &SeneryoBirim[*SeneryoSayisi].kusatma_makineleri);
        }  if (strstr(line, "\"troller\":") != NULL) {
            sscanf(line, " \"troller\": %d,", &SeneryoBirim[*SeneryoSayisi].troller);
        }
        if (strstr(line, "\"varg_binicileri\":") != NULL) {
            sscanf(line, " \"varg_binicileri\": %d,", &SeneryoBirim[*SeneryoSayisi].varg_binicileri);
        }
        if (strstr(line, "\"ork_dovusculeri\":") != NULL) {
            sscanf(line, " \"ork_dovusculeri\": %d,", &SeneryoBirim[*SeneryoSayisi].ork_dovusculeri);
        }
        if (strstr(line, "\"mizrakcilar\":") != NULL) {
            sscanf(line, " \"mizrakcilar\": %d,", &SeneryoBirim[*SeneryoSayisi].mizrakcilar);
        }
        if (strstr(line, "\"suvariler\":") != NULL) {
            sscanf(line, " \"suvariler\": %d,", &SeneryoBirim[*SeneryoSayisi].suvariler);
        }

    }

}







typedef struct
{
    char kahraman[50];
    char Canavar[50];
    char yetenekAd[MAX_LEN];
    int seviye;
    int elit_egitim;
    int savunma_ustaligi;
    int saldiri_gelistirmesi;
    int kusatma_ustaligi;


}SeneryoCek;








void ParseAJson(FILE* file0, SeneryoCek SeneryoCek[], int* YetenekSayisi) {
    char line[MAX_LEN];


    while (fgets(line, sizeof(line), file0)) {
        // Yetenek adını yakala (örneğin, "savunma_ustaligi", "saldiri_gelistirmesi")


        if (strstr(line, "\"savunma_ustaligi\":") != NULL) {
            sscanf(line, " \"savunma_ustaligi\": %d,", &SeneryoCek[*YetenekSayisi].savunma_ustaligi);
        }

        else  if (strstr(line, "\"elit_egitim\":") != NULL) {
            sscanf(line, " \"elit_egitim\": %d,", &SeneryoCek[*YetenekSayisi].elit_egitim);
        }

        else if (strstr(line, "\"saldiri_gelistirmesi\":") != NULL) {
            sscanf(line, " \"saldiri_gelistirmesi\": %d,", &SeneryoCek[*YetenekSayisi].saldiri_gelistirmesi);
        }
        else if (strstr(line, "\"kusatma_ustaligi\":") != NULL) {
            sscanf(line, " \"kusatma_ustaligi\": %d,", &SeneryoCek[*YetenekSayisi].kusatma_ustaligi);
        }




    }
    (*YetenekSayisi) = (*YetenekSayisi) + 1;
}



// Tüm birim tiplerini enum olarak tanımlayalım
enum UnitTypes {
    BOS = 0,
    ORK_DOVUSCULERI = 1,
    MIZRAKCILAR = 2,
    VARG_BINICILERI = 3,
    TROLLER = 4,
    KUSATMA_MAKINELERI = 5,
    PIYADE = 6,
    OKCU = 7,
    SUVARI = 8
};

typedef struct {
    int type;
    int count;
    float health;
} Cell;

Cell grid[GRID_SIZE][GRID_SIZE];
int currentScreen = 1; // 1, 2 veya 3 olabilir

void init() {
    glClearColor(0.9, 0.9, 0.9, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, GRID_SIZE, 0, GRID_SIZE);
}

void drawCell(int x, int y) {
    Cell cell = grid[y][x];

    float colors[9][3] = {
        {0.9, 0.9, 0.9},  // Boş
        {0.7, 0.2, 0.2},  // Ork Dövüşçüleri
        {0.2, 0.5, 0.8},  // Mızrakçılar
        {0.8, 0.4, 0.0},  // Varg Binicileri
        {0.5, 0.5, 0.0},  // Troller
        {0.4, 0.4, 0.4},  // Kuşatma Makineleri
        {0.2, 0.6, 1.0},  // Piyade
        {0.4, 0.8, 0.4},  // Okçu
        {1.0, 0.4, 0.4}   // Süvari
    };

    glColor3fv(colors[cell.type]);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + 1, y);
    glVertex2f(x + 1, y + 1);
    glVertex2f(x, y + 1);
    glEnd();

    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + 1, y);
    glVertex2f(x + 1, y + 1);
    glVertex2f(x, y + 1);
    glEnd();

    if (cell.type != 0) {

        glColor3f(1.0 - (cell.health / 2.0), cell.health / 2.0, 0.0);
        glBegin(GL_QUADS);
        glVertex2f(x, y + 0.9);
        glVertex2f(x + (cell.health / 2.0), y + 0.9);
        glVertex2f(x + (cell.health / 2.0), y + 1.0);
        glVertex2f(x, y + 1.0);
        glEnd();

        glColor3f(1.0, 1.0, 1.0);
        glRasterPos2f(x + 0.1, y + 0.1);
        char str[10];
        snprintf(str, 10, "%d", cell.count);
        for (char* c = str; *c != '\0'; c++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
        }

        char unitLetter = ' ';
        switch (cell.type) {
        case ORK_DOVUSCULERI: unitLetter = 'O'; break;
        case MIZRAKCILAR: unitLetter = 'M'; break;
        case VARG_BINICILERI: unitLetter = 'V'; break;
        case TROLLER: unitLetter = 'T'; break;
        case KUSATMA_MAKINELERI: unitLetter = 'K'; break;
        case PIYADE: unitLetter = 'P'; break;
        case OKCU: unitLetter = 'A'; break;
        case SUVARI: unitLetter = 'S'; break;
        }
        glRasterPos2f(x + 0.8, y + 0.8);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, unitLetter);
    }
}
int ta=5;
void drawGrid() {
    glColor3f(0.7, 0.7, 0.7);
    glBegin(GL_LINES);

    for (int i = 0; i <= GRID_SIZE; i++) {
        glVertex2f(i, 0);
        glVertex2f(i, GRID_SIZE);
        glVertex2f(0, i);
        glVertex2f(GRID_SIZE, i);
    }

    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(GRID_SIZE / 2, 0);
    glVertex2f(GRID_SIZE / 2, GRID_SIZE);

    glEnd();
}

void placeUnits(int type, int count, int startX, int startY, float initialHealth) {
    int x = startX, y = startY;

    // Sağlık değerini sınırlandır
    if (initialHealth < 0.0) initialHealth = 0.0;
    if (initialHealth > 2.0) initialHealth = 2.0;

    while (count > 0) {
        if (grid[y][x].type == 0 || grid[y][x].type == type) {
            int place = (count > MAX_UNITS_PER_CELL) ? MAX_UNITS_PER_CELL : count;
            grid[y][x].type = type;
            grid[y][x].count += place;
            grid[y][x].health = initialHealth;
            count -= place;
        }

        x++;
        if (x >= GRID_SIZE) {
            x = 0;
            y++;
            if (y >= GRID_SIZE) y = 0;
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    for (int y = 0; y < GRID_SIZE; y++) {
        for (int x = 0; x < GRID_SIZE; x++) {
            drawCell(x, y);
        }
    }

    drawGrid();
    glFlush();

    // Ekran numarasını göster
    glColor3f(0.0, 0.0, 0.0);
    glRasterPos2f(1, GRID_SIZE - 1);
    char str[20];
    snprintf(str, 20, "Ekran %d", currentScreen);
    for (char* c = str; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}



int main(int argc, char** argv) {



    int secim;
    char dosyaAdi[50]; // Dosya adı için karakter dizisi

    printf("1 ile 10 arasında bir sayı seçiniz: ");
    scanf("%d", &secim);

    const char* url = secilenURL(secim);
    if (url == NULL) {
        printf("Geçersiz seçim! Lütfen 1 ile 10 arasında bir sayı girin.\n");
        return 1;
    }

    // Dosya adını oluşturma (örn: indirilen_dosya_3.json)
    sprintf(dosyaAdi, "indirilen_dosya_%d.json", secim);

    // İndirilen dosyanın adını ekrana yazdır
    printf("Dosya indiriliyor: %s\n", dosyaAdi);

    dosyaIndir(url, dosyaAdi); // Dosyayı indir
    printf("Dosya başarıyla indirildi: %s\n", dosyaAdi);





    char a[MAX_LEN] = "senaryo_%d.json";

    char FileName[MAX_LEN];
    char line[256];
    SeneryoCek SeneryoCek[MAX_LEN];
    strcpy(FileName, dosyaAdi);
    SeneryoBirim SeneryoBirim[MAX_LEN];
    birim birimler[MAX_UNITS];
    Canavar Canavarlar[MAX_UNITS];
    Yetenek Yetenekler[MAX_UNITS];
    Kahraman Kahramanlar[MAX_UNITS];



    for (int i = 0; i < 1; i++) {
        SeneryoBirim[i].piyadeler = 0;
        SeneryoBirim[i].okcular = 0;
        SeneryoBirim[i].kusatma_makineleri = 0;
        SeneryoBirim[i].troller = 0;
        SeneryoBirim[i].varg_binicileri = 0;
        SeneryoBirim[i].ork_dovusculeri = 0;
        SeneryoBirim[i].suvariler = 0;
        SeneryoBirim[i].mizrakcilar = 0;

    }

    for (int i = 0; i < 15; i++) {
        strcpy(SeneryoCek[i].kahraman, "");
        strcpy(SeneryoCek[i].Canavar, "");
        strcpy(SeneryoCek[i].yetenekAd, "");
        SeneryoCek[i].seviye = 0;
        SeneryoCek[i].elit_egitim = 0;
        SeneryoCek[i].savunma_ustaligi = 0;
        SeneryoCek[i].saldiri_gelistirmesi = 0;
        SeneryoCek[i].kusatma_ustaligi = 0;
        Kahramanlar[i].bonus_degeri = 0;
        strcpy(Kahramanlar[i].kahramanAd, "");
        strcpy(Kahramanlar[i].bonus_turu, "");
        strcpy(Kahramanlar[i].etki_alani, "");
    }

    for (int i = 0; i < 12; i++) {
        strcpy(Yetenekler[i].yetenekAdi, "");
        Yetenekler[i].seviye = 0;
        Yetenekler[i].deger = 0;
        strcpy(Yetenekler[i].etkiledigi_birim, "");
    }
    for (int i = 0; i < MAX_UNITS; i++) {
        strcpy(birimler[i].name, "");
        birimler[i].attack = 0;
        birimler[i].defense = 0;
        birimler[i].health = 0;
        birimler[i].critical_chance = 0;
    }

    // Canavar yapısını sıfırlama
    for (int i = 0; i < MAX_UNITS; i++) {
        strcpy(Canavarlar[i].CanavarAd, "");
        Canavarlar[i].etki_degeri = 0;
        strcpy(Canavarlar[i].etki_turu, "");
        strcpy(Canavarlar[i].etki_alani, "");
    }






    printf("\n1.adim\n4.adim\nson adim");




    int Sayisi = 0;

    int YetenekSayisi = 0;

    FILE* file0 = fopen(FileName, "r");
    if (file0 == NULL) {
        printf("Dosya açılamadı!\n");
        return 1;
    }

    ParseAJson(file0, SeneryoCek, &Sayisi);



   


    fclose(file0);




    FILE* dosya;



    // Dosyayı okuma modunda aç
    dosya = fopen(FileName, "r");

    if (dosya == NULL) {
        printf("Dosya açılamadı.%s\n", FileName);
        return 1;
    }


    for (int i = 0; i < 2; i++)
    {
        while (fgets(line, sizeof(line), dosya)) {
            // "kahramanlar" alanını bulduğumuz satırı kontrol et
            if (strstr(line, "\"kahramanlar\":") != NULL) {
                // Kahraman isimlerini tırnaklar olmadan ayıkla
                sscanf(line, " \"kahramanlar\": [\"%[^\"]\",", &SeneryoCek[i].kahraman);
                i++;
            }
        }




    }
    fclose(dosya);



    FILE* dosya1 = fopen(FileName, "r");

    if (dosya1 == NULL) {
        printf("Dosya açılamadı.\n");
        return 1;
    }


    for (int i = 0; i < 2; i++)
    {

        while (fgets(line, sizeof(line), dosya)) {
            // "kahramanlar" alanını bulduğumuz satırı kontrol et
            if (strstr(line, "\"canavarlar\":") != NULL) {
                // Kahraman isimlerini tırnaklar olmadan ayıkla
                sscanf(line, " \"canavarlar\": [ \"%[^\"]\", ", SeneryoCek[i].Canavar);
                i++;
            }


        }
    }
    fclose(dosya1);











    // Dosyayı satır satır oku


    int sayi = 0;
    FILE* file = fopen(FileName, "r");
    if (file == NULL) {
        printf("Dosya açılamadı!\n");
        return 1;
    }

    // JSON dosyasını ayrıştır
    parse_jsonBirim(file, SeneryoBirim, &sayi);

    fclose(file);
    
    




    // Birimler için dizi
    int birimSayisi = 0;

    // JSON dosyasını açma
    FILE* file5 = fopen("C:\\Users\\HP\\source\\repos\\ProLab1_1\\ProLab1_1\\Files\\unit_types.json", "r");
    if (file5 == NULL) {
        printf("unit_types.json bulunamadi\n");
        return 1;
    }

    // JSON dosyasını ayrıştır
    parse_json(file5, birimler, &birimSayisi);

    fclose(file5);




    int CanavarSayisi = 0;

    FILE* file1 = fopen("C:\\Users\\HP\\source\\repos\\ProLab1_1\\ProLab1_1\\Files\\creatures.json", "r");
    if (file1 == NULL)
    {
        printf("cretures.json bulunamadi\n");
        return 1;
    }

    ParseJason(file1, Canavarlar, &CanavarSayisi);
    fclose(file1);



    YetenekSayisi = 0;

    FILE* file9 = fopen("C:\\Users\\HP\\source\\repos\\ProLab1_1\\ProLab1_1\\Files\\research.json", "r");
    if (file9 == NULL) {
        printf("reserch.json bulunamadi\n");
        return 1;
    }

    ParseJson(file9, Yetenekler, &YetenekSayisi);

    fclose(file9);




    // Birimler için dizi
    int KahramanSayisi = 0;

    // JSON dosyasını açma
    FILE* file3 = fopen("C:\\Users\\HP\\source\\repos\\ProLab1_1\\ProLab1_1\\Files\\heroes.json", "r");
    if (file3 == NULL) {
        printf("heroes.json bulunamadi\n");
        return 1;
    }

    // JSON dosyasını ayrıştır
    parseJason(file3, Kahramanlar, &KahramanSayisi);

    fclose(file3);



    // AtamalarBirim//
    int i = 0;
    birimPiyade birimPiyade;
    birimKusatma birimKusatma;
    birimokcu birimokcu;
    birimMizrakci birimMizrakci;
    birimorkdovucsu birimorkdovucsu;
    birimTrol birimTrol;
    birimSuvari birimSuvari;
    birimVargBinici birimVargBinici;


    birimPiyade.birim.attack = birimler[i].attack;
    birimPiyade.birim.defense = birimler[i].defense;
    birimPiyade.birim.health = birimler[i].health;
    birimPiyade.birim.critical_chance = birimler[i].critical_chance;


    i++;
    birimokcu.birim.attack = birimler[i].attack;
    birimokcu.birim.defense = birimler[i].defense;
    birimokcu.birim.health = birimler[i].health;
    birimokcu.birim.critical_chance = birimler[i].critical_chance;
    i++;
    birimSuvari.birim.attack = birimler[i].attack;
    birimSuvari.birim.defense = birimler[i].defense;
    birimSuvari.birim.health = birimler[i].health;
    birimSuvari.birim.critical_chance = birimler[i].critical_chance;
    i++;
    birimKusatma.birim.attack = birimler[i].attack;
    birimKusatma.birim.defense = birimler[i].defense;
    birimKusatma.birim.health = birimler[i].health;
    birimKusatma.birim.critical_chance = birimler[i].critical_chance;
    i++;
    birimorkdovucsu.birim.attack = birimler[i].attack;
    birimorkdovucsu.birim.defense = birimler[i].defense;
    birimorkdovucsu.birim.health = birimler[i].health;
    birimorkdovucsu.birim.critical_chance = birimler[i].critical_chance;
    i++;
    birimMizrakci.birim.attack = birimler[i].attack;
    birimMizrakci.birim.defense = birimler[i].defense;
    birimMizrakci.birim.health = birimler[i].health;
    birimMizrakci.birim.critical_chance = birimler[i].critical_chance;
    i++;
    birimVargBinici.birim.attack = birimler[i].attack;
    birimVargBinici.birim.defense = birimler[i].defense;
    birimVargBinici.birim.health = birimler[i].health;
    birimVargBinici.birim.critical_chance = birimler[i].critical_chance;
    i++;
    birimTrol.birim.attack = birimler[i].attack;
    birimTrol.birim.defense = birimler[i].defense;
    birimTrol.birim.health = birimler[i].health;
    birimTrol.birim.critical_chance = birimler[i].critical_chance;


    // toplam saldırı//
    double TopSaldiriTrol = birimTrol.birim.attack * SeneryoBirim[0].troller;
    double TopSaldiriVargBinici = birimVargBinici.birim.attack * SeneryoBirim[0].varg_binicileri;
    double TopSaldiriMizrakci = birimMizrakci.birim.attack * SeneryoBirim[0].mizrakcilar;
    double TopSaldiriOrkDovucsu = birimorkdovucsu.birim.attack * SeneryoBirim[0].ork_dovusculeri;

    double TopSaldiriKusatma = birimKusatma.birim.attack * SeneryoBirim[0].kusatma_makineleri;
    double TopSaldiriSuvari = birimSuvari.birim.attack * SeneryoBirim[0].suvariler;
    double TopSaldiriOkcu = birimokcu.birim.attack * SeneryoBirim[0].okcular;
    double TopSaldiriPiyade = birimPiyade.birim.attack * SeneryoBirim[0].piyadeler;

    // toplam savunma

    double TopSavunmaTrol = birimTrol.birim.defense * SeneryoBirim[0].troller;
    double TopSavunmaVargBinici = birimVargBinici.birim.defense * SeneryoBirim[0].varg_binicileri;
    double TopSavunmaMizrakci = birimMizrakci.birim.defense * SeneryoBirim[0].mizrakcilar;
    double TopSavunmaOrkDovucsu = birimorkdovucsu.birim.defense * SeneryoBirim[0].ork_dovusculeri;

    double TopSavunmaKusatma = birimKusatma.birim.defense * SeneryoBirim[0].kusatma_makineleri;
    double TopSavunmaSuvari = birimSuvari.birim.defense * SeneryoBirim[0].suvariler;
    double TopSavunmaOkcu = birimokcu.birim.defense * SeneryoBirim[0].okcular;
    double TopSavunmaPiyade = birimPiyade.birim.defense * SeneryoBirim[0].piyadeler;



    // grafik baslangıcdaki adamların sayılarıı atama


    int os = SeneryoBirim[0].ork_dovusculeri;
    int ms = SeneryoBirim[0].mizrakcilar;
    int vs = SeneryoBirim[0].varg_binicileri;
    int ts = SeneryoBirim[0].troller;
    int ps = SeneryoBirim[0].piyadeler;
    int As = SeneryoBirim[0].okcular;
    int ss = SeneryoBirim[0].suvariler;
    int ks = SeneryoBirim[0].kusatma_makineleri;


    double g1ilkSaglik = (float)birimorkdovucsu.birim.health/100;
    double g2ilkSaglik = (float)birimMizrakci.birim.health/100;
    double g3ilkSaglik = (float)birimVargBinici. birim.health/100;
    double g4ilkSaglik = (float)birimTrol. birim.health/100;
    double g5ilkSaglik = (float)birimPiyade. birim.health/100;
    double g6ilkSaglik = (float)birimokcu. birim.health/100;
    double g7ilkSaglik = (float)birimSuvari. birim.health/100;
    double g8ilkSaglik = (float)birimKusatma. birim.health/100;

    // grafik baslangıcdaki adamların canları atama
    




    char InsanKahramanSenaryo[MAX_LEN];
    char OrkKahramanSenaryo[MAX_LEN];


    char InsanCanavarSenaryo[MAX_LEN];
    char OrkCanavarSenaryo[MAX_LEN];



    int insansavunmaseneryo = 0;
    int orksavunmaseneryo = 0;
    int insansaldiriseneryo = 0;
    int orksaldiriseneryo = 0;
    int insanelitseneryo = 0;
    int orkelitseneryo = 0;
    int insanKusatmaseneryo = 0;
    int orkKusatmaseneryo = 0;



    int SaldiriSayisi = 1;







    //kahraman atama

    if (strcmp(SeneryoCek[0].kahraman, "Alparslan") == 0 || strcmp(SeneryoCek[0].kahraman, "Fatih_Sultan_Mehmet") == 0 || strcmp(SeneryoCek[0].kahraman, "Mete_Han") == 0 || strcmp(SeneryoCek[0].kahraman, "Yavuz_Sultan_Selim") == 0 || strcmp(SeneryoCek[0].kahraman, "Tugrul_Bey") == 0)
        strcpy(InsanKahramanSenaryo, SeneryoCek[0].kahraman);

    if (strcmp(SeneryoCek[1].kahraman, "Alparslan") == 0 || strcmp(SeneryoCek[1].kahraman, "Fatih_Sultan_Mehmet") == 0 || strcmp(SeneryoCek[1].kahraman, "Mete_Han") == 0 || strcmp(SeneryoCek[1].kahraman, "Yavuz_Sultan_Selim") == 0 || strcmp(SeneryoCek[1].kahraman, "Tugrul_Bey") == 0)
        strcpy(InsanKahramanSenaryo, SeneryoCek[1].kahraman);

    if (strcmp(SeneryoCek[0].kahraman, "Goruk_Vahsi") == 0 || strcmp(SeneryoCek[0].kahraman, "Thruk_Kemikkiran") == 0 || strcmp(SeneryoCek[0].kahraman, "Vrog_Kafakiran") == 0 || strcmp(SeneryoCek[0].kahraman, "Ugar_Zalim") == 0)
        strcpy(OrkKahramanSenaryo, SeneryoCek[0].kahraman);

    if (strcmp(SeneryoCek[1].kahraman, "Goruk_Vahsi") == 0 || strcmp(SeneryoCek[1].kahraman, "Thruk_Kemikkiran") == 0 || strcmp(SeneryoCek[1].kahraman, "Vrog_Kafakiran") == 0 || strcmp(SeneryoCek[1].kahraman, "Ugar_Zalim") == 0)
        strcpy(OrkKahramanSenaryo, SeneryoCek[1].kahraman);


    //canavar atama


    if (strcmp(SeneryoCek[0].Canavar, "Ejderha") == 0 || strcmp(SeneryoCek[0].Canavar, "Agri_Dagi_Devleri") == 0 || strcmp(SeneryoCek[0].Canavar, "Karakurt") == 0 || strcmp(SeneryoCek[0].Canavar, "Tepegoz") == 0 || strcmp(SeneryoCek[0].Canavar, "Samur") == 0)
        strcpy(InsanCanavarSenaryo, SeneryoCek[0].Canavar);

    if (strcmp(SeneryoCek[1].Canavar, "Ejderha") == 0 || strcmp(SeneryoCek[1].Canavar, "Agri_Dagi_Devleri") == 0 || strcmp(SeneryoCek[1].Canavar, "Karakurt") == 0 || strcmp(SeneryoCek[1].Canavar, "Tepegoz") == 0 || strcmp(SeneryoCek[1].Canavar, "Samur") == 0)
        strcpy(InsanCanavarSenaryo, SeneryoCek[1].Canavar);

    if (strcmp(SeneryoCek[0].Canavar, "Kara_Troll") == 0 || strcmp(SeneryoCek[0].Canavar, "Golge_Kurtlari") == 0 || strcmp(SeneryoCek[0].Canavar, "Camur_Devleri") == 0 || strcmp(SeneryoCek[0].Canavar, "Ates_Iblisi") == 0 || strcmp(SeneryoCek[0].Canavar, "Makrog_Savas_Beyi") == 0 || strcmp(SeneryoCek[0].Canavar, "Buz_Devleri") == 0)
        strcpy(OrkCanavarSenaryo, SeneryoCek[0].Canavar);

    if (strcmp(SeneryoCek[1].Canavar, "Kara_Troll") == 0 || strcmp(SeneryoCek[1].Canavar, "Golge_Kurtlari") == 0 || strcmp(SeneryoCek[1].Canavar, "Camur_Devleri") == 0 || strcmp(SeneryoCek[1].Canavar, "Ates_Iblisi") == 0 || strcmp(SeneryoCek[1].Canavar, "Makrog_Savas_Beyi") == 0 || strcmp(SeneryoCek[1].Canavar, "Buz_Devleri") == 0)
        strcpy(OrkCanavarSenaryo, SeneryoCek[1].Canavar);





    if (SeneryoBirim[0].kusatma_makineleri == 8)
    {

        orksaldiriseneryo = SeneryoCek[0].saldiri_gelistirmesi;
        insansavunmaseneryo = SeneryoCek[0].savunma_ustaligi;



    }
    else if (SeneryoBirim[0].kusatma_makineleri == 12)
    {


        insansavunmaseneryo = SeneryoCek[0].savunma_ustaligi;
        orksaldiriseneryo = SeneryoCek[0].saldiri_gelistirmesi;

    }



    if (SeneryoBirim[0].kusatma_makineleri == 5)
    {
        orksaldiriseneryo = SeneryoCek[0].saldiri_gelistirmesi;
        insansavunmaseneryo = SeneryoCek[0].savunma_ustaligi;



    }
    if (SeneryoBirim[0].kusatma_makineleri == 10)
    {

        insansavunmaseneryo = SeneryoCek[0].savunma_ustaligi;
        orksaldiriseneryo = SeneryoCek[0].saldiri_gelistirmesi;

    }
    if (SeneryoBirim[0].kusatma_makineleri == 1000 && (strcmp(SeneryoCek[0].kahraman, "Yavuz_Sultan_Selim") == 0))
    {

        insanKusatmaseneryo = SeneryoCek[0].kusatma_ustaligi;
        orkelitseneryo = SeneryoCek[0].elit_egitim;

    }
    if (strcmp(SeneryoCek[0].kahraman, "Thruk_Kemikkiran") == 0)
    {

        insansavunmaseneryo = SeneryoCek[0].savunma_ustaligi;
        orksaldiriseneryo = SeneryoCek[0].saldiri_gelistirmesi;

    }
    if (SeneryoBirim[0].kusatma_makineleri == 1000 && SeneryoBirim[0].mizrakcilar == 1000)
    {

        insansavunmaseneryo = SeneryoCek[0].savunma_ustaligi;
        orksaldiriseneryo = SeneryoCek[0].saldiri_gelistirmesi;

    }
    if (SeneryoBirim[0].kusatma_makineleri == 1 && SeneryoBirim[0].mizrakcilar == 1)
    {

        insansavunmaseneryo = SeneryoCek[0].savunma_ustaligi;
        orksaldiriseneryo = SeneryoCek[0].saldiri_gelistirmesi;


    }

    if (SeneryoBirim[0].piyadeler == 300)
    {

        insansavunmaseneryo = SeneryoCek[0].savunma_ustaligi;
        orksaldiriseneryo = SeneryoCek[0].saldiri_gelistirmesi;


    }

    int tempK = 0, temp2K = 0;











    FILE* dosya5 = fopen("C:\\Users\\HP\\source\\repos\\ProLab1_1\\ProLab1_1\\savas_sim.txt", "w");
    if (dosya5 == NULL) {
        printf("Dosya olusturulurken hata meydana geldi.\n");
        return 1;
    }



    if (strcmp(InsanKahramanSenaryo, "Alparslan") == 0)
    {


        TopSavunmaPiyade = TopSavunmaPiyade * (float)(100 + (Kahramanlar[0].bonus_degeri)) / 100;
        fprintf(dosya5, "Alparslan piyadelere savunma bonusu yuzde %d \n", Kahramanlar[0].bonus_degeri);

    }




    else if (strcmp(InsanKahramanSenaryo, "Fatih_Sultan_Mehmet") == 0)
    {
        TopSaldiriKusatma = TopSaldiriKusatma * (float)(100 + (Kahramanlar[1].bonus_degeri)) / 100;
        fprintf(dosya5, "Fatih_Sultan_Mehmet KusatmaMakinelerine saldiri bonusu yuzde %d \n", Kahramanlar[1].bonus_degeri);



    }
    else  if (strcmp(InsanKahramanSenaryo, "Mete_Han") == 0)
    {
        TopSavunmaOkcu = TopSavunmaOkcu * (float)(100 + (Kahramanlar[2].bonus_degeri)) / 100;
        fprintf(dosya5, "Mete_Han Okcu Savunma bonusu yuzde %d \n", Kahramanlar[2].bonus_degeri);



    }
    else  if (strcmp(InsanKahramanSenaryo, "Yavuz_Sultan_Selim") == 0)
    {
        fprintf(dosya5, "Yavuz_Sultan_Selim suvarilere kritik vurus bonusu yuzde %d \n", Kahramanlar[3].bonus_degeri);


        tempK = 1;



    }

    else if (strcmp(InsanKahramanSenaryo, "Tugrul_Bey") == 0)
    {
        TopSaldiriOkcu = TopSaldiriOkcu * (float)(100 + (Kahramanlar[4].bonus_degeri)) / 100;
        fprintf(dosya5, "Tugrul_Bey Okcu Saldiri bonusu yuzde %d \n", Kahramanlar[4].bonus_degeri);


    }
    //orkkahramanseneryo
    if (strcmp(OrkKahramanSenaryo, "Goruk_Vahsi") == 0)
    {
        TopSaldiriOrkDovucsu = TopSaldiriOrkDovucsu * (float)(100 + (Kahramanlar[5].bonus_degeri)) / 100;
        fprintf(dosya5, "Goruk_Vahsi OrkDovucsu Saldiri bonusu yuzde %d \n", Kahramanlar[5].bonus_degeri);

    }

    else if (strcmp(OrkKahramanSenaryo, "Thruk_Kemikkiran") == 0)
    {
        TopSavunmaTrol = TopSavunmaTrol * (float)(100 + (Kahramanlar[6].bonus_degeri)) / 100;
        fprintf(dosya5, "Thruk_Kemikkiran Trol Savunma bonusu yuzde %d \n", Kahramanlar[6].bonus_degeri);

    }

    else if (strcmp(OrkKahramanSenaryo, "Vrog_Kafakiran") == 0)
    {

        fprintf(dosya5, "Vrog_Kafakiran VargBinici Saldiri bonusu yuzde %d \n", Kahramanlar[7].bonus_degeri);

        temp2K = 1;


    }
    else if (strcmp(OrkKahramanSenaryo, "Ugar_Zalim") == 0)
    {
        TopSavunmaTrol = TopSavunmaTrol * (float)(100 + (Kahramanlar[8].bonus_degeri)) / 100;
        TopSavunmaVargBinici = TopSavunmaVargBinici * (float)(100 + (Kahramanlar[8].bonus_degeri)) / 100;
        TopSavunmaMizrakci = TopSavunmaMizrakci * (float)(100 + (Kahramanlar[8].bonus_degeri)) / 100;
        TopSavunmaOrkDovucsu = TopSavunmaOrkDovucsu * (float)(100 + (Kahramanlar[8].bonus_degeri)) / 100;

        fprintf(dosya5, "Ugar_Zalim Trol Savunma bonusu yuzde %d \n", Kahramanlar[8].bonus_degeri);
        fprintf(dosya5, "Ugar_Zalim VargBinici Savunma bonusu yuzde %d \n", Kahramanlar[8].bonus_degeri);
        fprintf(dosya5, "Ugar_Zalim Mizrakci Savunma bonusu yuzde %d \n", Kahramanlar[8].bonus_degeri);
        fprintf(dosya5, "Ugar_Zalim OrkDovucsu Savunma bonusu yuzde %d \n", Kahramanlar[8].bonus_degeri);



    }

    //canavarlar//

    if (strcmp(InsanCanavarSenaryo, "Ejderha") == 0)
    {

        TopSaldiriPiyade = TopSaldiriPiyade * (float)(100 + (Canavarlar[0].etki_degeri)) / 100;
        fprintf(dosya5, "Ejderha Piyade Saldiri bonusu yuzde %d \n", Canavarlar[0].etki_degeri);



    }
    int tempC = 0;
    if (strcmp(InsanCanavarSenaryo, "Agri_Dagi_Devleri") == 0)
    {

        TopSavunmaSuvari = TopSavunmaSuvari * (float)(100 + (Canavarlar[1].etki_degeri)) / 100;
        fprintf(dosya5, "Agri_Dagi_Devleri Suvari Savunma etki degeri yuzde %d \n", Canavarlar[1].etki_degeri);


    }
    else if (strcmp(InsanCanavarSenaryo, "Tepegoz") == 0)
    {

        TopSaldiriOkcu = TopSaldiriOkcu * (float)(100 + (Canavarlar[2].etki_degeri)) / 100;
        fprintf(dosya5, "Tepegoz Suvari Saldiri bonusu yuzde %d \n", Canavarlar[2].etki_degeri);


    }
    else if (strcmp(InsanCanavarSenaryo, "Karakurt") == 0)
    {

        fprintf(dosya5, "Karakurt piyadelere Savunma bonusu yuzde %d \n", Canavarlar[3].etki_degeri);

        tempC = 1;


    }
    else if (strcmp(InsanCanavarSenaryo, "Samur") == 0)
    {

        TopSavunmaPiyade = TopSavunmaPiyade * (float)(100 + (Canavarlar[4].etki_degeri)) / 100;
        fprintf(dosya5, "Samur Piyade Savunma bonusu yuzde %d \n", Canavarlar[4].etki_degeri);


    }

    if (strcmp(OrkCanavarSenaryo, "Kara_Troll") == 0)
    {
        TopSaldiriTrol = TopSaldiriTrol * (float)(100 + (Canavarlar[5].etki_degeri)) / 100;
        fprintf(dosya5, "Kara_Troll Trol Saldiri bonusu yuzde %d \n", Canavarlar[5].etki_degeri);

    }




    if (strcmp(OrkCanavarSenaryo, "Golge_Kurtlari") == 0)
    {
        TopSavunmaVargBinici = TopSavunmaVargBinici * (float)(100 + (Canavarlar[6].etki_degeri)) / 100;
        fprintf(dosya5, "Golge_Kurtlari VargBinici Savunma bonusu yuzde %d \n", Canavarlar[6].etki_degeri);

    }
    else if (strcmp(OrkCanavarSenaryo, "Camur_Devleri") == 0)
    {
        TopSavunmaOrkDovucsu = TopSavunmaOrkDovucsu * (float)(100 + (Canavarlar[7].etki_degeri)) / 100;
        fprintf(dosya5, "Camur_Devleri OrkDovucsu Savunma bonusu yuzde %d \n", Canavarlar[7].etki_degeri);

    }
    else if (strcmp(OrkCanavarSenaryo, "Ates_Iblisi") == 0)
    {
        TopSaldiriVargBinici = TopSaldiriVargBinici * (float)(100 + (Canavarlar[8].etki_degeri)) / 100;
        fprintf(dosya5, "Ates_Iblisi VargBinici Saldiri bonusu yuzde %d \n", Canavarlar[8].etki_degeri);

    }
    else if (strcmp(OrkCanavarSenaryo, "Makrog_Savas_Beyi") == 0)
    {
        TopSavunmaTrol = TopSavunmaTrol * (100 + (float)(Canavarlar[9].etki_degeri)) / 100;
        fprintf(dosya5, "Makrog_Savas_Beyi Trol Savunma bonusu yuzde %d \n", Canavarlar[9].etki_degeri);


    }
    else if (strcmp(OrkCanavarSenaryo, "Buz_Devleri") == 0)
    {
        TopSavunmaMizrakci = TopSavunmaMizrakci * (float)(100 + (Canavarlar[10].etki_degeri)) / 100;
        fprintf(dosya5, "Buz_Devleri Mizrakci Savunma bonusu yuzde %d \n", Canavarlar[10].etki_degeri);

    }

    // arastırma
    if (insansavunmaseneryo == 1)
    {
        TopSavunmaPiyade = TopSavunmaPiyade * (float)(100 + Yetenekler[0].deger) / 100;
        TopSavunmaOkcu = TopSavunmaOkcu * (float)(100 + Yetenekler[0].deger) / 100;
        TopSavunmaSuvari = TopSavunmaSuvari * (float)(100 + Yetenekler[0].deger) / 100;
        TopSavunmaKusatma = TopSavunmaKusatma * (float)(100 + Yetenekler[0].deger) / 100;
        fprintf(dosya5, "Arastirmanin piyade uzerinde savunma etkisi  yuzde %d \n  ", Yetenekler[0].deger);
        fprintf(dosya5, "Arastirmanin okcu uzerinde savunma etkisi  yuzde %d \n", Yetenekler[0].deger);
        fprintf(dosya5, "Arastirmanin suvari uzerinde savunma etkisi  yuzde %d  \n ", Yetenekler[0].deger);
        fprintf(dosya5, "Arastirmanin kusatma uzerinde savunma etkisi  yuzde %d \n", Yetenekler[0].deger);


    }
    else if (insansavunmaseneryo == 2)
    {
        TopSavunmaPiyade = TopSavunmaPiyade * (float)(100 + Yetenekler[1].deger) / 100;
        TopSavunmaOkcu = TopSavunmaOkcu * (float)(100 + Yetenekler[1].deger) / 100;
        TopSavunmaSuvari = TopSavunmaSuvari * (float)(100 + Yetenekler[1].deger) / 100;
        TopSavunmaKusatma = TopSavunmaKusatma * (float)(100 + Yetenekler[1].deger) / 100;
        fprintf(dosya5, "Arastirmanin piyade uzerinde savunma etkisi  yuzde %d  \n", Yetenekler[1].deger);
        fprintf(dosya5, "Arastirmanin okcu uzerinde savunma etkisi  yuzde %d  \n", Yetenekler[1].deger);
        fprintf(dosya5, "Arastirmanin suvari uzerinde savunma etkisi  yuzde %d  \n", Yetenekler[1].deger);
        fprintf(dosya5, "Arastirmanin kusatma uzerinde savunma etkisi  yuzde %d  \n", Yetenekler[1].deger);

    }
    else if (insansavunmaseneryo == 3)
    {
        TopSavunmaPiyade = TopSavunmaPiyade * (float)(100 + Yetenekler[2].deger) / 100;
        TopSavunmaOkcu = TopSavunmaOkcu * (float)(100 + Yetenekler[2].deger) / 100;
        TopSavunmaSuvari = TopSavunmaSuvari * (float)(100 + Yetenekler[2].deger) / 100;
        TopSavunmaKusatma = TopSavunmaKusatma * (float)(100 + Yetenekler[2].deger) / 100;
        fprintf(dosya5, "Arastirmanin piyade uzerinde savunma etkisi  yuzde %d  \n", Yetenekler[2].deger);
        fprintf(dosya5, "Arastirmanin okcu uzerinde savunma etkisi  yuzde %d  \n", Yetenekler[2].deger);
        fprintf(dosya5, "Arastirmanin suvari uzerinde savunma etkisi  yuzde %d  \n", Yetenekler[2].deger);
        fprintf(dosya5, "Arastirmanin kusatma uzerinde savunma etkisi  yuzde %d  \n", Yetenekler[2].deger);


    }

    if (insansaldiriseneryo == 1)
    {
        TopSaldiriPiyade = TopSaldiriPiyade * (float)(100 + Yetenekler[3].deger) / 100;
        TopSaldiriOkcu = TopSaldiriOkcu * (float)(100 + Yetenekler[3].deger) / 100;
        TopSaldiriSuvari = TopSaldiriSuvari * (float)(100 + Yetenekler[3].deger) / 100;
        TopSaldiriKusatma = TopSaldiriKusatma * (float)(100 + Yetenekler[3].deger) / 100;
        fprintf(dosya5, "Arastirmanin piyade uzerinde saldiri etkisi  yuzde %d  \n", Yetenekler[3].deger);
        fprintf(dosya5, "Arastirmanin okcu uzerinde saldiri etkisi  yuzde %d  \n", Yetenekler[3].deger);
        fprintf(dosya5, "Arastirmanin suvari uzerinde saldiri etkisi  yuzde %d  \n", Yetenekler[3].deger);
        fprintf(dosya5, "Arastirmanin kusatma uzerinde saldiri etkisi  yuzde %d  \n", Yetenekler[3].deger);

    }
    if (insansaldiriseneryo == 2)
    {
        TopSaldiriPiyade = TopSaldiriPiyade * (float)(100 + Yetenekler[4].deger) / 100;
        TopSaldiriOkcu = TopSaldiriOkcu * (float)(100 + Yetenekler[4].deger) / 100;
        TopSaldiriSuvari = TopSaldiriSuvari * (float)(100 + Yetenekler[4].deger) / 100;
        TopSaldiriKusatma = TopSaldiriKusatma * (float)(100 + Yetenekler[4].deger) / 100;
        fprintf(dosya5, "Arastirmanin piyade uzerinde saldiri etkisi  yuzde %d  \n", Yetenekler[4].deger);
        fprintf(dosya5, "Arastirmanin okcu uzerinde saldiri etkisi  yuzde %d  \n", Yetenekler[4].deger);
        fprintf(dosya5, "Arastirmanin suvari uzerinde saldiri etkisi  yuzde %d  \n", Yetenekler[4].deger);
        fprintf(dosya5, "Arastirmanin kusatma uzerinde saldiri etkisi  yuzde %d  \n", Yetenekler[4].deger);


    }
    if (insansaldiriseneryo == 3)
    {
        TopSaldiriPiyade = TopSaldiriPiyade * (float)(100 + Yetenekler[5].deger) / 100;
        TopSaldiriOkcu = TopSaldiriOkcu * (float)(100 + Yetenekler[5].deger) / 100;
        TopSaldiriSuvari = TopSaldiriSuvari * (float)(100 + Yetenekler[5].deger) / 100;
        TopSaldiriKusatma = TopSaldiriKusatma * (float)(100 + Yetenekler[5].deger) / 100;
        fprintf(dosya5, "Arastirmanin piyade uzerinde saldiri etkisi  yuzde %d  \n", Yetenekler[5].deger);
        fprintf(dosya5, "Arastirmanin okcu uzerinde saldiri etkisi  yuzde %d  \n", Yetenekler[5].deger);
        fprintf(dosya5, "Arastirmanin suvari uzerinde saldiri etkisi  yuzde %d  \n", Yetenekler[5].deger);
        fprintf(dosya5, "Arastirmanin kusatma uzerinde saldiri etkisi  yuzde %d  \n", Yetenekler[5].deger);


    }

    int tempAInsan = 0, tempA2Insan = 0, tempA3Insan = 0;

    int tempAOrk = 0, tempA2Ork = 0, tempA3Ork = 0;

    if (insanelitseneryo == 1)
    {
        tempAInsan = 1;
        fprintf(dosya5, "Arastirmanin piyade uzerinde saldiri etkisi  yuzde %d  \n", Yetenekler[6].deger);
        fprintf(dosya5, "Arastirmanin Okcu uzerinde saldiri etkisi  yuzde %d  \n", Yetenekler[6].deger);
        fprintf(dosya5, "Arastirmanin suvari uzerinde saldiri etkisi  yuzde %d  \n", Yetenekler[6].deger);
        fprintf(dosya5, "Arastirmanin kusatma uzerinde saldiri etkisi  yuzde %d  \n", Yetenekler[6].deger);


    }

    if (insanelitseneryo == 2)
    {
        tempA2Insan = 2;
        fprintf(dosya5, "Arastirmanin piyade uzerinde saldiri etkisi  yuzde %d  \n", Yetenekler[7].deger);
        fprintf(dosya5, "Arastirmanin Okcu uzerinde saldiri etkisi  yuzde %d  \n", Yetenekler[7].deger);
        fprintf(dosya5, "Arastirmanin suvari uzerinde saldiri etkisi  yuzde %d  \n", Yetenekler[7].deger);
        fprintf(dosya5, "Arastirmanin kusatma uzerinde saldiri etkisi  yuzde %d  \n", Yetenekler[7].deger);

        


    }
    if (insanelitseneryo == 3)
    {
        tempA3Insan = 3;
        fprintf(dosya5, "Arastirmanin piyade uzerinde saldiri etkisi  yuzde %d  \n", Yetenekler[8].deger);
        fprintf(dosya5, "Arastirmanin Okcu uzerinde saldiri etkisi  yuzde %d  \n", Yetenekler[8].deger);
        fprintf(dosya5, "Arastirmanin suvari uzerinde saldiri etkisi  yuzde %d  \n", Yetenekler[8].deger);
        fprintf(dosya5, "Arastirmanin kusatma uzerinde saldiri etkisi  yuzde %d  \n", Yetenekler[8].deger);


    }
    if (insanKusatmaseneryo == 1)
    {

        TopSaldiriKusatma = TopSaldiriKusatma * (float)(100 + Yetenekler[9].deger) / 100;
        fprintf(dosya5, "Arastirmanin kusatma uzerinde saldiri etkisi  yuzde %d \n ", Yetenekler[9].deger);



    }
    if (insanKusatmaseneryo == 2)
    {

        TopSaldiriKusatma = TopSaldiriKusatma * (float)(100 + Yetenekler[10].deger) / 100;
        fprintf(dosya5, "Arastirmanin kusatma uzerinde saldiri etkisi  yuzde %d \n ", Yetenekler[10].deger);

    }
    if (insanKusatmaseneryo == 3)
    {

        TopSaldiriKusatma = TopSaldiriKusatma * (float)(100 + Yetenekler[11].deger) / 100;
        fprintf(dosya5, "Arastirmanin kusatma uzerinde saldiri etkisi  yuzde %d  \n", Yetenekler[11].deger);


    }
    // ork arastirma

    if (orksavunmaseneryo == 1)
    {
        TopSavunmaOrkDovucsu = TopSavunmaOrkDovucsu * (float)(100 + Yetenekler[0].deger) / 100;
        TopSavunmaMizrakci = TopSavunmaMizrakci * (float)(100 + Yetenekler[0].deger) / 100;
        TopSavunmaVargBinici = TopSavunmaVargBinici * (float)(100 + Yetenekler[0].deger) / 100;
        TopSavunmaTrol = TopSavunmaTrol * (float)(100 + Yetenekler[0].deger) / 100;
        fprintf(dosya5, "Arastirmanin OrkDovucsu uzerinde savunma etkisi  yuzde %d  \n", Yetenekler[0].deger);
        fprintf(dosya5, "Arastirmanin Mizrakci uzerinde savunma etkisi  yuzde %d  \n", Yetenekler[0].deger);
        fprintf(dosya5, "Arastirmanin VargBinici uzerinde savunma etkisi  yuzde %d  \n", Yetenekler[0].deger);
        fprintf(dosya5, "Arastirmanin Trol uzerinde  savunma etkisi yuzde %d  \n", Yetenekler[0].deger);



    }
    else if (orksavunmaseneryo == 2)
    {
        TopSavunmaOrkDovucsu = TopSavunmaOrkDovucsu * (float)(100 + Yetenekler[1].deger) / 100;
        TopSavunmaMizrakci = TopSavunmaMizrakci * (float)(100 + Yetenekler[1].deger) / 100;
        TopSavunmaVargBinici = TopSavunmaVargBinici * (float)(100 + Yetenekler[1].deger) / 100;
        TopSavunmaTrol = TopSavunmaTrol * (float)(100 + Yetenekler[1].deger) / 100;
        fprintf(dosya5, "Arastirmanin OrkDovucsu uzerinde savunma etkisi  yuzde %d  \n", Yetenekler[1].deger);
        fprintf(dosya5, "Arastirmanin Mizrakci uzerinde savunma etkisi  yuzde %d  \n", Yetenekler[1].deger);
        fprintf(dosya5, "Arastirmanin VargBinici uzerinde savunma etkisi  yuzde %d  \n", Yetenekler[1].deger);
        fprintf(dosya5, "Arastirmanin Trol uzerinde  savunma etkisi yuzde %d  \n", Yetenekler[1].deger);


    }
    else if (orksavunmaseneryo == 3)
    {
        TopSavunmaOrkDovucsu = TopSavunmaOrkDovucsu * (float)(100 + Yetenekler[2].deger) / 100;
        TopSavunmaMizrakci = TopSavunmaMizrakci * (float)(100 + Yetenekler[2].deger) / 100;
        TopSavunmaVargBinici = TopSavunmaVargBinici * (float)(100 + Yetenekler[2].deger) / 100;
        TopSavunmaTrol = TopSavunmaTrol * (float)(100 + Yetenekler[2].deger) / 100;
        fprintf(dosya5, "Arastirmanin OrkDovucsu uzerinde savunma etkisi  yuzde %d  \n", Yetenekler[2].deger);
        fprintf(dosya5, "Arastirmanin Mizrakci uzerinde savunma etkisi  yuzde %d  \n", Yetenekler[2].deger);
        fprintf(dosya5, "Arastirmanin VargBinici uzerinde savunma etkisi  yuzde %d  \n", Yetenekler[2].deger);
        fprintf(dosya5, "Arastirmanin Trol uzerinde  savunma etkisi yuzde %d  \n", Yetenekler[2].deger);



    }

    if (orksaldiriseneryo == 1)
    {
        TopSaldiriOrkDovucsu = TopSaldiriOrkDovucsu * (float)(100 + Yetenekler[3].deger) / 100;
        TopSaldiriMizrakci = TopSaldiriMizrakci * (float)(100 + Yetenekler[3].deger) / 100;
        TopSaldiriVargBinici = TopSaldiriVargBinici * (float)(100 + Yetenekler[3].deger) / 100;
        TopSaldiriTrol = TopSaldiriTrol * (float)(100 + Yetenekler[3].deger) / 100;
        fprintf(dosya5, "Arastirmanin OrkDovucsu uzerinde saldiri etkisi  yuzde %d  \n", Yetenekler[3].deger);
        fprintf(dosya5, "Arastirmanin Mizrakci uzerinde saldiri etkisi  yuzde %d  \n", Yetenekler[3].deger);
        fprintf(dosya5, "Arastirmanin VargBinici uzerinde saldiri etkisi  yuzde %d  \n", Yetenekler[3].deger);
        fprintf(dosya5, "Arastirmanin Trol uzerinde  saldiri etkisi yuzde %d  \n", Yetenekler[3].deger);


    }
    if (orksaldiriseneryo == 2)
    {
        TopSaldiriOrkDovucsu = TopSaldiriOrkDovucsu * (float)(100 + Yetenekler[4].deger) / 100;
        TopSaldiriMizrakci = TopSaldiriMizrakci * (float)(100 + Yetenekler[4].deger) / 100;
        TopSaldiriVargBinici = TopSaldiriVargBinici * (float)(100 + Yetenekler[4].deger) / 100;
        TopSaldiriTrol = TopSaldiriTrol * (float)(100 + Yetenekler[4].deger) / 100;
        fprintf(dosya5, "Arastirmanin OrkDovucsu uzerinde saldiri etkisi  yuzde %d  \n", Yetenekler[4].deger);
        fprintf(dosya5, "Arastirmanin Mizrakci uzerinde saldiri etkisi  yuzde %d  \n", Yetenekler[4].deger);
        fprintf(dosya5, "Arastirmanin VargBinici uzerinde saldiri etkisi  yuzde %d  \n", Yetenekler[4].deger);
        fprintf(dosya5, "Arastirmanin Trol uzerinde  saldiri etkisi yuzde %d  \n", Yetenekler[4].deger);


    }
    if (orksaldiriseneryo == 3)
    {
        TopSaldiriOrkDovucsu = TopSaldiriOrkDovucsu * (float)(100 + Yetenekler[5].deger) / 100;
        TopSaldiriMizrakci = TopSaldiriMizrakci * (float)(100 + Yetenekler[5].deger) / 100;
        TopSaldiriVargBinici = TopSaldiriVargBinici * (float)(100 + Yetenekler[5].deger) / 100;
        TopSaldiriTrol = TopSaldiriTrol * (float)(100 + Yetenekler[5].deger) / 100;
        fprintf(dosya5, "Arastirmanin OrkDovucsu uzerinde saldiri etkisi  yuzde %d  \n", Yetenekler[5].deger);
        fprintf(dosya5, "Arastirmanin Mizrakci uzerinde saldiri etkisi  yuzde %d  \n", Yetenekler[5].deger);
        fprintf(dosya5, "Arastirmanin VargBinici uzerinde saldiri etkisi  yuzde %d  \n", Yetenekler[5].deger);
        fprintf(dosya5, "Arastirmanin Trol uzerinde  saldiri etkisi yuzde %d  \n", Yetenekler[5].deger);


    }
    if (orkelitseneryo == 1)
    {
        tempAOrk = 1;


        fprintf(dosya5, "Arastirmanin OrkDovucsu uzerinde saldiri etkisi  yuzde %d  \n", Yetenekler[6].deger);
        fprintf(dosya5, "Arastirmanin Mizrakci uzerinde saldiri etkisi  yuzde %d  \n", Yetenekler[6].deger);
        fprintf(dosya5, "Arastirmanin VargBinici uzerinde saldiri etkisi  yuzde %d  \n", Yetenekler[6].deger);
        fprintf(dosya5, "Arastirmanin Trol uzerinde  saldiri etkisi yuzde %d  \n", Yetenekler[6].deger);


       

    }
    if (orkelitseneryo == 2)
    {
        tempA2Ork = 2;
        fprintf(dosya5, "Arastirmanin OrkDovucsu uzerinde saldiri etkisi  yuzde %d  \n", Yetenekler[7].deger);
        fprintf(dosya5, "Arastirmanin Mizrakci uzerinde saldiri etkisi  yuzde %d  \n", Yetenekler[7].deger);
        fprintf(dosya5, "Arastirmanin VargBinici uzerinde saldiri etkisi  yuzde %d  \n", Yetenekler[7].deger);
        fprintf(dosya5, "Arastirmanin Trol uzerinde  saldiri etkisi yuzde %d  \n", Yetenekler[7].deger);


    }
    if (orkelitseneryo == 3)
    {
        tempA3Ork = 3;
        fprintf(dosya5, "Arastirmanin OrkDovucsu uzerinde saldiri etkisi  yuzde %d  \n", Yetenekler[8].deger);
        fprintf(dosya5, "Arastirmanin Mizrakci uzerinde saldiri etkisi  yuzde %d  \n", Yetenekler[8].deger);
        fprintf(dosya5, "Arastirmanin VargBinici uzerinde saldiri etkisi  yuzde %d  \n", Yetenekler[8].deger);
        fprintf(dosya5, "Arastirmanin Trol uzerinde  saldiri etkisi yuzde %d  \n", Yetenekler[8].deger);


    }



    while (1)
    {

      



        
        int kontrol = 0;
        if (SaldiriSayisi == 1)
            kontrol = 1;

        if (kontrol == 0)
            SaldiriSayisi++;



        // yorgunluk

        if (SaldiriSayisi % 5 == 0)
        {


            TopSaldiriPiyade = TopSaldiriPiyade * 0.9;
            TopSaldiriOkcu = TopSaldiriOkcu * 0.9;
            TopSaldiriKusatma = TopSaldiriKusatma * 0.9;
            TopSaldiriMizrakci = TopSaldiriMizrakci * 0.9;
            TopSaldiriOrkDovucsu = TopSaldiriOrkDovucsu * 0.9;
            TopSaldiriSuvari = TopSaldiriSuvari * 0.9;
            TopSaldiriTrol = TopSaldiriTrol * 0.9;
            TopSaldiriVargBinici = TopSaldiriVargBinici * 0.9;

            TopSavunmaPiyade = TopSavunmaPiyade * 0.9;
            TopSavunmaOkcu = TopSavunmaOkcu * 0.9;
            TopSavunmaKusatma *= 0.9;
            TopSavunmaMizrakci *= 0.9;
            TopSavunmaOrkDovucsu *= 0.9;
            TopSavunmaSuvari *= 0.9;
            TopSavunmaTrol *= 0.9;
            TopSavunmaVargBinici *= 0.9;

        }
        // kritik vurus hesabı,kahraman,canavar elit seneryolar için

        if (tempK == 1)
        {

            if (SaldiriSayisi % Kahramanlar[3].bonus_degeri == 0)
            {
                TopSaldiriSuvari = TopSaldiriSuvari * (100 + (Kahramanlar[3].bonus_degeri)) / 100;


            }
        }
        if (temp2K == 1)
        {

            if (SaldiriSayisi % Kahramanlar[7].bonus_degeri == 0)
                TopSaldiriVargBinici = TopSaldiriVargBinici * (100 + (Kahramanlar[7].bonus_degeri)) / 100;
        }




        if (tempC == 1)
        {
            if (SaldiriSayisi % Canavarlar[3].etki_degeri == 0)
            {
                TopSaldiriOkcu = TopSaldiriOkcu * (100 + (Canavarlar[3].etki_degeri)) / 100;
            }

        }

        if (tempAInsan == 1)
        {

            if (SaldiriSayisi % Yetenekler[6].deger == 0)
            {
                TopSaldiriPiyade = TopSaldiriPiyade * (100 + Yetenekler[6].deger) / 100;
                TopSaldiriOkcu = TopSaldiriOkcu * (100 + Yetenekler[6].deger) / 100;
                TopSaldiriSuvari = TopSaldiriSuvari * (100 + Yetenekler[6].deger) / 100;
                TopSaldiriKusatma = TopSaldiriKusatma * (100 + Yetenekler[6].deger) / 100;

            }
        }
        if (tempA2Insan == 2)
        {

            if (SaldiriSayisi % Yetenekler[7].deger == 0)
            {
                TopSaldiriPiyade = TopSaldiriPiyade * (100 + Yetenekler[7].deger) / 100;
                TopSaldiriOkcu = TopSaldiriOkcu * (100 + Yetenekler[7].deger) / 100;
                TopSaldiriSuvari = TopSaldiriSuvari * (100 + Yetenekler[7].deger) / 100;
                TopSaldiriKusatma = TopSaldiriKusatma * (100 + Yetenekler[7].deger) / 100;

            }
        }


        if (tempA3Insan == 3)
        {

            if (SaldiriSayisi % Yetenekler[8].deger == 0)
            {
                TopSaldiriPiyade = TopSaldiriPiyade * (100 + Yetenekler[8].deger) / 100;
                TopSaldiriOkcu = TopSaldiriOkcu * (100 + Yetenekler[8].deger) / 100;
                TopSaldiriSuvari = TopSaldiriSuvari * (100 + Yetenekler[8].deger) / 100;
                TopSaldiriKusatma = TopSaldiriKusatma * (100 + Yetenekler[8].deger) / 100;

            }
        }

        if (tempAOrk == 1)
        {

            if (SaldiriSayisi % Yetenekler[6].deger == 0)
            {
                TopSaldiriOrkDovucsu = TopSaldiriOrkDovucsu * (100 + Yetenekler[6].deger) / 100;
                TopSaldiriMizrakci = TopSaldiriMizrakci * (100 + Yetenekler[6].deger) / 100;
                TopSaldiriVargBinici = TopSaldiriVargBinici * (100 + Yetenekler[6].deger) / 100;
                TopSaldiriTrol = TopSaldiriTrol * (100 + Yetenekler[6].deger) / 100;

            }
        }
        if (tempA2Ork == 2)
        {

            if (SaldiriSayisi % Yetenekler[7].deger == 0)
            {
                TopSaldiriOrkDovucsu = TopSaldiriOrkDovucsu * (100 + Yetenekler[7].deger) / 100;
                TopSaldiriMizrakci = TopSaldiriMizrakci * (100 + Yetenekler[7].deger) / 100;
                TopSaldiriVargBinici = TopSaldiriVargBinici * (100 + Yetenekler[7].deger) / 100;
                TopSaldiriTrol = TopSaldiriTrol * (100 + Yetenekler[7].deger) / 100;

            }
        }
        if (tempA3Ork == 3)
        {

            if (SaldiriSayisi % Yetenekler[8].deger == 0)
            {
                TopSaldiriOrkDovucsu = TopSaldiriOrkDovucsu * (100 + Yetenekler[8].deger) / 100;
                TopSaldiriMizrakci = TopSaldiriMizrakci * (100 + Yetenekler[8].deger) / 100;
                TopSaldiriVargBinici = TopSaldiriVargBinici * (100 + Yetenekler[8].deger) / 100;
                TopSaldiriTrol = TopSaldiriTrol * (100 + Yetenekler[8].deger) / 100;

            }
        }


       

        

        fprintf(dosya5, "\n\n\n%d.Adim:\n\n", SaldiriSayisi);
        float ToplamSaldiriInsan = TopSaldiriKusatma + TopSaldiriOkcu + TopSaldiriPiyade + TopSaldiriSuvari;
        fprintf(dosya5, "Insan Toplam Saldiri=(kusatma_makineleriToplamGuc)%f %d(Adet)+(okcularToplamGuc)%f %d(Adet)+(piyadelerToplamGuc)%f %d(Adet)+(SuvarilerToplamGuc)%f %d(Adet)=%.2f\n\n", TopSaldiriKusatma, SeneryoBirim[0].kusatma_makineleri,
            TopSaldiriOkcu, SeneryoBirim[0].okcular, TopSaldiriPiyade, SeneryoBirim[0].piyadeler, TopSaldiriSuvari, SeneryoBirim[0].suvariler, ToplamSaldiriInsan);
        float ToplamSavunmaOrk = TopSavunmaMizrakci + TopSavunmaOrkDovucsu + TopSavunmaVargBinici + TopSavunmaTrol;
        fprintf(dosya5, "Ork Toplam Savunma=(MizrakciToplamGuc)%f (%d)(Adet)+(OrkDovucsuToplamGuc)%f %d(Adet)+(VargBiniciToplamGuc)%f %d(Adet)+(TrolToplamGuc)%f %d(Adet)=%.2f\n\n",
            TopSavunmaMizrakci, SeneryoBirim[0].mizrakcilar, TopSavunmaOrkDovucsu, SeneryoBirim[0].ork_dovusculeri, TopSavunmaVargBinici, SeneryoBirim[0].varg_binicileri, TopSavunmaTrol, SeneryoBirim[0].troller, ToplamSavunmaOrk);


        float c = ToplamSavunmaOrk / ToplamSaldiriInsan;

        float NetHasar = ToplamSaldiriInsan * (1.0 - (c));
        fprintf(dosya5, "Net Hasar=ToplamSaldiriInsan*(1-(ToplamSavunmaOrk/ToplamSaldiriInsan))\n%.2f*(1-(%.2f/%.2f))=%f\n", ToplamSaldiriInsan, ToplamSavunmaOrk,
            ToplamSaldiriInsan, NetHasar);





        // kalan canlar
        if (NetHasar > 0)
        {
            float OrkDovuscusu = (float)TopSavunmaOrkDovucsu / ToplamSavunmaOrk;

            float  OrantiliHasarOrkDovuscu = (float)ToplamSavunmaOrk * OrkDovuscusu;

            float kayipOrkDovuscusu = (float)OrantiliHasarOrkDovuscu / SeneryoBirim[0].ork_dovusculeri;
            int kayipOrkDovuscusu1 = birimorkdovucsu.birim.health - (int)kayipOrkDovuscusu;



            float mizrakci = (float)TopSavunmaMizrakci / ToplamSavunmaOrk;
            float OrantiliHasarMizrakci = (float)ToplamSavunmaOrk * mizrakci;

            float KayipMizrakci = (float)OrantiliHasarMizrakci / SeneryoBirim[0].mizrakcilar;
            int KayipMizrakci1 = birimMizrakci.birim.health - (int)KayipMizrakci;


            float VargBinici = TopSavunmaVargBinici / ToplamSavunmaOrk;
            float OrantiliHasarVargBinici = ToplamSavunmaOrk * VargBinici;

            float KayipVargBinici = OrantiliHasarVargBinici / SeneryoBirim[0].varg_binicileri;
            int KayipVargBinici1 = birimVargBinici.birim.health - (int)KayipVargBinici;

            float Trol = TopSavunmaTrol / ToplamSavunmaOrk;
            float OrantiliHasarTrol = ToplamSavunmaOrk * Trol;

            float kayipTrol = OrantiliHasarTrol / SeneryoBirim[0].troller;
            int kayipTrol1 = birimTrol.birim.health - (int)kayipTrol;




            fprintf(dosya5, "\nOrantili Hasar Dagilimi:  OrkDovuscusu=%f/%.1f=%.4f=>%.1f*%f=%f hasar\n", TopSavunmaOrkDovucsu, ToplamSavunmaOrk,
                OrkDovuscusu, ToplamSavunmaOrk, OrkDovuscusu, OrantiliHasarOrkDovuscu);
            fprintf(dosya5, "Sağlık Puanı = Eski Sağlık Puanı - Net Hasar / Birim Sayısı\n");
            if (birimorkdovucsu.birim.health > 0&&OrantiliHasarOrkDovuscu>0)
            {
                fprintf(dosya5, "\n OrkDovuscusu Kalan can:%d-%f=%d", birimorkdovucsu.birim.health, kayipOrkDovuscusu, kayipOrkDovuscusu1);
            }

            fprintf(dosya5, "\n  mizrakci=%f/%.1f=%.4f=>%.1f*%f=%f hasar\n", TopSavunmaMizrakci, ToplamSavunmaOrk,
                mizrakci, ToplamSavunmaOrk, mizrakci, OrantiliHasarMizrakci);

            if (birimMizrakci.birim.health > 0&&OrantiliHasarMizrakci>0)
            {
                fprintf(dosya5, "\n mizrakci Kalan can:%d-%f=%d", birimMizrakci.birim.health, KayipMizrakci, KayipMizrakci1);
            }


            fprintf(dosya5, "\n  VargBinici=%f/%.1f=%.4f=>%.1f*%f=%f hasar\n", TopSavunmaVargBinici, ToplamSavunmaOrk,
                VargBinici, ToplamSavunmaOrk, VargBinici, OrantiliHasarVargBinici);

            if (birimVargBinici.birim.health > 0&&OrantiliHasarVargBinici>0)
            {
                fprintf(dosya5, "\n VargBinici Kalan can:%d-%f=%d", birimVargBinici.birim.health, KayipVargBinici, KayipVargBinici1);
            }


            fprintf(dosya5, "\nTroller=%f/%.1f=%.4f=>%.1f*%f=%f hasar\n", TopSavunmaTrol, ToplamSavunmaOrk,
                Trol, ToplamSavunmaOrk, Trol, OrantiliHasarTrol);

            if (birimTrol.birim.health > 0&&OrantiliHasarTrol>0)
            {
                fprintf(dosya5, "\n Trol Kalan can:%d-%f=%d", birimTrol.birim.health, kayipTrol, kayipTrol1);

            }






            birimMizrakci.birim.health -= (OrantiliHasarMizrakci/ SeneryoBirim[0].mizrakcilar);
            birimTrol.birim.health -= (OrantiliHasarTrol/ SeneryoBirim[0].troller);
            birimVargBinici.birim.health -=( OrantiliHasarVargBinici/SeneryoBirim[0].varg_binicileri);
            birimorkdovucsu.birim.health -= (OrantiliHasarOrkDovuscu/ SeneryoBirim[0].ork_dovusculeri);
            
           

            if (birimMizrakci.birim.health <= 0)
                birimMizrakci.birim.health = 0;
            if (birimTrol.birim.health <= 0)
                birimTrol.birim.health = 0;
            if (birimVargBinici.birim.health <= 0)
                birimVargBinici.birim.health = 0;
            if (birimorkdovucsu.birim.health <= 0)
                birimorkdovucsu.birim.health = 0;


           




            if ((birimPiyade.birim.health == 0 && birimokcu.birim.health == 0 && birimSuvari.birim.health == 0 && birimKusatma.birim.health == 0))
            {
                fprintf(dosya5, "\nInsanların canı bitti Orklar Kazandi");
                break;

            }

            if (birimMizrakci.birim.health == 0 && birimorkdovucsu.birim.health == 0 && birimVargBinici.birim.health == 0 && birimTrol.birim.health == 0)
            {
                fprintf(dosya5, "\nOrklarin canı bitti Insanlar Kazandi");
                break;


            }
        }

       




        SaldiriSayisi++;

        // yorgunluk
        if (SaldiriSayisi % 5 == 0)
        {

            TopSaldiriPiyade = TopSaldiriPiyade * 0.9;
            TopSaldiriOkcu = TopSaldiriOkcu * 0.9;
            TopSaldiriKusatma = TopSaldiriKusatma * 0.9;
            TopSaldiriMizrakci = TopSaldiriMizrakci * 0.9;
            TopSaldiriOrkDovucsu = TopSaldiriOrkDovucsu * 0.9;
            TopSaldiriSuvari = TopSaldiriSuvari * 0.9;
            TopSaldiriTrol = TopSaldiriTrol * 0.9;
            TopSaldiriVargBinici = TopSaldiriVargBinici * 0.9;

            TopSavunmaPiyade = TopSavunmaPiyade * 0.9;
            TopSavunmaOkcu = TopSavunmaOkcu * 0.9;
            TopSavunmaKusatma *= 0.9;
            TopSavunmaMizrakci *= 0.9;
            TopSavunmaOrkDovucsu *= 0.9;
            TopSavunmaSuvari *= 0.9;
            TopSavunmaTrol *= 0.9;
            TopSavunmaVargBinici *= 0.9;

        }


        // kritik vurus hesabı

        if (tempK == 1)
        {

            if (SaldiriSayisi % Kahramanlar[3].bonus_degeri == 0)
            {
                TopSaldiriSuvari = TopSaldiriSuvari * (100 + (Kahramanlar[3].bonus_degeri)) / 100;


            }
        }
        if (temp2K == 1)
        {

            if (SaldiriSayisi % Kahramanlar[7].bonus_degeri == 0)
                TopSaldiriVargBinici = TopSaldiriVargBinici * (100 + (Kahramanlar[7].bonus_degeri)) / 100;
        }




        if (tempC == 1)
        {
            if (SaldiriSayisi % Canavarlar[3].etki_degeri == 0)
            {
                TopSaldiriOkcu = TopSaldiriOkcu * (100 + (Canavarlar[3].etki_degeri)) / 100;
            }

        }

        if (tempAInsan == 1)
        {

            if (SaldiriSayisi % Yetenekler[6].deger == 0)
            {
                TopSaldiriPiyade = TopSaldiriPiyade * (100 + Yetenekler[6].deger) / 100;
                TopSaldiriOkcu = TopSaldiriOkcu * (100 + Yetenekler[6].deger) / 100;
                TopSaldiriSuvari = TopSaldiriSuvari * (100 + Yetenekler[6].deger) / 100;
                TopSaldiriKusatma = TopSaldiriKusatma * (100 + Yetenekler[6].deger) / 100;

            }
        }
        if (tempA2Insan == 2)
        {

            if (SaldiriSayisi % Yetenekler[7].deger == 0)
            {
                TopSaldiriPiyade = TopSaldiriPiyade * (100 + Yetenekler[7].deger) / 100;
                TopSaldiriOkcu = TopSaldiriOkcu * (100 + Yetenekler[7].deger) / 100;
                TopSaldiriSuvari = TopSaldiriSuvari * (100 + Yetenekler[7].deger) / 100;
                TopSaldiriKusatma = TopSaldiriKusatma * (100 + Yetenekler[7].deger) / 100;

            }
        }


        if (tempA3Insan == 3)
        {

            if (SaldiriSayisi % Yetenekler[8].deger == 0)
            {
                TopSaldiriPiyade = TopSaldiriPiyade * (100 + Yetenekler[8].deger) / 100;
                TopSaldiriOkcu = TopSaldiriOkcu * (100 + Yetenekler[8].deger) / 100;
                TopSaldiriSuvari = TopSaldiriSuvari * (100 + Yetenekler[8].deger) / 100;
                TopSaldiriKusatma = TopSaldiriKusatma * (100 + Yetenekler[8].deger) / 100;

            }
        }

        if (tempAOrk == 1)
        {

            if (SaldiriSayisi % Yetenekler[6].deger == 0)
            {
                TopSaldiriOrkDovucsu = TopSaldiriOrkDovucsu * (100 + Yetenekler[6].deger) / 100;
                TopSaldiriMizrakci = TopSaldiriMizrakci * (100 + Yetenekler[6].deger) / 100;
                TopSaldiriVargBinici = TopSaldiriVargBinici * (100 + Yetenekler[6].deger) / 100;
                TopSaldiriTrol = TopSaldiriTrol * (100 + Yetenekler[6].deger) / 100;

            }
        }
        if (tempA2Ork == 2)
        {

            if (SaldiriSayisi % Yetenekler[7].deger == 0)
            {
                TopSaldiriOrkDovucsu = TopSaldiriOrkDovucsu * (100 + Yetenekler[7].deger) / 100;
                TopSaldiriMizrakci = TopSaldiriMizrakci * (100 + Yetenekler[7].deger) / 100;
                TopSaldiriVargBinici = TopSaldiriVargBinici * (100 + Yetenekler[7].deger) / 100;
                TopSaldiriTrol = TopSaldiriTrol * (100 + Yetenekler[7].deger) / 100;

            }
        }
        if (tempA3Ork == 3)
        {

            if (SaldiriSayisi % Yetenekler[8].deger == 0)
            {
                TopSaldiriOrkDovucsu = TopSaldiriOrkDovucsu * (100 + Yetenekler[8].deger) / 100;
                TopSaldiriMizrakci = TopSaldiriMizrakci * (100 + Yetenekler[8].deger) / 100;
                TopSaldiriVargBinici = TopSaldiriVargBinici * (100 + Yetenekler[8].deger) / 100;
                TopSaldiriTrol = TopSaldiriTrol * (100 + Yetenekler[8].deger) / 100;

            }
        }




        fprintf(dosya5, "\n\n\n\n%d.Adim:\n\n\n", SaldiriSayisi);
        float ToplamSaldiriOrk = TopSaldiriMizrakci + TopSaldiriOrkDovucsu + TopSaldiriVargBinici + TopSaldiriTrol;
        fprintf(dosya5, "Ork Toplam Saldiri=(MizrakciToplamGuc)%f %d(Adet)+(ork_dovusculeriToplamGuc)%f %d(Adet)+(VargBiniciToplamGuc)%f %d(Adet)+(TrolToplamGuc)%f %d(Adet)=%.2f\n\n", TopSaldiriMizrakci, SeneryoBirim[0].mizrakcilar,
            TopSaldiriOrkDovucsu, SeneryoBirim[0].ork_dovusculeri, TopSaldiriVargBinici, SeneryoBirim[0].varg_binicileri, TopSaldiriTrol, SeneryoBirim[0].troller, ToplamSaldiriOrk);

        float ToplamSavunmaInsan = TopSavunmaKusatma + TopSavunmaOkcu + TopSavunmaPiyade + TopSavunmaSuvari;
        fprintf(dosya5, "Insan Toplam Savunma=(KusatmaToplamGuc)%f (%d)(Adet)+(OkcuToplamGuc)%f %d(Adet)+(PiyadeToplamGuc)%f %d(Adet)+(SuvariToplamGuc)%f %d(Adet)=%.2f\n\n",
            TopSavunmaKusatma, SeneryoBirim[0].kusatma_makineleri, TopSavunmaOkcu, SeneryoBirim[0].okcular, TopSavunmaPiyade, SeneryoBirim[0].piyadeler, TopSavunmaSuvari, SeneryoBirim[0].suvariler, ToplamSavunmaInsan);






        NetHasar = ToplamSaldiriOrk * (1.0 - (ToplamSavunmaInsan / ToplamSaldiriOrk));
        fprintf(dosya5, "Net Hasar=ToplamSaldiriOrk*(1-(ToplamSavunmaInsan/ToplamSaldiriOrk))\n%.2f*(1-(%.2f/%.2f))=%f\n", ToplamSaldiriOrk, ToplamSavunmaInsan,
            ToplamSaldiriOrk, NetHasar);


        if (NetHasar > 0)
        {
            float Piyade = (float)TopSavunmaPiyade / ToplamSavunmaInsan;
            float  OrantiliHasarPiyade = (float)ToplamSavunmaInsan * Piyade;

            float kayipPiyade = (float)OrantiliHasarPiyade / SeneryoBirim[0].piyadeler;
            int kayipPiyade1 = birimPiyade.birim.health - (int)kayipPiyade;

            float Okcu = (float)TopSavunmaOkcu / ToplamSavunmaInsan;
            float  OrantiliHasarOkcu = (float)ToplamSavunmaInsan * Okcu;

            float kayipOkcu = (float)OrantiliHasarOkcu / SeneryoBirim[0].okcular;
            int kayipOkcu1 = birimokcu.birim.health - (int)kayipOkcu;

            float Suvariler = (float)TopSavunmaSuvari / ToplamSavunmaInsan;
            float  OrantiliHasarSuvariler = (float)ToplamSavunmaInsan * Suvariler;

            float kayipSuvari = (float)OrantiliHasarSuvariler / SeneryoBirim[0].suvariler;
            int kayipSuvari1 = birimSuvari.birim.health - (int)kayipSuvari;


            float Kusatma = (float)TopSavunmaKusatma / ToplamSavunmaInsan;
            float  OrantiliHasarKusatma = (float)ToplamSavunmaInsan * Kusatma;

            float kayipKusatma = (float)OrantiliHasarKusatma / SeneryoBirim[0].kusatma_makineleri;
            int kayipKusatma1 = birimKusatma.birim.health - (int)kayipKusatma;


            fprintf(dosya5, "\nOrantili Hasar Dagilimi:  Piyade=%f/%.1f=%.4f=>%.1f*%f=%f hasar\n", TopSavunmaPiyade, ToplamSavunmaInsan,
                Piyade, ToplamSavunmaInsan, Piyade, OrantiliHasarPiyade);
            fprintf(dosya5, "Sağlık Puanı = Eski Sağlık Puanı - Net Hasar / Birim Sayısı\n");


            if (birimPiyade.birim.health > 0&&OrantiliHasarPiyade>0)
            {
                fprintf(dosya5, "\n  piyade Kalan can:%d-%f=%d", birimPiyade.birim.health, kayipPiyade, kayipPiyade1);
            }


            fprintf(dosya5, "\n  Okcu=%f/%.1f=%.4f=>%.1f*%f=%f hasar\n", TopSavunmaOkcu, ToplamSavunmaInsan,
                Okcu, ToplamSavunmaInsan, Okcu, OrantiliHasarOkcu);

            if (birimokcu.birim.health > 0&& OrantiliHasarOkcu>0)
            {
                fprintf(dosya5, "\n okcu Kalan can:%d-%f=%d ", birimokcu.birim.health, kayipOkcu, kayipOkcu1);
            }

            fprintf(dosya5, "\n  Suvariler=%f/%.1f=%.4f=>%.1f*%f=%f hasar\n", TopSavunmaSuvari, ToplamSavunmaInsan,
                Suvariler, ToplamSavunmaInsan, Suvariler, OrantiliHasarSuvariler);

            if (birimSuvari.birim.health > 0&&OrantiliHasarSuvariler>0)
            {
                fprintf(dosya5, "\n  Suvari Kalan can:%d-%f=%d", birimSuvari.birim.health, kayipSuvari, kayipSuvari1);
            }

            fprintf(dosya5, "\n Kusatma=%f/%.1f=%.4f=>%.1f*%f=%f hasar\n", TopSavunmaKusatma, ToplamSavunmaInsan,
                Kusatma, ToplamSavunmaInsan, Kusatma, OrantiliHasarKusatma);

            if (birimKusatma.birim.health > 0&& OrantiliHasarKusatma>0)
            {
                fprintf(dosya5, "\n  Kusatma Kalan can:%d-%f=%d", birimKusatma.birim.health, kayipKusatma, kayipKusatma1);

            }








            birimPiyade.birim.health -= (OrantiliHasarPiyade/ SeneryoBirim[0].piyadeler);
            birimokcu.birim.health -=( OrantiliHasarOkcu/ SeneryoBirim[0].okcular);
            birimSuvari.birim.health -= (OrantiliHasarSuvariler/ SeneryoBirim[0].suvariler);
            birimKusatma.birim.health -= (OrantiliHasarKusatma/ SeneryoBirim[0].kusatma_makineleri);
            
           

            if (birimPiyade.birim.health <= 0)
                birimPiyade.birim.health = 0;
            if (birimokcu.birim.health <= 0)
                birimokcu.birim.health = 0;
            if (birimSuvari.birim.health <= 0)
                birimSuvari.birim.health = 0;
            if (birimKusatma.birim.health <= 0)
                birimKusatma.birim.health = 0;






            

            if ((birimPiyade.birim.health == 0 && birimokcu.birim.health == 0 && birimSuvari.birim.health == 0 && birimKusatma.birim.health == 0))
            {
                fprintf(dosya5, "\nInsanların canı bitti Orklar Kazandi");
                break;

            }

            if (birimMizrakci.birim.health == 0 && birimorkdovucsu.birim.health == 0 && birimVargBinici.birim.health == 0 && birimTrol.birim.health == 0)
            {
                fprintf(dosya5, "\nOrklarin canı bitti Insanlar Kazandi");
                break;


            }









            //4.adim

            if (SaldiriSayisi == 4)
            {
                 saglikOrta1 =(double) birimorkdovucsu.birim.health/100;

                 saglikOrta2 = (double)birimMizrakci.birim.health/100;
                 saglikOrta3 = (double)birimVargBinici.birim.health / 100;

                 saglikOrta4 = (double)birimTrol.birim.health / 100;

                 saglikOrta5 = (double)birimPiyade.birim.health / 100;
                 saglikOrta6 = (double)birimokcu.birim.health / 100;
                 saglikOrta7 = (double)birimSuvari.birim.health / 100;
                 saglikOrta8 = (double)birimKusatma.birim.health / 100;

            }
                  







            
        }

      


    }
    fclose(dosya5);


    //grafik1
              
    
    //  ilk sayıları
    g1 = os;
    g2 = ms;
    g3 = vs;
    g4 = ts;
    g5 = ps;
    g6 = As;
    g7 = ss;
    g8 = ks;
    
      //son sayıları
     g1Son = SeneryoBirim[0].ork_dovusculeri;
     g2Son = SeneryoBirim[0].mizrakcilar;
     g3Son = SeneryoBirim[0].varg_binicileri;
     g4Son = SeneryoBirim[0].troller;
     g5Son = SeneryoBirim[0].piyadeler;
     g6Son = SeneryoBirim[0].okcular;
     g7Son = SeneryoBirim[0].suvariler;
     g8Son = SeneryoBirim[0].kusatma_makineleri;


     // son canları
      g1SonSaglik = (double)birimorkdovucsu.birim.health/100;
      g2SonSaglik = (double)birimMizrakci.birim.health / 100;
      g3SonSaglik = (double)birimVargBinici.birim.health / 100;
      g4SonSaglik = (double)birimTrol.birim.health / 100;
      
      g5SonSaglik = (double)birimPiyade.birim.health / 100;
      g6SonSaglik = (double)birimokcu.birim.health / 100;
      g7SonSaglik = (double)birimSuvari.birim.health / 100;
      g8SonSaglik = (double)birimKusatma.birim.health/100;


       g1ilkSaglik1 = g1ilkSaglik;
       g2ilkSaglik2 = g2ilkSaglik;
       g3ilkSaglik3 = g3ilkSaglik;
       g4ilkSaglik4 = g4ilkSaglik;
       g5ilkSaglik5 = g5ilkSaglik;
       g6ilkSaglik6 = g6ilkSaglik;
       g7ilkSaglik7 = g7ilkSaglik;
       g8ilkSaglik8 = g8ilkSaglik;

     
     




    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Savaş Simülasyonu - Üç Ekran");

    init();
    memset(grid, 0, sizeof(grid));
    // Orklar
    placeUnits(ORK_DOVUSCULERI, os, 0, 2, g1ilkSaglik1);    // 100 ork, 
    placeUnits(MIZRAKCILAR, ms, 0, 3, g2ilkSaglik2);         // 80 mızrakçı
    placeUnits(VARG_BINICILERI, vs, 0, 6, g3ilkSaglik3);     // 50 varg binicisi, 
    placeUnits(TROLLER, ts, 0, 9, g4ilkSaglik4);             // 30 trol, 

    // İnsanlar
    placeUnits(PIYADE, ps, 10, 0, g5ilkSaglik5);           // 120 piyade, 
    placeUnits(OKCU, As, 10, 5, g6ilkSaglik6);               // 90 okçu, 
    placeUnits(SUVARI, ss, 10, 10, g7ilkSaglik7);           // 60 süvari, 
    placeUnits(KUSATMA_MAKINELERI, ks, 10, 15, g8ilkSaglik8);// 20 kuşatma makinesi,

    glutDisplayFunc(display);
    glutKeyboardFunc([](unsigned char key, int x, int y) {
        if (key == ' ') {
            currentScreen = (currentScreen % 3) + 1;
            memset(grid, 0, sizeof(grid));

            switch (currentScreen) {
            case 1:
                // İlk ekran - Başlangıç durumu
                placeUnits(ORK_DOVUSCULERI,g1, 0, 2,g1ilkSaglik1);    // 100 ork, 
                placeUnits(MIZRAKCILAR, g2, 0, 3, g2ilkSaglik2);         // 80 mızrakçı
                placeUnits(VARG_BINICILERI, g3, 0, 6, g3ilkSaglik3);     // 50 varg binicisi, 
                placeUnits(TROLLER, g4, 0, 9, g4ilkSaglik4);             // 30 trol, 

                // İnsanlar
                placeUnits(PIYADE, g5, 10, 0, g5ilkSaglik5);           // 120 piyade, 
                placeUnits(OKCU, g6, 10, 5, g6ilkSaglik6);               // 90 okçu, 
                placeUnits(SUVARI, g7, 10, 10, g7ilkSaglik7);           // 60 süvari, 
                placeUnits(KUSATMA_MAKINELERI, g8, 10, 15, g8ilkSaglik8);// 20 kuşat,
                break;

            case 2:
                // İkinci ekran - İlk değişim (İnsan birliklerinde azalma)
                placeUnits(ORK_DOVUSCULERI, g1Son, 0, 2, saglikOrta1);
                placeUnits(MIZRAKCILAR, g2Son, 0, 3, saglikOrta2);
                placeUnits(VARG_BINICILERI, g3Son, 0, 6, saglikOrta3);
                placeUnits(TROLLER, g4Son, 0, 9, saglikOrta4);

                placeUnits(PIYADE, g5Son, 10, 0, saglikOrta5);
                placeUnits(OKCU, g6Son, 10, 5, saglikOrta6);
                placeUnits(SUVARI, g7Son, 10, 10, saglikOrta7);
                placeUnits(KUSATMA_MAKINELERI, g8Son, 10, 15, saglikOrta8);
                break;

            case 3:
                // Üçüncü ekran - İkinci değişim (İnsan birliklerinde daha fazla azalma)
                placeUnits(ORK_DOVUSCULERI, g1Son, 0, 2, g1SonSaglik);
                placeUnits(MIZRAKCILAR, g2Son, 0, 3, g2SonSaglik);
                placeUnits(VARG_BINICILERI, g3Son, 0, 6, g3SonSaglik);
                placeUnits(TROLLER, g4Son, 0, 9, g4SonSaglik);

                placeUnits(PIYADE, g5Son, 10, 0, g5SonSaglik);
                placeUnits(OKCU, g6Son, 10, 5, g6SonSaglik);
                placeUnits(SUVARI, g7Son, 10, 10, g7SonSaglik);
                placeUnits(KUSATMA_MAKINELERI, g8Son, 10, 15, g8SonSaglik);
                break;
               
                break;
            }
            glutPostRedisplay();
        }
        });

    glutMainLoop();

    //grafik


    return 0;
}



