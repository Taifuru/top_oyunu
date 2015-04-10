bool done = false, draw = true, deger = false;

float t = 0;
float atis_sure = 1;
int atis_sure1;

int aci = 45;
float hiz = 60.0;
int hiz1;

float ruzgar_hizi = 0;
int ruzgar_hizi1;

struct gostergeler
{
	ALLEGRO_BITMAP *image;
	float g_x;
	float g_y;
	float g_gen;
	float g_yuk;
	int g_aci;
};

struct gostergeler gosterge_nesne[4];

void gosterge_yukle()
{
	for (int i = 0; i < 4; i++)
	{
		gosterge_nesne[i].image = al_load_bitmap("data_/gosterge.png");
	}
}

void gosterge_olustur()
{
	for (int i = 0; i < 4; i++)
	{
		gosterge_nesne[i].g_y = 100;
		gosterge_nesne[i].g_aci = 45;
		gosterge_nesne[i].g_gen = 100;
		gosterge_nesne[i].g_yuk = 100;
	}

	gosterge_nesne[0].g_x = 100;
	gosterge_nesne[1].g_x = 250;
	gosterge_nesne[2].g_x = 850;
	gosterge_nesne[3].g_x = 1000;
}

void gosterge_ciz(ALLEGRO_FONT *font)
{
	for (int i = 0; i < 4; i++)
	{
		if (i < 2)
		{
			al_draw_rotated_bitmap(gosterge_nesne[i].image, 50, 50, gosterge_nesne[i].g_x, gosterge_nesne[i].g_y, (360 - gosterge_nesne[i].g_aci)*OYUN_PI / 180, 0);
		}
		else
		{
			al_draw_rotated_bitmap(gosterge_nesne[i].image, 50, 50, gosterge_nesne[i].g_x, gosterge_nesne[i].g_y, (180 + gosterge_nesne[i].g_aci)*OYUN_PI / 180, ALLEGRO_FLIP_VERTICAL);
		}
	}

	al_draw_text(font, al_map_rgb(255, 255, 255), gosterge_nesne[0].g_x-80, gosterge_nesne[0].g_y + 100, ALLEGRO_ALIGN_LEFT, "Atis Acisi");
	al_draw_text(font, al_map_rgb(255, 255, 255), gosterge_nesne[1].g_x-20, gosterge_nesne[1].g_y + 100, ALLEGRO_ALIGN_LEFT, "Atis Hizi");
	al_draw_text(font, al_map_rgb(255, 255, 255), gosterge_nesne[2].g_x-80, gosterge_nesne[2].g_y + 100, ALLEGRO_ALIGN_LEFT, "Atis Acisi");
	al_draw_text(font, al_map_rgb(255, 255, 255), gosterge_nesne[3].g_x-20, gosterge_nesne[3].g_y + 100, ALLEGRO_ALIGN_LEFT, "Atis Hizi");
}

void egik_atis_hesap(KARAKTER _karakter)
{
	top_nesne.top_x = _karakter.kr_x;
	top_nesne.top_y = _karakter.kr_y - 60;

	top_nesne.top_aci = aci * OYUN_PI / 180;
	top_nesne.top_v0 = hiz + ruzgar_hizi;
	top_nesne.top_atis = false;

	top_nesne.top_t_ucus = ((top_nesne.top_v0*sin(top_nesne.top_aci) )* 2 )/ 9.8;
	
	top_nesne.top_vx = top_nesne.top_v0*cos(top_nesne.top_aci);
	top_nesne.top_vy = top_nesne.top_v0*sin(top_nesne.top_aci) - 9.8*top_nesne.top_t_ucus;
}

void egik_atis_hesap_yon_tusu()
{
	top_nesne.top_aci = aci * OYUN_PI / 180;
	top_nesne.top_v0 = hiz - ruzgar_hizi;
	top_nesne.top_atis = false;

	top_nesne.top_t_ucus = ((top_nesne.top_v0*sin(top_nesne.top_aci)) * 2) / 9.8;

	top_nesne.top_vx = top_nesne.top_v0*cos(top_nesne.top_aci);
	top_nesne.top_vy = top_nesne.top_v0*sin(top_nesne.top_aci) - 9.8*top_nesne.top_t_ucus;
}

float egik_atis_hesap_x(KARAKTER _karakter, float t_, int dgr)
{
	if (dgr == 1)
	{
		top_nesne.top_v0 = hiz - ruzgar_hizi;
		top_nesne.top_x = _karakter.kr_x + top_nesne.top_v0 * cos(top_nesne.top_aci) * t_;
	}
	else if (dgr == 2)
	{
		top_nesne.top_v0 = hiz - ruzgar_hizi;
		top_nesne.top_x = _karakter.kr_x - top_nesne.top_v0 * cos(top_nesne.top_aci) * t_;
	}
	return top_nesne.top_x;
}

float egik_atis_hesap_y(KARAKTER _karakter, float t_, int dgr)
{
	if (dgr == 1)
		top_nesne.top_y = _karakter.kr_y - 60 + -1 * (t_*top_nesne.top_v0*sin(top_nesne.top_aci) - 0.5*9.8*t_*t_);
	else if (dgr == 2)
		top_nesne.top_y = _karakter.kr_y - 60 + -1 * (t_*top_nesne.top_v0*sin(top_nesne.top_aci) - 0.5*9.8*t_*t_);

	return top_nesne.top_y;
}

bool carpisma_bina(struct TOP_STRUCT top, BINALAR bina[BINA_SAYISI])
{
	for (int i = 0; i < BINA_SAYISI; i++)
	{
		if ((top.top_x + al_get_bitmap_width(top.image))< bina[i].bina_x || top.top_x > (bina[i].bina_x + bina[i].bina_gen)
			|| (top.top_y + al_get_bitmap_height(top.image)) < bina[i].bina_y || top.top_y > (bina[i].bina_y + bina[i].bina_yuk))
		{
			//return false;
		}
		else
		{
			printf("carpisma\n");
			return true;
		}
	}
	return false;
}

bool carpisma_karakter(struct TOP_STRUCT top, KARAKTER karakter)
{
	if (top.top_x + al_get_bitmap_width(top.image) < karakter.kr_x || top.top_x > karakter.kr_x + al_get_bitmap_width(karakter.kr)
		|| top.top_y + al_get_bitmap_height(top.image) < karakter.kr_y || top.top_y > karakter.kr_y + al_get_bitmap_height(karakter.kr))
	{
		//return false;
	}
	else
	{
		printf("carpisma bina\n");
		return true;
	}

	return false;
}