
struct karakter_ok
{
	ALLEGRO_BITMAP *image;
	float ok_x;
	float ok_y;
	int yer;
};

struct karakter_ok k_ok, k_ok2;

void secim_ok_cizdir()
{
	al_draw_bitmap(k_ok.image, k_ok.ok_x, k_ok.ok_y, 0);
	al_draw_bitmap(k_ok2.image, k_ok2.ok_x, k_ok2.ok_y, 0);
}

void karakter_secim_ciz(ALLEGRO_FONT *font)
{
	al_draw_text(font, al_map_rgb(255, 255, 255), 100, 100, ALLEGRO_ALIGN_LEFT, "Karakter 1");
	al_draw_text(font, al_map_rgb(255, 0, 0), 100, 150, ALLEGRO_ALIGN_LEFT, "Kirmizi");
	al_draw_text(font, al_map_rgb(0, 255, 0), 100, 200, ALLEGRO_ALIGN_LEFT, "Yesil");
	al_draw_text(font, al_map_rgb(255, 102, 0), 100, 250, ALLEGRO_ALIGN_LEFT, "Turuncu");

	al_draw_text(font, al_map_rgb(255, 255, 255), 800, 100, ALLEGRO_ALIGN_LEFT, "Karakter 2");
	al_draw_text(font, al_map_rgb(255, 0, 0), 800, 150, ALLEGRO_ALIGN_LEFT, "Kirmizi");
	al_draw_text(font, al_map_rgb(0, 255, 0), 800, 200, ALLEGRO_ALIGN_LEFT, "Yesil");
	al_draw_text(font, al_map_rgb(255, 102, 0), 800, 250, ALLEGRO_ALIGN_LEFT, "Turuncu");

	secim_ok_cizdir();
}

void secim_ok_olustur()
{
	k_ok.image = al_load_bitmap("data_/top.png");
	k_ok.ok_x = 40;
	k_ok.ok_y = 150 - 25;
	k_ok.yer = 1;

	k_ok2.image = al_load_bitmap("data_/top.png");
	k_ok2.ok_x = 740;
	k_ok2.ok_y = 150 - 25;
	k_ok2.yer = 1;
}

void secim_ok_yer_ayarla1(int i, ALLEGRO_SAMPLE *menu_secim_ses)
{
	if (k_ok.yer == 1 && i == 1)
	{
		k_ok.yer = 2;
	}
	else if (k_ok.yer == 2 && i == -1)
	{
		k_ok.yer = 1;
	}
	else if (k_ok.yer == 2 && i == 1)
	{
		k_ok.yer = 3;
	}
	else if (k_ok.yer == 3 && i == -1)
	{
		k_ok.yer = 2;
	}

	switch (k_ok.yer)
	{
	case 1:
		k_ok.ok_x = 40;
		k_ok.ok_y = 150 - 25;
		break;
	case 2:
		k_ok.ok_x = 40;
		k_ok.ok_y = 200 - 25;
		break;
	case 3:
		k_ok.ok_x = 40;
		k_ok.ok_y = 250 - 25;
		break;
	}

	al_play_sample(menu_secim_ses, 0.8, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
}

void secim_ok_yer_ayarla2(int i, ALLEGRO_SAMPLE *menu_secim_ses)
{
	printf("kokyer %d\n", k_ok.yer);
	if (k_ok2.yer == 1 && i == 1)
	{
		k_ok2.yer = 2;
	}
	else if (k_ok2.yer == 2 && i == -1)
	{
		k_ok2.yer = 1;
	}
	else if (k_ok2.yer == 2 && i == 1)
	{
		k_ok2.yer = 3;
	}
	else if (k_ok2.yer == 3 && i == -1)
	{
		k_ok2.yer = 2;
	}

	switch (k_ok2.yer)
	{
	case 1:
		k_ok2.ok_x = 740;
		k_ok2.ok_y = 150 - 25;
		break;
	case 2:
		k_ok2.ok_x = 740;
		k_ok2.ok_y = 200 - 25;
		break;
	case 3:
		k_ok2.ok_x = 740;
		k_ok2.ok_y = 250 - 25;
		break;
	}

	al_play_sample(menu_secim_ses, 0.8, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
}