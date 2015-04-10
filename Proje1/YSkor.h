bool yuksek_skor_kontrol(KARAKTER kr_)
{
	for (int i = 0; i < 3; i++)
	{
		if (kr_.kr_score > yuksek_skor_deger[i])
		{
			if (i == 0)
				yuksek_skor_deger[0] = kr_.kr_score;
			else if (i == 1)
			{
				yuksek_skor_deger[0] = yuksek_skor_deger[1];
				yuksek_skor_deger[1] = kr_.kr_score;
			}
			else if (i == 2)
			{
				yuksek_skor_deger[0] = yuksek_skor_deger[1];
				yuksek_skor_deger[1] = yuksek_skor_deger[2];
				yuksek_skor_deger[2] = kr_.kr_score;
			}

			wsprintf(yuksek_skor_yazi[i], "%d. Oyuncu\'nun Puani -- %d", i + 1, yuksek_skor_deger[i]);
			return true;
		}
	}

	return false;
}

void oyun_kazanan_ciz(ALLEGRO_FONT *font)
{
	if (karakter1.kr_score > karakter2.kr_score)
	{
		karakter_score_deger = karakter1.kr_score;
		wsprintf(kazanan_yazi, "Tebrikler!! %d. Oyuncu Kazandi!!! Puan : %d", 1, karakter_score_deger);
		if (yuksek_skor_kontrol(karakter1))
		{
			wsprintf(kazanan_yazi_skor, "Tebrikler!! En iyiler Tablosuna girdin!!");
		}
	}
	else
	{
		karakter_score_deger = karakter2.kr_score;
		wsprintf(kazanan_yazi, "Tebrikler!! %d. Oyuncu Kazandi!!! Puan : %d", 1, karakter_score_deger);
		if (yuksek_skor_kontrol(karakter2))
		{
			wsprintf(kazanan_yazi_skor, "Tebrikler!! En iyiler Tablosuna girdin!!");
		}
	}

	al_draw_text(font, al_map_rgb(17, 7, 137), 20, 350, ALLEGRO_ALIGN_LEFT, kazanan_yazi);
	al_draw_text(font, al_map_rgb(17, 7, 137), 20, 398, ALLEGRO_ALIGN_LEFT, kazanan_yazi_skor);
}

void yuksek_skor_cizdir(ALLEGRO_FONT *font)
{
	for (int i = 2; i >= 0; i--)
	{
		al_draw_text(font, al_map_rgb(17, 7, 137), 200, 200 + i * 35, ALLEGRO_ALIGN_LEFT, yuksek_skor_yazi[i]);
	}
}

void yuksek_skor_dosya_yaz()
{
	FILE *di;

	fopen_s(&di, "data_/yuksek_skor.txt", "w");
	if (di == NULL)
	{
		printf("Dosya acilamadi\n");
		exit(0);
	}

	for (int i = 0; i < 3; i++)
	{
		fprintf_s(di, "%d\n", yuksek_skor_deger[i]);
	}

	fclose(di);
}

void yuksek_skor_dosya_oku()
{
	FILE *di;

	fopen_s(&di, "data_/yuksek_skor.txt", "r");

	if (di == NULL)
	{
		for (int i = 0; i < 3; i++)
		{
			wsprintf(yuksek_skor_yazi[i], "%d. Oyuncu\'nun Puani -- 0", i+1);
		}
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			fscanf_s(di, "%d\n", &yuksek_skor_deger[i]);
			wsprintf(yuksek_skor_yazi[i], "%d. Oyuncu\'nun Puani -- %d", i+1, yuksek_skor_deger[i]);
		}

		fclose(di);
	}
}

float skor_hesap(KARAKTER kr_, bool bina_carp, bool kr_carp, float sure)
{
	if (bina_carp)
	{
		(kr_).kr_score += 1 / (sure + 1);
	}
	
	if (kr_carp)
	{
		(kr_).kr_score += 10 / (sure + 1);
	}

	printf("karakter score %f \n", (kr_).kr_score);
	return kr_.kr_score;
}