
//Binalar ve genel özellikleri

typedef struct bina_
{
	//binalarýn resimlerini yukluyoruz
	ALLEGRO_BITMAP *bina_resim;
	float bina_x;
	float bina_y;
	int bina_gen;
	int bina_yuk;
}BINALAR;

struct patlama
{
	float pt_x;
	float pt_y;
	float pt_r;
	bool pt_var;
};

//Bina sayýsý tanýmlanýyor
enum { BINA_SAYISI = 6 , PT_SAYISI = 1000};

//Binalarý tuttuðumuz struct deðiþkeni
BINALAR binaDegisken[BINA_SAYISI];

struct patlama ptlma[PT_SAYISI];

//Arkaplan resmi
ALLEGRO_BITMAP *oyun_arkaplan;

void binaCizdir(int binaSayisi)
{
	for (int i = 0; i < binaSayisi; i++)
	{
		al_draw_scaled_bitmap(binaDegisken[i].bina_resim, 0, 0, 228, 421, binaDegisken[i].bina_x, binaDegisken[i].bina_y, binaDegisken[i].bina_gen, binaDegisken[i].bina_yuk, 0);
	}
}

//Binalarin ekrana cizilmesi
void bina_yerlestir(int binaSayisi, ALLEGRO_DISPLAY *display)
{
	for (int i = 0; i < binaSayisi; i++)
	{
		int deger = 100 + rand() % 200;
		binaDegisken[i].bina_x = 200 * i;
		binaDegisken[i].bina_y = 700 - deger;
		binaDegisken[i].bina_gen = 100 + rand() % 100;
		binaDegisken[i].bina_yuk = deger;

		if (i == 0)
		{
			karakter1 = karakterOlustur(karakter1, binaDegisken[i].bina_x, binaDegisken[i].bina_y, 1, display);
		}
		else if (i == BINA_SAYISI - 1)
		{
			karakter2 = karakterOlustur(karakter2, binaDegisken[i].bina_x, binaDegisken[i].bina_y, 2, display);
		}
	}
}

void binaResimYukle(int binaSayisi, ALLEGRO_DISPLAY *display)
{
	for (int i = 0; i < binaSayisi; i++)
	{
		binaDegisken[i].bina_resim = al_load_bitmap("data_/bina.png"); // bina resimlerini yukluyoruz...

		if ( !binaDegisken[i].bina_resim ) // Yukleme esnasinda hata var mi bakiyoruz...
		{
			al_show_native_message_box(display, "Error", "Error", "Failed to load image!",
				NULL, ALLEGRO_MESSAGEBOX_ERROR);

			for (int j = i; j > 0; j--)//Bellekte yer kaplamasin diye verileri yok ediyoruz...
				al_destroy_bitmap(binaDegisken[i].bina_resim);

			al_destroy_display(display);
			exit(0);
		}
	}

	//bina_yerlestir(binaSayisi, display);
}

void oyun_arkaplan_yukle()
{
	oyun_arkaplan = al_load_bitmap("data_/oyun_arkaplan.png");
}

void oyun_arkaplan_ciz()
{
	al_draw_bitmap(oyun_arkaplan, 0, 0, 0);
}

void binaYokEt()
{
	for (int i = 0; i < BINA_SAYISI; i++)
		al_destroy_bitmap(binaDegisken[i].bina_resim);
}

void patlama_olustur()
{
	for (int i = 0; i < PT_SAYISI; i++)
	{
		ptlma[i].pt_x = 0.0;
		ptlma[i].pt_y = 0.0;
		ptlma[i].pt_r = 25.0;
		ptlma[i].pt_var = false;
	}
}

void patlama_cizdir()
{
	int i = 0;
	while (ptlma[i].pt_var == true)
	{
		al_draw_filled_circle(ptlma[i].pt_x, ptlma[i].pt_y, ptlma[i].pt_r, al_map_rgb(17, 7, 137));
		i++;
	}
}

void patlama_ekle(struct TOP_STRUCT top1_)
{
	for (int i = 0; i < PT_SAYISI; i++)
	{
		if (ptlma[i].pt_var == false)
		{
			printf("patlama ekle %d\n", i);
			ptlma[i].pt_x = top1_.top_x;
			ptlma[i].pt_y = top1_.top_y;
			ptlma[i].pt_var = true;
			break;
		}
	}
}

void patlama_sil()
{
	for (int i = 0; i < PT_SAYISI; i++)
	{
		if (ptlma[i].pt_var == true)
		{
			ptlma[i].pt_var = false;
		}
		else
			break;
	}
}