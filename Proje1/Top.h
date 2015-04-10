struct TOP_STRUCT
{
	ALLEGRO_BITMAP *image;
	float top_x;
	float top_y;
	float top_t_ucus;
	float top_vx;
	float top_vy;
	float top_v0;
	float top_aci;
	bool top_atis;
};

struct EFEKT_STRUCT
{
	ALLEGRO_BITMAP *image;
	float e_x;
	float e_y;
};

struct EFEKT_STRUCT efekt_nesne;
struct TOP_STRUCT top_nesne;

void topCizdir(float x, float y)
{
	top_nesne.top_x = x;
	top_nesne.top_y = y;

	al_draw_bitmap(top_nesne.image, top_nesne.top_x, top_nesne.top_y, 0);
}

void topResimYukle()
{
	top_nesne.image = al_load_bitmap("data_/top.png");

	if (!top_nesne.image)
	{
		printf("top yuklme hata");
		exit(0);
	}
}

void efekt_resim_yukle()
{
	efekt_nesne.image = al_load_bitmap("data_/efektler.png");
	al_convert_mask_to_alpha(efekt_nesne.image, al_map_rgb(0, 0, 0));

	if (!efekt_nesne.image)
	{
		printf("efekt yuklme hata");
		exit(0);
	}
}

void efekt_cizdir()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			al_draw_bitmap_region(efekt_nesne.image, i * 64, j * 64, 64, 64, top_nesne.top_x, top_nesne.top_y, 0);
		}
	}
}