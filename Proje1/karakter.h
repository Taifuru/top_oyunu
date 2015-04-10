
//Karakter struct yapisi
typedef struct kr
{
	ALLEGRO_BITMAP *kr;
	float kr_x;
	float kr_y;
	float kr_score;
	bool kr_sira;
	int kr_hak;
}KARAKTER;

KARAKTER karakter1, karakter2;

void karakterRenkSec(int kr1, int kr2, KARAKTER *karakter1, KARAKTER *karakter2)
{
	char temp[30];

	switch (kr1)
	{
		case 1:
			wsprintf(temp, "data_/karakter_1_%d.png", 1);
			(*karakter1).kr = al_load_bitmap(temp);
			break;
		case 2:
			wsprintf(temp, "data_/karakter_1_%d.png", 2);
			(*karakter1).kr = al_load_bitmap(temp);
			break;
		case 3:
			wsprintf(temp, "data_/karakter_1_%d.png", 3);
			(*karakter1).kr = al_load_bitmap(temp);
			break;
	}

	switch (kr2)
	{
	case 1:
		wsprintf(temp, "data_/karakter_2_%d.png", 1);
		(*karakter2).kr = al_load_bitmap(temp);
		break;
	case 2:
		wsprintf(temp, "data_/karakter_2_%d.png", 2);
		(*karakter2).kr = al_load_bitmap(temp);
		break;
	case 3:
		wsprintf(temp, "data_/karakter_2_%d.png", 3);
		(*karakter2).kr = al_load_bitmap(temp);
		break;
	}
}

KARAKTER karakterOlustur(KARAKTER _kr, int x, int y, int renk, ALLEGRO_DISPLAY *display)
{
	char tmp[30];

	//Karakter rengi seçimi
	wsprintf(tmp, "data_/karakter_%d_1.png", renk);

	_kr.kr = al_load_bitmap(tmp); // Karakter resminin load edilmesi
	_kr.kr_score = 0;
	_kr.kr_x = x + 20.0;
	_kr.kr_y = y - al_get_bitmap_height(_kr.kr);
	_kr.kr_hak = 3;

	//Karakter sýrasý belirleniyor
	if (renk == 1)
	{
		_kr.kr_sira = true;
	}
	else
		_kr.kr_sira = false;

	if (!_kr.kr)
	{
		al_show_native_message_box(display, "Hata", "Hata", "Karakter dosyalari yuklenemedi!!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
	}

	return _kr;
}

void karakter_cizdir(KARAKTER _kr)
{
	al_draw_bitmap(_kr.kr, _kr.kr_x, _kr.kr_y , 0);
}