const int SCREEN_W = 1200;
const int SCREEN_H = 700;
const float FPS = 60.0;
const float frameFPS = 120.0;

bool carpisma_bina_bool = false;
bool carpisma_karakter_bool = false;

bool menu_cizim = true;
bool oyun_cizim = false;
bool oyun_durdur = false;
bool oyun_sonu = false;
bool yuksek_skor_cizim = false;
bool sira_degis = false;
bool karakter_secim = false;

char aci_yazi[30];
char hiz_yazi[30];
char ruzgar_hizi_yazi[30];
char kazanan_yazi[50];
char kazanan_yazi_skor[50];
char atis_sure_yazi[50];

char yuksek_skor_yazi[3][40];
int yuksek_skor_deger[3];

int karakter_score_deger;

void oyun_sifirla(ALLEGRO_DISPLAY *display)
{
	done = false;
	draw = true;
	deger = false;

	t = 0;
	aci = 45;
	hiz = 60.0;
	hiz1 = 20;

	ruzgar_hizi = 0;

	carpisma_bina_bool = false;
	carpisma_karakter_bool = false;

	menu_cizim = true;
	oyun_cizim = false;
	oyun_durdur = false;
	oyun_sonu = false;
	yuksek_skor_cizim = false;

	bina_yerlestir(BINA_SAYISI, display);

	egik_atis_hesap(karakter1);
	patlama_sil();
	gosterge_olustur();

	hiz1 = hiz;
	ruzgar_hizi = -30 + rand() % 30;
	ruzgar_hizi1 = ruzgar_hizi;

	atis_sure1 = atis_sure;

	//Aci yazisi
	wsprintf(aci_yazi, "Atis Acisi : %d", aci);
	wsprintf(hiz_yazi, "Atis Hizi : %d", hiz1);
	wsprintf(ruzgar_hizi_yazi, "Ruzgar Hizi : %d", ruzgar_hizi1);
	wsprintf(atis_sure_yazi, "Atis Suresi : %d", atis_sure1);
}