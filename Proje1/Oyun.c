#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define OYUN_PI 3.142857

#include "karakter.h"
#include "Top.h"
#include "Binalar.h"
#include "Atis.h"
#include "Degerler.h"
#include "Menu.h"
#include "YSkor.h"
#include "KarakterSecim.h"

int main(int argc, char **argv)
{
	srand(time(NULL));

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_SAMPLE *menu_arkaplan_ses = NULL;
	ALLEGRO_SAMPLE *menu_secim_ses = NULL;
	ALLEGRO_SAMPLE *carpma_ses = NULL;
	ALLEGRO_SAMPLE_ID carpma_ses_id;

	ALLEGRO_SAMPLE_INSTANCE *menu_arkaplan_ses_instance = NULL;
	ALLEGRO_FONT *oyun_font = NULL;
	ALLEGRO_FONT *oyun_sonu_font = NULL;
	ALLEGRO_FONT *yuksek_skor_font = NULL;

	if (!al_init())
	{
		al_show_native_message_box(display, "Hata", "Allegro Tanitim", "Allegro Baslatilamadi!!", 0, 0);
		return -1;
	}

	if (!al_install_audio()){
		al_show_native_message_box(display, "Hata", "Allegro Ses", "Allegro Ses Baslatilamadi!!", 0, 0);
		return -1;
	}

	if (!al_init_acodec_addon()){
		al_show_native_message_box(display, "Hata", "Allegro Ses", "Allegro Ses Codec yuklenemedi!!", 0, 0);
		return -1;
	}

	al_init_primitives_addon();
	al_init_font_addon(); // Font addon baþlatýlýyor
	al_init_ttf_addon();// ttf addon baþlatýlýyor

	//Fontlar yükleniyor
	oyun_font = al_load_font("data_/pirulen.ttf", 18, 0);
	oyun_sonu_font = al_load_font("data_/pirulen.ttf", 36, 0);
	yuksek_skor_font = al_load_font("data_/pirulen.ttf", 30, 0);

	//Ne kadar ses dosyasý kullandýðýmýzý yazýyoruz
	if (!al_reserve_samples(3))
	{
		fprintf(stderr, "failed to reserve samples!\n");
		return -1;
	}

	//Ses i dosyadan yukledik
	menu_arkaplan_ses = al_load_sample("data_/music/im_blue_1110.ogg");
	menu_secim_ses = al_load_sample("data_/music/menu_secim.ogg");
	carpma_ses = al_load_sample("data_/music/hit.wav");

	menu_arkaplan_ses_instance = al_create_sample_instance(menu_arkaplan_ses);
	al_set_sample_instance_playmode(menu_arkaplan_ses_instance, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(menu_arkaplan_ses_instance, al_get_default_mixer());

	//Ekran oluþturuldu
	display = al_create_display(SCREEN_W, SCREEN_H);

	if (!display)
	{
		al_show_native_message_box(display, "Hata", "Görüntü Ayarlarý", "Görüntü Olusturulamadi", 0, 0);
		return -1;
	}

	al_init_image_addon();//Resim eklentisi yuklendi
	al_install_keyboard();//Klavye eklendi

	//event oluþturma
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();

	//timer oluþturma
	ALLEGRO_TIMER *timer = al_create_timer(1 / FPS);
	ALLEGRO_TIMER *frameTimer = al_create_timer(1 / frameFPS);

	//Oluþturduðumuz timer ý event sýrasýna koyuyoruz
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_timer_event_source(frameTimer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	menu_resim_yukle(display);
	binaResimYukle(6, display);
	oyun_arkaplan_yukle();
	topResimYukle();
	efekt_resim_yukle();
	menu_ok_olustur();
	secim_ok_olustur();
	patlama_olustur();
	yuksek_skor_dosya_oku();
	gosterge_yukle();

	//Baþlangýç deðerleri atýlýyor
	oyun_sifirla(display);

	//Timer ý baþlattýk
	al_start_timer(timer);
	al_start_timer(frameTimer);

	while (done == false)
	{
		ALLEGRO_EVENT events;
		if (!oyun_sonu)
			al_wait_for_event(event_queue, &events);

		if (events.type == ALLEGRO_EVENT_TIMER)
		{
			if (events.timer.source == timer)
			{
				
			}
			else if (events.timer.source == frameTimer && oyun_cizim && !oyun_durdur)
			{
				carpisma_bina_bool = carpisma_bina(top_nesne, binaDegisken);

				if (t < top_nesne.top_t_ucus * 2)
				{
					if (karakter1.kr_sira)
					{
						egik_atis_hesap_x(karakter1, t, 1);
						egik_atis_hesap_y(karakter1, t, 1);
						carpisma_karakter_bool = carpisma_karakter(top_nesne, karakter2);
						karakter1.kr_score = skor_hesap(karakter1, carpisma_bina_bool, carpisma_karakter_bool, atis_sure);
					}
					else if (karakter2.kr_sira)
					{
						egik_atis_hesap_x(karakter2, t, 2);
						egik_atis_hesap_y(karakter2, t, 2);
						carpisma_karakter_bool = carpisma_karakter(top_nesne, karakter1);
						karakter2.kr_score = skor_hesap(karakter2, carpisma_bina_bool, carpisma_karakter_bool, atis_sure);
					}

					if (top_nesne.top_atis)
					{
						t += al_get_timer_speed(frameTimer) * 15;
					}

					if (atis_sure < 60)
					{
						atis_sure += al_get_timer_speed(frameTimer);
						atis_sure1 = atis_sure;
						wsprintf(atis_sure_yazi, "Atis Suresi : %d", atis_sure1);
					}
					else
						sira_degis = true;
				}

				if (t > top_nesne.top_t_ucus * 2 || sira_degis)
				{
					al_stop_sample(&carpma_ses_id);

					if (oyun_sonu == false)
					{
						ruzgar_hizi = -30 + rand() % 30;
						ruzgar_hizi1 = ruzgar_hizi;

						wsprintf(ruzgar_hizi_yazi, "Ruzgar Hizi : %d", ruzgar_hizi1);
					}

					if (karakter1.kr_sira && top_nesne.top_atis && karakter1.kr_hak > 0)
					{
						karakter1.kr_hak -= 1;
						top_nesne.top_atis = false;
						t = 0;
						atis_sure = 0;
						printf("kr1 %d\n", karakter1.kr_hak);
						carpisma_bina_bool = false;
						karakter1.kr_sira = false;
						karakter2.kr_sira = true;
					}
					else if (karakter2.kr_sira && top_nesne.top_atis && karakter2.kr_hak > 0)
					{
						karakter2.kr_hak -= 1;
						top_nesne.top_atis = false;
						t = 0;
						atis_sure = 0;
						carpisma_bina_bool = false;
						karakter1.kr_sira = true;
						karakter2.kr_sira = false;
					}

					if (karakter1.kr_hak == 0 && karakter2.kr_hak == 0 && oyun_sonu == false)
					{
						oyun_sonu = true;
						oyun_cizim = false;

						printf("Oyun Bitti\n");
					}
				}
			}

			draw = true;
		}
		else if (events.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (events.keyboard.keycode)
			{
				if (!oyun_durdur && !oyun_sonu)
				{
					case ALLEGRO_KEY_UP:
						if (menu_cizim)
						{
							menu_ok_yer_ayarla(-1, menu_secim_ses);
						}
						else if (oyun_cizim && !top_nesne.top_atis && aci < 90)
						{
							aci += 1;
							egik_atis_hesap_yon_tusu();
							wsprintf(aci_yazi, "Atis Acisi : %d", aci);
							gosterge_nesne[0].g_aci += 1;
							gosterge_nesne[2].g_aci += 1;
						}

						if (karakter_secim)
						{
							secim_ok_yer_ayarla2(-1, menu_secim_ses);
						}

						break;

					case ALLEGRO_KEY_DOWN:
						if (menu_cizim)
						{
							menu_ok_yer_ayarla(1, menu_secim_ses);
						}
						else if (oyun_cizim && !top_nesne.top_atis && aci > 20)
						{
							aci-= 1;
							egik_atis_hesap_yon_tusu();
							wsprintf(aci_yazi, "Atis Acisi : %d", aci);
							printf("%s\n", aci_yazi);
							gosterge_nesne[0].g_aci -= 1;
							gosterge_nesne[2].g_aci -= 1;
						}

						if (karakter_secim)
						{
							secim_ok_yer_ayarla2(1, menu_secim_ses);
						}

						break;

					case ALLEGRO_KEY_RIGHT:
						if ( hiz < 101 && oyun_cizim && !top_nesne.top_atis)
						{
							hiz += 1;
							hiz1 = hiz;
							egik_atis_hesap_yon_tusu();
							wsprintf(hiz_yazi, "Atis Hizi : %d", hiz1);
							gosterge_nesne[1].g_aci += 1;
							gosterge_nesne[3].g_aci += 1;
						}
						
						break;
					case ALLEGRO_KEY_LEFT:
						if (hiz > 39 && oyun_cizim && !top_nesne.top_atis )
						{
							hiz -= 1;
							hiz1 = hiz;
							egik_atis_hesap_yon_tusu();
							wsprintf(hiz_yazi, "Atis Hizi : %d", hiz1);
							gosterge_nesne[1].g_aci -= 1;
							gosterge_nesne[3].g_aci -= 1;
						}
						break;

					case ALLEGRO_KEY_SPACE:
						if (menu_cizim)
						{
							switch (m_oklari.yer)
							{
							case 1:
								menu_cizim = false;
								oyun_cizim = false;
								karakter_secim = true;

								break;
							case 2:
								menu_cizim = false;
								oyun_cizim = false;
								karakter_secim = false;
								yuksek_skor_cizim = true;
								break;
							case 3:
								done = true;
								break;
							}
						}
						else if (karakter_secim)
						{
							karakter_secim = false;
							oyun_cizim = true;
							karakterRenkSec(k_ok.yer, k_ok2.yer, &karakter1, &karakter2);
						}
						else if (oyun_cizim)
						{
							if (!top_nesne.top_atis)
							{
								top_nesne.top_atis = true;
							}
						}
						break;

					case ALLEGRO_KEY_W:
						if (oyun_cizim && !top_nesne.top_atis && ((aci + 10)<90))
						{
							aci += 10;
							egik_atis_hesap_yon_tusu();
							wsprintf(aci_yazi, "Atis Acisi : %d", aci);
							gosterge_nesne[0].g_aci += 10;
							gosterge_nesne[2].g_aci += 10;
						}

						if (karakter_secim)
						{
							secim_ok_yer_ayarla1(-1, menu_secim_ses);
						}

						break;

					case ALLEGRO_KEY_S:
						if (oyun_cizim && !top_nesne.top_atis && ((aci-10)>20) )
						{
							aci -= 10;
							egik_atis_hesap_yon_tusu();
							wsprintf(aci_yazi, "Atis Acisi : %d", aci);
							gosterge_nesne[0].g_aci -= 10;
							gosterge_nesne[2].g_aci -= 10;
						}

						if (karakter_secim)
						{
							secim_ok_yer_ayarla1(1, menu_secim_ses);
						}

						break;
					case ALLEGRO_KEY_D:
						if ((hiz+10) < 101 && oyun_cizim && !top_nesne.top_atis)
						{
							hiz += 10;
							hiz1 = hiz;
							egik_atis_hesap_yon_tusu();
							wsprintf(hiz_yazi, "Atis Hizi : %d", hiz1);
							gosterge_nesne[1].g_aci += 10;
							gosterge_nesne[3].g_aci += 10;
						}
						break;
					case ALLEGRO_KEY_A:
						if ((hiz-10) > 39 && oyun_cizim && !top_nesne.top_atis)
						{
							hiz -= 10;
							hiz1 = hiz;
							egik_atis_hesap_yon_tusu();
							wsprintf(hiz_yazi, "Atis Hizi : %d", hiz1);
							gosterge_nesne[1].g_aci -= 10;
							gosterge_nesne[3].g_aci -= 10;
						}
						break;
				}
				
				case ALLEGRO_KEY_P:
					if (oyun_cizim)
						oyun_durdur = !oyun_durdur;
					break;

				case ALLEGRO_KEY_ESCAPE:
					if (menu_cizim)
						done = true;
					else if (oyun_cizim)
					{
						menu_cizim = true;
						oyun_cizim = false;
					}
					else if (yuksek_skor_cizim)
					{
						yuksek_skor_cizim = false;
						menu_cizim = true;
					}
					break;
			}
		}

		if (draw)
		{
			draw = false;

			if (menu_cizim)
			{
				al_play_sample_instance(menu_arkaplan_ses_instance);
				menu_cizdir();
				menu_ok_cizdir();
			}
			else
			{
				al_stop_sample_instance(menu_arkaplan_ses_instance);
			}

			if (karakter_secim)
			{
				karakter_secim_ciz(oyun_font);
			}

			if (oyun_cizim)
			{
				oyun_arkaplan_ciz();

				binaCizdir(6);

				patlama_cizdir();

				karakter_cizdir(karakter1);
				karakter_cizdir(karakter2);

				al_draw_text(oyun_font, al_map_rgb(255, 255, 255), 500, 50, ALLEGRO_ALIGN_LEFT, aci_yazi);
				al_draw_text(oyun_font, al_map_rgb(255, 255, 255), 500, 68, ALLEGRO_ALIGN_LEFT, hiz_yazi);
				al_draw_text(oyun_font, al_map_rgb(255, 255, 255), 500, 86, ALLEGRO_ALIGN_LEFT, ruzgar_hizi_yazi);
				al_draw_text(oyun_font, al_map_rgb(255, 255, 255), 500, 104, ALLEGRO_ALIGN_LEFT, atis_sure_yazi);

				
				gosterge_ciz(oyun_font);
				topCizdir(top_nesne.top_x, top_nesne.top_y);

				if (oyun_durdur)
					oyun_durdur_buton_ciz();

				if (carpisma_bina_bool)
				{
					patlama_ekle(top_nesne);
					efekt_cizdir();
					al_play_sample(carpma_ses, 0.8, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &carpma_ses_id);
					carpisma_bina_bool = false;
				}

			}
			else if (oyun_sonu)
			{
				oyun_sonu_arkaplan_ciz();

				oyun_kazanan_ciz(oyun_sonu_font);
			}
			else if (yuksek_skor_cizim)
			{
				yuksek_skor_cizdir(oyun_font);
			}

			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));

			if (oyun_sonu)
			{
				al_rest(6);

				oyun_sifirla(display);
			}
		}
	}

	//Pointerlari silmeyi unutma
	al_destroy_display(display);
	yuksek_skor_dosya_yaz();
	return 0;
}