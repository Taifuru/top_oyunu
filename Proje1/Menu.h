
struct menu_arkaplan
{
	ALLEGRO_BITMAP *image;
	float x;
	float y;
};

struct butonlar
{
	ALLEGRO_BITMAP *image;
	char isim[20];
	float x;
	float y;
	float genislik;
	float yukseklik;
};

struct menu_ok
{
	ALLEGRO_BITMAP *image;
	float ok_x;
	float ok_y;
	int yer;
};

//Menüdeki butonlar için nesne oluþturduk
struct butonlar button[4];

//Menü arkaplaný için nesne oluþturduk
struct menu_arkaplan m_arkaplan;

//Menu oklari
struct menu_ok m_oklari;

//Butonlarýn resimlerinin dosyadan okunmasý
void buton_resim_yukle(ALLEGRO_DISPLAY *display)
{
	char dosya_isim[20];
	
	for (int i = 0; i < 4; i++)
	{
		wsprintf(dosya_isim, "data_/buton_%d.png", i+1);
		button[i].image = al_load_bitmap(dosya_isim);

		if (!button[i].image)
		{
			al_show_native_message_box(display, "Hata", "Hata", "Dosyalar yüklenirken bir hata oluþtu", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			al_destroy_display(display);
			exit(0);
		}
	}
}

void menu_arkaplan_resim_yukle(ALLEGRO_DISPLAY *display)
{
	m_arkaplan.image = al_load_bitmap("data_/menu_arkaplan.png");
	if (!m_arkaplan.image)
	{
		al_show_native_message_box(display, "Hata", "Hata", "Dosyalar yüklenirken bir hata oluþtu", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
		exit(0);
	}
}

void menu_cizdir()
{
	al_draw_bitmap(m_arkaplan.image, m_arkaplan.x, m_arkaplan.y, 0);

	for (int i = 0; i < 3; i++)
	{
		al_draw_bitmap(button[i].image, button[i].x, button[i].y, 0);
	}
}

void oyun_durdur_buton_ciz()
{
	al_draw_bitmap(button[3].image, button[3].x, button[3].y, 0);
}

void menu_resim_yukle(ALLEGRO_DISPLAY *display)
{
	buton_resim_yukle(display);
	menu_arkaplan_resim_yukle(display);

	m_arkaplan.x = 0;
	m_arkaplan.y = 0;

	for (int i = 0; i < 3; i++)
	{
		button[i].x = 450;
		button[i].y = 255 + i * 70;
		button[i].genislik = 300;
		button[i].yukseklik = 50;
	}

	button[3].x = 200;
	button[3].y = 50;
	button[3].genislik = 600;
	button[3].yukseklik = 600;
}

void menu_ok_olustur()
{
	m_oklari.image = al_load_bitmap("data_/top.png");
	m_oklari.ok_x = 780;
	m_oklari.ok_y = 255;
	m_oklari.yer = 1;
}

void menu_ok_cizdir()
{
	al_draw_bitmap(m_oklari.image, m_oklari.ok_x, m_oklari.ok_y, 0);
}

void menu_ok_yer_ayarla(int i, ALLEGRO_SAMPLE *menu_secim_ses)
{
	if (m_oklari.yer == 1 && i == 1)
	{
		m_oklari.yer = 2;
	}
	else if (m_oklari.yer == 2 && i == -1)
	{
		m_oklari.yer = 1;
	}
	else if (m_oklari.yer == 2 && i == 1)
	{
		m_oklari.yer = 3;
	}
	else if (m_oklari.yer == 3 && i == -1)
	{
		m_oklari.yer = 2;
	}

	switch (m_oklari.yer)
	{
		case 1:
			m_oklari.ok_x = 780;
			m_oklari.ok_y = 255;
			break;
		case 2:
			m_oklari.ok_x = 780;
			m_oklari.ok_y = 325;
			break;
		case 3:
			m_oklari.ok_x = 780;
			m_oklari.ok_y = 395;
			break;
	}

	al_play_sample(menu_secim_ses, 0.8, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
}

void oyun_sonu_arkaplan_ciz()
{
	al_draw_bitmap(m_arkaplan.image, m_arkaplan.x, m_arkaplan.y, 0);
}